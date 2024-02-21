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
std::wstring Helper::Utf8ToUtf16(const std::string& str)
{
    // convert utf8 to utf16
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    return converter.from_bytes(str.c_str());
}
//---------------------------------------------------------------------------
std::string Helper::Utf16ToUtf8(const std::wstring& str)
{
    // convert utf16 to utf8
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    return converter.to_bytes(str.c_str());
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
