
#include "PrimaryGeneratorAction.hh"
#include "PrimaryGeneratorMessenger.hh"

#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4Event.hh"
#include "G4Exception.hh"

PrimaryGeneratorAction::PrimaryGeneratorAction()
{
  fGun = new G4ParticleGun(1);

  // defaults
  fEnergy = 1.0*GeV;
  fPosition = {0,0, 1.0*m};
  fDirection = {0,0,-1};

  SetParticleInternal("mu-");
  SetDirectionInternal(fDirection);

  fMessenger = new PrimaryGeneratorMessenger(this);
}

PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
  delete fMessenger;
  delete fGun;
}

void PrimaryGeneratorAction::SetParticleInternal(const G4String& name)
{
  if (!(name=="e-"||name=="e+"||name=="mu-"||name=="mu+"||name=="pi-"||name=="pi+")) {
    G4Exception("PrimaryGeneratorAction::SetParticleInternal","MYGUN001",
                FatalException,"Use e-/e+/mu-/mu+/pi-/pi+");
  }
  auto* p = G4ParticleTable::GetParticleTable()->FindParticle(name);
  if (!p) {
    G4Exception("PrimaryGeneratorAction::SetParticleInternal","MYGUN002",
                FatalException,("Not found: "+name).c_str());
  }
  fParticleName = name;
  fGun->SetParticleDefinition(p);
}

void PrimaryGeneratorAction::SetDirectionInternal(const G4ThreeVector& dir)
{
  if (dir.mag2() <= 0.) {
    G4Exception("PrimaryGeneratorAction::SetDirectionInternal","MYGUN003",
                FatalException,"Direction must be non-zero");
  }
  fDirection = dir.unit();
}

void PrimaryGeneratorAction::SetParticleFromUI(const G4String& name) { SetParticleInternal(name); }
void PrimaryGeneratorAction::SetEnergyFromUI(G4double e) { fEnergy = e; }
void PrimaryGeneratorAction::SetPositionFromUI(const G4ThreeVector& p) { fPosition = p; }
void PrimaryGeneratorAction::SetDirectionFromUI(const G4ThreeVector& d) { SetDirectionInternal(d); }

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* event)
{
  fGun->SetParticleEnergy(fEnergy);
  fGun->SetParticlePosition(fPosition);
  fGun->SetParticleMomentumDirection(fDirection);
  fGun->GeneratePrimaryVertex(event);
}
