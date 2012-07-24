#ifndef SUDOKU_FRAME_H
#define SUDOKU_FRAME_H

#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/menu.h>
#include <wx/gdicmn.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/statusbr.h>
#include <wx/panel.h>
#include <wx/sizer.h>
#include <wx/frame.h>
#include <wx/filedlg.h>
#include <wx/aboutdlg.h>
#include <algorithm>
#include <fstream>
#include "WorkingPanel.h"

#define wxID_NEWGAME 1000
#define wxID_NEWGOAL 1001
#define wxID_FILL 1002
#define wxID_PLAY 1003
#define wxID_DESIGN 1004
#define wxID_EASY 1005
#define wxID_NORMAL 1006
#define wxID_HARD 1007

class SudokuFrame : public wxFrame 
{
    friend class WorkingPanel;
protected:
    wxMenu* gameMenu;
    wxMenu* editMenu;
    wxMenu* settingMenu;
    wxMenu* helpMenu;
    wxStatusBar* statusBar;
    WorkingPanel * workingPanel;

    void OnNewGame(wxCommandEvent & WXUNUSED(event));
    void OnSaveGame(wxCommandEvent & WXUNUSED(event));
    void OnOpenGame(wxCommandEvent & WXUNUSED(event));
    void OnExitGame(wxCommandEvent & WXUNUSED(event));
    void OnUndo(wxCommandEvent & WXUNUSED(event));
    void OnRedo(wxCommandEvent & WXUNUSED(event));
    void OnReset(wxCommandEvent & WXUNUSED(event));
    void OnNewGoal(wxCommandEvent & WXUNUSED(event));
    void OnFill(wxCommandEvent & WXUNUSED(event));
    void OnClear(wxCommandEvent & WXUNUSED(event));
    void OnPlay(wxCommandEvent & WXUNUSED(event));
    void OnDesign(wxCommandEvent & WXUNUSED(event));
    void OnAbout(wxCommandEvent & WXUNUSED(event));
    void OnSize(wxSizeEvent & WXUNUSED(event));

    void NewGame();
    void Record();
    void ClearRecord();
    stack<SudokuBase> undo;
    stack<SudokuBase> redo;
    wxMenuBar* menuBar;

public:
    
    SudokuFrame( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Sudoku Puzzle"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 600,625), long style = wxDEFAULT_FRAME_STYLE|wxFULL_REPAINT_ON_RESIZE|wxTAB_TRAVERSAL|wxWANTS_CHARS );
    ~SudokuFrame();
};

#endif //SUDOKU_FRAME_H

