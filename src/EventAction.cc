#include "EventAction.hh"
#include "SimulationParameters.hh"
#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4Run.hh"  // Add this to ensure G4Run is fully defined
#include "G4ios.hh"
#include "G4Threading.hh"
#include <chrono>
#include <ctime>
#include <iomanip>  // For formatting the output

// Constructor
EventAction::EventAction(SimulationParameters* aSP)
    : SP(aSP), fTimer(nullptr), fLastPrintProgress(0), fAccumulatedTime(0.0) {
    fTimer = new G4Timer();  // Initialize the timer
    fTimer->Start();         // Start the timer

    // Register the accumulable for thread-safe accumulation
    G4AccumulableManager::Instance()->RegisterAccumulable(fAccumulatedTime);
}
// Destructor
EventAction::~EventAction() {
    delete fTimer;
}

// Begin of event (not used for progress in this case)
void EventAction::BeginOfEventAction(const G4Event* /*event*/) {
    // Add any logic needed before the event starts
}

// End of event (where we print progress information)
void EventAction::EndOfEventAction(const G4Event* event) {
    // Print the progress after each event
    PrintProgress(event);
}

// Progress printing function
void EventAction::PrintProgress(const G4Event* event) {
    G4int threadID = G4Threading::G4GetThreadId();
    if (threadID == 0) {
        G4int eventID = event->GetEventID();  // Current event number
        G4int totalEvents = G4RunManager::GetRunManager()->GetCurrentRun()->GetNumberOfEventToBeProcessed();

        // Calculate progress percentage
        int progress = (100 * (eventID + 1)) / totalEvents;

        // Check if progress has advanced by 2% or more since last print
        if (progress >= fLastPrintProgress + 5 || eventID == totalEvents - 1) {
            fLastPrintProgress = progress;

            // Calculate elapsed time
            fTimer->Stop();
            G4double timeElapsed = fTimer->GetRealElapsed();  // Time passed in seconds
            fTimer->Start();  // Restart the timer

            // Estimate remaining time
            G4double timePerEvent = timeElapsed / (eventID + 1);  // Average time per event
            G4double estimatedTimeRemaining = timePerEvent * (totalEvents - eventID - 1);

            // Get the current system time and format it
            auto currentTime = std::chrono::system_clock::now();
            std::time_t currentTimeC = std::chrono::system_clock::to_time_t(currentTime);
            std::tm* currentTimeLocal = std::localtime(&currentTimeC);

            // Calculate the estimated finish time
            auto estimatedFinishTime = currentTime + std::chrono::seconds(static_cast<int>(estimatedTimeRemaining));
            std::time_t estimatedFinishTimeC = std::chrono::system_clock::to_time_t(estimatedFinishTime);
            std::tm* estimatedFinishTimeLocal = std::localtime(&estimatedFinishTimeC);

            // Print progress along with the current time and estimated finish time
            G4cout << std::fixed << std::setprecision(2)
                   << "Progress: " << progress << "% ("
                   << "Event " << eventID + 1 << " of " << totalEvents << "), "
                   << "Time elapsed: " << timeElapsed << " s, "
                   << "Estimated remaining time: " << estimatedTimeRemaining << " s, "
                   << "Current time: " << std::put_time(currentTimeLocal, "%H:%M:%S") << ", "
                   << "Estimated finish time: " << std::put_time(estimatedFinishTimeLocal, "%H:%M:%S")
                   << G4endl;
        }
    }
}
