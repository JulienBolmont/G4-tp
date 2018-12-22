//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include <TH1D.h>
#include <TFile.h>
#include <TTree.h>
#include <CLHEP/Units/SystemOfUnits.h>

#include "TPHistoManager.hh"
#include "TPHistoManagerMessenger.hh"
#include "G4UnitsTable.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

TPHistoManager::TPHistoManager()
:fRootFile(0),
 fNtuple1(0),
 fEabs(0.),
 fEabsSmeared(0.)
{

  fOutputFileName = "TP.root";

  fMessenger = new TPHistoManagerMessenger(this);

  // histograms
  for (G4int k=0; k<kMaxHisto; k++) fHisto[k] = 0;
  fNbOfEnergyBins = 200;
  fEnergyMin = 0.;
  fEnergyMax = 1.0*CLHEP::MeV;

  // ntuple
  fNtuple1 = 0;

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

TPHistoManager::~TPHistoManager()
{

  if (fRootFile) delete fRootFile;
  delete fMessenger;

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void TPHistoManager::Book()
{
  // Creating a tree container to handle histograms and ntuples.
  // This tree is associated to an output file.
  //

  if(!fOutputFileName.contains(".root")) fOutputFileName += ".root";

  fRootFile = new TFile(fOutputFileName,"RECREATE");
  if (! fRootFile) {
    G4cout << " TPHistoManager::Book :"
           << " problem creating the ROOT TFile "
           << G4endl;
    return;
  }

  // id = 0
  fHisto[0] = new TH1D("EAbs", "Edep in absorber (MeV)", fNbOfEnergyBins, fEnergyMin, fEnergyMax);
  // id = 1
  fHisto[1] = new TH1D("EAbs_first_int_compton", "Edep in absorber - First Interaction = Compton (MeV)", fNbOfEnergyBins, fEnergyMin, fEnergyMax);
  // id = 2
  fHisto[2] = new TH1D("EAbs_first_int_pe", "Edep in absorber - First Interaction = P.E. (MeV)", fNbOfEnergyBins, fEnergyMin, fEnergyMax);
  // id = 3
  fHisto[3] = new TH1D("EAbs_first_int_pe_e_exit", "Edep in absorber - First Interaction = P.E. + e- exit (MeV)", fNbOfEnergyBins, fEnergyMin, fEnergyMax);
  // id = 4
  fHisto[4] = new TH1D("Nb_of_Compt_scatt", "Number of Compton Scattering per event", 10, 0, 10);
  // id = 5
  fHisto[5] = new TH1D("EAbsSmeared", "Edep in absorber (MeV) - Smeared with Energy Resolution", fNbOfEnergyBins, fEnergyMin, fEnergyMax);

  for ( G4int i=0; i<kMaxHisto; ++i ) {
    if (! fHisto[i]) G4cout << "\n can't create histo " << i << G4endl;
  }

  // create 1st ntuple
  fNtuple1 = new TTree("Ntuple1", "Absorber");
  fNtuple1->Branch("Nevent", &fNEvent, "Nevent/I");
  fNtuple1->Branch("Eabs", &fEabs, "Eabs/D");
  fNtuple1->Branch("EabsSmeared", &fEabsSmeared, "EabsSmeared/D");
  fNtuple1->Branch("NbOfComptonScatterings", &fNbOfScatterings, "NbOfComptonScatterings/I");

  G4cout << "\n----> Output file is open in " << fOutputFileName << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void TPHistoManager::Save()
{
  
  if (! fRootFile) return;

  fRootFile->Write();       // Writing the histograms to the file
  fRootFile->Close();       // and closing the tree (and the file)

  G4cout << "\n----> Histograms and ntuples are saved in file " << fOutputFileName << G4endl;

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void TPHistoManager::FillHisto(G4int ih, G4double xbin, G4double weight)
{
  if (ih >= kMaxHisto) {
    G4cerr << "---> warning from HistoManager::FillHisto() : histo " << ih
           << " does not exist. (xbin=" << xbin << " weight=" << weight << ")"
           << G4endl;
    return;
  }
  if  (fHisto[ih]) { fHisto[ih]->Fill(xbin, weight); }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void TPHistoManager::Normalize(G4int ih, G4double fac)
{
  if (ih >= kMaxHisto) {
    G4cout << "---> warning from HistoManager::Normalize() : histo " << ih
           << " does not exist. (fac=" << fac << ")" << G4endl;
    return;
  }
  if (fHisto[ih]) fHisto[ih]->Scale(fac);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void TPHistoManager::FillNtuple(G4int nevent, G4double energyAbs, G4double energyAbsSmeared, G4int nbOfScattering)
{

  fEabs = energyAbs;
  fEabsSmeared = energyAbsSmeared;
  fNbOfScatterings = nbOfScattering;
  fNEvent = nevent;

  if (fNtuple1) fNtuple1->Fill();

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void TPHistoManager::PrintStatistic()
{

  G4cout << "\n ----> print histograms statistic \n" << G4endl;
  for ( G4int i=0; i<kMaxHisto; ++i ) {
    TH1D* h1 = fHisto[i];
    const G4String name = h1->GetName();

    G4String unitCategory;
    if (name[0] == 'E' ) unitCategory = "Energy";
    if (name[0] == 'L' ) unitCategory = "Length";

    if (name[0] == 'N' ) {
		G4cout << name
           << ": mean = " << h1->GetMean()
           << " rms = " << h1->GetRMS()
           << G4endl;
	} else {
    	G4cout << name
           << ": mean = " << G4BestUnit(h1->GetMean(), unitCategory)
           << " rms = " << G4BestUnit(h1->GetRMS(), unitCategory )
           << G4endl;
    }


  }

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
