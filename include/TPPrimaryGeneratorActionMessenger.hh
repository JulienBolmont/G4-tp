
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#ifndef TPPrimaryGeneratorActionMessenger_h
#define TPPrimaryGeneratorActionMessenger_h 1

#include "G4UImessenger.hh"
#include "globals.hh"

class G4UIdirectory;
class G4UIcmdWithAString;
class TPPrimaryGeneratorAction;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class TPPrimaryGeneratorActionMessenger: public G4UImessenger
{
  public:

    TPPrimaryGeneratorActionMessenger(TPPrimaryGeneratorAction* );
   ~TPPrimaryGeneratorActionMessenger();

    virtual void SetNewValue(G4UIcommand*, G4String);

  private:

    TPPrimaryGeneratorAction*    fPrimaryGeneratorAction;

    G4UIdirectory*               fGenDir;
    G4UIcmdWithAString*          fGenCmd;

};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
