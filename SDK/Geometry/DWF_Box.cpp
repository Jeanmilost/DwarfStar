/****************************************************************************
 * ==> DWF_Box -------------------------------------------------------------*
 ****************************************************************************
 * Description : Geometric box                                              *
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

#include "DWF_Box.h"

using namespace DWF_Geometry;

//---------------------------------------------------------------------------
// Box
//---------------------------------------------------------------------------
Box::Box()
{}
//---------------------------------------------------------------------------
Box::Box(const DWF_Math::Vector3F& min, const DWF_Math::Vector3F& max) :
    m_Min(min),
    m_Max(max)
{}
//---------------------------------------------------------------------------
Box::~Box()
{}
//---------------------------------------------------------------------------
Box* Box::ApplyMatrix(const DWF_Math::Matrix4x4F& matrix) const
{
    // build a new polygon transforming all vertices of the polygon using
    // given matrix, and return new built polygon
    return new Box(matrix.Transform(m_Min), matrix.Transform(m_Max));
}
//---------------------------------------------------------------------------
