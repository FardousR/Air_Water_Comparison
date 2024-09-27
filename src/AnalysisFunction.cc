#include "Analysis.hh"
#include "G4Step.hh"
#include "G4ThreeVector.hh"
#include <vector>
#include <cmath>

// Function to split the step into voxel segments
std::vector<VoxelSegment> Analysis::SplitStepIntoVoxels(
    const G4Step* step,
    G4int nBinsX, G4double minX, G4double maxX,
    G4int nBinsY, G4double minY, G4double maxY,
    G4int nBinsZ, G4double minZ, G4double maxZ,
    G4double totalEnergyDeposit)
{
    std::vector<VoxelSegment> segments;

    // Calculate voxel sizes
    G4double voxelSizeX = (maxX - minX) / nBinsX;
    G4double voxelSizeY = (maxY - minY) / nBinsY;
    G4double voxelSizeZ = (maxZ - minZ) / nBinsZ;

    // Get pre and post step points
    G4ThreeVector prePosition = step->GetPreStepPoint()->GetPosition();
    G4ThreeVector postPosition = step->GetPostStepPoint()->GetPosition();

    // // Clamp prePosition within bounds
    // prePosition.setX(std::max(minX, std::min(prePosition.x(), maxX)));
    // prePosition.setY(std::max(minY, std::min(prePosition.y(), maxY)));
    // prePosition.setZ(std::max(minZ, std::min(prePosition.z(), maxZ)));
    //
    // // Clamp postPosition within bounds (optional, depending on your needs)
    // postPosition.setX(std::max(minX, std::min(postPosition.x(), maxX)));
    // postPosition.setY(std::max(minY, std::min(postPosition.y(), maxY)));
    // postPosition.setZ(std::max(minZ, std::min(postPosition.z(), maxZ)));

    // Total step length
    G4double totalStepLength = (postPosition - prePosition).mag();

    // Determine voxel indices for pre and post step points
    G4double epsilon = 1e-6; // Small margin for floating-point precision
    G4int preVoxelX = std::floor((prePosition.x() - minX + epsilon) / voxelSizeX);
    G4int preVoxelY = std::floor((prePosition.y() - minY + epsilon) / voxelSizeY);
    G4int preVoxelZ = std::floor((prePosition.z() - minZ + epsilon) / voxelSizeZ);

    G4int postVoxelX = std::floor((postPosition.x() - minX + epsilon) / voxelSizeX);
    G4int postVoxelY = std::floor((postPosition.y() - minY + epsilon) / voxelSizeY);
    G4int postVoxelZ = std::floor((postPosition.z() - minZ + epsilon) / voxelSizeZ);

    // std::cout << preVoxelZ<<"  "<< prePosition.z()  << '\n';

    // If the particle stays in the same voxel, handle it directly
    if (preVoxelX == postVoxelX && preVoxelY == postVoxelY && preVoxelZ == postVoxelZ) {
        if (preVoxelX >= 0 && preVoxelX < nBinsX &&
            preVoxelY >= 0 && preVoxelY < nBinsY &&
            preVoxelZ >= 0 && preVoxelZ < nBinsZ) {
            VoxelSegment segment;
            segment.center = G4ThreeVector((preVoxelX + 0.5) * voxelSizeX + minX,
                                           (preVoxelY + 0.5) * voxelSizeY + minY,
                                           (preVoxelZ + 0.5) * voxelSizeZ + minZ);
            segment.stepLength = totalStepLength;
            segment.energyDeposit = totalEnergyDeposit;
            segments.push_back(segment);
        }
    } else {
        // Handle multi-voxel steps
        G4ThreeVector currentPosition = prePosition;
        G4double remainingLength = totalStepLength;
        G4ThreeVector stepDirection = (postPosition - prePosition).unit();

        while (remainingLength > 0) {
            // Compute the next boundary for each axis
            G4double nextBoundaryX = (stepDirection.x() > 0) ?
                voxelSizeX * (preVoxelX + 1) + minX :
                voxelSizeX * preVoxelX + minX;

            G4double nextBoundaryY = (stepDirection.y() > 0) ?
                voxelSizeY * (preVoxelY + 1) + minY :
                voxelSizeY * preVoxelY + minY;

            G4double nextBoundaryZ = (stepDirection.z() > 0) ?
                voxelSizeZ * (preVoxelZ + 1) + minZ :
                voxelSizeZ * preVoxelZ + minZ;

            // Compute distances to the next voxel boundaries along each axis
            G4double tX = std::abs((nextBoundaryX - currentPosition.x()) / stepDirection.x());
            G4double tY = std::abs((nextBoundaryY - currentPosition.y()) / stepDirection.y());
            G4double tZ = std::abs((nextBoundaryZ - currentPosition.z()) / stepDirection.z());

            // Find the minimum time to reach the next boundary (smallest t)
            G4double tMin = std::min({tX, tY, tZ});

            // Calculate the actual step length based on this minimum time
            G4double stepLength = tMin * stepDirection.mag();

            // Cap the step length if it exceeds the remaining length
            if (stepLength > remainingLength) {
                stepLength = remainingLength;
            }

            // Check if the voxel indices are still within bounds
            if (preVoxelX < 0 || preVoxelX >= nBinsX ||
                preVoxelY < 0 || preVoxelY >= nBinsY ||
                preVoxelZ < 0 || preVoxelZ >= nBinsZ) {
                break; // Exit the loop if the particle is outside the boundaries
            }

            // Calculate energy deposit fraction for this segment
            G4double energyDeposit = totalEnergyDeposit * (stepLength / totalStepLength);

            // Compute the center of the current voxel
            G4ThreeVector voxelCenter((preVoxelX + 0.5) * voxelSizeX + minX,
                                      (preVoxelY + 0.5) * voxelSizeY + minY,
                                      (preVoxelZ + 0.5) * voxelSizeZ + minZ);

            // Store the segment info
            VoxelSegment segment;
            segment.center = voxelCenter;
            segment.stepLength = stepLength;
            segment.energyDeposit = energyDeposit;
            segments.push_back(segment);

            // Move to the next position and update the remaining length
            currentPosition += stepDirection * stepLength;
            remainingLength -= stepLength;

            // Update voxel indices based on the direction and distance moved
            if (tMin == tX) {
                preVoxelX += (stepDirection.x() > 0) ? 1 : -1;
            }
            if (tMin == tY) {
                preVoxelY += (stepDirection.y() > 0) ? 1 : -1;
            }
            if (tMin == tZ) {
                preVoxelZ += (stepDirection.z() > 0) ? 1 : -1;
            }
        }
    }

    return segments;
}



void Analysis::FindCTCcenter() {
    // Get the min and max range from PTV
    G4double min = SP->GetPTV().yRange[0];
    G4double max = SP->GetPTV().yRange[1];

    // Clear any previous data in the vectors
    pos_peaks.clear();
    pos_valleys.clear();

    // Get the peak centers from the collimator
    std::vector<G4double> peakCenters = SP->GetCollimator().peakCenters;
    for (G4double num : peakCenters) {
        if (num >= min && num <= max) {  // Check if the number is in the range
            pos_peaks.push_back(num);    // Add it to the pos_peaks vector
        }
    }

    // Get the valley centers from the collimator
    std::vector<G4double> valleyCenters = SP->GetCollimator().valleyCenters;
    for (G4double num : valleyCenters) {
        if (num >= min && num <= max) {  // Check if the number is in the range
            pos_valleys.push_back(num);  // Add it to the pos_valleys vector
        }
    }
    return;
}


G4double Analysis::GetParticleID(G4int PDG)
{
    // Map PDG codes to specific particleID values
    switch (PDG)
    {
        case 2212: // Proton
            return isPrimary(ParentID, TrackID) ? 0.5 : 1.5;

        case -11: // Electron
            return 2.5;

        case 2112: // Neutron
            return 3.5;

        case 1000020040: // Alpha particle (Helium-4 nucleus)
            return 4.5;

        case 0: // Undefined or unknown particle
            return 5.5;

        default:
            if (PDG > 1000020040)
                return 6.5; // Heavy ions
            else
                return -55; // Unknown particle ID
    }
}

G4bool Analysis::isPrimary(G4int parentID, G4int trackID)
{
    // If the particle has no parent (parentID == 0) and it's the
    // first track (trackID == 1), it's a primary particle
    if (parentID == 0 && trackID == 1) {
        return true;
    }
    return false;
}


G4double Analysis::GetNeuKermaFactor(G4double energy)
{
    // Ensure that we have valid neutron energy data
    if (n_data < 2)
        return 0;  // Return 0 if there isn't enough data for interpolation

    // Loop through neutron energy data to find the correct range
    for (int i = 0; i < n_data - 1; ++i)
    {
        if (neutron_energy[i] <= energy && energy < neutron_energy[i + 1])
        {
            // Perform linear interpolation between the two data points
            G4double delta_energy = neutron_energy[i + 1] - neutron_energy[i];
            G4double delta_factor = f_water[i + 1] - f_water[i];

            return f_water[i] + (delta_factor / delta_energy) * (energy - neutron_energy[i]);
        }
    }

    // Return 0 if the energy is out of the interpolation range
    return 0;
}
