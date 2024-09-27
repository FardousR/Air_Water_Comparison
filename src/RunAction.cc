#include "RunAction.hh"
#include "G4RunManager.hh"
#include "G4Threading.hh"
#include "G4AccumulableManager.hh"
#include "G4MTRunManager.hh"
#include "G4Run.hh"
#include "G4ios.hh"
#include <iomanip>
#include <chrono>

// Constructor
RunAction::RunAction(SimulationParameters* aSP)
    : G4UserRunAction(), SP(aSP), fProcessedEvents(0), fLastPrintProgress(0) {
    // Initialize the Analysis and set simulation parameters
    Analysis* myana = Analysis::GetAnalysis();
    myana->SetSimulationParameters(SP);
    myana->BookHistograms();
    fTimer = new G4Timer();
}

RunAction::~RunAction() {
    delete fTimer;
}

void RunAction::BeginOfRunAction(const G4Run*) {
    // Reset accumulables at the start of the run
    G4AccumulableManager* accumulableManager = G4AccumulableManager::Instance();
    accumulableManager->Reset();

    // Start the timer for progress tracking
    fTimer->Start();
    startTime = time(0);

    // Record start time with high precision
    runStartTime = std::chrono::high_resolution_clock::now();

    // Open analysis output
    Analysis* myana = Analysis::GetAnalysis();
    myana->Open();
}

void RunAction::EndOfRunAction(const G4Run*) {
    // Save and close analysis output
    Analysis* myana = Analysis::GetAnalysis();
    myana->Save();
    myana->Close();

    // Stop the timer and record end time
    fTimer->Stop();
    endTime = time(0);
    runEndTime = std::chrono::high_resolution_clock::now();

    // Calculate total time taken
    G4int threadID = G4Threading::G4GetThreadId();
    if (threadID == 0)
    {
      std::chrono::duration<double> totalTime = runEndTime - runStartTime;
      G4cout << "Run completed in " << totalTime.count() << " seconds." << G4endl;

      // Print time information
      G4cout << "Start time: " << ctime(&startTime);
      G4cout << "End time: " << ctime(&endTime);
      G4cout << "Total time for Simulation: "<< totalTime.count() << '\n';
      G4int numThreads = 1;
      if (G4Threading::IsMultithreadedApplication()) {
        numThreads = G4MTRunManager::GetMasterRunManager()->GetNumberOfThreads();
      }
      // Calculate time per 1000 particles
      G4int totalEvents = G4RunManager::GetRunManager()->GetCurrentRun()->GetNumberOfEventToBeProcessed();
      if (totalEvents > 0) {
          G4double timePer1000Particles = numThreads*(totalTime.count()/totalEvents) * 1000;
          G4cout << "Time per 1000 particles: " << timePer1000Particles << " seconds." << G4endl;
      }
   }
}

void RunAction::RecordEventProcessed() {
    // Safely accumulate the number of processed events
    G4AccumulableManager* accumulableManager = G4AccumulableManager::Instance();
    fProcessedEvents += 1;
    accumulableManager->Merge();

    // Update progress periodically
    UpdateProgress();
}

// Get total number of processed events
G4int RunAction::GetTotalProcessedEvents() {
    return fProcessedEvents.GetValue();
}

void RunAction::UpdateProgress() {
    G4int totalEvents = G4RunManager::GetRunManager()->GetCurrentRun()->GetNumberOfEventToBeProcessed();
    G4int processedEvents = fProcessedEvents.GetValue();  // Get the accumulated value

    // Calculate progress percentage
    G4int progress = (100 * processedEvents) / totalEvents;

    // Print progress every 10% or on the last event
    if (progress >= fLastPrintProgress + 10 || processedEvents == totalEvents) {
        fLastPrintProgress = progress;
        PrintProgress();
    }
}

void RunAction::PrintProgress() {
    G4int totalEvents = G4RunManager::GetRunManager()->GetCurrentRun()->GetNumberOfEventToBeProcessed();
    G4int processedEvents = fProcessedEvents.GetValue();
    G4double timeElapsed = fTimer->GetRealElapsed();  // Time passed in seconds
    G4double timePerEvent = timeElapsed / processedEvents;
    G4double estimatedRemainingTime = timePerEvent * (totalEvents - processedEvents);

    G4cout << std::fixed << std::setprecision(2)
           << "Progress: " << (100 * processedEvents) / totalEvents << "% ("
           << "Processed " << processedEvents << " of " << totalEvents << " events), "
           << "Time elapsed: " << timeElapsed << " s, "
           << "Estimated remaining time: " << estimatedRemainingTime << " s."
           << G4endl;
}
