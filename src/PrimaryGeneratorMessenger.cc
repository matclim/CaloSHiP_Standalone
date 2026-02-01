
#include "PrimaryGeneratorMessenger.hh"
#include "PrimaryGeneratorAction.hh"

#include "G4UIdirectory.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWith3VectorAndUnit.hh"
#include "G4UIcmdWith3Vector.hh"

PrimaryGeneratorMessenger::PrimaryGeneratorMessenger(PrimaryGeneratorAction* action)
: fAction(action)
{
  fDir = new G4UIdirectory("/mygun/");
  fDir->SetGuidance("Primary generator controls");

  fParticleCmd = new G4UIcmdWithAString("/mygun/particle", this);
  fParticleCmd->SetGuidance("Set particle: e-/e+/mu-/mu+/pi-/pi+");

  fEnergyCmd = new G4UIcmdWithADoubleAndUnit("/mygun/energy", this);
  fEnergyCmd->SetGuidance("Set kinetic energy (e.g. 1 GeV, 200 MeV)");
  fEnergyCmd->SetUnitCategory("Energy");   // <-- this is valid for UIcmd parser
  fEnergyCmd->SetDefaultUnit("GeV");

  fPosCmd = new G4UIcmdWith3VectorAndUnit("/mygun/position", this);
  fPosCmd->SetGuidance("Set position (e.g. 0 0 1 m)");
  fPosCmd->SetUnitCategory("Length");
  fPosCmd->SetDefaultUnit("m");

  fDirCmd = new G4UIcmdWith3Vector("/mygun/direction", this);
  fDirCmd->SetGuidance("Set direction (dx dy dz), will be normalized");
}

PrimaryGeneratorMessenger::~PrimaryGeneratorMessenger()
{
  delete fDirCmd;
  delete fPosCmd;
  delete fEnergyCmd;
  delete fParticleCmd;
  delete fDir;
}

void PrimaryGeneratorMessenger::SetNewValue(G4UIcommand* command, G4String newValue)
{
  if (command == fParticleCmd) {
    fAction->SetParticleFromUI(newValue);
  } else if (command == fEnergyCmd) {
    fAction->SetEnergyFromUI(fEnergyCmd->GetNewDoubleValue(newValue));
  } else if (command == fPosCmd) {
    fAction->SetPositionFromUI(fPosCmd->GetNew3VectorValue(newValue));
  } else if (command == fDirCmd) {
    fAction->SetDirectionFromUI(fDirCmd->GetNew3VectorValue(newValue));
  }
}
