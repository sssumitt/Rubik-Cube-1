#include "Cube.h"
#include "FaceCube.h"
#include "CoordCube.h"
#include <iostream>

#include <MoveTable.h>
#include <PruningTable.h>



int main() {
    Cube cube;


    FaceCube fc;
    fc.updateFacelets(cube);
    fc.printFacelets(cube);


    // CoordCube c = c.get_CoordCube(cube);
   

    // Cube convert = c.getCube(c) ;
    // std::cout<< "Edge: ";
    // for(int i = 0 ; i< EDGE_COUNT ; i++){
    //     std::cout << convert.edgePositions[i] << " ";
    // }

    // std::cout<<std::endl;

    // FaceCube fc2;
    // fc2.updateFacelets(convert);
    // fc2.printFacelets(convert);
    

    
    return 0 ; 
}
