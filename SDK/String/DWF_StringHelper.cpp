/****************************************************************************
 * ==> DWF_StringHelper ----------------------------------------------------*
 ****************************************************************************
 * Description: Helper class for strings                                    *
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

#include "DWF_StringHelper.h"

// std
#include <clocale>
#include <codecvt>

#if (__cplusplus >= 201703L)
    #ifdef _MSC_VER
        // windows
        #include <windows.h>
    #else
        // libraries
        #include "ConvertUTF.h"
    #endif
#endif

using namespace DWF_String;

//---------------------------------------------------------------------------
// Helper
//---------------------------------------------------------------------------
std::string Helper::SetLocale_ThreadSafe(int category, const char* pLocale)
{
    static std::mutex lockMutex;

    // lock up the thread
    std::unique_lock<std::mutex> lock(lockMutex);

    // change the locale and get the previous one
    const char* pRes = std::setlocale(category, pLocale);

    return pRes ? std::string(pRes) : std::string();
}
//---------------------------------------------------------------------------
std::string Helper::ToLowerCase(const std::string& str)
{
    std::string lowerStr;

    // save current locale
    const std::string loc = SetLocale_ThreadSafe(LC_ALL, nullptr);

    try
    {
        for (std::size_t i = 0; i < str.length(); ++i)
            lowerStr += ::tolower(str[i]);
    }
    catch (...)
    {
        // restore locale
        SetLocale_ThreadSafe(LC_ALL, loc.c_str());
        throw;
    }

    // restore locale
    SetLocale_ThreadSafe(LC_ALL, loc.c_str());

    return lowerStr;
}
//---------------------------------------------------------------------------
std::wstring Helper::ToLowerCase(const std::wstring& str)
{
    std::wstring lowerStr;

    // save current locale
    const std::string loc = SetLocale_ThreadSafe(LC_ALL, nullptr);

    try
    {
        for (std::size_t i = 0; i < str.length(); ++i)
            lowerStr += ::towlower(str[i]);
    }
    catch (...)
    {
        // restore locale
        SetLocale_ThreadSafe(LC_ALL, loc.c_str());
        throw;
    }

    // restore locale
    SetLocale_ThreadSafe(LC_ALL, loc.c_str());

    return lowerStr;
}
//---------------------------------------------------------------------------
std::string Helper::ToUpperCase(const std::string& str)
{
    std::string upperStr;

    // save current locale
    const std::string loc = SetLocale_ThreadSafe(LC_ALL, nullptr);

    try
    {
        for (std::size_t i = 0; i < str.length(); ++i)
            upperStr += ::toupper(str[i]);
    }
    catch (...)
    {
        // restore locale
        SetLocale_ThreadSafe(LC_ALL, loc.c_str());
        throw;
    }

    // restore locale
    SetLocale_ThreadSafe(LC_ALL, loc.c_str());

    return upperStr;
}
//---------------------------------------------------------------------------
std::wstring Helper::ToUpperCase(const std::wstring& str)
{
    std::wstring upperStr;

    // save current locale
    const std::string loc = SetLocale_ThreadSafe(LC_ALL, nullptr);

    try
    {
        for (std::size_t i = 0; i < str.length(); ++i)
            upperStr += ::towupper(str[i]);
    }
    catch (...)
    {
        // restore locale
        SetLocale_ThreadSafe(LC_ALL, loc.c_str());
        throw;
    }

    // restore locale
    SetLocale_ThreadSafe(LC_ALL, loc.c_str());

    return upperStr;
}
//---------------------------------------------------------------------------
std::wstring Helper::StrToWStr(const std::string& str)
{
    std::wstring result(str.length(), L' ');
    std::copy(str.begin(), str.end(), result.begin());
    return result;
}
//---------------------------------------------------------------------------
std::string Helper::WStrToStr(const std::wstring& str)
{
    std::string result(str.length(), ' ');
    std::copy(str.begin(), str.end(), result.begin());
    return result;
}
//---------------------------------------------------------------------------
std::wstring Helper::Utf8ToUtf16(const std::string& str)
{
    // string converter was deprecated since c++ 17 and removed since c++ 26. So no longer use it since c++ 17
    #if (__cplusplus < 201703L)
        // convert utf8 to utf16
        std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
        return converter.from_bytes(str.c_str());
    #else
        #ifdef _MSC_VER
            if (str.empty())
                return std::wstring();

            auto ssize = (int)str.size();
            auto wsize = ::MultiByteToWideChar(CP_UTF8, 0, str.data(), ssize, nullptr, 0);

            if (!wsize)
                return std::wstring();

            std::wstring ws;
            ws.resize(wsize);

            wsize = ::MultiByteToWideChar(CP_UTF8, 0, str.data(), ssize, &ws[0], wsize);

            if (!wsize)
                return std::wstring();

            return ws;
        #else
            // source code from:
            // http://www.codeproject.com/Articles/17573/Convert-Between-std-string-and-std-wstring-UTF-8-a

            std::size_t wideSize = str.length();

            // search for system char length (can be different on Windows, Linux, OSX or other systems)
            if (sizeof(wchar_t) == 2)
            {
                // calculate utf16 size, prepare utf16 container and calculate source and destination offsets
                wchar_t*    pWideStringNative = new wchar_t[wideSize + 1];
                const UTF8* pSourceStart      = reinterpret_cast<const UTF8*>(str.c_str());
                const UTF8* pSourceEnd        = pSourceStart + wideSize;
                UTF16*      pTargetStart      = reinterpret_cast<UTF16*>(pWideStringNative);
                UTF16*      pTargetEnd        = pTargetStart + wideSize + 1;

                // convert to utf16
                const int res = ConvertUTF8toUTF16(&pSourceStart,
                                                    pSourceEnd,
                                                   &pTargetStart,
                                                    pTargetEnd,
                                                    lenientConversion);

                // conversion failed?
                if (res != conversionOK)
                {
                    delete[] pWideStringNative;
                    throw new std::exception("Conversion failed - wchar_t length - 2");
                }

                // get and return utf16 converted string
                *pTargetStart = 0;
                std::wstring resultString(pWideStringNative);
                delete[] pWideStringNative;
                return resultString;
            }
            else
            if (sizeof(wchar_t) == 4)
            {
                // calculate utf16 size, prepare utf16 container and calculate source and destination offsets
                wchar_t*    pWideStringNative = new wchar_t[wideSize + 1];
                const UTF8* pSourceStart      = reinterpret_cast<const UTF8*>(str.c_str());
                const UTF8* pSourceEnd        = pSourceStart + wideSize;
                UTF32*      pTargetStart      = reinterpret_cast<UTF32*>(pWideStringNative);
                UTF32*      pTargetEnd        = pTargetStart + wideSize;

                // convert to utf16
                const int res = ConvertUTF8toUTF32(&pSourceStart,
                                                    pSourceEnd,
                                                   &pTargetStart,
                                                    pTargetEnd,
                                                    lenientConversion);

                // conversion failed?
                if (res != conversionOK)
                {
                    delete[] pWideStringNative;
                    throw new std::exception("Conversion failed - wchar_t length - 4");
                }

                // get and return utf16 converted string
                *pTargetStart = 0;
                std::wstring resultString(pWideStringNative);
                delete[] pWideStringNative;
                return resultString;
            }
            else
                throw new std::exception("Conversion failed - unknown wchar_t length");
        #endif
    #endif
}
//---------------------------------------------------------------------------
std::string Helper::Utf16ToUtf8(const std::wstring& str)
{
    // string converter was deprecated since c++ 17 and removed since c++ 26. So no longer use it since c++ 17
    #if (__cplusplus < 201703L)
        // convert utf16 to utf8
        std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
        return converter.to_bytes(str.c_str());
    #else
        #ifdef _MSC_VER
            if (str.empty())
                return std::string();

            auto wsize = (int)str.size();
            auto ssize = ::WideCharToMultiByte(CP_UTF8, 0, str.data(), wsize, nullptr, 0, nullptr, nullptr);

            if (!ssize)
                return std::string();

            std::string s;
            s.resize(ssize);

            ssize = ::WideCharToMultiByte(CP_UTF8, 0, str.data(), wsize, &s[0], ssize, nullptr, nullptr);

            if (!ssize)
                return std::string();

            return s;
        #else
            // source code from:
            // http://www.codeproject.com/Articles/17573/Convert-Between-std-string-and-std-wstring-UTF-8-a

            std::size_t wideSize = str.length();

            // search for system char length (can be different on Windows, Linux, OSX or other systems)
            if (sizeof(wchar_t) == 2)
            {
                // calculate utf8 size, prepare utf8 container and calculate source and destination offsets
                std::size_t  utf8Size          = 2 * wideSize + 1;
                char*        pUtf8StringNative = new char[utf8Size];
                const UTF16* pSourceStart      = reinterpret_cast<const UTF16*>(str.c_str());
                const UTF16* pSourceEnd        = pSourceStart + wideSize;
                UTF8*        pTargetStart      = reinterpret_cast<UTF8*>(pUtf8StringNative);
                UTF8*        pTargetEnd        = pTargetStart + utf8Size;

                // convert to utf8
                const int res = ConvertUTF16toUTF8(&pSourceStart,
                                                    pSourceEnd,
                                                   &pTargetStart,
                                                    pTargetEnd,
                                                    lenientConversion);

                // conversion failed?
                if (res != conversionOK)
                {
                    delete[] pUtf8StringNative;
                    throw new std::exception("Conversion failed - wchar_t length - 2");
                }

                // get and return utf8 converted string
                *pTargetStart = 0;
                std::string resultString(pUtf8StringNative);
                delete[] pUtf8StringNative;
                return resultString;
            }
            else
            if (sizeof(wchar_t) == 4)
            {
                // calculate utf8 size, prepare utf8 container and calculate source and destination offsets
                std::size_t  utf8Size          = 4 * wideSize + 1;
                char*        pUtf8StringNative = new char[utf8Size];
                const UTF32* pSourceStart      = reinterpret_cast<const UTF32*>(str.c_str());
                const UTF32* pSourceEnd        = pSourceStart + wideSize;
                UTF8*        pTargetStart      = reinterpret_cast<UTF8*>(pUtf8StringNative);
                UTF8*        pTargetEnd        = pTargetStart + utf8Size;

                // convert to utf8
                const int res = ConvertUTF32toUTF8(&pSourceStart,
                                                    pSourceEnd,
                                                   &pTargetStart,
                                                    pTargetEnd,
                                                    lenientConversion);

                // conversion failed?
                if (res != conversionOK)
                {
                    delete[] pUtf8StringNative;
                    throw new std::exception("Conversion failed - wchar_t length - 4");
                }

                // get and return utf8 converted string
                *pTargetStart = 0;
                std::string resultString(pUtf8StringNative);
                delete[] pUtf8StringNative;
                return resultString;
            }
            else
                throw new std::exception("Conversion failed - unknown wchar_t length");
        #endif
    #endif
}
//---------------------------------------------------------------------------
std::string Helper::BoolToStr(bool value, bool numeric)
{
    if (numeric)
        return value ? "1" : "0";

    return value ? "true" : "false";
}
//---------------------------------------------------------------------------
std::wstring Helper::BoolToWStr(bool value, bool numeric)
{
    if (numeric)
        return value ? L"1" : L"0";

    return value ? L"true" : L"false";
}
//---------------------------------------------------------------------------
bool Helper::StrToBool(const std::string& str)
{
    return (str == "1" || ToLowerCase(str) == "true") ? true : false;
}
//---------------------------------------------------------------------------
bool Helper::StrToBool(const std::wstring& str)
{
    return (str == L"1" || ToLowerCase(str) == L"true") ? true : false;
}
//---------------------------------------------------------------------------
