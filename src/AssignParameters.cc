#include "SimulationParameters.hh"
#include <stdexcept>
#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>

void SimulationParameters::AssignDefaultParameters() {
    // Assign setup parameters
    AssignDefaultSetupParameters();

    // Assign physics parameters
    AssignDefaultPhysicsParameters();

    // Assign beam parameters
    AssignDefaultBeamParameters();

    // Assign PTV parameters
    AssignDefaultPTVParameters();

    // Assign collimator parameters
    AssignDefaultCollimatorParameters();

    // Assign histogram parameters
    AssignDefaultHistogramParameters();

    // Assign shield parameters
    AssignDefaultShieldParameters();

    return;
}

// Helper function to parse arguments
template <typename T>
void ParseArgument(const char* arg, T& output, const std::string& errorMsg) {
    try {
        output = std::stod(arg);
    } catch (const std::invalid_argument&) {
        std::cerr << errorMsg << std::endl;
        exit(1);
    }
}

void SimulationParameters::Initialization(int argc, char** argv) {
    for (int i = 1; i < argc; ++i) {  // Start from 1 to skip argv[0] which is the program name
        std::string arg = argv[i];

        if (arg == "-h") {
            PrintHelp();
            exit(0);
        } else if (arg == "-gui") {
            setup.use_gui = true;
        } else if (arg == "-grid") {
            setup.use_coll = true;
        } else if (arg == "-phantom") {
            setup.place_phantom = true;
        } else if (arg == "-mouse") {
            setup.place_mouse = true;
        } else if (arg == "-thr") {
            if (++i < argc) {
                ParseArgument(argv[i], setup.n_thread, "Invalid argument for number of threads (-thr).");
            } else {
                std::cerr << "Missing argument for -thr option." << std::endl;
                exit(1);
            }
        } else if (arg == "-out") {
            if (++i < argc) {
                setup.out_file = argv[i];
            } else {
                std::cerr << "Missing argument for -out option." << std::endl;
                exit(1);
            }
        } else if (arg == "-sob") {
            if (++i < argc) {
                bm.planFile = argv[i];
                std::ifstream file(bm.planFile);
                if (!file) {
                    std::cerr << "SOBP file not found: " << argv[i] << std::endl;
                    exit(1);
                }
            } else {
                std::cerr << "Missing argument for -sob option." << std::endl;
                exit(1);
            }
        } else if (arg == "-par") {
            if (++i < argc) {
                ParseArgument(argv[i], setup.n_particle, "Invalid argument for number of particles (-par).");
            } else {
                std::cerr << "Missing argument for -par option." << std::endl;
                exit(1);
            }
        } else if (arg == "-pl") {
            if (++i < argc) {
                phy.phy_list = argv[i];
            } else {
                std::cerr << "Missing argument for -pl option." << std::endl;
                exit(1);
            }
        } else if (arg == "-sl") {
            if (++i < argc) {
                ParseArgument(argv[i], phy.step_length, "Invalid argument for step length (-sl).");
            } else {
                std::cerr << "Missing argument for -sl option." << std::endl;
                exit(1);
            }
        } else if (arg == "-shield_pos") {
            // Shield position input (expects 3 values for x, y, z)
            if (i + 3 < argc) {
                ParseArgument(argv[++i], shield.pos[0], "Invalid argument for shield X-position (-shield_pos).");
                ParseArgument(argv[++i], shield.pos[1], "Invalid argument for shield Y-position (-shield_pos).");
                ParseArgument(argv[++i], shield.pos[2], "Invalid argument for shield Z-position (-shield_pos).");
                setup.use_shield = true;
            } else {
                std::cerr << "Missing arguments for shield position (-shield_pos)." << std::endl;
                exit(1);
            }
        } else if (arg == "-shield_size") {
            // Shield size input (expects 3 values for x, y, z)
            if (i + 3 < argc) {
                ParseArgument(argv[++i], shield.size[0], "Invalid argument for shield X-size (-shield_size).");
                ParseArgument(argv[++i], shield.size[1], "Invalid argument for shield Y-size (-shield_size).");
                ParseArgument(argv[++i], shield.size[2], "Invalid argument for shield Z-size (-shield_size).");
                setup.use_shield = true;
            } else {
                std::cerr << "Missing arguments for shield size (-shield_size)." << std::endl;
                exit(1);
            }
        } else if (arg == "-shield_mat") {
            // Shield material input
            if (++i < argc) {
                shield.mat = argv[i];  // Store the shield material as a string
                setup.use_shield = true;
            } else {
                std::cerr << "Missing argument for shield material (-shield_mat)." << std::endl;
                exit(1);
            }
        } else if (arg == "-gph") {
            ParseArgument(argv[i], coll.pos[2], "Invalid argument for grid-phantom distance (-gph).");
            setup.use_coll = true;
        } else if (arg == "-sadx") {
            ParseArgument(argv[i], bm.sad[0], "Invalid argument for SADx (-sadx).");
        } else if (arg == "-sady") {
            ParseArgument(argv[i], bm.sad[1], "Invalid argument for SADy (-sady).");
        } else if (arg == "-csx") {
            ParseArgument(argv[i], coll.pos[0], "Invalid argument for collimator X-shift (-csx).");
            setup.use_coll = true;
        } else if (arg == "-csy") {
            ParseArgument(argv[i], coll.pos[1], "Invalid argument for collimator Y-shift (-csy).");
            setup.use_coll = true;
        } else if (arg == "-agx") {
            ParseArgument(argv[i], coll.angle[0], "Invalid argument for collimator X angle (-agx).");
            setup.use_coll = true;
        } else if (arg == "-agy") {
            ParseArgument(argv[i], coll.angle[1], "Invalid argument for collimator Y angle (-agy).");
            setup.use_coll = true;
        } else if (arg == "-agz") {
            ParseArgument(argv[i], coll.angle[2], "Invalid argument for collimator Z angle (-agz).");
            setup.use_coll = true;
        } else if (arg == "-ctc") {
            ParseArgument(argv[i], coll.ctc, "Invalid argument for grid center-to-center distance (-ctc).");
            setup.use_coll = true;
        } else if (arg == "-thk") {
            ParseArgument(argv[i], coll.len[2], "Invalid argument for grid thickness (-thk).");
            setup.use_coll = true;
        } else if (arg == "-tpt") {
            ParseArgument(argv[i], coll.throughput, "Invalid argument for grid throughput (-tpt).");
            setup.use_coll = true;
        } else if (arg == "-mat") {
            coll.mat = std::string(argv[i]);
            setup.use_coll = true;
        } else {
            std::cerr << "Unknown option: " << arg << std::endl;
            std::cerr << "Use -h for help." << std::endl;
            exit(1);
        }
    }
}

void SimulationParameters::AssignSpots() {
    std::ifstream inputFile(bm.planFile);
    if (!inputFile.is_open()) {
        std::cerr << "Error: Unable to open file " << bm.planFile << std::endl;
        exit(0);
    }

    bm.spots.clear();
    std::string line;

    while (std::getline(inputFile, line)) {
        SpotParameter spot;
        std::stringstream ss(line);
        ss >> spot.energy >> spot.e_spread >> spot.spotx >> spot.spoty
           >> spot.sig_x >> spot.sig_y >> spot.div_x >> spot.div_y
           >> spot.cov_x >> spot.cov_y >> spot.weight;

        // Apply multipliers
        spot.energy *= 1000.0;  // Convert to desired unit, e.g., MeV
        spot.e_spread *= 1000.0; // Spread, possibly converting to keV
        spot.spotx *= 10.0;     // Convert to mm
        spot.spoty *= 10.0;     // Convert to mm
        spot.sig_x = (spot.sig_x * 10.0) / 2.355;  // FWHM to sigma conversion
        spot.sig_y = (spot.sig_y * 10.0) / 2.355;
        spot.cov_x *= 10.0;  // Covariance in mm
        spot.cov_y *= 10.0;  // Covariance in mm
        // Add the spot to the vector
        bm.spots.push_back(spot);
    }

    inputFile.close();
    AssignTotal();
    return;
}

void SimulationParameters::AssignTotal() {
    bm.num_spots = bm.spots.size();
    bm.total_weight = 0.0;
    for (size_t i = 0; i < bm.num_spots; i++) {
        bm.total_weight += bm.spots[i].weight;
    }
    return;
}
