
#include "High_Precision_Fibre_layer.hh"

#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4Tubs.hh"
#include "G4Material.hh"
#include "G4RotationMatrix.hh"
#include "G4SystemOfUnits.hh"
#include "G4Exception.hh"

#include <cmath>
#include <sstream>

void High_Precision_Fibre_layer::PlaceModule(G4LogicalVolume* mother,
                                             G4Material* air,
                                             G4Material* polystyrene,
                                             const G4String& modulePhysName,
                                             G4int copyNo,
                                             const G4ThreeVector& centerInMother,
                                             int orientation)
{
  // Container for the whole "3-sublayer" module
  auto* solidModule = new G4Box(modulePhysName + "_Solid",
                                fPlaneXY/2, fPlaneXY/2, fModuleDz/2);
  auto* logicModule = new G4LogicalVolume(solidModule, air, modulePhysName + "_LV");

  new G4PVPlacement(nullptr, centerInMother, logicModule,
                    modulePhysName, mother, false, copyNo, true);

  // Fibre geometry
  const G4double r = fDiam/2;

  // Fibre axis is Z by default for G4Tubs; we rotate depending on orientation.
  // We'll build fibres as a cylinder of half-length = fFibreLen/2.
  auto* solidFibre = new G4Tubs("FibreSolid", 0.0, r, fFibreLen/2, 0.*deg, 360.*deg);
  auto* logicFibre = new G4LogicalVolume(solidFibre, polystyrene, modulePhysName + "_FibreLV");

  G4RotationMatrix rot;
  if (orientation == 1) {
    // horizontal fibres along X: rotate Z-axis -> X-axis
    rot.rotateY(90.*deg);
  } else if (orientation == 2) {
    // vertical fibres along Y: rotate Z-axis -> Y-axis
    rot.rotateX(90.*deg);
  } else {
    G4Exception("High_Precision_Fibre_layer::PlaceModule","FIB001",FatalException,
                "Invalid orientation (use 1 or 2).");
  }

  // How many fibres across the packed direction?
  // If fibres run along X, they are packed in Y across fPlaneXY with pitch = 1.2mm.
  const double nExact = fPlaneXY / fPitch;
  const int nFib = (int)std::llround(nExact);
  if (std::fabs(nExact - nFib) > 1e-6) {
    G4Exception("High_Precision_Fibre_layer::PlaceModule","FIB002",FatalException,
                "fibrePlaneXY/pitch is not integer; choose compatible values.");
  }

  // Sublayer offsets (your spec)
  const G4double dx[3] = { 0.0, 0.6*mm, 0.0 };
  const G4double dz[3] = { 0.0, 1.2*mm, 2.4*mm };

  // We place sublayers such that z=0 is the module center.
  // Shift so the lowest sublayer starts near -fModuleDz/2 + r.
  // Here we anchor sublayer 0 at z = -fModuleDz/2 + r, then add dz[].
  const G4double z0 = -fModuleDz/2 + r;

  // Loop fibres
  for (int sub = 0; sub < 3; ++sub) {
    for (int i = 0; i < nFib; ++i) {
      // coordinate in packed direction:
      const G4double u = -fPlaneXY/2 + (i + 0.5)*fPitch;

      G4ThreeVector pos(0,0,0);

      if (orientation == 1) {
        // along X, packed in Y => u is Y
        pos = G4ThreeVector(dx[sub], u, z0 + dz[sub]);
      } else {
        // along Y, packed in X => u is X
        pos = G4ThreeVector(u + dx[sub], 0.0, z0 + dz[sub]);
      }

      // Make PV name unique-ish but not insane
      std::ostringstream pvname;
      pvname << "FibrePV_s" << sub;

      const int fibreCopy = sub*nFib + i; // unique within module
      new G4PVPlacement(G4Transform3D(rot, pos),
                        logicFibre,
                        pvname.str().c_str(),
                        logicModule,
                        false,
                        fibreCopy,
                        true);
    }
  }
}
