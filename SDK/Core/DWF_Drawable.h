/****************************************************************************
 * ==> DWF_Drawable --------------------------------------------------------*
 ****************************************************************************
 * Description:  Generic drawable object                                    *
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
#include "DWF_Matrix4x4.h"
#include "DWF_Shader.h"
#include "DWF_Renderer.h"

/**
* Generic drawable object
*@author Jean-Milost Reymond
*/
class DWF_Drawable : public DWF_Object
{
    public:
        DWF_Drawable();
        virtual ~DWF_Drawable();

        /**
        * Draw the object
        *@param renderer - renderer to use for drawing
        *@param matrix - matrix to apply to mesh
        *@param pShader - shader that will be used to draw the model
        */
        virtual void Draw(const DWF_Renderer& renderer, const DWF_Matrix4x4F& matrix, const DWF_Shader& shader) const = 0;
};
