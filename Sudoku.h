#ifndef SUDOKU_H
#define SUDOKU_H

#include "Cell.h"
#include "SudokuBase.h"
#include <cstring>

class Sudoku : public SudokuBase
{
private:
    void Copy(const Sudoku & other);
    void Copy(const SudokuBase & base);
    Status status;
    u_short filledCell;
    bool IsParadoxical(const Cell & c);
public:
    void Fill(const Cell & c);
    void Reset();
    Sudoku();
    Sudoku(const Sudoku & other);
    Sudoku(const SudokuBase & base);
    Sudoku & operator=(const Sudoku & other);
    Sudoku & operator=(const SudokuBase & base);
    Status GetStatus();
};

#endif
