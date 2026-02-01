
#pragma once

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"

class G4VPhysicalVolume;
class DetectorMessenger;

class DetectorConstruction : public G4VUserDetectorConstruction {
public:
  DetectorConstruction();
  ~DetectorConstruction() override;

  G4VPhysicalVolume* Construct() override;

  // Setters called by DetectorMessenger (must be used before /run/initialize)
  void SetCode(const G4String& s) { fCode = s; }

  // Lead
  void SetPbT(G4double v) { fPbT = v; }

  // Wide layers (PVT or your chosen material)
  void SetWidePlaneXY(G4double v) { fWidePlaneXY = v; }
  void SetWideT(G4double v)       { fWideT = v; }
  void SetWidePitch(G4double v)   { fWidePitch = v; }

  // Thin layers (polystyrene)
  void SetThinPlaneXY(G4double v) { fThinPlaneXY = v; }
  void SetThinT(G4double v)       { fThinT = v; }
  void SetThinPitch(G4double v)   { fThinPitch = v; }

private:
  // Detector code (sequence of 1/2/3/4/7; other chars ignored)
  G4String fCode;

  // Dimensions (defaults)
  G4double fPbT;

  G4double fWidePlaneXY;
  G4double fWideT;
  G4double fWidePitch;

  G4double fThinPlaneXY;
  G4double fThinT;
  G4double fThinPitch;

  DetectorMessenger* fMessenger = nullptr;
};
