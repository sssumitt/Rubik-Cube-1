#ifndef PRUNING_TABLE_H
#define PRUNING_TABLE_H

#include "CoordCube.h"
#include "Move.h"
#include <array>
#include <string>

class PruningTable {
public:
    // Constructors and Destructor
    PruningTable();

    // Methods to load pruning tables from files
    bool loadPruningTables(const std::string& directory);

    template <std::size_t Size>
    bool loadPruningTableBinary(const std::string& filename, std::array<signed char, Size>& table);

 
    // Pruning table for the permutation of corners and UD-slice edges in phase 2
    // Gives lower estimation for moves needed to reach the solved cube
    static std::array<signed char, N_SLICE2 * N_URFtoDLF * N_PARITY / 2> Slice_URFtoDLF_Parity_Prun;

    // Pruning table for the permutation of edges in phase 2
    // Gives lower estimation for moves needed to reach the solved cube
    static std::array<signed char, N_SLICE2 * N_URtoDF * N_PARITY / 2> Slice_URtoDF_Parity_Prun;


    // Pruning table for the twist of corners and the position of UD-slice edges in phase 1
    // Gives lower estimation for moves needed to reach the H-subgroup
    static std::array<signed char, N_SLICE1 * N_TWIST / 2 + 1> Slice_Twist_Prun;

    // Pruning table for the flip of edges and the position of UD-slice edges in phase 1
    // Gives lower estimation for moves needed to reach the H-subgroup
    static std::array<signed char, N_SLICE1 * N_FLIP / 2> Slice_Flip_Prun;
    
};

#endif // PRUNING_TABLE_H
