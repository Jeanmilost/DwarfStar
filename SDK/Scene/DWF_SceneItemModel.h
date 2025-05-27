/****************************************************************************
 * ==> DWF_SceneItemModel --------------------------------------------------*
 ****************************************************************************
 * Description : Scene item containing a model                              *
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
#include <vector>

// classes
#include "DWF_SceneItemModelBase.h"
#include "DWF_Model.h"
#include "DWF_Shader.h"

#pragma once

namespace DWF_Scene
{
    /**
    * Scene item containing a model
    *@author Jean-Milost Reymond
    */
    class SceneItem_Model : public SceneItem_ModelBase
    {
        public:
            /**
            * Constructor
            *@param name - item name
            */
            SceneItem_Model(const std::wstring& name);

            virtual ~SceneItem_Model();

            /**
            * Gets the model
            *@return the model
            */
            virtual inline DWF_Model::Model* GetModel() const;

            /**
            * Sets the model
            *@param pModel - the model to set
            *@note Don't delete the model from outside, it will be deleted internally
            */
            virtual inline void SetModel(const std::shared_ptr<DWF_Model::Model>& pModel);

            /**
            * Gets the shader to use to render the model
            *@return the shader to use to render the model
            */
            virtual inline DWF_Renderer::Shader* GetShader() const;

            /**
            * Sets the shader to use to render the model
            *@param pShader - the shader to use to render the model
            *@??? Don't delete the model from outside, it will be deleted internally
            */
            virtual inline void SetShader(DWF_Renderer::Shader* pShader);

            /**
            * Renders the item
            *@param viewMatrix - view matrix to connect to shader
            *@param pRenderer - renderer to use to render the scene
            */
            virtual void Render(const DWF_Math::Matrix4x4F&   viewMatrix,
                                const DWF_Renderer::Renderer* pRenderer) const;

        private:
            std::shared_ptr<DWF_Model::Model> m_pModel;
            DWF_Renderer::Shader*             m_pShader       = nullptr;
            bool                              m_ShaderIsLocal = false;
    };

    //---------------------------------------------------------------------------
    // SceneItem_Model
    //---------------------------------------------------------------------------
    inline DWF_Model::Model* SceneItem_Model::GetModel() const
    {
        return m_pModel.get();
    }
    //---------------------------------------------------------------------------
    inline void SceneItem_Model::SetModel(const std::shared_ptr<DWF_Model::Model>& pModel)
    {
        m_pModel = pModel;
    }
    //---------------------------------------------------------------------------
    inline DWF_Renderer::Shader* SceneItem_Model::GetShader() const
    {
        return m_pShader;
    }
    //---------------------------------------------------------------------------
    inline void SceneItem_Model::SetShader(DWF_Renderer::Shader* pShader)
    {
        m_pShader = pShader;
    }
    //---------------------------------------------------------------------------
}
