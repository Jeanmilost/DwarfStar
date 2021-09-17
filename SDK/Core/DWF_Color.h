/****************************************************************************
 * ==> DWF_Color -----------------------------------------------------------*
 ****************************************************************************
 * Description:  Color                                                      *
 * Contained in: Core                                                       *
 * Developer:    Jean-Milost Reymond                                        *
 ****************************************************************************
 * MIT License - DwarfStar engine                                           *
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

// dwarfstar
#include "DWF_Object.h"

/**
* Color
*@author Jean-Milost Reymond
*/
template <class T>
class DWF_Color : public DWF_Object
{
    public:
        T m_R; // color red component
        T m_G; // color green component
        T m_B; // color blue component
        T m_A; // color alpha component

        inline DWF_Color();

        /**
        * Constructor
        *@param r - red component
        *@param g - green component
        *@param b - blue component
        *@param a - alpha component
        */
        inline DWF_Color(T r, T g, T b, T a);

        /**
        * Copy constructor
        *@param other - other color to copy from
        */
        inline DWF_Color(const DWF_Color& other);

        virtual ~DWF_Color();

        /**
        * Copy operator
        *@param other - other color to copy from
        *@return this vector
        */
        virtual inline DWF_Color& operator = (const DWF_Color& other);

        /**
        * Equality operator
        *@param value - value to compare
        *@return true if values are identical, otherwise false
        */
        virtual inline bool operator == (const DWF_Color& value) const;

        /**
        * Not equality operator
        *@param value - value to compare
        *@return true if values are not identical, otherwise false
        */
        virtual inline bool operator != (const DWF_Color& value) const;
};

typedef DWF_Color<unsigned> DWF_ColorU;
typedef DWF_Color<float>    DWF_ColorF;

//---------------------------------------------------------------------------
// DWF_Color
//---------------------------------------------------------------------------
template <class T>
DWF_Color<T>::DWF_Color() :
    DWF_Object(),
    m_R(T(0.0)),
    m_G(T(0.0)),
    m_B(T(0.0)),
    m_A(T(0.0))
{}
//---------------------------------------------------------------------------
template <class T>
DWF_Color<T>::DWF_Color(T r, T g, T b, T a) :
    DWF_Object(),
    m_R(r),
    m_G(g),
    m_B(b),
    m_A(a)
{}
//---------------------------------------------------------------------------
template <class T>
DWF_Color<T>::DWF_Color(const DWF_Color& other) :
    DWF_Object(),
    m_R(other.m_R),
    m_G(other.m_G),
    m_B(other.m_B),
    m_A(other.m_A)
{}
//---------------------------------------------------------------------------
template <class T>
DWF_Color<T>::~DWF_Color()
{}
//---------------------------------------------------------------------------
template<class T>
DWF_Color<T>& DWF_Color<T>::operator = (const DWF_Color& other)
{
    m_R = other.m_R;
    m_G = other.m_G;
    m_B = other.m_B;
    m_A = other.m_A;

    return *this;
}
//---------------------------------------------------------------------------
template<class T>
bool DWF_Color<T>::operator == (const DWF_Color& value) const
{
    return (m_R == value.m_R && m_G == value.m_G && m_B == value.m_B && m_A == value.m_A);
}
//---------------------------------------------------------------------------
template<class T>
bool DWF_Color<T>::operator != (const DWF_Color& value) const
{
    return (m_R != value.m_R || m_G != value.m_G || m_B != value.m_B || m_A != value.m_A);
}
//---------------------------------------------------------------------------
