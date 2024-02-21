/****************************************************************************
 * ==> DWF_CapsuleCollider -------------------------------------------------*
 ****************************************************************************
 * Description : Capsule collider                                           *
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

#include "DWF_CapsuleCollider.h"

using namespace DWF_Collider;

//---------------------------------------------------------------------------
// Capsule_Collider
//---------------------------------------------------------------------------
Capsule_Collider::Capsule_Collider() :
    Collider()
{}
//---------------------------------------------------------------------------
Capsule_Collider::Capsule_Collider(const DWF_Math::Vector3F&   pos,
                                   const DWF_Math::Matrix4x4F& matrix,
                                         float                 radius,
                                         float                 yTop,
                                         float                 yBottom,
                                         bool                  compensateRadius) :
    Collider(pos, matrix)
{
    // set the capsule. NOTE use the fully qualified name to avoid to use an inherited function)
    Capsule_Collider::SetCapsule(radius, yTop, yBottom, compensateRadius);
}
//---------------------------------------------------------------------------
Capsule_Collider::~Capsule_Collider()
{}
//---------------------------------------------------------------------------
Collider* Capsule_Collider::Clone() const
{
    return new Capsule_Collider(m_Pos,
                                m_MatRS,
                                m_Capsule.m_Radius,
                                m_Capsule.m_Top.m_Y,
                                m_Capsule.m_Bottom.m_Y,
                                false);
}
//---------------------------------------------------------------------------
DWF_Geometry::Capsule Capsule_Collider::GetCapsule() const
{
    DWF_Geometry::Capsule capsule;
    capsule.m_Radius = m_Capsule.m_Radius;

    // build transform matrix
    DWF_Math::Matrix4x4F matrix = m_MatRS;
    matrix.m_Table[3][0]        = m_Pos.m_X;
    matrix.m_Table[3][1]        = m_Pos.m_Y;
    matrix.m_Table[3][2]        = m_Pos.m_Z;

    // transform the capsule top and bottom positions
    capsule.m_Top    = matrix.Transform(m_Capsule.m_Top);
    capsule.m_Bottom = matrix.Transform(m_Capsule.m_Bottom);

    return capsule;
}
//---------------------------------------------------------------------------
void Capsule_Collider::SetCapsule(float radius, float yTop, float yBottom, bool compensateRadius)
{
    m_Capsule.m_Radius     = radius;
    m_Capsule.m_Top.m_Y    = compensateRadius ? yTop    + radius : yTop;
    m_Capsule.m_Bottom.m_Y = compensateRadius ? yBottom - radius : yBottom;
}
//---------------------------------------------------------------------------
DWF_Math::Vector3F Capsule_Collider::Support(const DWF_Math::Vector3F& dir) const
{
    // find support in model space
    const DWF_Math::Vector3F invDir = m_InvMatRS.Transform(dir);

    DWF_Math::Vector3F result  = invDir.Normalize() * m_Capsule.m_Radius;
    result.m_Y                += (dir.m_Y > 0.0f) ? (m_Capsule.m_Top.m_Y - m_Capsule.m_Radius) : (m_Capsule.m_Bottom.m_Y + m_Capsule.m_Radius);

    // convert support to world space
    return m_MatRS.Transform(result) + m_Pos;
}
//---------------------------------------------------------------------------
