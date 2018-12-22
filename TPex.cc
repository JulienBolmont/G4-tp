
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "G4VPhysicsConstructor.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"
//#include "G4EmStandardPhysics_option4.hh"

#include "TPDetectorConstruction.hh"
#include "TPPrimaryGeneratorAction.hh"
#include "TPRunAction.hh"
#include "TPEventAction.hh"
#include "TPSteppingAction.hh"
#include "TPHistoManager.hh"
#include "TPAbortHandler.hh"
#include "PhysicsList.hh"


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

int main(int argc,char** argv)
{

  // Register Handler for clean run abort
  TPAbortHandler::Install();

  // Detect interactive mode (if no arguments) and define UI session
  //
  G4UIExecutive* ui = 0;
  if ( argc == 1 ) {
    ui = new G4UIExecutive(argc, argv);
  }

  // Construct the default run manager
  //
  G4RunManager * runManager = new G4RunManager;


  // set an HistoManager
  //
  TPHistoManager* histo = new TPHistoManager();


  // Set mandatory initialization classes
  //
  TPDetectorConstruction* detector = new TPDetectorConstruction(histo);
  runManager->SetUserInitialization(detector);
  runManager->SetUserInitialization(new PhysicsList);

  // Set user action classes
  //
  TPPrimaryGeneratorAction* gen_action =
                          new TPPrimaryGeneratorAction();
  runManager->SetUserAction(gen_action);
  //
  TPRunAction* run_action = new TPRunAction(histo);
  runManager->SetUserAction(run_action);
  //
  TPEventAction* event_action = new TPEventAction(histo, detector);
  runManager->SetUserAction(event_action);
  //
  TPSteppingAction* stepping_action =
                    new TPSteppingAction(event_action);
  runManager->SetUserAction(stepping_action);

  // Initialize G4 kernel
  //
  runManager->Initialize();

  // Initialize visualization
  //
  G4VisManager* visManager = new G4VisExecutive;
  visManager->Initialize();

  // Get the pointer to the User Interface manager
  //
  G4UImanager* UImanager = G4UImanager::GetUIpointer();

  if ( ! ui ) {
    // batch mode
    G4String command = "/control/execute ";
    G4String fileName = argv[1];
    UImanager->ApplyCommand(command+fileName);
  }
  else {
    // interactive mode
    UImanager->ApplyCommand("/control/execute init_vis.mac");
    ui->SessionStart();
    delete ui;
  }

  // Job termination
  delete visManager;
  delete histo;
  delete runManager;

  return 0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
