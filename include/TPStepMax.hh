
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#ifndef TPStepMax_h
#define TPStepMax_h 1

#include "globals.hh"
#include "G4VDiscreteProcess.hh"
#include "G4ParticleDefinition.hh"
#include "G4Step.hh"


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class TPStepMax : public G4VDiscreteProcess
{
  public:     

     TPStepMax(const G4String& processName ="UserStepMax");
    ~TPStepMax();

     virtual G4bool   IsApplicable(const G4ParticleDefinition&);    
     void     SetMaxStep(G4double);
     
     virtual G4double PostStepGetPhysicalInteractionLength(const G4Track& track,
                                             G4double   previousStepSize,
                                             G4ForceCondition* condition);

     virtual G4VParticleChange* PostStepDoIt(const G4Track&, const G4Step&);

     virtual G4double GetMeanFreePath(const G4Track&,G4double,G4ForceCondition*)
       {return DBL_MAX;};     // it is not needed here !

  private:

     G4double          fMaxChargedStep;

};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

