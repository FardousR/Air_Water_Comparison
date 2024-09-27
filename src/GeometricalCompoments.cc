#include "DetectorConstruction.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4Material.hh"
#include "G4NistManager.hh"

G4VPhysicalVolume* DetectorConstruction::ConstructShield(G4LogicalVolume* MotherVolume) {
    // Get the NIST material manager to look up materials
    G4NistManager* nist = G4NistManager::Instance();

    // Get the material for the shield from the SP->GetShield()parameter struct
    G4Material* shieldMaterial = nist->FindOrBuildMaterial(SP->GetShield().mat);
    if (!shieldMaterial) {
        G4cerr << "Error: Material " << SP->GetShield().mat << " not found!" << G4endl;
        return nullptr;
    }

    // Create the shield as a box with the dimensions from SP->GetShield().size
    G4Box* shieldBox = new G4Box("Shield",
                                 SP->GetShield().size[0] / 2,  // Half-length in X
                                 SP->GetShield().size[1] / 2,  // Half-length in Y
                                 SP->GetShield().size[2] / 2); // Half-length in Z

    // Create a logical volume for the shield
    G4LogicalVolume* shieldLogical = new G4LogicalVolume(shieldBox, shieldMaterial, "ShieldLogical");

    // Define the position of the shield from SP->GetShield().pos
    G4ThreeVector shieldPosition = G4ThreeVector(SP->GetShield().pos[0], SP->GetShield().pos[1],
                                                                       SP->GetShield().pos[2]);

    // Place the shield in the mother volume
    G4VPhysicalVolume* shieldPhysical = new G4PVPlacement(
        nullptr,                      // No rotation
        shieldPosition,               // Position
        shieldLogical,                // Logical volume
        "ShieldPhysical",             // Name
        MotherVolume,                 // Mother volume
        false,                        // No boolean operations
        0,                            // Copy number
        true);                        // Check overlaps

    return shieldPhysical; // Return the physical volume of the shield
}

G4VPhysicalVolume* DetectorConstruction::ConstructMouseLeg(G4LogicalVolume* MotherVolume, G4double depth){
    // Get the NIST material manager to look up materials
    G4NistManager* nist = G4NistManager::Instance();

    // Get the material for the mouse leg (G4_WATER is used as a placeholder)
    G4Material* legMaterial = nist->FindOrBuildMaterial("G4_TISSUE_SOFT_ICRP");
    if (!legMaterial) {
        G4cerr << "Error: Material G4_WATER not found!" << G4endl;
        return nullptr;
    }


    // Define the cylindrical shape for the mouse leg
    G4double legRadius = 2.5 * mm;  // Radius of the leg
    G4double legLength = 20.0 * mm; // Length of the leg

    // Create the mouse leg as a cylinder
    G4Tubs* legCylinder = new G4Tubs("MouseLeg",
                                     0,              // Inner radius (0 for a solid cylinder)
                                     legRadius,      // Outer radius
                                     legLength / 2,  // Half-length in Z (because Geant4 uses half-lengths)
                                     0,              // Starting angle of the segment (full circle here)
                                     360 * deg);     // Angle span of the segment (360 degrees for a full cylinder)

    // Create a logical volume for the mouse leg
    G4LogicalVolume* legLogical = new G4LogicalVolume(legCylinder, legMaterial, "MouseLegLogical");

    // Define the position of the mouse leg
    G4ThreeVector legPosition = G4ThreeVector(0, -2.5, legRadius+depth);

    // Define a rotation matrix to rotate the cylinder by 90 degrees around the X-axis
    G4RotationMatrix* rotation = new G4RotationMatrix();
    rotation->rotateX(90 * deg);  // Rotate by 90 degrees around the X-axis

    // Place the mouse leg in the mother volume with the defined rotation
    G4VPhysicalVolume* legPhysical = new G4PVPlacement(
        rotation,                   // Apply the 90-degree rotation
        legPosition,                // Position
        legLogical,                 // Logical volume
        "MouseLegPhysical",         // Name
        MotherVolume,               // Mother volume
        false,                      // No boolean operations
        0,                          // Copy number
        true);                      // Check overlaps

    return legPhysical; // Return the physical volume of the mouse leg
}
