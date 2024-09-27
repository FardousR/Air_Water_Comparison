
#ifndef DetectorConstruction_h
#define DetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "SimulationParameters.hh"
#include "globals.hh"
#include "G4UserLimits.hh"
#include "G4NistManager.hh"
#include "G4Tubs.hh"
#include "G4Box.hh"
#include "G4PVPlacement.hh"
#include "G4LogicalVolume.hh"
#include "G4SystemOfUnits.hh"
#include "G4VisAttributes.hh"
#include "G4SubtractionSolid.hh"
#include "G4UnionSolid.hh"
#include "G4MultiUnion.hh"
#include "G4Region.hh"
#include "G4ProductionCuts.hh"
#include "G4RegionStore.hh"
#include <iostream>
#include <stdlib.h>

class G4VPhysicalVolume;
class G4LogicalVolume;

/// Detector construction class to define materials and geometry.

class DetectorConstruction : public G4VUserDetectorConstruction
{
  public:
    DetectorConstruction(SimulationParameters* aSP);
    virtual ~DetectorConstruction();
    virtual G4VPhysicalVolume* Construct();

    G4LogicalVolume* GetScoringVolume() const { return fScoringVolume; }
    G4VPhysicalVolume* ConstructWorld();
    G4VPhysicalVolume* ConstructAir(G4LogicalVolume* MotherVolume);
    G4VPhysicalVolume* ConstructShield(G4LogicalVolume* MotherVolume);
    G4VPhysicalVolume* ConstructPhantom(G4LogicalVolume* MotherVolume);
    G4VPhysicalVolume* ConstructCollimator(G4LogicalVolume* MotherVolume);
    G4VPhysicalVolume* ConstructMouseLeg(G4LogicalVolume* MotherVolume, G4double depth);

  private:
    G4UserLimits*   StepLimit;
    SimulationParameters* SP;

  protected:
    G4LogicalVolume*  fScoringVolume;
};
#endif
