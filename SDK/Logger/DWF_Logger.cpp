/****************************************************************************
 * ==> DWF_Logger ----------------------------------------------------------*
 ****************************************************************************
 * Description : Application logger                                         *
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

#include "DWF_Logger.h"

using namespace DWF_Logger;

//---------------------------------------------------------------------------
// Static members
//---------------------------------------------------------------------------
std::unique_ptr<Logger::IInstance> Logger::m_pInstance;
std::mutex                         Logger::m_Mutex;
//---------------------------------------------------------------------------
// Logger::IInstance
//---------------------------------------------------------------------------
Logger::IInstance::IInstance()
{
    m_pInstance = new Logger();
}
//---------------------------------------------------------------------------
Logger::IInstance::~IInstance()
{
    if (m_pInstance)
        delete m_pInstance;
}
//---------------------------------------------------------------------------
// Logger
//---------------------------------------------------------------------------
Logger::Logger()
{}
//---------------------------------------------------------------------------
Logger::~Logger()
{
    Flush();
}
//---------------------------------------------------------------------------
const Logger& Logger::operator = (const Logger& other)
{
    throw new std::exception("Cannot create a copy of a singleton class");
}
//---------------------------------------------------------------------------
Logger* Logger::GetInstance()
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
        throw new std::exception("Could not create the logger unique instance");

    return m_pInstance->m_pInstance;
}
//---------------------------------------------------------------------------
void Logger::ReleaseInstance()
{
    // lock up the thread
    std::unique_lock<std::mutex> lock(m_Mutex);

    // release the instance
    m_pInstance.reset();
}
//---------------------------------------------------------------------------
void Logger::Open(const std::wstring& fileName)
{
    // already opened?
    if (!m_FileName.empty())
        return;

    m_FileName = fileName;

    // log the stream start
    m_Stream << L"Logs started" << std::endl;
    m_Stream << L"------------" << std::endl;
}
//---------------------------------------------------------------------------
void Logger::Flush() const
{
    // not opened?
    if (m_FileName.empty())
        return;

    DWF_Buffer::StdFileBuffer logFile;

    // open the log file
    logFile.Open(m_FileName, DWF_Buffer::FileBuffer::IEMode::IE_M_Write);

    const wchar_t      bom        = 0xFEFF;
    const std::wstring logContent = m_Stream.str();

    // flush the content
    logFile.Write(&bom, 2);
    logFile.Write(logContent.c_str(), logContent.length() * sizeof(wchar_t));
}
//---------------------------------------------------------------------------
