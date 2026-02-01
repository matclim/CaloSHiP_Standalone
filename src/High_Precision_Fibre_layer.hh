#pragma once
#include "G4ThreeVector.hh"
#include "globals.hh"

class G4LogicalVolume;
class G4Material;

class High_Precision_Fibre_layer {
public:
  High_Precision_Fibre_layer(G4double planeXY,
                             G4double fibreLen,
                             G4double fibreDiam,
                             G4double pitch,
                             G4double moduleDz)
  : fPlaneXY(planeXY), fFibreLen(fibreLen), fDiam(fibreDiam),
    fPitch(pitch), fModuleDz(moduleDz) {}

  // orientation:
  // 1 = horizontal fibres (along X, packed in Y)
  // 2 = vertical fibres   (along Y, packed in X)
  void PlaceModule(G4LogicalVolume* mother,
                   G4Material* air,
                   G4Material* polystyrene,
                   const G4String& modulePhysName,
                   G4int copyNo,
                   const G4ThreeVector& centerInMother,
                   int orientation);

private:
  G4double fPlaneXY;   // full size in X/Y
  G4double fFibreLen;  // fibre length (along axis)
  G4double fDiam;      // 1.2 mm
  G4double fPitch;     // 1.2 mm
  G4double fModuleDz;  // thickness of the 3-sublayer module
};
