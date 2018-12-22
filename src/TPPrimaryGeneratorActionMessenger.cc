//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "TPPrimaryGeneratorActionMessenger.hh"

#include "TPPrimaryGeneratorAction.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithAString.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

TPPrimaryGeneratorActionMessenger::TPPrimaryGeneratorActionMessenger(TPPrimaryGeneratorAction* gAction)
:G4UImessenger(),fPrimaryGeneratorAction(gAction),
fGenDir(0),fGenCmd(0)
{

  fGenDir = new G4UIdirectory("/tp/generator/");
  fGenDir->SetGuidance("Particle generator for a TP.");

  fGenCmd = new G4UIcmdWithAString("/tp/generator/distrib", this);
  fGenCmd->SetGuidance(
    "Set the spatial distribution of generated particles. Three distributions are possible : 'sphere' for an isotropic distribution, 'disk' for an isotropic distribution in the XY plane, and 'beam' for a beam-like generation along the Z axis."
  );
  fGenCmd->SetParameterName("Shape",false);
  fGenCmd->AvailableForStates(G4State_Idle);

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

TPPrimaryGeneratorActionMessenger::~TPPrimaryGeneratorActionMessenger()
{

  delete fGenCmd;
  delete fGenDir;

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void TPPrimaryGeneratorActionMessenger::SetNewValue(G4UIcommand* command,
                                            G4String newValue)
{


  if( command == fGenCmd ) {

    if(newValue != "sphere" && newValue != "disk" && newValue != "beam") {

      G4cout << "Warning in TPPrimaryGeneratorActionMessenger::SetNewValue :" << G4endl;
      G4cout << "  Value " << newValue << " for tp/generator/distrib is not allowed ! Using 'sphere'." << G4endl;
      newValue = "sphere";

    }

    fPrimaryGeneratorAction->SetGenerationSpatialDistribution(newValue);

  }

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
