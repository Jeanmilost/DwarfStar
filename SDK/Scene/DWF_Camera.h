/****************************************************************************
 * ==> DWF_Camera ----------------------------------------------------------*
 ****************************************************************************
 * Description : Camera (or point of view)                                  *
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

// classes
#include "DWF_Vector3.h"
#include "DWF_Matrix4x4.h"
#include "DWF_PointOfView.h"

#pragma once

namespace DWF_Scene
{
    /**
    * Camera (or point of view)
    *@author Jean-Milost Reymond
    */
    class Camera : public PointOfView
    {
        public:
            /**
            * Matrix combination type
            */
            enum class IEMatCombType
            {
                IE_CT_Scale_Rotate_Translate,
                IE_CT_Scale_Translate_Rotate,
                IE_CT_Rotate_Translate_Scale,
                IE_CT_Rotate_Scale_Translate,
                IE_CT_Translate_Rotate_Scale,
                IE_CT_Translate_Scale_Rotate
            };

            IEMatCombType      m_MatCombType = IEMatCombType::IE_CT_Scale_Translate_Rotate;
            float              m_AngleX      = 0.0f;
            float              m_AngleY      = 0.0f;
            float              m_AngleZ      = 0.0f;
            DWF_Math::Vector3F m_Position;
            DWF_Math::Vector3F m_Factor;

            Camera();
            virtual ~Camera();

            /**
            * Gets the camera transformation matrix
            *@return the camera transformation matrix
            */
            virtual DWF_Math::Matrix4x4F ToMatrix() const;
    };
}