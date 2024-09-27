#include "DetectorConstruction.hh"

//#include "PhysicalConstants.hh"

//****************************************************************************//

DetectorConstruction::DetectorConstruction(SimulationParameters* aSP)
{
  SP = aSP;
  StepLimit = new G4UserLimits(SP->GetPhysics().step_length);
}

//****************************************************************************//

DetectorConstruction::~DetectorConstruction()
{
  delete StepLimit;
}

//****************************************************************************//

G4VPhysicalVolume* DetectorConstruction::Construct()
{
  G4Region* ScoringRegion = new G4Region("ScoringRegion");

  // Construct World volume
  G4VPhysicalVolume* physical_world = ConstructWorld();
  G4VPhysicalVolume* physical_air = ConstructAir(physical_world->GetLogicalVolume());
  physical_air->GetLogicalVolume()->SetUserLimits(StepLimit);
  ScoringRegion->AddRootLogicalVolume(physical_air->GetLogicalVolume());
  G4VPhysicalVolume* physical_phantom;
  if (SP->GetSetup().place_phantom){
    physical_phantom = ConstructPhantom(physical_air->GetLogicalVolume());
    physical_phantom->GetLogicalVolume()->SetUserLimits(StepLimit);
    ScoringRegion->AddRootLogicalVolume(physical_phantom->GetLogicalVolume());
  }

  if (SP->GetSetup().use_coll){
    G4VPhysicalVolume* physical_collimator = ConstructCollimator(physical_air->GetLogicalVolume());
    physical_collimator->GetLogicalVolume()->SetUserLimits(StepLimit);
    ScoringRegion->AddRootLogicalVolume(physical_collimator->GetLogicalVolume());
  }

  if (SP->GetSetup().place_mouse){
    G4LogicalVolume* environment =physical_air->GetLogicalVolume();
    G4double depth = 0;

    if (SP->GetSetup().place_phantom){
      environment =  physical_phantom->GetLogicalVolume();
      depth = -200;
    }

    G4VPhysicalVolume* physical_mouse = ConstructMouseLeg(environment, depth);
    physical_mouse->GetLogicalVolume()->SetUserLimits(StepLimit);
    ScoringRegion->AddRootLogicalVolume(physical_mouse->GetLogicalVolume());
  }

  G4ProductionCuts* cuts = new G4ProductionCuts;
    cuts->SetProductionCut(0.05, G4ProductionCuts::GetIndex("gamma"));
    cuts->SetProductionCut(0.05, G4ProductionCuts::GetIndex("e-"));
    cuts->SetProductionCut(0.05, G4ProductionCuts::GetIndex("e+"));
    cuts->SetProductionCut(0.05, G4ProductionCuts::GetIndex("proton"));
  ScoringRegion->SetProductionCuts(cuts);

  ScoringRegion->SetUserLimits(StepLimit);
  return physical_world;
}

G4VPhysicalVolume* DetectorConstruction::ConstructWorld(){
  G4NistManager* nist = G4NistManager::Instance();
  G4Material* vacuum = nist->FindOrBuildMaterial("G4_Galactic");
  G4bool checkOverlaps = true;

  // Construct World volume
  G4double world_x = 2000*mm, world_y = 2000*mm, world_z = 6000*mm;

  G4Box* solid_world             = new G4Box("World", world_x/2, world_y/2, world_z/2);
  G4LogicalVolume* logical_world =
               new G4LogicalVolume(solid_world,                           //its solid
                                   vacuum,                                //its material
                                   "world");                              //its name

  // Visual attributes of the world
  G4VisAttributes * world_visAtt = new G4VisAttributes(G4Colour(0.0,1.0,1.0));
  world_visAtt->SetForceWireframe(true);
  logical_world->SetVisAttributes(world_visAtt);

  // Physical placment of the world volume
  G4VPhysicalVolume* physical_world =
                    new G4PVPlacement(0,                                  //no rotation
                                      G4ThreeVector(),                    //at (0,0,0)
                                      logical_world,                      //its logical volume
                                      "world",                            //its name
                                      0,                                  //its mother  volume
                                      false,                              //no boolean operation
                                      0,                                  //copy number
                                      checkOverlaps);                     //overlaps checking
 return physical_world;
}

G4VPhysicalVolume* DetectorConstruction::ConstructAir(G4LogicalVolume* MotherVolume){
  G4NistManager* nist = G4NistManager::Instance();
  G4Material* air = nist->FindOrBuildMaterial("G4_AIR");
  G4bool checkOverlaps = true;

  G4double air_x = 1000*mm, air_y = 1000*mm, air_z = 1790*mm;
  G4Box* solid_air             = new G4Box("air", air_x/2, air_y/2, air_z/2);
  G4LogicalVolume* logical_air =
             new G4LogicalVolume(solid_air,                               //its solid
                                 air,                                     //its material
                                 "air");                                  //its name
  // Visual attributes of the air
  G4VisAttributes* air_visAtt = new G4VisAttributes(G4Colour(0.0,1.0,1.0));
  air_visAtt->SetForceWireframe(true);
  logical_air->SetVisAttributes(air_visAtt);

  // Physical placment of the air volume
  G4VPhysicalVolume* physical_air =
                  new G4PVPlacement(0,                                     //no rotation
                                    G4ThreeVector(),                       //at (0,0,0)
                                    logical_air,                           //its logical volume
                                    "air",                                 //its name
                                    MotherVolume,                         //its mother  volume
                                    false,                                 //no boolean operation
                                    0,                                     //copy number
                                    checkOverlaps);                        //overlaps checking
 return physical_air;
}

G4VPhysicalVolume* DetectorConstruction::ConstructPhantom(G4LogicalVolume* MotherVolume){
  G4NistManager* nist = G4NistManager::Instance();
  G4Material* water = nist->FindOrBuildMaterial("G4_WATER");
  G4bool checkOverlaps = true;

  G4double air_x = 400*mm, air_y = 400*mm, air_z = 400*mm;
  G4Box* solid_phantom = new G4Box("pahantom", air_x/2, air_y/2, air_z/2);
  G4LogicalVolume* logical_phantom =
             new G4LogicalVolume(solid_phantom,                               //its solid
                                 water,                                     //its material
                                 "phantom");                                  //its name

  // Visual attributes of the water (water-like blue color with 0.3 transparency)
  G4VisAttributes* phantom_visAtt = new G4VisAttributes(G4Colour(0.0, 0.5, 1.0, 0.3));  // Blue color with transparency
  phantom_visAtt->SetForceWireframe(true);  // Wireframe view
  phantom_visAtt->SetForceSolid(true);      // Force solid view (will show transparency)
  logical_phantom->SetVisAttributes(phantom_visAtt);

  // Physical placment of the air volume
  G4VPhysicalVolume* physical_phantom =
                  new G4PVPlacement(0,                                     //no rotation
                                    G4ThreeVector(0, 0, air_z/2),                       //at (0,0,0)
                                    logical_phantom,                           //its logical volume
                                    "phantom",                                 //its name
                                    MotherVolume,                         //its mother  volume
                                    false,                                 //no boolean operation
                                    0,                                     //copy number
                                    checkOverlaps);                        //overlaps checking
 return physical_phantom;
}
