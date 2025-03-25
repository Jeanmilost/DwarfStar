/****************************************************************************
 * ==> DWF_Shader_Collection_OpenGL ----------------------------------------*
 ****************************************************************************
 * Description: OpenGL ready-to-use shader collection                       *
 * Developer:   Jean-Milost Reymond                                         *
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

#pragma once

// std
#include <string>

namespace DWF_Renderer
{
    /**
    * OpenGL ready-to-use shader collection
    *@author Jean-Milost Reymond
    */
    class Shader_Collection_OpenGL
    {
        public:
            /**
            * Shader type
            */
            enum class IEShaderType
            {
                IE_ST_Color,
                IE_ST_Texture,
                IE_ST_Texture_Normal,
                IE_ST_Texture_Alpha_Cut,
                IE_ST_Skybox,
                IE_ST_Line
            };

            Shader_Collection_OpenGL();
            virtual ~Shader_Collection_OpenGL();

            /**
            * Gets a vertex shader
            *@param type - shader type to get
            *@return the vertex shader
            */
            static std::string GetVertexShader(IEShaderType type);

            /**
            * Gets a fragment shader
            *@param type - shader type to get
            *@return the fragment shader
            */
            static std::string GetFragmentShader(IEShaderType type);
    };
}
