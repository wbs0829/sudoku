#include "SudokuFrame.h"

SudokuFrame::SudokuFrame( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	menuBar = new wxMenuBar( 0 );
	gameMenu = new wxMenu();
	wxMenuItem* newGameMenuItem;
	newGameMenuItem = new wxMenuItem( gameMenu, wxID_NEWGAME, wxString( wxT("&New Game") ) + wxT('\t') + wxT("ctrl+n"), wxEmptyString, wxITEM_NORMAL );
	gameMenu->Append( newGameMenuItem );
	
	wxMenuItem* openMenuItem;
	openMenuItem = new wxMenuItem( gameMenu, wxID_OPEN, wxString( wxT("&Open") ) + wxT('\t') + wxT("ctrl+o"), wxEmptyString, wxITEM_NORMAL );
	gameMenu->Append( openMenuItem );
	
	wxMenuItem* saveMenuItem;
	saveMenuItem = new wxMenuItem( gameMenu, wxID_SAVE, wxString( wxT("&Save") ) + wxT('\t') + wxT("ctrl+s"), wxEmptyString, wxITEM_NORMAL );
	gameMenu->Append( saveMenuItem );
	
	wxMenuItem* gameSeparator;
	gameSeparator = gameMenu->AppendSeparator();
	
	wxMenuItem* exitMenuItem;
	exitMenuItem = new wxMenuItem( gameMenu, wxID_EXIT, wxString( wxT("&Exit") ) + wxT('\t') + wxT("alt+f4"), wxEmptyString, wxITEM_NORMAL );
	gameMenu->Append( exitMenuItem );
	
	menuBar->Append( gameMenu, wxT("&Game") );
	
	editMenu = new wxMenu();
	wxMenuItem* undoMenuItem;
	undoMenuItem = new wxMenuItem( editMenu, wxID_UNDO, wxString( wxT("&Undo") ) + wxT('\t') + wxT("ctrl+z"), wxEmptyString, wxITEM_NORMAL );
	editMenu->Append( undoMenuItem );
	
	wxMenuItem* redoMenuItem;
	redoMenuItem = new wxMenuItem( editMenu, wxID_REDO, wxString( wxT("&Redo") ) + wxT('\t') + wxT("ctrl+y"), wxEmptyString, wxITEM_NORMAL );
	editMenu->Append( redoMenuItem );
	
	wxMenuItem* editSeparator;
	editSeparator = editMenu->AppendSeparator();
	
	wxMenuItem* resetMenuItem;
	resetMenuItem = new wxMenuItem( editMenu, wxID_RESET, wxString( wxT("Re&set") ) + wxT('\t') + wxT("ctrl+r"), wxEmptyString, wxITEM_NORMAL );
	editMenu->Append( resetMenuItem );
	
	wxMenuItem* newGoalMenuItem;
	newGoalMenuItem = new wxMenuItem( editMenu, wxID_NEWGOAL, wxString( wxT("&New Goal") ) + wxT('\t') + wxT("ctrl+g"), wxEmptyString, wxITEM_NORMAL );
	editMenu->Append( newGoalMenuItem );
	
	wxMenuItem* fillMenuItem;
	fillMenuItem = new wxMenuItem( editMenu, wxID_FILL, wxString( wxT("&Fill") ) + wxT('\t') + wxT("ctrl+f"), wxEmptyString, wxITEM_NORMAL );
	editMenu->Append( fillMenuItem );
	
	wxMenuItem* clearMenuItem;
	clearMenuItem = new wxMenuItem( editMenu, wxID_CLEAR, wxString( wxT("&Clear") ) + wxT('\t') + wxT("ctrl+c"), wxEmptyString, wxITEM_NORMAL );
	editMenu->Append( clearMenuItem );
	
	menuBar->Append( editMenu, wxT("&Edit") );

	settingMenu = new wxMenu();
	wxMenuItem* modeMenuItem;
	modeMenuItem = new wxMenuItem( settingMenu, wxID_ANY, wxString( wxT("----------Mode----------") ) , wxEmptyString, wxITEM_NORMAL );
	settingMenu->Append( modeMenuItem );
	modeMenuItem->Enable( false );
	
	wxMenuItem* playMenuItem;
	playMenuItem = new wxMenuItem( settingMenu, wxID_PLAY, wxString( wxT("&Play") ) , wxEmptyString, wxITEM_RADIO );
	settingMenu->Append( playMenuItem );
	
	wxMenuItem* designMenuItem;
	designMenuItem = new wxMenuItem( settingMenu, wxID_DESIGN, wxString( wxT("&Design") ) , wxEmptyString, wxITEM_RADIO );
	settingMenu->Append( designMenuItem );
	
	wxMenuItem* settingSeparator;
	settingSeparator = settingMenu->AppendSeparator();
	
	wxMenuItem* difficultyMenuItem;
	difficultyMenuItem = new wxMenuItem( settingMenu, wxID_ANY, wxString( wxT("-------Difficulty-------") ) , wxEmptyString, wxITEM_NORMAL );
	settingMenu->Append( difficultyMenuItem );
	difficultyMenuItem->Enable( false );
	
	wxMenuItem* easyMenuItem;
	easyMenuItem = new wxMenuItem( settingMenu, wxID_EASY, wxString( wxT("&Easy") ) , wxEmptyString, wxITEM_RADIO );
	settingMenu->Append( easyMenuItem );
	
	wxMenuItem* normalMenuItem;
	normalMenuItem = new wxMenuItem( settingMenu, wxID_NORMAL, wxString( wxT("&Normal") ) , wxEmptyString, wxITEM_RADIO );
	settingMenu->Append( normalMenuItem );
	
	wxMenuItem* hardMenuItem;
	hardMenuItem = new wxMenuItem( settingMenu, wxID_HARD, wxString( wxT("&Hard") ) , wxEmptyString, wxITEM_RADIO );
	settingMenu->Append( hardMenuItem );
	
	menuBar->Append( settingMenu, wxT("&Setting") );
	
	helpMenu = new wxMenu();
	wxMenuItem* aboutMenuItem;
	aboutMenuItem = new wxMenuItem( helpMenu, wxID_HELP, wxString( wxT("&About") ) + wxT('\t') + wxT("F1"), wxEmptyString, wxITEM_NORMAL );
	helpMenu->Append( aboutMenuItem );
	
	menuBar->Append( helpMenu, wxT("&Help") );
	
	this->SetMenuBar( menuBar );
	
	statusBar = this->CreateStatusBar( 1, wxST_SIZEGRIP, wxID_ANY );
	
    workingPanel = new WorkingPanel(this);

    //wxBoxSizer * mainbSizer;
    //mainbSizer = new wxBoxSizer(wxVERTICAL);
    //mainbSizer->Add(workingPanel, 1, wxEXPAND | wxALL, 5);

    //this->SetSizer(mainbSizer);
    //this->Layout();

    editMenu->Enable(wxID_RESET, true);
    editMenu->Enable(wxID_NEWGOAL, false);
    editMenu->Enable(wxID_FILL, false);
    editMenu->Enable(wxID_CLEAR, false);
    editMenu->Enable(wxID_UNDO, false);
    editMenu->Enable(wxID_REDO, false);

    Connect(wxID_HELP, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(SudokuFrame::OnAbout));
    Connect(wxEVT_SIZE, wxSizeEventHandler(SudokuFrame::OnSize));
    Connect(wxID_NEWGAME, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(SudokuFrame::OnNewGame));
    Connect(wxID_EXIT, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(SudokuFrame::OnExitGame));
    Connect(wxID_RESET, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(SudokuFrame::OnReset));
    Connect(wxID_NEWGOAL, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(SudokuFrame::OnNewGoal));
    Connect(wxID_FILL, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(SudokuFrame::OnFill));
    Connect(wxID_CLEAR, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(SudokuFrame::OnClear));
    Connect(wxID_PLAY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(SudokuFrame::OnPlay));
    Connect(wxID_DESIGN, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(SudokuFrame::OnDesign));
    Connect(wxID_SAVE, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(SudokuFrame::OnSaveGame));
    Connect(wxID_OPEN, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(SudokuFrame::OnOpenGame));
    Connect(wxID_UNDO, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(SudokuFrame::OnUndo));
    Connect(wxID_REDO, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(SudokuFrame::OnRedo));
}

SudokuFrame::~SudokuFrame()
{
}

void SudokuFrame::OnAbout(wxCommandEvent & WXUNUSED(event))
{
    wxAboutDialogInfo info;
    info.SetName(wxT("Sudoku"));
    info.SetVersion(wxT("1.0 Beta"));
    info.SetDescription(wxT("Sudoku can generate puzzles and help you generate puzzles."));
    info.SetCopyright(wxT("(C) 2012 MonoAmber <wbs.y829@gmail.com>"));

    wxAboutBox(info);
}

void SudokuFrame::OnSize(wxSizeEvent & WXUNUSED(event))
{
    wxSize size = GetClientSize();
    workingPanel->SetSize(0,0,size.x,size.y);
}

void SudokuFrame::OnNewGame(wxCommandEvent & WXUNUSED(event))
{
    NewGame();
}

void SudokuFrame::NewGame()
{
    u_short dfclt;
    if (settingMenu->IsChecked(wxID_EASY)) {
        dfclt = 40;
    } else if (settingMenu->IsChecked(wxID_NORMAL)) {
        dfclt = 50;
    } else {
        dfclt = 81;
    }
    workingPanel->sdk.Reset();
    workingPanel->sdkm.Generate(workingPanel->sdk, dfclt);
    workingPanel->sdk = workingPanel->sdkm;
    for ( u_short row = 0; row < SudokuBase::Row; ++row) {
        for ( u_short col = 0; col < SudokuBase::Col; ++col) {
            if (workingPanel->sdk.GetNumber(row, col)) {
                workingPanel->fixed[row][col] = true;
            } else {
                workingPanel->fixed[row][col] = false;
            } 
        }
    }
    ClearRecord();
    workingPanel->Paint();
}

void SudokuFrame::OnExitGame(wxCommandEvent & WXUNUSED(event))
{
    Close(true);
}

void SudokuFrame::OnReset(wxCommandEvent & WXUNUSED(event))
{
    Record();
    for ( u_short row = 0; row < SudokuBase::Row; ++row) {
        for ( u_short col = 0; col < SudokuBase::Col; ++col) {
            if (!workingPanel->fixed[row][col]) {
                workingPanel->sdk.Fill(Cell(row, col, 0));
            }
        }
    }
    workingPanel->Paint();
}

void SudokuFrame::OnNewGoal(wxCommandEvent & WXUNUSED(event))
{
    Record();
    workingPanel->sdks.Solve(Sudoku());
    workingPanel->sdks.GetAnAnswer();
    workingPanel->sdk = workingPanel->sdks;
    workingPanel->Paint();
}

void SudokuFrame::OnFill(wxCommandEvent & WXUNUSED(event))
{
    Record();
    workingPanel->sdks.Solve(workingPanel->sdk);
    workingPanel->sdks.GetAnAnswer();
    workingPanel->sdk = workingPanel->sdks;
    workingPanel->Paint();
}

void SudokuFrame::OnClear(wxCommandEvent & WXUNUSED(event))
{
    Record();
    workingPanel->sdk.Reset();
    workingPanel->Paint();
}

void SudokuFrame::OnPlay(wxCommandEvent & WXUNUSED(event))
{
    wxMessageDialog msgdlg(this, wxT("Would you want to change mode"), wxT("Change Mode"), wxYES_NO|wxNO_DEFAULT);
    if (msgdlg.ShowModal() == wxID_NO) {
        settingMenu->Check(wxID_DESIGN, true);
        return;
    }
    gameMenu->Enable(wxID_NEWGAME, true);

    editMenu->Enable(wxID_RESET, true);
    editMenu->Enable(wxID_NEWGOAL, false);
    editMenu->Enable(wxID_FILL, false);
    editMenu->Enable(wxID_CLEAR, false);

    ClearRecord();
    NewGame();
}

void SudokuFrame::OnDesign(wxCommandEvent & WXUNUSED(event))
{
    wxMessageDialog msgdlg(this, wxT("Would you want to change mode"), wxT("Change Mode"), wxYES_NO|wxNO_DEFAULT);
    if (msgdlg.ShowModal() == wxID_NO) {
        settingMenu->Check(wxID_PLAY, true);
        return;
    }
    gameMenu->Enable(wxID_NEWGAME, false);

    editMenu->Enable(wxID_RESET, false);
    editMenu->Enable(wxID_NEWGOAL, true);
    editMenu->Enable(wxID_FILL, true);
    editMenu->Enable(wxID_CLEAR, true);

    memset(workingPanel->fixed, false, SudokuBase::CellAmount);
    ClearRecord();
    workingPanel->Paint();
}

void SudokuFrame::OnSaveGame(wxCommandEvent & WXUNUSED(event))
{
    wxFileDialog saveFileDialog(this, wxT("Save sudoku file"), wxT(""), wxT(""), wxT("Sudoku file (*.sdk)|*.sdk"), wxFD_SAVE);
    if (saveFileDialog.ShowModal() == wxID_CANCEL) {
        return;
    }
    wxString path = saveFileDialog.GetPath();
    if (path.Find('c') != wxNOT_FOUND) {
        path+=wxT(".sdk");
    }
    ofstream fout(path.fn_str());
    if (!fout) {
        wxMessageDialog(this, wxT("Can't write."), wxT("Error"), wxOK).ShowModal();
    }
    bool pl = settingMenu->IsChecked(wxID_PLAY);
    if (pl) {
        for ( u_short row = 0; row < SudokuBase::Row; ++row) {
            for ( u_short col = 0; col < SudokuBase::Col; ++col) {
                if (workingPanel->sdk.GetNumber(row, col)) {
                    fout << char(workingPanel->sdk.GetNumber(row, col)+(workingPanel->fixed[row][col]?'a'-1:'0'));
                } else {
                    fout << '0';
                }
            }
            fout << endl;
        }
    } else {
        for ( u_short row = 0; row < SudokuBase::Row; ++row) {
            for ( u_short col = 0; col < SudokuBase::Col; ++col) {
                if (workingPanel->sdk.GetNumber(row, col)) {
                    fout << char('a'-1+workingPanel->sdk.GetNumber(row, col));
                } else {
                    fout << '0';
                }
            }
            fout << endl;
        }
    }
    fout.close();
}

void SudokuFrame::OnOpenGame(wxCommandEvent & WXUNUSED(event))
{
    wxFileDialog openFileDialog(this, wxT("Open sudoku file"), wxT(""), wxT(""), wxT("Sudoku file (*.sdk)|*.sdk"), wxFD_OPEN|wxFD_FILE_MUST_EXIST);
    if (openFileDialog.ShowModal() == wxID_CANCEL) {
        return;
    }
    ifstream fin(openFileDialog.GetPath().fn_str());
    char c;
    bool pl = settingMenu->IsChecked(wxID_PLAY);
    Sudoku s;
    bool f[SudokuBase::Row][SudokuBase::Col] = {};
    for ( u_short i = 0; i < SudokuBase::CellAmount; ++i) {
        if (!fin.get(c)) {
            wxMessageDialog(this, wxT("Sudoku file is not full."), wxT("Error"), wxOK).ShowModal();
            return;
        }
        if ('0' <= c && c <= '9') {
            s.Fill(Cell(i/SudokuBase::Col, i%SudokuBase::Col, c - '0'));
        } else if ('a' <= c && c <= 'i') {
            s.Fill(Cell(i/SudokuBase::Col, i%SudokuBase::Col, c - 'a' + 1));
            if (pl) {
                f[i/SudokuBase::Col][i%SudokuBase::Col] = true;
            }
        } else {
            --i;
        }
    }
    workingPanel->sdk = s;
    memcpy(workingPanel->fixed, f, sizeof(f));
    fin.close();
    ClearRecord();
    workingPanel->Paint();
}

void SudokuFrame::Record()
{
    undo.push(workingPanel->sdk);
    redo = stack<SudokuBase>();
    editMenu->Enable(wxID_REDO, false);
    editMenu->Enable(wxID_UNDO, true);
}

void SudokuFrame::ClearRecord()
{
    undo = stack<SudokuBase>();
    editMenu->Enable(wxID_UNDO, false);
    redo = stack<SudokuBase>();
    editMenu->Enable(wxID_REDO, false);
}

void SudokuFrame::OnRedo(wxCommandEvent & WXUNUSED(event))
{
    undo.push(workingPanel->sdk);
    editMenu->Enable(wxID_UNDO, true);
    workingPanel->sdk = redo.top();
    redo.pop();
    if (redo.empty()) {
        editMenu->Enable(wxID_REDO, false);
    }
    SetStatusText(wxT(""));
    workingPanel->Paint();
}

void SudokuFrame::OnUndo(wxCommandEvent & WXUNUSED(event))
{
    redo.push(workingPanel->sdk);
    editMenu->Enable(wxID_REDO, true);
    workingPanel->sdk = undo.top();
    undo.pop();
    if (undo.empty()) {
        editMenu->Enable(wxID_UNDO, false);
    }
    SetStatusText(wxT(""));
    workingPanel->Paint(); 
}
