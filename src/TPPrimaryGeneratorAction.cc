
#include "TPPrimaryGeneratorAction.hh"

#include "G4RunManager.hh"
#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4IonTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4ChargedGeantino.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"

#include "TPPrimaryGeneratorActionMessenger.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

TPPrimaryGeneratorAction::TPPrimaryGeneratorAction()
 : G4VUserPrimaryGeneratorAction(),
   fParticleGun(0)
{

  G4int n_particle = 1;
  fParticleGun  = new G4ParticleGun(n_particle);

  fMessenger = new TPPrimaryGeneratorActionMessenger(this);

  // Default particle kinematic

  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
  G4ParticleDefinition* particle
                    = particleTable->FindParticle("gamma");
  fParticleGun->SetParticleDefinition(particle);
  fParticleGun->SetParticlePosition(G4ThreeVector(0.,0.,0.));
  fParticleGun->SetParticleEnergy(0*keV);

  fParticleGun->SetParticleMomentumDirection(G4ThreeVector(1.,0.,0.));

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

TPPrimaryGeneratorAction::~TPPrimaryGeneratorAction()
{

  delete fParticleGun;
  delete fMessenger;

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void TPPrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{

  //G4ParticleDefinition* particle = fParticleGun->GetParticleDefinition();


  ///G4double x0  = 0*cm, y0  = 0*cm, z0  = 0*cm;
  ///G4double dx0 = 0*cm, dy0 = 0*cm, dz0 = 0*cm;
  //G4double x0  = 4*cm, y0  = 4*cm, z0  = 4*cm;
  //G4double dx0 = 1*cm, dy0 = 1*cm, dz0 = 1*cm;
  //x0 += dx0*(G4UniformRand()-0.5);
  //y0 += dy0*(G4UniformRand()-0.5);
  //z0 += dz0*(G4UniformRand()-0.5);
  fParticleGun->SetParticlePosition(G4ThreeVector(0,0,0));


  G4double theta, phi;
  if(fSpatialDistribution == "sphere") {
    // Isotropic distribution
    theta = 360 * G4UniformRand() * degree;
    phi = 180 * G4UniformRand()* degree;
    fParticleGun->SetParticleMomentumDirection(G4ThreeVector(sin(phi)*cos(theta),sin(phi)*sin(theta),cos(phi)));
  } else if(fSpatialDistribution == "disk") {
    // Isotropic distribution in the XY plane
    theta = 360 * G4UniformRand() * degree;
    fParticleGun->SetParticleMomentumDirection(G4ThreeVector(cos(theta),sin(theta),0));
  } else {
    // Beam along the Z direction
    fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0, 0, 1));
  }

  //create vertex
  //
  fParticleGun->GeneratePrimaryVertex(anEvent);

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void TPPrimaryGeneratorAction::SetGenerationSpatialDistribution(G4String distrib)
{

  fSpatialDistribution = distrib;

}
