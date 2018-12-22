//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "TPDetectorConstructionMessenger.hh"

#include "TPDetectorConstruction.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithoutParameter.hh"
#include "G4RunManager.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

TPDetectorConstructionMessenger::TPDetectorConstructionMessenger(TPDetectorConstruction* pDet)
:G4UImessenger(),fDetectorConstruction(pDet),
 fDetDir(0), fDetCmd(0)
{

  fDetDir = new G4UIdirectory("/tp/det/");
  fDetDir->SetGuidance("Experimental setup for a TP.");

  fDetCmd = new G4UIcmdWithAString("/tp/det/loadGeoGDML",this);
  fDetCmd->SetGuidance(
    "Load a geometry from a gdml file. Possible files can be listed using /tp/det/listAllGeometries."
  );
  fDetCmd->SetParameterName("GDMLFile",false);
  fDetCmd->AvailableForStates(G4State_Idle);

  fDetListCmd = new G4UIcmdWithoutParameter("/tp/det/listAllGeometries",this);
  fDetListCmd->SetGuidance(
    "List all possible geometries.\n..."
  );
  fDetListCmd->AvailableForStates(G4State_Idle);

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

TPDetectorConstructionMessenger::~TPDetectorConstructionMessenger()
{

  delete fDetCmd;
  delete fDetListCmd;
  delete fDetDir;

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void TPDetectorConstructionMessenger::SetNewValue(G4UIcommand* command,
                                          G4String newValue)
{

  if( command == fDetCmd ) {
    // We check if the file with name 'newValue' really exists. This uses Boost library.
    path pc(newValue);
    if(is_regular_file(pc)) fDetectorConstruction->SetGDMLFile(newValue);
    else {
      G4cout << "WARNING : The geometry file " << newValue << " was not found !" << G4endl;
      G4cout << "Using default." << G4endl;
    }

  }

  if( command == fDetListCmd ) {
    // This algorithm uses Boost library !
    G4cout << "List of all GDML files in directory \"geometries/\":" << G4endl;
    path p("./geometries");
    for (auto i = directory_iterator(p); i != directory_iterator(); i++)
    {
        if (!is_directory(i->path())) //we eliminate directories
        {
            G4cout << "- " << i->path().filename().string() << G4endl;
        }
        else continue;
    }

 }

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
