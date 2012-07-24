#ifndef  WORKINGPANEL_H
#define  WORKINGPANEL_H

#include <wx/panel.h>
#include <wx/font.h>
#include <wx/dcclient.h>
#include <wx/string.h>
#include <wx/stattext.h>
#include <wx/msgdlg.h>
#include <wx/window.h>
#include <stack>
#include "Cell.h"
#include "SudokuBase.h"
#include "Sudoku.h"
#include "SudokuSolver.h"
#include "SudokuMaker.h"

class WorkingPanel : public wxPanel
{
    friend class SudokuFrame;
protected:
    Cell focusCell;
    wxFont font;
    wxCoord x0, y0, cellLen;
    wxWindow * myParent;

    void OnPaint(wxPaintEvent & e);
    void OnLeftDown(wxMouseEvent & e);
    void OnKeyDown(wxKeyEvent & e);
    void OnSize(wxSizeEvent & e);

    void Paint();
    Sudoku sdk;
    SudokuSolver sdks;
    SudokuMaker sdkm;
    bool fixed[SudokuBase::Row][SudokuBase::Col];
public:
    WorkingPanel(wxWindow* parent);
};

#endif  /*WORKINGPANEL_H*/
