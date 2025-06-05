/****************************************************************************
 * ==> DWF_SceneItemStaticAsset --------------------------------------------*
 ****************************************************************************
 * Description : Scene item containing a static asset                       *
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

// std
#include <functional>
#include <vector>

// classes
#include "DWF_SceneItemModelBase.h"
#include "DWF_ModelFormat.h"
#include "DWF_Shader.h"
#include "DWF_Renderer.h"

#pragma once

namespace DWF_Scene
{
    /**
    * Scene item containing a static asset
    *@author Jean-Milost Reymond
    */
    class SceneItem_StaticAsset : public SceneItem_ModelBase
    {
        public:
            /**
            * Constructor
            *@param name - item name
            */
            SceneItem_StaticAsset(const std::wstring& name);

            virtual ~SceneItem_StaticAsset();

            /**
            * Sets the model to use
            *@param pModelFormat - the model to use
            */
            virtual inline void SetModel(const std::shared_ptr<DWF_Model::ModelFormat>& pModelFormat);

            /**
            * Renders the item
            *@param viewMatrix - view matrix to connect to shader
            *@param pRenderer - renderer to use to render the scene
            */
            virtual void Render(const DWF_Math::Matrix4x4F&   viewMatrix,
                                const DWF_Renderer::Renderer* pRenderer) const;

        private:
            std::shared_ptr<DWF_Model::ModelFormat> m_pModelFormat;

            /**
            * Draws a model
            *@param pModelFormat - model to draw
            *@param pShader - shader to use to draw the model
            *@param pRenderer - renderer to use to draw the model
            */
            void DrawModel(const DWF_Model::ModelFormat* pModelFormat,
                           const DWF_Renderer::Shader*   pShader,
                           const DWF_Renderer::Renderer* pRenderer) const;
    };

    //---------------------------------------------------------------------------
    // SceneItem_StaticAsset
    //---------------------------------------------------------------------------
    inline void SceneItem_StaticAsset::SetModel(const std::shared_ptr<DWF_Model::ModelFormat>& pModelFormat)
    {
        m_pModelFormat = pModelFormat;
    }
    //---------------------------------------------------------------------------
}
