//
// Class TPDetectorConstruction implementation
//
// ----------------------------------------------------------------------------

#include "TPDetectorConstruction.hh"

// Geant4 includes
//
#include "globals.hh"
#include "G4GeometryManager.hh"
#include "G4VisAttributes.hh"

// Materials
//
#include "G4Material.hh"

// Geometry includes
//
#include "G4LogicalVolume.hh"
#include "G4VPhysicalVolume.hh"
#include "G4PVParameterised.hh"
#include "G4PVPlacement.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"

// Reflected solids
//
#include "G4ReflectedSolid.hh"
#include "G4DisplacedSolid.hh"
#include "G4ReflectionFactory.hh"
#include "G4RotationMatrix.hh"
#include "G4AffineTransform.hh"
#include "G4Transform3D.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4SolidStore.hh"
#include "G4RunManager.hh"

// Assembly volumes
//
#include "G4AssemblyVolume.hh"


// GDML parser include
//
#include "G4GDMLParser.hh"
#include "G4SDManager.hh"

#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"

//#include "TPSensitiveDetector.hh"
#include "TPHistoManager.hh"
#include "TPDetectorConstructionMessenger.hh"
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//
// Constructor
//
TPDetectorConstruction::TPDetectorConstruction(TPHistoManager *histo)
  : G4VUserDetectorConstruction()
{

  fHistoManager = histo;
  fEnergyResolution = 0.;

  fMessenger = new TPDetectorConstructionMessenger(this);
  // File read by default
  fReadFile = "geometries/thin_cylinder_vacuum_geometry.gdml";

  fParser = NULL;

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//
// Destructor
//
TPDetectorConstruction::~TPDetectorConstruction()
{

  if(fParser != NULL) delete fParser;
  delete fMessenger;

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//
// Constructs geometries and materials
//
G4VPhysicalVolume* TPDetectorConstruction::Construct()
{

  //if(fReadFile.compareTo("") == 0) return NULL;
  if(fParser != NULL) delete fParser;
  fParser = new G4GDMLParser();
  fParser->Clear();

  // Clean old geometry, if any
  //
  G4GeometryManager::GetInstance()->OpenGeometry();
  G4PhysicalVolumeStore::GetInstance()->Clean();
  G4LogicalVolumeStore::GetInstance()->Clean();
  G4SolidStore::GetInstance()->Clean();

  // Reading of Geometry using G4GDML

  // ACTIVATING OVERLAP CHECK when read volumes are placed.
  // Can take long time in case of complex geometries
  //
  // fParser.SetOverlapCheck(true);
  fParser->Read(fReadFile,true);

  // TO DO : check network connexion before reading the file with validation on.
/*
  try{fParser->Read(fReadFile,true);}
  catch(const G4Exception &e)
    {

      G4cout << "EXCEPTION CAUGHT !" << G4endl;
      G4cout << "Unable to read the GDMLfile or to reach schema definitions. Trying again with no validation." << G4endl;
      fParser->Read(fReadFile,false);

    }*/

  G4cout << "***********************************" << G4endl;
  G4cout << "Construction of geometry from file " << fReadFile << G4endl;
  G4cout << "***********************************" << G4endl;

  //
  fWorldPhysVol = fParser->GetWorldVolume();
  G4cout << " --------> World Vol. named : " << fWorldPhysVol->GetName() << G4endl;

  const G4GDMLAuxMapType* auxmap = fParser->GetAuxMap();
  G4cout << "Found " << auxmap->size()
            << " volume(s) with auxiliary information."
            << G4endl << G4endl;

  // Loop on all volumes which have auxiliary informations
  for(G4GDMLAuxMapType::const_iterator iter=auxmap->begin();
      iter!=auxmap->end(); iter++)
  {

  G4cout << "> BING !!" << G4endl;
  G4cout << "> " << ((*iter).first) << G4endl;
  G4cout << "> " << ((*iter).first)->GetName() << G4endl;

	if((((*iter).first)->GetName()).find("Volume") == std::string::npos) {

	  G4cout << "Volume \"" << ((*iter).first)->GetName()
	         << "\" seems to be crappy and will be ignored !"
	         << G4endl << G4endl;
	  continue;

    }

    G4cout << "Volume " << ((*iter).first)->GetName()
           << " has the following list of auxiliary information: "
           << G4endl << G4endl;

	G4LogicalVolume* myvol = (*iter).first;

	// Loop on all auxiliary information for a given volume
    for (G4GDMLAuxListType::const_iterator vit=(*iter).second.begin();
         vit!=(*iter).second.end();vit++) {

      if ((*vit).type=="Color")
      {
        G4cout << "Giving color " << (*vit).value
               << " to volume " << myvol->GetName()
               <<  G4endl << G4endl;

        G4Colour SensDetCol(0.0, 0.0, 1.0);
        G4Colour::GetColour((*vit).value, SensDetCol);
        G4VisAttributes* DetVisAtt= new G4VisAttributes(SensDetCol);
        DetVisAtt->SetForceSolid(true);
        myvol->SetVisAttributes(DetVisAtt);
      }

      if ((*vit).type=="Resolution")
      {
        fEnergyResolution = strtof((*vit).value,0);
        G4cout << "Resolution tag found with value "
      	       << fEnergyResolution
               <<  G4endl << G4endl;
      }

    }
  }

  // Set Visualization attributes to world (red box)
  //
  G4VisAttributes* WorldBoxVisAtt= new G4VisAttributes(G4Colour(1.0,0.0,0.0));
  fWorldPhysVol->GetLogicalVolume()->SetVisAttributes(WorldBoxVisAtt);

  return fWorldPhysVol;

}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


void TPDetectorConstruction::UpdateGeometry()
{

	if (fWorldPhysVol) {

//		fParser.Clear();
		G4RunManager::GetRunManager()->DefineWorldVolume(Construct());
		G4RunManager::GetRunManager()->GeometryHasBeenModified();

	}

}
