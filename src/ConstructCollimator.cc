#include "G4Box.hh"
#include "G4MultiUnion.hh"
#include "G4PVPlacement.hh"
#include "G4SubtractionSolid.hh"
#include "G4LogicalVolume.hh"
#include "G4NistManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4Transform3D.hh"
#include "G4VisAttributes.hh"
#include "G4Material.hh"
#include "G4Colour.hh"
#include "G4RotationMatrix.hh"
#include "G4ThreeVector.hh"
#include "DataType.hh"
#include "DetectorConstruction.hh"

// Helper function to add a slit at a specified Y position
void AddSlit(G4MultiUnion* msc_slits, G4Box* solid_msc_slit, G4double slit_pos_y, G4double ctc, CollimatorParameter& coll) {
    G4Transform3D Transformation3D(G4RotationMatrix(), G4ThreeVector(0, slit_pos_y, 0));
    msc_slits->AddNode(*solid_msc_slit, Transformation3D);

    // Track peak and valley centers
    coll.peakCenters.push_back(slit_pos_y + coll.pos[1]); // Peak center (slit position)
    coll.valleyCenters.push_back(slit_pos_y + coll.pos[1] + ctc / 2); // Valley center (midway between slits)

    if (slit_pos_y != 0) {
        // Add symmetric slit on the negative Y side
        Transformation3D = G4Transform3D(G4RotationMatrix(), G4ThreeVector(0, -slit_pos_y, 0));
        msc_slits->AddNode(*solid_msc_slit, Transformation3D);

        // Track symmetric peak and valley centers
        coll.peakCenters.push_back(-slit_pos_y);  // Symmetric peak center
        coll.valleyCenters.push_back(-(slit_pos_y + ctc / 2));  // Symmetric valley center
    }
}

G4VPhysicalVolume* DetectorConstruction::ConstructCollimator(G4LogicalVolume* MotherVolume)
{
    // Extract collimator parameters
    G4bool checkOverlaps = true;
    CollimatorParameter coll = SP->GetCollimator();
    G4double ph_col_dis = -(coll.pos[2] + coll.len[2] / 2) * mm;
    G4NistManager* nist = G4NistManager::Instance();
    G4Material* matmsc = nist->FindOrBuildMaterial(coll.mat);  // Collimator material

    // Create a msc plate and slits
    G4Box* solid_msc_plate = new G4Box("msc_plate", (coll.len[0] + 100.00) / 2, (coll.len[1] + 100.00) / 2, coll.len[2]/ 2);
    G4Box* solid_msc_slit = new G4Box("msc_slit", coll.len[0] / 2, coll.slitWidth / 2, coll.len[2] + 1.00 / 2);
    G4MultiUnion* msc_slits = new G4MultiUnion("msc_slits");

    // Slit placement logic
    if (coll.maxSlitExtY[0] == 0 && coll.maxSlitExtY[1] == 0) {
        // Uniform slit placement along Y-axis
        for (G4double slit_pos_y = 0; slit_pos_y <= (coll.len[1] - coll.slitWidth) / 2; slit_pos_y += coll.ctc) {
            AddSlit(msc_slits, solid_msc_slit, slit_pos_y, coll.ctc, coll);
        }
    } else {
        // Slit placement within a specified Y-range
        for (G4double slit_pos_y = coll.maxSlitExtY[0] - coll.slitWidth / 2; slit_pos_y <= coll.maxSlitExtY[1] - coll.slitWidth / 2; slit_pos_y += coll.ctc) {
            AddSlit(msc_slits, solid_msc_slit, slit_pos_y, coll.ctc, coll);
        }
    }

    msc_slits->Voxelize();  // Finalize the union of slits

    // Subtract slits from the msc plate to create the final msc
    G4SubtractionSolid* solid_msc = new G4SubtractionSolid("msc", solid_msc_plate, msc_slits, 0, G4ThreeVector(0, 0, 0));

    // Logical volume for the msc
    G4LogicalVolume* logical_msc = new G4LogicalVolume(solid_msc, matmsc, "msc");

    // Set visual attributes for the msc
    G4VisAttributes* msc_visAtt = new G4VisAttributes(G4Colour(0.72, 0.45, 0.20, 1.0));  // Copper color (R, G, B, Alpha)
    msc_visAtt->SetForceSolid(true);
    logical_msc->SetVisAttributes(msc_visAtt);

    // Transform the msc (rotation and translation)
    G4Transform3D Transformation3D = G4Transform3D(G4RotationMatrix((coll.angle[0] / 1000) * rad, (coll.angle[1] / 1000) * rad, (coll.angle[2] / 1000) * rad),
                                                                     G4ThreeVector(coll.pos[0], coll.pos[1], ph_col_dis));

    // Place the msc in the mother volume
    return new G4PVPlacement(Transformation3D, logical_msc, "msc", MotherVolume, false, 0, checkOverlaps);
}
