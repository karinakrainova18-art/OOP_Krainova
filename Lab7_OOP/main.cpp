#include "include/simulation.h"
#include <iostream>
#include <thread>
#include <chrono>

using namespace std::chrono_literals;

int main() {
    Simulation sim;
    
    std::cout << "Starting simulation..." << std::endl;
    std::cout << "Simulation will run for " << SIMULATION_DURATION_SEC << " seconds." << std::endl;
    std::cout << "Press Ctrl+C to stop early" << std::endl;
    
    sim.start();
    
    std::this_thread::sleep_for(SIMULATION_DURATION_SEC * 1s + 500ms);
    
    sim.stop();
    
    sim.print_survivors();
    
    return 0;
}

