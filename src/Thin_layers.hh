
#pragma once

#include "G4ThreeVector.hh"
#include "globals.hh"

class G4LogicalVolume;
class G4Material;

// Builds one layer of thin polystyrene bars inside an AIR container.
// orientation = 1: bars long in X, tiled in Y
// orientation = 2: bars long in Y, tiled in X
class Thin_layers {
public:
  Thin_layers(G4double planeXY, G4double thicknessZ, G4double barPitch)
    : fPlaneXY(planeXY), fThicknessZ(thicknessZ), fPitch(barPitch) {}

  void PlaceLayer(G4LogicalVolume* mother,
                  G4Material* air,
                  G4Material* polystyrene,
                  const G4String& layerPhysName,
                  G4int copyNo,
                  const G4ThreeVector& centerInMother,
                  int orientation);

private:
  G4double fPlaneXY;     // full plane size in X/Y
  G4double fThicknessZ;  // full layer thickness
  G4double fPitch;       // bar pitch (bar width)
};
