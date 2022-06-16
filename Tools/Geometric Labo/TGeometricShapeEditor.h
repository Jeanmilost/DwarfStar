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

#ifndef TGeometricShapeEditorH
#define TGeometricShapeEditorH

// vcl
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Imaging.pngimage.hpp>
#include "TGeometricVectorFrame.h"

// dwarfstar engine
#include "DWF_Common_Types.h"
#include "DWF_Geometry_Shape.h"

using namespace DWF_Geometry;

/**
* Shape editor
*@author Jean-Milost Reymond
*/
class TGeometricShapeEditor : public TForm
{
    __published:
        TPageControl *pcPages;
        TTabSheet *tsLine;
        TTabSheet *tsRay;
        TTabSheet *tsSegment;
        TTabSheet *tsPolygon;
        TTabSheet *tsCircle;
        TTabSheet *tsRect;
        TPanel *paButtons;
        TButton *btOK;
        TButton *btCancel;
        TPanel *paLineHeader;
        TImage *imLine;
        TLabel *laLineTitle;
        TPanel *paRayHeader;
        TImage *imRay;
        TLabel *laRayTitle;
        TPanel *paSegmentHeader;
        TImage *imSegment;
        TLabel *laSegmentTitle;
        TPanel *paPolygonHeader;
        TImage *imPolygon;
        TLabel *laPolygonTitle;
        TPanel *paCircleHeader;
        TImage *imCircle;
        TLabel *laCircleTitle;
        TPanel *paRectHeader;
        TImage *imRect;
        TLabel *laRectTitle;
        TPanel *paLineValues;
        TPanel *paLinePoint;
        TGeometricVectorFrame *gvLinePoint;
        TLabel *laLinePointCaption;
        TPanel *paLineDir;
        TLabel *laLineDirCaption;
        TGeometricVectorFrame *gvLineDir;
        TPanel *paRayValues;
        TPanel *paRayPos;
        TLabel *laRayPosCaption;
        TGeometricVectorFrame *gvRayPos;
        TPanel *paRayDir;
        TLabel *laRayDirCaption;
        TGeometricVectorFrame *gvRayDir;
        TPanel *paSegmentValues;
        TPanel *paSegmentStart;
        TLabel *laSegmentStartCaption;
        TGeometricVectorFrame *gvSegmentStart;
        TPanel *paSegmentEnd;
        TLabel *laSegmentEndCaption;
        TGeometricVectorFrame *gvSegmentEnd;
        TPanel *paPolygonValues;
        TPanel *paPolygonV1;
        TLabel *laPolygonV1Caption;
        TGeometricVectorFrame *gvPolygonV1;
        TPanel *paPolygonV2;
        TLabel *laPolygonV2Caption;
        TGeometricVectorFrame *gvPolygonV2;
        TPanel *paPolygonV3;
        TLabel *laPolygonV3Caption;
        TGeometricVectorFrame *gvPolygonV3;
        TPanel *paCircleValues;
        TPanel *paCircleCenter;
        TLabel *laCircleCenterCaption;
        TGeometricVectorFrame *gvCircleCenter;
        TPanel *paCircleRadius;
        TLabel *laCircleRadiusCaption;
        TEdit *edCircleRadius;
        TPanel *paRectValues;
        TPanel *paRectLeftTop;
        TLabel *laRectLeftCaption;
        TPanel *paRectRightBottom;
        TEdit *edRectTop;
        TLabel *laRectTopCaption;
        TEdit *edRectLeft;
        TLabel *laRectRightCaption;
        TEdit *edRectRight;
        TLabel *laRectBottomCaption;
        TEdit *edRectBottom;
        TTabSheet *tsPlane;
        TPanel *paPlaneHeader;
        TImage *imPlane;
        TLabel *laPlaneTitle;
        TPanel *paPlaneValues;
        TPanel *paPlaneAB;
        TLabel *laPlaneACaption;
        TLabel *laPlaneBCaption;
        TEdit *edPlaneB;
        TEdit *edPlaneA;
        TPanel *paPlaneCD;
        TLabel *laPlaneCCaption;
        TLabel *laPlaneDCaption;
        TEdit *edPlaneC;
        TEdit *edPlaneD;
        TTabSheet *tsSphere;
        TTabSheet *tsBox;
        TTabSheet *tsDisk;
        TTabSheet *tsCylinder;
        TPanel *paSphereHeader;
        TImage *imSphere;
        TLabel *laSphereTitle;
        TPanel *paSphereValues;
        TPanel *paSphereCenter;
        TLabel *laSphereCenterCaption;
        TGeometricVectorFrame *gvSphereCenter;
        TPanel *paSphereRadius;
        TLabel *laSphereRadiusCaption;
        TEdit *edSphereRadius;
        TPanel *paBoxHeader;
        TImage *imBox;
        TLabel *laBoxTitle;
        TPanel *paBoxValues;
        TPanel *paBoxMin;
        TLabel *laBoxMinCaption;
        TGeometricVectorFrame *gvBoxMin;
        TPanel *paBoxMax;
        TLabel *laBoxMaxCaption;
        TGeometricVectorFrame *gvBoxMax;
        TPanel *paDiskValues;
        TPanel *paDiskCenter;
        TLabel *laDiskCenterCaption;
        TGeometricVectorFrame *gvDiskCenter;
        TPanel *paDiskNormal;
        TLabel *laDiskNormalCaption;
        TGeometricVectorFrame *gvDiskNormal;
        TPanel *paDiskRadius;
        TLabel *laDiskRadiusCaption;
        TPanel *paDiskHeader;
        TImage *imDisk;
        TLabel *laDiskTitle;
        TEdit *edDiskRadius;
        TPanel *paCylinderHeader;
        TImage *imCylinder;
        TLabel *laCylinderTitle;
        TPanel *paCylinderValues;
        TPanel *paCylinderStart;
        TLabel *laCylinderStartCaption;
        TGeometricVectorFrame *gvCylinderStart;
        TPanel *paCylinderEnd;
        TLabel *laCylinderEndCaption;
        TGeometricVectorFrame *gvCylinderEnd;
        TPanel *paCylinderRadius;
        TLabel *laCylinderRadiusCaption;
        TEdit *edCylinderRadius;

        void __fastcall FormShow(TObject* pSender);
        void __fastcall edPlaneAChange(TObject* pSender);
        void __fastcall edPlaneBChange(TObject* pSender);
        void __fastcall edPlaneCChange(TObject* pSender);
        void __fastcall edPlaneDChange(TObject* pSender);
        void __fastcall edCircleRadiusChange(TObject* pSender);
        void __fastcall edRectLeftChange(TObject* pSender);
        void __fastcall edRectTopChange(TObject* pSender);
        void __fastcall edRectRightChange(TObject* pSender);
        void __fastcall edRectBottomChange(TObject* pSender);
        void __fastcall btCancelClick(TObject* pSender);
        void __fastcall btOKClick(TObject* pSender);
        void __fastcall edSphereRadiusChange(TObject* pSender);
        void __fastcall edDiskRadiusChange(TObject* pSender);
        void __fastcall edCylinderRadiusChange(TObject* pSender);

    public:
        /**
        * Constructor
        *@param pOwner - form owner
        *@param pShape2D - 2d shape to edit
        */
        __fastcall TGeometricShapeEditor(TComponent* pOwner, DWF_Shape2D<M_Real>* pShape2D);

        /**
        * Constructor
        *@param pOwner - form owner
        *@param pShape3D - 3d shape to edit
        */
        __fastcall TGeometricShapeEditor(TComponent* pOwner, DWF_Shape3D<M_Real>* pShape3D);

    private:
        union
        {
            DWF_Shape2D<M_Real>* m_pShape2D;
            DWF_Shape3D<M_Real>* m_pShape3D;
        };

        std::wstring m_LastValidPlaneA;
        std::wstring m_LastValidPlaneB;
        std::wstring m_LastValidPlaneC;
        std::wstring m_LastValidPlaneD;
        std::wstring m_LastValidCircleRadius;
        std::wstring m_LastValidRectLeft;
        std::wstring m_LastValidRectTop;
        std::wstring m_LastValidRectRight;
        std::wstring m_LastValidRectBottom;
        std::wstring m_LastValidSphereRadius;
        std::wstring m_LastValidDiskRadius;
        std::wstring m_LastValidCylinderRadius;
};
extern PACKAGE TGeometricShapeEditor* GeometricShapeEditor;
#endif
