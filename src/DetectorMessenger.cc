
#include "DetectorMessenger.hh"
#include "DetectorConstruction.hh"

#include "G4UIdirectory.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"

DetectorMessenger::DetectorMessenger(DetectorConstruction* det)
: fDet(det)
{
  fDir = new G4UIdirectory("/det/");
  fDir->SetGuidance("Detector geometry controls");

  fCodeCmd = new G4UIcmdWithAString("/det/code", this);
  fCodeCmd->SetGuidance("Detector code: sequence of 1/2/3/4/7. Others ignored.");

  // Lead
  fPbTCmd = new G4UIcmdWithADoubleAndUnit("/det/pbT", this);
  fPbTCmd->SetUnitCategory("Length");
  fPbTCmd->SetDefaultUnit("mm");
  fPbTCmd->SetGuidance("Lead thickness.");

  // Wide
  fWidePlaneXYCmd = new G4UIcmdWithADoubleAndUnit("/det/widePlaneXY", this);
  fWidePlaneXYCmd->SetUnitCategory("Length");
  fWidePlaneXYCmd->SetDefaultUnit("m");
  fWidePlaneXYCmd->SetGuidance("Wide plane size in X and Y (full length).");

  fWideTCmd = new G4UIcmdWithADoubleAndUnit("/det/wideT", this);
  fWideTCmd->SetUnitCategory("Length");
  fWideTCmd->SetDefaultUnit("cm");
  fWideTCmd->SetGuidance("Wide scintillator thickness.");

  fWidePitchCmd = new G4UIcmdWithADoubleAndUnit("/det/widePitch", this);
  fWidePitchCmd->SetUnitCategory("Length");
  fWidePitchCmd->SetDefaultUnit("cm");
  fWidePitchCmd->SetGuidance("Wide bar pitch (bar width).");

  // Thin
  fThinPlaneXYCmd = new G4UIcmdWithADoubleAndUnit("/det/thinPlaneXY", this);
  fThinPlaneXYCmd->SetUnitCategory("Length");
  fThinPlaneXYCmd->SetDefaultUnit("m");
  fThinPlaneXYCmd->SetGuidance("Thin plane size in X and Y (full length).");

  fThinTCmd = new G4UIcmdWithADoubleAndUnit("/det/thinT", this);
  fThinTCmd->SetUnitCategory("Length");
  fThinTCmd->SetDefaultUnit("cm");
  fThinTCmd->SetGuidance("Thin scintillator thickness.");

  fThinPitchCmd = new G4UIcmdWithADoubleAndUnit("/det/thinPitch", this);
  fThinPitchCmd->SetUnitCategory("Length");
  fThinPitchCmd->SetDefaultUnit("cm");
  fThinPitchCmd->SetGuidance("Thin bar pitch (bar width).");
}

DetectorMessenger::~DetectorMessenger()
{
  delete fThinPitchCmd;
  delete fThinTCmd;
  delete fThinPlaneXYCmd;

  delete fWidePitchCmd;
  delete fWideTCmd;
  delete fWidePlaneXYCmd;

  delete fPbTCmd;
  delete fCodeCmd;
  delete fDir;
}

void DetectorMessenger::SetNewValue(G4UIcommand* cmd, G4String val)
{
  if (cmd == fCodeCmd) fDet->SetCode(val);

  else if (cmd == fPbTCmd) fDet->SetPbT(fPbTCmd->GetNewDoubleValue(val));

  else if (cmd == fWidePlaneXYCmd) fDet->SetWidePlaneXY(fWidePlaneXYCmd->GetNewDoubleValue(val));
  else if (cmd == fWideTCmd)       fDet->SetWideT(fWideTCmd->GetNewDoubleValue(val));
  else if (cmd == fWidePitchCmd)   fDet->SetWidePitch(fWidePitchCmd->GetNewDoubleValue(val));

  else if (cmd == fThinPlaneXYCmd) fDet->SetThinPlaneXY(fThinPlaneXYCmd->GetNewDoubleValue(val));
  else if (cmd == fThinTCmd)       fDet->SetThinT(fThinTCmd->GetNewDoubleValue(val));
  else if (cmd == fThinPitchCmd)   fDet->SetThinPitch(fThinPitchCmd->GetNewDoubleValue(val));
}
