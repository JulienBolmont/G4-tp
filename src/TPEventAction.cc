
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include <TRandom3.h>
#include <TMath.h>

#include "TPEventAction.hh"
#include "TPDetectorConstruction.hh"


#include "TPRunAction.hh"
#include "TPHistoManager.hh"

#include "G4Event.hh"
#include "G4EventManager.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

TPEventAction::TPEventAction(TPHistoManager* histo, TPDetectorConstruction* detector)
:G4UserEventAction(),
 fHistoManager(histo),
 fDetector(detector),
 fEnergyAbs(0.),
 fPrintModulo(0)
{

 fPrintModulo = 1000;
 fFirstInteractionName = "";

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

TPEventAction::~TPEventAction()
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void TPEventAction::BeginOfEventAction(const G4Event *evt)
{

  G4int evtNb = evt->GetEventID();
  if (evtNb%fPrintModulo == 0) G4cout << "\n---> Begin of event: " << evtNb << G4endl;

  // initialisation per event
  fEnergyAbs = 0.;
  fEnergyAbsSmeared = 0.;
  fEnergyAbs_first_int = -1;
  fNbOfComptonScatteringsPerEvent = 0;
  fFirstInteractionName = "";

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void TPEventAction::EndOfEventAction(const G4Event *evt)
{

  // Smear deposited energy according to energy resolution provided in geometry.
  // Division by 2.35 to translate from FWHM to Sigma.
  TRandom3 *rnd = new TRandom3(0);

  if(fDetector->GetEnergyResolution() == 0) fEnergyAbsSmeared = fEnergyAbs;
  else fEnergyAbsSmeared = rnd->Gaus(fEnergyAbs, fEnergyAbs/TMath::Sqrt(fEnergyAbs)*(fDetector->GetEnergyResolution()*TMath::Sqrt(0.662))/2.35);

  delete rnd;

  G4cout << "----------- END OF EVENT WITH EDEP = " << fEnergyAbs << G4endl;

  //fill histograms
  //
  if(fEnergyAbs > 0) fHistoManager->FillHisto(0, fEnergyAbs);
  if(fEnergyAbsSmeared > 0) fHistoManager->FillHisto(5, fEnergyAbsSmeared);
  if(fFirstInteractionName == "compt") fHistoManager->FillHisto(1, fEnergyAbs_first_int);
  if(fFirstInteractionName == "phot") {
  	fHistoManager->FillHisto(2, fEnergyAbs_first_int);
  	fHistoManager->FillHisto(3, fEnergyAbs);
  }
  if(fEnergyAbs > 0) fHistoManager->FillHisto(4, fNbOfComptonScatteringsPerEvent);

  //fill ntuple
  //
  if(fEnergyAbs > 0) {
  	fHistoManager->FillNtuple(evt->GetEventID(), fEnergyAbs, fEnergyAbsSmeared, fNbOfComptonScatteringsPerEvent);
  	//G4EventManager::GetEventManager()->KeepTheCurrentEvent();
  }

  // To display only selected events, add :
  //  if(...) G4EventManager::GetEventManager()->KeepTheCurrentEvent();
  // Use with
  //  Idle> /vis/disable
  //  Idle> /run/beamOn 10000
  // then at end of run
  //   Idle> /vis/enable
  //   Idle> /vis/reviewKeptEvents
  // To finish:
  //   /vis/abortReviewKeptEvents
  //   continue

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
