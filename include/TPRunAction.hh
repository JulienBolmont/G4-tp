
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#ifndef TPRunAction_h
#define TPRunAction_h 1

#include "G4UserRunAction.hh"
#include "globals.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class G4Run;
class TPHistoManager;

class TPRunAction : public G4UserRunAction
{
public:

  TPRunAction(TPHistoManager*);
  virtual ~TPRunAction();

  virtual void BeginOfRunAction(const G4Run*);
  virtual void   EndOfRunAction(const G4Run*);
    
  void FillPerEvent(G4double, G4double); 

private:

  TPHistoManager* fHistoManager;

  G4double fSumEAbs, fSum2EAbs;    
  G4double fSumLAbs, fSum2LAbs;

};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

