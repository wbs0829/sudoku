#include "SudokuMaker.h"

void SudokuMaker::Copy(const SudokuMaker & other)
{
    SudokuBase::Copy(other);
    status = other.status;
}

SudokuMaker::Status SudokuMaker::GetStatus()
{
    return status;
}

SudokuMaker::SudokuMaker(const SudokuMaker & other)
{
    Copy(other);
}

SudokuMaker & SudokuMaker::operator = (const SudokuMaker & other)
{
    Copy(other);
    return *this;
}

void SudokuMaker::Generate(const SudokuBase & base, u_short needBlank)
{
    SudokuSolver sdks;
    sdks.Solve(base);
    if (sdks.GetStatus() == Paradoxical) {
        status = Paradoxical;
        return;
    }
    sdks.GetAnAnswer();
    SudokuBase::Copy(sdks);
    counter rowBlank[Row] = {};
    counter colBlank[Col] = {};
    counter blockBlank[Floor][Tower] = {};
    for ( u_short blank = 0; blank < NumberRange-1; ++blank) {
        for ( u_short row = 0; row < Row; ++row) {
            if (rowBlank[row] == blank) {
                vector<u_short> vecFilled;
                for ( u_short col = 0; col < Col; ++col) {
                    if (map[row][col]) {
                        vecFilled.push_back(col);
                    }
                }
                while (!vecFilled.empty()) {
                    u_short randomIndex = rand()%vecFilled.size();
                    u_short col = vecFilled[randomIndex];
                    u_short num = map[row][col];
                    map[row][col] = 0;
                    sdks.Solve(*this);
                    if (sdks.GetStatus() != Full) {
                        vecFilled.erase(vecFilled.begin()+randomIndex);
                        map[row][col] = num;
                    } else {
                        ++rowBlank[row];
                        ++colBlank[col];
                        ++blockBlank[row/RowInFloor][col/ColInTower];
                        if (--needBlank == 0) {
                            status = NotEmpty;
                            return;
                        }
                        break;
                    }
                }
            }
        }
        for ( u_short col = 0; col < Col; ++col) {
            if (colBlank[col] == blank) {
                vector<u_short> vecFilled;
                for ( u_short row = 0; row < Row; ++row) {
                    if (map[row][col]) {
                        vecFilled.push_back(row);
                    }
                }
                while (!vecFilled.empty()) {
                    u_short randomIndex = rand()%vecFilled.size();
                    u_short row = vecFilled[randomIndex];
                    u_short num = map[row][col];
                    map[row][col] = 0;
                    sdks.Solve(*this);
                    if (sdks.GetStatus() != Full) {
                        map[row][col] = num;
                        vecFilled.erase(vecFilled.begin()+randomIndex);
                    } else {
                        ++rowBlank[row];
                        ++colBlank[col];
                        ++blockBlank[row/RowInFloor][col/ColInTower];
                        if (--needBlank == 0) {
                            status = NotEmpty;
                            return;
                        }
                        break;
                    }
                }
            }
        }
    }
    status = NotEmpty;
}
