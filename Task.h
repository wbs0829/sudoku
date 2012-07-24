#ifndef SUDOKU_TASK_H
#define SUDOKU_TASK_H

#include "Cell.h"

/*
 * The members, row and col, in Cell have more meaning when in Task.
 */
class Task : public Cell
{
public:
    enum Information{ ImpoCell, ImpoHorGroup, ImpoVerGroup, KnownHorGroup, KnownVerGroup};
    Information info;
    Task(const Cell &r, Information i) : info(i) {row = r.row; col = r.col; num = r.num; }
};
#endif
