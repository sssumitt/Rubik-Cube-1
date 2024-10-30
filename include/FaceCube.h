#ifndef FACECUBE_H
#define FACECUBE_H

#include "Edge.h"
#include "Cube.h"
#include "Corner.h"
#include "Color.h"
#include "Move.h"
#include "Face.h"

#include <array>
#include <string>

// Forward declaration
class Cube;

class FaceCube {
public:
    FaceCube();

    // Update the facelets of the cube based on the current state of the cube
    void updateFacelets(const Cube &cube);

    Cube getCube()const ;  

    // Get the current state of the cube as a string
    std::string getFacelets(const Cube &cube);

    std::string colorToString(Color color) const;

    // Print the facelets of the cube
    void printFacelets(const Cube &cube);

private:
    std::array<std::array<Color, 9>, 6> facelets; // 6 faces, each with 9 facelets

    struct EdgeMapping {
        Face face1; int index1;
        Face face2; int index2;
    };

    struct CornerMapping {
        Face face1; int index1;
        Face face2; int index2;
        Face face3; int index3;
    };

    std::tuple<int, int> findEdge(Color color1, Color color2) const;
    std::tuple<int, int> findCorner(Color color1, Color color2, Color color3) const;

    // Mappings from positions to facelets
    static const EdgeMapping edgeMappings[12];
    static const CornerMapping cornerMappings[8];

    // Edge and corner colors in solved state
    static const Color edgeColors[12][2];
    static const Color cornerColors[8][3];
};

#endif // FACECUBE_H
