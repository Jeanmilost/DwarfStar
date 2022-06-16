/****************************************************************************
 * ==> TGeometricShapeEditor -----------------------------------------------*
 ****************************************************************************
 * Description : This module provides an editor for the geometric shapes    *
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
#include "TGeometricShapeEditor.h"

// dwarfstar engine
#include "DWF_Geometry_Line.h"
#include "DWF_Geometry_Ray.h"
#include "DWF_Geometry_Segment.h"
#include "DWF_Geometry_Plane.h"
#include "DWF_Geometry_Polygon.h"
#include "DWF_Geometry_Circle.h"
#include "DWF_Geometry_Rect.h"
#include "DWF_Geometry_Sphere.h"
#include "DWF_Geometry_Box.h"
#include "DWF_Geometry_Disk.h"
#include "DWF_Geometry_Cylinder.h"

// interface
#include "TGeometricFrameCommon.h"

#pragma package(smart_init)
#pragma link "TGeometricVectorFrame"
#pragma resource "*.dfm"

//---------------------------------------------------------------------------
// TShapeEditor
//---------------------------------------------------------------------------
TGeometricShapeEditor* GeometricShapeEditor;
//---------------------------------------------------------------------------
__fastcall TGeometricShapeEditor::TGeometricShapeEditor(TComponent* pOwner, DWF_Shape2D<M_Real>* pShape2D) :
    TForm(pOwner),
    m_pShape2D(pShape2D)
{
    // hide all the pages
    for (int i = 0; i < pcPages->PageCount; ++i)
        pcPages->Pages[i]->TabVisible = false;

    // get a line
    DWF_Line2DR* pLine = dynamic_cast<DWF_Line2DR*>(m_pShape2D);

    // found it?
    if (pLine)
    {
        // set the editor caption
        Caption = laLineTitle->Caption;

        // expose the line point value
        gvLinePoint->SetX(pLine->GetPoint().m_X);
        gvLinePoint->SetY(pLine->GetPoint().m_Y);
        gvLinePoint->HideZ();

        // expose the line direction value
        gvLineDir->SetX(pLine->GetDir().m_X);
        gvLineDir->SetY(pLine->GetDir().m_Y);
        gvLineDir->HideZ();

        // show the line editor
        pcPages->ActivePage = tsLine;
        return;
    }

    // get a ray
    DWF_Ray2DR* pRay = dynamic_cast<DWF_Ray2DR*>(m_pShape2D);

    // found it?
    if (pRay)
    {
        // set the editor caption
        Caption = laRayTitle->Caption;

        // expose the ray point value
        gvRayPos->SetX(pRay->GetPos().m_X);
        gvRayPos->SetY(pRay->GetPos().m_Y);
        gvRayPos->HideZ();

        // expose the ray direction value
        gvRayDir->SetX(pRay->GetDir().m_X);
        gvRayDir->SetY(pRay->GetDir().m_Y);
        gvRayDir->HideZ();

        // show the ray editor
        pcPages->ActivePage = tsRay;
        return;
    }

    // get a line segment
    DWF_Segment2DR* pSegment = dynamic_cast<DWF_Segment2DR*>(m_pShape2D);

    // found it?
    if (pSegment)
    {
        // set the editor caption
        Caption = laSegmentTitle->Caption;

        // expose the line segment start value
        gvSegmentStart->SetX(pSegment->m_Start.m_X);
        gvSegmentStart->SetY(pSegment->m_Start.m_Y);
        gvSegmentStart->HideZ();

        // expose the line segment end value
        gvSegmentEnd->SetX(pSegment->m_End.m_X);
        gvSegmentEnd->SetY(pSegment->m_End.m_Y);
        gvSegmentEnd->HideZ();

        // show the line segment editor
        pcPages->ActivePage = tsSegment;
        return;
    }

    // get a polygon
    DWF_Polygon2DR* pPolygon = dynamic_cast<DWF_Polygon2DR*>(m_pShape2D);

    // found it?
    if (pPolygon)
    {
        // set the editor caption
        Caption = laPolygonTitle->Caption;

        // expose the polygon vertex 1 value
        gvPolygonV1->SetX(pPolygon->GetVertex1().m_X);
        gvPolygonV1->SetY(pPolygon->GetVertex1().m_Y);
        gvPolygonV1->HideZ();

        // expose the polygon vertex 2 value
        gvPolygonV2->SetX(pPolygon->GetVertex2().m_X);
        gvPolygonV2->SetY(pPolygon->GetVertex2().m_Y);
        gvPolygonV2->HideZ();

        // expose the polygon vertex 3 value
        gvPolygonV3->SetX(pPolygon->GetVertex3().m_X);
        gvPolygonV3->SetY(pPolygon->GetVertex3().m_Y);
        gvPolygonV3->HideZ();

        // show the polygon editor
        pcPages->ActivePage = tsPolygon;
        return;
    }

    // get a circle
    DWF_CircleR* pCircle = dynamic_cast<DWF_CircleR*>(m_pShape2D);

    // found it?
    if (pCircle)
    {
        // set the editor caption
        Caption = laCircleTitle->Caption;

        // expose the circle center value
        gvCircleCenter->SetX(pCircle->m_Center.m_X);
        gvCircleCenter->SetY(pCircle->m_Center.m_Y);
        gvCircleCenter->HideZ();

        // expose the circle radius value
        edCircleRadius->Text = ::FloatToStr(pCircle->m_Radius);

        // show the circle editor
        pcPages->ActivePage = tsCircle;
        return;
    }

    // get a rectangle
    DWF_RectR* pRect = dynamic_cast<DWF_RectR*>(m_pShape2D);

    // found it?
    if (pRect)
    {
        // set the editor caption
        Caption = laRectTitle->Caption;

        // expose the rect left, top, right and bottom values
        edRectLeft->Text   = ::FloatToStr(pRect->m_Left);
        edRectTop->Text    = ::FloatToStr(pRect->m_Top);
        edRectRight->Text  = ::FloatToStr(pRect->m_Right);
        edRectBottom->Text = ::FloatToStr(pRect->m_Bottom);

        // show the rectangle editor
        pcPages->ActivePage = tsRect;
        return;
    }
}
//---------------------------------------------------------------------------
__fastcall TGeometricShapeEditor::TGeometricShapeEditor(TComponent* pOwner, DWF_Shape3D<M_Real>* pShape3D) :
    TForm(pOwner),
    m_pShape3D(pShape3D)
{
    // hide all the pages
    for (int i = 0; i < pcPages->PageCount; ++i)
        pcPages->Pages[i]->TabVisible = false;

    // get a line
    DWF_Line3DR* pLine = dynamic_cast<DWF_Line3DR*>(m_pShape3D);

    // found it?
    if (pLine)
    {
        // set the editor caption
        Caption = laLineTitle->Caption;

        // expose the line point value
        gvLinePoint->SetX(pLine->GetPoint().m_X);
        gvLinePoint->SetY(pLine->GetPoint().m_Y);
        gvLinePoint->SetZ(pLine->GetPoint().m_Z);

        // expose the line direction value
        gvLineDir->SetX(pLine->GetDir().m_X);
        gvLineDir->SetY(pLine->GetDir().m_Y);
        gvLineDir->SetZ(pLine->GetDir().m_Z);

        // show the line editor
        pcPages->ActivePage = tsLine;
        return;
    }

    // get a ray
    DWF_Ray3DR* pRay = dynamic_cast<DWF_Ray3DR*>(m_pShape3D);

    // found it?
    if (pRay)
    {
        // set the editor caption
        Caption = laRayTitle->Caption;

        // expose the ray point value
        gvRayPos->SetX(pRay->GetPos().m_X);
        gvRayPos->SetY(pRay->GetPos().m_Y);
        gvRayPos->SetZ(pRay->GetPos().m_Z);

        // expose the ray direction value
        gvRayDir->SetX(pRay->GetDir().m_X);
        gvRayDir->SetY(pRay->GetDir().m_Y);
        gvRayDir->SetZ(pRay->GetDir().m_Z);

        // show the ray editor
        pcPages->ActivePage = tsRay;
        return;
    }

    // get a line segment
    DWF_Segment3DR* pSegment = dynamic_cast<DWF_Segment3DR*>(m_pShape3D);

    // found it?
    if (pSegment)
    {
        // set the editor caption
        Caption = laSegmentTitle->Caption;

        // expose the line segment start value
        gvSegmentStart->SetX(pSegment->m_Start.m_X);
        gvSegmentStart->SetY(pSegment->m_Start.m_Y);
        gvSegmentStart->SetZ(pSegment->m_Start.m_Z);

        // expose the line segment end value
        gvSegmentEnd->SetX(pSegment->m_End.m_X);
        gvSegmentEnd->SetY(pSegment->m_End.m_Y);
        gvSegmentEnd->SetZ(pSegment->m_End.m_Z);

        // show the line segment editor
        pcPages->ActivePage = tsSegment;
        return;
    }

    // get a plane
    DWF_PlaneR* pPlane = dynamic_cast<DWF_PlaneR*>(m_pShape3D);

    // found it?
    if (pPlane)
    {
        // set the editor caption
        Caption = laPlaneTitle->Caption;

        // expose the plane values
        edPlaneA->Text = ::FloatToStr(pPlane->m_A);
        edPlaneB->Text = ::FloatToStr(pPlane->m_B);
        edPlaneC->Text = ::FloatToStr(pPlane->m_C);
        edPlaneD->Text = ::FloatToStr(pPlane->m_D);

        // show the rectangle editor
        pcPages->ActivePage = tsPlane;
        return;
    }

    // get a polygon
    DWF_Polygon3DR* pPolygon = dynamic_cast<DWF_Polygon3DR*>(m_pShape3D);

    // found it?
    if (pPolygon)
    {
        // set the editor caption
        Caption = laPolygonTitle->Caption;

        // expose the polygon vertex 1 value
        gvPolygonV1->SetX(pPolygon->GetVertex1().m_X);
        gvPolygonV1->SetY(pPolygon->GetVertex1().m_Y);
        gvPolygonV1->SetZ(pPolygon->GetVertex1().m_Z);

        // expose the polygon vertex 2 value
        gvPolygonV2->SetX(pPolygon->GetVertex2().m_X);
        gvPolygonV2->SetY(pPolygon->GetVertex2().m_Y);
        gvPolygonV2->SetZ(pPolygon->GetVertex2().m_Z);

        // expose the polygon vertex 3 value
        gvPolygonV3->SetX(pPolygon->GetVertex3().m_X);
        gvPolygonV3->SetY(pPolygon->GetVertex3().m_Y);
        gvPolygonV3->SetZ(pPolygon->GetVertex3().m_Z);

        // show the polygon editor
        pcPages->ActivePage = tsPolygon;
        return;
    }

    // get a sphere
    DWF_SphereR* pSphere = dynamic_cast<DWF_SphereR*>(m_pShape3D);

    // found it?
    if (pSphere)
    {
        // set the editor caption
        Caption = laSphereTitle->Caption;

        // expose the sphere center value
        gvSphereCenter->SetX(pSphere->m_Center.m_X);
        gvSphereCenter->SetY(pSphere->m_Center.m_Y);
        gvSphereCenter->SetZ(pSphere->m_Center.m_Z);

        // expose the sphere radius value
        edSphereRadius->Text = ::FloatToStr(pSphere->m_Radius);

        // show the sphere editor
        pcPages->ActivePage = tsSphere;
        return;
    }

    // get a box
    DWF_BoxR* pBox = dynamic_cast<DWF_BoxR*>(m_pShape3D);

    // found it?
    if (pBox)
    {
        // set the editor caption
        Caption = laBoxTitle->Caption;

        // expose the box min value
        gvBoxMin->SetX(pBox->m_Min.m_X);
        gvBoxMin->SetY(pBox->m_Min.m_Y);
        gvBoxMin->SetZ(pBox->m_Min.m_Z);

        // expose the box max value
        gvBoxMax->SetX(pBox->m_Max.m_X);
        gvBoxMax->SetY(pBox->m_Max.m_Y);
        gvBoxMax->SetZ(pBox->m_Max.m_Z);

        // show the box editor
        pcPages->ActivePage = tsBox;
        return;
    }

    // get a disk
    DWF_DiskR* pDisk = dynamic_cast<DWF_DiskR*>(m_pShape3D);

    // found it?
    if (pDisk)
    {
        // set the editor caption
        Caption = laDiskTitle->Caption;

        // expose the disk center value
        gvDiskCenter->SetX(pDisk->m_Center.m_X);
        gvDiskCenter->SetY(pDisk->m_Center.m_Y);
        gvDiskCenter->SetZ(pDisk->m_Center.m_Z);

        // expose the disk normal value
        gvDiskNormal->SetX(pDisk->m_Normal.m_X);
        gvDiskNormal->SetY(pDisk->m_Normal.m_Y);
        gvDiskNormal->SetZ(pDisk->m_Normal.m_Z);

        // expose the disk radius value
        edDiskRadius->Text = ::FloatToStr(pDisk->m_Radius);

        // show the disk editor
        pcPages->ActivePage = tsDisk;
        return;
    }

    // get a cylinder
    DWF_CylinderR* pCylinder = dynamic_cast<DWF_CylinderR*>(m_pShape3D);

    // found it?
    if (pCylinder)
    {
        // set the editor caption
        Caption = laCylinderTitle->Caption;

        // expose the cylinder start value
        gvCylinderStart->SetX(pCylinder->m_Start.m_X);
        gvCylinderStart->SetY(pCylinder->m_Start.m_Y);
        gvCylinderStart->SetY(pCylinder->m_Start.m_Y);

        // expose the cylinder end value
        gvCylinderEnd->SetX(pCylinder->m_End.m_X);
        gvCylinderEnd->SetY(pCylinder->m_End.m_Y);
        gvCylinderEnd->SetY(pCylinder->m_End.m_Y);

        // expose the cylinder radius value
        edCylinderRadius->Text = ::FloatToStr(pCylinder->m_Radius);

        // show the cylinder editor
        pcPages->ActivePage = tsCylinder;
        return;
    }
}
//---------------------------------------------------------------------------
void __fastcall TGeometricShapeEditor::FormShow(TObject *Sender)
{
    // if the circle editor is visible, calculate the real radius edit width
    if (pcPages->ActivePage == tsCircle)
        edCircleRadius->Width =
                (gvCircleCenter->edY->Left + gvCircleCenter->edY->Width) - gvCircleCenter->edX->Left;
}
//---------------------------------------------------------------------------
void __fastcall TGeometricShapeEditor::edPlaneAChange(TObject* pSender)
{
    TGeometricFrameCommon::ValidateFloatResult(edPlaneA, m_LastValidPlaneA);
}
//---------------------------------------------------------------------------
void __fastcall TGeometricShapeEditor::edPlaneBChange(TObject* pSender)
{
    TGeometricFrameCommon::ValidateFloatResult(edPlaneB, m_LastValidPlaneB);
}
//---------------------------------------------------------------------------
void __fastcall TGeometricShapeEditor::edPlaneCChange(TObject* pSender)
{
    TGeometricFrameCommon::ValidateFloatResult(edPlaneC, m_LastValidPlaneC);
}
//---------------------------------------------------------------------------
void __fastcall TGeometricShapeEditor::edPlaneDChange(TObject* pSender)
{
    TGeometricFrameCommon::ValidateFloatResult(edPlaneD, m_LastValidPlaneD);
}
//---------------------------------------------------------------------------
void __fastcall TGeometricShapeEditor::edCircleRadiusChange(TObject* pSender)
{
    TGeometricFrameCommon::ValidateFloatResult(edCircleRadius, m_LastValidCircleRadius);
}
//---------------------------------------------------------------------------
void __fastcall TGeometricShapeEditor::edRectLeftChange(TObject* pSender)
{
    TGeometricFrameCommon::ValidateFloatResult(edRectLeft, m_LastValidRectLeft);
}
//---------------------------------------------------------------------------
void __fastcall TGeometricShapeEditor::edRectTopChange(TObject* pSender)
{
    TGeometricFrameCommon::ValidateFloatResult(edRectTop, m_LastValidRectTop);
}
//---------------------------------------------------------------------------
void __fastcall TGeometricShapeEditor::edRectRightChange(TObject* pSender)
{
    TGeometricFrameCommon::ValidateFloatResult(edRectRight, m_LastValidRectRight);
}
//---------------------------------------------------------------------------
void __fastcall TGeometricShapeEditor::edRectBottomChange(TObject* pSender)
{
    TGeometricFrameCommon::ValidateFloatResult(edRectBottom, m_LastValidRectBottom);
}
//---------------------------------------------------------------------------
void __fastcall TGeometricShapeEditor::edSphereRadiusChange(TObject* pSender)
{
    TGeometricFrameCommon::ValidateFloatResult(edSphereRadius, m_LastValidSphereRadius);
}
//---------------------------------------------------------------------------
void __fastcall TGeometricShapeEditor::edDiskRadiusChange(TObject* pSender)
{
    TGeometricFrameCommon::ValidateFloatResult(edDiskRadius, m_LastValidDiskRadius);
}
//---------------------------------------------------------------------------
void __fastcall TGeometricShapeEditor::edCylinderRadiusChange(TObject* pSender)
{
    TGeometricFrameCommon::ValidateFloatResult(edCylinderRadius, m_LastValidCylinderRadius);
}
//---------------------------------------------------------------------------
void __fastcall TGeometricShapeEditor::btCancelClick(TObject* pSender)
{
    // ignore all changes and close the form
    Close();
}
//---------------------------------------------------------------------------
void __fastcall TGeometricShapeEditor::btOKClick(TObject* pSender)
{
    if (pcPages->ActivePage == tsLine)
    {
        // get a 2d line
        DWF_Line2DR* pLine2D = dynamic_cast<DWF_Line2DR*>(m_pShape2D);

        // found it?
        if (pLine2D)
        {
            // apply the new line point value
            pLine2D->SetPoint(DWF_Vector2DR(gvLinePoint->GetX(), gvLinePoint->GetY()));

            // apply the new line direction value
            pLine2D->SetDir(DWF_Vector2DR(gvLineDir->GetX(), gvLineDir->GetY()));
        }

        // get a 3d line
        DWF_Line3DR* pLine3D = dynamic_cast<DWF_Line3DR*>(m_pShape3D);

        // found it?
        if (pLine3D)
        {
            // apply the new line point value
            pLine3D->SetPoint(DWF_Vector3DR(gvLinePoint->GetX(), gvLinePoint->GetY(), gvLinePoint->GetZ()));

            // apply the new line direction value
            pLine3D->SetDir(DWF_Vector3DR(gvLineDir->GetX(), gvLineDir->GetY(), gvLineDir->GetZ()));
        }
    }
    else
    if (pcPages->ActivePage == tsRay)
    {
        // get a 2d ray
        DWF_Ray2DR* pRay2D = dynamic_cast<DWF_Ray2DR*>(m_pShape2D);

        // found it?
        if (pRay2D)
        {
            // apply the new ray point value
            pRay2D->SetPos(DWF_Vector2DR(gvRayPos->GetX(), gvRayPos->GetY()));

            // apply the new direction value
            pRay2D->SetDir(DWF_Vector2DR(gvRayDir->GetX(), gvRayDir->GetY()));
        }

        // get a 3d ray
        DWF_Ray3DR* pRay3D = dynamic_cast<DWF_Ray3DR*>(m_pShape3D);

        // found it?
        if (pRay3D)
        {
            // apply the new ray point value
            pRay3D->SetPos(DWF_Vector3DR(gvRayPos->GetX(), gvRayPos->GetY(), gvRayPos->GetZ()));

            // apply the new direction value
            pRay3D->SetDir(DWF_Vector3DR(gvRayDir->GetX(), gvRayDir->GetY(), gvRayDir->GetZ()));
        }
    }
    else
    if (pcPages->ActivePage == tsSegment)
    {
        // get a 2d line segment
        DWF_Segment2DR* pSegment2D = dynamic_cast<DWF_Segment2DR*>(m_pShape2D);

        // found it?
        if (pSegment2D)
        {
            // apply the new line segment start value
            pSegment2D->m_Start = DWF_Vector2DR(gvSegmentStart->GetX(), gvSegmentStart->GetY());

            // apply the new line segment end value
            pSegment2D->m_End = DWF_Vector2DR(gvSegmentEnd->GetX(), gvSegmentEnd->GetY());
        }

        // get a 3d line segment
        DWF_Segment3DR* pSegment3D = dynamic_cast<DWF_Segment3DR*>(m_pShape3D);

        // found it?
        if (pSegment3D)
        {
            // apply the new line segment start value
            pSegment3D->m_Start = DWF_Vector3DR(gvSegmentStart->GetX(), gvSegmentStart->GetY(), gvSegmentStart->GetZ());

            // apply the new line segment end value
            pSegment3D->m_End = DWF_Vector3DR(gvSegmentEnd->GetX(), gvSegmentEnd->GetY(), gvSegmentEnd->GetZ());
        }
    }
    else
    if (pcPages->ActivePage == tsPlane)
    {
        // get a plane
        DWF_PlaneR* pPlane = dynamic_cast<DWF_PlaneR*>(m_pShape3D);

        // found it?
        if (pPlane)
        {
            // apply the new rect left, top, right and bottom values
            pPlane->m_A = ::StrToFloat(edPlaneA->Text);
            pPlane->m_B = ::StrToFloat(edPlaneB->Text);
            pPlane->m_C = ::StrToFloat(edPlaneC->Text);
            pPlane->m_D = ::StrToFloat(edPlaneD->Text);
        }
    }
    else
    if (pcPages->ActivePage == tsPolygon)
    {
        // get a 2d polygon
        DWF_Polygon2DR* pPolygon2D = dynamic_cast<DWF_Polygon2DR*>(m_pShape2D);

        // found it?
        if (pPolygon2D)
        {
            // apply the new polygon vertices values
            pPolygon2D->SetVertex1(DWF_Vector2DR(gvPolygonV1->GetX(), gvPolygonV1->GetY()));
            pPolygon2D->SetVertex2(DWF_Vector2DR(gvPolygonV2->GetX(), gvPolygonV2->GetY()));
            pPolygon2D->SetVertex3(DWF_Vector2DR(gvPolygonV3->GetX(), gvPolygonV3->GetY()));
        }

        // get a 3d polygon
        DWF_Polygon3DR* pPolygon3D = dynamic_cast<DWF_Polygon3DR*>(m_pShape3D);

        // found it?
        if (pPolygon3D)
        {
            // apply the new polygon vertices values
            pPolygon3D->SetVertex1(DWF_Vector3DR(gvPolygonV1->GetX(), gvPolygonV1->GetY(), gvPolygonV1->GetZ()));
            pPolygon3D->SetVertex2(DWF_Vector3DR(gvPolygonV2->GetX(), gvPolygonV2->GetY(), gvPolygonV2->GetZ()));
            pPolygon3D->SetVertex3(DWF_Vector3DR(gvPolygonV3->GetX(), gvPolygonV3->GetY(), gvPolygonV3->GetZ()));
        }
    }
    else
    if (pcPages->ActivePage == tsCircle)
    {
        // get a circle
        DWF_CircleR* pCircle = dynamic_cast<DWF_CircleR*>(m_pShape2D);

        // found it?
        if (pCircle)
        {
            // apply the new circle center value
            pCircle->m_Center = DWF_Vector2DR(gvCircleCenter->GetX(), gvCircleCenter->GetY());

            // apply the new circle radius value
            pCircle->m_Radius = ::StrToFloat(edCircleRadius->Text);
        }
    }
    else
    if (pcPages->ActivePage == tsRect)
    {
        // get a rectangle
        DWF_RectR* pRect = dynamic_cast<DWF_RectR*>(m_pShape2D);

        // found it?
        if (pRect)
        {
            // apply the new rect left, top, right and bottom values
            pRect->m_Left   = ::StrToFloat(edRectLeft->Text);
            pRect->m_Top    = ::StrToFloat(edRectTop->Text);
            pRect->m_Right  = ::StrToFloat(edRectRight->Text);
            pRect->m_Bottom = ::StrToFloat(edRectBottom->Text);
        }
    }
    else
    if (pcPages->ActivePage == tsSphere)
    {
        // get a sphere
        DWF_SphereR* pSphere = dynamic_cast<DWF_SphereR*>(m_pShape3D);

        // found it?
        if (pSphere)
        {
            // apply the new sphere center value
            pSphere->m_Center = DWF_Vector3DR(gvSphereCenter->GetX(), gvSphereCenter->GetY(), gvSphereCenter->GetZ());

            // apply the new sphere radius value
            pSphere->m_Radius = ::StrToFloat(edSphereRadius->Text);
        }
    }
    else
    if (pcPages->ActivePage == tsBox)
    {
        // get a box
        DWF_BoxR* pBox = dynamic_cast<DWF_BoxR*>(m_pShape3D);

        // found it?
        if (pBox)
        {
            // apply the new box min value
            pBox->m_Min = DWF_Vector3DR(gvBoxMin->GetX(), gvBoxMin->GetY(), gvBoxMin->GetZ());

            // apply the new box max value
            pBox->m_Max = DWF_Vector3DR(gvBoxMax->GetX(), gvBoxMax->GetY(), gvBoxMax->GetZ());
        }
    }
    else
    if (pcPages->ActivePage == tsDisk)
    {
        // get a disk
        DWF_DiskR* pDisk = dynamic_cast<DWF_DiskR*>(m_pShape3D);

        // found it?
        if (pDisk)
        {
            // apply the new disk center value
            pDisk->m_Center = DWF_Vector3DR(gvDiskCenter->GetX(), gvDiskCenter->GetY(), gvDiskCenter->GetZ());

            // apply the new disk normal value
            pDisk->m_Normal = DWF_Vector3DR(gvDiskNormal->GetX(), gvDiskNormal->GetY(), gvDiskNormal->GetZ());

            // apply the new disk radius value
            pDisk->m_Radius = ::StrToFloat(edDiskRadius->Text);
        }
    }
    else
    if (pcPages->ActivePage == tsCylinder)
    {
        // get a cylinder
        DWF_CylinderR* pCylinder = dynamic_cast<DWF_CylinderR*>(m_pShape3D);

        // found it?
        if (pCylinder)
        {
            // apply the new cylinder start value
            pCylinder->m_Start = DWF_Vector3DR(gvCylinderStart->GetX(), gvCylinderStart->GetY(), gvCylinderStart->GetZ());

            // apply the new cylinder end value
            pCylinder->m_End = DWF_Vector3DR(gvCylinderEnd->GetX(), gvCylinderEnd->GetY(), gvCylinderEnd->GetZ());

            // apply the new cylinder radius value
            pCylinder->m_Radius = ::StrToFloat(edCylinderRadius->Text);
        }
    }

    Close();
}
//---------------------------------------------------------------------------
