/****************************************************************************
 * ==> TMainForm -----------------------------------------------------------*
 ****************************************************************************
 * Description : This module provides the application main form             *
 * Developer   : Jean-Milost Reymond                                        *
 ****************************************************************************
 * MIT License - DwarfStar Engine                                           *
 *                                                                          *
 * Permission is hereby granted, free of charge, to any person obtaining a  *
 * copy of this software and associated documentation files (the            *
 * "Software"), to deal in the Software without restriction, including      *
 * without limitation the rights to use, copy, modify, merge, publish,      *
 * distribute, sublicense, and/or sell copies of the Software, and to       *
 * permit persons to whom the Software is furnished to do so, subject to    *
 * the following conditions:                                                *
 *                                                                          *
 * The above copyright notice and this permission notice shall be included  *
 * in all copies or substantial portions of the Software.                   *
 *                                                                          *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS  *
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF               *
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.   *
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY     *
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,     *
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE        *
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                   *
 ****************************************************************************/

#ifndef MainH
#define MainH

// vcl
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Menus.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <System.Actions.hpp>
#include <Vcl.ActnList.hpp>
#include <Vcl.AppEvnts.hpp>
#include <Vcl.ImgList.hpp>
#include <Vcl.Buttons.hpp>
#include <Vcl.Imaging.PngImage.hpp>
#include <Vcl.Dialogs.hpp>

// interface
#include "TGeometricDocument2D.h"
#include "TGeometricDocument3D.h"
#include "TGeometricSimulator.h"

/**
* Application main form
*@author Jean-Milost Reymond
*/
class TMainForm : public TForm
{
    __published:
        TMainMenu *mmMain;
        TMenuItem *miFile;
        TMenuItem *miFileNew;
        TMenuItem *mi2DDocument;
        TMenuItem *mi3DDocument;
        TPanel *paToolbar;
        TActionList *alActions;
        TAction *acAddCircle;
        TApplicationEvents *aeMainEvents;
        TMenuItem *miShapes;
        TMenuItem *miShapesAddCircle;
        TAction *acAddLine;
        TAction *acAddRay;
        TAction *acAddSegment;
        TAction *acAddPolygon;
        TAction *acAddRect;
        TMenuItem *miAddLine;
        TMenuItem *miAddRay;
        TMenuItem *miAddSegment;
        TMenuItem *miAddPolygon;
        TMenuItem *miAddRect;
        TImageList *ilShapeIcons;
        TTimer *tmSimulator;
        TPanel *paDocument2DButtons;
        TAction *acIntersectionMode;
        TAction *acInsideMode;
        TMenuItem *miSimulator;
        TMenuItem *miIntersectionMode;
        TMenuItem *miInsideMode;
        TAction *acSimulatorStop;
        TPanel *paSimulatorButtons;
        TSpeedButton *btAddRect;
        TSpeedButton *btAddCircle;
        TSpeedButton *btAddPolygon2D;
        TSpeedButton *btAddSegment2D;
        TSpeedButton *btAddRay2D;
        TSpeedButton *btAddLine2D;
        TSpeedButton *btIntersectionMode;
        TSpeedButton *btInsideMode;
        TSpeedButton *btSimulatorStop;
        TMenuItem *miSimulatorStop;
        TAction *acFileNewDoc2D;
        TAction *acFileNewDoc3D;
        TAction *acFileClose;
        TMenuItem *miFileClose;
        TAction *acFileOpen;
        TAction *acFileSave;
        TMenuItem *miFileOpen;
        TMenuItem *miFileSave;
        TAction *acFileQuit;
        TMenuItem *miFileQuit;
        TOpenDialog *odOpen;
        TSaveDialog *sdSave;
        TAction *acFileSaveAs;
        TMenuItem *miFileSaveAs;
        TPanel *paDocument3DButtons;
        TSpeedButton *btAddSphere;
        TAction *acAddSphere;
        TMenuItem *miAddSphere;
        TSpeedButton *btAddLine3D;
        TSpeedButton *btAddRay3D;
        TSpeedButton *btAddSegment3D;
        TSpeedButton *btAddPolygon3D;
        TPanel *paView;
        TSpeedButton *btAddPlane;
        TSpeedButton *btAddBox;
        TSpeedButton *btAddDisk;
        TSpeedButton *btAddCylinder;
        TAction *acAddPlane;
        TAction *acAddBox;
        TAction *acAddDisk;
        TAction *acAddCylinder;
        TMenuItem *miAddPlane;
        TMenuItem *miAddBox;
        TMenuItem *miAddDisk;
        TMenuItem *miAddCylinder;

        void __fastcall acFileNewDoc2DExecute(TObject* pSender);
        void __fastcall acFileNewDoc3DExecute(TObject* pSender);
        void __fastcall acFileOpenExecute(TObject* pSender);
        void __fastcall acFileSaveExecute(TObject* pSender);
        void __fastcall acFileSaveAsExecute(TObject* pSender);
        void __fastcall acFileCloseExecute(TObject* pSender);
        void __fastcall acFileQuitExecute(TObject* pSender);
        void __fastcall acAddLineExecute(TObject* pSender);
        void __fastcall acAddRayExecute(TObject* pSender);
        void __fastcall acAddSegmentExecute(TObject* pSender);
        void __fastcall acAddPlaneExecute(TObject* pSender);
        void __fastcall acAddPolygonExecute(TObject* pSender);
        void __fastcall acAddCircleExecute(TObject* pSender);
        void __fastcall acAddRectExecute(TObject* pSender);
        void __fastcall acAddSphereExecute(TObject* pSender);
        void __fastcall acAddBoxExecute(TObject* pSender);
        void __fastcall acAddDiskExecute(TObject* pSender);
        void __fastcall acAddCylinderExecute(TObject* pSender);
        void __fastcall acIntersectionModeExecute(TObject* pSender);
        void __fastcall acInsideModeExecute(TObject* pSender);
        void __fastcall acSimulatorStopExecute(TObject* pSender);
        void __fastcall tmSimulatorTimer(TObject* pSender);
        void __fastcall aeMainEventsMessage(tagMSG& msg, bool& handled);
        void __fastcall FormCreate(TObject* pSender);
        void __fastcall FormCloseQuery(TObject* pSender, bool& canClose);

    public:
        __fastcall TMainForm(TComponent* pOwner);
        virtual __fastcall ~TMainForm();

    protected:
        /**
        * View panel main procedure
        *@param message- Windows procedure message
        */
        void __fastcall ViewWndProc(TMessage& message);

    private:
        /**
        * Interface status
        */
        enum IEInterfaceStatus
        {
            IE_IS_DocumentClosed,
            IE_IS_DocumentOpened,
            IE_IS_Sim_Inside_Mode,
            IE_IS_Sim_Intersect_Mode,
        };

        typedef std::vector<TControl*> IControls;

        TGeometricDocument* m_pGeometricDocument;
        TGeometricSimulator m_GeometricSimulator;
        TCanvas*            m_pDocCanvas;
        TBitmap*            m_pOverlay;
        IEInterfaceStatus   m_Status;
        std::wstring        m_FileName;
        bool                m_Editing;
        TWndMethod          m_fViewWndProc_Backup;

        /**
        * Updates the inteface status
        */
        void UpdateInterface();

        /**
        * Opens the document
        *@return true on success, otherwise false
        */
        bool OpenDocument();

        /**
        * Saves the document
        *@param selectFile - if true, the user will be prompted to select the destination file name
        *@return true on success, otherwise false
        */
        bool SaveDocument(bool selectFile);

        /**
        * Closes any previously opened document
        *@return true if document was closed, otherwise false
        */
        bool CloseDocument();

        /**
        * Opens the form editor
        */
        void OpenEditor();

        /**
        * Updates the caption
        */
        void UpdateCaption();

        /**
        * Distribute the controls horizontally, from first on the left to last on the right
        *@param controls - controls to distribute
        */
        void DistributeCtrlsLTR(IControls& controls);

        /**
        * Distribute the controls horizontally, from first on the right to last on the left
        *@param controls - controls to distribute
        */
        void DistributeCtrlsRTL(IControls& controls);

        /**
        * Draw the document content
        *@param pCanvas - canvas to draw on
        */
        void Draw(TCanvas* pCanvas);

        /**
        * Called when key is down
        *@param key - pressed key code
        *@param shift - special shift keys state
        */
        void OnKeyDown(WORD& key, TShiftState shift);
};
extern PACKAGE TMainForm* MainForm;
#endif
