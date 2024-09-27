#include "Analysis.hh"
void Analysis::BookHistograms(){
  auto analysisManager = G4AnalysisManager::Instance();
  BookDose1DHisto();
  BookDose2DHisto();

  return;
}
void Analysis::BookParticleTypeHisto(){
  auto analysisManager = G4AnalysisManager::Instance();
}

void Analysis::BookKEHisto(){
  auto analysisManager = G4AnalysisManager::Instance();
  return;
}

void Analysis::BookDose1DHisto(){
  auto analysisManager = G4AnalysisManager::Instance();
  H1ID_MiceDose = analysisManager->CreateH1("DoseMouse",          "DoseMouse",        1, -1,   5);

  H1ID_LetSpectra[0] = analysisManager->CreateH1("ALL_LET",                           "ALL_LET",    200,  0,   5);
  H1ID_LetSpectra[1] = analysisManager->CreateH1("Proton_LET",                     "Proton_LET",    200,  0,   5);
  H1ID_LetSpectra[2] = analysisManager->CreateH1("Primary_Proton_LET",     "Primary_Proton_LET",    200,  0,   5);
  H1ID_LetSpectra[3] = analysisManager->CreateH1("Secondary_Proton_LET", "Secondary_Proton_LET",   2000,  0, 100);
  H1ID_LetSpectra[4] = analysisManager->CreateH1("ALL_Secondaries_LET",   "ALL_Secondaries_LET",   2000,  0, 100);


  return;
}

void Analysis::BookDose2DHisto(){
  auto analysisManager = G4AnalysisManager::Instance();

  H2ID_dose[0] = analysisManager->CreateH2("DoseXY",  "DoseXY",    200,  -50,  50, 200,  -50,  50);
  H2ID_dose[1] = analysisManager->CreateH2("DoseYZ",  "DoseYZ",    300,  -50, 100, 200,  -50,  50);
  H2ID_dose[2] = analysisManager->CreateH2("DoseXZ",  "DoseXZ",    300,  -50, 100, 200,  -50,  50);

  H2ID_let[0] = analysisManager->CreateH2("dLET_XY",  "dLET_XY",    200,  -50,  50, 200, -50,  50);
  H2ID_let[1] = analysisManager->CreateH2("dLET_YZ",  "dLET_YZ",    300,  -50, 100, 200,  -50, 50);
  H2ID_let[2] = analysisManager->CreateH2("dLET_XZ",  "dLET_XZ",    300,  -50, 100, 200,  -50, 50);

  H2ID_energy[0] = analysisManager->CreateH2("EnergyXY",  "EnergyXY",    200,  -50,  50, 200,  -50,  50);
  H2ID_energy[1] = analysisManager->CreateH2("EnergyYZ",  "EnergyYZ",    300,  -50, 100, 200,  -50,  50);
  H2ID_energy[2] = analysisManager->CreateH2("EnergyXZ",  "EnergyXZ",    300,  -50, 100, 200,  -50,  50);

  H2ID_fluence[0] = analysisManager->CreateH2("FluenceXY",  "FluenceXY",    200,  -50,  50, 200,  -50,  50);
  H2ID_fluence[1] = analysisManager->CreateH2("FluenceYZ",  "FluenceYZ",    300,  -50, 100, 200,  -50,  50);
  H2ID_fluence[2] = analysisManager->CreateH2("FluenceXZ",  "FluenceXZ",    300,  -50, 100, 200,  -50,  50);
  return;
}

void Analysis::BookFluenceHisto(){
  auto analysisManager = G4AnalysisManager::Instance();
  return;
}

void Analysis::BookLETdHisto(){
  auto analysisManager = G4AnalysisManager::Instance();
  return;
}

void Analysis::BookLETfHisto(){

}
