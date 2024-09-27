#ifndef SimulationParameters_h
#define SimulationParameters_h 1

#include "G4SystemOfUnits.hh"
#include "G4ThreeVector.hh"
#include "DataType.hh"
#include <string>
#include <vector>

class SimulationParameters
{
 public:
    SimulationParameters(int argc, char** argv);
    ~SimulationParameters();

    void Initialization(int argc, char** argv);
    void AssignDefaultParameters();
    void PrintHelp();
    void PrintParameters() const;
    void PrintSpotsParameters() const;

    // Getter and Setter for PtvParameter
    const PtvParameter& GetPTV() const { return ptv; }
    void SetPTV(const PtvParameter& new_ptv) { ptv = new_ptv; }

    // Getter and Setter for BeamParameter
    const BeamParameter& GetBeam() const { return bm; }
    void SetBeam(const BeamParameter& new_bm) { bm = new_bm; }

    // Getter and Setter for SetupParameter
    const SetupParameter& GetSetup() const { return setup; }
    void SetSetup(const SetupParameter& new_setup) { setup = new_setup; }

    // Getter and Setter for PhysicsParameter
    const PhysicsParameter& GetPhysics() const { return phy; }
    void SetPhysics(const PhysicsParameter& new_phy) { phy = new_phy; }

    // Getter and Setter for CollimatorParameter
    const CollimatorParameter& GetCollimator() const { return coll; }
    void SetCollimator(const CollimatorParameter& new_coll) { coll = new_coll; }

    // Getter and Setter for HistogramParameter
    const HistogramParameter& GetHistogram() const { return his; }
    void SetHistogram(const HistogramParameter& new_his) { his = new_his; }

    // Getter and Setter for ShieldParameter
    const ShieldParameter& GetShield() const { return shield; }
    void SetShield(const ShieldParameter& new_shield) { shield = new_shield; }

    // Default parameter assignment methods
    void AssignDefaultSetupParameters();
    void AssignDefaultPhysicsParameters();
    void AssignDefaultBeamParameters();
    void AssignDefaultPTVParameters();
    void AssignDefaultCollimatorParameters();
    void AssignDefaultHistogramParameters();
    void AssignDefaultShieldParameters();
    void AssignSpots();
    void AssignTotal();

 private:
    PtvParameter ptv;               // PTV parameters
    BeamParameter bm;               // Beam parameters
    SetupParameter setup;           // Setup parameters
    PhysicsParameter phy;           // Physics parameters
    CollimatorParameter coll;       // Collimator parameters
    ShieldParameter shield;         // Shield parameters
    HistogramParameter his;         // Histogram parameters
};

#endif
