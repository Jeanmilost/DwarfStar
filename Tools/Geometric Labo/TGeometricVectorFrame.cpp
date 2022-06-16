/****************************************************************************
 * ==> TGeometricVectorFrame -----------------------------------------------*
 ****************************************************************************
 * Description : This module provides a frame to edit a vector content      *
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
#include "TGeometricVectorFrame.h"

// interface
#include "TGeometricFrameCommon.h"

#pragma package(smart_init)
#pragma resource "*.dfm"

//---------------------------------------------------------------------------
TGeometricVectorFrame* GeometricVectorFrame;
//---------------------------------------------------------------------------
__fastcall TGeometricVectorFrame::TGeometricVectorFrame(TComponent* pOwner) :
    TFrame(pOwner)
{}
//---------------------------------------------------------------------------
void __fastcall TGeometricVectorFrame::edXChange(TObject* pSender)
{
    TGeometricFrameCommon::ValidateFloatResult(edX, m_LastValidX);
}
//---------------------------------------------------------------------------
void __fastcall TGeometricVectorFrame::edYChange(TObject* pSender)
{
    TGeometricFrameCommon::ValidateFloatResult(edY, m_LastValidY);
}
//---------------------------------------------------------------------------
void __fastcall TGeometricVectorFrame::edZChange(TObject* pSender)
{
    TGeometricFrameCommon::ValidateFloatResult(edZ, m_LastValidZ);
}
//---------------------------------------------------------------------------
void TGeometricVectorFrame::HideZ()
{
    // hide the z components
    laZ->Visible = false;
    edZ->Visible = false;

    // increase the other edit widths
    edX->Width = 110;
    edY->Width = 110;
}
//---------------------------------------------------------------------------
float TGeometricVectorFrame::GetX() const
{
    return ::StrToFloat(edX->Text);
}
//---------------------------------------------------------------------------
void TGeometricVectorFrame::SetX(float value)
{
    edX->Text = ::FloatToStr(value);
}
//---------------------------------------------------------------------------
float TGeometricVectorFrame::GetY() const
{
    return ::StrToFloat(edY->Text);
}
//---------------------------------------------------------------------------
void TGeometricVectorFrame::SetY(float value)
{
    edY->Text = ::FloatToStr(value);
}
//---------------------------------------------------------------------------
float TGeometricVectorFrame::GetZ() const
{
    return ::StrToFloat(edZ->Text);
}
//---------------------------------------------------------------------------
void TGeometricVectorFrame::SetZ(float value)
{
    edZ->Text = ::FloatToStr(value);
}
//---------------------------------------------------------------------------
