#include "Thin_layers.hh"

#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4Material.hh"
#include "G4Exception.hh"
#include <cmath>

void Thin_layers::PlaceLayer(G4LogicalVolume* mother,
                             G4Material* air,
                             G4Material* polystyrene,
                             const G4String& layerPhysName,
                             G4int copyNo,
                             const G4ThreeVector& centerInMother,
                             int orientation)
{
  // --- container (AIR) ---
  auto* solidLayer = new G4Box(layerPhysName + "_Solid",
                               fPlaneXY/2, fPlaneXY/2, fThicknessZ/2);
  auto* logicLayer = new G4LogicalVolume(solidLayer, air, layerPhysName + "_LV");

  new G4PVPlacement(nullptr, centerInMother, logicLayer,
                    layerPhysName, mother, false, copyNo, true);

  // bar count must be integer
  const double nExact = fPlaneXY / fPitch;
  const int nBars = (int)std::llround(nExact);
  if (std::fabs(nExact - nBars) > 1e-6) {
    G4Exception("Thin_layers::PlaceLayer", "THIN001", FatalException,
                "thin planeXY/pitch is not an integer. Choose compatible values.");
  }

  // --- bars ---
  // orientation 1: long X, tile in Y
  // orientation 2: long Y, tile in X
  G4double barX=0, barY=0, barZ=fThicknessZ;

  if (orientation == 1) {
    barX = fPlaneXY;
    barY = fPitch;
  } else if (orientation == 2) {
    barX = fPitch;
    barY = fPlaneXY;
  } else {
    G4Exception("Thin_layers::PlaceLayer", "THIN002", FatalException,
                "Invalid orientation (use 1 or 2).");
  }

  auto* solidBar = new G4Box(layerPhysName + "_BarSolid",
                             barX/2, barY/2, barZ/2);
  auto* logicBar = new G4LogicalVolume(solidBar, polystyrene,
                                       layerPhysName + "_BarLV");

  for (int i = 0; i < nBars; ++i) {
    G4ThreeVector pos(0,0,0);
    if (orientation == 1) {
      const double y = -fPlaneXY/2 + (i + 0.5)*fPitch;
      pos = G4ThreeVector(0, y, 0);
    } else {
      const double x = -fPlaneXY/2 + (i + 0.5)*fPitch;
      pos = G4ThreeVector(x, 0, 0);
    }

    // Give thin bars their own PV name (lets you filter separately later)
    new G4PVPlacement(nullptr, pos, logicBar,
                      "ThinBarPV",
                      logicLayer,
                      false,
                      i,   // bar copy number
                      true);
  }
}
