#ifndef DataType_h
#define DataType_h 1
#include <iostream>
#include <vector>
#include <array>
#include "G4Event.hh"
#include "G4SystemOfUnits.hh"
#include "G4SteppingManager.hh"
#include "G4VTouchable.hh"
#include "G4VPhysicalVolume.hh"
#include "G4TrackVector.hh"
#include "G4ProcessType.hh"
#include "G4Region.hh"
#include "G4ThreeVector.hh"

// Avoid using namespace std in headers.
extern struct SetupParameter {
    int n_particle;
    int n_progress;
    int n_thread;
    std::string out_file;
    bool place_phantom;
    bool place_mouse;
    bool use_gui;
    bool use_coll;
    bool use_shield;
} SetupParameter_;

extern struct PhysicsParameter {
    std::string phy_list;
    double step_length;
    bool use_sl_neutral;
    std::array<double, 4> production_cut;
} PhysicsParameter_;

extern struct SpotParameter {
    double energy;
    double e_spread;
    double spotx;
    double spoty;
    double sig_x;
    double sig_y;
    double div_x;
    double div_y;
    double cov_x;
    double cov_y;
    double weight;
} SpotParameter_;

extern struct BeamParameter {
    std::string particle;
    std::string planFile;
    double position;
    std::array<double, 2> sad;
    std::vector<SpotParameter> spots;
    double total_weight;
    int num_spots;
} BeamParameter_;

extern struct PtvParameter {
    std::array<double, 2> xRange;
    std::array<double, 2> yRange;
    std::array<double, 2> zRange;
} PtvParameter_;

extern struct CollimatorParameter {
    std::string mat;
    std::array<double, 3> len;
    std::array<double, 3> pos;
    std::array<double, 3> angle;
    std::array<double, 2> maxSlitExtX;
    std::array<double, 2> maxSlitExtY;
    double ctc;
    double throughput;
    double slitWidth;
    std::vector<double> peakCenters;
    std::vector<double> valleyCenters;
} CollimatorParameter_;

extern struct ShieldParameter {
    std::string mat;
    double pos[3];
    double size[3];
} ShieldParameter_;

extern struct VoxelSegment {
    G4ThreeVector center;    // Center of the voxel
    G4double stepLength;     // Length of the step within the voxel
    G4double energyDeposit;  // Energy deposit in the voxel
} VoxelSegment_;


extern struct HistogramParameter {
    std::array<double, 2> xRange;
    std::array<double, 2> yRange;
    std::array<double, 2> zRange;
    std::array<double, 2> xBinNum;
    std::array<double, 2> yBinNum;
    std::array<double, 2> zBinNum;
    std::array<double, 3> xBinWidth;
    std::array<double, 3> yBinWidth;
    std::array<double, 3> zBinWidth;
} HistogramParameter_;

extern struct HistogramSize {
    double xBinNum;
    double yBinNum;
    double zBinNum;
    std::array<double, 2> xRange;
    std::array<double, 2> yRange;
    std::array<double, 2> zRange;
} HistogramSize_;

extern struct HistogramScoringParameter {
    std::array<double, 3> xProfile;
    std::array<double, 3> yProfile;
    std::array<double, 3> zProfile;
} HistogramScoringParameter_;

extern struct ScoredQuantity {
  int EventID;
  int TrackID;
  int ParentID;
  int ProcessSubType;
  int ParticleGenType;
  int ParticlePDGcode;
  double ParticleCharge;
  double StepInitialKE;
  double StepFinalKE;
  double StepMeanKE;
  double TotalSecondaryEnergy;
  double EnergyDeposit;
  double StepLength;
  double MaterialDensity;
  double WatDoseFactor;
  double WatSPFactor;
  double WatEnergyFactor;
  double StoppingPower;
  double WatStoppingPower;
  double GeometryVolume;
  std::string ParticleName;
  std::string ProcessName;
  std::string GeometryComponent;
  const G4Step* CurrentStep;
  G4ThreeVector PreStepPosition;
  G4ThreeVector PostStepPosition;
  G4ThreeVector EnergyDepositPoint;
  G4ProcessType ProcessType;
} ScoredQuantity_;

#endif
