/****************************************************************************
 * ==> DWF_Renderer_OpenGL -------------------------------------------------*
 ****************************************************************************
 * Description: OpenGL renderer                                             *
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

// classes
#include "DWF_Renderer.h"

// windows
#include <Windows.h>

// openGL
#define GLEW_STATIC
#include <GL/glew.h>
#include <gl/gl.h>

namespace DWF_Renderer
{
    /**
    * Renderer based on the OpenGL library
    *@author Jean-Milost Reymond
    */
    class Renderer_OpenGL : public Renderer
    {
        public:
            Renderer_OpenGL();
            virtual ~Renderer_OpenGL();

            /**
            * Enables OpenGL
            *@param hWnd - control or form handle on which OpenGL scene will be drawn
            *@return true on success, otherwise false
            */
            virtual bool EnableOpenGL(HWND hWnd);

            /**
            * Disables OpenGL and clears memory
            *@param hWnd - control or form handle on which OpenGL scene was drawn
            */
            virtual void DisableOpenGL(HWND hWnd);

            /**
            * Creates OpenGL viewport
            *@param width - viewport width
            *@param height - viewport height
            *@param zNear - viewport near clipping
            *@param zFar - viewport far clipping
            *@param[out] matrix - the projection matrix matching with viewport
            */
            virtual void CreateViewport(float                       w,
                                        float                       h,
                                        float                       zNear,
                                        float                       zFar,
                                        const Shader*               pShader,
                                              DWF_Math::Matrix4x4F& matrix) const;

            /**
            * Begins a scene
            *@param color - scene background color
            *@param flags - scene flags
            */
            virtual void BeginScene(const DWF_Model::ColorF& color, IESceneFlags flags) const;

            /**
            * Ends a scene
            */
            virtual void EndScene() const;

            /**
            * Selects the current OpenGL context
            *@return true on success, otherwise false
            */
            virtual bool SelectContext() const;

            /**
            * Generates a texture
            *@return texture
            */
            virtual DWF_Model::Texture* GenerateTexture() const;

            /**
            * Generates a shader
            *@return texture
            */
            virtual Shader* GenerateShader() const;

            /**
            * Connects the projection matrix to the shader
            *@param pShader - shader to connect to
            *@param projectionMatrix - projection matrix
            */
            virtual void ConnectProjectionMatrixToShader(const Shader*               pShader,
                                                         const DWF_Math::Matrix4x4F& projectionMatrix) const;

            /**
            * Connects the view matrix to the shader
            *@param pShader - shader to connect to
            *@param viewMatrix - view matrix
            */
            virtual void ConnectViewMatrixToShader(const Shader*               pShader,
                                                   const DWF_Math::Matrix4x4F& viewMatrix) const;

            /**
            * Sets the projection matrix
            *@param pShader - shader to connect to
            *@param projectionMatrix - projection matrix
            */
            virtual void SetProjectionMatrix(const Shader*               pShader,
                                             const DWF_Math::Matrix4x4F& projectionMatrix) const;

            /**
            * Sets the view matrix
            *@param pShader - shader to connect to
            *@param viewMatrix - view matrix
            */
            virtual void SetViewMatrix(const Shader*               pShader,
                                       const DWF_Math::Matrix4x4F& viewMatrix) const;

            /**
            * Draws a mesh using OpenGL and shader
            *@param mesh - mesh to draw
            *@param modelMatrix - model matrix to apply to mesh
            *@param pShader - shader that will be used to draw the model
            *@param ignoreDepthTest - if true, the depth test status will be ignored (meaning that the caller is responsible of it)
            *@return true on success, otherwise false
            */
            virtual bool Draw(const DWF_Model::Mesh&      mesh,
                              const DWF_Math::Matrix4x4F& modelMatrix,
                              const Shader*               pShader,
                                    bool                  ignoreDepthTest) const;

            /**
            * Draws a mesh using OpenGL and shader
            *@param mesh - mesh to draw
            *@param modelMatrix - model matrix to apply to mesh
            *@param pShader - shader that will be used to draw the model
            *@param disableDepthTestOnTransparency - if true, depth test will be disabled on transparency
            *@param ignoreDepthTest - if true, the depth test status will be ignored (meaning that the caller is responsible of it)
            *@return true on success, otherwise false
            */
            virtual bool Draw(const DWF_Model::Mesh&      mesh,
                              const DWF_Math::Matrix4x4F& modelMatrix,
                              const Shader*               pShader,
                                    bool                  disableDepthTestOnTransparency,
                                    bool                  ignoreDepthTest) const;

            /**
            * Draws a line
            *@param start - start line position
            *@param end - end line position
            *@param startColor - line start color
            *@param endColor - line start color
            *@param modelMatrix - model matrix that will be used to draw the line
            *@param pShader - shader that will be used to draw the line
            *@param width - line width
            *@param smooth - if true, smoothing mode will be enabled for this line
            *@return true on success, otherwise false
            */
            virtual void DrawLine(const DWF_Math::Vector3F&   start,
                                  const DWF_Math::Vector3F&   end,
                                  const DWF_Model::ColorF&    startColor,
                                  const DWF_Model::ColorF&    endColor,
                                  const DWF_Math::Matrix4x4F& modelMatrix,
                                  const Shader*               pShader,
                                        float                 width  = 1.0f,
                                        bool                  smooth = true) const;

            /**
            * Draws a skybox
            *@param mesh - mesh containing the geometry to use to draw the skybox
            *@param viewMatrix - view matrix
            *@param pShader - shader to use to draw the skybox
            */
            virtual void DrawSkybox(const DWF_Model::Mesh&      mesh,
                                    const DWF_Math::Matrix4x4F& viewMatrix,
                                    const Shader*               pShader) const;

            /**
            * Selects texture to draw
            *@param pShader - shader that will draw the texture
            *@param pTexture - the texture to select
            */
            virtual void SelectTexture(const Shader* pShader, const DWF_Model::Texture* pTexture) const;

            /**
            * Enables or disables the depth test
            *@param value - if true, the depth test will be enabled
            */
            virtual void EnableDepthTest(bool value) const;

            /**
            * Gets shader uniform handle
            *@param pShader - shader containing uniform to get
            *@param attribute - uniform attribute to get from shader
            *@return uniform handle, -1 if not found or on error
            */
            static GLint GetUniform(const Shader* pShader, Shader::IEAttribute attribute);

            /**
            * Gets shader attribute
            *@param pShader - shader containing attribute to get
            *@param attribute - attribute to get from shader
            *@return uniform handle, -1 if not found or on error
            */
            static GLint GetAttribute(const Shader* pShader, Shader::IEAttribute attribute);

        private:
            HDC   m_hDC;
            HGLRC m_hRC;
    };
}