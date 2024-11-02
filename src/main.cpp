#include "Cube.h"
#include "FaceCube.h"
#include "CoordCube.h"
#include <iostream>

#include <MoveTable.h>
#include <PruningTable.h>




int main() {
    Cube cube ;
    cube.applyMove("R ") ;
    cube.display() ;
    
    CoordCube c ;
    c.set_CoordCube( cube ) ;

    Cube cube2 = c.getCube( );

    cube2.display() ; 
    
    
    return 0 ; 
}
