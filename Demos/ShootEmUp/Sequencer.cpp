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

#include "Sequencer.h"

// std
#include <memory>

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
DWF_Math::Vector3F Sequencer::GetPosition(const std::wstring& name, double elapsedTime) const
{
    ITasks::const_iterator it = m_Tasks.find(name);

    // task not found?
    if (it == m_Tasks.end())
        return DWF_Math::Vector3F();

    if (it->second->m_CmdIndex >= it->second->m_pSequence->m_Pattern.size())
        return DWF_Math::Vector3F();

    const ICommand* pRunningCmd = it->second->m_pSequence->m_Pattern[it->second->m_CmdIndex];

    switch (pRunningCmd->m_Curve)
    {
        case IECurve::IE_C_Linear:

        default:
            return DWF_Math::Vector3F();
    }
}
//---------------------------------------------------------------------------
