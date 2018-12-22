//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "TPHistoManagerMessenger.hh"
#include "TPHistoManager.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithAnInteger.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

TPHistoManagerMessenger::TPHistoManagerMessenger(TPHistoManager *histoManager)
:fHistoManager(histoManager)
{

	fDir = new G4UIdirectory("/tp/histos/");
	fDir->SetGuidance("Output histograms.");

	fFileNameCmd = new G4UIcmdWithAString("/tp/histos/fileName",this);
	fFileNameCmd->SetGuidance("Name of the root output file.");
	fFileNameCmd->SetParameterName("ROOTFile",false);
	fFileNameCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

	fEbinCmd = new G4UIcmdWithAnInteger("/tp/histos/nBinsE",this);
	fEbinCmd->SetGuidance("Set number of bins for energy");
	fEbinCmd->SetParameterName("NEbins",false);
	fEbinCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

	fEMinCmd = new G4UIcmdWithADoubleAndUnit("/tp/histos/minEnergy",this);
	fEMinCmd->SetGuidance("Set min kinetic energy");
	fEMinCmd->SetParameterName("eMin",false);
	fEMinCmd->SetUnitCategory("Energy");
	fEMinCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

	fEMaxCmd = new G4UIcmdWithADoubleAndUnit("/tp/histos/maxEnergy",this);
	fEMaxCmd->SetGuidance("Set max kinetic energy");
	fEMaxCmd->SetParameterName("eMax",false);
	fEMaxCmd->SetUnitCategory("Energy");
	fEMaxCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

TPHistoManagerMessenger::~TPHistoManagerMessenger()
{

	delete fFileNameCmd;
	delete fEbinCmd;
	delete fEMinCmd;
	delete fEMaxCmd;
	delete fDir;

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void TPHistoManagerMessenger::SetNewValue(G4UIcommand* command,
                                          G4String newValue)
{

  if(command == fFileNameCmd) fHistoManager->SetOutputFileName(newValue);
  else if(command == fEbinCmd) fHistoManager->SetNbOfEnergyBins(fEbinCmd->GetNewIntValue(newValue));
  else if(command == fEMinCmd) fHistoManager->SetEnergyMin(fEMinCmd->GetNewDoubleValue(newValue));
  else if(command == fEMaxCmd) fHistoManager->SetEnergyMax(fEMaxCmd->GetNewDoubleValue(newValue));
  else return;

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
