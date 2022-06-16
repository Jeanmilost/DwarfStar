/****************************************************************************
 * ==> TGlobalResources ----------------------------------------------------*
 ****************************************************************************
 * Description : This module provides the global resources for the          *
 *               geometric labo application                                 *
 * Developer   : Jean-Milost Reymond                                        *
 ****************************************************************************
 * MIT License - DwarfStar Engine                                           *
 *                                                                          *
 * Permission is hereby granted, free of charge, to any person obtaining a  *
 * copy of this software and associated documentation files (the            *
 * "Software"), to deal in the Software without restriction, including      *
 * without limitation the rights to use, copy, modify, merge, publish,      *
 * distribute, sublicense, and/or sell copies of the Software, and to       *
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

#pragma hdrstop
#include "TGlobalResources.h"

//---------------------------------------------------------------------------
// TGlobalResources
//---------------------------------------------------------------------------
const std::string TGlobalResources::m_ShaderVertexProgram   = "#version 150\r\n\
                                                               precision mediump float;\r\n\
                                                               in      vec3  dwf_in_pos;\r\n\
                                                               uniform vec4  dwf_in_color;\r\n\
                                                               uniform mat4  dwf_uniform_projection;\r\n\
                                                               uniform mat4  dwf_uniform_view;\r\n\
                                                               uniform mat4  dwf_uniform_model;\r\n\
                                                               out     vec4  dwf_fragment_color;\r\n\
                                                               void main()\r\n\
                                                               {\r\n\
                                                                   mat4 mScene        = dwf_uniform_projection * dwf_uniform_view * dwf_uniform_model;\r\n\
                                                                   dwf_fragment_color = dwf_in_color;\r\n\
                                                                   gl_Position        = mScene * vec4(dwf_in_pos, 1);\r\n\
                                                               }";
const std::string TGlobalResources::m_ShaderFragmentProgram = "#version 150\r\n\
                                                               precision mediump float;\r\n\
                                                               in vec4 dwf_fragment_color;\r\n\
                                                               void main()\r\n\
                                                               {\r\n\
                                                                   gl_FragColor = dwf_fragment_color;\r\n\
                                                               }";
//---------------------------------------------------------------------------
