#ifndef SUDOKU_BASE_H
#define SUDOKU_BASE_H

#include <cstring>
#include <ostream>

using namespace std;

class SudokuBase
{
public:
    enum Status{Unknown, Full, Empty, NotEmpty, Paradoxical};
    typedef unsigned short u_short;
    const static u_short Order      = 3;
    const static u_short RowInFloor = Order;
    const static u_short ColInTower = Order;
    const static u_short Tower      = Order;
    const static u_short Floor      = Order;
    const static u_short Row        = RowInFloor * Floor;
    const static u_short Col        = ColInTower * Tower;
    const static u_short Block      = Tower * Floor;
    const static u_short NumberRange = Order*Order+1;
    const static u_short CellAmount = Row * Col;
    typedef u_short Map[Row][Col];
    u_short GetNumber(u_short r, u_short c) const;
    SudokuBase();
    SudokuBase(const SudokuBase & other);
    SudokuBase & operator=(const SudokuBase & other);
    friend ostream & operator<<(ostream &os, const SudokuBase &s);
protected:
    const static u_short MinStep = 17;
    Map map;
    void Copy(const SudokuBase & other);
};

const char * StatusToString(SudokuBase::Status s);
#endif
