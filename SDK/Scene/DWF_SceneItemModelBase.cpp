/****************************************************************************
 * ==> DWF_SceneItemModelBase ----------------------------------------------*
 ****************************************************************************
 * Description : Scene item containing a base for a model                   *
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

#include "DWF_SceneItemModelBase.h"

using namespace DWF_Scene;

//---------------------------------------------------------------------------
// SceneItem_ModelBase
//---------------------------------------------------------------------------
SceneItem_ModelBase::SceneItem_ModelBase(const std::wstring& name) :
    SceneItem(name)
{}
//---------------------------------------------------------------------------
SceneItem_ModelBase::~SceneItem_ModelBase()
{}
//---------------------------------------------------------------------------
DWF_Math::Matrix4x4F SceneItem_ModelBase::BuildMatrix(const DWF_Math::Vector3F& pos,
                                                            float               roll,
                                                            float               pitch,
                                                            float               yaw,
                                                      const DWF_Math::Vector3F& scale) const
{
    DWF_Math::Matrix4x4F defMatrix = DWF_Math::Matrix4x4F::Identity();
    DWF_Math::Vector3F   axis;

    // set rotation axis
    axis.m_X = 1.0f;
    axis.m_Y = 0.0f;
    axis.m_Z = 0.0f;

    // create the rotation matrix
    DWF_Math::Matrix4x4F rotateXMatrix = defMatrix.Rotate(roll, axis);

    defMatrix = DWF_Math::Matrix4x4F::Identity();

    // set rotation axis
    axis.m_X = 0.0f;
    axis.m_Y = 1.0f;
    axis.m_Z = 0.0f;

    // create the rotation matrix
    DWF_Math::Matrix4x4F rotateYMatrix = defMatrix.Rotate(pitch, axis);

    defMatrix = DWF_Math::Matrix4x4F::Identity();

    // set rotation axis
    axis.m_X = 0.0f;
    axis.m_Y = 0.0f;
    axis.m_Z = 1.0f;

    // create the rotation matrix
    DWF_Math::Matrix4x4F rotateZMatrix = defMatrix.Rotate(yaw, axis);

    defMatrix = DWF_Math::Matrix4x4F::Identity();

    // create the scale matrix
    DWF_Math::Matrix4x4F scaleMatrix = defMatrix.Scale(scale);

    // build the model matrix
    DWF_Math::Matrix4x4F intermediateMatrix = scaleMatrix.Multiply(rotateXMatrix);
                         intermediateMatrix = intermediateMatrix.Multiply(rotateYMatrix);
    DWF_Math::Matrix4x4F matrix             = intermediateMatrix.Multiply(rotateZMatrix);

    // place it in the world
    matrix.m_Table[3][0] = pos.m_X;
    matrix.m_Table[3][1] = pos.m_Y;
    matrix.m_Table[3][2] = pos.m_Z;

    return matrix;
}
//---------------------------------------------------------------------------
