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

// std
#include <string>
#include <sstream>
#include <mutex>

// classes
#include "DWF_StdFileBuffer.h"
#include "DWF_Vector2.h"
#include "DWF_Vector3.h"
#include "DWF_Matrix4x4.h"
#include "DWF_Quaternion.h"

#pragma once

namespace DWF_Logger
{
    /**
    * Application logger
    *@author Jean-Milost Reymond
    */
    class Logger
    {
        public:
            /**
            * Gets logger instance
            *@return logger instance, nullptr on error
            */
            static Logger* GetInstance();

            /**
            * Releases the logger instance
            */
            static void ReleaseInstance();

            /**
            * Generic log indirection operator
            *@param msg - message to log
            *@return itself
            */
            template <class T>
            inline Logger& operator << (const T& msg);

            /**
            * Generic log indirection operator for 2D vector
            *@param value - value to log
            *@return itself
            */
            virtual inline Logger& operator << (const DWF_Math::Vector2F& value);

            /**
            * Generic log indirection operator for 3D vector
            *@param value - value to log
            *@return itself
            */
            virtual inline Logger& operator << (const DWF_Math::Vector3F& value);

            /**
            * Generic log indirection operator for 4x4 matrix
            *@param value - value to log
            *@return itself
            */
            virtual inline Logger& operator << (const DWF_Math::Matrix4x4F& value);

            /**
            * Generic log indirection operator for quaternion
            *@param value - value to log
            *@return itself
            */
            virtual inline Logger& operator << (const DWF_Math::QuaternionF& value);

            /**
            * Opens a log file and start to log
            *@param fileName - log file name
            */
            virtual void Open(const std::wstring& fileName);

        private:
            /**
            * Instance class, needed to allow unique_ptr usage despite of singleton privacy and without
            * declare unique_ptr friend
            */
            struct IInstance
            {
                Logger* m_pInstance = nullptr;

                IInstance();
                virtual ~IInstance();
            };

            static std::unique_ptr<IInstance> m_pInstance;
            static std::mutex                 m_Mutex;
                   std::wstring               m_FileName;
                   std::wostringstream        m_Stream;

            Logger();

            /**
            * Copy constructor
            *@param other - other logger to copy from
            */
            Logger(const Logger& other);

            ~Logger();

            /**
            * Copy operator
            *@param other - other logger to copy from
            */
            const Logger& operator = (const Logger& other);

            /**
            * Flushes the log content
            */
            void Flush() const;
    };

    //---------------------------------------------------------------------------
    // Logger
    //---------------------------------------------------------------------------
    template <class T>
    inline Logger& Logger::operator << (const T& msg)
    {
        m_Stream << msg;
        return *this;
    }
    //---------------------------------------------------------------------------
    inline Logger& Logger::operator << (const DWF_Math::Vector2F& value)
    {
        m_Stream << L"Vector 2:\n";
        m_Stream << L"[" << value.m_X << L", " << value.m_Y << L"]\n";
        return *this;
    }
    //---------------------------------------------------------------------------
    inline Logger& Logger::operator << (const DWF_Math::Vector3F& value)
    {
        m_Stream << L"Vector 3:\n";
        m_Stream << L"[" << value.m_X << L", " << value.m_Y << L", " << value.m_Z << L"]\n";
        return *this;
    }
    //---------------------------------------------------------------------------
    inline Logger& Logger::operator << (const DWF_Math::Matrix4x4F& value)
    {
        m_Stream << L"Matrix 4x4:\n";
        m_Stream << L"[" << value.m_Table[0][0] << L", " << value.m_Table[1][0] << L", " << value.m_Table[2][0] << L", " << value.m_Table[3][0] << L"]\n";
        m_Stream << L"[" << value.m_Table[0][1] << L", " << value.m_Table[1][1] << L", " << value.m_Table[2][1] << L", " << value.m_Table[3][1] << L"]\n";
        m_Stream << L"[" << value.m_Table[0][2] << L", " << value.m_Table[1][2] << L", " << value.m_Table[2][2] << L", " << value.m_Table[3][2] << L"]\n";
        m_Stream << L"[" << value.m_Table[0][3] << L", " << value.m_Table[1][3] << L", " << value.m_Table[2][3] << L", " << value.m_Table[3][3] << L"]\n";

        return *this;
    }
    //---------------------------------------------------------------------------
    inline Logger& Logger::operator << (const DWF_Math::QuaternionF& value)
    {
        m_Stream << L"Quaternion:\n";
        m_Stream << L"[" << value.m_X << L", " << value.m_Y << L", " << value.m_Z << L", " << value.m_W << L"]\n";
        return *this;
    }
    //---------------------------------------------------------------------------
}
