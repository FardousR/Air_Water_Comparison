#ifndef RunAction_h
#define RunAction_h 1

#include "G4UserRunAction.hh"
#include "G4Accumulable.hh"
#include "G4Timer.hh"
#include "SimulationParameters.hh"
#include "Analysis.hh"
#include <ctime>
#include <chrono>  // For time tracking

class RunAction : public G4UserRunAction {
public:
    RunAction(SimulationParameters* aSP);
    virtual ~RunAction();

    virtual void BeginOfRunAction(const G4Run*);
    virtual void EndOfRunAction(const G4Run*);
    void RecordEventProcessed();  // To record processed events in EventAction
    G4int GetTotalProcessedEvents();  // Get total number of processed events


private:
    SimulationParameters* SP;
    G4Timer* fTimer;
    G4Accumulable<G4int> fProcessedEvents;  // Accumulable for processed events
    G4int fLastPrintProgress;

    time_t startTime, endTime;  // For start and end time
    std::chrono::time_point<std::chrono::high_resolution_clock> runStartTime, runEndTime;

    void UpdateProgress();
    void PrintProgress();
};

#endif
