// PruningTable.cpp
#include "PruningTable.h"
#include "CoordCube.h"

#include <fstream>
#include <iostream>
#include <sstream>

// Initialize static member variables
std::array<signed char, N_SLICE2 * N_URFtoDLF * N_PARITY / 2> PruningTable::Slice_URFtoDLF_Parity_Prun;
std::array<signed char, N_SLICE2 * N_URtoDF * N_PARITY / 2> PruningTable::Slice_URtoDF_Parity_Prun;
std::array<signed char, N_SLICE1 * N_TWIST / 2 + 1> PruningTable::Slice_Twist_Prun;
std::array<signed char, N_SLICE1 * N_FLIP / 2> PruningTable::Slice_Flip_Prun;

// Constructor
PruningTable::PruningTable() {
    loadPruningTables("Table");
}

// Method to load pruning tables from binary files
bool PruningTable::loadPruningTables(const std::string& directory) {
    bool success = true;
    success &= loadPruningTableBinary(directory + "/Slice_URFtoDLF_Parity_Prun", Slice_URFtoDLF_Parity_Prun);
    success &= loadPruningTableBinary(directory + "/Slice_URtoDF_Parity_Prun", Slice_URtoDF_Parity_Prun);
    success &= loadPruningTableBinary(directory + "/Slice_Twist_Prun", Slice_Twist_Prun);
    success &= loadPruningTableBinary(directory + "/Slice_Flip_Prun", Slice_Flip_Prun);

    if (!success) {
        std::cerr << "Failed to load one or more pruning tables." << std::endl;
    }

    return success;
}

// Template function to load a pruning table from a binary file
template <size_t Size>
bool PruningTable::loadPruningTableBinary(const std::string& filename, std::array<signed char, Size>& table) {
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        std::cerr << "Error opening pruning table file: " << filename << std::endl;
        return false;
    }

    // Read the entire table at once
    file.read(reinterpret_cast<char*>(table.data()), Size * sizeof(signed char));

    if (!file) {
        std::cerr << "Error reading pruning table from file: " << filename << std::endl;
        return false;
    }

    return true;
}