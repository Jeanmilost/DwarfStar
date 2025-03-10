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

#include "DWF_Force.h"

using namespace DWF_Physics;

//---------------------------------------------------------------------------
// Force
//---------------------------------------------------------------------------
Force::Force() :
    m_GroundDir(0.0f, -1.0f, 0.0f)
{}
//---------------------------------------------------------------------------
Force::~Force()
{}
//---------------------------------------------------------------------------
void Force::Add(const DWF_Math::Vector3F& velocity)
{
    m_Velocities.push_back(velocity);
}
//---------------------------------------------------------------------------
DWF_Math::Vector3F Force::Calculate()
{
    // apply the friction to each force, except the gravity one
    ApplyFriction();

    // get the gravity force as base
    DWF_Math::Vector3F resultVector(m_GroundDir.m_X * m_Gravity, m_GroundDir.m_Y * m_Gravity, m_GroundDir.m_Z * m_Gravity);

    // apply each force to the result
    for (std::size_t i = 0; i < m_Velocities.size(); ++i)
        resultVector += m_Velocities[i];

    return resultVector;
}
//---------------------------------------------------------------------------
void Force::ApplyFriction()
{
    // no velocities to apply?
    if (m_Velocities.empty())
        return;

    // iterate through forces to apply
    for (std::int64_t i = m_Velocities.size() - 1; i >= 0; --i)
    {
        // subtract the friction from the force on the x axis
        if (m_Velocities[i].m_X > 0.0f)
        {
            m_Velocities[i].m_X -= m_Friction;

            if (m_Velocities[i].m_X <= 0.0f)
                m_Velocities[i].m_X = 0.0f;
        }
        else
        if (m_Velocities[i].m_X < 0.0f)
        {
            m_Velocities[i].m_X += m_Friction;

            if (m_Velocities[i].m_X >= 0.0f)
                m_Velocities[i].m_X = 0.0f;
        }

        // subtract the friction from the force on the y axis
        if (m_Velocities[i].m_Y > 0.0f)
        {
            m_Velocities[i].m_Y -= m_Friction;

            if (m_Velocities[i].m_Y <= 0.0f)
                m_Velocities[i].m_Y = 0.0f;
        }
        else
        if (m_Velocities[i].m_Y < 0.0f)
        {
            m_Velocities[i].m_Y += m_Friction;

            if (m_Velocities[i].m_Y >= 0.0f)
                m_Velocities[i].m_Y = 0.0f;
        }

        // subtract the friction from the force on the z axis
        if (m_Velocities[i].m_Z > 0.0f)
        {
            m_Velocities[i].m_Z -= m_Friction;

            if (m_Velocities[i].m_Z <= 0.0f)
                m_Velocities[i].m_Z = 0.0f;
        }
        else
        if (m_Velocities[i].m_Z < 0.0f)
        {
            m_Velocities[i].m_Z += m_Friction;

            if (m_Velocities[i].m_Z >= 0.0f)
                m_Velocities[i].m_Z = 0.0f;
        }

        // force has no longer effect?
        if (m_Velocities[i].m_X == 0.0f &&
            m_Velocities[i].m_Y == 0.0f &&
            m_Velocities[i].m_Z == 0.0f)
            // remove it from force list
            m_Velocities.erase(m_Velocities.begin() + i);
    }
}
//---------------------------------------------------------------------------
