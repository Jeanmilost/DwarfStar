#ifndef MainH
#define MainH

// vcl
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Buttons.hpp>

// dwarfstar engine
#include "DWF_Main_Engine.h"

class TMainForm : public TForm
{
    __published:
        TPanel *paView;
        TPanel *paToolbar;
        TBitBtn *btFiles;

        void __fastcall FormCreate(TObject* pSender);
        void __fastcall paViewResize(TObject* pSender);

    public:
        /**
        * Constructor
        *@param pOwner - form owner
        */
        __fastcall TMainForm(TComponent* pOwner);

        __fastcall ~TMainForm();

    protected:
        /**
        * View panel main procedure
        *@param message- Windows procedure message
        */
        void __fastcall ViewWndProc(TMessage& message);

    private:
        DWF_Main::DWF_Engine m_Engine;
        TWndMethod           m_fViewWndProc_Backup;

        /**
        * Called when thread do nothing else
        *@param pSender - event sender
        *@param[in, out] done - if true, idle loop was ternimated and may do nothing else
        */
        void __fastcall IdleLoop(TObject* pSender, bool& done);

        /**
        * Process the drawing
        */
        void Draw();
};
extern PACKAGE TMainForm* MainForm;
#endif
