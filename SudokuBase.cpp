#include "SudokuBase.h"

SudokuBase::SudokuBase()
{
    memset(map, 0, sizeof(map));
}

SudokuBase::SudokuBase(const SudokuBase & other)
{
    memcpy(map, other.map, sizeof(map));
}

void SudokuBase::Copy(const SudokuBase & other)
{
    memcpy(map, other.map, sizeof(map));
}

SudokuBase & SudokuBase::operator=(const SudokuBase & other)
{
    Copy(other);
    return *this;
}

SudokuBase::u_short SudokuBase::GetNumber(u_short r, u_short c) const
{
    return map[r][c];
}

ostream & operator<<(ostream &os, const SudokuBase &s)
{
    SudokuBase::u_short floor, row, tower, col;
    for ( floor = 0; floor < SudokuBase::Floor; ++floor) {
        for ( row = 0; row < SudokuBase::RowInFloor; ++row) {
            for ( tower = 0; tower < SudokuBase::Tower; ++tower) {
                for ( col = 0; col < SudokuBase::ColInTower; ++col) {
                    os << s.map[floor*SudokuBase::RowInFloor+row][tower*SudokuBase::ColInTower+col];
                }
                os << ' ';
            }
            os << endl; 
        }
        os << endl; 
    }
    return os;
}

const char * StatusToString(SudokuBase::Status s)
{
    switch (s) {
    case SudokuBase::Unknown :
        return "Unknown";
    case SudokuBase::Full :
        return "Full";
    case SudokuBase::Empty :
        return "Empty";
    case SudokuBase::NotEmpty :
        return "NotEmpty";
    case SudokuBase::Paradoxical :
        return "Paradoxical";
    default :
        return "";
    }
}
