#ifndef MOVE_H
#define MOVE_H

enum  class Move {
    U, U_PRIME, U2,
    D, D_PRIME, D2,
    L, L_PRIME, L2,
    R, R_PRIME, R2,
    F, F_PRIME, F2,
    B, B_PRIME, B2,
};

enum class Move_P1 {
    U, U_PRIME, U2,
    D, D_PRIME, D2,
    R2, L2, F2, B2
};


#endif // MOVE_H