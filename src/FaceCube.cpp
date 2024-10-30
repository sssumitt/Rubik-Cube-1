#include "FaceCube.h"
#include <iostream>
// Edge mappings
const FaceCube::EdgeMapping FaceCube::edgeMappings[12] = {
    {U, 5, R, 1},  // UR  0
    {U, 7, F, 1},  // UF  1
    {U, 3, L, 1},  // UL  2
    {U, 1, B, 1},  // UB  3

    {D, 5, R, 7},  // DR  4
    {D, 1, F, 7},  // DF  5
    {D, 3, L, 7},  // DL  6
    {D, 7, B, 7},  // DB  7

    {F, 5, R, 3},  // FR  8
    {F, 3, L, 5},  // FL  9

    {B, 5, L, 3},  // BL 10
    {B, 3, R, 5},  // BR 11
};

 //URF, UFL, ULB, UBR, DFR, DLF, DBL, DRB

// Corner mappings
const FaceCube::CornerMapping FaceCube::cornerMappings[8] = {
    {U, 8, R, 0, F, 2}, // URF  0
    {U, 6, F, 0, L, 2}, // UFL  1
    {U, 0, L, 0, B, 2}, // ULB  2
    {U, 2, B, 0, R, 2}, // UBR  3

    {D, 2, F, 8, R, 6}, // DFR  4

    {D, 0, L, 8, F, 6}, // DLF  5

    {D, 6, B, 8, L, 6}, // DBL  6

    {D, 8, R, 8, B, 6}  // DRB  7
    
};

// Edge colors in solved state
const Color FaceCube::edgeColors[12][2] = {
    {w, r},  // UR
    {w, g},  // UF
    {w, o},  // UL
    {w, b},  // UB

    {y, r},  // DR
    {y, g},  // DF
    {y, o},  // DL
    {y, b},  // DB

    {g, r},  // FR
    {g, o},  // FL

    {b, o},  // BL
    {b, r}   // BR
};

// Corner colors in solved state
const Color FaceCube::cornerColors[8][3] = {
    {w, r, g},  // URF
    {w, g, o},  // UFL
    {w, o, b},  // ULB
    {w, b, r},  // UBR
    {y, g, r},  // DFR

    {y, o, g},  // DLF

    {y, b ,o},  // DBL
    {y, r, b}   // DRB
};

FaceCube::FaceCube() {
    // Initialize facelets to default colors
    for (int face = U; face <= B; ++face) {
        for (int index = 0; index < 9; ++index) {
            facelets[face][index] = static_cast<Color>(face);
        }
    }


}

void FaceCube::updateFacelets(const Cube &cube ) {
    // Reset facelets to default colors
    for (int face = U; face <= B; ++face) {
        for (int index = 0; index < 9; ++index) {
            facelets[face][index] = static_cast<Color>(face);
        }
    }

    // std::cout<< " Entered updateFacelets " << std::endl ;

    // std::cout<<"EdgeP :" ;

    // for(int i = 0 ; i< 12 ; i++)    std::cout << cube.edgePositions[i] << " ";
    // std::cout<<"\n" ;

    // std::cout<<"EdgeO :" ;
    // for(int i = 0 ; i< 12 ; i++)    std::cout << cube.edgeOrientations[i] << " " ;
    // std::cout<<"\n" ;

    // std::cout<<"CornerP :" ;
    //  for(int i = 0 ; i< 8 ; i++)    std::cout << cube.cornerPositions[i] << " ";
    // std::cout<<"\n" ;

    // std::cout<<"CornerO :" ;
    // for(int i = 0 ; i< 8 ; i++)    std::cout << cube.cornerOrientations[i] << " " ;
    // std::cout<<"\n" ;

    // Update edges
    for (int i = 0; i < 12; ++i) {

        int pos = cube.edgePositions[i] ;     // Position where edge i is currently located  
        
       
        char ori = cube.edgeOrientations[i];        // Orientation of edge i 
      

        EdgeMapping mapping = edgeMappings[pos];

        Color color1 = edgeColors[i][0];
        Color color2 = edgeColors[i][1];



        if (ori == '1')
            std::swap(color1, color2);
        

        facelets[mapping.face1][mapping.index1] = color1;
        facelets[mapping.face2][mapping.index2] = color2;

    }

    // Update corners
    for (int i = 0; i < 8; ++i) {
        int pos = cube.cornerPositions[i];         // Position where corner i is currently located
        char ori = cube.cornerOrientations[i];      // Orientation of corner i
        CornerMapping mapping = cornerMappings[pos];

        Color color1 = cornerColors[i][0];
        Color color2 = cornerColors[i][1];
        Color color3 = cornerColors[i][2];

        if (ori == '1') {
            // Rotate colors clockwise
            Color temp = color1;
            color1 = color3;
            color3 = color2;
            color2 = temp;

        } else if (ori == '2') {
            // Rotate colors counter-clockwise
            Color temp = color1;
            color1 = color2;
            color2 = color3;
            color3 = temp;
        }
      
        

        facelets[mapping.face1][mapping.index1] = color1;
        facelets[mapping.face2][mapping.index2] = color2;
        facelets[mapping.face3][mapping.index3] = color3;
    }

}




// Helper function to find edge
std::tuple<int, int> FaceCube::findEdge(Color color1, Color color2) const {
    for (int i = 0; i < EDGE_COUNT; ++i) {
        if ((edgeColors[i][0] == color1 && edgeColors[i][1] == color2)) {
            return std::make_tuple(i, 0); // Position, Orientation 0
        }
        if ((edgeColors[i][0] == color2 && edgeColors[i][1] == color1)) {
            return std::make_tuple(i, 1); // Position, Orientation 1
        }
    }
    throw std::invalid_argument("Edge not found");
}

// Helper function to find corner
std::tuple<int, int> FaceCube::findCorner(Color color1, Color color2, Color color3) const {
    for (int i = 0; i < CORNER_COUNT; ++i) {
        // Check all three possible orientations
        if ((cornerColors[i][0] == color1 && cornerColors[i][1] == color2 && cornerColors[i][2] == color3)) {
            return std::make_tuple(i, 0); // Position, Orientation 0
        }
        if ((cornerColors[i][0] == color2 && cornerColors[i][1] == color3 && cornerColors[i][2] == color1)) {
            return std::make_tuple(i, 1); // Position, Orientation 1
        }
        if ((cornerColors[i][0] == color3 && cornerColors[i][1] == color1 && cornerColors[i][2] == color2)) {
            return std::make_tuple(i, 2); // Position, Orientation 2
        }
    }
    throw std::invalid_argument("Corner not found");
}
Cube FaceCube::getCube() const { 
    Cube cube; 

    // Edge initialization 
    for(int i = 0; i < EDGE_COUNT; i++) {
       EdgeMapping mapping = edgeMappings[i];

        Color color1 = facelets[mapping.face1][mapping.index1];
        Color color2 = facelets[mapping.face2][mapping.index2];
        
        int pos, ori;

        try {
            std::tie(pos, ori) = findEdge(color1, color2);
            cube.edgePositions[i] = pos;
            cube.edgeOrientations[i] = ori;
        }
        catch (const std::invalid_argument& e) {
            throw std::runtime_error("Unsolvable cube: " + std::string(e.what()));
        }
    }

    // Corner initialization
    for(int i = 0; i < CORNER_COUNT; i++) {
        CornerMapping mapping = cornerMappings[i];

        Color color1 = facelets[mapping.face1][mapping.index1];
        Color color2 =  facelets[mapping.face2][mapping.index2];
        Color color3 =  facelets[mapping.face3][mapping.index3];

        int pos, ori;

        try {
            std::tie(pos, ori) = findCorner(color1, color2, color3);
            cube.cornerPositions[i] = pos;
            cube.cornerOrientations[i] = ori;
        }
        catch (const std::invalid_argument& e) {
            throw std::runtime_error("Unsolvable cube: " + std::string(e.what()));
        }
    }

    return cube;
}


std::string FaceCube::colorToString(Color color) const {
    switch (color) {
        case U: return "\033[1;37mW\033[0m"; // White
        case R: return "\033[1;31mR\033[0m"; // Red
        case F: return "\033[1;32mG\033[0m"; // Green
        case D: return "\033[1;33mY\033[0m"; // Yellow
        case L: return "\033[1;35mO\033[0m"; // Orange-purple
        case B: return "\033[1;34mB\033[0m"; // Blue
        default: return "?";
    }
}

std::string FaceCube::getFacelets(const Cube &cube) {
    updateFacelets(cube);
    std::string faceletString;
    for (int face = U; face <= B; ++face) {
        for (int index = 0; index < 9; ++index) {
            faceletString += colorToString(facelets[face][index]);
        }
    }
    return faceletString;
}

void FaceCube::printFacelets(const Cube &cube) {
  
    // Print Up face
    std::cout << "    " << colorToString(facelets[U][0]) << colorToString(facelets[U][1]) << colorToString(facelets[U][2]) << "\n";
    std::cout << "    " << colorToString(facelets[U][3]) << colorToString(facelets[U][4]) << colorToString(facelets[U][5]) << "\n";
    std::cout << "    " << colorToString(facelets[U][6]) << colorToString(facelets[U][7]) << colorToString(facelets[U][8]) << "\n";

    // Print Left, Front, Right, Back faces
    for (int row = 0; row < 3; ++row) {
        std::cout << colorToString(facelets[L][row * 3 + 0]) << colorToString(facelets[L][row * 3 + 1]) << colorToString(facelets[L][row * 3 + 2]) << " ";
        std::cout << colorToString(facelets[F][row * 3 + 0]) << colorToString(facelets[F][row * 3 + 1]) << colorToString(facelets[F][row * 3 + 2]) << " ";
        std::cout << colorToString(facelets[R][row * 3 + 0]) << colorToString(facelets[R][row * 3 + 1]) << colorToString(facelets[R][row * 3 + 2]) << " ";
        std::cout << colorToString(facelets[B][row * 3 + 0]) << colorToString(facelets[B][row * 3 + 1]) <<  colorToString(facelets[B][row * 3 + 2])<< "\n";
    }

    // Print Down face
    std::cout <<"    " << colorToString(facelets[D][0]) << colorToString(facelets[D][1]) << colorToString(facelets[D][2]) << "\n";
    std::cout <<"    " << colorToString(facelets[D][3]) << colorToString(facelets[D][4]) << colorToString(facelets[D][5]) << "\n";
    std::cout <<"    " << colorToString(facelets[D][6]) << colorToString(facelets[D][7]) << colorToString(facelets[D][8]) << "\n";

    std::cout << "\n";

}
