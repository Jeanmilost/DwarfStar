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

#pragma once

// std
#include <cmath>

// retrograde engine
#include "DWF_Object.h"
#include "DWF_Vector3.h"

/**
* Geometric sphere
*@author Jean-Milost Reymond
*/
class DWF_Sphere : public DWF_Object
{
    public:
        DWF_Vector3F m_Center;
        float        m_Radius = 0.0f;

        /**
        * Constructor
        */
        DWF_Sphere();

        /**
        * Constructor
        *@param center - center
        *@param radius - radius
        */
        DWF_Sphere(const DWF_Vector3F& center, float radius);

        /**
        * Destructor
        */
        virtual ~DWF_Sphere();

        /**
        * Check if a point is inside rectangle
        *@param x - point x coordinate
        *@param y - point y coordinate
        *@param Z - point z coordinate
        *@return true if point is inside the sphere, otherwise false
        */
        virtual bool Inside(float x, float y, float z) const;

        /**
        * Check if a point is inside the sphere
        *@param point - point coordinate
        *@return true if point is inside the sphere, otherwise false
        */
        virtual bool Inside(const DWF_Vector3F& point) const;

        /**
        * Check if sphere intersects with another sphere
        *@param other - other sphere to check
        *@return true if spheres intersect, otherwise false
        */
        virtual bool Intersect(const DWF_Sphere& other) const;
};
