/****************************************************************************
 * ==> DWF_PolygonCollider -------------------------------------------------*
 ****************************************************************************
 * Description : Polygon collider                                           *
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

// classes
#include "DWF_Polygon.h"
#include "DWF_Collider.h"

#pragma once

namespace DWF_Collider
{
    /**
    * Polygon collider
    *@author Jean-Milost Reymond
    */
    class Polygon_Collider : public Collider
    {
        public:
            Polygon_Collider();

            /**
            * Constructor
            *@param v1 - first polygon vertex
            *@param v2 - second polygon vertex
            *@param v3 - third polygon vertex
            */
            Polygon_Collider(const DWF_Math::Vector3F& v1,
                             const DWF_Math::Vector3F& v2,
                             const DWF_Math::Vector3F& v3);

            virtual ~Polygon_Collider();

            /**
            * Gets the polygon matching the collider
            *@return the polygon matching the collider
            */
            virtual DWF_Geometry::Polygon GetPolygon() const;

            /**
            * Sets the collider polygon
            *@param v1 - first polygon vertex
            *@param v2 - second polygon vertex
            *@param v3 - third polygon vertex
            */
            virtual void SetPolygon(const DWF_Math::Vector3F& v1,
                                    const DWF_Math::Vector3F& v2,
                                    const DWF_Math::Vector3F& v3);

            /**
            * Support function for the Minkowski difference
            *@param dir - search direction
            *@return the furthest vertex belonging to the polygon along the direction
            */
            virtual DWF_Math::Vector3F Support(const DWF_Math::Vector3F& dir) const;

        protected:
            DWF_Geometry::Polygon m_Polygon;
            DWF_Math::Vector3F    m_Normal;
    };
}
