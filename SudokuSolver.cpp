#include "SudokuSolver.h"
#include <iostream>
using namespace std;

SudokuSolver::SudokuSolver()
{
    Reset();
}

SudokuSolver::SudokuSolver(const SudokuSolver &other)
{
    Copy(other);
}

void SudokuSolver::FillNotChange(const Cell & c)
{
    if (map[c.row][c.col] == c.num || c.num == 0) {
        return ;
    }
    if (map[c.row][c.col] > 0){
        status = Paradoxical;
        return ;
    }
    if (status == Empty) {
        status = NotEmpty;
    } else if (status == Paradoxical) {
        return;
    }
    ++effectiveCell;
    qFill.push(c);
    Maintain();
    return ;
}

void SudokuSolver::Fill(const Cell & c)
{
    if (map[c.row][c.col] == c.num) {
        return ;
    }
    if (map[c.row][c.col] > 0){
        Sudoku sdk(*this);
        sdk.Fill(c);
        Solve(sdk);
        return ;
    }
    if (status == Empty) {
        status = NotEmpty;
    } else if (status == Paradoxical) {
        return;
    }
    ++effectiveCell;
    qFill.push(c);
    Maintain();
    return ;
}

SudokuSolver & SudokuSolver::operator = (const SudokuSolver & other)
{
    Copy(other);
    return *this;
}

void SudokuSolver::Reset()
{
    memset(map, 0, sizeof(map));
	memset(possible, 1, sizeof(possible));
	memset(horGroupPossible, 1, sizeof(horGroupPossible));
	memset(verGroupPossible, 1, sizeof(verGroupPossible));
	memset(impossibility, 0, sizeof(impossibility));
	memset(rowImpossibility, 0, sizeof(rowImpossibility));
	memset(colImpossibility, 0, sizeof(colImpossibility));
	memset(blockImpossibility, 0, sizeof(blockImpossibility));
	memset(horGroupImpossibility, 0, sizeof(horGroupImpossibility));
	memset(verGroupImpossibility, 0, sizeof(verGroupImpossibility));
	memset(floorGroup, 0, sizeof(floorGroup));
	memset(towerGroup, 0, sizeof(towerGroup));
	memset(rowGroup, 0, sizeof(rowGroup));
	memset(colGroup, 0, sizeof(colGroup));

    effectiveCell = 0;
    filledCell = 0;
    status = Empty;
    qFill = queue<Cell>();
    qCheck = queue<Task>();
}

void SudokuSolver::Copy(const SudokuSolver & other)
{
    if (other.status == Empty) {
        Reset();
        return;
    }
    status = other.status;
    effectiveCell = other.effectiveCell;
    filledCell = other.filledCell;
    memcpy(map, other.map, sizeof(map));
    if (status != Full && status != Paradoxical) {
		memcpy(possible, other.possible, sizeof(possible));
		memcpy(horGroupPossible, other.horGroupPossible, sizeof(horGroupPossible));
		memcpy(verGroupPossible, other.verGroupPossible, sizeof(verGroupPossible));
		memcpy(impossibility, other.impossibility, sizeof(impossibility));
		memcpy(rowImpossibility, other.rowImpossibility, sizeof(rowImpossibility));
		memcpy(colImpossibility, other.colImpossibility, sizeof(colImpossibility));
		memcpy(blockImpossibility, other.blockImpossibility, sizeof(blockImpossibility));
		memcpy(horGroupImpossibility, other.horGroupImpossibility, sizeof(horGroupImpossibility));
		memcpy(verGroupImpossibility, other.verGroupImpossibility, sizeof(verGroupImpossibility));
		memcpy(floorGroup, other.floorGroup, sizeof(floorGroup));
		memcpy(towerGroup, other.towerGroup, sizeof(towerGroup));
		memcpy(rowGroup, other.rowGroup, sizeof(rowGroup));
		memcpy(colGroup, other.colGroup, sizeof(colGroup));
        qFill = other.qFill;
        qCheck = other.qCheck;
    }
}

void SudokuSolver::Test()
{
    if (status == Full) {
        return;
    }
    if (status == Empty) {
        return;
    }
    if (status == Paradoxical) {
        return;
    }
    if (status == Unknown) {
        cerr << "Test an unknown sudoku." << endl;
        return;
    }
    if (effectiveCell < MinStep) {
        return;
    }
    Cell c = MinPossibilityCell();
    SudokuSolver oneSolution, otherSolution;
    for ( c.num = 1; c.num < NumberRange; ++c.num) {
        if (possible[c.row][c.col][c.num]) {
            if (oneSolution.status == Empty) {
                oneSolution = *this;
                oneSolution.Fill(c);
                oneSolution.Test();
                if (oneSolution.status == Paradoxical) {
                    oneSolution.Reset();
                    continue;
                }
                if (oneSolution.status == NotEmpty) {
                   status = NotEmpty;
                   return;
                }
            }
            else {
                otherSolution = *this;
                otherSolution.Fill(c);
                otherSolution.Test();
                if (otherSolution.status == Paradoxical) {
                    otherSolution.Reset();
                    continue;
                }
                /*
                 * otherSolution.status = NotEmpty, Full means this->status = NotEmpty
                 */
                status = NotEmpty;
                return;
            } 
        }
    }
    if (oneSolution.status != Empty) {
        *this = oneSolution;
    }
    else {
        status = Paradoxical;
    }
}

Cell SudokuSolver::MinPossibilityCell()
{
    Cell c, r;
    u_short minPossibility = NumberRange;
    for ( c.row = 0; c.row < Row; ++c.row) {
        for ( c.col = 0; c.col < Col; ++c.col) {
            if (impossibility[c.row][c.col] == NumberRange-3) {
                return c;
            }
            if (map[c.row][c.col] == 0 && NumberRange-1-impossibility[c.row][c.col] < minPossibility) {
                minPossibility = NumberRange-1-impossibility[c.row][c.col];
                r = c;
            }
        }
    }
    return r; 
}

void SudokuSolver::Maintain()
{
    while (!qFill.empty()) {
        Fill();
        while (!qCheck.empty()) {
            Task t = qCheck.front();
            qCheck.pop();
//            cout << t.row << t.col << t.num << t.info << endl
//                 << qFill.size() << endl
//                 << qCheck.size() << endl;
            switch(t.info) {
            case Task::ImpoCell :
                CheckImpoCell(static_cast<Cell>(t));
                break;
            case Task::ImpoHorGroup :
                CheckImpoHorGroup(static_cast<Cell>(t));
                break;
            case Task::ImpoVerGroup :
                CheckImpoVerGroup(static_cast<Cell>(t));
                break;
            case Task::KnownHorGroup :
                CheckKnownHorGroup(static_cast<Cell>(t));
                break;
            case Task::KnownVerGroup :
                CheckKnownVerGroup(static_cast<Cell>(t));
                break;
            }
//            cout < *this;
            if (status == Paradoxical) {
                return;
            }
        }
    } 
}

void SudokuSolver::Fill()
{
    Cell c = qFill.front();
    qFill.pop();

    if (map[c.row][c.col]) {
        return;
    }
//    cout << c.row << c.col << c.num << endl
//         << qFill.size() << endl
//         << qCheck.size() << endl;
    
    map[c.row][c.col] = c.num;
    if (++filledCell == CellAmount) {
        status = Full;
    }

    possible[c.row][c.col][c.num] = false;
//    cout << c.row << c.col << c.num << '=' << false << endl;

    for ( size_t col = 0; col < Col; ++col) {
        if (possible[c.row][col][c.num]) {
            possible[c.row][col][c.num] = false;
//            cout << c.row << col << c.num << '=' << false << endl;
            qCheck.push(Task(Cell(c.row, col, c.num), Task::ImpoCell));
        }
    }
    
    for ( size_t row = 0; row < Row; ++row) {
        if (possible[row][c.col][c.num]) {
            possible[row][c.col][c.num] = false;
//            cout << row << c.col << c.num << '=' << false << endl;
            qCheck.push(Task(Cell(row, c.col, c.num), Task::ImpoCell));
        }
    }
    
    for ( size_t row = c.row/RowInFloor*RowInFloor, _row_ = row+RowInFloor; row < _row_; ++row) {
        for ( size_t col = c.col/ColInTower*ColInTower, _col_ = col+ColInTower; col < _col_; ++col) {
            if (possible[row][col][c.num]) {
                possible[row][col][c.num] = false;
//                cout << row << col << c.num << '=' << false << endl;
                qCheck.push(Task(Cell(row, col, c.num), Task::ImpoCell));
            }
        }
    }

    for ( u_short num = 1; num < NumberRange; ++num) {
        if (possible[c.row][c.col][num]) {
            possible[c.row][c.col][num] = false;
//            cout << c.row << c.col << num << '=' << false << endl;
            qCheck.push(Task(Cell(c.row, c.col, num), Task::ImpoCell));
        }
    }
    possible[c.row][c.col][c.num] = true; 
//    cout << c.row << c.col << c.num << '=' << true << endl;
//    cout < *this;
}

void SudokuSolver::CheckImpoCell(const Cell & c)
{
    if (++impossibility[c.row][c.col] == NumberRange-2 && map[c.row][c.col] == 0) {
        for ( u_short num = 1; num < NumberRange; ++num) {
            if (possible[c.row][c.col][num]) {
//                cout << c.row << c.col << '=' << num << endl;
                qFill.push(Cell(c.row, c.col, num));
                break;
            }
        }
    } else if (impossibility[c.row][c.col] == NumberRange-1) {
        status = Paradoxical;
//        cout << "status=P" << endl;
        return;
    }
    if (++rowImpossibility[c.row][c.num] == NumberRange-2) {
        for ( size_t col = 0; col < Col; ++col) {
            if (possible[c.row][col][c.num]) {
//                cout << c.row << col << '=' << c.num << endl;
                qFill.push(Cell(c.row, col, c.num));
                break;
            }
        }
    } else if (rowImpossibility[c.row][c.num] == NumberRange-1) {
        status = Paradoxical;
//        cout << "status=P" << endl;
        return;
    }
    if (++colImpossibility[c.col][c.num] == NumberRange-2) {
        for ( size_t row = 0; row < Row; ++row) {
            if (possible[row][c.col][c.num]) {
//                cout << row << c.col << '=' << c.num << endl;
                qFill.push(Cell(row, c.col, c.num));
                break;
            }
        }
    } else if (colImpossibility[c.col][c.num] == NumberRange-1) {
        status = Paradoxical;
//        cout << "status=P" << endl;
        return;
    }
    if (++blockImpossibility[c.row/RowInFloor][c.col/ColInTower][c.num] == NumberRange-2) {
       for ( size_t row = c.row/RowInFloor*RowInFloor, _row_ = row+RowInFloor; row < _row_; ++row) {
           for ( size_t col = c.col/ColInTower*ColInTower, _col_ = col+ColInTower; col < _col_; ++col) {
               if (possible[row][col][c.num]) {
//                   cout << row << col << '=' << c.num << endl;
                   qFill.push(Cell(row, col, c.num));
                   break;
               }
           }
       }
    } else if (blockImpossibility[c.row/RowInFloor][c.col/ColInTower][c.num] == NumberRange-1) {
        status = Paradoxical;
//        cout << "status=P" << endl;
        return;
    }
    if (++horGroupImpossibility[c.row][c.col/ColInTower][c.num] == ColInTower && horGroupPossible[c.row][c.col/ColInTower][c.num]) {
        horGroupPossible[c.row][c.col/ColInTower][c.num] = false;
//        cout << c.row << '[' << c.col/ColInTower << ']' << c.num << '=' << false << endl;
        qCheck.push(Task(Cell(c.row, c.col/ColInTower, c.num), Task::ImpoHorGroup));
    }
    if (++verGroupImpossibility[c.col][c.row/RowInFloor][c.num] == RowInFloor && verGroupPossible[c.col][c.row/RowInFloor][c.num]) {
        verGroupPossible[c.col][c.row/RowInFloor][c.num] = false;
//        cout << '[' << c.row/RowInFloor << ']' << c.col << c.num << '=' << false << endl;
        qCheck.push(Task(Cell(c.row/RowInFloor, c.col, c.num), Task::ImpoVerGroup));
    }
}

void SudokuSolver::CheckImpoHorGroup(const Cell & c)
{
    for ( size_t col = c.col*ColInTower, _col_ = col+ColInTower; col < _col_; ++col) {
        if (possible[c.row][col][c.num]) {
            possible[c.row][col][c.num] = false;
//            cout << c.row << col << c.num << '=' << false << endl;
            qCheck.push(Task(Cell(c.row, col, c.num), Task::ImpoCell));
        }
    }
    if (++floorGroup[c.row/RowInFloor][c.col][c.num] == RowInFloor-1) {
        for ( size_t row = c.row/RowInFloor*RowInFloor, _row_ = row+RowInFloor; row < _row_; ++row) {
            if (horGroupPossible[row][c.col][c.num]) {
//                cout << row << '[' << c.col << ']' << c.num << '=' << true << endl;
                qCheck.push(Task(Cell(row, c.col, c.num), Task::KnownHorGroup));
                break;
            }
        }
    }
    if (++rowGroup[c.row][c.num] == Tower-1) {
        for ( size_t col = 0; col < Tower; ++col) {
            if (horGroupPossible[c.row][col][c.num]) {
//                cout << c.row << '[' << col << ']' << c.num << '=' << true << endl;
                qCheck.push(Task(Cell(c.row, col, c.num), Task::KnownHorGroup));
                break;
            }
        }
    }
}

void SudokuSolver::CheckImpoVerGroup(const Cell & c)
{
    for ( size_t row = c.row*RowInFloor, _row_ = row+RowInFloor; row < _row_; ++row) {
        if (possible[row][c.col][c.num]) {
            possible[row][c.col][c.num] = false;
//            cout << row << c.col << c.num << '=' << false << endl;
            qCheck.push(Task(Cell(row, c.col, c.num), Task::ImpoCell));
        }
    }
    if (++towerGroup[c.col/ColInTower][c.row][c.num] == ColInTower-1) {
        for ( size_t col = c.col/ColInTower*ColInTower, _col_ = col+ColInTower; col < _col_; ++col) {
            if (verGroupPossible[col][c.row][c.num]) {
//                cout << '[' << c.row << ']' << col << c.num << '=' << true << endl;
                qCheck.push(Task(Cell(c.row, col, c.num), Task::KnownVerGroup));
                break;
            }
        }
    }
    if (++colGroup[c.col][c.num] == Floor-1) {
        for ( size_t row = 0; row < Floor; ++row) {
            if (verGroupPossible[c.col][row][c.num]) {
//                cout << '[' << row << ']' << c.col << c.num << '=' << true << endl;
                qCheck.push(Task(Cell(row, c.col, c.num), Task::KnownVerGroup));
                break;
            }
        }
    }
}


void SudokuSolver::CheckKnownHorGroup(const Cell & c)
{
    horGroupPossible[c.row][c.col][c.num] = false;
    for ( size_t row = c.row/RowInFloor*RowInFloor, _row_ = row+RowInFloor; row < _row_; ++row) {
        if (horGroupPossible[row][c.col][c.num]) {
            horGroupPossible[row][c.col][c.num] = false;
//            cout << row << '[' << c.col << ']' << c.num << '=' << false << endl;
            qCheck.push(Task(Cell(row, c.col, c.num), Task::ImpoHorGroup));
        }
    }
    for ( size_t col = 0; col < Tower; ++col) {
        if (horGroupPossible[c.row][col][c.num]) {
            horGroupPossible[c.row][col][c.num] = false;
//            cout << c.row << '[' << col << ']' << c.num << '=' << false << endl;
            qCheck.push(Task(Cell(c.row, col, c.num), Task::ImpoHorGroup));
        }
    }
    horGroupPossible[c.row][c.col][c.num] = true;
}
void SudokuSolver::CheckKnownVerGroup(const Cell & c)
{
    verGroupPossible[c.col][c.row][c.num] = false;
    for ( size_t col = c.col/ColInTower*ColInTower, _col_ = col+ColInTower; col < _col_; ++col) {
        if (verGroupPossible[col][c.row][c.num]) {
            verGroupPossible[col][c.row][c.num] = false;
//            cout << '[' << c.row << ']' << col << c.num << '=' << false << endl;
            qCheck.push(Task(Cell(c.row, col, c.num), Task::ImpoVerGroup));
        }
    }
    for ( size_t row = 0; row < Floor; ++row) {
        if (verGroupPossible[c.col][row][c.num]) {
            verGroupPossible[c.col][row][c.num] = false;
//            cout << '[' << row << ']' << c.col << c.num << '=' << false << endl;
            qCheck.push(Task(Cell(row, c.col, c.num), Task::ImpoVerGroup));
        }
    }
    verGroupPossible[c.col][c.row][c.num] = true;
}



ostream & operator<(ostream &os, const SudokuSolver &s)
{
    SudokuSolver::u_short floor, row, tower, col, horn, vern;
    for ( floor = 0; floor < SudokuSolver::Floor; ++floor) {
        for ( row = 0; row < SudokuSolver::RowInFloor; ++row) {
            for ( horn = 0; horn < SudokuSolver::Order; ++horn) {
                for ( tower = 0; tower < SudokuSolver::Tower; ++tower) {
                    for ( col = 0; col < SudokuSolver::ColInTower; ++col) {
                        for ( vern = 0; vern < SudokuSolver::Order; ++vern) {
                            if (s.possible[floor*SudokuSolver::RowInFloor+row][tower*SudokuSolver::ColInTower+col][horn*SudokuSolver::Order+vern+1]) {
                                os << setw(2) << horn*SudokuSolver::Order+vern+1;
                            } else {
                                os << "  ";
                            }
                        }
                        os << " ";
                    }
                    if (tower != 2) {
                        os << "|";
                    }
                }
                os << endl;
            }
            if (row+SudokuSolver::RowInFloor*floor != 8) {
                if (row == 2) {
                    os << "---------------------+---------------------+---------------------" << endl;
                } else {
                    os << "                     |                     |                     " << endl;
                }
            }
        }
    }
    os << endl;
    return os;
}

void SudokuSolver::Solve(const SudokuBase &s)
{
    Reset();
    for ( size_t row = 0; row < Row; ++row) {
        for ( size_t col = 0; col < Col; ++col) {
            if (s.GetNumber(row, col)) {
                FillNotChange(Cell(row, col, s.GetNumber(row, col)));
                if (status == Paradoxical) {
                    return;
                }
            }
        }
    }
    Test();
}

void SudokuSolver::GetAnAnswer()
{
    if (status != Empty && status != NotEmpty) {
        return;
    }
    do {
        Cell c = MinPossibilityCell();
        vector<u_short> possibleNumber;
        for ( c.num = 1; c.num < NumberRange; ++c.num) {
            if (possible[c.row][c.col][c.num]) {
                possibleNumber.push_back(c.num);
            }
        }
        while (!possibleNumber.empty()) {
            u_short randIndex = rand()%possibleNumber.size();
            c.num = possibleNumber[randIndex];
            possibleNumber.erase(possibleNumber.begin()+randIndex);
            SudokuSolver t(*this);
            t.Fill(c);
            if (t.status != Paradoxical) {
                Copy(t);
                break;
            }
        } 
    } while (status == NotEmpty);
}

SudokuSolver::Status SudokuSolver::GetStatus() const
{
    return status;
}
