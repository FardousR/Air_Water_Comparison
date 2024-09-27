#include "SimulationParameters.hh"
#include <iostream>
#include <iomanip>

#include "SimulationParameters.hh"
#include <iostream>
#include <iomanip>

void SimulationParameters::PrintParameters() const {
    // Set up formatting for table output
    const int label_width = 30;
    const int value_width = 20;

    std::cout << std::left << std::setw(label_width) << "Parameter"
              << std::setw(value_width) << "Value" << std::endl;
    std::cout << std::string(label_width + value_width, '-') << std::endl;

    // Print particle and simulation settings
    std::cout << std::left << std::setw(label_width) << "Particle Type"
              << std::setw(value_width) << bm.particle << std::endl;
    std::cout << std::setw(label_width) << "Number of Threads"
              << std::setw(value_width) << setup.n_thread << std::endl;
    std::cout << std::setw(label_width) << "Number of Particles"
              << std::setw(value_width) << setup.n_particle << std::endl;
    std::cout << std::setw(label_width) << "Progress Interval"
              << std::setw(value_width) << setup.n_progress << " particles" << std::endl;

    // Print physics parameters
    std::cout << std::setw(label_width) << "Physics List"
              << std::setw(value_width) << phy.phy_list << std::endl;
    std::cout << std::setw(label_width) << "Step Length"
              << std::setw(value_width) << phy.step_length / mm << " mm" << std::endl;
    std::cout << std::setw(label_width) << "Use Step Limiter for Neutrals"
              << std::setw(value_width) << (phy.use_sl_neutral ? "Yes" : "No") << std::endl;
    std::cout << std::setw(label_width) << "Production Cuts (Photon, Electron, Proton, Neutron)"
              << "[" << phy.production_cut[0] / mm << " mm, "
              << phy.production_cut[1] / mm << " mm, "
              << phy.production_cut[2] / mm << " mm, "
              << phy.production_cut[3] / mm << " mm]" << std::endl;

    // Print beam parameters
    std::cout << std::setw(label_width) << "SOBP File"
              << std::setw(value_width) << bm.planFile << std::endl;
    std::cout << std::setw(label_width) << "SADx"
              << std::setw(value_width) << bm.sad[0] / mm << " mm" << std::endl;
    std::cout << std::setw(label_width) << "SADy"
              << std::setw(value_width) << bm.sad[1] / mm << " mm" << std::endl;
    std::cout << std::setw(label_width) << "Number of Spots"
              << std::setw(value_width) << bm.num_spots << std::endl;

    // Print grid and collimator parameters
    std::cout << std::setw(label_width) << "Grid Enabled"
              << std::setw(value_width) << (setup.use_coll ? "Yes" : "No") << std::endl;
    std::cout << std::setw(label_width) << "Grid-Phantom Distance"
              << std::setw(value_width) << coll.pos[2] / mm << " mm" << std::endl;
    std::cout << std::setw(label_width) << "Grid Center-to-Center Distance"
              << std::setw(value_width) << coll.ctc / mm << " mm" << std::endl;
    std::cout << std::setw(label_width) << "Grid Thickness"
              << std::setw(value_width) << coll.len[2] / mm << " mm" << std::endl;
    std::cout << std::setw(label_width) << "Grid Throughput"
              << std::setw(value_width) << coll.throughput << std::endl;
    std::cout << std::setw(label_width) << "Collimator X Angle"
              << std::setw(value_width) << coll.angle[0] << " radians" << std::endl;
    std::cout << std::setw(label_width) << "Collimator Y Angle"
              << std::setw(value_width) << coll.angle[1] << " radians" << std::endl;
    std::cout << std::setw(label_width) << "Collimator Z Angle"
              << std::setw(value_width) << coll.angle[2] << " radians" << std::endl;
    std::cout << std::setw(label_width) << "Collimator X Shift"
              << std::setw(value_width) << coll.pos[0] / mm << " mm" << std::endl;
    std::cout << std::setw(label_width) << "Collimator Y Shift"
              << std::setw(value_width) << coll.pos[1] / mm << " mm" << std::endl;
    std::cout << std::setw(label_width) << "Grid Material"
              << std::setw(value_width) << coll.mat << std::endl;
    std::cout << std::setw(label_width) << "Max Slit Extension X"
              << "[" << coll.maxSlitExtX[0] / mm << " mm, "
              << coll.maxSlitExtX[1] / mm << " mm]" << std::endl;
    std::cout << std::setw(label_width) << "Max Slit Extension Y"
              << "[" << coll.maxSlitExtY[0] / mm << " mm, "
              << coll.maxSlitExtY[1] / mm << " mm]" << std::endl;

    // Print PTV boundary parameters
    std::cout << std::setw(label_width) << "PTV X Range"
              << "[" << ptv.xRange[0] / mm << " mm, "
              << ptv.xRange[1] / mm << " mm]" << std::endl;
    std::cout << std::setw(label_width) << "PTV Y Range"
              << "[" << ptv.yRange[0] / mm << " mm, "
              << ptv.yRange[1] / mm << " mm]" << std::endl;
    std::cout << std::setw(label_width) << "PTV Z Range"
              << "[" << ptv.zRange[0] / mm << " mm, "
              << ptv.zRange[1] / mm << " mm]" << std::endl;

    // Print histogram bin widths
    std::cout << std::setw(label_width) << "X Bin Width"
              << "[" << his.xBinWidth[0] / mm << " mm, "
              << his.xBinWidth[1] / mm << " mm, "
              << his.xBinWidth[2] / mm << " mm]" << std::endl;
    std::cout << std::setw(label_width) << "Y Bin Width"
              << "[" << his.yBinWidth[0] / mm << " mm, "
              << his.yBinWidth[1] / mm << " mm, "
              << his.yBinWidth[2] / mm << " mm]" << std::endl;
    std::cout << std::setw(label_width) << "Z Bin Width"
              << "[" << his.zBinWidth[0] / mm << " mm, "
              << his.zBinWidth[1] / mm << " mm, "
              << his.zBinWidth[2] / mm << " mm]" << std::endl;

    // Print shield parameters
    std::cout << std::setw(label_width) << "Shield Material"
              << std::setw(value_width) << shield.mat << std::endl;
    std::cout << std::setw(label_width) << "Shield Position"
              << "[" << shield.pos[0] / mm << " mm, "
              << shield.pos[1] / mm << " mm, "
              << shield.pos[2] / mm << " mm]" << std::endl;
    std::cout << std::setw(label_width) << "Shield Size"
              << "[" << shield.size[0] / mm << " mm, "
              << shield.size[1] / mm << " mm, "
              << shield.size[2] / mm << " mm]" << std::endl;

    // Print file names and GUI settings
    std::cout << std::setw(label_width) << "Output File"
              << std::setw(value_width) << setup.out_file << std::endl;
    std::cout << std::setw(label_width) << "GUI Enabled"
              << std::setw(value_width) << (setup.use_gui ? "Yes" : "No") << std::endl;

    return;
}

void SimulationParameters::PrintSpotsParameters() const {
    // Header
    std::cout << std::endl;
    std::cout << std::setw(40) << "***----------------------------------------------------------- Spots Parameters ---------------------------------------------------------***" << std::endl;
    std::cout << std::endl;

    // Column names
    std::cout << std::setw(8)  << "No"
              << std::setw(12) << "Energy"
              << std::setw(12) << "Spread"
              << std::setw(12) << "Spot(x)"
              << std::setw(12) << "Spot(y)"
              << std::setw(12) << "Sig(x)"
              << std::setw(12) << "Sig(y)"
              << std::setw(12) << "Div(x)"
              << std::setw(12) << "Div(y)"
              << std::setw(12) << "Cov(x)"
              << std::setw(12) << "Cov(y)"
              << std::setw(12) << "Weight"
              << std::endl;

    // Separator
    std::cout << std::setw(8)  << "---"
              << std::setw(12) << "------"
              << std::setw(12) << "------"
              << std::setw(12) << "------"
              << std::setw(12) << "------"
              << std::setw(12) << "------"
              << std::setw(12) << "------"
              << std::setw(12) << "------"
              << std::setw(12) << "------"
              << std::setw(12) << "------"
              << std::setw(12) << "------"
              << std::setw(12) << "------"
              << std::endl;

    // Print each spot at intervals of 400
    for (std::size_t i = 0; i < bm.spots.size(); i += 1) {
        const auto& spot = bm.spots[i];
        std::cout << std::setw(8)  << i + 1
                  << std::setw(12) << std::setprecision(4) << spot.energy
                  << std::setw(12) << std::setprecision(4) << spot.e_spread
                  << std::setw(12) << std::setprecision(4) << spot.spotx
                  << std::setw(12) << std::setprecision(4) << spot.spoty
                  << std::setw(12) << std::setprecision(4) << spot.sig_x
                  << std::setw(12) << std::setprecision(4) << spot.sig_y
                  << std::setw(12) << std::setprecision(4) << spot.div_x
                  << std::setw(12) << std::setprecision(4) << spot.div_y
                  << std::setw(12) << std::setprecision(4) << spot.cov_x
                  << std::setw(12) << std::setprecision(4) << spot.cov_y
                  << std::setw(12) << std::setprecision(2) << spot.weight
                  << std::endl;
    }

    std::cout << std::endl << std::endl;
    return;
}
