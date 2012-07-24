#include <wx/wx.h>
#include "SudokuFrame.h"

class SudokuApp : public wxApp
{
public:
    virtual bool OnInit();
};

IMPLEMENT_APP(SudokuApp)

bool SudokuApp::OnInit()
{
    SudokuFrame * sdkFrame = new SudokuFrame(NULL);
    sdkFrame->Show(true);
    return true;
}
