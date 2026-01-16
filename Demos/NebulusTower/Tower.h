/****************************************************************************
 * ==> Tower ---------------------------------------------------------------*
 ****************************************************************************
 * Description : Nebulus tower                                              *
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

#pragma once

// std
#include <string.h>

// classes
#include "DWF_Texture_OpenGL.h"

// demo
#include "Item.h"

namespace Nebulus
{
    /**
    * Tower
    *@author Jean-Milost Reymond
    */
    class Tower : public Item
    {
        public:
            /**
            * Called when a texture loader function should be attached to the tower model
            *@param arg1 - the model for which the texture function should be attached
            */
            typedef std::function<void(std::shared_ptr<DWF_Model::Model>&)> ITfOnAttachTextureFunction;

            /**
            * Constructor
            *@param pScene - the current scene with which this item is linked
            */
            Tower(DWF_Scene::Scene* pScene);

            virtual ~Tower();

            /**
            * Loads the tower texture
            *@param fileName - texture file name
            *@param is32bit - if true, the texture is a 32 bit texture
            */
            virtual DWF_Model::Texture_OpenGL* LoadTexture(const std::string& fileName, bool is32bit) const;

            /**
            * Loads the tower and adds it to the scene
            *@param pShader - shader to use to draw the tower
            *@returns true on success, otherwise false
            */
            virtual bool Load(const std::shared_ptr<DWF_Renderer::Shader>& pShader);

            /**
            * Sets OnAttachTextureFunction function
            *@param fHandler - function handler
            */
            virtual void Set_OnAttachTextureFunction(ITfOnAttachTextureFunction fHandler);

        private:
            float                      m_X                        = 0.0f;
            float                      m_Y                        = 4.0f;
            float                      m_Z                        = 0.0f;
            ITfOnAttachTextureFunction m_fOnAttachTextureFunction = nullptr;
    };
}
