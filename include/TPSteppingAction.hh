

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#ifndef TPSteppingAction_h
#define TPSteppingAction_h 1

#include "G4UserSteppingAction.hh"

class TPDetectorConstruction;
class TPEventAction;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class TPSteppingAction : public G4UserSteppingAction
{

public:
  TPSteppingAction(TPEventAction*);
  virtual ~TPSteppingAction();

  virtual void UserSteppingAction(const G4Step*);
    
private:
  TPEventAction*          fEventAction;
  
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
