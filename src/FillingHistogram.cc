#include "Analysis.hh"


void Analysis::FillScoringData(ScoredQuantity aSDL){
  auto analysisManager = G4AnalysisManager::Instance();
  SDL = aSDL;
  voxalizedData  = SplitStepIntoVoxels(SDL.CurrentStep,
                                      200,  -50.0*mm,   50.0*mm,
                                      200,  -50.0*mm,   50.0*mm,
                                      300,  -50.0*mm,  100.0*mm,  SDL.EnergyDeposit);

  FillDose1D();
  FillDose2D();
 }

void Analysis::FillKE(){


}

void Analysis::FillDose1D(){
    auto analysisManager = G4AnalysisManager::Instance();
    // std::cout << SDL.GeometryComponent<<"  "<<SDL.EnergyDeposit<<"  "<<SDL.EnergyDeposit/keV<<"  "<< SDL.EnergyDeposit/joule<< "  "<< SDL.MaterialDensity << '\n';
    if (SDL.GeometryComponent == "MouseLegPhysical"){
      analysisManager->FillH1(H1ID_MiceDose, 1, (SDL.EnergyDeposit / joule) / (SDL.MaterialDensity * SDL.GeometryVolume/m3));
      analysisManager->FillH1(H1ID_LetSpectra[0], (SDL.EnergyDeposit/keV) / (SDL.StepLength/um));
      if(SDL.ParticlePDGcode == 2212){
        // std::cout << SDL.EnergyDeposit <<"  "<<(SDL.EnergyDeposit/keV) / (SDL.StepLength/um) << '\n';
        analysisManager->FillH1(H1ID_LetSpectra[1], (SDL.EnergyDeposit/keV) / (SDL.StepLength/um));
        if(SDL.TrackID == 1 && SDL.ParentID == 0)
          analysisManager->FillH1(H1ID_LetSpectra[2], (SDL.EnergyDeposit/keV) / (SDL.StepLength/um));
        else
          analysisManager->FillH1(H1ID_LetSpectra[3], (SDL.EnergyDeposit/keV) / (SDL.StepLength/um));
      }

      else
        analysisManager->FillH1(H1ID_LetSpectra[4], (SDL.EnergyDeposit/keV) / (SDL.StepLength/um));
    }
    return;
}
//
void Analysis::FillDose2D(){
  auto analysisManager = G4AnalysisManager::Instance();
  for (int i = 0; i<voxalizedData.size(); i++){
    if(0<voxalizedData[i].center.z()&&voxalizedData[i].center.z()<5){
        analysisManager->FillH2(H2ID_dose[0], voxalizedData[i].center.x(),
                                              voxalizedData[i].center.y(),
                                              (voxalizedData[i].energyDeposit / joule)/(0.5*0.5*5.0*10e-9));
        if(SDL.ParticlePDGcode == 2212){
            analysisManager->FillH2(H2ID_let[0],  voxalizedData[i].center.x(),
                                                  voxalizedData[i].center.y(),
            (voxalizedData[i].energyDeposit/keV*voxalizedData[i].energyDeposit/keV)/voxalizedData[i].stepLength/um);

            analysisManager->FillH2(H2ID_energy[0], voxalizedData[i].center.x(),
                                                    voxalizedData[i].center.y(),
                                                    voxalizedData[i].energyDeposit/keV);

            analysisManager->FillH2(H2ID_fluence[0], voxalizedData[i].center.x(),
                                                     voxalizedData[i].center.y(),
                                                     voxalizedData[i].stepLength/(0.5*0.5*5.0*10e-9));
        }
    }

    if(-2.5<voxalizedData[i].center.x()&&voxalizedData[i].center.x()<2.5){
      analysisManager->FillH2(H2ID_dose[1],  voxalizedData[i].center.z(),
                                             voxalizedData[i].center.y(),
                                             (voxalizedData[i].energyDeposit / joule)/(0.5*0.5*5.0*10e-9));
      if(SDL.ParticlePDGcode == 2212){
          analysisManager->FillH2(H2ID_let[1], voxalizedData[i].center.z(),
                                               voxalizedData[i].center.y(),
          (voxalizedData[i].energyDeposit/keV*voxalizedData[i].energyDeposit/keV)/voxalizedData[i].stepLength/um);

          analysisManager->FillH2(H2ID_energy[1], voxalizedData[i].center.z(),
                                                  voxalizedData[i].center.y(),
                                                  voxalizedData[i].energyDeposit/keV);

          analysisManager->FillH2(H2ID_fluence[1], voxalizedData[i].center.z(),
                                                   voxalizedData[i].center.y(),
                                                   voxalizedData[i].stepLength/(0.5*0.5*5.0*10e-9));
       }
    }

    if(-12.5<voxalizedData[i].center.y()&&voxalizedData[i].center.y()<7.5){
      analysisManager->FillH2(H2ID_dose[2],  voxalizedData[i].center.z(),
                                             voxalizedData[i].center.x(),
                                             (voxalizedData[i].energyDeposit / joule)/(0.5*0.5*5.0*10e-9));
      if(SDL.ParticlePDGcode == 2212){
          analysisManager->FillH2(H2ID_let[2], voxalizedData[i].center.z(),
                                             voxalizedData[i].center.x(),
          (voxalizedData[i].energyDeposit/keV*voxalizedData[i].energyDeposit/keV)/voxalizedData[i].stepLength/um);


          analysisManager->FillH2(H2ID_energy[2], voxalizedData[i].center.z(),
                                                voxalizedData[i].center.x(),
                                                voxalizedData[i].energyDeposit/keV);

          analysisManager->FillH2(H2ID_fluence[2], voxalizedData[i].center.z(),
                                                 voxalizedData[i].center.x(),
                                                 voxalizedData[i].stepLength/(0.5*20.0*0.5*10e-9));
      }
    }
 }
  return;
}

void Analysis::FillFluence(){
  auto analysisManager = G4AnalysisManager::Instance();
  return;
}

void Analysis::FillLETD(){
  auto analysisManager = G4AnalysisManager::Instance();
  return;
 }

 void Analysis::FillLETF(){
   auto analysisManager = G4AnalysisManager::Instance();
   return;
 }
