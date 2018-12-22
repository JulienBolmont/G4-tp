
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#ifndef TPDetectorConstructionMessenger_h
#define TPDetectorConstructionMessenger_h 1

#include "G4UImessenger.hh"
#include "globals.hh"
#include <boost/filesystem.hpp>

class TPDetectorConstruction;
class G4UIdirectory;
class G4UIcmdWithAString;
class G4UIcmdWithoutParameter;

using namespace boost::filesystem;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class TPDetectorConstructionMessenger: public G4UImessenger
{
  public:

    TPDetectorConstructionMessenger(TPDetectorConstruction* );
   ~TPDetectorConstructionMessenger();

    virtual void SetNewValue(G4UIcommand*, G4String);

  private:

    TPDetectorConstruction*    fDetectorConstruction;

    G4UIdirectory*             fDetDir;
    G4UIcmdWithAString*        fDetCmd;
    G4UIcmdWithoutParameter*   fDetListCmd;

};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
