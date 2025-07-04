/****************************************************************************
 * ==> DWF_Particle --------------------------------------------------------*
 ****************************************************************************
 * Description: Item for particles system                                   *
 * Developer:   Jean-Milost Reymond                                         *
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

// classes
#include "DWF_Vector3.h"
#include "DWF_Matrix4x4.h"

namespace DWF_Particles
{
    /**
    * Item for particle system
    *@author Jean-Milost Reymond
    */
    class Particle
    {
        public:
            DWF_Math::Vector3F   m_StartPos;           // particle start position
            DWF_Math::Vector3F   m_Velocity;           // velocity to apply to the particle
            DWF_Math::Matrix4x4F m_Matrix;             // particle matrix, which will be applied while the drawing
            float                m_Gravity     = 0.0f; // gravity to apply to particle
            double               m_Lifetime    = 0.0;  // particle lifetime
            double               m_ElapsedTime = 0.0;  // elapsed time since particle appeared

            Particle();
            virtual ~Particle();
    };
}
