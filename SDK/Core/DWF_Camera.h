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

#pragma once

// dwarfstar
#include "DWF_Object.h"
#include "DWF_Vector3.h"
#include "DWF_Matrix4x4.h"

/**
* Camera system
*@author Jean-Milost Reymond
*/
class DWF_Camera : public DWF_Object
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

        IEMatCombType m_MatCombType = DWF_Camera::IEMatCombType::IE_CT_Scale_Rotate_Translate;
        float         m_xAngle      = 0.0f;
        float         m_yAngle      = 0.0f;
        float         m_zAngle      = 0.0f;
        DWF_Vector3F  m_Factor      = DWF_Vector3F(1.0f, 1.0f, 1.0f);
        DWF_Vector3F  m_Position;

        DWF_Camera();
        virtual ~DWF_Camera();

        /**
        * Gets the camera matrix
        * @return the camera matrix
        */
        virtual DWF_Matrix4x4F GetMatrix() const;
};
