#include "SimulationParameters.hh"
#include <stdexcept>

#include <string>
#include <vector>
using namespace std;

// Functions to assign default values

void SimulationParameters::AssignDefaultSetupParameters() {
    setup.n_particle = 100000;        // Default number of particles
    setup.n_progress = 50000;         // Default progress update interval
    setup.n_thread = 5;               // Default number of threads
    setup.out_file = "output.root";   // Default output file
    setup.use_gui = 0;                // GUI disabled by default
    setup.use_coll = 0;               // MSC disabled by default
    setup.use_shield = 0;             // Shield disabled by default
    setup.place_phantom = 0;          // Phantom placement disabled by default
    setup.place_mouse = 0;            // Mouse placement disabled by default
}


void SimulationParameters::AssignDefaultPhysicsParameters() {
    phy.phy_list = "QGSP_BIC_EMY"; // Default physics list
    phy.step_length = 1.0;            // Default step length
    phy.use_sl_neutral = false;       // Use step limiter for neutrals
    phy.production_cut[0] = 0.1;      // Default photon production cut
    phy.production_cut[1] = 0.1;      // Default electron production cut
    phy.production_cut[2] = 0.1;      // Default proton production cut
    phy.production_cut[3] = 0.1;
}

void SimulationParameters::AssignDefaultBeamParameters() {
    bm.particle = "proton";         // Default particle type
    bm.planFile = "Plan.dat";       // Default plan file
    bm.position = 0.0;              // Default beam position
    bm.sad[0] = 2560.0;             // Default SAD in X
    bm.sad[1] = 2000.0;             // Default SAD in Y
    bm.total_weight = 1.0;          // Default total weight of beam
    bm.num_spots = 0;               // Default number of spots
    bm.spots.clear();               // Clear any existing spots
}

void SimulationParameters::AssignDefaultPTVParameters() {
    ptv.xRange[0] = -50.0;             // Default minimum X of PTV
    ptv.xRange[1] = 50.0;              // Default maximum X of PTV
    ptv.yRange[0] = -50.0;             // Default minimum Y of PTV
    ptv.yRange[1] = 50.0;              // Default maximum Y of PTV
    ptv.zRange[0] = -50.0;             // Default minimum Z of PTV
    ptv.zRange[1] = 50.0;              // Default maximum Z of PTV
}

void SimulationParameters::AssignDefaultCollimatorParameters() {
    coll.mat = "G4_W";        // Default collimator material
    coll.len[0] = 180.0;          // Default length X
    coll.len[1] = 80.0;          // Default length Y
    coll.len[2] = 25.0;          // Default length Z
    coll.pos[0] = 0.0;            // Default position X
    coll.pos[1] = 0.0;            // Default position Y
    coll.pos[2] = 50.0;            // Default position Z
    coll.angle[0] = 0.0;          // Default angle X
    coll.angle[1] = 0.0;          // Default angle Y
    coll.angle[2] = 0.0;          // Default angle Z
    coll.maxSlitExtX[0] =  0.0;   // Default max slit X min
    coll.maxSlitExtX[1] =  0.0;   // Default max slit X max
    coll.maxSlitExtY[0] = 0.0;    // Default max slit Y min
    coll.maxSlitExtY[1] = 0.0;    // Default max slit Y max
    coll.ctc = 2.0;               // Default center-to-center distance
    coll.throughput = 0.5;        // Default throughput
    coll.slitWidth = coll.ctc * coll.throughput;
}

void SimulationParameters::AssignDefaultHistogramParameters() {
    his.xRange[0] = -100.0;     // Default X range min
    his.xRange[1] = 100.0;      // Default X range max
    his.yRange[0] = -100.0;     // Default Y range min
    his.yRange[1] = 100.0;      // Default Y range max
    his.zRange[0] = -100.0;     // Default Z range min
    his.zRange[1] = 100.0;      // Default Z range max
    his.xBinWidth[0] = 1.0;     // Default X bin width min
    his.xBinWidth[1] = 1.0;     // Default X bin width max
    his.xBinWidth[2] = 1.0;     // Default X bin width max
    his.yBinWidth[0] = 1.0;     // Default Y bin width min
    his.yBinWidth[1] = 1.0;     // Default Y bin width max
    his.yBinWidth[2] = 1.0;     // Default Y bin width max
    his.zBinWidth[0] = 1.0;     // Default Z bin width min
    his.zBinWidth[1] = 1.0;     // Default Z bin width max
    his.zBinWidth[2] = 1.0;     // Default Z bin width max
}


void SimulationParameters::AssignDefaultShieldParameters() {
    shield.mat = "Lead";         // Default material
    shield.pos[0] = 0.0;         // Default position X
    shield.pos[1] = 0.0;         // Default position Y
    shield.pos[2] = 0.0;         // Default position Z
    shield.size[0] = 10.0;       // Default size X
    shield.size[1] = 10.0;       // Default size Y
    shield.size[2] = 10.0;       // Default size Z
}
