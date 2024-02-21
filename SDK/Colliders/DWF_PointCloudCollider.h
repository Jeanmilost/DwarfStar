/****************************************************************************
 * ==> DWF_PointCloudCollider ----------------------------------------------*
 ****************************************************************************
 * Description : Point cloud (i.e. a set of points) collider                *
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

// std
#include <vector>

// classes
#include "DWF_Vector3.h"
#include "DWF_Collider.h"

#pragma once

namespace DWF_Collider
{
    /**
    * Point cloud (i.e. a set of points) collider
    *@author Jean-Milost Reymond
    */
    class PointCloud_Collider : public Collider
    {
        public:
            typedef std::vector<DWF_Math::Vector3F> IPoints;

            PointCloud_Collider();

            /**
            * Constructor
            *@param pos - the collider position to set
            *@param matrix - the collider rotation/scale matrix to set
            *@param points - points
            *@note If the matrix contains a position value, it will be ignored
            */
            PointCloud_Collider(const DWF_Math::Vector3F&   pos,
                                const DWF_Math::Matrix4x4F& matrix,
                                const IPoints&              points);

            virtual ~PointCloud_Collider();

            /**
            * Gets the points matching the collider
            *@return the points matching the collider
            */
            virtual IPoints GetPoints() const;

            /**
            * Sets the collider points
            *@param points - points
            */
            virtual void SetPoints(const IPoints& points);

            /**
            * Adds a point in the collider
            *@param point - point to add
            */
            virtual void AddPoint(const DWF_Math::Vector3F& point);

            /**
            * Support function for the Minkowski difference
            *@param dir - search direction
            *@return the furthest vertex belonging to the polygon along the direction
            */
            virtual DWF_Math::Vector3F Support(const DWF_Math::Vector3F& dir) const;

        protected:
            IPoints m_Points;
    };
}
