/****************************************************************************
 * ==> DWF_Collider --------------------------------------------------------*
 ****************************************************************************
 * Description : Basic collider                                             *
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

#include "DWF_Collider.h"

using namespace DWF_Collider;

//---------------------------------------------------------------------------
// Collider
//---------------------------------------------------------------------------
Collider::Collider()
{
    // set the default matrix. NOTE use the fully qualified name to avoid to use an inherited function)
    Collider::SetMatrix(DWF_Math::Matrix4x4F::Identity());
}
//---------------------------------------------------------------------------
Collider::Collider(const DWF_Math::Vector3F& pos, const DWF_Math::Matrix4x4F& matrix)
{
    // set the position. NOTE use the fully qualified name to avoid to use an inherited function)
    Collider::SetPos(pos);

    // set the rotation/scale matrix. NOTE use the fully qualified name to avoid to use an inherited function)
    Collider::SetMatrix(matrix);
}
//---------------------------------------------------------------------------
Collider::~Collider()
{}
//---------------------------------------------------------------------------
Collider* Collider::Transform(const DWF_Math::Vector3F& pos, const DWF_Math::Matrix4x4F& matrix) const
{
    std::unique_ptr<Collider> pCollider(Clone());

    DWF_Math::Matrix4x4F matRS = matrix;
    matRS.m_Table[3][0]        = 0.0f;
    matRS.m_Table[3][1]        = 0.0f;
    matRS.m_Table[3][2]        = 0.0f;

    pCollider->m_Pos = pos + m_Pos;
    pCollider->SetMatrix(m_MatRS.Multiply(matRS));

    return pCollider.release();
}
//---------------------------------------------------------------------------
