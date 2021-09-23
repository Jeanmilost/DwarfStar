/****************************************************************************
 * ==> DWF_Box -------------------------------------------------------------*
 ****************************************************************************
 * Description:  Geometric box                                              *
 * Contained in: Core                                                       *
 * Developer:    Jean-Milost Reymond                                        *
 ****************************************************************************
 * MIT License - DwarfStar engine                                           *
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

//---------------------------------------------------------------------------
// DWF_Box
//---------------------------------------------------------------------------
DWF_Box::DWF_Box() :
    DWF_Object()
{}
//---------------------------------------------------------------------------
DWF_Box::DWF_Box(const DWF_Vector3F& min, const DWF_Vector3F& max) :
    DWF_Object(),
    m_Min(min),
    m_Max(max)
{}
//---------------------------------------------------------------------------
DWF_Box::~DWF_Box()
{}
//---------------------------------------------------------------------------
DWF_Vector3F DWF_Box::GetCenter() const
{
    return DWF_Vector3F((m_Min.m_X + m_Max.m_X) / 2.0f,
                        (m_Min.m_Y + m_Max.m_Y) / 2.0f,
                        (m_Min.m_Z + m_Max.m_Z) / 2.0f);
}
//---------------------------------------------------------------------------
DWF_Box::IEAxis DWF_Box::GetLongestAxis() const
{
    // calculate each edge length
    const float x = std::fabs(m_Max.m_X - m_Min.m_X);
    const float y = std::fabs(m_Max.m_Y - m_Min.m_Y);
    const float z = std::fabs(m_Max.m_Z - m_Min.m_Z);

    // search for longest axis
    if (x >= y && x >= z)
        return IEAxis::IE_A_X;
    else
    if (y >= x && y >= z)
        return IEAxis::IE_A_Y;
    else
        return IEAxis::IE_A_Z;
}
//---------------------------------------------------------------------------
DWF_PlaneF DWF_Box::GetSplittingPlane(IEAxis axis) const
{
    switch (axis)
    {
        case IEAxis::IE_A_X: return DWF_PlaneF(1.0f, 0.0f, 0.0f, -GetCenter().m_X);
        case IEAxis::IE_A_Y: return DWF_PlaneF(0.0f, 1.0f, 0.0f, -GetCenter().m_Y);
        case IEAxis::IE_A_Z: return DWF_PlaneF(0.0f, 0.0f, 1.0f, -GetCenter().m_Z);
        default:             return DWF_PlaneF();
    }
}
//---------------------------------------------------------------------------
DWF_PlaneF DWF_Box::GetSplittingPlane(IEAxis axis, const DWF_Vector3F& center) const
{
    switch (axis)
    {
        case IEAxis::IE_A_X: return DWF_PlaneF(1.0f, 0.0f, 0.0f, -center.m_X);
        case IEAxis::IE_A_Y: return DWF_PlaneF(0.0f, 1.0f, 0.0f, -center.m_Y);
        case IEAxis::IE_A_Z: return DWF_PlaneF(0.0f, 0.0f, 1.0f, -center.m_Z);
        default:             return DWF_PlaneF();
    }
}
//-----------------------------------------------------------------------------------------
void DWF_Box::Cut(DWF_Box& leftBox, DWF_Box& rightBox)
{
    // calculate each edge length
    const float x = std::fabs(m_Max.m_X - m_Min.m_X);
    const float y = std::fabs(m_Max.m_Y - m_Min.m_Y);
    const float z = std::fabs(m_Max.m_Z - m_Min.m_Z);

    int longestAxis;

    // search for longest axis
    if ((x >= y) && (x >= z))
        longestAxis = 0;
    else
    if ((y >= x) && (y >= z))
        longestAxis = 1;
    else
        longestAxis = 2;

    // cut box
    switch (longestAxis)
    {
        // cut on x axis
        case 0:
            leftBox.m_Min     = m_Min;
            leftBox.m_Max     = m_Max;
            leftBox.m_Max.m_X = m_Min.m_X + (x * 0.5f);

            rightBox.m_Min     = m_Min;
            rightBox.m_Max     = m_Max;
            rightBox.m_Min.m_X = leftBox.m_Max.m_X;

            return;

        // cut on y axis
        case 1:
            leftBox.m_Min     = m_Min;
            leftBox.m_Max     = m_Max;
            leftBox.m_Max.m_Y = m_Min.m_Y + (y * 0.5f);

            rightBox.m_Min     = m_Min;
            rightBox.m_Max     = m_Max;
            rightBox.m_Min.m_Y = leftBox.m_Max.m_Y;

            return;

        // cut on z axis
        case 2:
            leftBox.m_Min     = m_Min;
            leftBox.m_Max     = m_Max;
            leftBox.m_Max.m_Z = m_Min.m_Z + (z * 0.5f);

            rightBox.m_Min     = m_Min;
            rightBox.m_Max     = m_Max;
            rightBox.m_Min.m_Z = leftBox.m_Max.m_Z;

            return;
    }
}
//---------------------------------------------------------------------------
bool DWF_Box::Inside(float x, float y, float z) const
{
    return Inside(DWF_Vector3F(x, y, z));
}
//---------------------------------------------------------------------------
bool DWF_Box::Inside(const DWF_Vector3F& point) const
{
    return (point.m_X >= m_Min.m_X &&
            point.m_Y >= m_Min.m_Y &&
            point.m_Z >= m_Min.m_Z &&
            point.m_X <= m_Max.m_X &&
            point.m_Y <= m_Max.m_Y &&
            point.m_Z <= m_Max.m_Z);
}
//---------------------------------------------------------------------------
bool DWF_Box::Intersect(const DWF_Box& other) const
{
    return !(m_Min.m_X > other.m_Max.m_X || m_Max.m_X < other.m_Min.m_X ||
             m_Min.m_Y > other.m_Max.m_Y || m_Max.m_Y < other.m_Min.m_Y ||
             m_Min.m_Z > other.m_Max.m_Z || m_Max.m_Z < other.m_Min.m_Z);
}
//---------------------------------------------------------------------------
