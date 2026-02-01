
#include "DetectorConstruction.hh"
#include "DetectorMessenger.hh"

#include "Wide_layers.hh"
#include "Thin_layers.hh"

#include "G4NistManager.hh"
#include "G4Material.hh"

#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"

#include "G4SystemOfUnits.hh"
#include "G4ThreeVector.hh"

#include <string>
#include <cmath>

static G4String DefaultCode()
{
  // Your requested default: 20 horizontal wide + 20 vertical wide alternating,
  // each interleaved with lead => "1727" repeated 20 times
  G4String s;
  for (int i = 0; i < 20; ++i) s += "1727";
  return s;
}

DetectorConstruction::DetectorConstruction()
: fCode(DefaultCode())
, fPbT(3.0*mm)
, fWidePlaneXY(2.16*m)
, fWideT(1.0*cm)
, fWidePitch(6.0*cm)
, fThinPlaneXY(2.16*m)
, fThinT(1.0*cm)
, fThinPitch(1.0*cm)
{
  fMessenger = new DetectorMessenger(this);
}

DetectorConstruction::~DetectorConstruction()
{
  delete fMessenger;
}

G4VPhysicalVolume* DetectorConstruction::Construct()
{
  auto* nist = G4NistManager::Instance();

  auto* air  = nist->FindOrBuildMaterial("G4_AIR");
  auto* lead = nist->FindOrBuildMaterial("G4_Pb");

  // Wide layers: if you later define "true PVT", swap this material for it.
  auto* wideMat = nist->FindOrBuildMaterial("G4_POLYSTYRENE");

  // Thin layers: polystyrene as requested
  auto* thinMat = nist->FindOrBuildMaterial("G4_POLYSTYRENE");

  // --- Filter code to only valid chars ---
  std::string code;
  code.reserve(fCode.size());
  for (char c : std::string(fCode)) {
    if (c=='1' || c=='2' || c=='3' || c=='4' || c=='7') code.push_back(c);
  }

  // --- Compute total detector thickness along Z ---
  double totalZ = 0.0;
  for (char c : code) {
    if (c=='7') totalZ += fPbT;
    else if (c=='1' || c=='2') totalZ += fWideT;
    else if (c=='3' || c=='4') totalZ += fThinT;
  }

  // Choose world size to fit the larger of wide/thin planes
  const double maxPlaneXY = std::max(fWidePlaneXY, fThinPlaneXY);

  const double marginXY = 1.0*m;
  const double marginZ  = 1.0*m;

  const double worldXY = maxPlaneXY + marginXY;
  const double worldZ  = totalZ + marginZ;

  // --- World ---
  auto* solidWorld = new G4Box("World", worldXY/2, worldXY/2, worldZ/2);
  auto* logicWorld = new G4LogicalVolume(solidWorld, air, "WorldLV");
  auto* physWorld  = new G4PVPlacement(nullptr, {}, logicWorld, "WorldPV", nullptr, false, 0, true);

  // --- Lead logical volume (reused) ---
  auto* solidPb = new G4Box("PbPlate", maxPlaneXY/2, maxPlaneXY/2, fPbT/2);
  auto* logicPb = new G4LogicalVolume(solidPb, lead, "PbPlateLV");

  // --- Layer builders ---
  Wide_layers wide(fWidePlaneXY, fWideT, fWidePitch);
  Thin_layers thin(fThinPlaneXY, fThinT, fThinPitch);

  // Place stack centered around z = 0
  double zCursor = +totalZ/2;   // current "top surface" of next layer

  int wideLayerCopy = 0;  // copy number for wide layer containers
  int thinLayerCopy = 0;  // copy number for thin layer containers
  int pbCopy        = 0;  // copy number for lead plates

  for (char c : code) {
    const double t =
      (c=='7') ? fPbT :
      (c=='1' || c=='2') ? fWideT :
      fThinT;

    const double zCenter = zCursor - t/2;

    if (c=='7') {
      new G4PVPlacement(nullptr,
                        G4ThreeVector(0,0,zCenter),
                        logicPb,
                        "PbPlatePV",
                        logicWorld,
                        false,
                        pbCopy++,
                        true);
    }
    else if (c=='1') {
      wide.PlaceLayer(logicWorld, air, wideMat,
                      "WideLayerPV",
                      wideLayerCopy++,
                      G4ThreeVector(0,0,zCenter),
                      1);
    }
    else if (c=='2') {
      wide.PlaceLayer(logicWorld, air, wideMat,
                      "WideLayerPV",
                      wideLayerCopy++,
                      G4ThreeVector(0,0,zCenter),
                      2);
    }
    else if (c=='3') {
      thin.PlaceLayer(logicWorld, air, thinMat,
                      "ThinLayerPV",
                      thinLayerCopy++,
                      G4ThreeVector(0,0,zCenter),
                      1);
    }
    else if (c=='4') {
      thin.PlaceLayer(logicWorld, air, thinMat,
                      "ThinLayerPV",
                      thinLayerCopy++,
                      G4ThreeVector(0,0,zCenter),
                      2);
    }

    zCursor -= t;
  }

  return physWorld;
}
