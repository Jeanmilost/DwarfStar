/****************************************************************************
 * ==> DWF_CylinderCollider ------------------------------------------------*
 ****************************************************************************
 * Description : Cylinder collider                                          *
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
#include "DWF_Cylinder.h"
#include "DWF_Collider.h"

#pragma once

namespace DWF_Collider
{
    /**
    * Cylinder collider
    *@note This collider need to be height aligned with y axis, cannot be rotated
    *@author Jean-Milost Reymond
    */
    class Cylinder_Collider : public Collider
    {
        public:
            /*REM
            float m_Radius = 0.0f;
            float m_yCap   = 0.0f;
            float m_yBase  = 0.0f;
            */

            Cylinder_Collider();

            /**
            * Constructor
            *@param pos - the collider position to set
            *@param matrix - the collider rotation/scale matrix to set
            *@param radius - cylinder radius
            *@param yTop - cylinder top (or cap) position on y axis
            *@param yBottom - cylinder bottom (or base) position on y axis
            *@note If the matrix contains a position value, it will be ignored
            */
            Cylinder_Collider(const DWF_Math::Vector3F&   pos,
                              const DWF_Math::Matrix4x4F& matrix,
                                    float                 radius,
                                    float                 yTop,
                                    float                 yBottom);

            virtual ~Cylinder_Collider();

            /**
            * Clones the collider
            *@return cloned collider
            *@note The returned collider should be deleted when useless
            */
            virtual Collider* Clone() const;

            /**
            * Gets the capsule matching the collider
            *@return the capsule matching the collider
            */
            virtual DWF_Geometry::Cylinder GetCylinder() const;

            /**
            * Sets the collider capsule
            *@param radius - cylinder radius
            *@param yTop - cylinder top (or cap) position on y axis
            *@param yBottom - cylinder bottom (or base) position on y axis
            */
            virtual void SetCylinder(float radius, float yTop, float yBottom);

            /**
            * Support function for the Minkowski difference
            *@param dir - search direction
            *@return the furthest vertex belonging to the polygon along the direction
            */
            virtual DWF_Math::Vector3F Support(const DWF_Math::Vector3F& dir) const;

        protected:
            DWF_Geometry::Cylinder m_Cylinder;
    };
}
