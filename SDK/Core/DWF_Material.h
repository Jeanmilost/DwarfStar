/****************************************************************************
 * ==> DWF_Material --------------------------------------------------------*
 ****************************************************************************
 * Description:  Material                                                   *
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
#include "DWF_Color.h"
#include "DWF_Texture.h"

/**
* Material, describes the way a vertex buffer draws its content
*@author Jean-Milost Reymond
*/
class DWF_Material : public DWF_Object
{
    public:
        DWF_ColorF   m_Color       = DWF_ColorF(1.0f, 1.0f, 1.0f, 1.0f); // vertex color, applied to all vertices if per-vertex color is disabled
        DWF_Texture* m_pTexture    = nullptr;                            // texture to apply to vertex buffer
        bool         m_Transparent = false;                              // whether or not the alpha blending should be activated
        bool         m_Wireframe   = false;                              // whether or not the vertex buffer should be drawn in wire frame

        DWF_Material();
        virtual ~DWF_Material();
};
