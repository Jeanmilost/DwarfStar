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

#ifndef TGeometricFrameCommonH
#define TGeometricFrameCommonH

// vcl
#include <Vcl.StdCtrls.hpp>

// std
#include <string>

/**
* Common classes and functions for the geometric frames
*@author Jean-Milost Reymond
*/
class TGeometricFrameCommon
{
    public:
        /**
        * Validates the numerical result of an edit
        *@param pEdit - edit containing the result to validate
        *@param[in, out] lastValidValue - last known valid value
        */
        static void ValidateFloatResult(TEdit* pEdit, std::wstring& lastValidValue);
};

#endif
