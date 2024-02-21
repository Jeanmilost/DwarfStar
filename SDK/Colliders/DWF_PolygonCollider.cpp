/****************************************************************************
 * ==> DWF_PolygonCollider -------------------------------------------------*
 ****************************************************************************
 * Description : Polygon collider                                           *
 * Developer   : Jean-Milost Reymond                                        *
 ****************************************************************************
 * MIT License - DwarfStar Game Engine                                      *
 *                                                                          *
 * Permission is hereby granted, free of charge, to any person obtaining a  *
 * copy of this software and associated documentation files (the            *
 * "Software"), to deal in the Software without restriction, including      *
 * without limitation the rights to use, copy, modify, merge, publish,      *
 * distribute, sub-license, and/or sell copies of the Software, and to      *
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

#include "DWF_PolygonCollider.h"

using namespace DWF_Collider;

//---------------------------------------------------------------------------
// Polygon_Collider
//---------------------------------------------------------------------------
Polygon_Collider::Polygon_Collider() :
    Collider()
{}
//---------------------------------------------------------------------------
Polygon_Collider::Polygon_Collider(const DWF_Math::Vector3F& v1,
                                   const DWF_Math::Vector3F& v2,
                                   const DWF_Math::Vector3F& v3) :
    Collider()
{
    // set the polygon. NOTE use the fully qualified name to avoid to use an inherited function)
    Polygon_Collider::SetPolygon(v1, v2, v3);
}
//---------------------------------------------------------------------------
Polygon_Collider::~Polygon_Collider()
{}
//---------------------------------------------------------------------------
DWF_Geometry::Polygon Polygon_Collider::GetPolygon() const
{
    return m_Polygon;
}
//---------------------------------------------------------------------------
void Polygon_Collider::SetPolygon(const DWF_Math::Vector3F& v1,
                                  const DWF_Math::Vector3F& v2,
                                  const DWF_Math::Vector3F& v3)
{
    // set the polygon vertices
    m_Polygon.m_Vertex[0] = v1;
    m_Polygon.m_Vertex[1] = v2;
    m_Polygon.m_Vertex[2] = v3;

    // cache the polygon normal
    m_Normal = m_Polygon.GetNormal();
}
//---------------------------------------------------------------------------
DWF_Math::Vector3F Polygon_Collider::Support(const DWF_Math::Vector3F& dir) const
{
    float              dot0          = m_Polygon.m_Vertex[0].Dot(dir);
    float              dot1          = m_Polygon.m_Vertex[1].Dot(dir);
    float              dot2          = m_Polygon.m_Vertex[2].Dot(dir);
    DWF_Math::Vector3F furthestPoint = m_Polygon.m_Vertex[0];

    // find which polygon vertex is furthest along dir
    if (dot1 > dot0)
    {
        furthestPoint = m_Polygon.m_Vertex[1];

        if (dot2 > dot1)
            furthestPoint = m_Polygon.m_Vertex[2];
    }
    else
    if (dot2 > dot0)
        furthestPoint = m_Polygon.m_Vertex[2];

    // fake some depth behind polygon, so volume should be considered
    if (dir.Dot(m_Normal) < 0)
        furthestPoint -= m_Normal;

    return furthestPoint;
}
//---------------------------------------------------------------------------
