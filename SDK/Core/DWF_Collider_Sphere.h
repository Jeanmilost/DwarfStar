/****************************************************************************
 * ==> DWF_Collider_Sphere -------------------------------------------------*
 ****************************************************************************
 * Description:  Sphere collider                                            *
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
#include "DWF_Collider.h"
#include "DWF_Sphere.h"

/**
* Sphere collider
*@author Jean-Milost Reymond
*/
class DWF_Collider_Sphere : public DWF_Collider
{
    public:
        DWF_Sphere m_Sphere;

        DWF_Collider_Sphere();
        virtual ~DWF_Collider_Sphere();

        /**
        * Checks if this a point is inside the collider
        *@param point - point to check
        *@return true if the point is inside the collider, otherwise false
        */
        virtual bool Inside(const DWF_Vector3F& point) const;

        /**
        * Checks if this collider collides with another collider
        *@param other - other collider to check against
        *@return true if this collider collides with the other collider, otherwise false
        */
        virtual bool Collide(const DWF_Collider& other) const;
};
