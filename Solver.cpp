#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include "SudokuBase.h"
#include "SudokuSolver.h"
#include "Sudoku.h"

using namespace std;

void working(istream *in)
{
    Sudoku sin;
    SudokuSolver sdk;
    int c;
//    while (1) {
//        sin.Reset();
    for (unsigned short i = 0; i < SudokuBase::CellAmount; i++) {
        if ( (c = in->get()) == -1) {
            cerr << "Sudoku is incomplete." << endl;
            exit(2);
        } else {
            c -= '0';
            if ( 0 <= c && c < SudokuBase::NumberRange) {
                if (c != 0) {
                    sin.Fill(Cell(i/SudokuBase::Col,i%SudokuBase::Col,c));
                }
            } else {
                --i;
            }
        }
    }
    sdk.Solve(sin);
    switch (sdk.GetStatus()) {
    case SudokuBase::Paradoxical :
        cerr << "Sudoku is paradoxical." << endl;
        break;
    case SudokuBase::NotEmpty :
        cerr << "Sudoku is not unique." << endl;
        break;
    case SudokuBase::Empty :
        cerr << "Sudoku is empty." << endl;
        break;
    case SudokuBase::Full :
        cout << sdk;
        break;
    default :
        cerr << "Unknown status." << endl;
    }
//    }
}
int main(int argc, char *argv[])
{
    clock_t t0 = clock();
    ifstream fin;
    istream * in;
    bool _t = false;
    bool open_file = false;
    for ( int i = 1; i < argc; ++i) {
        if (*(argv[i]) != '-') {
            fin.open(argv[i]);
            if ( fin.fail()) {
                cerr << "Fail to open the file" << endl;
                return 1;
            }
            in = dynamic_cast<istream*>(&fin);
            open_file = true;
        } else if (strcmp("-t", argv[i]) == 0) {
            _t = true;
        }
    }
    if (!open_file){
        in = &cin;
    }
    working(in);
    if (open_file) {
        fin.close();
    }
    if (_t) {
       cout << "Time:" << (clock()-t0)*1000/CLOCKS_PER_SEC << "ms" << endl;
    }
    return 0;
}
