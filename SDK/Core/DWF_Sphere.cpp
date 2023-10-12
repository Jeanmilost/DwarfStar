/****************************************************************************
 * ==> DWF_Sphere ----------------------------------------------------------*
 ****************************************************************************
 * Description : Geometric sphere                                           *
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

#include "DWF_Sphere.h"

// std
#include <memory>
#define _USE_MATH_DEFINES
#include <math.h>
#include <cmath>

//---------------------------------------------------------------------------
// DWF_Sphere
//---------------------------------------------------------------------------
DWF_Sphere::DWF_Sphere() :
    DWF_Object()
{}
//---------------------------------------------------------------------------
DWF_Sphere::DWF_Sphere(const DWF_Vector3F& center, float radius) :
    DWF_Object(),
    m_Center(center),
    m_Radius(radius)
{}
//---------------------------------------------------------------------------
DWF_Sphere::~DWF_Sphere()
{}
//---------------------------------------------------------------------------
bool DWF_Sphere::Inside(float x, float y, float z) const
{
    return Inside(DWF_Vector3F(x, y, z));
}
//---------------------------------------------------------------------------
bool DWF_Sphere::Inside(const DWF_Vector3F& point) const
{
    // calculate the distance between test point and the center of the sphere
    const DWF_Vector3F length   = point - m_Center;
    const float        distance = length.Length();

    // check if distance is shorter than the sphere radius and return result
    return (distance <= m_Radius);
}
//---------------------------------------------------------------------------
bool DWF_Sphere::Intersect(const DWF_Sphere& other) const
{
    const DWF_Vector3F dist(std::fabsf(m_Center.m_X - other.m_Center.m_X),
                            std::fabsf(m_Center.m_Y - other.m_Center.m_Y),
                            std::fabsf(m_Center.m_Z - other.m_Center.m_Z));

    const float length = dist.Length();

    return (length <= (m_Radius + other.m_Radius));
}
//---------------------------------------------------------------------------
