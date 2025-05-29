/****************************************************************************
 * ==> DWF_Particles -------------------------------------------------------*
 ****************************************************************************
 * Description: Particles system                                            *
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

#include "DWF_Particles.h"

using namespace DWF_Particles;

//---------------------------------------------------------------------------
// Particles
//---------------------------------------------------------------------------
Particles::Particles()
{}
//---------------------------------------------------------------------------
Particles::~Particles()
{
    for (std::size_t i = 0; i < m_Particles.size(); ++i)
        delete m_Particles[i];
}
//---------------------------------------------------------------------------
Particle* Particles::Add()
{
    std::unique_ptr<Particle> pParticle = std::make_unique<Particle>();

    m_Particles.push_back(pParticle.get());

    return pParticle.release();
}
//---------------------------------------------------------------------------
void Particles::Add(std::size_t count)
{
    for (std::size_t i = 0; i < count; ++i)
        Add();
}
//---------------------------------------------------------------------------
void Particles::Delete(Particle* pParticle)
{
    for (std::size_t i = 0; i < m_Particles.size(); ++i)
        if (m_Particles[i] == pParticle)
        {
            delete m_Particles[i];
            m_Particles.erase(m_Particles.begin() + i);
            return;
        }
}
//---------------------------------------------------------------------------
void Particles::DeleteAt(std::size_t index)
{
    if (index >= m_Particles.size())
        return;

    delete m_Particles[index];
    m_Particles.erase(m_Particles.begin() + index);
}
//---------------------------------------------------------------------------
Particle* Particles::Get(std::size_t index) const
{
    if (index >= m_Particles.size())
        return nullptr;

    return m_Particles[index];
}
//---------------------------------------------------------------------------
std::size_t Particles::GetCount() const
{
    return m_Particles.size();
}
//---------------------------------------------------------------------------
void Particles::Animate(double elapsedTime)
{
    if (!m_Particles.size())
        return;

    if (!m_fOnCalculateMotion)
        return;

    for (std::size_t i = 0; i < m_Particles.size(); ++i)
        m_fOnCalculateMotion(this, m_Particles[i], elapsedTime);
}
//---------------------------------------------------------------------------
void Particles::Set_OnCalculateMotion(ITfOnCalculateMotion fOnCalculateMotion)
{
    m_fOnCalculateMotion = fOnCalculateMotion;
}
//---------------------------------------------------------------------------
