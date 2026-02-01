
#pragma once
#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ThreeVector.hh"
#include "globals.hh"

class G4ParticleGun;
class G4Event;
class PrimaryGeneratorMessenger;

class PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction {
public:
  PrimaryGeneratorAction();
  ~PrimaryGeneratorAction() override;

  void GeneratePrimaries(G4Event* event) override;

  // called by messenger
  void SetParticleFromUI(const G4String& name);
  void SetEnergyFromUI(G4double e);
  void SetPositionFromUI(const G4ThreeVector& p);
  void SetDirectionFromUI(const G4ThreeVector& d);

private:
  void SetParticleInternal(const G4String& name);
  void SetDirectionInternal(const G4ThreeVector& dir);

  G4ParticleGun* fGun = nullptr;
  PrimaryGeneratorMessenger* fMessenger = nullptr;

  G4String      fParticleName = "mu-";
  G4double      fEnergy = 1.0;             // internal units
  G4ThreeVector fPosition = {0,0,0};
  G4ThreeVector fDirection = {0,0,-1};
};
