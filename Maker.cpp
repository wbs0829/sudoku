#include <iostream>
#include "SudokuSolver.h"
#include "SudokuMaker.h"

using namespace std;

int main()
{
    unsigned short l;
    cin >> l;
    srand(time(0));
    SudokuSolver sdks;
    sdks.GetAnAnswer();
    SudokuMaker sdkm;
    sdkm.Generate(sdks, l);
    cout << sdkm;
    return 0; 
}
