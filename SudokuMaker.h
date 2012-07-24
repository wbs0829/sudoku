#ifndef SUDOKU_MAKER_H
#define SUDOKU_MAKER_H

#include "SudokuBase.h"
#include "Sudoku.h"
#include "SudokuSolver.h"

class SudokuMaker : public SudokuBase
{
private:
    typedef u_short counter;
    Status status;
    void Copy(const SudokuMaker &);
public:
    SudokuMaker(){}
    SudokuMaker(const SudokuMaker &);
    SudokuMaker & operator = (const SudokuMaker &);
    void Generate(const SudokuBase &, u_short limit);
    Status GetStatus();
};
#endif
