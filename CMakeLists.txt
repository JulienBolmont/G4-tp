#----------------------------------------------------------------------------
# Setup the project
cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
project(TP)

#----------------------------------------------------------------------------
# Find Geant4 package, activating all available UI and Vis drivers by default
# You can set WITH_GEANT4_UIVIS to OFF via the command line or ccmake/cmake-gui
# to build a batch mode only executable
#
option(WITH_GEANT4_UIVIS "Build example with Geant4 UI and Vis drivers" ON)
if(WITH_GEANT4_UIVIS)
  find_package(Geant4 REQUIRED ui_all vis_all)
else()
  find_package(Geant4 REQUIRED)
endif()

#----------------------------------------------------------------------------
# Setup Geant4 include directories and compile definitions
#
include(${Geant4_USE_FILE})
#message(INFO " Geant4 libraries are in ${Geant4_LIBRARIES}")

#----------------------------------------------------------------------------
# Find ROOT (required package)
#
find_package(ROOT REQUIRED)
if(ROOT_FOUND)
  message(INFO " ROOT ${ROOT_VERSION} found !")
else()
  message(FATAL_ERROR " ROOT was not found !")
endif()

if(NOT "${ROOT_INCLUDE_DIRS}" STREQUAL "")
  set(ROOT_INCLUDE_LOCATION ${ROOT_INCLUDE_DIRS})
  message(INFO " Using ROOT_INCLUDE_DIRS.")
elseif(NOT "${ROOT_INCLUDE_DIR}" STREQUAL "")
  set(ROOT_INCLUDE_LOCATION ${ROOT_INCLUDE_DIR})
  message(INFO " Using ROOT_INCLUDE_DIR.")
else()
  message(FATAL_ERROR " Cannot find ROOT headers !")
endif()
#message(INFO " ROOT libraries are in ${ROOT_LIBRARIES}")

#----------------------------------------------------------------------------
# Find BOOST library (required)
#
find_package(Boost REQUIRED filesystem system)
#message(INFO " Boost libraries are in ${Boost_LIBRARIES}")

#----------------------------------------------------------------------------
# Locate sources and headers for this project
#
include_directories(${PROJECT_SOURCE_DIR}/include
                    ${PROJECT_SOURCE_DIR}/shared/include
                    ${Geant4_INCLUDE_DIR}
                    ${ROOT_INCLUDE_LOCATION}
                    ${Boost_INCLUDE_DIRS})
file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc
                  ${PROJECT_SOURCE_DIR}/shared/src/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh
                  ${PROJECT_SOURCE_DIR}/shared/include/*.hh)
file(COPY ${PROJECT_SOURCE_DIR}/geometries DESTINATION ${PROJECT_BINARY_DIR}/)
file(COPY ${PROJECT_SOURCE_DIR}/analysis DESTINATION ${PROJECT_BINARY_DIR}/)

#----------------------------------------------------------------------------
# Add the executable, and link it to the Geant4 libraries
#
add_executable(TPex TPex.cc ${sources} ${headers})
target_link_libraries(TPex ${Geant4_LIBRARIES} ${ROOT_LIBRARIES} ${Boost_LIBRARIES})

#----------------------------------------------------------------------------
# Copy all scripts to the build directory, i.e. the directory in which we
# build TPex. This is so that we can run the executable directly because it
# relies on these scripts being in the current working directory.
#
set(TPex_SCRIPTS
    TPex.in run.mac run_tp.mac init_vis.mac vis.mac README.txt
  )

foreach(_script ${TPex_SCRIPTS})
  configure_file(
    ${PROJECT_SOURCE_DIR}/${_script}
    ${PROJECT_BINARY_DIR}/${_script}
    COPYONLY
    )
endforeach()

#----------------------------------------------------------------------------
# Install the executable to 'bin' directory under CMAKE_INSTALL_PREFIX
#
# install(TARGETS TPex DESTINATION bin)
