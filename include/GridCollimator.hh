#ifndef GridCollimator_h
#define GridCollimator_h 1

#include "globals.hh"
#include "G4UserLimits.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4SubtractionSolid.hh"
#include "G4UnionSolid.hh"
#include "G4MultiUnion.hh"
#include "G4PVPlacement.hh"
#include "G4LogicalVolume.hh"
#include "G4SystemOfUnits.hh"
#include "G4VisAttributes.hh"
#include "SimulationParameters.hh"
#include <iostream>
#include <stdlib.h>

class GridCollimator
{
  public:
    GridCollimator(SimulationParameters* aSP);
    G4Material* AssignMaterial(G4String aMat);
   ~GridCollimator();
    G4VPhysicalVolume* ConstructGridCollimator(G4LogicalVolume* MotherVolume);

  private:
    G4double grid_mat;
    G4double grid_pos_x;
    G4double grid_pos_y;
    G4double grid_pos_z;
    G4double grid_length_x;
    G4double grid_length_y;
    G4double grid_length_z;
    G4double grid_ctc;
    G4double grid_throughput;
    G4double grid_angle;

    G4double slit_size_x;
    G4double slit_size_y;
    G4double slit_size_z;
    SimulationParameters* SP;
};
#endif
