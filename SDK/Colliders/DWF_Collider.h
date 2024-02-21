/****************************************************************************
 * ==> DWF_Collider --------------------------------------------------------*
 ****************************************************************************
 * Description : Basic collider                                             *
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
#include "DWF_Matrix4x4.h"

#pragma once

namespace DWF_Collider
{
    /**
    * Basic collider
    *@author Jean-Milost Reymond
    */
    class Collider
    {
        public:
            Collider();

            /**
            * Constructor
            *@param pos - the collider position to set
            *@param matrix - the collider rotation/scale matrix to set
            *@note If the matrix contains a position value, it will be ignored
            */
            Collider(const DWF_Math::Vector3F& pos, const DWF_Math::Matrix4x4F& matrix);

            virtual ~Collider();

            /**
            * Clones the collider
            *@return cloned collider
            *@note The returned collider should be deleted when useless
            */
            virtual Collider* Clone() const = 0;

            /**
            * Gets the collider position
            *@return the collider position
            */
            virtual inline DWF_Math::Vector3F GetPos() const;

            /**
            * Sets the collider position
            *@param pos - the collider position to set
            */
            virtual inline void SetPos(const DWF_Math::Vector3F& pos);

            /**
            * Gets the collider rotation/scale matrix
            *@return the collider rotation/scale matrix
            */
            virtual inline DWF_Math::Matrix4x4F GetMatrix() const;

            /**
            * Gets the collider inverted rotation/scale matrix
            *@return the collider inverted rotation/scale matrix
            */
            virtual inline DWF_Math::Matrix4x4F GetInvMatrix() const;

            /**
            * Sets the collider rotation/scale matrix
            *@param matrix - the collider rotation/scale matrix to set
            *@note If the matrix contains a position value, it will be ignored
            */
            virtual inline void SetMatrix(const DWF_Math::Matrix4x4F& matrix);

            /**
            * Support function for the Minkowski difference
            *@param dir - search direction
            *@return the furthest vertex belonging to the polygon along the direction
            */
            virtual DWF_Math::Vector3F Support(const DWF_Math::Vector3F& dir) const = 0;

            /**
            * Creates a new collider by transforming this collider by a transform pos and matrix
            *@param pos - the position by which the collider should be transformed
            *@param matrix - the rotation/scale matrix by which the collider should be transformed
            *@note The returned collider should be deleted when useless
            */
            virtual Collider* Transform(const DWF_Math::Vector3F& pos, const DWF_Math::Matrix4x4F& matrix) const;

        protected:
            DWF_Math::Vector3F   m_Pos;      // origin in world space
            DWF_Math::Matrix4x4F m_MatRS;    // rotation/scale model matrix
            DWF_Math::Matrix4x4F m_InvMatRS; // inverted rotation/scale matrix
    };

    /**
    * Collider list
    *@author Jean-Milost Reymond
    */
    typedef std::vector<Collider*> Colliders;

    //---------------------------------------------------------------------------
    // Collider
    //---------------------------------------------------------------------------
    inline DWF_Math::Vector3F Collider::GetPos() const
    {
        return m_Pos;
    }
    //---------------------------------------------------------------------------
    inline void Collider::SetPos(const DWF_Math::Vector3F& pos)
    {
        m_Pos = pos;
    }
    //---------------------------------------------------------------------------
    inline DWF_Math::Matrix4x4F Collider::GetMatrix() const
    {
        return m_MatRS;
    }
    //---------------------------------------------------------------------------
    inline DWF_Math::Matrix4x4F Collider::GetInvMatrix() const
    {
        return m_InvMatRS;
    }
    //---------------------------------------------------------------------------
    inline void Collider::SetMatrix(const DWF_Math::Matrix4x4F& matrix)
    {
        m_MatRS = matrix;

        // reset the position component (only rotation and scale are required)
        m_MatRS.m_Table[3][0] = 0.0f;
        m_MatRS.m_Table[3][1] = 0.0f;
        m_MatRS.m_Table[3][2] = 0.0f;

        // calculate the inverted rotation/scale matrix
        float determinant = 0.0f;
        m_InvMatRS = m_MatRS.Inverse(determinant);
    }
    //---------------------------------------------------------------------------
}
