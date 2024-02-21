/****************************************************************************
 * ==> DWF_Arcball ---------------------------------------------------------*
 ****************************************************************************
 * Description : Arcball for camera                                         *
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

#include "DWF_Arcball.h"

 // visual studio specific code
#ifdef _MSC_VER
    // std
    #define _USE_MATH_DEFINES
    #include <math.h>
#endif

 // classes
#include "DWF_Camera.h"

using namespace DWF_Scene;

//---------------------------------------------------------------------------
// Arcball
//---------------------------------------------------------------------------
Arcball::Arcball() :
    PointOfView()
{}
//---------------------------------------------------------------------------
Arcball::~Arcball()
{}
//------------------------------------------------------------------------------
void Arcball::SetAngleX(float value)
{
    #ifdef __CODEGEARC__
        m_AngleX = fmodf(value, (float)M_PI * 2.0f);
    #else
        m_AngleX = std::fmodf(value, (float)M_PI * 2.0f);
    #endif
}
//------------------------------------------------------------------------------
void Arcball::SetAngleY(float value)
{
    #ifdef __CODEGEARC__
        m_AngleY = fmodf(value, (float)M_PI * 2.0f);
    #else
        m_AngleY = std::fmodf(value, (float)M_PI * 2.0f);
    #endif
}
//------------------------------------------------------------------------------
DWF_Math::Matrix4x4F Arcball::ToMatrix() const
{
    // are angles out of bounds?
    #ifdef __CODEGEARC__
        const float angleX = fmod(m_AngleX, (float)(M_PI * 2.0));
        const float angleY = fmod(m_AngleY, (float)(M_PI * 2.0));
    #else
        const float angleX = std::fmodf(m_AngleX, (float)(M_PI * 2.0));
        const float angleY = std::fmodf(m_AngleY, (float)(M_PI * 2.0));
    #endif

    DWF_Math::Matrix4x4F defMatrix = DWF_Math::Matrix4x4F::Identity();
    DWF_Math::Vector3F   axis;

    axis.m_X = 1.0f;
    axis.m_Y = 0.0f;
    axis.m_Z = 0.0f;

    // create a matrix for the rotation on the X axis
    const DWF_Math::Matrix4x4F cameraMatrixX = defMatrix.Rotate(angleX, axis);

    defMatrix = DWF_Math::Matrix4x4F::Identity();
    axis.m_X  = 0.0f;
    axis.m_Y  = 1.0f;
    axis.m_Z  = 0.0f;

    // create a matrix for the rotation on the Y axis
    const DWF_Math::Matrix4x4F cameraMatrixY = defMatrix.Rotate(angleY, axis);

    // combine the rotation matrices
    const DWF_Math::Matrix4x4F cameraMatrixXY = cameraMatrixY.Multiply(cameraMatrixX);

    defMatrix = DWF_Math::Matrix4x4F::Identity();

    const DWF_Math::Matrix4x4F cameraPos = defMatrix.Translate(m_Position);

    Camera camera;

    // configure the camera
    camera.m_Position.m_X =  0.0f;
    camera.m_Position.m_Y =  0.0f;
    camera.m_Position.m_Z = -m_Radius;
    camera.m_AngleX       =  0.0f;
    camera.m_AngleY       =  0.0f;
    camera.m_AngleZ       =  0.0f;
    camera.m_Factor.m_X   =  1.0f;
    camera.m_Factor.m_Y   =  1.0f;
    camera.m_Factor.m_Z   =  1.0f;
    camera.m_MatCombType  =  Camera::IEMatCombType::IE_CT_Scale_Rotate_Translate;

    // build the camera
    const DWF_Math::Matrix4x4F cameraMatrix = camera.ToMatrix();
    return cameraPos.Multiply(cameraMatrixXY.Multiply(cameraMatrix));
}
//---------------------------------------------------------------------------
