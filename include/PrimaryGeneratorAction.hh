#ifndef PrimaryGeneratorAction_h
#define PrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "SimulationParameters.hh"
#include "globals.hh"
#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"
#include "DataType.hh"

// Add the correct type for spot based on PlanSpot
class PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction {
public:
    PrimaryGeneratorAction(SimulationParameters* aSP);
    virtual ~PrimaryGeneratorAction();
    // Generate primary particles for an event
    virtual void GeneratePrimaries(G4Event* anEvent) override;
    void multivariateGaussian(double mean_x, double mean_y, double sigma_x,
                              double sigma_y, double cov_xy, double& x, double& y);

private:
    SimulationParameters* SP;  // Pointer to simulation parameters
    G4ParticleGun* fParticleGun;
    G4int total_number_spots;
    G4double total_weight_spots;
    G4double SADx, SADy;
    G4double pos_x, pos_y, pos_z, dir_x, dir_y, dir_z;

    SpotParameter spot;  // Correct type for spots in the beam

    G4int spot_selector();
};


#endif
