/****************************************************************************
 * ==> DWF_Camera ----------------------------------------------------------*
 ****************************************************************************
 * Description:  Camera system                                              *
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

#include "DWF_Camera.h"

//---------------------------------------------------------------------------
// DWF_Camera
//---------------------------------------------------------------------------
DWF_Camera::DWF_Camera() :
    DWF_Object()
{}
//---------------------------------------------------------------------------
DWF_Camera::~DWF_Camera()
{}
//---------------------------------------------------------------------------
DWF_Matrix4x4F DWF_Camera::GetMatrix() const
{
    DWF_Matrix4x4F scaleMatrix;

    // build a scale matrix
    scaleMatrix.Scale(m_Factor);

    DWF_Vector3F   axis;
    DWF_Matrix4x4F rotateXMatrix;

    // build a rotation matrix on the x axis
    axis.m_X = 1.0f;
    axis.m_Y = 0.0f;
    axis.m_Z = 0.0f;
    rotateXMatrix.Rotate(m_xAngle, axis);

    DWF_Matrix4x4F rotateYMatrix;

    // build a rotation matrix on the y axis
    axis.m_X = 0.0f;
    axis.m_Y = 1.0f;
    axis.m_Z = 0.0f;
    rotateYMatrix.Rotate(m_yAngle, axis);

    DWF_Matrix4x4F rotateZMatrix;

    // build a rotation matrix on the z axis
    axis.m_X = 0.0f;
    axis.m_Y = 0.0f;
    axis.m_Z = 1.0f;
    rotateZMatrix.Rotate(m_zAngle, axis);

    DWF_Matrix4x4F translateMatrix;

    // build a translation matrix
    translateMatrix.Translate(m_Position);

    // build model matrix
    switch (m_MatCombType)
    {
        case DWF_Camera::IEMatCombType::IE_CT_Scale_Rotate_Translate:
        {
            const DWF_Matrix4x4F buildMatrix1 = scaleMatrix.Multiply(rotateXMatrix);
            const DWF_Matrix4x4F buildMatrix2 = buildMatrix1.Multiply(rotateYMatrix);
            const DWF_Matrix4x4F buildMatrix3 = buildMatrix2.Multiply(rotateZMatrix);
            return buildMatrix3.Multiply(translateMatrix);
        }

        case DWF_Camera::IEMatCombType::IE_CT_Scale_Translate_Rotate:
        {
            const DWF_Matrix4x4F buildMatrix1 = scaleMatrix.Multiply(translateMatrix);
            const DWF_Matrix4x4F buildMatrix2 = buildMatrix1.Multiply(rotateXMatrix);
            const DWF_Matrix4x4F buildMatrix3 = buildMatrix2.Multiply(rotateYMatrix);
            return buildMatrix3.Multiply(rotateZMatrix);
        }

        case DWF_Camera::IEMatCombType::IE_CT_Rotate_Translate_Scale:
        {
            const DWF_Matrix4x4F buildMatrix1 = rotateXMatrix.Multiply(rotateYMatrix);
            const DWF_Matrix4x4F buildMatrix2 = buildMatrix1.Multiply(rotateZMatrix);
            const DWF_Matrix4x4F buildMatrix3 = buildMatrix2.Multiply(translateMatrix);
            return buildMatrix3.Multiply(scaleMatrix);
        }

        case DWF_Camera::IEMatCombType::IE_CT_Rotate_Scale_Translate:
        {
            const DWF_Matrix4x4F buildMatrix1 = rotateXMatrix.Multiply(rotateYMatrix);
            const DWF_Matrix4x4F buildMatrix2 = buildMatrix1.Multiply(rotateZMatrix);
            const DWF_Matrix4x4F buildMatrix3 = buildMatrix2.Multiply(scaleMatrix);
            return buildMatrix3.Multiply(translateMatrix);
        }

        case DWF_Camera::IEMatCombType::IE_CT_Translate_Rotate_Scale:
        {
            const DWF_Matrix4x4F buildMatrix1 = translateMatrix.Multiply(rotateXMatrix);
            const DWF_Matrix4x4F buildMatrix2 = buildMatrix1.Multiply(rotateYMatrix);
            const DWF_Matrix4x4F buildMatrix3 = buildMatrix2.Multiply(rotateZMatrix);
            return buildMatrix3.Multiply(scaleMatrix);
        }

        case DWF_Camera::IEMatCombType::IE_CT_Translate_Scale_Rotate:
        {
            const DWF_Matrix4x4F buildMatrix1 = translateMatrix.Multiply(scaleMatrix);
            const DWF_Matrix4x4F buildMatrix2 = buildMatrix1.Multiply(rotateXMatrix);
            const DWF_Matrix4x4F buildMatrix3 = buildMatrix2.Multiply(rotateYMatrix);
            return buildMatrix3.Multiply(rotateZMatrix);
        }
    }

    return DWF_Matrix4x4F();
}
//---------------------------------------------------------------------------
