#ifndef SUDOKU_CELL_H
#define SUDOKU_CELL_H

#include "SudokuBase.h"

class Cell
{
public:
    typedef unsigned short u_short;
    size_t row;
    size_t col;
    u_short num;
    Cell(size_t r = 0, size_t c = 0, u_short n = 0) :row(r), col(c), num(n){}
};
#endif
