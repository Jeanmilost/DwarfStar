/****************************************************************************
 * ==> DWF_Plane -----------------------------------------------------------*
 ****************************************************************************
 * Description:  Geometric Plane                                            *
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

#pragma once

// dwarfstar
#include "DWF_Object.h"
#include "DWF_Vector3.h"
#include "DWF_Line.h"
#include "DWF_Ray.h"

/**
* Geometric Plane
*@author Jean-Milost Reymond
*/
template <class T>
class DWF_Plane : public DWF_Object
{
    public:
        T m_A; // plane a coordinate
        T m_B; // plane b coordinate
        T m_C; // plane c coordinate
        T m_D; // plane d coordinate

        /**
        * Constructor
        */
        inline DWF_Plane();

        /**
        * Constructor
        *@param a - a coordinate
        *@param b - b coordinate
        *@param c - c coordinate
        *@param d - d coordinate
        */
        inline DWF_Plane(T a, T b, T c, T d);

        /**
        * Copy constructor
        *@param other - other matrix to copy
        */
        inline DWF_Plane(const DWF_Plane& other);

        /**
        * Destructor
        */
        inline ~DWF_Plane();

        /**
        * Assignation operator
        *@param other - other matrix to copy from
        */
        virtual inline DWF_Plane& operator = (const DWF_Plane& other);

        /**
        * Operator -
        *@return inverted plane
        */
        virtual inline DWF_Plane operator - () const;

        /**
        * Operator ==
        *@param other - other plane to compare
        *@return true if planes are identical, otherwise false
        */
        virtual inline bool operator == (const DWF_Plane& other) const;

        /**
        * Operator !=
        *@param other - other plane to compare
        *@return true if planes are not identical, otherwise false
        */
        virtual inline bool operator != (const DWF_Plane& other) const;

        /**
        * Copies plane from another
        *@param other - other matrix to copy from
        */
        virtual inline void Copy(const DWF_Plane& other);

        /**
        * Calculates a plane using 3 vertex
        *@param v1 - value of the first vertex
        *@param v2 - value of the second vertex
        *@param v3 - value of the third vertex
        *@return the built plane
        */
        static DWF_Plane FromPoints(const DWF_Vector3<T>& v1,
                                    const DWF_Vector3<T>& v2,
                                    const DWF_Vector3<T>& v3);

        /**
        * Calculates a plane using a point and a normal
        *@param point - a point belongs to the plane
        *@param normal - normal of the plane
        *@return the built plane
        */
        static DWF_Plane FromPointNormal(const DWF_Vector3<T>& point,
                                         const DWF_Vector3<T>& normal);

        /**
        * Calculates distance to plane
        *@param point - point from which the distance must be calculated
        *@return distance to plane
        */
        virtual inline T DistanceTo(const DWF_Vector3<T>& point) const;

        /**
        * Checks if plane intersects line and calculates intersection point
        *@param line - line
        *@param[out] point - calculated point on plane
        *@return true if plane intersects line, otherwise false
        */
        virtual inline bool Intersect(const DWF_Line<T>& line, DWF_Vector3<T>& point) const;

        /**
        * Checks if plane intersects ray and calculates intersection point
        *@param ray - ray
        *@param[out] point - calculated point on plane
        *@return true if plane intersects ray, otherwise false
        */
        virtual inline bool Intersect(const DWF_Ray<T>& ray, DWF_Vector3<T>& point) const;

        /**
        * Compare plane with the given plane using the given tolerance
        *@param other - other plane to compare
        *@param tolerance - tolerance for comparison
        *@return true if planes are equals in the limits of the given tolerance,
        *         otherwise false
        */
        virtual inline bool Compare(const DWF_Plane& other, T tolerance) const;
};

typedef DWF_Plane<float>  DWF_PlaneF;
typedef DWF_Plane<double> DWF_PlaneD;

//---------------------------------------------------------------------------
// DWF_Plane
//---------------------------------------------------------------------------
template <class T>
DWF_Plane<T>::DWF_Plane() :
    DWF_Object(),
    m_A(T(0.0)),
    m_B(T(0.0)),
    m_C(T(0.0)),
    m_D(T(0.0))
{}
//---------------------------------------------------------------------------
template <class T>
DWF_Plane<T>::DWF_Plane(T a, T b, T c, T d) :
    DWF_Object(),
    m_A(a),
    m_B(b),
    m_C(c),
    m_D(d)
{}
//---------------------------------------------------------------------------
template <class T>
DWF_Plane<T>::DWF_Plane(const DWF_Plane& other) :
    DWF_Object()
{
    Copy(other);
}
//---------------------------------------------------------------------------
template <class T>
DWF_Plane<T>::~DWF_Plane()
{}
//---------------------------------------------------------------------------
template <class T>
DWF_Plane<T>& DWF_Plane<T>::operator = (const DWF_Plane& other)
{
    Copy(other);
    return *this;
}
//---------------------------------------------------------------------------
template <class T>
DWF_Plane<T> DWF_Plane<T>::operator - () const
{
    return DWF_Plane<T>(-m_A, -m_B, -m_C, -m_D);
}
//---------------------------------------------------------------------------
template <class T>
bool DWF_Plane<T>::operator == (const DWF_Plane<T>& other) const
{
    return ((m_A == other.m_A) && (m_B == other.m_B) && (m_C == other.m_C) && (m_D == other.m_D));
}
//---------------------------------------------------------------------------
template <class T>
bool DWF_Plane<T>::operator != (const DWF_Plane<T>& other) const
{
    return ((m_A != other.m_A) || (m_B != other.m_B) || (m_C != other.m_C) || (m_D != other.m_D));
}
//---------------------------------------------------------------------------
template <class T>
void DWF_Plane<T>::Copy(const DWF_Plane& other)
{
    m_A = other.m_A;
    m_B = other.m_B;
    m_C = other.m_C;
    m_D = other.m_D;
}
//---------------------------------------------------------------------------
template <class T>
DWF_Plane<T> DWF_Plane<T>::FromPoints(const DWF_Vector3<T>& v1,
                                      const DWF_Vector3<T>& v2,
                                      const DWF_Vector3<T>& v3)
{
    // calculate edge vectors
    const DWF_Vector3<T> e1 = v2 - v1;
    const DWF_Vector3<T> e2 = v3 - v1;

    // calculate the normal of the plane
    const DWF_Vector3<T> normal = e1.Cross(e2).Normalize();

    // calculate and return the plane
    return FromPointNormal(v1, normal);
}
//---------------------------------------------------------------------------
template <class T>
DWF_Plane<T> DWF_Plane<T>::FromPointNormal(const DWF_Vector3<T>& point,
                                           const DWF_Vector3<T>& normal)
{
    // the a, b, and c components are only the normal of the plane, and the D
    // component can be calculated using the aX + bY + cZ + d = 0 algorithm
    return DWF_Plane(normal.m_X,
                     normal.m_Y,
                     normal.m_Z,
                   -(normal.Dot(point)));
}
//---------------------------------------------------------------------------
template <class T>
T DWF_Plane<T>::DistanceTo(const DWF_Vector3<T>& point) const
{
    // get the normal of the plane
    const DWF_Vector3<T> n(m_A, m_B, m_C);

    // calculate the distance between the plane and the point
    return n.Dot(point) + m_D;
}
//---------------------------------------------------------------------------
template <class T>
bool DWF_Plane<T>::Intersect(const DWF_Line<T>& line, DWF_Vector3<T>& point) const
{
    const DWF_Ray<T> ray(line.m_Start, line.m_End - line.m_Start);

    return Intersect(ray, point);
}
//---------------------------------------------------------------------------
template <class T>
bool DWF_Plane<T>::Intersect(const DWF_Ray<T>& ray, DWF_Vector3<T>& point) const
{
    // gets the normal of the plane
    const DWF_Vector3<T> normal(m_A, m_B, m_C);

    // get ray position and dir
    const DWF_Vector3<T> rp = ray.GetPos();
    const DWF_Vector3<T> rd = ray.GetDir();

    // calculates the angle between the line and the normal to the plane
    const T dot = normal.Dot(rd);

    // if normal to the plane is perpendicular to the line, then the line is
    // either parallel to the plane and there are no solutions or the line is
    // on the plane in which case there are an infinite number of solutions
    if (!dot)
        return false;

    const T temp = (m_D + normal.Dot(rp)) / dot;

    // calculates the intersection point
    point = DWF_Vector3<T>(rp.m_X - (temp * rd.m_X),
                           rp.m_Y - (temp * rd.m_Y),
                           rp.m_Z - (temp * rd.m_Z));

    return true;
}
//---------------------------------------------------------------------------
template <class T>
bool DWF_Plane<T>::Compare(const DWF_Plane<T>& other, T tolerance) const
{
    return (((m_A >= (other.m_A - tolerance))  &&
             (m_A <= (other.m_A + tolerance))) &&
            ((m_B >= (other.m_B - tolerance))  &&
             (m_B <= (other.m_B + tolerance))) &&
            ((m_C >= (other.m_C - tolerance))  &&
             (m_C <= (other.m_C + tolerance))) &&
            ((m_D >= (other.m_D - tolerance))  &&
             (m_D <= (other.m_D + tolerance))));
}
//---------------------------------------------------------------------------