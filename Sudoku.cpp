#include "Sudoku.h"
#include <iostream>
using namespace std;

Sudoku::Sudoku()
{
    Reset();
}

Sudoku::Sudoku(const Sudoku & other)
{
    Copy(other);
}

Sudoku::Sudoku(const SudokuBase & base)
{
    Copy(base);
}

void Sudoku::Copy(const Sudoku & other)
{
    SudokuBase::Copy(other);
    status = other.status;
    filledCell = other.filledCell;
}

void Sudoku::Copy(const SudokuBase & base)
{
    SudokuBase::Copy(base);
    status = Unknown;
}

void Sudoku::Fill(const Cell & c)
{
    if (c.num != map[c.row][c.col]) {
        map[c.row][c.col] = c.num;
        if (status != Unknown) {
            if (status == Paradoxical) {
                status = Unknown;
            } else {
                if (c.num) {
                    if (filledCell == 0) {
                        status = NotEmpty;
                    }
                    if (IsParadoxical(c)) {
                        return;
                    }
                    ++filledCell;
                    if (filledCell == CellAmount) {
                        status = Full;
                    }
                } else {
                    if (filledCell == CellAmount) {
                        status = NotEmpty;
                    }
                    --filledCell;
                    if (filledCell == 0) {
                        status = Empty;
                    }
                }
            }
        }
    }
}

void Sudoku::Reset()
{
    memset(map, 0, sizeof(map));
    status = Empty;
    filledCell = 0;
}

Sudoku & Sudoku::operator=(const Sudoku & other)
{
    Copy(other);
    return *this;
}

Sudoku & Sudoku::operator=(const SudokuBase & base)
{
    Copy(base);
    return *this;
}

bool Sudoku::IsParadoxical(const Cell & c)
{
    for ( size_t i = 0; i < Order*Order; ++i) {
        if (map[c.row][i] == map[c.row][c.col] && i != c.col) {
            status = Paradoxical;
            return true;
        }
        if (map[i][c.col] == map[c.row][c.col] && i != c.row) {
            status = Paradoxical;
            return true;
        }
        u_short row = c.row/RowInFloor*RowInFloor+i/ColInTower;
        u_short col = c.col/ColInTower*ColInTower+i%ColInTower;
        if (map[row][col] == map[c.row][c.col] && col != c.col && row != c.row) {
            status = Paradoxical;
            return true;
        }
    }
    return false; 
}

Sudoku::Status Sudoku::GetStatus()
{
    if (status == Unknown) {
        filledCell = 0;
        for ( size_t j = 0; j < Order*Order; ++j) {
            bool existingRow[NumberRange] = {};
            bool existingCol[NumberRange] = {};
            bool existingBlock[NumberRange] = {};
            u_short row = j/Tower*Floor, col = j%Tower*Tower; 
            for ( size_t i = 0; i < Order*Order; ++i) {
                if (existingRow[map[j][i]]) {
                    status = Paradoxical;
                    return Paradoxical;
                }
                existingRow[map[j][i]] = true;
                existingRow[0] = false;
                if (existingCol[map[i][j]]) {
                    status = Paradoxical;
                    return Paradoxical;
                }
                existingCol[map[i][j]] = true;
                existingCol[0] = false;
                u_short r = row+i/ColInTower, c = col+i%ColInTower;
                if (existingBlock[map[r][c]]) {
                    status = Paradoxical;
                    return Paradoxical;
                }
                existingBlock[map[r][c]] = true;
                existingBlock[0] = false;
                if (map[i][j]) {
                    ++filledCell;
                }
            }
        }
        if (filledCell == 0) {
            status = Empty;
        } else if (filledCell == CellAmount) {
            status = Full;
        } else {
            status = NotEmpty;
        }
    }
    return status;
}
