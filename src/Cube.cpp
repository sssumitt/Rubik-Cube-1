#include <iostream>
#include <sstream>
#include <unordered_map>
#include <array>

#include "Cube.h"
#include "Edge.h"
#include "Corner.h"
// Define the permutation and orientation for each move

std::unordered_map<Move, std::string> moveToStringMap = {
    {Move::U, "U"},     {Move::U_PRIME, "U'"}, {Move::U2, "U2"},
    {Move::D, "D"},     {Move::D_PRIME, "D'"}, {Move::D2, "D2"},
    {Move::F, "F"},     {Move::F_PRIME, "F'"}, {Move::F2, "F2"},
    {Move::B, "B"},     {Move::B_PRIME, "B'"}, {Move::B2, "B2"},
    {Move::L, "L"},     {Move::L_PRIME, "L'"}, {Move::L2, "L2"},
    {Move::R, "R"},     {Move::R_PRIME, "R'"}, {Move::R2, "R2"}
};

Cube::Cube() {
    // Initialize edge positions and orientations
    for (int i = UR; i <= BR; i++) {
        edgePositions[i] = static_cast<Edge>(i);
        edgeOrientations[i] = '0';
    }
    // Initialize corner positions and orientations
    for (int i = URF; i <= DRB; i++) {
        cornerPositions[i] = static_cast<Corner>(i);
        cornerOrientations[i] = '0';
    }


}

void Cube::applyMove(const std::string& move) {
    std::istringstream iss(move);
    std::string singleMove;
    while (iss >> singleMove) {
        rotateFace(singleMove);
    }
}

bool Cube::isSolved() const {
    // Check if all edges and corners are in their original positions and orientations
    for (int i = 0; i < 12; ++i) {
        if (edgePositions[i] != i || edgeOrientations[i] != 0) {
            return false;
        }
    }
    for (int i = 0; i < 8; ++i) {
        if (cornerPositions[i] != i || cornerOrientations[i] != 0) {
            return false;
        }
    }
    return true;
}

std::string Cube::moveToString(Move move) const{
    auto it = moveToStringMap.find(move);
    if (it != moveToStringMap.end()) {
        return it->second;
    }
    return "Invalid Move";
}

void Cube::rotateFace(const std::string& move) {
    // Parse the move
    bool inverse = false;
    int turns = 1;
    std::string face = move;

    if (move.length() > 1) {
        if (move[1] == '\'') {
            inverse = true;
            face = move.substr(0, 1);
        } else if (move[1] == '2') {
            turns = 2;
            face = move.substr(0, 1);
        }
    }
 
   switch (face[0]) {
        case 'U':
            rotateEdges({UR, UF, UL, UB}, inverse);
            rotateCorners({URF, UFL, ULB, UBR}, inverse);
            if(turns == 2) {
                rotateEdges({UR, UF, UL, UB}, inverse);
                rotateCorners({URF, UFL, ULB, UBR}, inverse);
            }
            // U moves do not affect orientations
            break;
        case 'D':
            rotateEdges({DR, DF, DL, DB}, inverse);
            rotateCorners({DFR, DLF, DBL, DRB}, inverse);
            if(turns == 2) {
                rotateEdges({DR, DF, DL, DB}, inverse);
                rotateCorners({DFR, DLF, DBL, DRB}, inverse);
            }
            // D moves do not affect orientations
            break;
        case 'F':
            if(turns == 2) {
                rotateEdges({UF, FR, DF, FL}, inverse);
                rotateCorners({UFL ,URF, DFR, DLF}, inverse);

                rotateEdges({UF, FR, DF, FL}, inverse);
                rotateCorners({UFL ,URF, DFR, DLF}, inverse);
                
                break;
            }else {
                rotateEdges({UF, FR, DF, FL}, inverse);        // Corrected edge order
                rotateCorners({UFL ,URF, DFR, DLF}, inverse);  // Corrected corner order
                // Update edge orientations for F move
                for (int idx : {UF, FR, DF, FL}) {             // Corrected edge indices
                    edgeOrientations[idx] ^= 1;                // Flip edge orientation
                }
                // Update corner orientations for F move

                cornerOrientations[UFL] = ((cornerOrientations[UFL] - '0' +  1) % 3)+ '0';
                cornerOrientations[URF] = ((cornerOrientations[URF] - '0' +  2) % 3)+ '0';
                cornerOrientations[DFR] = ((cornerOrientations[DFR] - '0' +  1) % 3)+ '0';
                cornerOrientations[DLF] = ((cornerOrientations[DLF] - '0' +  2) % 3)+ '0';
            }
            
            break;
        case 'B':
            if(turns == 2) {
                rotateEdges({UB, BR, DB ,BL}, inverse);
                rotateCorners({ULB, UBR , DRB, DBL}, inverse);
                rotateEdges({UB, BR, DB ,BL}, inverse);
                rotateCorners({ULB, UBR , DRB, DBL}, inverse);
            }
            else {
                rotateEdges({UB, BR, DB ,BL}, inverse);
                rotateCorners({ULB, UBR , DRB, DBL}, inverse);

                // Update edge orientations for B move
                for (int idx : {UB, BR, DB ,BL}) {
                    edgeOrientations[idx] ^= 1;  // Flip edge orientation
                }

                // Update corner orientations for B move
                cornerOrientations[ULB] = ((cornerOrientations[ULB] - '0' +  2) % 3) + '0';
                cornerOrientations[UBR] = ((cornerOrientations[UBR] - '0' +  1) % 3) + '0';
                cornerOrientations[DRB] = ((cornerOrientations[DRB] - '0' +  2) % 3) + '0';
                cornerOrientations[DBL] = ((cornerOrientations[DBL] - '0' +  1) % 3) + '0';

            }
        
            break;
        case 'L':
            if(turns == 2 ) {
    
                rotateEdges({FL,DL,BL,UL}, inverse);
                rotateCorners({UFL, DLF, DBL, ULB}, inverse);
                
                rotateEdges({FL,DL,BL,UL}, inverse);
                rotateCorners({UFL, DLF, DBL, ULB}, inverse);

            }

            else {
                rotateEdges({FL,DL,BL,UL}, inverse);
                rotateCorners({UFL, DLF, DBL, ULB}, inverse);

                // Update corner orientations for L move
                cornerOrientations[UFL] = ((cornerOrientations[UFL]  - '0'+  2) % 3) + '0';  //dlf 
                cornerOrientations[DLF] = ((cornerOrientations[DLF]  - '0'+  1) % 3) + '0';  //dbl
                cornerOrientations[DBL] = ((cornerOrientations[DBL]  - '0'+  2) % 3) + '0';  //ulb
                cornerOrientations[ULB] = ((cornerOrientations[ULB]  - '0'+  1) % 3) + '0';  //ufl
            }
                
            break;
        case 'R':
            if(turns == 2 ) {
                rotateEdges({FR, DR, BR, UR}, inverse);
                rotateCorners({DFR ,DRB,UBR, URF}, inverse);
                rotateEdges({FR, DR, BR, UR}, inverse);
                rotateCorners({DFR ,DRB,UBR, URF}, inverse);
            }
            else {
                rotateEdges({FR, DR, BR, UR}, inverse);
                rotateCorners({DFR ,DRB,UBR, URF}, inverse);

                
                // // Update corner orientations for R move
                cornerOrientations[URF] = ( ((cornerOrientations[URF] -'0' )+  1 ) % 3 ) + '0'; // UBR
                cornerOrientations[UBR] = ( ((cornerOrientations[UBR] -'0' )+  2 ) % 3 ) + '0'; // URF
                cornerOrientations[DRB] = ( ((cornerOrientations[DRB] -'0' )+  1 ) % 3 ) + '0'; // UBR
                cornerOrientations[DFR] = ( ((cornerOrientations[DFR] -'0' )+  2 ) % 3 ) + '0'; // URF

            }
            
            break;
        default:
            std::cerr << "Move " << move << " not implemented.\n";
            return;
    }
}


void Cube::rotateEdges(const std::array<int, 4>& indices, bool inverse) {
    if (!inverse) {
        int tempPos = edgePositions[indices[0]];

        for (int i = 0; i < 3; ++i) edgePositions[indices[i]] = edgePositions[indices[i + 1]];
        
        edgePositions[indices[3]] = tempPos;
      
    } else {
        int tempPos = edgePositions[indices[3]];

        for (int i = 3; i > 0; --i)  edgePositions[indices[i]] = edgePositions[indices[i - 1]];
        
        edgePositions[indices[0]] = tempPos;
     
    }
}

void Cube::rotateCorners(const std::array<int, 4>& indices, bool inverse) {
    if (!inverse) {
        int tempPos = cornerPositions[indices[0]];
        for (int i = 0; i < 3; ++i) {
            cornerPositions[indices[i]] = cornerPositions[indices[i + 1]];
        }
        cornerPositions[indices[3]] = tempPos;

    } else {
        int tempPos = cornerPositions[indices[3]];
        for (int i = 3; i > 0; --i) {
            cornerPositions[indices[i]] = cornerPositions[indices[i - 1]];
      
        }
        cornerPositions[indices[0]] = tempPos;
      
    }
}

// Template functions for rotating corners and edges
template <size_t N>
void rotateLeft_corner(std::array<Corner, N>& arr, int l, int r) {
    Corner temp = arr[l];
    for (int i = l; i < r; i++)
        arr[i] = arr[i + 1];
    arr[r] = temp;
}

template <size_t N>
void rotateRight_corner(std::array<Corner, N>& arr, int l, int r) {
    Corner temp = arr[r];
    for (int i = r; i > l; i--)
        arr[i] = arr[i - 1];
    arr[l] = temp;
}

template <size_t N>
void rotateLeft_edge(std::array<Edge, N>& arr, int l, int r) {
    Edge temp = arr[l];
    for (int i = l; i < r; i++)
        arr[i] = arr[i + 1];
    arr[r] = temp;
}

template <size_t N>
void rotateRight_edge(std::array<Edge, N>& arr, int l, int r) {
    Edge temp = arr[r];
    for (int i = r; i > l; i--)
        arr[i] = arr[i - 1];
    arr[l] = temp;
}

// Function for combination calculation
int Cube::Cnk(int n, int k) const {
    if (n < k)
        return 0;
    if (k > n / 2)
        k = n - k;
    int s = 1;
    for (int i = n, j = 1; i != n - k; i--, j++) {
        s *= i;
        s /= j;
    }
    return s;
}

short Cube::getTwist() const {
    short ret = 0;
    for (int i = URF; i < DRB; i++)
        ret = (short)(3 * ret + cornerOrientations[i]);
    return ret;
}

void Cube::setTwist(short twist) {
    int twistParity = 0;
    for (int i = DRB - 1; i >= URF; i--) {
        twistParity += cornerOrientations[i] = (char)(twist % 3);
        twist /= 3;
    }
    cornerOrientations[DRB] = (char)((3 - twistParity % 3) % 3);
}

short Cube::getFlip() const {
    short ret = 0;
    for (int i = UR; i < BR; i++)
        ret = (short)(2 * ret + edgeOrientations[i]);
    return ret;
}

void Cube::setFlip(short flip) {
    int flipParity = 0;
    for (int i = BR - 1; i >= UR; i--) {
        flipParity += edgeOrientations[i] = ( char)(flip % 2);
        flip /= 2;
    }
    edgeOrientations[BR] = (char)((2 - flipParity % 2) % 2);
}

short Cube::cornerParity()const {
    int s = 0;
    for (int i = DRB; i >= URF + 1; i--)
        for (int j = i - 1; j >= URF; j--)
            if (cornerPositions[j] > cornerPositions[i])
                s++;
    return (short)(s % 2);
}

short Cube::edgeParity()const {
    int s = 0;
    for (int i = BR; i >= UR + 1; i--)
        for (int j = i - 1; j >= UR; j--)
            if (edgePositions[j] > edgePositions[i])
                s++;
    return (short)(s % 2);
}

short Cube::getFRtoBR() const {
    int a = 0, x = 0, b = 0;
    std::array<Edge, 4> edge4;
    for (int j = BR; j >= UR; j--)
        if (FR <= edgePositions[j] && edgePositions[j] <= BR) {
            a += Cnk(11 - j, x + 1);
            edge4[3 - x++] = static_cast<Edge>(edgePositions[j]);
        }

    for (int j = 3; j > 0; j--) {
        int k = 0;
        while (edge4[j] != j + 8) {
            rotateLeft_edge(edge4, 0, j);
            k++;
        }
        b = (j + 1) * b + k;
    }
    return (short)(24 * a + b);
}

void Cube::setFRtoBR(short idx) {
    int x, j, k;
    std::array<Edge, 4> sliceEdge = {FR, FL, BL, BR};
    std::array<Edge, 8> otherEdge = {UR, UF, UL, UB, DR, DF, DL, DB};
    int b = idx % 24; // Permutation
    int a = idx / 24; // Combination
    for (int e = 0; e < EDGE_COUNT; e++)
        edgePositions[e] = DB; // Use DB to invalidate all edges

    for (j = 1; j < 4; j++) {
        k = b % (j + 1);
        b /= j + 1;
        while (k-- > 0)
            rotateRight_edge(sliceEdge, 0, j);
    }

    x = 3; // generate combination and set slice edges
    for (j = UR; j <= BR; j++)
        if (a - Cnk(11 - j, x + 1) >= 0) {
            edgePositions[j] = sliceEdge[3 - x];
            a -= Cnk(11 - j, x-- + 1);
        }

    x = 0; // set the remaining edges UR..DB
    for (j = UR; j <= BR; j++)
        if (edgePositions[j] == DB)
            edgePositions[j] = otherEdge[x++];
            
}

short Cube::getURFtoDLF() const {
    
    int a = 0, x = 0, b = 0;
    std::array<Corner, 6> corner6;
    for (int j = URF; j <= DRB; j++)
        if (cornerPositions[j] <= DLF) {
            a += Cnk(j, x + 1);
            corner6[x++] = static_cast<Corner>(cornerPositions[j]);
        }

    for (int j = 5; j > 0; j--) {
        int k = 0;
        while (corner6[j] != j) {
            rotateLeft_corner(corner6, 0, j);
            k++;
        }
        b = (j + 1) * b + k;
    }
    return (short)(720 * a + b);
}
short Cube::getURtoUL() const{
    int a = 0, b = 0, x = 0, j;
    std::array<Edge, 3> edge3 = {UR, UF, UL}; // Initialize with valid Edge values
    // compute the index a < (12 choose 3) and the edge permutation.
    for (j = UR; j <= BR; j++)
        if (edgePositions[j] <= UL) {
            a += Cnk(j, x + 1);
            edge3[x++] = static_cast<Edge>(edgePositions[j]);
        }

    for (j = 2; j > 0; j--)// compute the index b < 3! for the
    // permutation in edge3
    {
        int k = 0;
        while (edge3[j] != j) {
            rotateLeft_edge(edge3, 0, j);
            k++;
        }
        b = (j + 1) * b + k;
    }
    return (short) (6 * a + b);
}

void Cube::setURtoUL(short idx) {
    int x, e, j, k;
    std::array<Edge, 3> edge3 = {UR, UF, UL}; 
    int b = idx % 6; // Permutation
    int a = idx / 6; // Combination
    for(e = 0; e < EDGE_COUNT; e++) {
        edgePositions[e] = BR;// Use BR to invalidate all edges
    }

    for (j = 1; j < 3; j++) {// generate permutation from index b
        k = b % (j + 1);
        b /= j + 1;
        while (k-- > 0)
            rotateRight_edge(edge3, 0, j);
    }
    x = 2;// generate combination and set edges
    for (j = BR; j >= 0; j--) {
        if (a - Cnk(j, x + 1) >= 0) {
            edgePositions[j] = edge3[x];
            a -= Cnk(j, x-- + 1);
        }
    }
}

short Cube::getUBtoDF() const {
    int a = 0, x = 0, b = 0, j;
    std::array<Edge, 3> edge3 = {UR, UF, UL};
    // compute the index a < (12 choose 3) and the edge permutation.
    for (j = UR; j <= BR; j++)
        if (UB <= edgePositions[j] && edgePositions[j] <= DF) {
            a += Cnk(j, x + 1);
            edge3[x++] = static_cast<Edge>(edgePositions[j]);
        }

    for (j = 2; j > 0; j--)// compute the index b < 3! for the
    // permutation in edge3
    {
        int k = 0;
        while (edge3[j] != UB + j) {
            rotateLeft_edge(edge3, 0, j);
            k++;
        }
        b = (j + 1) * b + k;
    }
    return (short) (6 * a + b);
}

void Cube::setUBtoDF(short idx)
{
    int x, e, j, k;
   std::array<Edge, 3> edge3 = {UB, DR, DF}; 
    int b = idx % 6; // Permutation
    int a = idx / 6; // Combination
    for (e = 0; e < EDGE_COUNT; e++)
        edgePositions[e] = BR;// Use BR to invalidate all edges

    for (j = 1; j < 3; j++)// generate permutation from index b
    {
        k = b % (j + 1);
        b /= j + 1;
        while (k-- > 0)
            rotateRight_edge(edge3, 0, j);
    }
    x = 2;// generate combination and set edges
    for (j = BR; j >= 0; j--)
        if (a - Cnk(j, x + 1) >= 0) {
            edgePositions[j] = edge3[x];
            a -= Cnk(j, x-- + 1);
        }
}




void Cube::setURFtoDLF(short idx) {
    int x;
    std::array<Corner, 6> corner6 = {URF, UFL, ULB, UBR, DFR, DLF};
    std::array<Corner, 2> otherCorner = {DBL, DRB};
    int b = idx % 720; // Permutation
    int a = idx / 720; // Combination
    for (int c = 0; c < CORNER_COUNT; c++)
        cornerPositions[c] = DRB; // Use DRB to invalidate all corners

    for (int j = 1; j < 6; j++) {
        int k = b % (j + 1);
        b /= j + 1;
        while (k-- > 0)
            rotateRight_corner(corner6, 0, j);
    }
    x = 5; // generate combination and set corners
    for (int j = DRB; j >= 0; j--)
        if (a - Cnk(j, x + 1) >= 0) {
            cornerPositions[j] = corner6[x];
            a -= Cnk(j, x-- + 1);
        }
    x = 0;
    for (int j = URF; j <= DRB; j++)
        if (cornerPositions[j] == DRB)
            cornerPositions[j] = otherCorner[x++];
}

short Cube::getURtoDF() const {
    int a = 0, x = 0, b = 0;
    std::array<Edge, 6> edge6;
    for (int j = UR; j <= BR; j++)
        if (edgePositions[j] <= DF) {
            a += Cnk(j, x + 1);
            edge6[x++] = static_cast<Edge>(edgePositions[j]);
        }

    for (int j = 5; j > 0; j--) {
        int k = 0;
        while (edge6[j] != j) {
            rotateLeft_edge(edge6, 0, j);
            k++;
        }
        b = (j + 1) * b + k;
    }
    return 720 * a + b;
}

void Cube::setURtoDF(short idx) {
    int x, j;
    std::array<Edge, 6> edge6 = {UR, UF, UL, UB, DR, DF};
    std::array<Edge, 6> otherEdge = {DL, DB, FR, FL, BL, BR};
    int b = idx % 720; // Permutation
    int a = idx / 720; // Combination

    for (int e = 0; e < EDGE_COUNT; e++)
        edgePositions[e] = BR; // Use BR to invalidate all edges

    for (j = 1; j < 6; j++) {
        int k = b % (j + 1);
        b /= j + 1;
        while (k-- > 0)
            rotateRight_edge(edge6, 0, j);
    }
    x = 5; // generate combination and set edges
    for (j = BR; j >= 0; j--)
        if (a - Cnk(j, x + 1) >= 0) {
            edgePositions[j] = edge6[x];
            a -= Cnk(j, x-- + 1);
        }
    x = 0; // set the remaining edges DL..BR
    for (j = UR; j <= BR; j++)
        if (edgePositions[j] == BR)
            edgePositions[j] = otherEdge[x++];
}

int Cube::getURFtoDLB() const {
    std::array<Corner, 8> perm;
    int b = 0;
    for (int i = 0; i < 8; i++)
        perm[i] = static_cast<Corner>(cornerPositions[i]);
    for (int j = 7; j > 0; j--) {
        int k = 0;
        while (perm[j] != j) {
            rotateLeft_corner(perm, 0, j);
            k++;
        }
        b = (j + 1) * b + k;
    }
    return b;
}

void Cube::setURFtoDLB(int idx) {
    std::array<Corner, 8> perm = {URF, UFL, ULB, UBR, DFR, DLF, DBL, DRB};
    for (int j = 1; j < 8; j++) {
        int k = idx % (j + 1);
        idx /= j + 1;
        while (k-- > 0)
            rotateRight_corner(perm, 0, j);
    }

    int x = 7; // set corners
    for (int j = 7; j >= 0; j--)
        cornerPositions[j] = perm[x--];
}

int Cube::getURtoBR() const {
    std::array<Edge, 12> perm;
    int b = 0;
    for (int i = 0; i < 12; i++)
        perm[i] = static_cast<Edge>(edgePositions[i]);
    for (int j = 11; j > 0; j--) {
        int k = 0;
        while (perm[j] != j) {
            rotateLeft_edge(perm, 0, j);
            k++;
        }
        b = (j + 1) * b + k;
    }
    return b;
}

void Cube::setURtoBR(int idx) {
    std::array<Edge, 12> perm = { UR, UF, UL, UB, DR, DF, DL, DB, FR, FL, BL, BR };
    for (int j = 1; j < 12; j++) {
        int k = idx % (j + 1);
        idx /= j + 1;
        while (k-- > 0)
            rotateRight_edge(perm, 0, j);
    }
    int x = 11;
    for (int j = 11; j >= 0; j--)
        edgePositions[j] = perm[x--];
}

int Cube::verify() {
    int sum = 0;
    int edgeCount[EDGE_COUNT] = {0};
    int cornerCount[CORNER_COUNT] = {0};

    for (int e = 0; e < EDGE_COUNT; e++)
        edgeCount[edgePositions[e]]++;
    for (int i = 0; i < EDGE_COUNT; i++)
        if (edgeCount[i] != 1)
            return -2;

    for (int i = 0; i < EDGE_COUNT; i++)
        sum += edgeOrientations[i];
    if (sum % 2 != 0)
        return -3;

    for (int c = 0; c < CORNER_COUNT; c++)
        cornerCount[cornerPositions[c]]++;
    for (int i = 0; i < CORNER_COUNT; i++)
        if (cornerCount[i] != 1)
            return -4; // missing corners

    sum = 0;
    for (int i = 0; i < CORNER_COUNT; i++)
        sum += cornerOrientations[i];
    if (sum % 3 != 0)
        return -5; // twisted corner

    if ((edgeParity() ^ cornerParity()) != 0)
        return -6; // parity error

    return 0; // cube ok
}
