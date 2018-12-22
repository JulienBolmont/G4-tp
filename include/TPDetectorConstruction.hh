
//
// Class TPDetectorConstruction
//
// A detector construction class loading the geometry from GDML files.
//
// ----------------------------------------------------------------------------

#ifndef TPDetectorConstruction_H
#define TPDetectorConstruction_H 1


#include "G4VUserDetectorConstruction.hh"
#include "G4GDMLParser.hh"

#include "G4Material.hh"

#include "globals.hh"


class TPHistoManager;
class TPDetectorConstructionMessenger;

// ----------------------------------------------------------------------------

/// Detector construction used in GDML read/write example

class TPDetectorConstruction : public G4VUserDetectorConstruction
{
  public:

    // Constructor and destructor
    //
    TPDetectorConstruction(TPHistoManager *);
   ~TPDetectorConstruction();

    // Construction of SubDetectors
    //
    virtual G4VPhysicalVolume* Construct();

//    G4Material* GetAbsorberMaterial()  {return fAbsorberMaterial;};

    void SetGDMLFile(G4String rFile) {fReadFile = rFile;UpdateGeometry();};

//    const G4VPhysicalVolume* GetphysiWorld() {return fPhysiWorld;};
//    const G4VPhysicalVolume* GetAbsorber()   {return fPhysiAbsorber;};
    void UpdateGeometry();

    float GetEnergyResolution() {return fEnergyResolution;}

  private:

    // GDMLparser
    //
    G4GDMLParser* fParser;

    // Reading Settings
    //
    G4String fReadFile;
    G4VPhysicalVolume* fWorldPhysVol;
    //  G4Material*        fAbsorberMaterial;
    //  G4VPhysicalVolume* fPhysiWorld;    //pointer to the physical World
    //  G4VPhysicalVolume* fPhysiAbsorber; //pointer to the physical Absorber
	  TPHistoManager*    fHistoManager;
	  TPDetectorConstructionMessenger *fMessenger;
	  float fEnergyResolution;

};

// ----------------------------------------------------------------------------

#endif
