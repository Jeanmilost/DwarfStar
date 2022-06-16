#include <vcl.h>
#pragma hdrstop
#include "Main.h"

#pragma package(smart_init)
#pragma resource "*.dfm"

//---------------------------------------------------------------------------
TMainForm* MainForm;
//---------------------------------------------------------------------------
__fastcall TMainForm::TMainForm(TComponent* pOwner) :
    TForm(pOwner),
    m_fViewWndProc_Backup(NULL)
{}
//---------------------------------------------------------------------------
__fastcall TMainForm::~TMainForm()
{
    // restore the normal view procedure
    if (m_fViewWndProc_Backup)
        paView->WindowProc = m_fViewWndProc_Backup;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::FormCreate(TObject* pSender)
{
    // start up the engine
    if (!m_Engine.Startup(paView->Handle,
                          DWF_Main::DWF_Engine::IE_GA_OpenGL,
                          paView->ClientWidth,
                          paView->ClientHeight))
    {
        MessageDlg("The DwarfStar engine could not be initialized.\r\n\r\nApplication will close.",
                   mtError,
                   TMsgDlgButtons() << mbOK,
                   0);

        Application->Terminate();
        return;
    }

    // FIXME do that better
    m_Engine.CreateLevel();

    // hook the panel procedure
    m_fViewWndProc_Backup = paView->WindowProc;
    paView->WindowProc    = ViewWndProc;

    // from now, OpenGL will draw scene every time the thread do nothing else
    Application->OnIdle = IdleLoop;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::paViewResize(TObject* pSender)
{
    m_Engine.Resize(paView->ClientWidth, paView->ClientHeight);
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::ViewWndProc(TMessage& message)
{
    switch (message.Msg)
    {
        case WM_WINDOWPOSCHANGED:
        {
            if (m_fViewWndProc_Backup)
                m_fViewWndProc_Backup(message);

            // redraw here, thus the view will be redrawn to the correct size in real time while the
            // size changes
            Draw();
            return;
        }

        case WM_PAINT:
        {
            if (m_fViewWndProc_Backup)
                m_fViewWndProc_Backup(message);

            Draw();
            return;
        }
    }

    if (m_fViewWndProc_Backup)
        m_fViewWndProc_Backup(message);
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::IdleLoop(TObject* pSender, bool& done)
{
    done = false;
    Draw();
}
//---------------------------------------------------------------------------
void TMainForm::Draw()
{
    m_Engine.Draw();
}
//---------------------------------------------------------------------------
