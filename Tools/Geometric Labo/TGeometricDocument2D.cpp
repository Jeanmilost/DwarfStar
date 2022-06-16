/****************************************************************************
 * ==> TGeometricDocument2D ------------------------------------------------*
 ****************************************************************************
 * Description : This module provides a geometric 2D shapes document        *
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

#include "TGeometricDocument2D.h"

// std
#include <memory>

// dwarfstar engine
#include "DWF_Common_Helpers.h"
#include "DWF_Geometry_Line.h"
#include "DWF_Geometry_Ray.h"
#include "DWF_Geometry_Segment.h"
#include "DWF_Geometry_Polygon.h"
#include "DWF_Geometry_Circle.h"
#include "DWF_Geometry_Rect.h"
#include "DWF_XML_Helper.h"

// interface
#include "TGeometricDocumentTags.h"

//---------------------------------------------------------------------------
// TGeometricDocument2D::IShape
//---------------------------------------------------------------------------
TGeometricDocument2D::IShape::IShape() :
    m_pShape(NULL),
    m_FadeOffset(0.05f),
    m_FadeValue(0.0f),
    m_Selected(false)
{}
//---------------------------------------------------------------------------
TGeometricDocument2D::IShape::~IShape()
{
    if (m_pShape)
        delete m_pShape;
}
//---------------------------------------------------------------------------
// TGeometricDocument2D
//---------------------------------------------------------------------------
TGeometricDocument2D::TGeometricDocument2D() :
    TGeometricDocument()
{}
//---------------------------------------------------------------------------
TGeometricDocument2D::~TGeometricDocument2D()
{
    DWF_STDHelper::DelAndClear(m_Shapes);
}
//---------------------------------------------------------------------------
void TGeometricDocument2D::AddLine(const DWF_Vector2DR& point, const DWF_Vector2DR& dir)
{
    // create a line with a random color
    std::auto_ptr<IShape> pShape(new IShape());
    pShape->m_pShape = new DWF_Line2DR(point, dir);
    pShape->m_Color  = GetRandomColor();

    // add it to the document
    m_Shapes.push_back(pShape.get());
    pShape.release();

    // focus the newly created object
    m_FocusedIndex = m_Shapes.size() - 1;

    Touch();
}
//---------------------------------------------------------------------------
void TGeometricDocument2D::AddRay(const DWF_Vector2DR& point, const DWF_Vector2DR& dir)
{
    // create a ray with a random color
    std::auto_ptr<IShape> pShape(new IShape());
    pShape->m_pShape = new DWF_Ray2DR(point, dir);
    pShape->m_Color  = GetRandomColor();

    // add it to the document
    m_Shapes.push_back(pShape.get());
    pShape.release();

    // focus the newly created object
    m_FocusedIndex = m_Shapes.size() - 1;

    Touch();
}
//---------------------------------------------------------------------------
void TGeometricDocument2D::AddSegment(const DWF_Vector2DR& start, const DWF_Vector2DR& end)
{
    // create a line segment with a random color
    std::auto_ptr<IShape> pShape(new IShape());
    pShape->m_pShape = new DWF_Segment2DR(start, end);
    pShape->m_Color  = GetRandomColor();

    // add it to the document
    m_Shapes.push_back(pShape.get());
    pShape.release();

    // focus the newly created object
    m_FocusedIndex = m_Shapes.size() - 1;

    Touch();
}
//---------------------------------------------------------------------------
void TGeometricDocument2D::AddPolygon(const DWF_Vector2DR& v1,
                                      const DWF_Vector2DR& v2,
                                      const DWF_Vector2DR& v3)
{
    // create a polygon with a random color
    std::auto_ptr<IShape> pShape(new IShape());
    pShape->m_pShape = new DWF_Polygon2DR(v1, v2, v3);
    pShape->m_Color  = GetRandomColor();

    // add it to the document
    m_Shapes.push_back(pShape.get());
    pShape.release();

    // focus the newly created object
    m_FocusedIndex = m_Shapes.size() - 1;

    Touch();
}
//---------------------------------------------------------------------------
void TGeometricDocument2D::AddCircle(const DWF_Vector2DR& center, M_Real radius)
{
    // create a circle with a random color
    std::auto_ptr<IShape> pShape(new IShape());
    pShape->m_pShape = new DWF_CircleR(center, radius);
    pShape->m_Color  = GetRandomColor();

    // add it to the document
    m_Shapes.push_back(pShape.get());
    pShape.release();

    // focus the newly created object
    m_FocusedIndex = m_Shapes.size() - 1;

    Touch();
}
//---------------------------------------------------------------------------
void TGeometricDocument2D::AddRect(M_Real left, M_Real top, M_Real right, M_Real bottom)
{
    // create a rectangle with a random color
    std::auto_ptr<IShape> pShape(new IShape());
    pShape->m_pShape = new DWF_RectR(left, top, right, bottom);
    pShape->m_Color  = GetRandomColor();

    // add it to the document
    m_Shapes.push_back(pShape.get());
    pShape.release();

    // focus the newly created object
    m_FocusedIndex = m_Shapes.size() - 1;

    Touch();
}
//---------------------------------------------------------------------------
void TGeometricDocument2D::Select(std::size_t index, bool selected) const
{
    if (index >= m_Shapes.size())
        return;

    // select or unselect the shape
    m_Shapes[index]->m_Selected = selected;
}
//---------------------------------------------------------------------------
void TGeometricDocument2D::Reset(std::size_t index) const
{
    if (index >= m_Shapes.size())
        return;

    // reset the shape
    m_Shapes[index]->m_Selected  = false;
    m_Shapes[index]->m_FadeValue = 0.0f;
}
//---------------------------------------------------------------------------
void TGeometricDocument2D::Reset(void* pShape) const
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
void* TGeometricDocument2D::GetShape(std::size_t index) const
{
    if (index >= m_Shapes.size())
        return NULL;

    return m_Shapes[index]->m_pShape;
}
//---------------------------------------------------------------------------
std::size_t TGeometricDocument2D::GetShapeCount() const
{
    return m_Shapes.size();
}
//---------------------------------------------------------------------------
DWF_Shape2D<M_Real>* TGeometricDocument2D::GetFocused() const
{
    if (m_FocusedIndex >= m_Shapes.size())
        return NULL;

    return m_Shapes[m_FocusedIndex]->m_pShape;
}
//---------------------------------------------------------------------------
void TGeometricDocument2D::InflateFocused(M_Real offsetX, M_Real offsetY)
{
    DWF_Shape2D<M_Real>* pShape = GetFocused();

    if (!pShape)
        return;

    switch (pShape->GetFigure())
    {
        case DWF_Shape2D<M_Real>::IE_SF_Line:
        case DWF_Shape2D<M_Real>::IE_SF_Ray:
            // the size of these shapes is not allowed to change
            ::PlaySound((LPCWSTR)SND_ALIAS_SYSTEMEXCLAMATION, NULL, SND_ALIAS_ID | SND_ASYNC);
            return;

        case DWF_Shape2D<M_Real>::IE_SF_Segment:
        {
            // get line segment to update
            DWF_Segment2DR* pSegment = static_cast<DWF_Segment2DR*>(pShape);

            // calculate segment direction
            const DWF_Vector2DR dir = (pSegment->m_End - pSegment->m_Start).Normalize();

            // combine offsets
            const M_Real offset = offsetX ? offsetX : offsetY;

            // update the segment endpoints
            pSegment->m_Start.m_X -= (offset * dir.m_X);
            pSegment->m_Start.m_Y -= (offset * dir.m_Y);
            pSegment->m_End.m_X   += (offset * dir.m_X);
            pSegment->m_End.m_Y   += (offset * dir.m_Y);

            Touch();
            return;
        }

        case DWF_Shape2D<M_Real>::IE_SF_Polygon:
        {
            // get polygon to update
            DWF_Polygon2DR* pPolygon = static_cast<DWF_Polygon2DR*>(pShape);

            // get polygon center
            const DWF_Vector2DR center = pPolygon->GetCenter();

            // iterate through each polygon vertices
            for (std::size_t i = 0; i < 3; ++i)
            {
                // get next vertex and calculate his direction
                const DWF_Vector2DR vertex = pPolygon->GetVertex(i);
                const DWF_Vector2DR dir    = (vertex - center).Normalize();

                // increase the vertex position from center
                pPolygon->SetVertex(i, DWF_Vector2DR(vertex.m_X + (offsetX * dir.m_X),
                                                     vertex.m_Y + (offsetY * dir.m_Y)));
            }

            Touch();
            return;
        }

        case DWF_Shape2D<M_Real>::IE_SF_Circle:
        {
            // update circle size
            DWF_CircleR* pCircle  = static_cast<DWF_CircleR*>(pShape);
            pCircle->m_Radius    += offsetX ? offsetX : offsetY;

            // check if circle radius is out of bounds, correct it if yes
            if (pCircle->m_Radius <= 1.0f)
                pCircle->m_Radius = 1.0f;

            Touch();
            return;
        }

        case DWF_Shape2D<M_Real>::IE_SF_Rect:
        {
            // update rectangle size
            DWF_RectR* pRect  = static_cast<DWF_RectR*>(pShape);
            pRect->Inflate(pRect->Width()  > 1.0f || offsetX > 0.0f ? offsetX : 0.0f,
                           pRect->Height() > 1.0f || offsetY > 0.0f ? offsetY : 0.0f);
            pRect->Normalize();

            Touch();
            return;
        }
    }
}
//---------------------------------------------------------------------------
void TGeometricDocument2D::MoveFocused(M_Real offsetX, M_Real offsetY)
{
    DWF_Shape2D<M_Real>* pShape = GetFocused();

    if (!pShape)
        return;

    switch (pShape->GetFigure())
    {
        case DWF_Shape2D<M_Real>::IE_SF_Line:
        {
            // get the line to update
            DWF_Line2DR* pLine = static_cast<DWF_Line2DR*>(pShape);

            // get the current line position
            DWF_Vector2DR linePos = pLine->GetPoint();

            // calculate the next position
            linePos.m_X += offsetX;
            linePos.m_Y += offsetY;

            // update the line position
            pLine->SetPoint(linePos);

            Touch();
            return;
        }

        case DWF_Shape2D<M_Real>::IE_SF_Ray:
        {
            // get the ray to update
            DWF_Ray2DR* pRay = static_cast<DWF_Ray2DR*>(pShape);

            // get the current ray position
            DWF_Vector2DR rayPos = pRay->GetPos();

            // calculate the next position
            rayPos.m_X += offsetX;
            rayPos.m_Y += offsetY;

            // update the ray position
            pRay->SetPos(rayPos);

            Touch();
            return;
        }

        case DWF_Shape2D<M_Real>::IE_SF_Segment:
        {
            // get the segment to update
            DWF_Segment2DR* pSegment = static_cast<DWF_Segment2DR*>(pShape);

            // update the segment start position
            pSegment->m_Start.m_X += offsetX;
            pSegment->m_Start.m_Y += offsetY;

            // update the segment end position
            pSegment->m_End.m_X += offsetX;
            pSegment->m_End.m_Y += offsetY;

            Touch();
            return;
        }

        case DWF_Shape2D<M_Real>::IE_SF_Polygon:
        {
            // get the polygon to update
            DWF_Polygon2DR* pPolygon = static_cast<DWF_Polygon2DR*>(pShape);

            // update the polygon position
            for (std::size_t i = 0; i < 3; ++i)
                pPolygon->SetVertex(i, DWF_Vector2DR(pPolygon->GetVertex(i).m_X + offsetX,
                                                     pPolygon->GetVertex(i).m_Y + offsetY));

            Touch();
            return;
        }

        case DWF_Shape2D<M_Real>::IE_SF_Circle:
        {
            // update the circle position
            DWF_CircleR* pCircle   = static_cast<DWF_CircleR*>(pShape);
            pCircle->m_Center.m_X += offsetX;
            pCircle->m_Center.m_Y += offsetY;

            Touch();
            return;
        }

        case DWF_Shape2D<M_Real>::IE_SF_Rect:
        {
            // update the rect position
            DWF_RectR* pRect = static_cast<DWF_RectR*>(pShape);
            pRect->m_Left   += offsetX;
            pRect->m_Top    += offsetY;
            pRect->m_Right  += offsetX;
            pRect->m_Bottom += offsetY;

            Touch();
            return;
        }
    }
}
//---------------------------------------------------------------------------
void TGeometricDocument2D::RotateFocused(M_Real offset)
{
    DWF_Shape2D<M_Real>* pShape = GetFocused();

    if (!pShape)
        return;

    switch (pShape->GetFigure())
    {
        case DWF_Shape2D<M_Real>::IE_SF_Line:
        {
            // get the line to update
            DWF_Line2DR* pLine = static_cast<DWF_Line2DR*>(pShape);

            // get the line direction
            DWF_Vector2DR lineDir = pLine->GetDir();

            DWF_Matrix3x3R matrix;

            // create a matrix to rotate the line on his arbitrary point
            matrix.Rotate(DWF_MathHelper::DegToRad(offset), DWF_Vector2DR(M_Real(1.0), M_Real(1.0)));

            // update the line direction
            pLine->SetDir(matrix.Transform(lineDir));

            Touch();
            return;
        }

        case DWF_Shape2D<M_Real>::IE_SF_Ray:
        {
            // get the ray to update
            DWF_Ray2DR* pRay = static_cast<DWF_Ray2DR*>(pShape);

            // get the ray direction
            DWF_Vector2DR rayDir = pRay->GetDir();

            DWF_Matrix3x3R matrix;

            // create a matrix to rotate the ray around his position
            matrix.Rotate(DWF_MathHelper::DegToRad(offset), DWF_Vector2DR(M_Real(1.0), M_Real(1.0)));

            // update the ray direction
            pRay->SetDir(matrix.Transform(rayDir));

            Touch();
            return;
        }

        case DWF_Shape2D<M_Real>::IE_SF_Segment:
        {
            // get the line segment to rotate
            DWF_Segment2DR* pSegment = static_cast<DWF_Segment2DR*>(pShape);

            DWF_Matrix3x3R matrix;

            // create a matrix to rotate the line segment around his start position
            matrix.RotateCenter(DWF_MathHelper::DegToRad(offset), pSegment->m_Start);

            // update the line end position
            pSegment->m_End = matrix.Transform(pSegment->m_End);

            Touch();
            return;
        }

        case DWF_Shape2D<M_Real>::IE_SF_Polygon:
        {
            // get the polygon to rotate
            DWF_Polygon2DR* pPolygon = static_cast<DWF_Polygon2DR*>(pShape);

            // get his center
            const DWF_Vector2DR center = pPolygon->GetCenter();

            // iterate through the polygon vertices
            for (std::size_t i = 0; i < 3; ++i)
            {
                DWF_Matrix3x3R matrix;

                // create a matrix to rotate the polygon on his current location
                matrix.RotateCenter(DWF_MathHelper::DegToRad(offset), center);

                // calculate the new vertex position
                const DWF_Vector2DR vertex = matrix.Transform(pPolygon->GetVertex(i));

                // update the vertex in the polygon
                pPolygon->SetVertex(i, vertex);
            }

            Touch();
            return;
        }

        case DWF_Shape2D<M_Real>::IE_SF_Circle:
        case DWF_Shape2D<M_Real>::IE_SF_Rect:
            // these shapes are not allowed to rotate. The rect is included because it's an aligned
            // bounding rect
            ::PlaySound((LPCWSTR)SND_ALIAS_SYSTEMEXCLAMATION, NULL, SND_ALIAS_ID | SND_ASYNC);
            return;
    }
}
//---------------------------------------------------------------------------
void TGeometricDocument2D::Draw(const TRect& rect, TCanvas* pCanvas) const
{
    DrawBackground(rect, pCanvas->Handle);

    // get the shape count on the document
    const std::size_t count = m_Shapes.size();

    // iterate through all document shapes
    for (std::size_t i = 0; i < count; ++i)
    {
        // if the shape is selected, fade the color
        if (m_Shapes[i]->m_Selected)
            FadeColor(m_Shapes[i]);

        // search for the shape to draw
        switch (m_Shapes[i]->m_pShape->GetFigure())
        {
            case DWF_Shape2D<M_Real>::IE_SF_Line:
            {
                // get the line to draw
                const DWF_Line2DR* pLine = static_cast<DWF_Line2DR*>(m_Shapes[i]->m_pShape);

                // set an arbitrary length for the line (in fact the line is infinite)
                const int lineLength = 100000;

                // calculate the ray coordinates for drawing
                const DWF_Vector2DR linePos = pLine->GetPoint();
                const DWF_Vector2DR lineDir = pLine->GetDir();
                const DWF_Vector2DR lineStart(linePos.m_X - (lineLength * lineDir.m_X),
                                              linePos.m_Y - (lineLength * lineDir.m_Y));
                const DWF_Vector2DR lineEnd(linePos.m_X + (lineLength * lineDir.m_X),
                                            linePos.m_Y + (lineLength * lineDir.m_Y));

                HPEN hPen = NULL;

                try
                {
                    // get the line color
                    const TColor color =
                            m_Shapes[i]->m_Color.Blend(clWhite,
                                                       m_Shapes[i]->m_FadeValue).GetVCLColor();

                    // create a GDI pen
                    hPen = ::CreatePen(PS_SOLID, 1, Graphics::ColorToRGB(color));

                    if (!hPen)
                        continue;

                    // apply the GDI pen. Do that, because otherwise the VCL canvas may fail to
                    // configure the pen correctly
                    ::SelectObject(pCanvas->Handle, hPen);

                    // is the line focused?
                    if (i == m_FocusedIndex)
                    {
                        // configure the pen to use to draw the focus highlight
                        pCanvas->Pen->Style = psSolid;
                        pCanvas->Pen->Color = clHighlight;
                        pCanvas->Pen->Width = 2;

                        // draw the focus highlight above the line
                        pCanvas->MoveTo(lineStart.m_X, lineStart.m_Y);
                        pCanvas->LineTo(lineEnd.m_X,   lineEnd.m_Y);
                    }

                    // configure the pen to use
                    pCanvas->Pen->Style = psSolid;
                    pCanvas->Pen->Color = color;
                    pCanvas->Pen->Width = 1;

                    // draw the line segment
                    pCanvas->MoveTo(lineStart.m_X, lineStart.m_Y);
                    pCanvas->LineTo(lineEnd.m_X,   lineEnd.m_Y);

                    // draw the line arbitrary point
                    DrawPoint(linePos,
                              6,
                              i == m_FocusedIndex ? 2 : 0,
                              color,
                              clHighlight,
                              pCanvas);
                }
                __finally
                {
                    if (hPen)
                        ::DeleteObject(hPen);
                }

                continue;
            }

            case DWF_Shape2D<M_Real>::IE_SF_Ray:
            {
                // get the ray to draw
                const DWF_Ray2DR* pRay = static_cast<DWF_Ray2DR*>(m_Shapes[i]->m_pShape);

                // set an arbitrary length for the ray (in fact the ray is infinite)
                const int rayLength = 100000;

                // calculate the ray coordinates for drawing
                const DWF_Vector2DR rayPos = pRay->GetPos();
                const DWF_Vector2DR rayDir = pRay->GetDir();
                const DWF_Vector2DR rayEnd(rayPos.m_X + (rayLength * rayDir.m_X),
                                           rayPos.m_Y + (rayLength * rayDir.m_Y));

                HPEN hPen = NULL;

                try
                {
                    // get the line color
                    const TColor color =
                            m_Shapes[i]->m_Color.Blend(clWhite,
                                                       m_Shapes[i]->m_FadeValue).GetVCLColor();

                    // create a GDI pen
                    hPen = ::CreatePen(PS_SOLID, 1, Graphics::ColorToRGB(color));

                    if (!hPen)
                        continue;

                    // apply the GDI pen. Do that, because otherwise the VCL canvas may fail to
                    // configure the pen correctly
                    ::SelectObject(pCanvas->Handle, hPen);

                    // is the ray focused?
                    if (i == m_FocusedIndex)
                    {
                        // configure the pen to use to draw the focus highlight
                        pCanvas->Pen->Style = psSolid;
                        pCanvas->Pen->Color = clHighlight;
                        pCanvas->Pen->Width = 2;

                        // draw the focus highlight above the ray
                        pCanvas->MoveTo(rayPos.m_X, rayPos.m_Y);
                        pCanvas->LineTo(rayEnd.m_X, rayEnd.m_Y);
                    }

                    // configure the pen to use
                    pCanvas->Pen->Style = psSolid;
                    pCanvas->Pen->Color = color;
                    pCanvas->Pen->Width = 1;

                    // draw the line segment
                    pCanvas->MoveTo(rayPos.m_X, rayPos.m_Y);
                    pCanvas->LineTo(rayEnd.m_X, rayEnd.m_Y);

                    // draw the ray position
                    DrawPoint(rayPos,
                              6,
                              i == m_FocusedIndex ? 2 : 0,
                              color,
                              clHighlight,
                              pCanvas);
                }
                __finally
                {
                    if (hPen)
                        ::DeleteObject(hPen);
                }

                continue;
            }

            case DWF_Shape2D<M_Real>::IE_SF_Segment:
            {
                // get the line segment to draw
                const DWF_Segment2DR* pSegment = static_cast<DWF_Segment2DR*>(m_Shapes[i]->m_pShape);

                HPEN hPen = NULL;

                try
                {
                    // get the line color
                    const TColor color =
                            m_Shapes[i]->m_Color.Blend(clWhite,
                                                       m_Shapes[i]->m_FadeValue).GetVCLColor();

                    // create a GDI pen
                    hPen = ::CreatePen(PS_SOLID, 1, Graphics::ColorToRGB(color));

                    if (!hPen)
                        continue;

                    // apply the GDI pen. Do that, because otherwise the VCL canvas may fail to
                    // configure the pen correctly
                    ::SelectObject(pCanvas->Handle, hPen);

                    // is the line segment focused?
                    if (i == m_FocusedIndex)
                    {
                        // configure the pen to use to draw the focus highlight
                        pCanvas->Pen->Style = psSolid;
                        pCanvas->Pen->Color = clHighlight;
                        pCanvas->Pen->Width = 2;

                        // draw the focus highlight above the line
                        pCanvas->MoveTo(pSegment->m_Start.m_X, pSegment->m_Start.m_Y);
                        pCanvas->LineTo(pSegment->m_End.m_X,   pSegment->m_End.m_Y);
                    }

                    // configure the pen to use
                    pCanvas->Pen->Style = psSolid;
                    pCanvas->Pen->Color = color;
                    pCanvas->Pen->Width = 1;

                    // draw the line segment
                    pCanvas->MoveTo(pSegment->m_Start.m_X, pSegment->m_Start.m_Y);
                    pCanvas->LineTo(pSegment->m_End.m_X,   pSegment->m_End.m_Y);

                    // draw the segment start position
                    DrawPoint(pSegment->m_Start,
                              6,
                              i == m_FocusedIndex ? 2 : 0,
                              color,
                              clHighlight,
                              pCanvas);

                    // draw the segment end position
                    DrawPoint(pSegment->m_End,
                              6,
                              i == m_FocusedIndex ? 2 : 0,
                              color,
                              clHighlight,
                              pCanvas);
                }
                __finally
                {
                    if (hPen)
                        ::DeleteObject(hPen);
                }

                continue;
            }

            case DWF_Shape2D<M_Real>::IE_SF_Polygon:
            {
                // get the polygon to draw
                const DWF_Polygon2DR* pPolygon = static_cast<DWF_Polygon2DR*>(m_Shapes[i]->m_pShape);

                // configure the brush to use
                pCanvas->Brush->Style = bsSolid;
                pCanvas->Brush->Color = m_Shapes[i]->m_Color.Blend(clWhite,
                                                                   m_Shapes[i]->m_FadeValue).GetVCLColor();

                // configure the pen to use
                pCanvas->Pen->Style = psSolid;
                pCanvas->Pen->Color = m_Shapes[i]->m_Color.GetVCLColor();
                pCanvas->Pen->Width = 1;

                // create vertice list and reserve memory to contain 3 vertices
                std::vector<TPoint> vertices;
                vertices.reserve(3);

                // iterate through polygon vertices
                for (std::size_t j = 0; j < 3; ++j)
                    // convert vertice to GDI point
                    vertices.push_back(TPoint(pPolygon->GetVertex(j).m_X, pPolygon->GetVertex(j).m_Y));

                // draw the polygon
                pCanvas->Polygon(&vertices[0], vertices.size() - 1);

                // is the polygon focused?
                if (i == m_FocusedIndex)
                {
                    // configure the brush to use to draw the focus highlight
                    pCanvas->Brush->Style = bsClear;

                    // configure the pen to use to draw the focus highlight
                    pCanvas->Pen->Style = psSolid;
                    pCanvas->Pen->Color = clHighlight;
                    pCanvas->Pen->Width = 2;

                    // draw the selection around the polygon
                    pCanvas->Polygon(&vertices[0], vertices.size() - 1);
                }

                continue;
            }

            case DWF_Shape2D<M_Real>::IE_SF_Circle:
            {
                // get the circle to draw
                const DWF_CircleR* pCircle = static_cast<DWF_CircleR*>(m_Shapes[i]->m_pShape);

                // configure the brush to use
                pCanvas->Brush->Style = bsSolid;
                pCanvas->Brush->Color = m_Shapes[i]->m_Color.Blend(clWhite,
                                                                   m_Shapes[i]->m_FadeValue).GetVCLColor();

                // configure the pen to use
                pCanvas->Pen->Style = psSolid;
                pCanvas->Pen->Color = m_Shapes[i]->m_Color.GetVCLColor();
                pCanvas->Pen->Width = 1;

                // draw the circle
                pCanvas->Ellipse(pCircle->m_Center.m_X - pCircle->m_Radius,
                                 pCircle->m_Center.m_Y - pCircle->m_Radius,
                                 pCircle->m_Center.m_X + pCircle->m_Radius,
                                 pCircle->m_Center.m_Y + pCircle->m_Radius);

                // is the circle focused?
                if (i == m_FocusedIndex)
                {
                    // configure the brush to use to draw the focus highlight
                    pCanvas->Brush->Style = bsClear;

                    // configure the pen to use to draw the focus highlight
                    pCanvas->Pen->Style = psSolid;
                    pCanvas->Pen->Color = clHighlight;
                    pCanvas->Pen->Width = 2;

                    // draw the selection around the circle
                    pCanvas->Ellipse(pCircle->m_Center.m_X - pCircle->m_Radius,
                                     pCircle->m_Center.m_Y - pCircle->m_Radius,
                                     pCircle->m_Center.m_X + pCircle->m_Radius,
                                     pCircle->m_Center.m_Y + pCircle->m_Radius);
                }

                continue;
            }

            case DWF_Shape2D<M_Real>::IE_SF_Rect:
            {
                // get the rectangle to draw
                const DWF_RectR* pRect = static_cast<DWF_RectR*>(m_Shapes[i]->m_pShape);

                // configure the brush to use
                pCanvas->Brush->Style = bsSolid;
                pCanvas->Brush->Color = m_Shapes[i]->m_Color.Blend(clWhite,
                                                                   m_Shapes[i]->m_FadeValue).GetVCLColor();

                // draw the rectangle
                pCanvas->FillRect(TRect(pRect->m_Left,
                                        pRect->m_Top,
                                        pRect->m_Right,
                                        pRect->m_Bottom));

                // is the rectangle focused?
                if (i == m_FocusedIndex)
                {
                    // configure the brush to use to draw the focus highlight
                    pCanvas->Brush->Style = bsSolid;
                    pCanvas->Brush->Color = clHighlight;

                    // calculate the pen width that will surround the rect
                    const std::size_t penWidth = std::min(2.0f, std::min(pRect->Width(), pRect->Height()));

                    // draw the focus highlight around the rectangle
                    for (std::size_t j = 0; j < penWidth; ++j)
                        pCanvas->FrameRect(TRect(pRect->m_Left   + j,
                                                 pRect->m_Top    + j,
                                                 pRect->m_Right  - j,
                                                 pRect->m_Bottom - j));
                }

                continue;
            }
        }
    }
}
//---------------------------------------------------------------------------
bool TGeometricDocument2D::DoReadContent(XMLNode* pNode)
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
                DWF_Vector2DR point;
                DWF_Vector2DR dir;

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
                DWF_Vector2DR pos;
                DWF_Vector2DR dir;

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
                DWF_Vector2DR start;
                DWF_Vector2DR end;

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
            if (std::strcmp(pShape->tag, M_Geometric_Doc_Polygon_Tag) == 0)
            {
                DWF_Vector2DR v1;
                DWF_Vector2DR v2;
                DWF_Vector2DR v3;

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
            if (std::strcmp(pShape->tag, M_Geometric_Doc_Circle_Tag) == 0)
            {
                DWF_Vector2DR center;
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

                AddCircle(center, radius);
            }
            else
            if (std::strcmp(pShape->tag, M_Geometric_Doc_Rect_Tag) == 0)
            {
                float left;
                float top;
                float right;
                float bottom;

                // iterate through shape values
                for (int k = 0; k < pShape->n_children; ++k)
                {
                    // get value node
                    XMLNode* pValue = pShape->children[k];

                    // search for value to read
                    if (std::strcmp(pValue->tag, M_Geometric_Doc_Left_Tag) == 0)
                        left = StrToFloat(pValue->text);
                    else
                    if (std::strcmp(pValue->tag, M_Geometric_Doc_Top_Tag) == 0)
                        top = StrToFloat(pValue->text);
                    else
                    if (std::strcmp(pValue->tag, M_Geometric_Doc_Right_Tag) == 0)
                        right = StrToFloat(pValue->text);
                    else
                    if (std::strcmp(pValue->tag, M_Geometric_Doc_Bottom_Tag) == 0)
                        bottom = StrToFloat(pValue->text);
                }

                AddRect(left, top, right, bottom);
            }
        }
    }

    return true;
}
//---------------------------------------------------------------------------
bool TGeometricDocument2D::DoWriteContent(XMLDoc& doc) const
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
                                               M_Geometric_Doc_2D_Value))
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
                    case DWF_Shape2D<M_Real>::IE_SF_Line:    shapeName = M_Geometric_Doc_Line_Tag;    break;
                    case DWF_Shape2D<M_Real>::IE_SF_Ray:     shapeName = M_Geometric_Doc_Ray_Tag;     break;
                    case DWF_Shape2D<M_Real>::IE_SF_Segment: shapeName = M_Geometric_Doc_Segment_Tag; break;
                    case DWF_Shape2D<M_Real>::IE_SF_Polygon: shapeName = M_Geometric_Doc_Polygon_Tag; break;
                    case DWF_Shape2D<M_Real>::IE_SF_Circle:  shapeName = M_Geometric_Doc_Circle_Tag;  break;
                    case DWF_Shape2D<M_Real>::IE_SF_Rect:    shapeName = M_Geometric_Doc_Rect_Tag;    break;
                    default:                                 return false;
                }

                // add a child to contain the shape
                XMLNode* pXMLShape = DWF_XML::DWF_Helper::AddTag(pXMLShapes, shapeName);

                // succeeded?
                if (!pXMLShape)
                    return false;

                // search for the shape to write
                switch (m_Shapes[i]->m_pShape->GetFigure())
                {
                    case DWF_Shape2D<M_Real>::IE_SF_Line:
                    {
                        // get the line to write
                        const DWF_Line2DR* pLine = static_cast<DWF_Line2DR*>(m_Shapes[i]->m_pShape);

                        // write the line point property
                        if (!AddTag(pXMLShape, M_Geometric_Doc_Point_Tag, pLine->GetPoint()))
                            return false;

                        // write the line dir property
                        if (!AddTag(pXMLShape, M_Geometric_Doc_Dir_Tag, pLine->GetDir()))
                            return false;

                        continue;
                    }

                    case DWF_Shape2D<M_Real>::IE_SF_Ray:
                    {
                        // get the ray to write
                        const DWF_Ray2DR* pRay = static_cast<DWF_Ray2DR*>(m_Shapes[i]->m_pShape);

                        // write the ray pos property
                        if (!AddTag(pXMLShape, M_Geometric_Doc_Pos_Tag, pRay->GetPos()))
                            return false;

                        // write the ray dir property
                        if (!AddTag(pXMLShape, M_Geometric_Doc_Dir_Tag, pRay->GetDir()))
                            return false;

                        continue;
                    }

                    case DWF_Shape2D<M_Real>::IE_SF_Segment:
                    {
                        // get the line segment to write
                        const DWF_Segment2DR* pSegment = static_cast<DWF_Segment2DR*>(m_Shapes[i]->m_pShape);

                        // write the segment start property
                        if (!AddTag(pXMLShape, M_Geometric_Doc_Start_Tag, pSegment->m_Start))
                            return false;

                        // write the segment end property
                        if (!AddTag(pXMLShape, M_Geometric_Doc_End_Tag, pSegment->m_End))
                            return false;

                        continue;
                    }

                    case DWF_Shape2D<M_Real>::IE_SF_Polygon:
                    {
                        // get the polygon to write
                        const DWF_Polygon2DR* pPolygon = static_cast<DWF_Polygon2DR*>(m_Shapes[i]->m_pShape);

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

                    case DWF_Shape2D<M_Real>::IE_SF_Circle:
                    {
                        // get the circle to write
                        const DWF_CircleR* pCircle = static_cast<DWF_CircleR*>(m_Shapes[i]->m_pShape);

                        // write the circle center property
                        if (!AddTag(pXMLShape, M_Geometric_Doc_Center_Tag, pCircle->m_Center))
                            return false;

                        // write the circle radius property
                        if (!DWF_XML::DWF_Helper::AddTag(pXMLShape,
                                                         M_Geometric_Doc_Radius_Tag,
                                                         pCircle->m_Radius))
                            return false;

                        continue;
                    }

                    case DWF_Shape2D<M_Real>::IE_SF_Rect:
                    {
                        // get the rectangle to write
                        const DWF_RectR* pRect = static_cast<DWF_RectR*>(m_Shapes[i]->m_pShape);

                        // write the rect left property
                        if (!DWF_XML::DWF_Helper::AddTag(pXMLShape,
                                                         M_Geometric_Doc_Left_Tag,
                                                         pRect->m_Left))
                            return false;

                        // write the rect top property
                        if (!DWF_XML::DWF_Helper::AddTag(pXMLShape,
                                                         M_Geometric_Doc_Top_Tag,
                                                         pRect->m_Top))
                            return false;

                        // write the rect right property
                        if (!DWF_XML::DWF_Helper::AddTag(pXMLShape,
                                                         M_Geometric_Doc_Right_Tag,
                                                         pRect->m_Right))
                            return false;

                        // write the rect bottom property
                        if (!DWF_XML::DWF_Helper::AddTag(pXMLShape,
                                                         M_Geometric_Doc_Bottom_Tag,
                                                         pRect->m_Bottom))
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
DWF_Vector2DR TGeometricDocument2D::ReadVectorFromXML(XMLNode* pNode) const
{
    DWF_Vector2DR vector;

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
    }

    return vector;
}
//---------------------------------------------------------------------------
bool TGeometricDocument2D::AddTag(      XMLNode*       pParent,
                                  const std::string&   name,
                                  const DWF_Vector2DR& vector) const
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

    return true;
}
//---------------------------------------------------------------------------
void TGeometricDocument2D::DrawBackground(const TRect& rect, HDC hDC) const
{
    if (!hDC)
        return;

    HBRUSH hBrush = NULL;
    HPEN   hPen   = NULL;

    try
    {
        // create the brush and pen to use
        hBrush = ::CreateSolidBrush(Graphics::ColorToRGB(GetBackgroundColor().GetVCLColor()));
        hPen   = ::CreatePen(PS_DOT, 1, Graphics::ColorToRGB(GetGridColor().GetVCLColor()));

        if (!hBrush || !hPen)
            return;

        // select the brush and pen to use
        ::SelectObject(hDC, hBrush);
        ::SelectObject(hDC, hPen);

        ::SetBkMode(hDC, OPAQUE);

        // draw document background
        ::FillRect(hDC, &rect, hBrush);

        const std::size_t width  = rect.Width();
        const std::size_t height = rect.Height();

        ::SetBkMode(hDC, TRANSPARENT);

        const std::size_t gridOffset = GetGridOffset();

        // draw horizontal lines
        for (std::size_t i = 0; i < height; i += gridOffset)
        {
            ::MoveToEx(hDC, rect.Left,  i, NULL);
            ::LineTo  (hDC, rect.Right, i);
        }

        // draw vertical lines
        for (std::size_t i = 0; i < width; i += gridOffset)
        {
            ::MoveToEx(hDC, i, rect.Top, NULL);
            ::LineTo  (hDC, i, rect.Bottom);
        }
    }
    __finally
    {
        if (hPen)
            ::DeleteObject(hPen);

        if (hBrush)
            ::DeleteObject(hBrush);
    }
}
//---------------------------------------------------------------------------
void TGeometricDocument2D::DrawPoint(const DWF_Vector2DR& point,
                                           int            fillSize,
                                           int            strokeSize,
                                           TColor         fillColor,
                                           TColor         strokeColor,
                                           TCanvas*       pCanvas) const
{
    // configure the brush to use
    pCanvas->Brush->Style = bsSolid;
    pCanvas->Brush->Color = fillColor;

    // calculate the half fill size
    const int halfFillSize = (fillSize >> 1);

    // draw the rectangle
    pCanvas->FillRect(TRect(point.m_X - halfFillSize,
                            point.m_Y - halfFillSize,
                            point.m_X + halfFillSize,
                            point.m_Y + halfFillSize));

    // do outline the point?
    if (strokeSize)
    {
        // configure the brush to use to draw the selection
        pCanvas->Brush->Style = bsSolid;
        pCanvas->Brush->Color = strokeColor;

        // outline the point
        for (std::size_t j = 0; j < std::size_t(strokeSize); ++j)
            pCanvas->FrameRect(TRect(point.m_X - halfFillSize - (j + 1),
                                     point.m_Y - halfFillSize - (j + 1),
                                     point.m_X + halfFillSize + (j + 1),
                                     point.m_Y + halfFillSize + (j + 1)));
    }
}
//---------------------------------------------------------------------------
void TGeometricDocument2D::FadeColor(IShape* pShape) const
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
