
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#ifndef TPEventAction_h
#define TPEventAction_h 1

#include "G4UserEventAction.hh"
#include "globals.hh"

class TPRunAction;
class TPHistoManager;
class TPDetectorConstruction;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class TPEventAction : public G4UserEventAction
{

public:

  TPEventAction(TPHistoManager *, TPDetectorConstruction *);
  virtual ~TPEventAction();

  virtual void  BeginOfEventAction(const G4Event *);
  virtual void    EndOfEventAction(const G4Event *);

  void SetFirstInteractionType(G4String intname) {if(fFirstInteractionName == "") fFirstInteractionName = intname;};
  G4String GetFirstInteractionType() {return fFirstInteractionName;};
  G4bool IsFirstInteractionTypeSet() {if(fFirstInteractionName == "") return false; else return true;};

  void SetEnergyAbsorbedAtFirstInteraction(G4double de) {if(fEnergyAbs_first_int == -1) fEnergyAbs_first_int = de;};
  G4double GetEnergyAbsorbedAtFirstInteraction() {return fEnergyAbs_first_int;};

  void AddEnergyAbs(G4double de) {fEnergyAbs += de;};
//  void AddEnergyAbsSmeared(G4double de_smeared) {fEnergyAbs += de_smeared;};
  void AddAComptonScattering() {fNbOfComptonScatteringsPerEvent++;}

private:

  TPHistoManager* fHistoManager;
  TPDetectorConstruction* fDetector;
  G4String  fFirstInteractionName;
  G4double  fEnergyAbs, fEnergyAbsSmeared, fEnergyAbs_first_int;
  G4int     fNbOfComptonScatteringsPerEvent;
  G4int     fPrintModulo;

};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
