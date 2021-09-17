/****************************************************************************
 * ==> DWF_Matrix3x3 -------------------------------------------------------*
 ****************************************************************************
 * Description:  3x3 matrix                                                 *
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
#include <memory>
#include <cmath>

// dwarfstar
#include "DWF_Object.h"
#include "DWF_Vector2.h"

/**
* 3x3 matrix
*@author Jean-Milost Reymond
*/
template <class T>
class DWF_Matrix3x3 : public DWF_Object
{
    public:
        T m_Table[3][3]; // 3x3 matrix array

        /**
        * Constructor
        */
        inline DWF_Matrix3x3();

        /**
        * Constructor
        *@param _11 - matrix value
        *@param _12 - matrix value
        *@param _13 - matrix value
        *@param _21 - matrix value
        *@param _22 - matrix value
        *@param _23 - matrix value
        *@param _31 - matrix value
        *@param _32 - matrix value
        *@param _33 - matrix value
        */
        inline DWF_Matrix3x3(T _11, T _12, T _13,
                             T _21, T _22, T _23,
                             T _31, T _32, T _33);

        /**
        * Copy constructor
        *@param other - other matrix to copy from
        */
        inline DWF_Matrix3x3(const DWF_Matrix3x3& other);

        /**
        * Destructor
        */
        virtual inline ~DWF_Matrix3x3();

        /**
        * Assignation operator
        *@param other - other matrix to copy from
        */
        virtual inline DWF_Matrix3x3& operator = (const DWF_Matrix3x3& other);

        /**
        * Equality operator
        *@param other - other matrix to compare
        *@return true if both matrix are equals, otherwise false
        */
        virtual inline bool operator == (const DWF_Matrix3x3& other);

        /**
        * Not equality operator
        *@param other - other matrix to compare
        *@return true if both matrix are not equals, otherwise false
        */
        virtual inline bool operator != (const DWF_Matrix3x3& other);

        /**
        * Copies matrix from another
        *@param other - other matrix to copy from
        */
        virtual inline void Copy(const DWF_Matrix3x3& other);

        /**
        * Checks if matrix and other matrix are equals
        *@param other - other matrix to compare
        *@return true if matrix are equals, otherwise false
        */
        virtual inline bool IsEqual(const DWF_Matrix3x3& other) const;

        /**
        * Checks if matrix is an identity matrix
        *@return true if matrix is an identity matrix, otherwise false
        */
        virtual inline bool IsIdentity() const;

        /**
        * Gets an identity matrix
        *@return identity matrix
        */
        static DWF_Matrix3x3 Identity();

        /**
        * Inverses a matrix
        *@param[out] determinant - matrix determinant
        */
        virtual inline DWF_Matrix3x3 Inverse(float& determinant);

        /**
        * Transposes a matrix
        *@return transposed matrix
        */
        virtual inline DWF_Matrix3x3 Transpose() const;

        /**
        * Multiplies matrix by another matrix
        *@param other - other matrix to multiply with
        *@return multiplied resulting matrix
        */
        virtual inline DWF_Matrix3x3 Multiply(const DWF_Matrix3x3<T>& other) const;

        /**
        * Translates matrix
        *@param t - translation vector
        *@return copy of translated matrix
        */
        virtual inline DWF_Matrix3x3 Translate(const DWF_Vector2<T>& t);

        /**
        * Rotates matrix
        *@param angle - rotation angle in radians
        *@param r - rotation direction (e.g. {0.0f, 0.0f, 1.0f} for a z-axis rotation)
        *@return copy of rotated matrix
        *@note rotation direction vector should be normalized before calling
        *      this function
        */
        virtual inline DWF_Matrix3x3 Rotate(T angle, const DWF_Vector2<T>& r);

        /**
        * Rotates matrix based on a rotation center point
        *@param angle - rotation angle in radians
        *@param center - rotation center point
        *@return copy of rotated matrix
        */
        virtual inline DWF_Matrix3x3 RotateCenter(T angle, const DWF_Vector2<T>& center);

        /**
        * Scales matrix
        *@param s - scale vector
        *@return copy of scaled matrix
        */
        virtual inline DWF_Matrix3x3 Scale(const DWF_Vector2<T>& s);

        /**
        * Applies a transformation matrix to a vector
        *@param vector - vector to transform
        *@return transformed vector
        */
        virtual inline DWF_Vector2<T> Transform(const DWF_Vector2<T>& vector) const;

        /**
        * Gets table pointer
        *@return pointer
        */
        virtual inline const T* GetPtr() const;
};

typedef DWF_Matrix3x3<float>  DWF_Matrix3x3F;
typedef DWF_Matrix3x3<double> DWF_Matrix3x3D;

//---------------------------------------------------------------------------
// DWF_Matrix3x3
//---------------------------------------------------------------------------
template <class T>
DWF_Matrix3x3<T>::DWF_Matrix3x3() :
    DWF_Object()
{
    // initialize matrix table
    Copy(Identity());
}
//---------------------------------------------------------------------------
template <class T>
DWF_Matrix3x3<T>::DWF_Matrix3x3(T _11, T _12, T _13,
                                T _21, T _22, T _23,
                                T _31, T _32, T _33) :
    DWF_Object()
{
    m_Table[0][0] = _11; m_Table[1][0] = _12; m_Table[2][0] = _13;
    m_Table[0][1] = _21; m_Table[1][1] = _22; m_Table[2][1] = _23;
    m_Table[0][2] = _31; m_Table[1][2] = _32; m_Table[2][2] = _33;
}
//---------------------------------------------------------------------------
template <class T>
DWF_Matrix3x3<T>::DWF_Matrix3x3(const DWF_Matrix3x3& other) :
    DWF_Object()
{
    Copy(other);
}
//---------------------------------------------------------------------------
template <class T>
DWF_Matrix3x3<T>::~DWF_Matrix3x3()
{}
//---------------------------------------------------------------------------
template <class T>
DWF_Matrix3x3<T>& DWF_Matrix3x3<T>::operator = (const DWF_Matrix3x3& other)
{
    Copy(other);
    return *this;
}
//---------------------------------------------------------------------------
template <class T>
bool DWF_Matrix3x3<T>::operator == (const DWF_Matrix3x3& other)
{
    return IsEqual(other);
}
//---------------------------------------------------------------------------
template <class T>
bool DWF_Matrix3x3<T>::operator != (const DWF_Matrix3x3& other)
{
    return !IsEqual(other);
}
//---------------------------------------------------------------------------
template <class T>
void DWF_Matrix3x3<T>::Copy(const DWF_Matrix3x3& other)
{
    // copy matrix table from other
    std::memcpy(m_Table, other.m_Table, sizeof(m_Table));
}
//---------------------------------------------------------------------------
template <class T>
bool DWF_Matrix3x3<T>::IsEqual(const DWF_Matrix3x3& other) const
{
    // compare each matrix element with other matrix. NOTE don't use std::memcmp here because the
    // comparison will fail in the following cases:
    // 1. if 0.0f == -0.0f, the equality operator will return true whereas the memory cmp will fail
    // 2. if NaN, the memory compare will always fail
    for (std::size_t i = 0; i < 3; ++i)
        for (std::size_t j = 0; j < 3; ++j)
            if (m_Table[i][j] != other.m_Table[i][j])
                return false;

    return true;
}
//---------------------------------------------------------------------------
template <class T>
bool DWF_Matrix3x3<T>::IsIdentity() const
{
    return IsEqual(Identity());
}
//---------------------------------------------------------------------------
template <class T>
DWF_Matrix3x3<T> DWF_Matrix3x3<T>::Identity()
{
    return DWF_Matrix3x3(T(1.0), T(0.0), T(0.0),
                         T(0.0), T(1.0), T(0.0),
                         T(0.0), T(0.0), T(1.0));
}
//---------------------------------------------------------------------------
template <class T>
DWF_Matrix3x3<T> DWF_Matrix3x3<T>::Inverse(float& determinant)
{
    T                determinant = T(0.0);
    DWF_Matrix3x3<T> result;

    for (std::size_t i = 0; i < 3; ++i)
        determinant = determinant + (m_Table[0][i] * (m_Table[1][(i + 1) % 3] * m_Table[2][(i + 2) % 3] -
                                                      m_Table[1][(i + 2) % 3] * m_Table[2][(i + 1) % 3]));

    for (std::size_t i = 0; i < 3; ++i)
        for (std::size_t j = 0; j < 3; ++j)
            result.m_Table[i][j] = ((m_Table[(i + 1) % 3][(j + 1) % 3] * m_Table[(i + 2) % 3][(j + 2) % 3]) -
                                    (m_Table[(i + 1) % 3][(j + 2) % 3] * m_Table[(i + 2) % 3][(j + 1) % 3])) / determinant;

    return result;
}
//---------------------------------------------------------------------------
template <class T>
DWF_Matrix3x3<T> DWF_Matrix3x3<T>::Transpose() const
{
    DWF_Matrix3x3 result;

    for (std::size_t i = 0; i < 3; ++i)
        for (std::size_t j = 0; j < 3; ++j)
            result.m_Table[j][i] = m_Table[i][j];

    return result;
}
//---------------------------------------------------------------------------
template <class T>
DWF_Matrix3x3<T> DWF_Matrix3x3<T>::Multiply(const DWF_Matrix3x3<T>& other) const
{
    DWF_Matrix3x3<T> matrix;

    for (std::size_t i = 0; i < 3; ++i)
        for (std::size_t j = 0; j < 3; ++j)
            matrix.m_Table[i][j] = m_Table[i][0] * other.m_Table[0][j] +
                                   m_Table[i][1] * other.m_Table[1][j] +
                                   m_Table[i][2] * other.m_Table[2][j];

    return matrix;
}
//---------------------------------------------------------------------------
template <class T>
DWF_Matrix3x3<T> DWF_Matrix3x3<T>::Translate(const DWF_Vector2<T>& t)
{
    m_Table[2][0] += m_Table[0][0] * t.m_X + m_Table[1][0] * t.m_Y;
    m_Table[2][1] += m_Table[0][1] * t.m_X + m_Table[1][1] * t.m_Y;
    m_Table[2][2] += m_Table[0][2] * t.m_X + m_Table[1][2] * t.m_Y;

    return *this;
}
//---------------------------------------------------------------------------
template <class T>
DWF_Matrix3x3<T> DWF_Matrix3x3<T>::Rotate(T angle, const DWF_Vector2<T>& r)
{
    // calculate sinus and cosinus values
    const T c = std::cos(angle);
    const T s = std::sin(angle);

    // create rotation matrix
    DWF_Matrix3x3<T> matrix = Identity();
    matrix.m_Table[0][0]    = c * r.m_X; matrix.m_Table[1][0] = -s * r.m_Y;
    matrix.m_Table[0][1]    = s * r.m_X; matrix.m_Table[1][1] = c * r.m_Y;

    // combine current matrix with rotation matrix
    *this = matrix.Multiply(*this);

    return *this;
}
//------------------------------------------------------------------------------
template <class T>
DWF_Matrix3x3<T> DWF_Matrix3x3<T>::RotateCenter(T angle, const DWF_Vector2<T>& center)
{
    const T c = std::cos(angle);
    const T s = std::sin(angle);

    // create rotation matrix
    DWF_Matrix3x3 matrix;
    matrix.SetIdentity();

    // equivalent to translate(center) * rotate(angle) * translate(-center)
    matrix.m_Table[0][0] = c; matrix.m_Table[1][0] = -s; matrix.m_Table[2][0] = center.m_X - center.m_X * c + center.m_Y * s;
    matrix.m_Table[0][1] = s; matrix.m_Table[1][1] =  c; matrix.m_Table[2][1] = center.m_Y - center.m_X * s - center.m_Y * c;

    // combine current matrix with rotation matrix
    *this = matrix.Multiply(*this);

    return *this;
}
//---------------------------------------------------------------------------
template <class T>
DWF_Matrix3x3<T> DWF_Matrix3x3<T>::Scale(const DWF_Vector2<T>& s)
{
    m_Table[0][0] *= s.m_X; m_Table[1][0] *= s.m_Y;
    m_Table[0][1] *= s.m_X; m_Table[1][1] *= s.m_Y;
    m_Table[0][2] *= s.m_X; m_Table[1][2] *= s.m_Y;

    return *this;
}
//---------------------------------------------------------------------------
template <class T>
DWF_Vector2<T> DWF_Matrix3x3<T>::Transform(const DWF_Vector2<T>& vector) const
{
    // calculates x and y coordinates and returns transformed vector
    return DWF_Vector2<T>((vector.m_X * m_Table[0][0] + vector.m_Y * m_Table[1][0] + m_Table[2][0]),
                          (vector.m_X * m_Table[0][1] + vector.m_Y * m_Table[1][1] + m_Table[2][1]));
}
//---------------------------------------------------------------------------
template <class T>
const T* DWF_Matrix3x3<T>::GetPtr() const
{
    return &m_Table[0][0];
}
//---------------------------------------------------------------------------
