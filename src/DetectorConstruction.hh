
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

  void SetFibrePlaneXY(G4double v)   { fFibrePlaneXY = v; }
  void SetFibreLen(G4double v)       { fFibreLen = v; }
  void SetFibreDiam(G4double v)      { fFibreDiam = v; }
  void SetFibrePitch(G4double v)     { fFibrePitch = v; }
  void SetFibreModuleDz(G4double v)  { fFibreModuleDz = v; }
  
  void SetAirGap(G4double v)         { fAirGap = v; }

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

  G4double fFibrePlaneXY;
  G4double fFibreLen;
  G4double fFibreDiam;
  G4double fFibrePitch;
  G4double fFibreModuleDz;



  DetectorMessenger* fMessenger = nullptr;
};
