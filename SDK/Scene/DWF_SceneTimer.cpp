/****************************************************************************
 * ==> DWF_SceneTimer ------------------------------------------------------*
 ****************************************************************************
 * Description : Scene timer                                                *
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

#include "DWF_SceneTimer.h"

using namespace DWF_Scene;

// std
#include <chrono>

//---------------------------------------------------------------------------
// Static members
//---------------------------------------------------------------------------
std::unique_ptr<Timer::IInstance> Timer::m_pInstance;
std::mutex                        Timer::m_Mutex;
//---------------------------------------------------------------------------
// Timer::IInstance
//---------------------------------------------------------------------------
Timer::IInstance::IInstance()
{
    m_pInstance = new Timer();
}
//---------------------------------------------------------------------------
Timer::IInstance::~IInstance()
{
    if (m_pInstance)
        delete m_pInstance;
}
//---------------------------------------------------------------------------
// Timer
//---------------------------------------------------------------------------
Timer::Timer()
{
    m_StartTime = std::chrono::system_clock::now();
}
//---------------------------------------------------------------------------
Timer::~Timer()
{}
//---------------------------------------------------------------------------
const Timer& Timer::operator = (const Timer& other)
{
    throw new std::exception("Cannot create a copy of a singleton class");
}
//---------------------------------------------------------------------------
Timer* Timer::GetInstance()
{
    // check instance out of the thread lock (double check lock)
    if (!m_pInstance)
    {
        // lock up the thread
        std::unique_lock<std::mutex> lock(m_Mutex);

        // create the instance
        if (!m_pInstance)
            m_pInstance.reset(new (std::nothrow)IInstance());
    }

    // still not created?
    if (!m_pInstance)
        throw new std::exception("Could not create the scene timer unique instance");

    return m_pInstance->m_pInstance;
}
//---------------------------------------------------------------------------
void Timer::ReleaseInstance()
{
    // lock up the thread
    std::unique_lock<std::mutex> lock(m_Mutex);

    // release the instance
    m_pInstance.reset();
}
//---------------------------------------------------------------------------
void Timer::StartTimerForItem(void* pItem)
{
    if (!pItem)
        return;

    IItems::iterator it = m_Items.find(pItem);

    if (it == m_Items.end())
    {
        m_Items[pItem] = std::chrono::system_clock::now();
        return;
    }

    it->second = std::chrono::system_clock::now();
}
//---------------------------------------------------------------------------
double Timer::GetElapsedTimeForItem(void* pItem) const
{
    if (!pItem)
        return 0.0;

    IItems::const_iterator it = m_Items.find(pItem);

    if (it == m_Items.end())
        return 0.0;

    // calculate the elapsed time
    const std::chrono::duration<double> elapsedTime = std::chrono::system_clock::now() - it->second;

    return elapsedTime.count() * 1000.0;
}
//---------------------------------------------------------------------------
double Timer::GetElapsedTimeSinceStart() const
{
    // calculate the elapsed time
    const std::chrono::duration<double> elapsedTime = std::chrono::system_clock::now() - m_StartTime;

    return elapsedTime.count() * 1000.0;
}
//---------------------------------------------------------------------------
std::size_t Timer::GetNextFrame(double&     elapsedTime,
                                std::size_t start,
                                std::size_t count,
                                double      duration,
                                bool        loop,
                                bool&       endReached) const
{
    endReached = false;

    if (!count)
        return 0;

    std::size_t frame = start;

    while (elapsedTime > duration)
    {
        ++frame;
        elapsedTime -= duration;
    }

    if (loop)
        frame = (frame % count);
    else
    if (frame >= count)
    {
        frame      = count - 1;
        endReached = true;
    }

    return frame;
}
//---------------------------------------------------------------------------
