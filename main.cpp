// main.cpp file 


#include "particle.h"
#include "detector.h"

#include<iostream>
#include<string>
#include<vector>
#include<cmath>

int main()
  {
    // Create a test vector of 8 particles
    std::vector<particle> particles;
    
    // adding particles to vector (2 electrons, 4 muons, 1 anti-electron and 1 anti-muon)
    particles.push_back(particle("electron", 0.511, -1, 5, 3, 5, 9));
    particles.push_back(particle("electron", 0.511, -1, 4.7, 3, 5, 9));
    particles.push_back(particle("muon", 106, -1, 4.7, 3, 5, 9));
    particles.push_back(particle("muon", 106, -1, 4.7, 3, 5, 9));
    particles.push_back(particle("muon", 106, -1, 4.7, 3, 5, 9));
    particles.push_back(particle("muon", 106, -1, 4.7, 3, 5, 9));
    particles.push_back(particle("antimuon", 106, 1, 4.7, 3, 5, 9));
    particles.push_back(particle("antielectron", 0.511, 1, 4.7, 3, 5, 9));

    std::vector<particle>::const_iterator i;

    // Print data for each particle using an iterator
    for(i = particles.begin(); i != particles.end(); ++i)
      {
        i->print_data();
      }

    // Create detectors
    detector tracker("Tracker", false, 0);
    detector calorimeter("Calorimeter", false, 0);
    detector muonChamber("Muon Chamber", false, 0);

    // Turn on detectors
    tracker.turn_on();
    calorimeter.turn_on();
    muonChamber.turn_on();

    // Iterate over the vector of particles
    for(const auto &p : particles)
      {
        // Pass the particle through each detector
        tracker.detect_particle(p);
        calorimeter.detect_particle(p);
        muonChamber.detect_particle(p);
      }

    // Print detection summary for each detector
    tracker.print_detection_summary();
    calorimeter.print_detection_summary();
    muonChamber.print_detection_summary();

    // Add the four-momentum of the first two particles
    if (particles.size() >= 2) 
      {
        particle sum_particle = particles[0] + particles[1];
        std::cout << "Summed electron Four Momenta:" << std::endl;
        std::cout << "E/c: " << sum_particle.get_E() << ", p_x: " << sum_particle.get_p_x() << ", p_y: " << sum_particle.get_p_y() << ", p_z: " << sum_particle.get_p_z() << std::endl;
      } 
    else 
      {
        std::cerr << "Error: There are not enough particles in the vector to perform addition." << std::endl;
        // Handle the error appropriately
      }

    // Calculate the dot product of the third and fourth particles
    if (particles.size() >= 4) 
      {
        double dot_product_result = particles[2] * particles[3];
        std::cout << "Dot product of the two muon four momenta: " << dot_product_result << std::endl;
      }

    // Assignment operator implementation 
    if (particles.size() >= 2) 
      {
        particle new_electron;
        new_electron = particles[0]; // Assign the first electron to a new electron 
        std::cout << "Now copy values of electron 1 to new electron by assignment. " << std::endl;
      }

    // copy constructor implementation
    if (particles.size() >= 3) 
      {
        particle new_muon = particles[2]; // Use copy constructor to copy the first muon to a new muon
        std::cout << "copy constructor of first muon to a new muon." << std::endl;
      }
    // move constructor implementation 
    if (particles.size() >= 8) 
      {
        particle new_antielectron = std::move(particles[7]); // Move the antielectron to a new antielectron object
        std::cout << "Moved antielectron to a new antielectron by move constructor." << std::endl;
      }

    // move assingment operator implementation
    if (particles.size() >= 8) 
      { 
        particle new_antimuon;
        new_antimuon = std::move(particles[6]); // Move assignment of the antimuon to a new antimuon
        std::cout << "Moved antimuon to a new antimuon by move assignment operator." << std::endl;
      }
  }
