#ifndef EVENTACTION_HH
#define EVENTACTION_HH

#include "G4UserEventAction.hh"
#include "SimulationParameters.hh"
#include "G4Timer.hh"
#include "G4Accumulable.hh"
#include "G4AccumulableManager.hh"

class EventAction : public G4UserEventAction {
public:
    EventAction(SimulationParameters* aSP);
    virtual ~EventAction();

    virtual void BeginOfEventAction(const G4Event*);
    virtual void EndOfEventAction(const G4Event*);

private:
    SimulationParameters* SP;
    G4Timer* fTimer;
    G4int fLastPrintProgress;

    std::map<G4int, G4Timer> fThreadTimers;  // Timers for each thread
    G4Accumulable<G4double> fAccumulatedTime;  // Accumulate time from all threads

    void PrintProgress(const G4Event* event);
};

#endif
