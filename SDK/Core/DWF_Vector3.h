/****************************************************************************
 * ==> DWF_Vector3 ---------------------------------------------------------*
 ****************************************************************************
 * Description:  3D vector                                                  *
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

// std
#include <algorithm>

// dwarfstar
#include "DWF_Object.h"

/**
* 3D vector
*@author Jean-Milost Reymond
*/
template <class T>
class DWF_Vector3 : public DWF_Object
{
    public:
        T m_X; // vector x coordinate
        T m_Y; // vector y coordinate
        T m_Z; // vector z coordinate

        inline DWF_Vector3();

        /**
        * Constructor
        *@param x - x coordinate
        *@param y - y coordinate
        *@param z - z coordinate
        */
        inline DWF_Vector3(T x, T y, T z);

        /**
        * Copy constructor
        *@param other - other vector to copy from
        */
        inline DWF_Vector3(const DWF_Vector3& other);

        virtual ~DWF_Vector3();

        /**
        * Copy operator
        *@param other - other vector to copy from
        *@return this vector
        */
        virtual inline DWF_Vector3& operator = (const DWF_Vector3& other);

        /**
        * Addition operator
        *@param value - value to add
        *@return resulting vector
        */
        virtual inline DWF_Vector3 operator + (const DWF_Vector3& value) const;
        virtual inline DWF_Vector3 operator + (const T&           value) const;

        /**
        * Subtraction operator
        *@param value - value to subtract
        *@return resulting vector
        */
        virtual inline DWF_Vector3 operator - (const DWF_Vector3& value) const;
        virtual inline DWF_Vector3 operator - (const T&           value) const;

        /**
        * Negation operator
        *@return inverted vector
        */
        virtual inline DWF_Vector3 operator - () const;

        /**
        * Multiplication operator
        *@param value - value to multiply
        *@return resulting vector
        */
        virtual inline DWF_Vector3 operator * (const DWF_Vector3& value) const;
        virtual inline DWF_Vector3 operator * (const T&           value) const;

        /**
        * Division operator
        *@param value - value to divide
        *@return resulting vector
        */
        virtual inline DWF_Vector3 operator / (const DWF_Vector3& value) const;
        virtual inline DWF_Vector3 operator / (const T&           value) const;

        /**
        * Addition and assignation operator
        *@param value - value to add
        *@return resulting vector
        */
        virtual inline const DWF_Vector3& operator += (const DWF_Vector3& value);
        virtual inline const DWF_Vector3& operator += (const T&           value);

        /**
        * Subtraction and assignation operator
        *@param value - value to subtract
        *@return resulting vector
        */
        virtual inline const DWF_Vector3& operator -= (const DWF_Vector3& value);
        virtual inline const DWF_Vector3& operator -= (const T&           value);

        /**
        * Multiplication and assignation operator
        *@param value - value to multiply
        *@return resulting vector
        */
        virtual inline const DWF_Vector3& operator *= (const DWF_Vector3& value);
        virtual inline const DWF_Vector3& operator *= (const T&           value);

        /**
        * Division and assignation operator
        *@param value - value to divide
        *@return resulting vector
        */
        virtual inline const DWF_Vector3& operator /= (const DWF_Vector3& value);
        virtual inline const DWF_Vector3& operator /= (const T&           value);

        /**
        * Equality operator
        *@param value - value to compare
        *@return true if values are identical, otherwise false
        */
        virtual inline bool operator == (const DWF_Vector3& value) const;

        /**
        * Not equality operator
        *@param value - value to compare
        *@return true if values are not identical, otherwise false
        */
        virtual inline bool operator != (const DWF_Vector3& value) const;

        /**
        * Calculates the vector length
        *@return vector length
        */
        virtual inline T Length() const;

        /**
        * Normalizes the vector
        *@return normalized vector
        */
        virtual inline DWF_Vector3 Normalize() const;

        /**
        * Calculates cross product between 2 vectors
        *@param vector - other vector to cross with
        *@return the resulting vector
        */
        virtual inline DWF_Vector3 Cross(const DWF_Vector3& vector) const;

        /**
        * Calculates dot product between 2 vectors
        *@param vector - other vector to dot with
        *@return resulting angle
        */
        virtual inline T Dot(const DWF_Vector3& vector) const;
};

typedef DWF_Vector3<float>  DWF_Vector3F;
typedef DWF_Vector3<double> DWF_Vector3D;

//---------------------------------------------------------------------------
// DWF_Vector3
//---------------------------------------------------------------------------
template <class T>
DWF_Vector3<T>::DWF_Vector3() :
    DWF_Object(),
    m_X(T(0.0)),
    m_Y(T(0.0)),
    m_Z(T(0.0))
{}
//---------------------------------------------------------------------------
template <class T>
DWF_Vector3<T>::DWF_Vector3(T x, T y, T z) :
    DWF_Object(),
    m_X(x),
    m_Y(y),
    m_Z(z)
{}
//---------------------------------------------------------------------------
template <class T>
DWF_Vector3<T>::DWF_Vector3(const DWF_Vector3& other) :
    DWF_Object(),
    m_X(other.m_X),
    m_Y(other.m_Y),
    m_Z(other.m_Z)
{}
//---------------------------------------------------------------------------
template <class T>
DWF_Vector3<T>::~DWF_Vector3()
{}
//---------------------------------------------------------------------------
template<class T>
DWF_Vector3<T>& DWF_Vector3<T>::operator = (const DWF_Vector3& other)
{
    m_X = other.m_X;
    m_Y = other.m_Y;
    m_Z = other.m_Z;

    return *this;
}
//---------------------------------------------------------------------------
template<class T>
DWF_Vector3<T> DWF_Vector3<T>::operator + (const DWF_Vector3& value) const
{
    return DWF_Vector3(m_X + value.m_X, m_Y + value.m_Y, m_Z + value.m_Z);
}
//---------------------------------------------------------------------------
template<class T>
DWF_Vector3<T> DWF_Vector3<T>::operator + (const T& value) const
{
    return DWF_Vector3(m_X + value, m_Y + value, m_Z + value);
}
//---------------------------------------------------------------------------
template<class T>
DWF_Vector3<T> DWF_Vector3<T>::operator - (const DWF_Vector3& value) const
{
    return DWF_Vector3(m_X - value.m_X, m_Y - value.m_Y, m_Z - value.m_Z);
}
//---------------------------------------------------------------------------
template<class T>
DWF_Vector3<T> DWF_Vector3<T>::operator - (const T& value) const
{
    return DWF_Vector3(m_X - value, m_Y - value, m_Z - value);
}
//---------------------------------------------------------------------------
template<class T>
DWF_Vector3<T> DWF_Vector3<T>::operator - () const
{
    return DWF_Vector3<T>(-m_X, -m_Y, -m_Z);
}
//---------------------------------------------------------------------------
template<class T>
DWF_Vector3<T> DWF_Vector3<T>::operator * (const DWF_Vector3& value) const
{
    return DWF_Vector3(m_X * value.m_X, m_Y * value.m_Y, m_Z * value.m_Z);
}
//---------------------------------------------------------------------------
template<class T>
DWF_Vector3<T> DWF_Vector3<T>::operator * (const T& value) const
{
    return DWF_Vector3(m_X * value, m_Y * value, m_Z * value);
}
//---------------------------------------------------------------------------
template<class T>
DWF_Vector3<T> DWF_Vector3<T>::operator / (const DWF_Vector3& value) const
{
    if (!value.m_X)
        throw new std::exception("Division by 0 error - invalid m_X value");

    if (!value.m_Y)
        throw new std::exception("Division by 0 error - invalid m_Y value");

    if (!value.m_Z)
        throw new std::exception("Division by 0 error - invalid m_Z value");

    return DWF_Vector3(m_X / value.m_X, m_Y / value.m_Y, m_Z / value.m_Z);
}
//---------------------------------------------------------------------------
template<class T>
DWF_Vector3<T> DWF_Vector3<T>::operator / (const T& value) const
{
    if (!value)
        throw new std::exception("Division by 0 error - invalid value");

    return DWF_Vector3(m_X / value, m_Y / value, m_Z / value);
}
//---------------------------------------------------------------------------
template<class T>
const DWF_Vector3<T>& DWF_Vector3<T>::operator += (const DWF_Vector3& value)
{
    m_X += value.m_X;
    m_Y += value.m_Y;
    m_Z += value.m_Z;

    return *this;
}
//---------------------------------------------------------------------------
template<class T>
const DWF_Vector3<T>& DWF_Vector3<T>::operator += (const T& value)
{
    m_X += value;
    m_Y += value;
    m_Z += value;

    return *this;
}
//---------------------------------------------------------------------------
template<class T>
const DWF_Vector3<T>& DWF_Vector3<T>::operator -= (const DWF_Vector3& value)
{
    m_X -= value.m_X;
    m_Y -= value.m_Y;
    m_Z -= value.m_Z;

    return *this;
}
//---------------------------------------------------------------------------
template<class T>
const DWF_Vector3<T>& DWF_Vector3<T>::operator -= (const T& value)
{
    m_X -= value;
    m_Y -= value;
    m_Z -= value;

    return *this;
}
//---------------------------------------------------------------------------
template<class T>
const DWF_Vector3<T>& DWF_Vector3<T>::operator *= (const DWF_Vector3& value)
{
    m_X *= value.m_X;
    m_Y *= value.m_Y;
    m_Z *= value.m_Z;

    return *this;
}
//---------------------------------------------------------------------------
template<class T>
const DWF_Vector3<T>& DWF_Vector3<T>::operator *= (const T& value)
{
    m_X *= value;
    m_Y *= value;
    m_Z *= value;

    return *this;
}
//---------------------------------------------------------------------------
template<class T>
const DWF_Vector3<T>& DWF_Vector3<T>::operator /= (const DWF_Vector3& value)
{
    if (!value.m_X)
        throw new std::exception("Division by 0 error - invalid m_X value");

    if (!value.m_Y)
        throw new std::exception("Division by 0 error - invalid m_Y value");

    if (!value.m_Z)
        throw new std::exception("Division by 0 error - invalid m_Z value");

    m_X /= value.m_X;
    m_Y /= value.m_Y;
    m_Z /= value.m_Z;

    return *this;
}
//---------------------------------------------------------------------------
template<class T>
const DWF_Vector3<T>& DWF_Vector3<T>::operator /= (const T& value)
{
    if (!value)
        throw new std::exception("Division by 0 error - invalid value");

    m_X /= value;
    m_Y /= value;
    m_Z /= value;

    return *this;
}
//---------------------------------------------------------------------------
template<class T>
bool DWF_Vector3<T>::operator == (const DWF_Vector3& value) const
{
    return (m_X == value.m_X && m_Y == value.m_Y && m_Z == value.m_Z);
}
//---------------------------------------------------------------------------
template<class T>
bool DWF_Vector3<T>::operator !=(const DWF_Vector3& value) const
{
    return (m_X != value.m_X || m_Y != value.m_Y || m_Z != value.m_Z);
}
//---------------------------------------------------------------------------
template <class T>
T DWF_Vector3<T>::Length() const
{
    return T(sqrt((double(m_X) * double(m_X)) + (double(m_Y) * double(m_Y)) + (double(m_Z) * double(m_Z))));
}
//---------------------------------------------------------------------------
template <class T>
DWF_Vector3<T> DWF_Vector3<T>::Normalize() const
{
    // calculate vector length
    const T len = Length();

    // no vector length?
    if (!len)
        return DWF_Vector3();

    // normalize vector (thus values will always be between 0.0f, and 1.0f)
    return DWF_Vector3(m_X / len, m_Y / len, m_Z / len);
}
//---------------------------------------------------------------------------
template <class T>
DWF_Vector3<T> DWF_Vector3<T>::Cross(const DWF_Vector3& vector) const
{
    return DWF_Vector3((m_Y * vector.m_Z) - (vector.m_Y * m_Z),
                       (m_Z * vector.m_X) - (vector.m_Z * m_X),
                       (m_X * vector.m_Y) - (vector.m_X * m_Y));
}
//---------------------------------------------------------------------------
template <class T>
T DWF_Vector3<T>::Dot(const DWF_Vector3& vector) const
{
    return ((m_X * vector.m_X) + (m_Y * vector.m_Y) + (m_Z * vector.m_Z));
}
//---------------------------------------------------------------------------
