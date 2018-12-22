
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#ifndef TPHistoManager_h
#define TPHistoManager_h 1

#include "globals.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class TFile;
class TTree;
class TH1D;
class TPHistoManagerMessenger;

const G4int kMaxHisto = 6;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class TPHistoManager
{

  public:

    TPHistoManager();
   ~TPHistoManager();
   
    void Book();
    void Save();

	void SetOutputFileName(G4String fname) {fOutputFileName = fname;};

    void FillHisto(G4int id, G4double bin, G4double weight = 1.0);
    void Normalize(G4int id, G4double fac);    

    void FillNtuple(G4int nevent, G4double energyAbs, G4double energyAbsSmeared, G4int nbOfScattering);
    
    void PrintStatistic();
    
    void SetNbOfEnergyBins(G4int n) {fNbOfEnergyBins = n;};
    void SetEnergyMin(G4double emin) {fEnergyMin = emin;};
    void SetEnergyMax(G4double emax) {fEnergyMax = emax;};
        
  private:
  
  	TPHistoManagerMessenger *fMessenger;
  
  	G4String fOutputFileName;
    TFile*   fRootFile;
    TH1D*    fHisto[kMaxHisto];            
    TTree*   fNtuple1;    

    G4double fEabs, fEabsSmeared;
    G4int    fNbOfScatterings;
    G4int    fNEvent;
    G4int    fNbOfEnergyBins;
    G4double fEnergyMin, fEnergyMax;

};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

