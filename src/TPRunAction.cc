//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "TPRunAction.hh"
#include "TPHistoManager.hh"

#include "G4Run.hh"
#include "G4RunManager.hh"
#include "G4UnitsTable.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

TPRunAction::TPRunAction(TPHistoManager* histo)
: G4UserRunAction(),
  fHistoManager(histo),
  fSumEAbs(0.), fSum2EAbs(0.),
  fSumLAbs(0.), fSum2LAbs(0.)
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

TPRunAction::~TPRunAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void TPRunAction::BeginOfRunAction(const G4Run* aRun)
{ 
  G4cout << "### Run " << aRun->GetRunID() << " start." << G4endl;
    
  //initialize cumulative quantities
  //
  fSumEAbs = fSum2EAbs = 0.;
  fSumLAbs = fSum2LAbs = 0.;
  
  //histograms
  //
  fHistoManager->Book(); 
  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void TPRunAction::FillPerEvent(G4double EAbs, G4double LAbs)
{

  //accumulate statistic
  //
  fSumEAbs += EAbs;  fSum2EAbs += EAbs*EAbs;
  fSumLAbs += LAbs;  fSum2LAbs += LAbs*LAbs;

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void TPRunAction::EndOfRunAction(const G4Run* aRun)
{

  G4int NbOfEvents = aRun->GetNumberOfEvent();
  G4cout << "### EndOfRunAction : Nb of events = " << NbOfEvents << G4endl;
  if (NbOfEvents == 0) return;
  
  //compute statistics: mean and rms
  //
  fSumEAbs /= NbOfEvents; fSum2EAbs /= NbOfEvents;
  G4double rmsEAbs = fSum2EAbs - fSumEAbs*fSumEAbs;
  if (rmsEAbs >0.) rmsEAbs = std::sqrt(rmsEAbs); else rmsEAbs = 0.;
    
  fSumLAbs /= NbOfEvents; fSum2LAbs /= NbOfEvents;
  G4double rmsLAbs = fSum2LAbs - fSumLAbs*fSumLAbs;
  if (rmsLAbs >0.) rmsLAbs = std::sqrt(rmsLAbs); else rmsLAbs = 0.;
    
  //print
  //
  G4cout
     << "\n--------------------End of Run------------------------------\n"
     << "\n mean Energy in Absorber : " << G4BestUnit(fSumEAbs,"Energy")
     << " +- "                          << G4BestUnit(rmsEAbs,"Energy")  
     << G4endl;
     
  G4cout
     << "\n mean trackLength in Absorber : " << G4BestUnit(fSumLAbs,"Length")
     << " +- "                               << G4BestUnit(rmsLAbs,"Length")  
     << "\n------------------------------------------------------------\n"
     << G4endl;
     
  //save histograms
  //
  fHistoManager->PrintStatistic();
  fHistoManager->Save();   
  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
