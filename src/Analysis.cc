#include "Analysis.hh"

G4ThreadLocal Analysis *the_analysis = 0;

Analysis::Analysis(){}
Analysis *Analysis::GetAnalysis() {
      if (!the_analysis) {
          the_analysis = new Analysis();
          G4AutoDelete::Register(the_analysis);
      }
  return the_analysis;
}


void Analysis::Open(){
  auto analysisManager = G4AnalysisManager::Instance();
  analysisManager->OpenFile(SP->GetSetup().out_file);
}

void Analysis::Save() {
  auto analysisManager = G4AnalysisManager::Instance();
  analysisManager->SetFileName(SP->GetSetup().out_file);
  analysisManager->Write();
}

void Analysis::Close() {
  auto analysisManager = G4AnalysisManager::Instance();
  analysisManager->CloseFile();
}
