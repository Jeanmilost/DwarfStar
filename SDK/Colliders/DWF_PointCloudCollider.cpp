/****************************************************************************
 * ==> DWF_PointCloudCollider ----------------------------------------------*
 ****************************************************************************
 * Description : Point cloud (i.e. a set of points) collider                *
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

#include "DWF_PointCloudCollider.h"

using namespace DWF_Collider;

//---------------------------------------------------------------------------
// PointCloud_Collider
//---------------------------------------------------------------------------
PointCloud_Collider::PointCloud_Collider() :
    Collider()
{}
//---------------------------------------------------------------------------
PointCloud_Collider::PointCloud_Collider(const DWF_Math::Vector3F&   pos,
                                         const DWF_Math::Matrix4x4F& matrix,
                                         const IPoints&              points) :
    Collider(pos, matrix)
{
    // set the point cloud. NOTE use the fully qualified name to avoid to use an inherited function)
    PointCloud_Collider::SetPoints(points);
}
//---------------------------------------------------------------------------
PointCloud_Collider::~PointCloud_Collider()
{}
//---------------------------------------------------------------------------
PointCloud_Collider::IPoints PointCloud_Collider::GetPoints() const
{
    // build transform matrix
    DWF_Math::Matrix4x4F matrix = m_MatRS;
    matrix.m_Table[3][0]        = m_Pos.m_X;
    matrix.m_Table[3][1]        = m_Pos.m_Y;
    matrix.m_Table[3][2]        = m_Pos.m_Z;

    IPoints points;

    // transform points
    for (std::size_t i = 0; i < m_Points.size(); ++i)
        points.push_back(matrix.Transform(m_Points[i]));

    return points;
}
//---------------------------------------------------------------------------
void PointCloud_Collider::SetPoints(const IPoints& points)
{
    m_Points = points;
}
//---------------------------------------------------------------------------
void PointCloud_Collider::AddPoint(const DWF_Math::Vector3F& point)
{
    m_Points.push_back(point);
}
//---------------------------------------------------------------------------
DWF_Math::Vector3F PointCloud_Collider::Support(const DWF_Math::Vector3F& dir) const
{
    if (m_Points.size())
        return DWF_Math::Vector3F();

    // find support in model space
    const DWF_Math::Vector3F invDir = m_InvMatRS.Transform(dir);

    DWF_Math::Vector3F furthestPoint = m_Points[0];
    float              maxDot        = furthestPoint.Dot(dir);

    for (std::size_t i = 1; i < m_Points.size(); ++i)
    {
        const DWF_Math::Vector3F v = m_Points[i];
        const float              d = v.Dot(dir);

        if (d > maxDot)
        {
            maxDot        = d;
            furthestPoint = v;
        }
    }

    // convert support to world space
    return m_MatRS.Transform(furthestPoint) + m_Pos;
}
//---------------------------------------------------------------------------
