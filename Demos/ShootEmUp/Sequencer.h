/****************************************************************************
 * ==> Sequencer -----------------------------------------------------------*
 ****************************************************************************
 * Description : Sequencer which executes patterns                          *
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
#include <map>
#include <vector>
#include <string>

// classes
#include "DWF_Vector3.h"

/**
* Sequencer which executes patterns
*@author Jean-Milost Reymond
*/
class Sequencer
{
    public:
        /**
        * Curve type
        */
        enum class IECurve
        {
            IE_C_Linear
        };

        /**
        * Command belonging to a sequence
        */
        struct ICommand
        {
            DWF_Math::Vector3F m_Direction;
            IECurve            m_Curve  = IECurve::IE_C_Linear;
            float              m_Length = 0.0f;
            double             m_Time   = 0.0;

            ICommand();
            virtual ~ICommand();
        };

        typedef std::vector<ICommand*> IPattern;

        /**
        * Sequence to execute
        */
        struct ISequence
        {
            std::wstring       m_Name;
            DWF_Math::Vector3F m_Position;
            IPattern           m_Pattern;

            ISequence();
            virtual ~ISequence();
        };

        Sequencer();
        virtual ~Sequencer();

        virtual bool Add(ISequence* pSequence);

        virtual DWF_Math::Vector3F GetPosition(const std::wstring& name, double elapsedTime) const;

    private:
        /**
        * Currently running task
        */
        struct ITask
        {
            ISequence*         m_pSequence   = nullptr;
            DWF_Math::Vector3F m_Position;
            std::size_t        m_Index       = 0;
            double             m_ElapsedTime = 0.0;

            ITask();
            ~ITask();
        };

        typedef std::map<std::wstring, ITask*> ITasks;

        ITasks m_Tasks;
};
