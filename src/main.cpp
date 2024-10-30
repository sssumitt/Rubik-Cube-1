#include "Cube.h"
#include "FaceCube.h"
#include "CoordCube.h"
#include <iostream>

#include <MoveTable.h>
#include <PruningTable.h>




int main() {
    Cube cube ;

    for(int i =0 ; i< 18 ; i++) {
        Move m = static_cast<Move>(i) ;
        
        std::cout << "Move : " << cube.moveToString(m) << std::endl;
        
        cube.applyMove(cube.moveToString(m)) ;

        FaceCube fc;
        fc.updateFacelets(cube) ;
        fc.printFacelets(cube) ;
        
    }
    
    return 0 ; 
}
