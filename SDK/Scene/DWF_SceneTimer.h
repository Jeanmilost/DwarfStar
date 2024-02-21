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

 // std
#include <string>
#include <mutex>
#include <map>

#pragma once

namespace DWF_Scene
{
    /**
    * Scene timer
    *@author Jean-Milost Reymond
    */
    class Timer
    {
        public:
            /**
            * Gets scene timer instance
            *@return scene timer instance, nullptr on error
            */
            static Timer* GetInstance();

            /**
            * Releases the timer instance
            */
            static void ReleaseInstance();

            /**
            * Associates a timer to an item and starts it
            *@param pItem - item with which the timer should be associated
            */
            virtual void StartTimerForItem(void* pItem);

            /**
            * Gets the elapsed time from the timer associated with the timer
            *@return the elapsed time from the timer associated with the timer, in milliseconds
            */
            virtual double GetElapsedTimeForItem(void* pItem) const;

            /**
            * Gets the elapsed time since app start
            *@return the elapsed time since app start, in milliseconds
            */
            virtual double GetElapsedTimeSinceStart() const;

            /**
            * Calculates the next frame
            *@param[in, out] elapsedTime - elapsed time since last frame, in milliseconds
            *@param start - start frame from which the next one will be calculated
            *@param count - frame count
            *@param duration - frame duration, in milliseconds
            *@param loop - if true, the frame will loop on end reached
            *@param[out] endReached - if loop is set to false, will be set to true if end was reached on function ends
            */
            virtual std::size_t GetNextFrame(double&     elapsedTime,
                                             std::size_t start,
                                             std::size_t count,
                                             double      duration,
                                             bool        loop,
                                             bool&       endReached) const;

        private:
            /**
            * Instance class, needed to allow unique_ptr usage despite of singleton privacy and without
            * declare unique_ptr friend
            */
            struct IInstance
            {
                Timer* m_pInstance = nullptr;

                IInstance();
                virtual ~IInstance();
            };

            typedef std::map<void*, std::chrono::system_clock::time_point> IItems;

            static std::unique_ptr<IInstance>            m_pInstance;
            static std::mutex                            m_Mutex;
                   std::chrono::system_clock::time_point m_StartTime;
                   IItems                                m_Items;

            Timer();

            /**
            * Copy constructor
            *@param other - other timer to copy from
            */
            Timer(const Timer& other);

            ~Timer();

            /**
            * Copy operator
            *@param other - other timer to copy from
            */
            const Timer& operator = (const Timer& other);
    };
}
