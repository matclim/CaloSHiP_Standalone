#pragma once
#include "G4UImessenger.hh"
#include "globals.hh"

class PrimaryGeneratorAction;
class G4UIdirectory;
class G4UIcmdWithAString;
class G4UIcmdWithADoubleAndUnit;
class G4UIcmdWith3VectorAndUnit;
class G4UIcmdWith3Vector;

class PrimaryGeneratorMessenger : public G4UImessenger {
public:
  explicit PrimaryGeneratorMessenger(PrimaryGeneratorAction* action);
  ~PrimaryGeneratorMessenger() override;

  void SetNewValue(G4UIcommand* command, G4String newValue) override;

private:
  PrimaryGeneratorAction* fAction = nullptr;

  G4UIdirectory* fDir = nullptr;
  G4UIcmdWithAString* fParticleCmd = nullptr;
  G4UIcmdWithADoubleAndUnit* fEnergyCmd = nullptr;
  G4UIcmdWith3VectorAndUnit* fPosCmd = nullptr;
  G4UIcmdWith3Vector* fDirCmd = nullptr;
};

