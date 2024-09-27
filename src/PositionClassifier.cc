#include "Analysis.hh"

// Check if y is within the peak area based on the spread and ctc constant
G4bool Analysis::inPeak(G4double y, G4double spread) {
    // return ((1 * ctc - spread) <= y && y <= (1 * ctc + spread)) ||
    //        ((0 * ctc - spread) <= y && y <= (0 * ctc + spread)) ||
    //        (-(1 * ctc + spread) <= y && y <= -(1 * ctc - spread));
}

// Check if y is within the valley area based on the spread and ctc constant
G4bool Analysis::inValley(G4double y, G4double spread) {
    // return ((0.5 * ctc - spread) <= y && y <= (0.5 * ctc + spread)) ||
    //        (-(0.5 * ctc + spread) <= y && y <= -(0.5 * ctc - spread));
}

// Check if (x, y, z) coordinates are inside the planning target volume (PTV)
G4bool Analysis::inPTV(G4double x, G4double y, G4double z) {
    // return (SP->GetPlanningVolume()->GetMinX() < x && x < SP->GetPlanningVolume()->GetMaxX() &&
    //         SP->GetPlanningVolume()->GetMinY() < y && y < SP->GetPlanningVolume()->GetMaxY() &&
    //         SP->GetPlanningVolume()->GetMinZ() < z && z < SP->GetPlanningVolume()->GetMaxZ());
}

// Check if x is inside the PTV along the X-axis
G4bool Analysis::inPTVX(G4double x) {
    // return (SP->GetPlanningVolume()->GetMinX() < x && x < SP->GetPlanningVolume()->GetMaxX());
}

// Check if y is inside the PTV along the Y-axis
G4bool Analysis::inPTVY(G4double y) {
    // return (SP->GetPlanningVolume()->GetMinY() < y && y < SP->GetPlanningVolume()->GetMaxY());
}

// Check if z is inside the PTV along the Z-axis
G4bool Analysis::inPTVZ(G4double z) {
    // return (SP->GetPlanningVolume()->GetMinZ() < z && z < SP->GetPlanningVolume()->GetMaxZ());
}

// Check if (x, y, z) coordinates are inside the collimator region
G4bool Analysis::inCollimator(G4double x, G4double y, G4double z) {
    // G4double z1 = -(SP->GetGridDistance() + SP->GetGridThickness());
    // G4double z2 = -SP->GetGridDistance();
    // return (-150.0 < x && x < 150.0 && -100.0 < y && y < 100.0 && z1 < z && z < z2);
}

// G4bool IsPointInsideCollimatorMetalRegion(G4double x, G4double y, G4double z) {
//     G4Navigator* navigator = new G4Navigator();
//     navigator->SetWorldVolume(G4TransportationManager::GetTransportationManager()->GetNavigatorForTracking()->GetWorldVolume());
//
//     G4ThreeVector point(x, y, z);
//     G4VPhysicalVolume* volume = navigator->LocateGlobalPointAndSetup(point);
//
//     if (volume) {
//         G4LogicalVolume* logicalVolume = volume->GetLogicalVolume();
//         G4Material* material = logicalVolume->GetMaterial();
//
//         // Check if this volume is part of the collimator
//         if (logicalVolume->GetName() == "CollimatorLogicalVolume") {
//             // Check if the material is metal
//             if (material->GetName() == "Metal") {
//                 return true;  // Point is inside the metal region of the collimator
//             }
//         }
//     }
//
//     return false;  // Point is outside the metal region or not inside the collimator
// }

// Check if (x, y, z) coordinates are inside the scoring volume
G4bool Analysis::inScoringVolume(G4double x, G4double y, G4double z) {
    // return (scoMinX <= x && x <= scoMaxX &&
    //         scoMinY <= y && y <= scoMaxY &&
    //         scoMinZ <= z && z <= scoMaxZ);
}
