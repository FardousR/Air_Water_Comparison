#ifndef Analysis_h
#define Analysis_h 1

#include "SimulationParameters.hh"
#include "G4ThreeVector.hh"
#include "G4String.hh"
#include "G4DynamicParticle.hh"
#include "DataType.hh"
#include <set>
#include "G4AutoDelete.hh"
#include "G4SystemOfUnits.hh"
#include "G4EventManager.hh"
#include "NeutronKerma.hh"
#include <cmath>


// #include "g4root.hh"
#include "G4AnalysisManager.hh"

#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
  TypeName(const TypeName&);               \
  void operator=(const TypeName&)

class Analysis
{
 public:
   Analysis(SimulationParameters* aSP){SP  = aSP;};
  ~Analysis() {};

   static Analysis *GetAnalysis();
   void BookHistograms();
   void SetHistogramInfo();
   void Open();
   void Save();
   void Close();
   void FillScoringData(ScoredQuantity aSDL);
   void AssignData();
   void CountParticles();
   void FillDose1D();
   void FillDose2D();
   void FillKE();
   void FillFluence();
   void FillLETD();
   void FillLETF();
   void FindCTCcenter();

   G4bool inPTV(G4double x, G4double y, G4double z);
   G4bool inPTVX(G4double x);
   G4bool inPTVY(G4double y);
   G4bool inPTVZ(G4double z);
   G4bool inPeak(G4double y, G4double spread);
   G4bool inValley(G4double y, G4double spread);
   G4bool inCollimator(G4double x, G4double y, G4double z);
   G4bool inScoringVolume(G4double x, G4double y, G4double z);
   G4bool isPrimary(G4int parentID, G4int trackID);
   std::vector<VoxelSegment> SplitStepIntoVoxels(
       const G4Step* step,
        G4int nBinsX, G4double minX, G4double maxX,
        G4int nBinsY, G4double minY, G4double maxY,
        G4int nBinsZ, G4double minZ, G4double maxZ,
        G4double totalEnergyDeposit);

   G4double GetParticleID(G4int PGD);
   void SetSimulationParameters(SimulationParameters* aSP){SP  = aSP;};
   SimulationParameters* GetSimulationParameters(){return SP;};

   G4double GetNeuKermaFactor(G4double energy);
   void BookParticleTypeHisto();
   void BookKEHisto();
   void BookDose1DHisto();
   void BookDose2DHisto();
   void BookFluenceHisto();
   void BookLETdHisto();
   void BookLETfHisto();

 private:
   Analysis();
   DISALLOW_COPY_AND_ASSIGN(Analysis);
   G4String ParticleName;
   G4int PDGcode, ParentID, TrackID;
   G4String ProcessName;
   G4ProcessType ProcessType;
   G4int ProcessSubType;
   G4double CenterCTC;
   std::vector<double> pos_peaks;
   std::vector<double> pos_valleys;
   SimulationParameters* SP;
   ScoredQuantity SDL;
   std::vector<VoxelSegment> voxalizedData;

   G4int H2ID_dose[3],H2ID_fluence[3], H2ID_let[3], H2ID_energy[3];
   G4int H1ID_MiceDose, H1ID_LetSpectra[5], H1ID_LetSpectraCal[5]; 
};
#endif
