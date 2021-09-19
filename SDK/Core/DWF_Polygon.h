/****************************************************************************
 * ==> DWF_Polygon ---------------------------------------------------------*
 ****************************************************************************
 * Description:  Geometric Polygon                                          *
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

// std
#define _USE_MATH_DEFINES
#include <math.h>
#include <vector>
#include <list>

// dwarfstar
#include "DWF_Object.h"
#include "DWF_Vector3.h"
#include "DWF_Matrix4x4.h"
#include "DWF_Plane.h"

/**
* Geometric Polygon
*@author Jean-Milost Reymond
*/
template <class T>
class DWF_Polygon : public DWF_Object
{
    public:
        DWF_Vector3<T> m_Vertex[3];

        /**
        * Constructor
        */
        DWF_Polygon();

        /**
        * Constructor
        *@param vertex1 - first vertex of the polygon
        *@param vertex2 - second vertex of the polygon
        *@param vertex3 - third vertex of the polygon
        */
        DWF_Polygon(const DWF_Vector3<T>& vertex1,
                    const DWF_Vector3<T>& vertex2,
                    const DWF_Vector3<T>& vertex3);

        /**
        * Destructor
        */
        virtual ~DWF_Polygon();

        /**
        * Creates and returns a clone of the polygon
        *@return a clone of the polygon
        *@note The returned polygon should be deleted when useless
        */
        virtual DWF_Polygon* GetClone() const;

        /**
        * Gets the polygon plane
        *@return the polygon plane
        */
        virtual DWF_Plane<T> GetPlane() const;

        /**
        * Calculates and returns the center point of the polygon
        *@return the center point of the polygon
        */
        virtual DWF_Vector3<T> GetCenter() const;

        /**
        * Gets polygon normal
        *@return polygon normal
        *@note This normal is equivalent for each polygon vertices
        */
        virtual DWF_Vector3<T> GetNormal() const;

        /**
        * Gets lines joining each vertex
        *@param[out] lines - vector to fill with lines
        */
        virtual void GetLines(std::vector< DWF_Line<T> >& lines) const;

        /**
        * Checks if a point is inside polygon
        *@param x - point x coordinate
        *@param y - point y coordinate
        *@param z - point z coordinate
        *@return true if point is inside polygon, otherwise false
        */
        virtual bool Inside(T x, T y, T z) const;

        /**
        * Checks if a point is inside polygon
        *@param point - point coordinate
        *@return true if point is inside polygon, otherwise false
        */
        virtual bool Inside(const DWF_Vector3<T>& point) const;

        /**
        * Checks if polygon intersects with another polygon
        *@param other - other polygon to check
        *@param tolerance - tolerance
        *@return true if polygons intersect, otherwise false
        */
        virtual bool Intersect(const DWF_Polygon& other, T tolerance = M_Epsilon) const;

        /**
        * Applies the given matrix to the polygon
        *@param matrix - matrix to apply
        *@return transformed polygon
        *@note The returned polygon should be deleted when useless
        */
        virtual DWF_Polygon* ApplyMatrix(const DWF_Matrix4x4<T>& matrix) const;
};

typedef DWF_Polygon<float>  DWF_PolygonF;
typedef DWF_Polygon<double> DWF_PolygonD;

/**
* Polygon list
*@note This class is cross-platform
*@author Jean-Milost Reymond
*/
typedef std::list<DWF_PolygonF*> DWF_PolygonsF;
typedef std::list<DWF_PolygonD*> DWF_PolygonsD;

//---------------------------------------------------------------------------
// DWF_Polygon
//---------------------------------------------------------------------------
template <class T>
DWF_Polygon<T>::DWF_Polygon()
{}
//---------------------------------------------------------------------------
template <class T>
DWF_Polygon<T>::DWF_Polygon(const DWF_Vector3<T>& vertex1,
                            const DWF_Vector3<T>& vertex2,
                            const DWF_Vector3<T>& vertex3)
{
    m_Vertex[0] = vertex1;
    m_Vertex[1] = vertex2;
    m_Vertex[2] = vertex3;
}
//---------------------------------------------------------------------------
template <class T>
DWF_Polygon<T>::~DWF_Polygon()
{}
//---------------------------------------------------------------------------
template <class T>
DWF_Polygon<T>* DWF_Polygon<T>::GetClone() const
{
    // copies the polygon, then returns the copy
    return new DWF_Polygon<T>(m_Vertex[0], m_Vertex[1], m_Vertex[2]);
}
//---------------------------------------------------------------------------
template <class T>
DWF_Plane<T> DWF_Polygon<T>::GetPlane() const
{
    // calculates the plane from the values of the 3 vertices of the polygon
    return DWF_Plane<T>::FromPoints(m_Vertex[0], m_Vertex[1], m_Vertex[2]);
}
//---------------------------------------------------------------------------
template <class T>
DWF_Vector3<T> DWF_Polygon<T>::GetCenter() const
{
    // calculates then returns the value of the midpoint of the polygon
    return DWF_Vector3<T>(((m_Vertex[0].m_X + m_Vertex[1].m_X + m_Vertex[2].m_X) / T(3.0)),
                          ((m_Vertex[0].m_Y + m_Vertex[1].m_Y + m_Vertex[2].m_Y) / T(3.0)),
                          ((m_Vertex[0].m_Z + m_Vertex[1].m_Z + m_Vertex[2].m_Z) / T(3.0)));
}
//---------------------------------------------------------------------------
template <class T>
DWF_Vector3<T> DWF_Polygon<T>::GetNormal() const
{
    // get polygon plane
    const DWF_Plane<T> plane = GetPlane();

    // extract the polygon normal
    return DWF_Vector3<T>(plane.m_A, plane.m_B, plane.m_C);
}
//---------------------------------------------------------------------------
template <class T>
void DWF_Polygon<T>::GetLines(std::vector< DWF_Line<T> >& lines) const
{
    lines.resize(3);
    lines[0] = DWF_Line<T>(m_Vertex[0], m_Vertex[1]);
    lines[1] = DWF_Line<T>(m_Vertex[1], m_Vertex[2]);
    lines[2] = DWF_Line<T>(m_Vertex[2], m_Vertex[0]);
}
//---------------------------------------------------------------------------
template <class T>
bool DWF_Polygon<T>::Inside(T x, T y, T z) const
{
    return Inside(DWF_Vector3<T>(x, y, z));
}
//---------------------------------------------------------------------------
template <class T>
bool DWF_Polygon<T>::Inside(const DWF_Vector3<T>& point) const
{
    /*
    * check if the point p is inside the polygon in the following manner:
    *
    *                  V1                         V1
    *                  /\                         /\
    *                 /  \                       /  \
    *                / *p \                  *P /    \
    *               /      \                   /      \
    *            V2 -------- V3             V2 -------- V3
    *
    * calculate the vectors between the point p and each polygon vertex, then
    * calculate the angle formed by each of these vectors. If the sum of the
    * angles is equal to a complete circle, i.e. 2 * pi in radians, then the
    * point p is inside the polygon limits, otherwise the point is outside. It
    * is assumed that the point to check belongs to the polygon's plane
    */
    const DWF_Vector3<T> nPToV1 = (m_Vertex[0] - point).Normalize();
    const DWF_Vector3<T> nPToV2 = (m_Vertex[1] - point).Normalize();
    const DWF_Vector3<T> nPToV3 = (m_Vertex[2] - point).Normalize();

    // calculate the angles using the dot product of each vectors. Limit range
    // to values between -1.0f and 1.0f
    const T a1 = std::max(std::min(nPToV1.Dot(nPToV2), T(1.0)), T(-1.0));
    const T a2 = std::max(std::min(nPToV2.Dot(nPToV3), T(1.0)), T(-1.0));
    const T a3 = std::max(std::min(nPToV3.Dot(nPToV1), T(1.0)), T(-1.0));

    // calculate the sum of all angles
    const T angleResult = std::acos(a1) + std::acos(a2) + std::acos(a3);

    // if sum is equal to 2 PI radians then point p is inside polygon. NOTE can
    // be higher due to precision errors in calculations
    return (angleResult >= (M_PI * T(2.0)));
}
//---------------------------------------------------------------------------
template <class T>
bool DWF_Polygon<T>::Intersect(const DWF_Polygon& other, T tolerance) const
{
    // get planes from polygons
    const DWF_Plane<T> plane1 = GetPlane();
    const DWF_Plane<T> plane2 = other.GetPlane();

    // are planes merged?
    if (plane1 == plane2 || plane1 == -plane2)
    {
        // is any vertex inside other polygon?
        if (Inside(other.m_Vertex[0]) || Inside(other.m_Vertex[1]) || Inside(other.m_Vertex[2]) ||
            other.Inside(m_Vertex[0]) || other.Inside(m_Vertex[1]) || other.Inside(m_Vertex[2]))
            return true;

        std::vector< DWF_Line<T> > lines;
        std::vector< DWF_Line<T> > otherLines;

        // get polygons lines
        GetLines(lines);
        other.GetLines(otherLines);

        // is shortest distance between lines equal to 0?
        if (lines[0].GetShortestDistance(otherLines[0]) < tolerance)
            return true;

        // is shortest distance between lines equal to 0?
        if (lines[1].GetShortestDistance(otherLines[0]) < tolerance)
            return true;

        // is shortest distance between lines equal to 0?
        if (lines[2].GetShortestDistance(otherLines[0]) < tolerance)
            return true;

        // is shortest distance between lines equal to 0?
        if (lines[0].GetShortestDistance(otherLines[1]) < tolerance)
            return true;

        // is shortest distance between lines equal to 0?
        if (lines[1].GetShortestDistance(otherLines[1]) < tolerance)
            return true;

        // is shortest distance between lines equal to 0?
        if (lines[2].GetShortestDistance(otherLines[1]) < tolerance)
            return true;

        // is shortest distance between lines equal to 0?
        if (lines[0].GetShortestDistance(otherLines[2]) < tolerance)
            return true;

        // is shortest distance between lines equal to 0?
        if (lines[1].GetShortestDistance(otherLines[2]) < tolerance)
            return true;

        // is shortest distance between lines equal to 0?
        if (lines[2].GetShortestDistance(otherLines[2]) < tolerance)
            return true;

        return false;
    }

    // get plane normals
    DWF_Vector3<T> normal1(plane1.m_A, plane1.m_B, plane1.m_C);
    DWF_Vector3<T> normal2(plane2.m_A, plane2.m_B, plane2.m_C);

    // calculate angle between planes
    const T planesDot = normal1.Dot(normal2);

    // are plane parallels?
    if (planesDot == T(1.0) || planesDot == T(-1.0))
        // planes are parallels but not merged, no collision is possible
        return false;

    // calculate distance from each first polygon vertex to second polygon plane
    const T dist1v1 = plane2.DistanceTo(m_Vertex[0]);
    const T dist1v2 = plane2.DistanceTo(m_Vertex[1]);
    const T dist1v3 = plane2.DistanceTo(m_Vertex[2]);

    // get polygon lines
    std::vector< DWF_Line<T> > lines;
    GetLines(lines);

    // prepare list containing first polygon intersection points
    std::vector< DWF_Vector3<T> > p1pts;
    p1pts.reserve(2);

    // is first polygon V1 to V2 line segment intersects second polygon plane?
    if ((dist1v1 >= T(0.0) && dist1v2 < T(0.0)) || (dist1v1 < T(0.0) && dist1v2 >= T(0.0)))
    {
        DWF_Vector3<T> p;

        // calculate intersection point and add to list on success
        if (plane2.Intersect(lines[0], p))
            p1pts.push_back(p);
    }

    // is first polygon V2 to V3 line segment intersects second polygon plane?
    if ((dist1v2 >= T(0.0) && dist1v3 < T(0.0)) || (dist1v2 < T(0.0) && dist1v3 >= T(0.0)))
    {
        DWF_Vector3<T> p;

        // calculate intersection point and add to list on success
        if (plane2.Intersect(lines[1], p))
            p1pts.push_back(p);
    }

    // is first polygon V3 to V1 line segment intersects second polygon plane?
    if ((dist1v3 >= T(0.0) && dist1v1 < T(0.0)) || (dist1v3 < T(0.0) && dist1v1 >= T(0.0)))
    {
        DWF_Vector3<T> p;

        // calculate intersection point and add to list on success
        if (plane2.Intersect(lines[2], p))
            p1pts.push_back(p);
    }

    // were the first polygon 2 intersection point found?
    if (p1pts.size() != 2)
        return false;

    // calculate distance from each second polygon vertex to first polygon plane
    const T dist2v1 = plane1.DistanceTo(other.m_Vertex[0]);
    const T dist2v2 = plane1.DistanceTo(other.m_Vertex[1]);
    const T dist2v3 = plane1.DistanceTo(other.m_Vertex[2]);

    // get other polygon lines
    std::vector< DWF_Line<T> > otherLines;
    other.GetLines(otherLines);

    // prepare list containing second polygon intersection points
    std::vector< DWF_Vector3<T> > p2pts;
    p2pts.reserve(2);

    // is second polygon V1 to V2 line segment intersects first polygon plane?
    if ((dist2v1 >= T(0.0) && dist2v2 < T(0.0)) || (dist2v1 < T(0.0) && dist2v2 >= T(0.0)))
    {
        DWF_Vector3<T> p;

        // calculate intersection point and add to list on success
        if (plane1.Intersect(otherLines[0], p))
            p2pts.push_back(p);
    }

    // is second polygon V2 to V3 line segment intersects first polygon plane?
    if ((dist2v2 >= T(0.0) && dist2v3 < T(0.0)) || (dist2v2 < T(0.0) && dist2v3 >= T(0.0)))
    {
        DWF_Vector3<T> p;

        // calculate intersection point and add to list on success
        if (plane1.Intersect(otherLines[1], p))
            p2pts.push_back(p);
    }

    // is second polygon V3 to V1 line segment intersects first polygon plane?
    if ((dist2v3 >= T(0.0) && dist2v1 < T(0.0)) || (dist2v3 < T(0.0) && dist2v1 >= T(0.0)))
    {
        DWF_Vector3<T> p;

        // calculate intersection point and add to list on success
        if (plane1.Intersect(otherLines[2], p))
            p2pts.push_back(p);
    }

    // were the second polygon 2 intersection point found?
    if (p2pts.size() != 2)
        return false;

    // first and second polygon intersection points are on the same line, so
    // check if calculated first and second polygon segments intersect
    return (DWF_MathHelper::IsBetween(p1pts[0], p2pts[0], p2pts[1], tolerance) ||
            DWF_MathHelper::IsBetween(p1pts[1], p2pts[0], p2pts[1], tolerance) ||
            DWF_MathHelper::IsBetween(p2pts[0], p1pts[0], p1pts[1], tolerance) ||
            DWF_MathHelper::IsBetween(p2pts[1], p1pts[0], p1pts[1], tolerance));
}
//---------------------------------------------------------------------------
template <class T>
DWF_Polygon<T>* DWF_Polygon<T>::ApplyMatrix(const DWF_Matrix4x4<T>& matrix) const
{
    // build a new polygon transforming all vertices of the polygon using
    // matrix, and return new built polygon
    return new DWF_Polygon(matrix.Transform(m_Vertex[0]),
                           matrix.Transform(m_Vertex[1]),
                           matrix.Transform(m_Vertex[2]));
}
//---------------------------------------------------------------------------
