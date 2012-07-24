#include "WorkingPanel.h"
#include "SudokuFrame.h"

WorkingPanel::WorkingPanel(wxWindow* parent) : wxPanel(parent, wxID_ANY, wxPoint(0,0), wxSize(600,600))
{
    myParent = parent;
    wxSystemSettings sysset;
    font = sysset.GetFont(wxSYS_DEFAULT_GUI_FONT);
    memset(fixed, false, sizeof(fixed));

    focusCell.row = 4;
    focusCell.col = 4;
    Connect(wxEVT_PAINT, wxPaintEventHandler(WorkingPanel::OnPaint));
    Connect(wxEVT_LEFT_DOWN, wxMouseEventHandler(WorkingPanel::OnLeftDown));
    Connect(wxEVT_KEY_DOWN, wxKeyEventHandler(WorkingPanel::OnKeyDown));
    Connect(wxEVT_SIZE, wxSizeEventHandler(WorkingPanel::OnSize));
    SetFocus();
}

void WorkingPanel::OnSize(wxSizeEvent & e)
{
    Paint();
}

void WorkingPanel::OnPaint(wxPaintEvent & e)
{
    Paint();
}

void WorkingPanel::Paint()
{
    wxPaintDC dc(this);
    dc.Clear();
    wxCoord x9, y9;
    wxSize sz = GetClientSize();
    wxCoord minLen;
    minLen = min(sz.GetHeight(), sz.GetWidth());
    cellLen = (minLen - 22) / 9;
    x0 = (sz.GetWidth() - 22 - cellLen*9) / 2;
    y0 = (sz.GetHeight() -22 - cellLen*9) / 2;
    x9 = x0 + 21 + cellLen*9;
    y9 = y0 + 21 + cellLen*9;
    for ( wxCoord x = 0; x < 5; ++x) {
        dc.DrawLine(x0+x,y0,x0+x,y9);
        dc.DrawLine(x9-x,y0,x9-x,y9);
    }
    for ( wxCoord y = 0; y < 5; ++y) {
        dc.DrawLine(x0,y0+y,x9,y0+y);
        dc.DrawLine(x0,y9-y,x9,y9-y);
    }
    dc.DrawLine(x0+cellLen+5, y0, x0+cellLen+5, y9);
    dc.DrawLine(x0+cellLen*2+6, y0, x0+cellLen*2+6, y9);
    dc.DrawLine(x0+cellLen*3+7, y0, x0+cellLen*3+7, y9);
    dc.DrawLine(x0+cellLen*3+8, y0, x0+cellLen*3+8, y9);
    dc.DrawLine(x0+cellLen*3+9, y0, x0+cellLen*3+9, y9);
    dc.DrawLine(x0+cellLen*4+10, y0, x0+cellLen*4+10, y9);
    dc.DrawLine(x0+cellLen*5+11, y0, x0+cellLen*5+11, y9);
    dc.DrawLine(x0+cellLen*6+12, y0, x0+cellLen*6+12, y9);
    dc.DrawLine(x0+cellLen*6+13, y0, x0+cellLen*6+13, y9);
    dc.DrawLine(x0+cellLen*6+14, y0, x0+cellLen*6+14, y9);
    dc.DrawLine(x0+cellLen*7+15, y0, x0+cellLen*7+15, y9);
    dc.DrawLine(x0+cellLen*8+16, y0, x0+cellLen*8+16, y9);
    dc.DrawLine(x0, y0+cellLen+5, x9, y0+cellLen+5);
    dc.DrawLine(x0, y0+cellLen*2+6, x9, y0+cellLen*2+6);
    dc.DrawLine(x0, y0+cellLen*3+7, x9, y0+cellLen*3+7);
    dc.DrawLine(x0, y0+cellLen*3+8, x9, y0+cellLen*3+8);
    dc.DrawLine(x0, y0+cellLen*3+9, x9, y0+cellLen*3+9);
    dc.DrawLine(x0, y0+cellLen*4+10, x9, y0+cellLen*4+10);
    dc.DrawLine(x0, y0+cellLen*5+11, x9, y0+cellLen*5+11);
    dc.DrawLine(x0, y0+cellLen*6+12, x9, y0+cellLen*6+12);
    dc.DrawLine(x0, y0+cellLen*6+13, x9, y0+cellLen*6+13);
    dc.DrawLine(x0, y0+cellLen*6+14, x9, y0+cellLen*6+14);
    dc.DrawLine(x0, y0+cellLen*7+15, x9, y0+cellLen*7+15);
    dc.DrawLine(x0, y0+cellLen*8+16, x9, y0+cellLen*8+16);
    wxCoord cx;
    wxCoord cy;
    wxString s;
    font.SetPixelSize(wxSize(0, cellLen));
    dc.SetFont(font);
    for ( size_t row = 0; row < SudokuBase::Row; ++row) {
        cy = y0+5+row*cellLen+row+row/3*2;
        for ( size_t col = 0; col < SudokuBase::Col; ++col) {
            if (fixed[row][col]) {
                dc.SetBrush(*wxLIGHT_GREY_BRUSH);
            } else {
                dc.SetBrush(*wxTRANSPARENT_BRUSH);
            }
            dc.SetPen(wxPen(wxColor(0,0,0), 0));
            cx = x0+5+col*cellLen+col+col/3*2;
            dc.DrawRectangle(cx, cy, cellLen, cellLen);
            if (sdk.GetNumber(row, col) != 0) {
                s.Printf(wxT("%d"), sdk.GetNumber(row, col));
                cx = x0+5+col*cellLen+col+col/3*2+(cellLen-dc.GetTextExtent(s).GetWidth())/2;
                dc.DrawText(s, cx, cy);
            }
        }
    }
    cx = x0+5+focusCell.col*cellLen+focusCell.col+focusCell.col/3*2;
    cy = y0+5+focusCell.row*cellLen+focusCell.row+focusCell.row/3*2;
    dc.DrawLine(cx+1,cy+1,cx+cellLen-2,cy+1);
    dc.DrawLine(cx+2,cy+2,cx+cellLen-3,cy+2);
    dc.DrawLine(cx+1,cy+1,cx+1,cy+cellLen-2);
    dc.DrawLine(cx+2,cy+2,cx+2,cy+cellLen-3);
    dc.DrawLine(cx+cellLen-2,cy+1,cx+cellLen-2,cy+cellLen-1);
    dc.DrawLine(cx+cellLen-3,cy+2,cx+cellLen-3,cy+cellLen-2);
    dc.DrawLine(cx+1,cy+cellLen-2,cx+cellLen-1,cy+cellLen-2);
    dc.DrawLine(cx+2,cy+cellLen-3,cx+cellLen-2,cy+cellLen-3);
}

void WorkingPanel::OnLeftDown(wxMouseEvent & e)
{
    SetFocus();
    wxPaintDC dc(this);
    wxPoint point = e.GetLogicalPosition(dc);
    if (point.x < x0+5 || point.y < y0+5) {
        return;
    }
    Cell tempCell;
    tempCell.row = (point.y - y0 - 5)/cellLen;
    tempCell.col = (point.x - x0 - 5)/cellLen;
    if (x0+5+tempCell.col*cellLen+tempCell.col+tempCell.col/3*2 > point.x) {
        --tempCell.col;
    }
    if (y0+5+tempCell.row*cellLen+tempCell.row+tempCell.row/3*2 > point.y) {
        --tempCell.row;
    }
    if (tempCell.row < SudokuBase::Row && tempCell.col < SudokuBase::Col) {
        focusCell = tempCell;
    }
    Paint();
}

void WorkingPanel::OnKeyDown(wxKeyEvent & e)
{
    int kc = e.GetKeyCode();
    switch (kc) {
    case WXK_LEFT :
        focusCell.col = (focusCell.col?focusCell.col:SudokuBase::Col)-1;
        break;
    case WXK_RIGHT :
        focusCell.col = (focusCell.col+1)%SudokuBase::Col;
        break;
    case WXK_UP :
        focusCell.row = (focusCell.row?focusCell.row:SudokuBase::Row)-1;
        break;
    case WXK_DOWN :
        focusCell.row = (focusCell.row+1)%SudokuBase::Row;
        break;
    default :
        if (fixed[focusCell.row][focusCell.col] == false) {
            if (WXK_NUMPAD0 <= kc && kc <= WXK_NUMPAD9) {
                focusCell.num = kc-WXK_NUMPAD0;
            } else if ('0' <= kc && kc <= '9') {
                focusCell.num = kc-'0';
            } else {
                break;
            }
            static_cast<SudokuFrame*>(myParent)->Record();
            sdk.Fill(focusCell);
            if (static_cast<SudokuFrame*>(myParent)->menuBar->IsChecked(wxID_PLAY)) {
                if (sdk.GetStatus() == Sudoku::Paradoxical) {
                    static_cast<SudokuFrame*>(myParent)->SetStatusText(wxT("Paradoxical"));
                } else {
                    static_cast<SudokuFrame*>(myParent)->SetStatusText(wxT(""));
                    if (sdk.GetStatus() == Sudoku::Full) {
                        sdks.Solve(sdk);
                        if (sdks.GetStatus() != Sudoku::Paradoxical) {
                            wxMessageDialog mdl(this, wxT("Congratulation! You win!"));
                            mdl.ShowModal();
                        }
                    }
                }
            } else {
                sdks.Solve(sdk);
                switch (sdks.GetStatus()) {
                case SudokuSolver::Paradoxical :
                    static_cast<SudokuFrame*>(myParent)->SetStatusText(wxT("Paradoxical"));
                    break;
                case SudokuSolver::NotEmpty :
                    static_cast<SudokuFrame*>(myParent)->SetStatusText(wxT("Not unique"));
                    break;
                case SudokuSolver::Full :
                    static_cast<SudokuFrame*>(myParent)->SetStatusText(wxT("Effictive"));
                    break;
                case SudokuSolver::Empty :
                    static_cast<SudokuFrame*>(myParent)->SetStatusText(wxT("Empty"));
                    break;
                default :
                    static_cast<SudokuFrame*>(myParent)->SetStatusText(wxT("Unknow"));
                    break;
                }
            }
        } 
        break;
    }
    Paint();
}

