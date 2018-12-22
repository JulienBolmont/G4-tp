
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#ifndef TPHistoManagerMessenger_h
#define TPHistoManagerMessenger_h 1

#include "G4UImessenger.hh"
#include "globals.hh"

class TPHistoManager;
class G4UIdirectory;
class G4UIcmdWithAString;
class G4UIcmdWithAnInteger;
class G4UIcmdWithADoubleAndUnit;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class TPHistoManagerMessenger: public G4UImessenger
{
  public:

    TPHistoManagerMessenger(TPHistoManager* );
   ~TPHistoManagerMessenger();

    virtual void SetNewValue(G4UIcommand*, G4String);

  private:

    TPHistoManager*            	fHistoManager;

    G4UIdirectory*             	fDir;
    G4UIcmdWithAString*        	fFileNameCmd;
    G4UIcmdWithAnInteger* 		  fEbinCmd;
    G4UIcmdWithADoubleAndUnit* 	fEMinCmd;
	  G4UIcmdWithADoubleAndUnit* 	fEMaxCmd;

};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
