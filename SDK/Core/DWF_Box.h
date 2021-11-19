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

#pragma once

// std
#include <cmath>

// retrograde engine
#include "DWF_Object.h"
#include "DWF_Vector3.h"
#include "DWF_Plane.h"
#include "DWF_Mesh.h"

/**
* Geometric box
*@author Jean-Milost Reymond
*/
class DWF_Box : public DWF_Object
{
    public:
        /**
        * Longest axis enumeration
        */
        enum class IEAxis
        {
            IE_A_X,
            IE_A_Y,
            IE_A_Z
        };

        DWF_Vector3F m_Min;
        DWF_Vector3F m_Max;

        /**
        * Constructor
        */
        DWF_Box();

        /**
        * Constructor
        *@param min - min corner
        *@param max - max corner
        */
        DWF_Box(const DWF_Vector3F& min, const DWF_Vector3F& max);

        /**
        * Destructor
        */
        virtual ~DWF_Box();

        /**
        * Gets center
        *@return center
        */
        virtual DWF_Vector3F GetCenter() const;

        /**
        * Gets longest axis
        *@return longest axis, @see IE_Axis enumeration
        */
        virtual IEAxis GetLongestAxis() const;

        /**
        * Gets splitting plane
        *@param axis - axis for which splitting plane should be get
        *@return splitting plane
        */
        virtual DWF_PlaneF GetSplittingPlane(IEAxis axis) const;

        /**
        * Gets splitting plane
        *@param axis - axis for which splitting plane should be get
        *@param center - box center
        *@return splitting plane
        */
        virtual DWF_PlaneF GetSplittingPlane(IEAxis axis, const DWF_Vector3F& center) const;

        /**
        * Cuts the box into 2 sub-boxes
        *@param[out] leftBox - left cut sub-box
        *@param[out] rightBox - right cut sub-box
        */
        virtual void Cut(DWF_Box& leftBox, DWF_Box& rightBox);

        /**
        * Check if a point is inside the box
        *@param x - point x coordinate
        *@param y - point y coordinate
        *@param z - point z coordinate
        *@return true if point is inside the box, otherwise false
        */
        virtual bool Inside(float x, float y, float z) const;

        /**
        * Check if a point is inside the box
        *@param point - point coordinate
        *@return true if point is inside the box, otherwise false
        */
        virtual bool Inside(const DWF_Vector3F& point) const;

        /**
        * Check if box intersects with another box
        *@param other - other box to check
        *@return true if boxes intersect, otherwise false
        */
        virtual bool Intersect(const DWF_Box& other) const;

        /**
        * Check if box intersects with a ray
        *@param ray - ray
        *@return true if box intersects ray, otherwise false
        */
        virtual bool Intersect(const DWF_RayF& ray) const;
};
