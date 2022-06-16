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

#include <vcl.h>
#pragma hdrstop
#include "Main.h"

// std
#include <sstream>

// dwarfstar engine
#include "DWF_Common_Types.h"
#include "DWF_Common_Helpers.h"
#include "DWF_Geometry_Shape.h"
#include "DWF_Geometry_Circle.h"

// interface
#include "TGeometricShapeEditor.h"

#pragma package(smart_init)
#pragma resource "*.dfm"

//---------------------------------------------------------------------------
TMainForm* MainForm;
//---------------------------------------------------------------------------
__fastcall TMainForm::TMainForm(TComponent* pOwner) :
    TForm(pOwner),
    m_pGeometricDocument(NULL),
    m_pDocCanvas(NULL),
    m_pOverlay(NULL),
    m_Status(IE_IS_DocumentClosed),
    m_Editing(false),
    m_fViewWndProc_Backup(NULL)
{
    UpdateInterface();
}
//---------------------------------------------------------------------------
__fastcall TMainForm::~TMainForm()
{
    if (m_pDocCanvas)
        delete m_pDocCanvas;

    if (m_pOverlay)
        delete m_pOverlay;

    // restore the normal view procedure
    if (m_fViewWndProc_Backup)
        paView->WindowProc = m_fViewWndProc_Backup;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::acFileNewDoc2DExecute(TObject* pSender)
{
    // close any previously opened document
    if (!CloseDocument())
        return;

    // open a new 2D document
    m_pGeometricDocument = new TGeometricDocument2D();

    // set status to opened
    m_Status = IE_IS_DocumentOpened;

    UpdateInterface();
    paView->Invalidate();
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::acFileNewDoc3DExecute(TObject* pSender)
{
    // close any previously opened document
    if (!CloseDocument())
        return;

    // open a new 3D document
    m_pGeometricDocument = new TGeometricDocument3D(paView->Handle);

    // set status to opened
    m_Status = IE_IS_DocumentOpened;

    UpdateInterface();
    paView->Invalidate();
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::acFileOpenExecute(TObject* pSender)
{
    // close any previously opened document
    if (!CloseDocument())
        return;

    // set the initial directory to "My Documents"
    odOpen->InitialDir = DWF_FileHelper::GetWindowsDir(CSIDL_MYDOCUMENTS).c_str();

    // open the save dialog box
    if (!odOpen->Execute())
        return;

    // keep the file name to open
    m_FileName = odOpen->FileName.c_str();

    // open the document
    if (!OpenDocument())
    {
        // show error message
        ::MessageDlg("An error occurred while the document was opened.",
                     mtError,
                     TMsgDlgButtons() << mbOK,
                     0);

        // close document again to reset the interface in his default state
        CloseDocument();
    }
    else
        // set status to opened
        m_Status = IE_IS_DocumentOpened;

    UpdateInterface();
    paView->Invalidate();
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::acFileSaveExecute(TObject* pSender)
{
    // file name was not previously opened?
    if (m_FileName.empty())
    {
        acFileSaveAs->Execute();
        return;
    }

    SaveDocument(false);
    UpdateCaption();
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::acFileSaveAsExecute(TObject* pSender)
{
    SaveDocument(true);
    UpdateCaption();
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::acFileCloseExecute(TObject* pSender)
{
    CloseDocument();
    paView->Invalidate();
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::acFileQuitExecute(TObject* pSender)
{
    Close();
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::acAddLineExecute(TObject* pSender)
{
    // get 2d document
    TGeometricDocument2D* pGeometricDocument2D =
            dynamic_cast<TGeometricDocument2D*>(m_pGeometricDocument);

    // is 2d document opened?
    if (pGeometricDocument2D)
    {
        const int centerX = paView->ClientWidth  / 2;
        const int centerY = paView->ClientHeight / 2;

        // add a line to the document
        pGeometricDocument2D->AddLine(DWF_Vector2DR(centerX, centerY),
                                      DWF_Vector2DR(std::sin(M_PI / 4.0f), -std::cos(M_PI / 4.0f)));

        paView->Invalidate();
    }
    else
    {
        // get 3d document
        TGeometricDocument3D* pGeometricDocument3D =
                dynamic_cast<TGeometricDocument3D*>(m_pGeometricDocument);

        // is 3d document opened?
        if (pGeometricDocument3D)
        {
            // add a segment to the document
            pGeometricDocument3D->AddLine(DWF_Vector3DR(0.0f, 0.0f, 0.0f),
                                          DWF_Vector3DR(-std::sin(M_PI / 4.0f),
                                                         std::cos(M_PI / 4.0f),
                                                         0.0f));

            paView->Invalidate();
        }
    }

    UpdateCaption();
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::acAddRayExecute(TObject* pSender)
{
    // get 2d document
    TGeometricDocument2D* pGeometricDocument2D =
            dynamic_cast<TGeometricDocument2D*>(m_pGeometricDocument);

    // is 2d document opened?
    if (pGeometricDocument2D)
    {
        const int centerX = paView->ClientWidth  / 2;
        const int centerY = paView->ClientHeight / 2;

        // add a ray to the document
        pGeometricDocument2D->AddRay(DWF_Vector2DR(centerX, centerY),
                                     DWF_Vector2DR(std::sin(M_PI / 4.0f), -std::cos(M_PI / 4.0f)));

        paView->Invalidate();
    }
    else
    {
        // get 3d document
        TGeometricDocument3D* pGeometricDocument3D =
                dynamic_cast<TGeometricDocument3D*>(m_pGeometricDocument);

        // is 3d document opened?
        if (pGeometricDocument3D)
        {
            // add a segment to the document
            pGeometricDocument3D->AddRay(DWF_Vector3DR(0.0f, 0.0f, 0.0f),
                                         DWF_Vector3DR(-std::sin(M_PI / 4.0f),
                                                        std::cos(M_PI / 4.0f),
                                                        0.0f));

            paView->Invalidate();
        }
    }

    UpdateCaption();
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::acAddSegmentExecute(TObject* pSender)
{
    // get 2d document
    TGeometricDocument2D* pGeometricDocument2D =
            dynamic_cast<TGeometricDocument2D*>(m_pGeometricDocument);

    // is 2d document opened?
    if (pGeometricDocument2D)
    {
        const int centerX = paView->ClientWidth  / 2;
        const int centerY = paView->ClientHeight / 2;

        // add a segment to the document
        pGeometricDocument2D->AddSegment(DWF_Vector2DR(centerX - 50.0f, centerY + 50.0f),
                                         DWF_Vector2DR(centerX + 50.0f, centerY - 50.0f));

        paView->Invalidate();
    }
    else
    {
        // get 3d document
        TGeometricDocument3D* pGeometricDocument3D =
                dynamic_cast<TGeometricDocument3D*>(m_pGeometricDocument);

        // is 3d document opened?
        if (pGeometricDocument3D)
        {
            // add a segment to the document
            pGeometricDocument3D->AddSegment(DWF_Vector3DR(-0.5f,  0.5f, 0.0f),
                                             DWF_Vector3DR( 0.5f, -0.5f, 0.0f));

            paView->Invalidate();
        }
    }

    UpdateCaption();
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::acAddPolygonExecute(TObject* pSender)
{
    // get 2d document
    TGeometricDocument2D* pGeometricDocument2D =
            dynamic_cast<TGeometricDocument2D*>(m_pGeometricDocument);

    // is 2d document opened?
    if (pGeometricDocument2D)
    {
        const int centerX = paView->ClientWidth  / 2;
        const int centerY = paView->ClientHeight / 2;

        // add a polygon to the document
        pGeometricDocument2D->AddPolygon(DWF_Vector2DR(centerX - 50, centerY + 50),
                                         DWF_Vector2DR(centerX,      centerY - 50),
                                         DWF_Vector2DR(centerX + 50, centerY + 50));

        paView->Invalidate();
    }
    else
    {
        // get 3d document
        TGeometricDocument3D* pGeometricDocument3D =
                dynamic_cast<TGeometricDocument3D*>(m_pGeometricDocument);

        // is 3d document opened?
        if (pGeometricDocument3D)
        {
            // add a polygon to the document
            pGeometricDocument3D->AddPolygon(DWF_Vector3DR(-0.1f, -0.1f, 0.0f),
                                             DWF_Vector3DR( 0.0f,  0.1f, 0.0f),
                                             DWF_Vector3DR( 0.1f, -0.1f, 0.0f));

            paView->Invalidate();
        }
    }

    UpdateCaption();
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::acAddCircleExecute(TObject* pSender)
{
    // get 2d document
    TGeometricDocument2D* pGeometricDocument2D =
            dynamic_cast<TGeometricDocument2D*>(m_pGeometricDocument);

    // 2d document isn't opened?
    if (!pGeometricDocument2D)
        return;

    // add a circle to the document
    pGeometricDocument2D->AddCircle(DWF_Vector2DR(paView->ClientWidth  / 2,
                                                  paView->ClientHeight / 2),
                                                  50.0f);

    paView->Invalidate();

    UpdateCaption();
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::acAddRectExecute(TObject* pSender)
{
    // get 2d document
    TGeometricDocument2D* pGeometricDocument2D =
            dynamic_cast<TGeometricDocument2D*>(m_pGeometricDocument);

    // 2d document isn't opened?
    if (!pGeometricDocument2D)
        return;

    const int centerX = paView->ClientWidth  / 2;
    const int centerY = paView->ClientHeight / 2;

    // add a rect to the document
    pGeometricDocument2D->AddRect(centerX - 25, centerY - 25, centerX + 25, centerY + 25);

    paView->Invalidate();

    UpdateCaption();
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::acAddPlaneExecute(TObject* pSender)
{
    // get 3d document
    TGeometricDocument3D* pGeometricDocument3D =
            dynamic_cast<TGeometricDocument3D*>(m_pGeometricDocument);

    // 3d document isn't opened?
    if (!pGeometricDocument3D)
        return;

    // add a plane to the document
    pGeometricDocument3D->AddPlane(DWF_Vector3DR(0.0f, 0.0f, 0.0f), DWF_Vector3DR(0.0f, 0.0f, 1.0f));

    paView->Invalidate();

    UpdateCaption();
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::acAddSphereExecute(TObject* pSender)
{
    // get 3d document
    TGeometricDocument3D* pGeometricDocument3D =
            dynamic_cast<TGeometricDocument3D*>(m_pGeometricDocument);

    // 3d document isn't opened?
    if (!pGeometricDocument3D)
        return;

    // add a sphere to the document
    pGeometricDocument3D->AddSphere(DWF_Vector3DR(0.0f, 0.0f, 0.0f), 0.25f);

    paView->Invalidate();

    UpdateCaption();
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::acAddBoxExecute(TObject* pSender)
{
    // get 3d document
    TGeometricDocument3D* pGeometricDocument3D =
            dynamic_cast<TGeometricDocument3D*>(m_pGeometricDocument);

    // 3d document isn't opened?
    if (!pGeometricDocument3D)
        return;

    // add a box to the document
    pGeometricDocument3D->AddBox(DWF_Vector3DR(-0.5f,  0.5f, -1.0f),
                                 DWF_Vector3DR( 0.5f, -0.5f,  1.0f));

    paView->Invalidate();

    UpdateCaption();
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::acAddDiskExecute(TObject* pSender)
{
    // get 3d document
    TGeometricDocument3D* pGeometricDocument3D =
            dynamic_cast<TGeometricDocument3D*>(m_pGeometricDocument);

    // 3d document isn't opened?
    if (!pGeometricDocument3D)
        return;

    // add a disk to the document
    pGeometricDocument3D->AddDisk(DWF_Vector3DR(0.0f, 0.0f, 0.0f),
                                  DWF_Vector3DR(0.0f, 0.0f, 0.5f),
                                  0.25f);

    paView->Invalidate();

    UpdateCaption();
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::acAddCylinderExecute(TObject* pSender)
{
    // get 3d document
    TGeometricDocument3D* pGeometricDocument3D =
            dynamic_cast<TGeometricDocument3D*>(m_pGeometricDocument);

    // 3d document isn't opened?
    if (!pGeometricDocument3D)
        return;

    // add a cylinder to the document
    pGeometricDocument3D->AddCylinder(DWF_Vector3DR(0.0f, -0.25f, 0.0f),
                                      DWF_Vector3DR(0.0f,  0.25f, 0.0f),
                                      0.25f);

    paView->Invalidate();

    UpdateCaption();
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::acIntersectionModeExecute(TObject* pSender)
{
    acSimulatorStop->Execute();

    m_Status = IE_IS_Sim_Intersect_Mode;

    // update the interface
    UpdateInterface();

    // update the simulator items
    miIntersectionMode->Checked = true;
    btIntersectionMode->Down    = true;

    // animate the result
    tmSimulator->Enabled = true;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::acInsideModeExecute(TObject* pSender)
{
    acSimulatorStop->Execute();

    m_Status = IE_IS_Sim_Inside_Mode;

    // update the interface
    UpdateInterface();

    // update the simulator items
    miInsideMode->Checked = true;
    btInsideMode->Down    = true;

    // animate the result
    tmSimulator->Enabled = true;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::acSimulatorStopExecute(TObject* pSender)
{
    // disable the animation timer
    tmSimulator->Enabled = false;

    // reset status to opened
    m_Status = IE_IS_DocumentOpened;

    // update the interface
    UpdateInterface();

    // update the simulator items
    miSimulatorStop->Checked = true;
    btSimulatorStop->Down    = true;

    // is document opened?
    if (m_pGeometricDocument)
        // reset the simulator
        m_GeometricSimulator.Reset(m_pGeometricDocument);

    paView->Invalidate();
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::tmSimulatorTimer(TObject* pSender)
{
    // is document opened?
    if (m_pGeometricDocument)
    {
        // search for running simulation mode
        switch (m_Status)
        {
            case IE_IS_Sim_Inside_Mode:
            {
                // run the inside test
                if (dynamic_cast<TGeometricDocument2D*>(m_pGeometricDocument))
                {
                    // get the mouse cursor position on the screen
                    TPoint mousePos = Mouse->CursorPos;

                    // convert to local document coordinates
                    if (!::ScreenToClient(paView->Handle, &mousePos))
                        return;

                    m_GeometricSimulator.TestInside(m_pGeometricDocument, mousePos);
                }
                else
                    m_GeometricSimulator.TestInside(m_pGeometricDocument, TPoint());

                break;
            }

            case IE_IS_Sim_Intersect_Mode:
                // run the intersections test
                m_GeometricSimulator.TestIntersections(m_pGeometricDocument);
                break;
        }

        // calculate the surface to repaint
        const TRect rect(0, 0, paView->ClientWidth, paView->ClientHeight);

        // repaint the document
        ::InvalidateRect(paView->Handle, &rect, false);
    }
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::aeMainEventsMessage(tagMSG& msg, bool& handled)
{
    // dispatch Windows messages
    switch (msg.message)
    {
        case WM_KEYDOWN:
        {
            if (m_Editing)
                return;

            TKeyboardState pKeyboardState;
            TShiftState    shiftState;

            // get keyboard state (contains also the mouse buttons state)
            if (::GetKeyboardState(pKeyboardState))
                // convert keyboard state to shift state
                shiftState = ::KeyboardStateToShiftState(pKeyboardState);

            WORD key = msg.wParam;

            OnKeyDown(key, shiftState);

            switch (key)
            {
                case VK_LEFT:
                case VK_RIGHT:
                case VK_UP:
                case VK_DOWN: handled = true; break;
            }

            return;
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::FormCreate(TObject* pSender)
{
    if (!m_pDocCanvas)
        m_pDocCanvas = new TCanvas();

    // hook the panel procedure
    m_fViewWndProc_Backup = paView->WindowProc;
    paView->WindowProc    = ViewWndProc;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::FormCloseQuery(TObject* pSender, bool& canClose)
{
    canClose = CloseDocument();
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::ViewWndProc(TMessage& message)
{
    switch (message.Msg)
    {
        case WM_WINDOWPOSCHANGED:
        {
            if (!m_pDocCanvas)
                break;

            if (m_fViewWndProc_Backup)
                m_fViewWndProc_Backup(message);

            HDC hDC = NULL;

            try
            {
                hDC = ::GetDC(paView->Handle);

                if (hDC)
                {
                    m_pDocCanvas->Handle = hDC;

                    // redraw here, thus the view will be redrawn to the correct size in real time
                    // while the size changes
                    Draw(m_pDocCanvas);
                }
            }
            __finally
            {
                if (hDC)
                    ::ReleaseDC(paView->Handle, hDC);
            }

            return;
        }

        case WM_PAINT:
        {
            if (!m_pDocCanvas)
                break;

            HDC           hDC = NULL;
            ::PAINTSTRUCT ps;

            try
            {
                hDC = ::BeginPaint(paView->Handle, &ps);

                if (hDC)
                {
                    m_pDocCanvas->Handle = hDC;
                    Draw(m_pDocCanvas);
                }
            }
            __finally
            {
                ::EndPaint(paView->Handle, &ps);
            }

            return;
        }
    }

    if (m_fViewWndProc_Backup)
        m_fViewWndProc_Backup(message);
}
//---------------------------------------------------------------------------
void TMainForm::UpdateInterface()
{
    bool documentOpened = false;
    bool simInsideMode  = false;

    // determine the application status
    switch (m_Status)
    {
        case IE_IS_DocumentOpened:
        case IE_IS_Sim_Intersect_Mode:
            paView->Cursor = crDefault;
            documentOpened = true;
            break;

        case IE_IS_Sim_Inside_Mode:
            documentOpened = true;
            simInsideMode  = true;
            break;
    }

    // check if 2d or 3d document is opened
    const bool doc2D = documentOpened &&           dynamic_cast<TGeometricDocument2D*>(m_pGeometricDocument);
    const bool doc3D = documentOpened && !doc2D && dynamic_cast<TGeometricDocument3D*>(m_pGeometricDocument);

    if (doc2D && simInsideMode)
        paView->Cursor = crCross;

    // stop the autosize while the 2d and 3d document button bars are refreshed
    paDocument2DButtons->AutoSize = false;
    paDocument3DButtons->AutoSize = false;

    // set shared shortcut to available action
    if (doc2D)
    {
        acAddCircle->ShortCut   = VK_F5;
        acAddRect->ShortCut     = VK_F6;
        acAddSphere->ShortCut   = 0;
        acAddBox->ShortCut      = 0;
    }
    else
    if (doc3D)
    {
        acAddCircle->ShortCut   = 0;
        acAddRect->ShortCut     = 0;
        acAddSphere->ShortCut   = VK_F5;
        acAddBox->ShortCut      = VK_F6;
    }

    try
    {
        // file menu
        acFileSave->Enabled   = documentOpened;
        acFileSaveAs->Enabled = documentOpened;
        acFileClose->Enabled  = documentOpened;

        // shapes menu content
        acAddCircle->Visible   = doc2D;
        acAddRect->Visible     = doc2D;
        acAddPlane->Visible    = doc3D;
        acAddSphere->Visible   = doc3D;
        acAddBox->Visible      = doc3D;
        acAddDisk->Visible     = doc3D;
        acAddCylinder->Visible = doc3D;

        // shapes menu
        acAddLine->Enabled     = documentOpened;
        acAddRay->Enabled      = documentOpened;
        acAddSegment->Enabled  = documentOpened;
        acAddPlane->Enabled    = documentOpened;
        acAddPolygon->Enabled  = documentOpened;
        acAddCircle->Enabled   = documentOpened;
        acAddRect->Enabled     = documentOpened;
        acAddSphere->Enabled   = documentOpened;
        acAddBox->Enabled      = documentOpened;
        acAddDisk->Enabled     = documentOpened;
        acAddCylinder->Enabled = documentOpened;

        // simulator menu
        acIntersectionMode->Enabled = documentOpened;
        acInsideMode->Enabled       = documentOpened;
        acSimulatorStop->Enabled    = documentOpened;

        // toolbars
        paToolbar->Visible           = documentOpened;
        paDocument2DButtons->Visible = doc2D;
        paDocument3DButtons->Visible = doc3D;
    }
    __finally
    {
        // restart the 2d and 3d document button bars autosize
        paDocument2DButtons->AutoSize = true;
        paDocument3DButtons->AutoSize = true;
    }

    // distribute the toolbars from right to left
    IControls controls;
    controls.push_back(paDocument2DButtons);
    controls.push_back(paDocument3DButtons);
    controls.push_back(paSimulatorButtons);
    DistributeCtrlsRTL(controls);

    UpdateCaption();
}
//---------------------------------------------------------------------------
bool TMainForm::OpenDocument()
{
    // is document already opened?
    if (m_pGeometricDocument)
        return false;

    // open document
    m_pGeometricDocument =
            TGeometricDocument::Load(DWF_StringHelper::UTF16ToUTF8(m_FileName), paView->Handle);

    // succeeded?
    return m_pGeometricDocument;
}
//---------------------------------------------------------------------------
bool TMainForm::SaveDocument(bool selectFile)
{
    // do user select the destination file name?
    if (selectFile)
    {
        // set the initial directory to "My Documents"
        sdSave->InitialDir = DWF_FileHelper::GetWindowsDir(CSIDL_MYDOCUMENTS).c_str();

        // open the save dialog box
        if (!sdSave->Execute())
            return false;

        // keep the file name to save
        m_FileName = sdSave->FileName.c_str();
    }

    do
    {
        // get 2d document
        TGeometricDocument2D* pGeometricDocument2D =
                dynamic_cast<TGeometricDocument2D*>(m_pGeometricDocument);

        // save 2D document if opened
        if (pGeometricDocument2D)
            if (pGeometricDocument2D->Save(DWF_StringHelper::UTF16ToUTF8(m_FileName)))
            {
                // reset it to unmodified
                pGeometricDocument2D->Untouch();
                return true;
            }

        // get 3d document
        TGeometricDocument3D* pGeometricDocument3D =
                dynamic_cast<TGeometricDocument3D*>(m_pGeometricDocument);

        // save 3D document if opened
        if (pGeometricDocument3D)
            if (pGeometricDocument3D->Save(DWF_StringHelper::UTF16ToUTF8(m_FileName)))
            {
                // reset it to unmodified
                pGeometricDocument3D->Untouch();
                return true;
            }

        ::MessageDlg("The document could not be saved due to an internal error.\n\nPlease contact your support to fix the issue.",
                     mtError,
                     TMsgDlgButtons() << mbOK,
                     0);

        // no opened document or unknown document
        return false;
    }
    while (::MessageDlg("An error occurred while the document was saved.\n\nDo you want to retry?",
                        mtError,
                        TMsgDlgButtons() << mbRetry << mbCancel,
                        0) == mrRetry);

    return false;
}
//---------------------------------------------------------------------------
bool TMainForm::CloseDocument()
{
    // already closed?
    if (!m_pGeometricDocument)
        return true;

    // was document modified?
    if (m_pGeometricDocument->IsTouched())
        // prompt the user about if the document should be saved
        if (::MessageDlg("The document was modified.\n\nDo you want to save your changes?",
                         mtConfirmation,
                         TMsgDlgButtons() << mbYes << mbNo,
                         0) == mrYes)
            if (!SaveDocument(true))
                return false;

    // stop the simulator
    acSimulatorStop->Execute();

    // set status to closed
    m_Status = IE_IS_DocumentClosed;

    // clear the file name
    m_FileName.clear();

    // delete the document
    delete m_pGeometricDocument;
    m_pGeometricDocument = NULL;

    UpdateInterface();

    return true;
}
//---------------------------------------------------------------------------
void TMainForm::OpenEditor()
{
    if (!m_pGeometricDocument)
        return;

    // get 2d document
    TGeometricDocument2D* pGeometricDocument2D =
            dynamic_cast<TGeometricDocument2D*>(m_pGeometricDocument);

    // found it?
    if (pGeometricDocument2D)
    {
        try
        {
            m_Editing = true;

            // create and show editor
            std::auto_ptr<TGeometricShapeEditor> pShapeEditor
                    (new TGeometricShapeEditor(this, pGeometricDocument2D->GetFocused()));
            pShapeEditor->ShowModal();
        }
        __finally
        {
            m_Editing = false;
        }

        paView->Invalidate();
    }

    // get 3d document
    TGeometricDocument3D* pGeometricDocument3D =
            dynamic_cast<TGeometricDocument3D*>(m_pGeometricDocument);

    // found it?
    if (pGeometricDocument3D)
    {
        try
        {
            m_Editing = true;

            // create and show editor
            std::auto_ptr<TGeometricShapeEditor> pShapeEditor
                    (new TGeometricShapeEditor(this, pGeometricDocument3D->GetFocused()));
            pShapeEditor->ShowModal();
        }
        __finally
        {
            m_Editing = false;
        }

        paView->Invalidate();
    }
}
//---------------------------------------------------------------------------
void TMainForm::UpdateCaption()
{
    // check if document was modified
    const bool modified = m_pGeometricDocument && m_pGeometricDocument->IsTouched();

    std::wostringstream sstr;

    // set the application name
    sstr << L"DwarfStar Geometric Laboratory";

    // is document opened with a valid file name?
    if (!m_FileName.empty())
        sstr << L" - " << DWF_FileHelper::GetStrippedFileName(m_FileName);

    // is document modified?
    if (modified)
        sstr << L"*";

    // set the main form caption
    Caption = sstr.str().c_str();
}
//---------------------------------------------------------------------------
void TMainForm::DistributeCtrlsLTR(IControls& controls)
{
    int pos = 0;

    // iterate through controls to distribute
    for (std::size_t i = 0; i < controls.size(); ++i)
    {
        // is control visible?
        if (!controls[i]->Visible)
            continue;

        // place the control on the left
        controls[i]->Left = pos;

        // calculate the next position
        pos += controls[i]->Margins->ControlWidth;
    }
}
//---------------------------------------------------------------------------
void TMainForm::DistributeCtrlsRTL(IControls& controls)
{
    // iterate through controls to distribute
    for (std::size_t i = 0; i < controls.size(); ++i)
    {
        // is control visible?
        if (!controls[i]->Visible)
            continue;

        // place the control on the right
        controls[i]->Left = 0;
    }
}
//---------------------------------------------------------------------------
void TMainForm::Draw(TCanvas* pCanvas)
{
    if (!pCanvas)
        return;

    // get 2d document
    TGeometricDocument2D* pGeometricDocument2D =
            dynamic_cast<TGeometricDocument2D*>(m_pGeometricDocument);

    // is 2d document opened?
    if (pGeometricDocument2D)
    {
        // create the overlay
        if (!m_pOverlay)
            m_pOverlay = new TBitmap();

        // resize the overlay
        if (m_pOverlay->Width != paView->Width || m_pOverlay->Height != paView->Height)
            m_pOverlay->SetSize(paView->Width, paView->Height);

        // draw the document content on the overlay
        pGeometricDocument2D->Draw(TRect(0, 0, paView->ClientWidth, paView->ClientHeight),
                                   m_pOverlay->Canvas);

        // copy the document content from overlay
        ::BitBlt(pCanvas->Handle,
                 0,
                 0,
                 paView->Width,
                 paView->Height,
                 m_pOverlay->Canvas->Handle,
                 0,
                 0,
                 SRCCOPY);

        return;
    }

    // get 3d document
    TGeometricDocument3D* pGeometricDocument3D =
            dynamic_cast<TGeometricDocument3D*>(m_pGeometricDocument);

    // is 3d document opened?
    if (pGeometricDocument3D)
    {
        const int width  = std::max(paView->ClientWidth,  1);
        const int height = std::max(paView->ClientHeight, 1);

        // create or resize the document viewport
        pGeometricDocument3D->CreateViewport(width, height);

        // draw the document content
        pGeometricDocument3D->Draw(TRect(0, 0, width, height), pCanvas);
        return;
    }

    // draw default background
    pCanvas->Brush->Style = bsSolid;
    pCanvas->Brush->Color = Color;
    pCanvas->FillRect(TRect(0, 0, paView->ClientWidth, paView->ClientHeight));
}
//---------------------------------------------------------------------------
void TMainForm::OnKeyDown(WORD& key, TShiftState shift)
{
    // is 2d document opened?
    if (!m_pGeometricDocument)
        return;

    int offsetX = 0;
    int offsetY = 0;
    int offsetZ = 0;

    int shape3DOffsetX = 0;
    int shape3DOffsetY = 0;
    int shape3DOffsetZ = 0;

    // search for pressed key
    switch (key)
    {
        case VK_TAB:
            if (shift.Contains(ssShift))
                m_pGeometricDocument->FocusPrev();
            else
                m_pGeometricDocument->FocusNext();

            paView->Invalidate();
            return;

        case VK_RETURN:   OpenEditor();        return;
        case VK_LEFT:     offsetX        = -1; break;
        case VK_RIGHT:    offsetX        =  1; break;
        case VK_UP:       offsetY        = -1; break;
        case VK_DOWN:     offsetY        =  1; break;
        case 0x38:
        case VK_ADD:      offsetZ        =  1; break;
        case 0x39:
        case VK_SUBTRACT: offsetZ        = -1; break;
        case 0x51:        shape3DOffsetX =  1; break;
        case 0x45:        shape3DOffsetX = -1; break;
        case 0x53:        shape3DOffsetY =  1; break;
        case 0x57:        shape3DOffsetY = -1; break;
        case 0x41:        shape3DOffsetZ =  1; break;
        case 0x44:        shape3DOffsetZ = -1; break;
        default:                               return;
    }

    // get 2d document
    TGeometricDocument2D* pGeometricDocument2D =
            dynamic_cast<TGeometricDocument2D*>(m_pGeometricDocument);

    // is 2d document opened?
    if (pGeometricDocument2D)
    {
        // apply the key effect
        if (shift.Contains(ssCtrl) && shift.Contains(ssShift))
            pGeometricDocument2D->RotateFocused(offsetX ? offsetX : offsetY);
        else
        if (shift.Contains(ssShift))
            pGeometricDocument2D->InflateFocused(offsetX, offsetY);
        else
            pGeometricDocument2D->MoveFocused(offsetX, offsetY);
    }

    // get 3d document
    TGeometricDocument3D* pGeometricDocument3D =
            pGeometricDocument2D ? NULL : dynamic_cast<TGeometricDocument3D*>(m_pGeometricDocument);

    // is 3d document opened?
    if (pGeometricDocument3D)
    {
        // apply the key effect
        pGeometricDocument3D->MoveCamera(-offsetY, -offsetX, -offsetZ);

        // apply the key effect
        if (shift.Contains(ssCtrl) && shift.Contains(ssShift))
            pGeometricDocument3D->RotateFocused(shape3DOffsetX, shape3DOffsetY, shape3DOffsetZ);
        else
        if (shift.Contains(ssShift))
            pGeometricDocument3D->InflateFocused(shape3DOffsetX, shape3DOffsetY, shape3DOffsetZ);
        else
            pGeometricDocument3D->MoveFocused(shape3DOffsetX, shape3DOffsetY, shape3DOffsetZ);
    }

    UpdateCaption();

    // repaint interface, but only if simulator is not running
    if (m_Status == IE_IS_DocumentOpened)
        paView->Invalidate();
}
//---------------------------------------------------------------------------
