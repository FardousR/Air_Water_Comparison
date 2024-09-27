#include "PrimaryGeneratorAction.hh"
#include "Randomize.hh"

PrimaryGeneratorAction::PrimaryGeneratorAction(SimulationParameters* aSP)
    : G4VUserPrimaryGeneratorAction(), SP(aSP), fParticleGun(nullptr) {

    // Initialize particle gun with one particle
    fParticleGun = new G4ParticleGun(1);

    // Set default particle properties
    G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
    G4String particleName = SP->GetBeam().particle;
    G4ParticleDefinition* particle = particleTable->FindParticle(particleName);
    fParticleGun->SetParticleDefinition(particle);

    // Retrieve beam and SOBP parameters
    total_number_spots = SP->GetBeam().num_spots;;
    total_weight_spots = SP->GetBeam().total_weight;
    SADx = 2560*mm;//SP->GetBeam().sad[0];
    SADy = 2000*mm;//SP->GetBeam().sad[1];
    pos_z = 500.0;
}

PrimaryGeneratorAction::~PrimaryGeneratorAction() {
    delete fParticleGun;
}

G4int PrimaryGeneratorAction::spot_selector() {
    G4double spot_weight = G4UniformRand() * total_weight_spots;
    G4double cumulative_weight = 0;

    for (G4int i = 0; i < total_number_spots; ++i) {
        cumulative_weight += SP->GetBeam().spots[i].weight;
        if (spot_weight < cumulative_weight) {
            return i;
        }
    }
    return total_number_spots - 1;  // Return last spot in case of rounding errors
}

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent) {
    // Get the selected spot from the beam
    spot = SP->GetBeam().spots[spot_selector()];

    // Generate particle energy based on the selected spot's energy and spread
    G4double energy = G4RandGauss::shoot(spot.energy, spot.e_spread);

    // Calculate position and direction of the spot
    G4double spot_x_pos = spot.spotx * ((SADx - 500) / SADx);
    G4double spot_y_pos = spot.spoty * ((SADy - 500) / SADy);
    G4double spot_x_dir = atan(spot.spotx / SADx);
    G4double spot_y_dir = atan(spot.spoty / SADy);

    multivariateGaussian(spot_x_pos, spot_x_dir, spot.sig_x, spot.div_x, -spot.cov_x, pos_x, dir_x);
    multivariateGaussian(spot_y_pos, spot_y_dir, spot.sig_y, spot.div_y, -spot.cov_y, pos_y, dir_y);

    dir_z = 1.0;  // Ensure particles move along the Z-axis

    // Set particle properties for the event
    fParticleGun->SetParticleEnergy(energy * MeV);
    fParticleGun->SetParticlePosition(G4ThreeVector(pos_x*mm, pos_y*mm, -pos_z*mm));
    fParticleGun->SetParticleMomentumDirection(G4ThreeVector(dir_x, dir_y, dir_z));
    fParticleGun->GeneratePrimaryVertex(anEvent);
}

void PrimaryGeneratorAction::multivariateGaussian(double mean_x, double mean_y, double sigma_x, double sigma_y, double cov_xy, double& x, double& y) {
    double z1 = G4RandGauss::shoot(0.0, 1.0);
    double z2 = G4RandGauss::shoot(0.0, 1.0);

    // Covariance matrix
    double cov_matrix[2][2] = {{sigma_x * sigma_x, cov_xy}, {cov_xy, sigma_y * sigma_y}};

    // Cholesky decomposition
    double MLH[2][2] = {{0}};
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j <= i; ++j) {
            double sum = 0;
            for (int k = 0; k < j; ++k) {
                sum += MLH[i][k] * MLH[j][k];
            }
            if (i == j) {
                MLH[i][j] = sqrt(cov_matrix[i][j] - sum);
            } else {
                MLH[i][j] = (cov_matrix[i][j] - sum) / MLH[j][j];
            }
        }
    }

    // Generate correlated Gaussian variables
    x = mean_x + MLH[0][0] * z1 + MLH[0][1] * z2;
    y = mean_y + MLH[1][0] * z1 + MLH[1][1] * z2;
}
