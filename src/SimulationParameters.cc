#include "SimulationParameters.hh"
#include <stdexcept>

SimulationParameters::SimulationParameters(int argc, char** argv) {
    AssignDefaultParameters();
    Initialization(argc, argv);
    AssignSpots();
}

SimulationParameters::~SimulationParameters() {

}
