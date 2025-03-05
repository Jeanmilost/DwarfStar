/****************************************************************************
 * ==> DWF_Force -----------------------------------------------------------*
 ****************************************************************************
 * Description : Physical force                                             *
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

#pragma once

// std
#include <vector>

// engine
#include "DWF_Vector3.h"

namespace DWF_Physics
{
    class Force
    {
        public:
            /**
            * Force value
            */
            /*REM
            struct IValue
            {
                DWF_Math::Vector3F m_Direction;      // for input and output, the force direction
                double             m_Speed    = 0.0; // for input, the speed to apply to the force
                double             m_Distance = 0.0; // for output, the distance to apply to the position in the calculated direction
            };
            */

            Force();
            virtual ~Force();

            /**
            * Gets the gravity force
            *@return the gravity force
            */
            virtual inline float GetGravity() const;

            /**
            * Sets the gravity force
            *@param value - the gravity force
            */
            virtual inline void SetGravity(float value);

            /**
            * Gets the friction force
            *@return the friction force
            */
            virtual inline float GetFriction() const;

            /**
            * Sets the friction force
            *@param value - the friction force
            */
            virtual inline void SetFriction(float value);

            /**
            * Gets the ground dir
            *@return the ground dir
            */
            virtual inline DWF_Math::Vector3F GetGroundDir() const;

            /**
            * Sets the ground dir
            *@param value - the ground dir
            */
            virtual inline void SetGroundDir(const DWF_Math::Vector3F& value);

            /**
            * Adds a new force to the current one
            *@param velocity - velocity
            */
            virtual void Add(const DWF_Math::Vector3F& velocity);

            /**
            * Calculates the resulting force
            *@return force
            */
            virtual DWF_Math::Vector3F Calculate();

        private:
            typedef std::vector<DWF_Math::Vector3F> IVelocities;

            IVelocities        m_Velocities;
            DWF_Math::Vector3F m_GroundDir;
            float              m_Gravity  = 0.05f;
            float              m_Friction = 0.006f;

            /**
            * Applies the friction to the force
            */
            void ApplyFriction();
    };

    //---------------------------------------------------------------------------
    // Force
    //---------------------------------------------------------------------------
    inline float Force::GetGravity() const
    {
        return m_Gravity;
    }
    //---------------------------------------------------------------------------
    inline void Force::SetGravity(float value)
    {
        m_Gravity = value;
    }
    //---------------------------------------------------------------------------
    inline float Force::GetFriction() const
    {
        return m_Friction;
    }
    //---------------------------------------------------------------------------
    inline void Force::SetFriction(float value)
    {
        m_Friction = value;
    }
    //---------------------------------------------------------------------------
    inline DWF_Math::Vector3F Force::GetGroundDir() const
    {
        return m_GroundDir;
    }
    //---------------------------------------------------------------------------
    inline void Force::SetGroundDir(const DWF_Math::Vector3F& value)
    {
        m_GroundDir = value;
    }
    //---------------------------------------------------------------------------
}
