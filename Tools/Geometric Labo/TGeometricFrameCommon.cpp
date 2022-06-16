/****************************************************************************
 * ==> TGeometricFrameCommon -----------------------------------------------*
 ****************************************************************************
 * Description : This module provides a common set of classes and functions *
 *               to use with the geometric frames                           *
 * Developer   : Jean-Milost Reymond                                        *
 ****************************************************************************
 * MIT License - DwarfStar Engine                                           *
 *                                                                          *
 * Permission is hereby granted, free of charge, to any person obtaining a  *
 * copy of this software and associated documentation files (the            *
 * "Software"), to deal in the Software without restriction, including      *
 * without limitation the rights to use, copy, modify, merge, publish,      *
 * distribute, sublicense, and/or sell copies of the Software, and to       *
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

#include "TGeometricFrameCommon.h"

//---------------------------------------------------------------------------
void TGeometricFrameCommon::ValidateFloatResult(TEdit* pEdit, std::wstring& lastValidValue)
{
    if (!pEdit)
        return;

    try
    {
        // test the conversion to float and validate the result on success
        ::StrToFloat(pEdit->Text);
        lastValidValue = pEdit->Text.c_str();
    }
    catch (...)
    {}

    // is new change valid?
    if (pEdit->Text != UnicodeString(lastValidValue.c_str()))
    {
        // no, revert it and select the whole text
        pEdit->Text = lastValidValue.c_str();
        pEdit->SelectAll();
    }
}
//---------------------------------------------------------------------------
