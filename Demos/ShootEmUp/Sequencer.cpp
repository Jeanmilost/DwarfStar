/****************************************************************************
 * ==> Sequencer -----------------------------------------------------------*
 ****************************************************************************
 * Description : Shoot-em-up sequencer which executes patterns              *
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

#include "Sequencer.h"

// std
#include <memory>

using namespace ShootEmUp;

//---------------------------------------------------------------------------
// Sequencer::ICommand
//---------------------------------------------------------------------------
Sequencer::ICommand::ICommand()
{}
//---------------------------------------------------------------------------
Sequencer::ICommand::~ICommand()
{}
//---------------------------------------------------------------------------
// Sequencer::ISequence
//---------------------------------------------------------------------------
Sequencer::ISequence::ISequence()
{}
//---------------------------------------------------------------------------
Sequencer::ISequence::~ISequence()
{
    for (std::size_t i = 0; i < m_Pattern.size(); ++i)
        delete m_Pattern[i];
}
//---------------------------------------------------------------------------
// Sequencer::ITask
//---------------------------------------------------------------------------
Sequencer::ITask::ITask()
{}
//---------------------------------------------------------------------------
Sequencer::ITask::~ITask()
{
    if (m_pSequence)
        delete m_pSequence;
}
//---------------------------------------------------------------------------
// Sequencer
//---------------------------------------------------------------------------
Sequencer::Sequencer()
{}
//---------------------------------------------------------------------------
Sequencer::~Sequencer()
{
    // delete all remaining running tasks
    for (ITasks::iterator it = m_Tasks.begin(); it != m_Tasks.end(); ++it)
        delete it->second;
}
//---------------------------------------------------------------------------
bool Sequencer::Add(ISequence* pSequence)
{
    if (!pSequence)
        return false;

    // sequence should be named
    if (pSequence->m_Name.empty())
        return false;

    // task already exists?
    if (m_Tasks.find(pSequence->m_Name) != m_Tasks.end())
        return false;

    // create a new task for the sequence
    std::unique_ptr<ITask> pTask = std::make_unique<ITask>();
    pTask->m_pSequence           = pSequence;
    pTask->m_Position            = pSequence->m_Position;

    // add the task to the running tasks
    m_Tasks[pSequence->m_Name] = pTask.get();
    pTask.release();

    return true;
}
//---------------------------------------------------------------------------
void Sequencer::Delete(const std::wstring& name)
{
    // get matching task
    ITasks::const_iterator it = m_Tasks.find(name);

    // task not found?
    if (it == m_Tasks.end())
        return;

    // delete task
    delete it->second;
    m_Tasks.erase(it);
}
//---------------------------------------------------------------------------
DWF_Math::Vector3F Sequencer::GetPosition(const std::wstring& name, double elapsedTime) const
{
    // get matching task
    ITasks::const_iterator it = m_Tasks.find(name);

    // task not found?
    if (it == m_Tasks.end())
        return DWF_Math::Vector3F();

    // end reached?
    if (it->second->m_Index >= it->second->m_pSequence->m_Pattern.size())
        return DWF_Math::Vector3F();

    // get running command
    const ICommand* pRunningCmd = it->second->m_pSequence->m_Pattern[it->second->m_Index];

    // dispatch the curve type
    switch (pRunningCmd->m_Curve)
    {
        case IECurve::IE_C_Linear:
        {
            // increase elapsed time
            it->second->m_ElapsedTime += elapsedTime;

            // sequence end reached?
            if (it->second->m_ElapsedTime >= pRunningCmd->m_Time)
            {
                // set time end and increase to next command
                it->second->m_ElapsedTime = pRunningCmd->m_Time;
                ++it->second->m_Index;

                // sequence end reached?
                if (it->second->m_Index >= it->second->m_pSequence->m_Pattern.size())
                {
                    // notify that sequence end was reached
                    if (m_fOnEndReached)
                        m_fOnEndReached(this, it->second->m_pSequence);

                    return DWF_Math::Vector3F();
                }
                else
                {
                    // calculate next start position and reset time
                    it->second->m_Position    += pRunningCmd->m_Direction * pRunningCmd->m_Length;
                    it->second->m_ElapsedTime  = 0.0;

                    return it->second->m_Position;
                }
            }

            // calculate distance from start point
            const double distance = (pRunningCmd->m_Length * it->second->m_ElapsedTime) / pRunningCmd->m_Time;

            // calculate and return next position
            return it->second->m_Position + (pRunningCmd->m_Direction * (float)distance);
        }

        default:
            return DWF_Math::Vector3F();
    }
}
//---------------------------------------------------------------------------
bool Sequencer::EndReached(const std::wstring& name) const
{
    // get matching task
    ITasks::const_iterator it = m_Tasks.find(name);

    // task not found?
    if (it == m_Tasks.end())
        return false;

    return (it->second->m_Index >= it->second->m_pSequence->m_Pattern.size());
}
//---------------------------------------------------------------------------
void Sequencer::Set_OnEndReached(ITfOnEndReached fOnEndReached)
{
    m_fOnEndReached = fOnEndReached;
}
//---------------------------------------------------------------------------
