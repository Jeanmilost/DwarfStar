/****************************************************************************
 * ==> TGeometricDocument3D ------------------------------------------------*
 ****************************************************************************
 * Description : This module provides a geometric 3D shapes document        *
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

#include "TGeometricDocument3D.h"

// std
#include <memory>
#include <algorithm>

// dwarfstar engine
#include "DWF_Common_Helpers.h"
#include "DWF_Diagnostics_Exception.h"
#include "DWF_Geometry_Line.h"
#include "DWF_Geometry_Ray.h"
#include "DWF_Geometry_Segment.h"
#include "DWF_Geometry_Polygon.h"
#include "DWF_Geometry_Plane.h"
#include "DWF_Geometry_Sphere.h"
#include "DWF_Geometry_Box.h"
#include "DWF_Geometry_Disk.h"
#include "DWF_Geometry_Cylinder.h"
#include "DWF_Modeling_Surface.h"
#include "DWF_Modeling_Sphere.h"
#include "DWF_Modeling_Box.h"
#include "DWF_Modeling_Disk.h"
#include "DWF_Modeling_Cylinder.h"
#include "DWF_XML_Helper.h"

// interface
#include "TGlobalResources.h"
#include "TGeometricDocumentTags.h"

#ifdef DWF_OS_WIN
    #ifdef __llvm__
        #pragma link "glewSL.a"
    #else
        #pragma link "glewSL.lib"
    #endif
#endif

//---------------------------------------------------------------------------
// TGeometricDocument3D::IShape
//---------------------------------------------------------------------------
TGeometricDocument3D::IShape::IShape() :
    m_pShape(NULL),
    m_FadeOffset(0.05f),
    m_FadeValue(0.0f),
    m_Selected(false)
{}
//---------------------------------------------------------------------------
TGeometricDocument3D::IShape::~IShape()
{
    if (m_pShape)
        delete m_pShape;
}
//---------------------------------------------------------------------------
// TGeometricDocument3D::IGraphicShape
//---------------------------------------------------------------------------
TGeometricDocument3D::IGraphicShape::IGraphicShape() :
    m_pShape(NULL),
    m_GLObject(IE_GO_Plane),
    m_Focused(false)
{}
//---------------------------------------------------------------------------
TGeometricDocument3D::IGraphicShape::~IGraphicShape()
{}
//---------------------------------------------------------------------------
// TGeometricDocument3D::IArcBall
//---------------------------------------------------------------------------
TGeometricDocument3D::IArcBall::IArcBall() :
    m_AngleX(M_PI * 0.125),
    m_AngleY(M_PI * 0.25),
    m_Radius(2.5)
{}
//---------------------------------------------------------------------------
TGeometricDocument3D::IArcBall::~IArcBall()
{}
//---------------------------------------------------------------------------
// TGeometricDocument3D
//---------------------------------------------------------------------------
TGeometricDocument3D::TGeometricDocument3D(HWND hWnd) :
    TGeometricDocument(),
    m_hWnd(hWnd),
    m_MaxAngle(M_PI * M_Real(2.0)),
    m_InsideSimEnabled(false)
{
    // initialize the document
    if (!Initialize())
        M_THROW_EXCEPTION("The 3D document could not be initialized");
}
//---------------------------------------------------------------------------
TGeometricDocument3D::~TGeometricDocument3D()
{
    // delete the shapes
    DWF_STDHelper::DelAndClear(m_Shapes);

    // delete the meshes used to draw the shapes
    for (IMeshDictionary::iterator it = m_Meshes.begin(); it != m_Meshes.end(); ++it)
        DWF_STDHelper::DelAndClear(it->second);

    // shutdown opengl
    m_Renderer.DisableOpenGL(m_hWnd);
}
//---------------------------------------------------------------------------
void TGeometricDocument3D::AddLine(const DWF_Vector3DR& point, const DWF_Vector3DR& dir)
{
    // create a line with a random color
    std::auto_ptr<IShape> pShape(new IShape());
    pShape->m_pShape = new DWF_Line3DR(point, dir);
    pShape->m_Color  = GetRandomColor();

    // add it to the document
    m_Shapes.push_back(pShape.get());
    pShape.release();

    // focus the newly created object
    m_FocusedIndex = m_Shapes.size() - 1;

    Touch();
}
//---------------------------------------------------------------------------
void TGeometricDocument3D::AddRay(const DWF_Vector3DR& point, const DWF_Vector3DR& dir)
{
    // create a ray with a random color
    std::auto_ptr<IShape> pShape(new IShape());
    pShape->m_pShape = new DWF_Ray3DR(point, dir);
    pShape->m_Color  = GetRandomColor();

    // add it to the document
    m_Shapes.push_back(pShape.get());
    pShape.release();

    // focus the newly created object
    m_FocusedIndex = m_Shapes.size() - 1;

    Touch();
}
//---------------------------------------------------------------------------
void TGeometricDocument3D::AddSegment(const DWF_Vector3DR& start, const DWF_Vector3DR& end)
{
    // create a line segment with a random color
    std::auto_ptr<IShape> pShape(new IShape());
    pShape->m_pShape = new DWF_Segment3DR(start, end);
    pShape->m_Color  = GetRandomColor();

    // add it to the document
    m_Shapes.push_back(pShape.get());
    pShape.release();

    // focus the newly created object
    m_FocusedIndex = m_Shapes.size() - 1;

    Touch();
}
//---------------------------------------------------------------------------
void TGeometricDocument3D::AddPolygon(const DWF_Vector3DR& v1,
                                      const DWF_Vector3DR& v2,
                                      const DWF_Vector3DR& v3)
{
    // create a polygon with a random color
    std::auto_ptr<IShape> pShape(new IShape());
    pShape->m_pShape = new DWF_Polygon3DR(v1, v2, v3);
    pShape->m_Color  = GetRandomColor();

    // add it to the document
    m_Shapes.push_back(pShape.get());
    pShape.release();

    // focus the newly created object
    m_FocusedIndex = m_Shapes.size() - 1;

    Touch();
}
//---------------------------------------------------------------------------
void TGeometricDocument3D::AddPlane(const DWF_Vector3DR& point, const DWF_Vector3DR& normal)
{
    // create a rectangle with a random color
    std::auto_ptr<IShape> pShape(new IShape());
    pShape->m_pShape       = new DWF_PlaneR(DWF_PlaneR::FromPointNormal(point, normal));
    pShape->m_Color        = GetRandomColor();
    pShape->m_VirtualCoord = point;

    // add it to the document
    m_Shapes.push_back(pShape.get());
    pShape.release();

    // focus the newly created object
    m_FocusedIndex = m_Shapes.size() - 1;

    Touch();
}
//---------------------------------------------------------------------------
void TGeometricDocument3D::AddSphere(const DWF_Vector3DR& center, M_Real radius)
{
    // create a rectangle with a random color
    std::auto_ptr<IShape> pShape(new IShape());
    pShape->m_pShape = new DWF_SphereR(center, radius);
    pShape->m_Color  = GetRandomColor();

    // add it to the document
    m_Shapes.push_back(pShape.get());
    pShape.release();

    // focus the newly created object
    m_FocusedIndex = m_Shapes.size() - 1;

    Touch();
}
//---------------------------------------------------------------------------
void TGeometricDocument3D::AddBox(const DWF_Vector3DR& min, const DWF_Vector3DR& max)
{
    // create a rectangle with a random color
    std::auto_ptr<IShape> pShape(new IShape());
    pShape->m_pShape = new DWF_BoxR(min, max);
    pShape->m_Color  = GetRandomColor();

    // add it to the document
    m_Shapes.push_back(pShape.get());
    pShape.release();

    // focus the newly created object
    m_FocusedIndex = m_Shapes.size() - 1;

    Touch();
}
//---------------------------------------------------------------------------
void TGeometricDocument3D::AddDisk(const DWF_Vector3DR& center,
                                   const DWF_Vector3DR& normal,
                                         M_Real         radius)
{
    // create a rectangle with a random color
    std::auto_ptr<IShape> pShape(new IShape());
    pShape->m_pShape = new DWF_DiskR(center, normal, radius);
    pShape->m_Color  = GetRandomColor();

    // add it to the document
    m_Shapes.push_back(pShape.get());
    pShape.release();

    // focus the newly created object
    m_FocusedIndex = m_Shapes.size() - 1;

    Touch();
}
//---------------------------------------------------------------------------
void TGeometricDocument3D::AddCylinder(const DWF_Vector3DR& start, const DWF_Vector3DR& end, M_Real radius)
{
    // create a rectangle with a random color
    std::auto_ptr<IShape> pShape(new IShape());
    pShape->m_pShape = new DWF_CylinderR(start, end, radius);
    pShape->m_Color  = GetRandomColor();

    // add it to the document
    m_Shapes.push_back(pShape.get());
    pShape.release();

    // focus the newly created object
    m_FocusedIndex = m_Shapes.size() - 1;

    Touch();
}
//---------------------------------------------------------------------------
void TGeometricDocument3D::Select(std::size_t index, bool selected) const
{
    if (index >= m_Shapes.size())
        return;

    // select or unselect the shape
    m_Shapes[index]->m_Selected = selected;
}
//---------------------------------------------------------------------------
void TGeometricDocument3D::Reset(std::size_t index) const
{
    if (index >= m_Shapes.size())
        return;

    // reset the shape
    m_Shapes[index]->m_Selected  = false;
    m_Shapes[index]->m_FadeValue = 0.0f;
}
//---------------------------------------------------------------------------
void TGeometricDocument3D::Reset(void* pShape) const
{
    // iterate through shapes
    for (std::size_t i = 0; i < m_Shapes.size(); ++i)
        // found shape to reset?
        if (m_Shapes[i]->m_pShape == pShape)
        {
            Reset(i);
            return;
        }
}
//---------------------------------------------------------------------------
void TGeometricDocument3D::EnableInsideSimulator(bool value)
{
    m_InsideSimEnabled = value;

    // reset the simulator point if disabled
    if (!m_InsideSimEnabled)
        m_Point = DWF_Vector3DR();
}
//---------------------------------------------------------------------------
DWF_Vector3DR TGeometricDocument3D::GetInsideSimulatorPoint() const
{
    return m_Point;
}
//---------------------------------------------------------------------------
void* TGeometricDocument3D::GetShape(std::size_t index) const
{
    if (index >= m_Shapes.size())
        return NULL;

    return m_Shapes[index]->m_pShape;
}
//---------------------------------------------------------------------------
std::size_t TGeometricDocument3D::GetShapeCount() const
{
    return m_Shapes.size();
}
//---------------------------------------------------------------------------
DWF_Shape3D<M_Real>* TGeometricDocument3D::GetFocused() const
{
    if (m_FocusedIndex >= m_Shapes.size())
        return NULL;

    return m_Shapes[m_FocusedIndex]->m_pShape;
}
//---------------------------------------------------------------------------
DWF_Vector3DR TGeometricDocument3D::GetPoint() const
{
    return m_Point;
}
//---------------------------------------------------------------------------
void TGeometricDocument3D::SetPoint(const DWF_Vector3DR& point)
{
    m_Point = point;
}
//---------------------------------------------------------------------------
void TGeometricDocument3D::CreateViewport(int width, int height)
{
    m_Renderer.CreateViewport(width, height);

    // calculate aspect ratio
    const float aspect = float(width) / float(height);
    const float zNear  = 1.0f;
    const float zFar   = 99999.0f;

    // calculate the projection matrix
    m_Projection = m_Renderer.GetProjection(45.0f, aspect, zNear, zFar);

    // connect the projection matrix to the shader
    m_Renderer.SetProjectionMatrix(&m_Shader, m_Projection);

    // calculate the current view matrix
    m_View = GetArcBallMatrix(m_Arcball);
}
//---------------------------------------------------------------------------
void TGeometricDocument3D::MoveCamera(M_Real offsetX, M_Real offsetY, M_Real offsetRadius)
{
    // scale the offset values to match with the OpenGL coordinate system
    offsetX      *= 0.01f;
    offsetY      *= 0.01f;
    offsetRadius *= 0.01f;

    // update the arcball values
    m_Arcball.m_AngleX = std::fmod(m_Arcball.m_AngleX + offsetX, m_MaxAngle);
    m_Arcball.m_AngleY = std::fmod(m_Arcball.m_AngleY + offsetY, m_MaxAngle);
    m_Arcball.m_Radius =
            std::min(std::max(m_Arcball.m_Radius + offsetRadius, M_Real(1.0)), M_Real(100.0));

    m_View = GetArcBallMatrix(m_Arcball);
}
//---------------------------------------------------------------------------
void TGeometricDocument3D::InflateFocused(M_Real offsetX, M_Real offsetY, M_Real offsetZ)
{
    // inside simulator enabled?
    if (m_InsideSimEnabled)
        return;

    DWF_Shape3D<M_Real>* pShape = GetFocused();

    if (!pShape)
        return;

    // scale the offset values to match with the OpenGL coordinate system
    offsetX *= 0.01f;
    offsetY *= 0.01f;
    offsetZ *= 0.01f;

    switch (pShape->GetFigure())
    {
        case DWF_Shape3D<M_Real>::IE_SF_Line:
        case DWF_Shape3D<M_Real>::IE_SF_Ray:
        case DWF_Shape3D<M_Real>::IE_SF_Plane:
            // the size of these shapes is not allowed to change
            ::PlaySound((LPCWSTR)SND_ALIAS_SYSTEMEXCLAMATION, NULL, SND_ALIAS_ID | SND_ASYNC);
            return;

        case DWF_Shape3D<M_Real>::IE_SF_Segment:
        {
            // get line segment to update
            DWF_Segment3DR* pSegment = static_cast<DWF_Segment3DR*>(pShape);

            // calculate segment direction
            const DWF_Vector3DR dir = (pSegment->m_End - pSegment->m_Start).Normalize();

            // combine offsets
            const M_Real offset = (offsetX ? offsetX : (offsetY ? offsetY : offsetZ));

            // update the segment endpoints
            pSegment->m_Start.m_X -= (offset * dir.m_X);
            pSegment->m_Start.m_Y -= (offset * dir.m_Y);
            pSegment->m_Start.m_Z -= (offset * dir.m_Z);
            pSegment->m_End.m_X   += (offset * dir.m_X);
            pSegment->m_End.m_Y   += (offset * dir.m_Y);
            pSegment->m_End.m_Z   += (offset * dir.m_Z);

            Touch();
            return;
        }

        case DWF_Shape3D<M_Real>::IE_SF_Polygon:
        {
            // get polygon to update
            DWF_Polygon3DR* pPolygon = static_cast<DWF_Polygon3DR*>(pShape);

            // get polygon center
            const DWF_Vector3DR center = pPolygon->GetCenter();

            // iterate through each polygon vertices
            for (std::size_t i = 0; i < 3; ++i)
            {
                // get next vertex and calculate his direction
                const DWF_Vector3DR vertex = pPolygon->GetVertex(i);
                const DWF_Vector3DR dir    = (vertex - center).Normalize();

                // increase the vertex position from center
                pPolygon->SetVertex(i, DWF_Vector3DR(vertex.m_X + (offsetX * dir.m_X),
                                                     vertex.m_Y + (offsetY * dir.m_Y),
                                                     vertex.m_Z + (offsetY * dir.m_Z)));
            }

            Touch();
            return;
        }

        case DWF_Shape3D<M_Real>::IE_SF_Sphere:
        {
            // update sphere size
            DWF_SphereR* pSphere  = static_cast<DWF_SphereR*>(pShape);
            pSphere->m_Radius    += M_Real(offsetX ? offsetX : (offsetY ? offsetY : offsetZ));

            // check if circle radius is out of bounds, correct it if yes
            if (pSphere->m_Radius <= 0.001f)
                pSphere->m_Radius = 0.001f;

            Touch();
            return;
        }

        case DWF_Shape3D<M_Real>::IE_SF_Box:
        {
            // update box size
            DWF_BoxR* pBox  = static_cast<DWF_BoxR*>(pShape);
            pBox->m_Min.m_X -= offsetX * M_Real(0.5);
            pBox->m_Max.m_X += offsetX * M_Real(0.5);
            pBox->m_Min.m_Y -= offsetY * M_Real(0.5);
            pBox->m_Max.m_Y += offsetY * M_Real(0.5);
            pBox->m_Min.m_Z -= offsetZ * M_Real(0.5);
            pBox->m_Max.m_Z += offsetZ * M_Real(0.5);

            Touch();
            return;
        }

        case DWF_Shape3D<M_Real>::IE_SF_Disk:
        {
            // update disk size
            DWF_DiskR* pDisk  = static_cast<DWF_DiskR*>(pShape);
            pDisk->m_Radius  += M_Real(offsetX ? offsetX : (offsetY ? offsetY : offsetZ));

            // check if circle radius is out of bounds, correct it if yes
            if (pDisk->m_Radius <= 0.001f)
                pDisk->m_Radius = 0.001f;

            Touch();
            return;
        }

        case DWF_Shape3D<M_Real>::IE_SF_Cylinder:
        {
            // update cylinder size
            DWF_CylinderR* pCylinder  = static_cast<DWF_CylinderR*>(pShape);
            pCylinder->m_Radius      += M_Real(offsetX ? offsetX : offsetY);

            // check if circle radius is out of bounds, correct it if yes
            if (pCylinder->m_Radius <= 0.001f)
                pCylinder->m_Radius = 0.001f;

            // calculate segment direction
            const DWF_Vector3DR dir = (pCylinder->m_End - pCylinder->m_Start).Normalize();

            // update the segment endpoints
            pCylinder->m_Start.m_X -= (offsetZ * dir.m_X);
            pCylinder->m_Start.m_Y -= (offsetZ * dir.m_Y);
            pCylinder->m_Start.m_Z -= (offsetZ * dir.m_Z);
            pCylinder->m_End.m_X   += (offsetZ * dir.m_X);
            pCylinder->m_End.m_Y   += (offsetZ * dir.m_Y);
            pCylinder->m_End.m_Z   += (offsetZ * dir.m_Z);

            Touch();
            return;
        }
    }
}
//---------------------------------------------------------------------------
void TGeometricDocument3D::MoveFocused(M_Real offsetX, M_Real offsetY, M_Real offsetZ)
{
    // scale the offset values to match with the OpenGL coordinate system
    offsetX *= 0.01f;
    offsetY *= 0.01f;
    offsetZ *= 0.01f;

    // inside simulator enabled?
    if (m_InsideSimEnabled)
    {
        // calculate the next position
        m_Point.m_X += offsetX;
        m_Point.m_Y -= offsetY;
        m_Point.m_Z -= offsetZ;
        return;
    }

    DWF_Shape3D<M_Real>* pShape = GetFocused();

    if (!pShape)
        return;

    switch (pShape->GetFigure())
    {
        case DWF_Shape3D<M_Real>::IE_SF_Line:
        {
            // get the line to update
            DWF_Line3DR* pLine = static_cast<DWF_Line3DR*>(pShape);

            // get the current line position
            DWF_Vector3DR linePos = pLine->GetPoint();

            // calculate the next position
            linePos.m_X += offsetX;
            linePos.m_Y -= offsetY;
            linePos.m_Z -= offsetZ;

            // update the line position
            pLine->SetPoint(linePos);

            Touch();
            return;
        }

        case DWF_Shape3D<M_Real>::IE_SF_Ray:
        {
            // get the ray to update
            DWF_Ray3DR* pRay = static_cast<DWF_Ray3DR*>(pShape);

            // get the current ray position
            DWF_Vector3DR rayPos = pRay->GetPos();

            // calculate the next position
            rayPos.m_X += offsetX;
            rayPos.m_Y -= offsetY;
            rayPos.m_Z -= offsetZ;

            // update the ray position
            pRay->SetPos(rayPos);

            Touch();
            return;
        }

        case DWF_Shape3D<M_Real>::IE_SF_Segment:
        {
            // get the segment to update
            DWF_Segment3DR* pSegment = static_cast<DWF_Segment3DR*>(pShape);

            // update the segment start position
            pSegment->m_Start.m_X += offsetX;
            pSegment->m_Start.m_Y -= offsetY;
            pSegment->m_Start.m_Z -= offsetZ;

            // update the segment end position
            pSegment->m_End.m_X += offsetX;
            pSegment->m_End.m_Y -= offsetY;
            pSegment->m_End.m_Z -= offsetZ;

            Touch();
            return;
        }

        case DWF_Shape3D<M_Real>::IE_SF_Plane:
        {
            // update the plane position
            m_Shapes[m_FocusedIndex]->m_VirtualCoord.m_X += offsetX;
            m_Shapes[m_FocusedIndex]->m_VirtualCoord.m_Y -= offsetY;
            m_Shapes[m_FocusedIndex]->m_VirtualCoord.m_Z -= offsetZ;

            Touch();
            return;
        }

        case DWF_Shape3D<M_Real>::IE_SF_Polygon:
        {
            // get the polygon to update
            DWF_Polygon3DR* pPolygon = static_cast<DWF_Polygon3DR*>(pShape);

            // update the polygon position
            for (std::size_t i = 0; i < 3; ++i)
                pPolygon->SetVertex(i, DWF_Vector3DR(pPolygon->GetVertex(i).m_X + offsetX,
                                                     pPolygon->GetVertex(i).m_Y - offsetY,
                                                     pPolygon->GetVertex(i).m_Z - offsetZ));

            Touch();
            return;
        }

        case DWF_Shape3D<M_Real>::IE_SF_Sphere:
        {
            // update the sphereposition
            DWF_SphereR* pSphere   = static_cast<DWF_SphereR*>(pShape);
            pSphere->m_Center.m_X += offsetX;
            pSphere->m_Center.m_Y -= offsetY;
            pSphere->m_Center.m_Z -= offsetZ;

            //REM Validate(pSphere->m_Radius, pSphere->m_Center, DWF_RectR(-1.0f, -3.0f, 1.0f, -1.0f));

            Touch();
            return;
        }

        case DWF_Shape3D<M_Real>::IE_SF_Box:
        {
            // update the box position
            DWF_BoxR* pBox = static_cast<DWF_BoxR*>(pShape);
            pBox->m_Min.m_X += offsetX;
            pBox->m_Min.m_Y -= offsetY;
            pBox->m_Min.m_Z -= offsetZ;
            pBox->m_Max.m_X += offsetX;
            pBox->m_Max.m_Y -= offsetY;
            pBox->m_Max.m_Z -= offsetZ;

            Touch();
            return;
        }

        case DWF_Shape3D<M_Real>::IE_SF_Disk:
        {
            // update the disk position
            DWF_DiskR* pDisk = static_cast<DWF_DiskR*>(pShape);
            pDisk->m_Center.m_X += offsetX;
            pDisk->m_Center.m_Y -= offsetY;
            pDisk->m_Center.m_Z -= offsetZ;

            Touch();
            return;
        }

        case DWF_Shape3D<M_Real>::IE_SF_Cylinder:
        {
            // update the cylinder position
            DWF_CylinderR* pCylinder = static_cast<DWF_CylinderR*>(pShape);
            pCylinder->m_Start.m_X += offsetX;
            pCylinder->m_Start.m_Y -= offsetY;
            pCylinder->m_Start.m_Z -= offsetZ;
            pCylinder->m_End.m_X   += offsetX;
            pCylinder->m_End.m_Y   -= offsetY;
            pCylinder->m_End.m_Z   -= offsetZ;

            Touch();
            return;
        }
    }
}
//---------------------------------------------------------------------------
void TGeometricDocument3D::RotateFocused(M_Real offsetX, M_Real offsetY, M_Real offsetZ)
{
    // inside simulator enabled?
    if (m_InsideSimEnabled)
        return;

    DWF_Shape3D<M_Real>* pShape = GetFocused();

    if (!pShape)
        return;

    switch (pShape->GetFigure())
    {
        case DWF_Shape3D<M_Real>::IE_SF_Line:
        {
            // get the line to update
            DWF_Line3DR* pLine = static_cast<DWF_Line3DR*>(pShape);

            // get the line direction
            DWF_Vector3DR lineDir = pLine->GetDir();

            DWF_Matrix4x4R matrixRotX;
            DWF_Matrix4x4R matrixRotY;
            DWF_Matrix4x4R matrixRotZ;

            // create the matrices to rotate the line on his arbitrary point
            matrixRotX.Rotate(DWF_MathHelper::DegToRad(offsetX), DWF_Vector3DR(M_Real(1.0), M_Real(0.0), M_Real(0.0)));
            matrixRotY.Rotate(DWF_MathHelper::DegToRad(offsetY), DWF_Vector3DR(M_Real(0.0), M_Real(1.0), M_Real(0.0)));
            matrixRotZ.Rotate(DWF_MathHelper::DegToRad(offsetZ), DWF_Vector3DR(M_Real(0.0), M_Real(0.0), M_Real(1.0)));

            DWF_Matrix4x4R matrixRotXY  = matrixRotX.Multiply(matrixRotY);
            DWF_Matrix4x4R matrixRotXYZ = matrixRotXY.Multiply(matrixRotZ);

            // update the line direction
            pLine->SetDir(matrixRotXYZ.Transform(lineDir));

            Touch();
            return;
        }

        case DWF_Shape3D<M_Real>::IE_SF_Ray:
        {
            // get the ray to update
            DWF_Ray3DR* pRay = static_cast<DWF_Ray3DR*>(pShape);

            // get the ray direction
            DWF_Vector3DR rayDir = pRay->GetDir();

            DWF_Matrix4x4R matrixRotX;
            DWF_Matrix4x4R matrixRotY;
            DWF_Matrix4x4R matrixRotZ;

            // create the matrices to rotate the line on his arbitrary point
            matrixRotX.Rotate(DWF_MathHelper::DegToRad(offsetX), DWF_Vector3DR(M_Real(1.0), M_Real(0.0), M_Real(0.0)));
            matrixRotY.Rotate(DWF_MathHelper::DegToRad(offsetY), DWF_Vector3DR(M_Real(0.0), M_Real(1.0), M_Real(0.0)));
            matrixRotZ.Rotate(DWF_MathHelper::DegToRad(offsetZ), DWF_Vector3DR(M_Real(0.0), M_Real(0.0), M_Real(1.0)));

            DWF_Matrix4x4R matrixRotXY  = matrixRotX.Multiply(matrixRotY);
            DWF_Matrix4x4R matrixRotXYZ = matrixRotXY.Multiply(matrixRotZ);

            // update the ray direction
            pRay->SetDir(matrixRotXYZ.Transform(rayDir));

            Touch();
            return;
        }

        case DWF_Shape3D<M_Real>::IE_SF_Segment:
        {
            // get the line segment to rotate
            DWF_Segment3DR* pSegment = static_cast<DWF_Segment3DR*>(pShape);

            DWF_Matrix4x4R matrixRotX;
            DWF_Matrix4x4R matrixRotY;
            DWF_Matrix4x4R matrixRotZ;

            // create the matrices to rotate the line on his arbitrary point
            matrixRotX.Rotate(DWF_MathHelper::DegToRad(offsetX), DWF_Vector3DR(M_Real(1.0), M_Real(0.0), M_Real(0.0)));
            matrixRotY.Rotate(DWF_MathHelper::DegToRad(offsetY), DWF_Vector3DR(M_Real(0.0), M_Real(1.0), M_Real(0.0)));
            matrixRotZ.Rotate(DWF_MathHelper::DegToRad(offsetZ), DWF_Vector3DR(M_Real(0.0), M_Real(0.0), M_Real(1.0)));

            DWF_Matrix4x4R matrixRotXY  = matrixRotX.Multiply(matrixRotY);
            DWF_Matrix4x4R matrixRotXYZ = matrixRotXY.Multiply(matrixRotZ);

            // update the line end position
            pSegment->m_End = matrixRotXYZ.Transform(pSegment->m_End);

            Touch();
            return;
        }

        case DWF_Shape3D<M_Real>::IE_SF_Plane:
        {
            // get the plane to rotate
            DWF_PlaneR* pPlane = static_cast<DWF_PlaneR*>(pShape);

            DWF_Matrix4x4R matrixRotX;
            DWF_Matrix4x4R matrixRotY;
            DWF_Matrix4x4R matrixRotZ;

            // create the matrices to rotate the line on his arbitrary point
            matrixRotX.Rotate(DWF_MathHelper::DegToRad(offsetX), DWF_Vector3DR(M_Real(1.0), M_Real(0.0), M_Real(0.0)));
            matrixRotY.Rotate(DWF_MathHelper::DegToRad(offsetY), DWF_Vector3DR(M_Real(0.0), M_Real(1.0), M_Real(0.0)));
            matrixRotZ.Rotate(DWF_MathHelper::DegToRad(offsetZ), DWF_Vector3DR(M_Real(0.0), M_Real(0.0), M_Real(1.0)));

            DWF_Matrix4x4R matrixRotXY  = matrixRotX.Multiply(matrixRotY);
            DWF_Matrix4x4R matrixRotXYZ = matrixRotXY.Multiply(matrixRotZ);

            // calculate the new plane direction
            const DWF_Vector3DR dir =
                    matrixRotXYZ.Transform(DWF_Vector3DR(pPlane->m_A, pPlane->m_B, pPlane->m_C));

            pPlane->m_A = dir.m_X;
            pPlane->m_B = dir.m_Y;
            pPlane->m_C = dir.m_Z;

            Touch();
            return;
        }

        case DWF_Shape3D<M_Real>::IE_SF_Polygon:
        {
            // get the polygon to rotate
            DWF_Polygon3DR* pPolygon = static_cast<DWF_Polygon3DR*>(pShape);

            // iterate through the polygon vertices
            for (std::size_t i = 0; i < 3; ++i)
            {
                DWF_Matrix4x4R matrixRotX;
                DWF_Matrix4x4R matrixRotY;
                DWF_Matrix4x4R matrixRotZ;

                // create the matrices to rotate the line on his arbitrary point
                matrixRotX.Rotate(DWF_MathHelper::DegToRad(offsetX), DWF_Vector3DR(M_Real(1.0), M_Real(0.0), M_Real(0.0)));
                matrixRotY.Rotate(DWF_MathHelper::DegToRad(offsetY), DWF_Vector3DR(M_Real(0.0), M_Real(1.0), M_Real(0.0)));
                matrixRotZ.Rotate(DWF_MathHelper::DegToRad(offsetZ), DWF_Vector3DR(M_Real(0.0), M_Real(0.0), M_Real(1.0)));

                DWF_Matrix4x4R matrixRotXY  = matrixRotX.Multiply(matrixRotY);
                DWF_Matrix4x4R matrixRotXYZ = matrixRotXY.Multiply(matrixRotZ);

                // calculate the new vertex position
                const DWF_Vector3DR vertex = matrixRotXYZ.Transform(pPolygon->GetVertex(i));

                // update the vertex in the polygon
                pPolygon->SetVertex(i, vertex);
            }

            Touch();
            return;
        }

        case DWF_Shape3D<M_Real>::IE_SF_Disk:
        {
            // get the disk to rotate
            DWF_DiskR* pDisk = static_cast<DWF_DiskR*>(pShape);

            DWF_Matrix4x4R matrixRotX;
            DWF_Matrix4x4R matrixRotY;
            DWF_Matrix4x4R matrixRotZ;

            // create the matrices to rotate the line on his arbitrary point
            matrixRotX.Rotate(DWF_MathHelper::DegToRad(offsetX), DWF_Vector3DR(M_Real(1.0), M_Real(0.0), M_Real(0.0)));
            matrixRotY.Rotate(DWF_MathHelper::DegToRad(offsetY), DWF_Vector3DR(M_Real(0.0), M_Real(1.0), M_Real(0.0)));
            matrixRotZ.Rotate(DWF_MathHelper::DegToRad(offsetZ), DWF_Vector3DR(M_Real(0.0), M_Real(0.0), M_Real(1.0)));

            DWF_Matrix4x4R matrixRotXY  = matrixRotX.Multiply(matrixRotY);
            DWF_Matrix4x4R matrixRotXYZ = matrixRotXY.Multiply(matrixRotZ);

            // update the disk direction
            pDisk->m_Normal = matrixRotXYZ.Transform(pDisk->m_Normal);

            Touch();
            return;
        }

        case DWF_Shape3D<M_Real>::IE_SF_Sphere:
        case DWF_Shape3D<M_Real>::IE_SF_Box:
        case DWF_Shape3D<M_Real>::IE_SF_Cylinder:
            // these shapes are not allowed to rotate. The rect is included because it's an aligned
            // bounding rect
            ::PlaySound((LPCWSTR)SND_ALIAS_SYSTEMEXCLAMATION, NULL, SND_ALIAS_ID | SND_ASYNC);
            return;
    }
}
//---------------------------------------------------------------------------
void TGeometricDocument3D::Draw(const TRect& rect, TCanvas* pCanvas) const
{
    IGraphicShapes graphicShapes;

    try
    {
        // get the shape count on the document
        const std::size_t count = m_Shapes.size();

        // iterate through shapes to draw
        for (std::size_t i = 0; i < count; ++i)
        {
            // create and populate a new graphic shape
            std::auto_ptr<IGraphicShape> pGraphicShape(new IGraphicShape());
            pGraphicShape->m_pShape       = m_Shapes[i]->m_pShape;
            pGraphicShape->m_VirtualCoord = m_Shapes[i]->m_VirtualCoord;
            pGraphicShape->m_Focused      = (i == m_FocusedIndex);

            const bool isPlane = (m_Shapes[i]->m_pShape->GetFigure() == DWF_Shape3D<M_Real>::IE_SF_Plane);

            // is the shape selected or focused?
            if (m_Shapes[i]->m_Selected)
            {
                // if the shape is selected, fade the color
                FadeColor(m_Shapes[i]);

                // get the reference color, which is the same as current color, but semitransparent
                DWF_Color refColor = m_Shapes[i]->m_Color;
                refColor.SetAlpha(64);

                // blend the final color to use
                pGraphicShape->m_Color = m_Shapes[i]->m_Color.Blend(refColor, m_Shapes[i]->m_FadeValue);
            }
            else
            if (isPlane && pGraphicShape->m_Focused)
                // set a special color for the focused planes or lines
                pGraphicShape->m_Color = DWF_Color(255, 0, 0, 32);
            else
            {
                // otherwise use the fully opaque shape color
                pGraphicShape->m_Color = m_Shapes[i]->m_Color;

                // keep planes semi-transparent even if not focused
                if (isPlane)
                    pGraphicShape->m_Color.SetAlpha(64);
            }

            // set the graphic shape to draw
            graphicShapes.push_back(pGraphicShape.get());
            pGraphicShape.release();
        }

        // sort the graphic shapes to draw the transparents one on the end
        std::sort(graphicShapes.begin(), graphicShapes.end(), OnCompareShapes);

        m_Renderer.BeginScene(GetBackgroundColor(),
                             (DWF_Core::DWF_Renderer::IESceneFlags)(DWF_Core::DWF_Renderer::IE_SF_ClearColor |
                                                                    DWF_Core::DWF_Renderer::IE_SF_ClearDepth));

        // by default alpha blending isn't required
        glEnable(GL_DEPTH_TEST);
        glDisable(GL_BLEND);

        // set the view matrix to use
        m_Renderer.SetViewMatrix(&m_Shader, m_View);

        // draw the background grid
        DrawBackground(DWF_RectR(-1.0f, -1.0f, 1.0f, 1.0f));

        // iterate through all document shapes
        for (std::size_t i = 0; i < count; ++i)
        {
            // make line solid
            glDisable(GL_LINE_STIPPLE);

            // is focused?
            if (graphicShapes[i]->m_Focused)
                // don't fill the polygons, draw their edge instead
                glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            else
                // fill the polygons again
                glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

            // do draw transparent shapes?
            if (graphicShapes[i]->m_Color.GetAlpha() < 255)
            {
                // enable the alpha blending
                glEnable(GL_BLEND);
                glBlendEquation(GL_FUNC_ADD);
                glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            }

            // search for the shape to draw
            switch (graphicShapes[i]->m_pShape->GetFigure())
            {
                case DWF_Shape3D<M_Real>::IE_SF_Line:
                {
                    // get the line to draw
                    const DWF_Line3DR* pLine = static_cast<DWF_Line3DR*>(graphicShapes[i]->m_pShape);

                    // set an arbitrary length for the line (in fact the line is infinite)
                    const int lineLength = 100000;

                    // calculate the ray coordinates for drawing
                    const DWF_Vector3DR linePos = pLine->GetPoint();
                    const DWF_Vector3DR lineDir = pLine->GetDir();
                    const DWF_Vector3DR lineStart(linePos.m_X - (lineLength * lineDir.m_X),
                                                  linePos.m_Y - (lineLength * lineDir.m_Y),
                                                  linePos.m_Z - (lineLength * lineDir.m_Z));
                    const DWF_Vector3DR lineEnd(linePos.m_X + (lineLength * lineDir.m_X),
                                                linePos.m_Y + (lineLength * lineDir.m_Y),
                                                linePos.m_Z + (lineLength * lineDir.m_Z));

                    // select the color to use
                    if (!SelectColor(graphicShapes[i]->m_Color))
                        continue;

                    // is line focused?
                    if (graphicShapes[i]->m_Focused)
                    {
                        // make line dotted (the pattern is set to -  -)
                        glLineStipple(1, 0xF00F);
                        glEnable(GL_LINE_STIPPLE);
                    }

                    // draw the line
                    m_Renderer.DrawLine(lineStart, lineEnd, (DWF_Core::DWF_Shader*)(&m_Shader));

                    continue;
                }

                case DWF_Shape3D<M_Real>::IE_SF_Ray:
                {
                    // get the ray to draw
                    const DWF_Ray3DR* pRay = static_cast<DWF_Ray3DR*>(graphicShapes[i]->m_pShape);

                    // set an arbitrary length for the ray (in fact the ray is infinite)
                    const int rayLength = 100000;

                    // calculate the ray coordinates for drawing
                    const DWF_Vector3DR rayPos = pRay->GetPos();
                    const DWF_Vector3DR rayDir = pRay->GetDir();
                    const DWF_Vector3DR rayEnd(rayPos.m_X + (rayLength * rayDir.m_X),
                                               rayPos.m_Y + (rayLength * rayDir.m_Y),
                                               rayPos.m_Z + (rayLength * rayDir.m_Z));

                    // select the color to use
                    if (!SelectColor(graphicShapes[i]->m_Color))
                        continue;

                    // is ray focused?
                    if (graphicShapes[i]->m_Focused)
                    {
                        // make ray dotted (the pattern is set to -  -)
                        glLineStipple(1, 0xF00F);
                        glEnable(GL_LINE_STIPPLE);
                    }

                    // draw the ray
                    m_Renderer.DrawLine(rayPos, rayEnd, (DWF_Core::DWF_Shader*)(&m_Shader));

                    continue;
                }

                case DWF_Shape3D<M_Real>::IE_SF_Segment:
                {
                    // get the line segment to draw
                    const DWF_Segment3DR* pSegment =
                            static_cast<DWF_Segment3DR*>(graphicShapes[i]->m_pShape);

                    // select the color to use
                    if (!SelectColor(graphicShapes[i]->m_Color))
                        continue;

                    // is line segment focused?
                    if (graphicShapes[i]->m_Focused)
                    {
                        // make line segment dotted (the pattern is set to -  -)
                        glLineStipple(1, 0xF00F);
                        glEnable(GL_LINE_STIPPLE);
                    }

                    // draw the line segment
                    m_Renderer.DrawLine(pSegment->m_Start,
                                        pSegment->m_End,
                                       (DWF_Core::DWF_Shader*)(&m_Shader));

                    continue;
                }

                case DWF_Shape3D<M_Real>::IE_SF_Plane:
                {
                    // plane is always filled
                    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

                    // get the plane to draw
                    const DWF_PlaneR* pPlane = static_cast<DWF_PlaneR*>(graphicShapes[i]->m_pShape);

                    // get the plane model to draw
                    IMeshDictionary::const_iterator it = m_Meshes.find(IE_GO_Plane);

                    if (it == m_Meshes.end())
                        continue;

                    // select the color to use
                    if (!SelectColor(graphicShapes[i]->m_Color))
                        continue;

                    DWF_Core::DWF_ModelTextures textures;

                    // draw the sphere
                    m_Renderer.Draw(it->second,
                                    BuildModelMatrix(graphicShapes[i]->m_VirtualCoord,
                                                     pPlane->m_A,
                                                     pPlane->m_B,
                                                     pPlane->m_C,
                                                     DWF_Vector3DR(1.0f, 1.0f, 1.0f)),
                                    textures,
                                    &m_Shader);

                    continue;
                }

                case DWF_Shape3D<M_Real>::IE_SF_Polygon:
                {
                    // get the polygon to draw
                    const DWF_Polygon3DR* pPolygon = static_cast<DWF_Polygon3DR*>(graphicShapes[i]->m_pShape);

                    DWF_Modeling::DWF_Mesh mesh;

                    // create and populate a vertex buffer for the polygon
                    std::auto_ptr<DWF_Modeling::DWF_VertexBuffer> pVertexBuffer(new DWF_Modeling::DWF_VertexBuffer());
                    pVertexBuffer->m_Info.m_Name     = L"dwf_polygon";
                    pVertexBuffer->m_Info.m_Type     = DWF_Modeling::DWF_VertexInfo::IE_VT_Triangles;
                    pVertexBuffer->m_Info.m_CullMode = DWF_Modeling::DWF_VertexInfo::IE_CM_Disabled;

                    pVertexBuffer->m_Data.reserve(9);

                    // iterate through polygon vertices
                    for (std::size_t j = 0; j < 3; ++j)
                    {
                        // add each polygon vertex in the vertex buffer
                        pVertexBuffer->m_Data.push_back(pPolygon->GetVertex(j).m_X);
                        pVertexBuffer->m_Data.push_back(pPolygon->GetVertex(j).m_Y);
                        pVertexBuffer->m_Data.push_back(pPolygon->GetVertex(j).m_Z);
                    }

                    mesh.push_back(pVertexBuffer.get());

                    // select the color to use
                    if (!SelectColor(graphicShapes[i]->m_Color))
                        continue;

                    DWF_Core::DWF_ModelTextures textures;

                    // draw the sphere
                    m_Renderer.Draw(mesh,
                                    DWF_Matrix4x4R(),
                                    textures,
                                    &m_Shader);

                    continue;
                }

                case DWF_Shape3D<M_Real>::IE_SF_Sphere:
                {
                    // get the geometric sphere
                    const DWF_SphereR* pSphere = static_cast<DWF_SphereR*>(graphicShapes[i]->m_pShape);

                    // get the sphere model to draw
                    IMeshDictionary::const_iterator it = m_Meshes.find(IE_GO_Sphere);

                    if (it == m_Meshes.end())
                        continue;

                    // select the color to use
                    if (!SelectColor(graphicShapes[i]->m_Color))
                        continue;

                    DWF_Core::DWF_ModelTextures textures;

                    // draw the sphere
                    m_Renderer.Draw(it->second,
                                    BuildModelMatrix(pSphere->m_Center,
                                                     0.0f,
                                                     0.0f,
                                                     0.0f,
                                                     DWF_Vector3DR(pSphere->m_Radius,
                                                                   pSphere->m_Radius,
                                                                   pSphere->m_Radius)),
                                    textures,
                                    &m_Shader);

                    continue;
                }

                case DWF_Shape3D<M_Real>::IE_SF_Box:
                {
                    // get the box to draw
                    const DWF_BoxR* pBox = static_cast<DWF_BoxR*>(graphicShapes[i]->m_pShape);

                    // get the plane model to draw
                    IMeshDictionary::const_iterator it = m_Meshes.find(IE_GO_Box);

                    if (it == m_Meshes.end())
                        continue;

                    // select the color to use
                    if (!SelectColor(graphicShapes[i]->m_Color))
                        continue;

                    DWF_Core::DWF_ModelTextures textures;

                    // draw the sphere
                    m_Renderer.Draw(it->second,
                                    BuildModelMatrix(pBox->GetCenter(),
                                                     0.0f,
                                                     0.0f,
                                                     0.0f,
                                                     DWF_Vector3DR((pBox->m_Max.m_X - pBox->m_Min.m_X) * 0.5f,
                                                                   (pBox->m_Max.m_Y - pBox->m_Min.m_Y) * 0.5f,
                                                                   (pBox->m_Max.m_Z - pBox->m_Min.m_Z) * 0.5f)),
                                    textures,
                                    &m_Shader);

                    continue;
                }

                case DWF_Shape3D<M_Real>::IE_SF_Disk:
                {
                    // get the disk to draw
                    const DWF_DiskR* pDisk = static_cast<DWF_DiskR*>(graphicShapes[i]->m_pShape);

                    // get the disk model to draw
                    IMeshDictionary::const_iterator it = m_Meshes.find(IE_GO_Disk);

                    if (it == m_Meshes.end())
                        continue;

                    // select the color to use
                    if (!SelectColor(graphicShapes[i]->m_Color))
                        continue;

                    DWF_Core::DWF_ModelTextures textures;

                    // draw the sphere
                    m_Renderer.Draw(it->second,
                                    BuildModelMatrix(pDisk->m_Center,
                                                     pDisk->m_Normal.m_X,
                                                     pDisk->m_Normal.m_Y,
                                                     pDisk->m_Normal.m_Z,
                                                     DWF_Vector3DR(pDisk->m_Radius,
                                                                   pDisk->m_Radius,
                                                                   pDisk->m_Radius)),
                                    textures,
                                    &m_Shader);

                    continue;
                }

                case DWF_Shape3D<M_Real>::IE_SF_Cylinder:
                {
                    // get the cylinder to draw
                    const DWF_CylinderR* pCylinder = static_cast<DWF_CylinderR*>(graphicShapes[i]->m_pShape);

                    // get the cylinder model to draw
                    IMeshDictionary::const_iterator it = m_Meshes.find(IE_GO_Cylinder);

                    if (it == m_Meshes.end())
                        continue;

                    // select the color to use
                    if (!SelectColor(graphicShapes[i]->m_Color))
                        continue;

                    DWF_Core::DWF_ModelTextures textures;

                    // draw the sphere
                    m_Renderer.Draw(it->second,
                                    BuildModelMatrix(pCylinder->m_Start + ((pCylinder->m_End - pCylinder->m_Start) / 2.0f),
                                                     0.0f,
                                                     0.0f,
                                                     0.0f,
                                                     DWF_Vector3DR(pCylinder->m_Radius,
                                                                  (pCylinder->m_End - pCylinder->m_Start).Length(),
                                                                   pCylinder->m_Radius)),
                                    textures,
                                    &m_Shader);

                    continue;
                }
            }
        }

        // do show the inside simulator point position?
        if (m_InsideSimEnabled)
        {
            // get the sphere model to draw
            IMeshDictionary::const_iterator it = m_Meshes.find(IE_GO_Sphere);

            if (it != m_Meshes.end())
                // select the color to use
                if (SelectColor(DWF_Color(255, 124, 8, 192)))
                {
                    // fill the polygons
                    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

                    // enable the alpha blending
                    glEnable(GL_BLEND);
                    glBlendEquation(GL_FUNC_ADD);
                    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

                    DWF_Core::DWF_ModelTextures textures;

                    // draw the sphere
                    m_Renderer.Draw(it->second,
                                    BuildModelMatrix(m_Point,
                                                     0.0f,
                                                     0.0f,
                                                     0.0f,
                                                     DWF_Vector3DR(0.01f, 0.01f, 0.01f)),
                                    textures,
                                    &m_Shader);
                }
        }
    }
    __finally
    {
        m_Renderer.EndScene();

        DWF_STDHelper::DelAndClear(graphicShapes);
    }
}
//---------------------------------------------------------------------------
bool TGeometricDocument3D::DoReadContent(XMLNode* pNode)
{
    // no root node?
    if (!pNode)
        return false;

    // iterate through document node children
    for (int i = 0; i < pNode->n_children; ++i)
    {
        // get child node
        XMLNode* pChild = pNode->children[i];

        // found it?
        if (!pChild)
            continue;

        // is the node containing the shapes?
        if (std::strcmp(pChild->tag, M_Geometric_Doc_Shapes_Tag) != 0)
            continue;

        // iterate through shapes
        for (int j = 0; j < pChild->n_children; ++j)
        {
            // get shape node
            XMLNode* pShape = pChild->children[j];

            // search for shape to build
            if (std::strcmp(pShape->tag, M_Geometric_Doc_Line_Tag) == 0)
            {
                DWF_Vector3DR point;
                DWF_Vector3DR dir;

                // iterate through shape values
                for (int k = 0; k < pShape->n_children; ++k)
                {
                    // get value node
                    XMLNode* pValue = pShape->children[k];

                    // search for value to read
                    if (std::strcmp(pValue->tag, M_Geometric_Doc_Point_Tag) == 0)
                        point = ReadVectorFromXML(pValue);
                    else
                    if (std::strcmp(pValue->tag, M_Geometric_Doc_Dir_Tag) == 0)
                        dir = ReadVectorFromXML(pValue);
                }

                AddLine(point, dir);
            }
            else
            if (std::strcmp(pShape->tag, M_Geometric_Doc_Ray_Tag) == 0)
            {
                DWF_Vector3DR pos;
                DWF_Vector3DR dir;

                // iterate through shape values
                for (int k = 0; k < pShape->n_children; ++k)
                {
                    // get value node
                    XMLNode* pValue = pShape->children[k];

                    // search for value to read
                    if (std::strcmp(pValue->tag, M_Geometric_Doc_Pos_Tag) == 0)
                        pos = ReadVectorFromXML(pValue);
                    else
                    if (std::strcmp(pValue->tag, M_Geometric_Doc_Dir_Tag) == 0)
                        dir = ReadVectorFromXML(pValue);
                }

                AddRay(pos, dir);
            }
            else
            if (std::strcmp(pShape->tag, M_Geometric_Doc_Segment_Tag) == 0)
            {
                DWF_Vector3DR start;
                DWF_Vector3DR end;

                // iterate through shape values
                for (int k = 0; k < pShape->n_children; ++k)
                {
                    // get value node
                    XMLNode* pValue = pShape->children[k];

                    // search for value to read
                    if (std::strcmp(pValue->tag, M_Geometric_Doc_Start_Tag) == 0)
                        start = ReadVectorFromXML(pValue);
                    else
                    if (std::strcmp(pValue->tag, M_Geometric_Doc_End_Tag) == 0)
                        end = ReadVectorFromXML(pValue);
                }

                AddSegment(start, end);
            }
            else
            if (std::strcmp(pShape->tag, M_Geometric_Doc_Plane_Tag) == 0)
            {
                DWF_Vector3DR point;
                DWF_Vector3DR normal;

                // iterate through shape values
                for (int k = 0; k < pShape->n_children; ++k)
                {
                    // get value node
                    XMLNode* pValue = pShape->children[k];

                    // search for value to read
                    if (std::strcmp(pValue->tag, M_Geometric_Doc_Point_Tag) == 0)
                        point = ReadVectorFromXML(pValue);
                    else
                    if (std::strcmp(pValue->tag, M_Geometric_Doc_Normal_Tag) == 0)
                        normal = ReadVectorFromXML(pValue);
                }

                AddPlane(point, normal);
            }
            else
            if (std::strcmp(pShape->tag, M_Geometric_Doc_Polygon_Tag) == 0)
            {
                DWF_Vector3DR v1;
                DWF_Vector3DR v2;
                DWF_Vector3DR v3;

                // iterate through shape values
                for (int k = 0; k < pShape->n_children; ++k)
                {
                    // get value node
                    XMLNode* pValue = pShape->children[k];

                    // search for value to read
                    if (std::strcmp(pValue->tag, M_Geometric_Doc_V1_Tag) == 0)
                        v1 = ReadVectorFromXML(pValue);
                    else
                    if (std::strcmp(pValue->tag, M_Geometric_Doc_V2_Tag) == 0)
                        v2 = ReadVectorFromXML(pValue);
                    else
                    if (std::strcmp(pValue->tag, M_Geometric_Doc_V3_Tag) == 0)
                        v3 = ReadVectorFromXML(pValue);
                }

                AddPolygon(v1, v2, v3);
            }
            else
            if (std::strcmp(pShape->tag, M_Geometric_Doc_Sphere_Tag) == 0)
            {
                DWF_Vector3DR center;
                float         radius;

                // iterate through shape values
                for (int k = 0; k < pShape->n_children; ++k)
                {
                    // get value node
                    XMLNode* pValue = pShape->children[k];

                    // search for value to read
                    if (std::strcmp(pValue->tag, M_Geometric_Doc_Center_Tag) == 0)
                        center = ReadVectorFromXML(pValue);
                    else
                    if (std::strcmp(pValue->tag, M_Geometric_Doc_Radius_Tag) == 0)
                        radius = ::StrToFloat(pValue->text);
                }

                AddSphere(center, radius);
            }
            else
            if (std::strcmp(pShape->tag, M_Geometric_Doc_Box_Tag) == 0)
            {
                DWF_Vector3DR min;
                DWF_Vector3DR max;

                // iterate through shape values
                for (int k = 0; k < pShape->n_children; ++k)
                {
                    // get value node
                    XMLNode* pValue = pShape->children[k];

                    // search for value to read
                    if (std::strcmp(pValue->tag, M_Geometric_Doc_Min_Tag) == 0)
                        min = ReadVectorFromXML(pValue);
                    else
                    if (std::strcmp(pValue->tag, M_Geometric_Doc_Max_Tag) == 0)
                        max = ReadVectorFromXML(pValue);
                }

                AddBox(min, max);
            }
            else
            if (std::strcmp(pShape->tag, M_Geometric_Doc_Disk_Tag) == 0)
            {
                DWF_Vector3DR center;
                DWF_Vector3DR normal;
                float         radius;

                // iterate through shape values
                for (int k = 0; k < pShape->n_children; ++k)
                {
                    // get value node
                    XMLNode* pValue = pShape->children[k];

                    // search for value to read
                    if (std::strcmp(pValue->tag, M_Geometric_Doc_Center_Tag) == 0)
                        center = ReadVectorFromXML(pValue);
                    else
                    if (std::strcmp(pValue->tag, M_Geometric_Doc_Normal_Tag) == 0)
                        normal = ReadVectorFromXML(pValue);
                    else
                    if (std::strcmp(pValue->tag, M_Geometric_Doc_Radius_Tag) == 0)
                        radius = ::StrToFloat(pValue->text);
                }

                AddDisk(center, normal, radius);
            }
            else
            if (std::strcmp(pShape->tag, M_Geometric_Doc_Cylinder_Tag) == 0)
            {
                DWF_Vector3DR start;
                DWF_Vector3DR end;
                float         radius;

                // iterate through shape values
                for (int k = 0; k < pShape->n_children; ++k)
                {
                    // get value node
                    XMLNode* pValue = pShape->children[k];

                    // search for value to read
                    if (std::strcmp(pValue->tag, M_Geometric_Doc_Start_Tag) == 0)
                        start = ReadVectorFromXML(pValue);
                    else
                    if (std::strcmp(pValue->tag, M_Geometric_Doc_End_Tag) == 0)
                        end = ReadVectorFromXML(pValue);
                    else
                    if (std::strcmp(pValue->tag, M_Geometric_Doc_Radius_Tag) == 0)
                        radius = ::StrToFloat(pValue->text);
                }

                AddCylinder(start, end, radius);
            }
        }
    }

    return true;
}
//---------------------------------------------------------------------------
bool TGeometricDocument3D::DoWriteContent(XMLDoc& doc) const
{
    // create node to contain the document info
    XMLNode* pDocument = XMLNode_alloc();

    // succeeded?
    if (!pDocument)
        return false;

    try
    {
        // set tag name
        if (!XMLNode_set_tag(pDocument, M_Geometric_Doc_Document_Tag))
        {
            XMLNode_free(pDocument);
            return NULL;
        }

        // add tag to document
        if (!XMLDoc_add_node(&doc, pDocument))
        {
            XMLNode_free(pDocument);
            return NULL;
        }

        // add the doc type value
        if (!DWF_XML::DWF_Helper::AddAttribute(pDocument,
                                               M_Geometric_Doc_Type_Tag,
                                               M_Geometric_Doc_3D_Value))
            return false;

        // create node to contain the shapes
        XMLNode* pXMLShapes = XMLNode_alloc();

        // succeeded?
        if (!pXMLShapes)
            return false;

        try
        {
            // set tag name
            if (!XMLNode_set_tag(pXMLShapes, M_Geometric_Doc_Shapes_Tag))
            {
                XMLNode_free(pXMLShapes);
                return NULL;
            }

            // add tag to document
            if (!XMLNode_add_child(pDocument, pXMLShapes))
            {
                XMLNode_free(pXMLShapes);
                return NULL;
            }

            // get the shape count on the document
            const std::size_t count = m_Shapes.size();

            // iterate through all document shapes to write
            for (std::size_t i = 0; i < count; ++i)
            {
                std::string shapeName;

                // get the shape name to write
                switch (m_Shapes[i]->m_pShape->GetFigure())
                {
                    case DWF_Shape3D<M_Real>::IE_SF_Line:     shapeName = M_Geometric_Doc_Line_Tag;     break;
                    case DWF_Shape3D<M_Real>::IE_SF_Ray:      shapeName = M_Geometric_Doc_Ray_Tag;      break;
                    case DWF_Shape3D<M_Real>::IE_SF_Segment:  shapeName = M_Geometric_Doc_Segment_Tag;  break;
                    case DWF_Shape3D<M_Real>::IE_SF_Plane:    shapeName = M_Geometric_Doc_Plane_Tag;    break;
                    case DWF_Shape3D<M_Real>::IE_SF_Polygon:  shapeName = M_Geometric_Doc_Polygon_Tag;  break;
                    case DWF_Shape3D<M_Real>::IE_SF_Sphere:   shapeName = M_Geometric_Doc_Sphere_Tag;   break;
                    case DWF_Shape3D<M_Real>::IE_SF_Box:      shapeName = M_Geometric_Doc_Box_Tag;      break;
                    case DWF_Shape3D<M_Real>::IE_SF_Disk:     shapeName = M_Geometric_Doc_Disk_Tag;     break;
                    case DWF_Shape3D<M_Real>::IE_SF_Cylinder: shapeName = M_Geometric_Doc_Cylinder_Tag; break;
                    default:                                  return false;
                }

                // add a child to contain the shape
                XMLNode* pXMLShape = DWF_XML::DWF_Helper::AddTag(pXMLShapes, shapeName);

                // succeeded?
                if (!pXMLShape)
                    return false;

                // search for the shape to write
                switch (m_Shapes[i]->m_pShape->GetFigure())
                {
                    case DWF_Shape3D<M_Real>::IE_SF_Line:
                    {
                        // get the line to write
                        const DWF_Line3DR* pLine = static_cast<DWF_Line3DR*>(m_Shapes[i]->m_pShape);

                        // write the line point property
                        if (!AddTag(pXMLShape, M_Geometric_Doc_Point_Tag, pLine->GetPoint()))
                            return false;

                        // write the line dir property
                        if (!AddTag(pXMLShape, M_Geometric_Doc_Dir_Tag, pLine->GetDir()))
                            return false;

                        continue;
                    }

                    case DWF_Shape3D<M_Real>::IE_SF_Ray:
                    {
                        // get the ray to write
                        const DWF_Ray3DR* pRay = static_cast<DWF_Ray3DR*>(m_Shapes[i]->m_pShape);

                        // write the ray pos property
                        if (!AddTag(pXMLShape, M_Geometric_Doc_Pos_Tag, pRay->GetPos()))
                            return false;

                        // write the ray dir property
                        if (!AddTag(pXMLShape, M_Geometric_Doc_Dir_Tag, pRay->GetDir()))
                            return false;

                        continue;
                    }

                    case DWF_Shape3D<M_Real>::IE_SF_Segment:
                    {
                        // get the line segment to write
                        const DWF_Segment3DR* pSegment = static_cast<DWF_Segment3DR*>(m_Shapes[i]->m_pShape);

                        // write the segment start property
                        if (!AddTag(pXMLShape, M_Geometric_Doc_Start_Tag, pSegment->m_Start))
                            return false;

                        // write the segment end property
                        if (!AddTag(pXMLShape, M_Geometric_Doc_End_Tag, pSegment->m_End))
                            return false;

                        continue;
                    }

                    case DWF_Shape3D<M_Real>::IE_SF_Plane:
                    {
                        // get the plane to write
                        const DWF_PlaneR* pPlane = static_cast<DWF_PlaneR*>(m_Shapes[i]->m_pShape);

                        // write the plane point property
                        if (!AddTag(pXMLShape, M_Geometric_Doc_Point_Tag, m_Shapes[i]->m_VirtualCoord))
                            return false;

                        // write the plane normal property
                        if (!AddTag(pXMLShape, M_Geometric_Doc_Normal_Tag, DWF_Vector3DR(pPlane->m_A,
                                                                                         pPlane->m_B,
                                                                                         pPlane->m_C)))
                            return false;

                        continue;
                    }

                    case DWF_Shape3D<M_Real>::IE_SF_Polygon:
                    {
                        // get the polygon to write
                        const DWF_Polygon3DR* pPolygon = static_cast<DWF_Polygon3DR*>(m_Shapes[i]->m_pShape);

                        // write the polygon vertex 1 property
                        if (!AddTag(pXMLShape, M_Geometric_Doc_V1_Tag, pPolygon->GetVertex1()))
                            return false;

                        // write the polygon vertex 2 property
                        if (!AddTag(pXMLShape, M_Geometric_Doc_V2_Tag, pPolygon->GetVertex2()))
                            return false;

                        // write the polygon vertex 3 property
                        if (!AddTag(pXMLShape, M_Geometric_Doc_V3_Tag, pPolygon->GetVertex3()))
                            return false;

                        continue;
                    }

                    case DWF_Shape3D<M_Real>::IE_SF_Sphere:
                    {
                        // get the sphere to write
                        const DWF_SphereR* pSphere = static_cast<DWF_SphereR*>(m_Shapes[i]->m_pShape);

                        // write the circle center property
                        if (!AddTag(pXMLShape, M_Geometric_Doc_Center_Tag, pSphere->m_Center))
                            return false;

                        // write the circle radius property
                        if (!DWF_XML::DWF_Helper::AddTag(pXMLShape,
                                                         M_Geometric_Doc_Radius_Tag,
                                                         pSphere->m_Radius))
                            return false;

                        continue;
                    }

                    case DWF_Shape3D<M_Real>::IE_SF_Box:
                    {
                        // get the box to write
                        const DWF_BoxR* pBox = static_cast<DWF_BoxR*>(m_Shapes[i]->m_pShape);

                        // write the box min property
                        if (!AddTag(pXMLShape, M_Geometric_Doc_Min_Tag, pBox->m_Min))
                            return false;

                        // write the box max property
                        if (!AddTag(pXMLShape, M_Geometric_Doc_Max_Tag, pBox->m_Max))
                            return false;

                        continue;
                    }

                    case DWF_Shape3D<M_Real>::IE_SF_Disk:
                    {
                        // get the disk to write
                        const DWF_DiskR* pDisk = static_cast<DWF_DiskR*>(m_Shapes[i]->m_pShape);

                        // write the disk center property
                        if (!AddTag(pXMLShape, M_Geometric_Doc_Center_Tag, pDisk->m_Center))
                            return false;

                        // write the disk normal property
                        if (!AddTag(pXMLShape, M_Geometric_Doc_Normal_Tag, pDisk->m_Normal))
                            return false;

                        // write the disk radius property
                        if (!DWF_XML::DWF_Helper::AddTag(pXMLShape,
                                                         M_Geometric_Doc_Radius_Tag,
                                                         pDisk->m_Radius))
                            return false;

                        continue;
                    }

                    case DWF_Shape3D<M_Real>::IE_SF_Cylinder:
                    {
                        // get the cylinder to write
                        const DWF_CylinderR* pCylinder = static_cast<DWF_CylinderR*>(m_Shapes[i]->m_pShape);

                        // write the cylinder start property
                        if (!AddTag(pXMLShape, M_Geometric_Doc_Start_Tag, pCylinder->m_Start))
                            return false;

                        // write the cylinder end property
                        if (!AddTag(pXMLShape, M_Geometric_Doc_End_Tag, pCylinder->m_End))
                            return false;

                        // write the cylinder radius property
                        if (!DWF_XML::DWF_Helper::AddTag(pXMLShape,
                                                         M_Geometric_Doc_Radius_Tag,
                                                         pCylinder->m_Radius))
                            return false;

                        continue;
                    }
                }
            }
        }
        catch (...)
        {
            XMLNode_free(pXMLShapes);
            throw;
        }
    }
    catch (...)
    {
        XMLNode_free(pDocument);
        throw;
    }

    return true;
}
//---------------------------------------------------------------------------
bool TGeometricDocument3D::Initialize()
{
    if (!m_hWnd)
        return false;

    // start OpenGL
    m_Renderer.EnableOpenGL(m_hWnd);

    // stop GLEW crashing on OSX :-/
    glewExperimental = GL_TRUE;

    // initialize GLEW
    if (glewInit() != GLEW_OK)
        return false;

    // configure depth testing
    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);
    glDepthFunc(GL_LEQUAL);
    glDepthRange(0.0f, 1.0f);

    // load the shader
    if (!LoadShader(TGlobalResources::m_ShaderVertexProgram,
                    TGlobalResources::m_ShaderFragmentProgram))
        return false;

    // generate models
    GeneratePlaneModel();
    GenerateSphereModel();
    GenerateBoxModel();
    GenerateDiskModel();
    GenerateCylinderModel();

    return true;
}
//---------------------------------------------------------------------------
void TGeometricDocument3D::GeneratePlaneModel()
{
    DWF_Modeling::DWF_Mesh mesh;

    // create a surface model. Only the vertices will be used in this model, other values are unused
    std::auto_ptr<DWF_Modeling::DWF_Surface> pSurfaceModel(new DWF_Modeling::DWF_Surface(99999.0f, 99999.0f));
    pSurfaceModel->SetColor(clWhite);
    pSurfaceModel->SetVertexFormat(DWF_Modeling::DWF_VertexInfo::IEFormat(0));
    pSurfaceModel->GetMesh(mesh);

    // disable the culling for this model
    mesh[0]->m_Info.m_CullMode = DWF_Modeling::DWF_VertexInfo::IE_CM_Disabled;

    // add the mesh to the dictionary
    m_Meshes[IE_GO_Plane] = mesh;
}
//---------------------------------------------------------------------------
void TGeometricDocument3D::GenerateSphereModel()
{
    DWF_Modeling::DWF_Mesh mesh;

    // create a sphere model. Only the vertices will be used in this model, other values are unused
    std::auto_ptr<DWF_Modeling::DWF_Sphere> pSphereModel(new DWF_Modeling::DWF_Sphere(1.0f, 25, 25));
    pSphereModel->SetColor(clWhite);
    pSphereModel->SetVertexFormat(DWF_Modeling::DWF_VertexInfo::IEFormat(0));
    pSphereModel->GetMesh(mesh);

    // add the mesh to the dictionary
    m_Meshes[IE_GO_Sphere] = mesh;
}
//---------------------------------------------------------------------------
void TGeometricDocument3D::GenerateBoxModel()
{
    DWF_Modeling::DWF_Mesh mesh;

    // create a box model. Only the vertices will be used in this model, other values are unused
    std::auto_ptr<DWF_Modeling::DWF_Box> pBoxModel(new DWF_Modeling::DWF_Box(1.0f, 1.0f, 1.0f, false));
    pBoxModel->SetColor(clWhite);
    pBoxModel->SetVertexFormat(DWF_Modeling::DWF_VertexInfo::IEFormat(0));
    pBoxModel->GetMesh(mesh);

    // add the mesh to the dictionary
    m_Meshes[IE_GO_Box] = mesh;
}
//---------------------------------------------------------------------------
void TGeometricDocument3D::GenerateDiskModel()
{
    DWF_Modeling::DWF_Mesh mesh;

    // create a disk model. Only the vertices will be used in this model, other values are unused
    std::auto_ptr<DWF_Modeling::DWF_Disk> pDiskModel(new DWF_Modeling::DWF_Disk(0.5f, 25));
    pDiskModel->SetColor(clWhite);
    pDiskModel->SetVertexFormat(DWF_Modeling::DWF_VertexInfo::IEFormat(0));
    pDiskModel->GetMesh(mesh);

    // add the mesh to the dictionary
    m_Meshes[IE_GO_Disk] = mesh;
}
//---------------------------------------------------------------------------
void TGeometricDocument3D::GenerateCylinderModel()
{
    DWF_Modeling::DWF_Mesh mesh;

    // create a cylinder model. Only the vertices will be used in this model, other values are unused
    std::auto_ptr<DWF_Modeling::DWF_Cylinder>
            pCylinderModel(new DWF_Modeling::DWF_Cylinder(0.5f,
                                                          0.25f,
                                                          0.25f,
                                                          25,
                                                          DWF_Modeling::DWF_Cylinder::IE_CC_Both));
    pCylinderModel->SetColor(clWhite);
    pCylinderModel->SetVertexFormat(DWF_Modeling::DWF_VertexInfo::IEFormat(0));
    pCylinderModel->GetMesh(mesh);

    // add the mesh to the dictionary
    m_Meshes[IE_GO_Cylinder] = mesh;
}
//---------------------------------------------------------------------------
DWF_Vector3DR TGeometricDocument3D::ReadVectorFromXML(XMLNode* pNode) const
{
    DWF_Vector3DR vector;

    // iterate through node attributes
    for (int i = 0; i < pNode->n_attributes; ++i)
    {
        // get attribute
        XMLAttribute* pAttribute = &pNode->attributes[i];

        // found it?
        if (!pAttribute)
            continue;

        // found the attribute attribute?
        if (std::strcmp(pAttribute->name, M_Geometric_Doc_X_Tag) == 0)
            vector.m_X = ::StrToFloat(pAttribute->value);
        else
        if (std::strcmp(pAttribute->name, M_Geometric_Doc_Y_Tag) == 0)
            vector.m_Y = ::StrToFloat(pAttribute->value);
        else
        if (std::strcmp(pAttribute->name, M_Geometric_Doc_Z_Tag) == 0)
            vector.m_Z = ::StrToFloat(pAttribute->value);
    }

    return vector;
}
//---------------------------------------------------------------------------
bool TGeometricDocument3D::AddTag(      XMLNode*       pParent,
                                  const std::string&   name,
                                  const DWF_Vector3DR& vector) const
{
    // add a child to contain the line point vector
    XMLNode* pNode = DWF_XML::DWF_Helper::AddTag(pParent, name);

    // succeeded?
    if (!pNode)
        return false;

    // add the vector x value
    if (!DWF_XML::DWF_Helper::AddAttribute(pNode, M_Geometric_Doc_X_Tag, vector.m_X))
        return false;

    // add the vector y value
    if (!DWF_XML::DWF_Helper::AddAttribute(pNode, M_Geometric_Doc_Y_Tag, vector.m_Y))
        return false;

    // add the vector z value
    if (!DWF_XML::DWF_Helper::AddAttribute(pNode, M_Geometric_Doc_Z_Tag, vector.m_Z))
        return false;

    return true;
}
//---------------------------------------------------------------------------
bool TGeometricDocument3D::LoadShader(const std::string& vertex, const std::string& fragment)
{
    if (vertex.empty())
        return false;

    if (fragment.empty())
        return false;

    // load and compile the shader programs
    m_Shader.CreateProgram();
    m_Shader.Attach(vertex,   DWF_Core::DWF_Shader::IE_ST_Vertex);
    m_Shader.Attach(fragment, DWF_Core::DWF_Shader::IE_ST_Fragment);

    // link the shader
    return m_Shader.Link(true);
}
//---------------------------------------------------------------------------
DWF_Matrix4x4R TGeometricDocument3D::GetArcBallMatrix(const IArcBall& arcball)
{
    DWF_Matrix4x4R rotMatX;

    // create a matrix for the rotation on the X axis
    rotMatX.Rotate(arcball.m_AngleX, DWF_Vector3DR(1.0f, 0.0f, 0.0f));

    DWF_Matrix4x4R rotMatY;

    // create a matrix for the rotation on the Y axis
    rotMatY.Rotate(arcball.m_AngleY, DWF_Vector3DR(0.0f, 1.0f, 0.0f));

    // combine the rotation matrices
    const DWF_Matrix4x4R rotMatXY = rotMatY.Multiply(rotMatX);

    DWF_Matrix4x4R transMat;

    // create a matrix for the translation
    transMat.Translate(DWF_Vector3DR(0.0f, 0.0f, -arcball.m_Radius));

    // build and return the final matrix
    return rotMatXY.Multiply(transMat);
}
//---------------------------------------------------------------------------
void TGeometricDocument3D::DrawBackground(const DWF_RectR& rect) const
{
    glDisable(GL_LINE_STIPPLE);
    glDisable(GL_BLEND);

    try
    {
        m_Shader.Use(true);

        // get the color slot from vertex shader
        const GLint colorSlot =
                DWF_Renderer::GetUniform(&m_Shader, DWF_Core::DWF_Shader::IE_SA_Color);

        // found it?
        if (colorSlot == -1)
            return;

        const DWF_Color color = GetGridColor();

        // connect the color to use to the shader
        glUniform4f(colorSlot,
                    color.GetRedF(),
                    color.GetGreenF(),
                    color.GetBlueF(),
                    color.GetAlphaF());
    }
    __finally
    {
        m_Shader.Use(false);
    }

    M_Real yPos = -0.4f;

    // draw the grid limits
    m_Renderer.DrawLine(DWF_Geometry::DWF_Vector3DR(rect.m_Left,  yPos, rect.m_Top),
                        DWF_Geometry::DWF_Vector3DR(rect.m_Right, yPos, rect.m_Top),
                       (DWF_Core::DWF_Shader*)(&m_Shader));
    m_Renderer.DrawLine(DWF_Geometry::DWF_Vector3DR(rect.m_Right, yPos, rect.m_Top),
                        DWF_Geometry::DWF_Vector3DR(rect.m_Right, yPos, rect.m_Bottom),
                       (DWF_Core::DWF_Shader*)(&m_Shader));
    m_Renderer.DrawLine(DWF_Geometry::DWF_Vector3DR(rect.m_Right, yPos, rect.m_Bottom),
                        DWF_Geometry::DWF_Vector3DR(rect.m_Left,  yPos, rect.m_Bottom),
                       (DWF_Core::DWF_Shader*)(&m_Shader));
    m_Renderer.DrawLine(DWF_Geometry::DWF_Vector3DR(rect.m_Left, yPos, rect.m_Bottom),
                        DWF_Geometry::DWF_Vector3DR(rect.m_Left, yPos, rect.m_Top),
                       (DWF_Core::DWF_Shader*)(&m_Shader));

    const M_Real gridOffset = M_Real(GetGridOffset()) / 100.0;

    // draw horizontal lines
    for (M_Real i = 0.0; i < rect.Height(); i += gridOffset)
    {
        const M_Real zPos = rect.m_Bottom - i;

        m_Renderer.DrawLine(DWF_Geometry::DWF_Vector3DR(rect.m_Left,  yPos, zPos),
                            DWF_Geometry::DWF_Vector3DR(rect.m_Right, yPos, zPos),
                           (DWF_Core::DWF_Shader*)(&m_Shader));
    }

    // draw vertical lines
    for (M_Real i = 0.0; i < rect.Width(); i += gridOffset)
    {
        const M_Real xPos = rect.m_Left + i;

        m_Renderer.DrawLine(DWF_Geometry::DWF_Vector3DR(xPos, yPos, rect.m_Top),
                            DWF_Geometry::DWF_Vector3DR(xPos, yPos, rect.m_Bottom),
                           (DWF_Core::DWF_Shader*)(&m_Shader));
    }
}
//---------------------------------------------------------------------------
bool TGeometricDocument3D::SelectColor(const DWF_Color& color) const
{
    try
    {
        m_Shader.Use(true);

        // get the color slot from vertex shader
        const GLint colorSlot =
                DWF_Renderer::GetUniform(&m_Shader, DWF_Core::DWF_Shader::IE_SA_Color);

        // found it?
        if (colorSlot == -1)
            return false;

        // connect the color to use to the shader
        glUniform4f(colorSlot,
                    color.GetRedF(),
                    color.GetGreenF(),
                    color.GetBlueF(),
                    color.GetAlphaF());
    }
    __finally
    {
        m_Shader.Use(false);
    }

    return true;
}
//---------------------------------------------------------------------------
DWF_Matrix4x4R TGeometricDocument3D::BuildModelMatrix(const DWF_Vector3DR& position,
                                                            float          xRotation,
                                                            float          yRotation,
                                                            float          zRotation,
                                                      const DWF_Vector3DR& scaleFactor) const
{
    // calculate the translate matrix
    DWF_Matrix4x4R translateMatrix;
    translateMatrix.Translate(position);

    // calculate the rotate matrix on X axis
    DWF_Matrix4x4R xRotateMatrix;
    xRotateMatrix.Rotate(xRotation, DWF_Vector3DR(1.0f, 0.0f, 0.0f));

    // calculate the rotate matrix on Y axis
    DWF_Matrix4x4R yRotateMatrix;
    yRotateMatrix.Rotate(yRotation, DWF_Vector3DR(0.0f, 1.0f, 0.0f));

    // calculate the rotate matrix on Z axis
    DWF_Matrix4x4R zRotateMatrix;
    zRotateMatrix.Rotate(zRotation, DWF_Vector3DR(0.0f, 0.0f, 1.0f));

    // calculate the scale matrix
    DWF_Matrix4x4R scaleMatrix;
    scaleMatrix.Scale(scaleFactor);

    DWF_Matrix4x4R modelMatrixSRX;
    DWF_Matrix4x4R modelMatrixSRXY;
    DWF_Matrix4x4R modelMatrixSRXYZ;

    // calculate the model matrix to use
    modelMatrixSRX   = scaleMatrix.Multiply(xRotateMatrix);
    modelMatrixSRXY  = modelMatrixSRX.Multiply(yRotateMatrix);
    modelMatrixSRXYZ = modelMatrixSRXY.Multiply(zRotateMatrix);

    return modelMatrixSRXYZ.Multiply(translateMatrix);
}
//---------------------------------------------------------------------------
void TGeometricDocument3D::FadeColor(IShape* pShape) const
{
    // fade color in or out
    pShape->m_FadeValue += pShape->m_FadeOffset;

    // is fade value out of bounds?
    if (pShape->m_FadeValue >= 1.0f)
    {
        pShape->m_FadeValue  =  1.0f;
        pShape->m_FadeOffset = -pShape->m_FadeOffset;
    }
    else
    if (pShape->m_FadeValue <= 0.0f)
    {
        pShape->m_FadeValue  =  0.0f;
        pShape->m_FadeOffset = -pShape->m_FadeOffset;
    }
}
//---------------------------------------------------------------------------
bool TGeometricDocument3D::OnCompareShapes(const IGraphicShape* pLeft, const IGraphicShape* pRight)
{
    return pLeft->m_Color.GetAlpha() > pRight->m_Color.GetAlpha();
}
//---------------------------------------------------------------------------
