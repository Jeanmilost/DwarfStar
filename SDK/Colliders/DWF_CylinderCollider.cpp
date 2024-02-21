/****************************************************************************
 * ==> DWF_CylinderCollider ------------------------------------------------*
 ****************************************************************************
 * Description : Cylinder collider                                          *
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

#include "DWF_CylinderCollider.h"

using namespace DWF_Collider;

//---------------------------------------------------------------------------
// Cylinder_Collider
//---------------------------------------------------------------------------
Cylinder_Collider::Cylinder_Collider() :
    Collider()
{}
//---------------------------------------------------------------------------
Cylinder_Collider::Cylinder_Collider(const DWF_Math::Vector3F&   pos,
                                     const DWF_Math::Matrix4x4F& matrix,
                                           float                 radius,
                                           float                 yTop,
                                           float                 yBottom) :
    Collider(pos, matrix)
{
    // set the cylinder. NOTE use the fully qualified name to avoid to use an inherited function)
    Cylinder_Collider::SetCylinder(radius, yTop, yBottom);
}
//---------------------------------------------------------------------------
Cylinder_Collider::~Cylinder_Collider()
{}
//---------------------------------------------------------------------------
Collider* Cylinder_Collider::Clone() const
{
    return new Cylinder_Collider(m_Pos,
                                 m_MatRS,
                                 m_Cylinder.m_Radius,
                                 m_Cylinder.m_Top.m_Y,
                                 m_Cylinder.m_Bottom.m_Y);
}
//---------------------------------------------------------------------------
DWF_Geometry::Cylinder Cylinder_Collider::GetCylinder() const
{
    DWF_Geometry::Cylinder cylinder;
    cylinder.m_Radius = m_Cylinder.m_Radius;

    // build transform matrix
    DWF_Math::Matrix4x4F matrix = m_MatRS;
    matrix.m_Table[3][0]        = m_Pos.m_X;
    matrix.m_Table[3][1]        = m_Pos.m_Y;
    matrix.m_Table[3][2]        = m_Pos.m_Z;

    // transform the capsule top and bottom positions
    cylinder.m_Top    = matrix.Transform(m_Cylinder.m_Top);
    cylinder.m_Bottom = matrix.Transform(m_Cylinder.m_Bottom);

    return cylinder;
}
//---------------------------------------------------------------------------
void Cylinder_Collider::SetCylinder(float radius, float yTop, float yBottom)
{
    m_Cylinder.m_Radius     = radius;
    m_Cylinder.m_Top.m_Y    = yTop;
    m_Cylinder.m_Bottom.m_Y = yBottom;
}
//---------------------------------------------------------------------------
DWF_Math::Vector3F Cylinder_Collider::Support(const DWF_Math::Vector3F& dir) const
{
    // find support in model space
    const DWF_Math::Vector3F invDir = m_InvMatRS.Transform(dir);

    // calculate the furthest point on the XZ direction
    const DWF_Math::Vector3F dirXZ(invDir.m_X, 0.0f, invDir.m_Z);

    // now calculate the furthest point on the Y direction
    DWF_Math::Vector3F result = dirXZ.Normalize() * m_Cylinder.m_Radius;
    result.m_Y                = (invDir.m_Y > 0.0f) ? m_Cylinder.m_Top.m_Y : m_Cylinder.m_Bottom.m_Y;

    // convert support to world space
    return m_MatRS.Transform(result) + m_Pos;
}
//---------------------------------------------------------------------------
