/****************************************************************************
 * ==> DWF_BoxCollider -----------------------------------------------------*
 ****************************************************************************
 * Description : Box collider                                               *
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

#include "DWF_BoxCollider.h"

using namespace DWF_Collider;

//---------------------------------------------------------------------------
// Box_Collider
//---------------------------------------------------------------------------
Box_Collider::Box_Collider() :
    Collider()
{}
//---------------------------------------------------------------------------
Box_Collider::Box_Collider(const DWF_Math::Vector3F&   pos,
                           const DWF_Math::Matrix4x4F& matrix,
                           const DWF_Math::Vector3F&   min,
                           const DWF_Math::Vector3F&   max) :
    Collider(pos, matrix)
{
    // set the box. NOTE use the fully qualified name to avoid to use an inherited function)
    Box_Collider::SetBox(min, max);
}
//---------------------------------------------------------------------------
Box_Collider::~Box_Collider()
{}
//---------------------------------------------------------------------------
Collider* Box_Collider::Clone() const
{
    return new Box_Collider(m_Pos, m_MatRS, m_Box.m_Min, m_Box.m_Max);
}
//---------------------------------------------------------------------------
DWF_Geometry::Box Box_Collider::GetBox() const
{
    // build transform matrix
    DWF_Math::Matrix4x4F matrix = m_MatRS;
    matrix.m_Table[3][0]        = m_Pos.m_X;
    matrix.m_Table[3][1]        = m_Pos.m_Y;
    matrix.m_Table[3][2]        = m_Pos.m_Z;

    // transform box
    std::unique_ptr<DWF_Geometry::Box> pBox(m_Box.ApplyMatrix(matrix));

    return DWF_Geometry::Box(pBox->m_Min, pBox->m_Max);
}
//---------------------------------------------------------------------------
void Box_Collider::SetBox(const DWF_Math::Vector3F& min, const DWF_Math::Vector3F& max)
{
    m_Box.m_Min = min;
    m_Box.m_Max = max;
}
//---------------------------------------------------------------------------
DWF_Math::Vector3F Box_Collider::Support(const DWF_Math::Vector3F& dir) const
{
    // find support in model space
    const DWF_Math::Vector3F invDir = m_InvMatRS.Transform(dir);

    DWF_Math::Vector3F result;
    result.m_X = (invDir.m_X > 0.0f) ? m_Box.m_Max.m_X : m_Box.m_Min.m_X;
    result.m_Y = (invDir.m_Y > 0.0f) ? m_Box.m_Max.m_Y : m_Box.m_Min.m_Y;
    result.m_Z = (invDir.m_Z > 0.0f) ? m_Box.m_Max.m_Z : m_Box.m_Min.m_Z;

    //convert support to world space
    return m_MatRS.Transform(result) + m_Pos;
}
//---------------------------------------------------------------------------
