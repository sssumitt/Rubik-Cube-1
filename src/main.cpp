#include "MoveTable.h"
#include "PruningTable.h"
#include "FaceCube.h"
#include "Search.h"
#include <iostream>
#include <string>

int main() {

    //scramble cube 
    Cube c ;
    c.applyMove("L' U D' U R L2 D' U' R2 U2 L R' U2 L2 D U R U L L2 D' U R U2 L2 D' U2 R'");

    FaceCube fc ; 
    fc.updateFacelets(c);
  
    std::string scrambledCubeStr =  fc.getFacelets(c); // Replace with an actual scrambled cube state

  
    // Create a Search object with the scrambled cube
    Search search(scrambledCubeStr);

    // Set maximum depth and timeout
    int maxDepth = 25;      // Maximum search depth
    long timeOut = 1000;       // Timeout in seconds
    int useSeparator = 0;   // Use separator in solution output (e.g., between phase 1 and phase 2 moves)

    // Perform the search to solve the cube
    std::string solution = search.ida_star_phase1(maxDepth, timeOut, useSeparator);

    // Output the solution
    if (!solution.empty()) {
        std::cout << "Solution: " << solution << std::endl;
    } else {
        std::cout << "No solution found within the given time and depth limits." << std::endl;
    }

    return 0;
}

