#pragma once

#include "G4ThreeVector.hh"
#include "globals.hh"

class G4LogicalVolume;
class G4Material;

// Builds one layer of 36 PVT bars inside an AIR container.
// orientation = 1: bars long in X, tiled in Y
// orientation = 2: bars long in Y, tiled in X
class Wide_layers {
public:
  Wide_layers(G4double planeXY, G4double thicknessZ, G4double barPitch)
    : fPlaneXY(planeXY), fThicknessZ(thicknessZ), fPitch(barPitch) {}

  // Places a full layer (container + bars) into 'mother'.
  // copyNo is the layer ID (so later you can read it with touchable->GetCopyNumber(1)).
  void PlaceLayer(G4LogicalVolume* mother,
                  G4Material* air,
                  G4Material* pvt,
                  const G4String& layerPhysName,
                  G4int copyNo,
                  const G4ThreeVector& centerInMother,
                  int orientation);

private:
  G4double fPlaneXY;     // full size in X/Y of the plane (e.g. 2.16*m)
  G4double fThicknessZ;  // full thickness of the layer (e.g. 0.01*m)
  G4double fPitch;       // bar pitch (e.g. 0.06*m)
};
