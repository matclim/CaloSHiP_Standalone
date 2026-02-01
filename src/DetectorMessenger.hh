
#pragma once

#include "G4UImessenger.hh"
#include "globals.hh"

class DetectorConstruction;
class G4UIdirectory;
class G4UIcmdWithAString;
class G4UIcmdWithADoubleAndUnit;

class DetectorMessenger : public G4UImessenger {
public:
  explicit DetectorMessenger(DetectorConstruction* det);
  ~DetectorMessenger() override;

  void SetNewValue(G4UIcommand* cmd, G4String val) override;

private:
  DetectorConstruction* fDet = nullptr;

  G4UIdirectory* fDir = nullptr;

  G4UIcmdWithAString* fCodeCmd = nullptr;

  // lead
  G4UIcmdWithADoubleAndUnit* fPbTCmd = nullptr;

  // wide
  G4UIcmdWithADoubleAndUnit* fWidePlaneXYCmd = nullptr;
  G4UIcmdWithADoubleAndUnit* fWideTCmd       = nullptr;
  G4UIcmdWithADoubleAndUnit* fWidePitchCmd   = nullptr;

  // thin
  G4UIcmdWithADoubleAndUnit* fThinPlaneXYCmd = nullptr;
  G4UIcmdWithADoubleAndUnit* fThinTCmd       = nullptr;
  G4UIcmdWithADoubleAndUnit* fThinPitchCmd   = nullptr;
};
