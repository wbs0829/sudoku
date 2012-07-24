#ifndef SUDOKU_SOLVER_H
#define SUDOKU_SOLVER_H

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <queue>
#include "SudokuBase.h"
#include "Sudoku.h"
#include "Cell.h"
#include "Task.h"

using namespace std;

class SudokuSolver : public SudokuBase
{
private:
    typedef u_short counter;
    
    bool possible[Row][Col][NumberRange];
    bool horGroupPossible[Row][Tower][NumberRange];
    bool verGroupPossible[Col][Floor][NumberRange];

    counter impossibility   [Row][Col];
    counter rowImpossibility[Row]     [NumberRange];
    counter colImpossibility     [Col][NumberRange];
    counter blockImpossibility[Floor][Tower][NumberRange];
    counter horGroupImpossibility[Row][Tower][NumberRange];
    counter verGroupImpossibility[Col][Floor][NumberRange];
    counter floorGroup[Floor][Tower][NumberRange];
    counter towerGroup[Tower][Floor][NumberRange];
    counter rowGroup[Row][NumberRange];
    counter colGroup[Col][NumberRange];

    queue<Cell> qFill;
    queue<Task> qCheck;

    counter effectiveCell;
    counter filledCell;

    Status status;

    void Copy(const SudokuSolver &);
    void Reset();

    void Maintain();
    void Fill();
    void CheckImpoCell(const Cell &);
    void CheckImpoHorGroup(const Cell &);
    void CheckImpoVerGroup(const Cell &);
    void CheckKnownHorGroup(const Cell &);
    void CheckKnownVerGroup(const Cell &);
    void Test();
    void FillNotChange(const Cell &);
    Cell MinPossibilityCell();
public:
    SudokuSolver();
    SudokuSolver(const SudokuSolver &);
    SudokuSolver & operator = (const SudokuSolver &);
    ~SudokuSolver(){}
    void Solve(const SudokuBase &);
    void Fill(const Cell &);
    void GetAnAnswer();
	Status GetStatus() const;
    friend ostream & operator<(ostream &, const SudokuSolver &);
};

#endif
