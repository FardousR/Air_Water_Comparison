#include "SimulationParameters.hh"
#include <iostream>

void SimulationParameters::PrintHelp() {
    std::cout << "Usage: SimulationProgram [options]\n";
    std::cout << "Options:\n";

    // General options
    std::cout << "\nGeneral Options:\n";
    std::cout << "  -h               Show this help message\n";
    std::cout << "  -gui             Enable the graphical user interface (GUI)\n";
    std::cout << "  -b               Enable batch mode\n";
    std::cout << "  -thr <value>     Set the number of threads to use [e.g. -thr 4]\n";
    std::cout << "  -out <file>      Set the output file name [e.g. -out output.root]\n";

    // Phantom and mouse options
    std::cout << "\nPhantom and Mouse Options:\n";
    std::cout << "  -phantom         Place the phantom in the simulation\n";
    std::cout << "  -mouse           Place the mouse in the simulation\n";

    // Collimator options
    std::cout << "\ncollimator and Collimator Options:\n";
    std::cout << "  -collimator            Enable collimator functionality\n";
    std::cout << "  -gph <value>     Set the collimator-phantom distance (in mm) [e.g. -gph 30.0]\n";
    std::cout << "  -csx <value>     Set the collimator X-shift (in mm) [e.g. -csx 20.0]\n";
    std::cout << "  -csy <value>     Set the collimator Y-shift (in mm) [e.g. -csy 10.0]\n";
    std::cout << "  -agx <value>     Set the collimator X-angle (in radians) [e.g. -agx 0.02]\n";
    std::cout << "  -agy <value>     Set the collimator Y-angle (in radians) [e.g. -agy 0.03]\n";
    std::cout << "  -agz <value>     Set the collimator Z-angle (in radians) [e.g. -agz 0.01]\n";
    std::cout << "  -ctc <value>     Set the collimator center-to-center distance (in mm) [e.g. -ctc 2.0]\n";
    std::cout << "  -thk <value>     Set the collimator thickness (in mm) [e.g. -thk 30.0]\n";
    std::cout << "  -tpt <value>     Set the collimator throughput (as a percentage) [e.g. -tpt 50.0]\n";
    std::cout << "  -mat <material>  Set the collimator material [e.g. -mat tungsten]\n";

    // Beam and particle simulation options
    std::cout << "\nBeam and Particle Options:\n";
    std::cout << "  -par <value>     Set the number of particles to simulate [e.g. -par 100000]\n";
    std::cout << "  -sob <file>      Set the SOBP (Spread-Out Bragg Peak) file [e.g. -sob sobp_file.dat]\n";
    std::cout << "  -sadx <value>    Set the source-to-axis distance in X (SADx) (in mm) [e.g. -sadx 50.0]\n";
    std::cout << "  -sady <value>    Set the source-to-axis distance in Y (SADy) (in mm) [e.g. -sady 45.0]\n";

    // PTV (Planned Target Volume) options
    std::cout << "\nPTV Boundary Options:\n";
    std::cout << "  -mipx <value>    Set the minimum PTV boundary in the X direction (in mm) [e.g. -mipx 10.0]\n";
    std::cout << "  -mipy <value>    Set the minimum PTV boundary in the Y direction (in mm) [e.g. -mipy 15.0]\n";
    std::cout << "  -mipz <value>    Set the minimum PTV boundary in the Z direction (in mm) [e.g. -mipz 20.0]\n";
    std::cout << "  -mapx <value>    Set the maximum PTV boundary in the X direction (in mm) [e.g. -mapx 50.0]\n";
    std::cout << "  -mapy <value>    Set the maximum PTV boundary in the Y direction (in mm) [e.g. -mapy 55.0]\n";
    std::cout << "  -mapz <value>    Set the maximum PTV boundary in the Z direction (in mm) [e.g. -mapz 60.0]\n";

    // Histogram and binning options
    std::cout << "\nHistogram and Binning Options:\n";
    std::cout << "  -binx <value>    Set the bin width in the X direction (in mm) [e.g. -binx 5.0]\n";
    std::cout << "  -biny <value>    Set the bin width in the Y direction (in mm) [e.g. -biny 5.0]\n";
    std::cout << "  -binz <value>    Set the bin width in the Z direction (in mm) [e.g. -binz 5.0]\n";

    std::cout << "\nFor more details, refer to the user manual or contact support.\n";
}
