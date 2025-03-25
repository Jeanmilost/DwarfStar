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

#include "DWF_Shader_Collection_OpenGL.h"

using namespace DWF_Renderer;

//---------------------------------------------------------------------------
// Shader_Collection_OpenGL
//---------------------------------------------------------------------------
Shader_Collection_OpenGL::Shader_Collection_OpenGL()
{}
//---------------------------------------------------------------------------
Shader_Collection_OpenGL::~Shader_Collection_OpenGL()
{}
//---------------------------------------------------------------------------
std::string Shader_Collection_OpenGL::GetVertexShader(IEShaderType type)
{
    switch (type)
    {
        case Shader_Collection_OpenGL::IEShaderType::IE_ST_Color:
            return "#version 130\n"
                   "precision mediump float;\n"
                   "attribute    vec3 dwf_aVertices;\n"
                   "attribute    vec4 dwf_aColor;\n"
                   "uniform      mat4 dwf_uProjection;\n"
                   "uniform      mat4 dwf_uView;\n"
                   "uniform      mat4 dwf_uModel;\n"
                   "varying lowp vec4 dwf_vColor;\n"
                   "void main(void)\n"
                   "{\n"
                   "    dwf_vColor  = dwf_aColor;\n"
                   "    gl_Position = dwf_uProjection * dwf_uView * dwf_uModel * vec4(dwf_aVertices, 1.0);\n"
                   "}";

        case Shader_Collection_OpenGL::IEShaderType::IE_ST_Texture:
            return "#version 130\n"
                   "precision mediump float;\n"
                   "attribute    vec3 dwf_aVertices;\n"
                   "attribute    vec4 dwf_aColor;\n"
                   "attribute    vec2 dwf_aTexCoord;\n"
                   "uniform      mat4 dwf_uProjection;\n"
                   "uniform      mat4 dwf_uView;\n"
                   "uniform      mat4 dwf_uModel;\n"
                   "varying lowp vec4 dwf_vColor;\n"
                   "varying      vec2 dwf_vTexCoord;\n"
                   "void main(void)\n"
                   "{\n"
                   "    dwf_vColor    = dwf_aColor;\n"
                   "    dwf_vTexCoord = dwf_aTexCoord;\n"
                   "    gl_Position   = dwf_uProjection * dwf_uView * dwf_uModel * vec4(dwf_aVertices, 1.0);\n"
                   "}";

        case Shader_Collection_OpenGL::IEShaderType::IE_ST_Texture_Normal:
            return "#version 130\n"
                   "precision mediump float;\n"
                   "attribute    vec3 dwf_aVertices;\n"
                   "attribute    vec3 dwf_aNormal;\n"
                   "attribute    vec4 dwf_aColor;\n"
                   "attribute    vec2 dwf_aTexCoord;\n"
                   "uniform      mat4 dwf_uProjection;\n"
                   "uniform      mat4 dwf_uView;\n"
                   "uniform      mat4 dwf_uModel;\n"
                   "varying lowp vec3 dwf_vNormal;\n"
                   "varying lowp vec4 dwf_vColor;\n"
                   "varying      vec2 dwf_vTexCoord;\n"
                   "void main(void)\n"
                   "{\n"
                   "    dwf_vNormal   = dwf_aNormal;\n"
                   "    dwf_vColor    = dwf_aColor;\n"
                   "    dwf_vTexCoord = dwf_aTexCoord;\n"
                   "    gl_Position   = dwf_uProjection * dwf_uView * dwf_uModel * vec4(dwf_aVertices, 1.0);\n"
                   "}";

        case Shader_Collection_OpenGL::IEShaderType::IE_ST_Skybox:
            return "#version 130\n"
                   "precision mediump float;\n"
                   "attribute vec3 dwf_aVertices;\n"
                   "uniform   mat4 dwf_uProjection;\n"
                   "uniform   mat4 dwf_uView;\n"
                   "varying   vec3 dwf_vTexCoord;\n"
                   "void main()\n"
                   "{\n"
                   "    dwf_vTexCoord = dwf_aVertices;\n"
                   "    gl_Position   = dwf_uProjection * dwf_uView * vec4(dwf_aVertices, 1.0);\n"
                   "}";

        case Shader_Collection_OpenGL::IEShaderType::IE_ST_Line:
            return "#version 130\n"
                   "precision mediump float;"
                   "attribute    vec3 dwf_aVertices;"
                   "attribute    vec4 dwf_aColor;"
                   "uniform      mat4 dwf_uProjection;"
                   "uniform      mat4 dwf_uView;"
                   "uniform      mat4 dwf_uModel;"
                   "varying lowp vec4 dwf_vColor;"
                   "void main(void)"
                   "{"
                   "    dwf_vColor  = dwf_aColor;"
                   "    gl_Position = dwf_uProjection * dwf_uView * dwf_uModel * vec4(dwf_aVertices, 1.0);"
                   "}";

        default:
            return std::string();
    }
}
//---------------------------------------------------------------------------
std::string Shader_Collection_OpenGL::GetFragmentShader(IEShaderType type)
{
    switch (type)
    {
        case Shader_Collection_OpenGL::IEShaderType::IE_ST_Color:
            return "#version 130\n"
                   "precision mediump float;\n"
                   "varying lowp vec4 dwf_vColor;\n"
                   "void main(void)\n"
                   "{\n"
                   "    gl_FragColor = dwf_vColor;\n"
                   "}";

        case Shader_Collection_OpenGL::IEShaderType::IE_ST_Texture:
            return "#version 130\n"
                   "precision mediump float;\n"
                   "uniform      sampler2D dwf_sTexture;\n"
                   "varying lowp vec4      dwf_vColor;\n"
                   "varying      vec2      dwf_vTexCoord;\n"
                   "void main(void)\n"
                   "{\n"
                   "    gl_FragColor = dwf_vColor * texture2D(dwf_sTexture, dwf_vTexCoord);\n"
                   "}";

        case Shader_Collection_OpenGL::IEShaderType::IE_ST_Texture_Normal:
            return "#version 130\n"
                   "precision mediump float;\n"
                   "uniform      sampler2D dwf_sTexture;\n"
                   "varying lowp vec3      dwf_vNormal;\n"
                   "varying lowp vec4      dwf_vColor;\n"
                   "varying      vec2      dwf_vTexCoord;\n"
                   "void main(void)\n"
                   "{\n"
                   "    gl_FragColor = dwf_vColor * texture2D(dwf_sTexture, dwf_vTexCoord);\n"
                   "}";

        case Shader_Collection_OpenGL::IEShaderType::IE_ST_Texture_Alpha_Cut:
            return "#version 130\n"
                   "precision mediump float;"
                   "uniform      sampler2D dwf_sTexture;"
                   "varying lowp vec4      dwf_vColor;"
                   "varying      vec2      dwf_vTexCoord;"
                   "void main(void)"
                   "{"
                   "    gl_FragColor = dwf_vColor * texture2D(dwf_sTexture, dwf_vTexCoord);"
                   ""
                   "    if (gl_FragColor.a < 0.5)"
                   "        discard;"
                   "}";

        case Shader_Collection_OpenGL::IEShaderType::IE_ST_Skybox:
            return "#version 330\n"
                   "precision mediump float;\n"
                   "uniform samplerCube dwf_sCubemap;\n"
                   "varying vec3        dwf_vTexCoord;\n"
                   "void main()\n"
                   "{\n"
                   "    gl_FragColor = texture(dwf_sCubemap, dwf_vTexCoord);\n"
                   "}";

        case Shader_Collection_OpenGL::IEShaderType::IE_ST_Line:
            return "#version 130\n"
                   "precision mediump float;"
                   "varying lowp vec4 dwf_vColor;"
                   "void main(void)"
                   "{"
                   "    gl_FragColor = dwf_vColor;"
                   "}";

        default:
            return std::string();
    }
}
//---------------------------------------------------------------------------
