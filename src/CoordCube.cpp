#include "CoordCube.h"
#include "Cube.h"
#include <iostream>



CoordCube::CoordCube() {
    // for solved cube 
    twist = 0;
    flip = 0;
    parity = 0;
    FRtoBR = 0;
    URFtoDLF = 0;
    URtoUL = 0;
    UBtoDF = 114;
    URtoDF = 0;

}

CoordCube CoordCube::get_CoordCube(const Cube &cube) {
    CoordCube c;
    c.twist = cube.getTwist();
    c.flip = cube.getFlip();
    c.parity = cube.cornerParity();
    c.FRtoBR = cube.getFRtoBR();
    c.URFtoDLF = cube.getURFtoDLF();
    c.URtoUL = cube.getURtoUL();
    c.UBtoDF = cube.getUBtoDF();
    c.URtoDF = cube.getURtoDF();
    return c;
}

Cube CoordCube::getCube(const CoordCube &c) const{
    Cube cube;
    cube.setTwist(c.twist);
    cube.setFlip(c.flip);
    cube.setFRtoBR(c.FRtoBR);
    cube.setURFtoDLF(c.URFtoDLF);
    cube.setURtoUL(c.URtoUL);
    cube.setUBtoDF(c.UBtoDF);
    cube.setURtoDF(c.URtoDF);
    return cube;
}
