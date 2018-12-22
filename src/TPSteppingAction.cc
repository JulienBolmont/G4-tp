
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "TPSteppingAction.hh"

#include "TPDetectorConstruction.hh"
#include "TPEventAction.hh"

#include "G4Step.hh"
#include "G4VProcess.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

TPSteppingAction::TPSteppingAction(TPEventAction* evt)
: G4UserSteppingAction(),
  fEventAction(evt)
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

TPSteppingAction::~TPSteppingAction()
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
// In the function UserSteppingAction, we want to collect some information:
// - The type of first interaction in the event
// - The energy deposited by the e- right after the first interaction
//    (only for p.e. and compton)
// - We also count the number of compton scatterings of the primary gamma
void TPSteppingAction::UserSteppingAction(const G4Step* aStep)
{

  // Get volume of the current step
  G4VPhysicalVolume* volume
  = aStep->GetPreStepPoint()->GetTouchableHandle()->GetVolume();

  // Only the energy deposition in the detector is recorded so the stepping
  // action returns without doing anything if the step is outside the detector.
  if(volume->GetName() != "DetectorPhysVolume") return;

  // Collect total energy deposited during the step.
  G4double edep = aStep->GetTotalEnergyDeposit();

  // For each step, deposited energy is summed to finally get the deposited
  // energy per event at the end of event (see
  // TPEventAction::EndOfEventAction()).
  fEventAction->AddEnergyAbs(edep);


  // In the following, go into the details of what happened. -------------------

  // Get the track
  G4Track* aTrack = aStep->GetTrack();
  // Get the particle involved in this step
  G4String ParticleInStep = aTrack->GetParticleDefinition()->GetParticleName();

  // A boolean to tag the primary particle (should be a gamma in our case).
  // Primary particles do not have a creator process and GetCreatorProcess
  // returns a NULL pointer.
  // This primary particle can be scattered multiple times before being
  // absorbed.
  G4bool IsPrimary = (aTrack->GetCreatorProcess() == NULL);
  // Boolean to tag photons and electrons in the current step.
  G4bool IsGamma = (ParticleInStep == "gamma");
  G4bool IsElectron = (ParticleInStep == "e-");


  // Primary particles do not have a creator process !
  G4String CreatorProcessName;
  if(!IsPrimary)
    CreatorProcessName = aTrack->GetCreatorProcess()->GetProcessName();
  else CreatorProcessName = "primary : no creator process !";


  // From the step, get the process that just happened
  const G4VProcess* processDefinedTheStep
    = aStep->GetPostStepPoint()->GetProcessDefinedStep();

  G4cout << "----- Particle   : " << ParticleInStep << G4endl;
  G4cout << "----- Is primary ? " << IsPrimary << G4endl;
  G4cout << "----- Creator    : " << CreatorProcessName << G4endl;
  G4cout << "----- Process    : " << processDefinedTheStep->GetProcessName()
                                                                    << G4endl;
  G4cout << "----- EDEP       : " << edep << G4endl;

  // Get A table of all secondary particles created.
  const std::vector<const G4Track*>* secondary =
                                          aStep->GetSecondaryInCurrentStep();


  // For the incident gamma (primary), store the type of the first interaction.
  if(IsPrimary) {

    fEventAction->SetFirstInteractionType(
                                    processDefinedTheStep->GetProcessName());

    // If the primary gamma first interaction is a p.e. effect, we collect the
    // energy of the emitted electron + the energy deposited by X-rays.
    if(processDefinedTheStep->GetProcessName() == "phot") {
      // Sum of the energy deposited by the electron + the energy of the
      // X rays (edep).
      G4cout << "---- Energy deposited phot : " << edep +
                      (*secondary)[0]->GetKineticEnergy() << G4endl;
      fEventAction->SetEnergyAbsorbedAtFirstInteraction(edep +
                      (*secondary)[0]->GetKineticEnergy());
    }

  }

  // In case of a Compton scattering, the energy absorbed at first interaction
  // is the energy of the electron (the first one created from a Compton
  // scattering.)
  if(IsElectron && CreatorProcessName == "compt") {
    // In case the first interaction is a compton scattering, we count it
    // (this count is reset for each new event).
    fEventAction->AddAComptonScattering();
    fEventAction->SetEnergyAbsorbedAtFirstInteraction(edep);
    G4cout << "---- Energy deposited compt : " << edep << G4endl;
  } else {
    G4cout << "---- " << IsElectron << " - " <<
      processDefinedTheStep->GetProcessName() << G4endl;
  }


}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
