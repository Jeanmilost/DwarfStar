/****************************************************************************
 * ==> Player --------------------------------------------------------------*
 ****************************************************************************
 * Description : Nebulus player                                             *
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
#include "DWF_IQM.h"
#include "DWF_Scene.h"
#include "DWF_SceneItemAnimAsset.h"

// demo
#include "Item.h"

namespace Nebulus
{
    /**
    * Player character
    *@author Jean-Milost Reymond
    */
    class Player : public Item
    {
        public:
            /**
            * Called when a texture loader function should be attached to the player model
            *@param arg1 - the model for which the texture function should be attached
            */
            typedef std::function<void(std::shared_ptr<DWF_Model::IQM>&)> ITfOnAttachTextureFunction;

            /**
            * Constructor
            *@param pScene - the current scene with which this item is linked
            */
            Player(DWF_Scene::Scene* pScene);

            virtual ~Player();

            /**
            * Loads the player texture
            *@param fileName - texture file name
            *@param is32bit - if true, the texture is a 32 bit texture
            */
            virtual DWF_Model::Texture_OpenGL* LoadTexture(const std::string& fileName, bool is32bit) const;

            /**
            * Loads the player and adds it to the scene
            *@param pModelShader - shader to use to draw the model
            *@param pColliderShader - shader to use to draw the model collider
            *@returns true on success, otherwise false
            */
            virtual bool Load(const std::shared_ptr<DWF_Renderer::Shader>& pModelShader,
                              const std::shared_ptr<DWF_Renderer::Shader>& pColliderShader);

            /**
            * Animates the player
            *@param pScene - scene containing the water
            *@param elapsedTime - elapsed time in milliseconds since the last frame
            */
            virtual void Animate(const DWF_Scene::Scene* pScene, double elapsedTime);

            /**
            * Applies the collision on player
            *@param pScene - the scene in which the collision happened
            *@param pItem1 - first item in collision
            *@param pCollider1 - collider belonging to the first item
            *@param pItem2 - second item in collision
            *@param pCollider2 - collider belonging to the second item
            *@param mtv - minimum translation vector resulting from the collision
            */
            virtual void ApplyCollision(const DWF_Scene::Scene*       pScene,
                                              DWF_Scene::SceneItem*   pItem1,
                                              DWF_Collider::Collider* pCollider1,
                                              DWF_Scene::SceneItem*   pItem2,
                                              DWF_Collider::Collider* pCollider2,
                                        const DWF_Math::Vector3F&     mtv);

            /**
            * Sets OnAttachTextureFunction function
            *@param fHandler - function handler
            */
            virtual void Set_OnAttachTextureFunction(ITfOnAttachTextureFunction fHandler);

        private:
            float                      m_xPos                     = 0.0f;
            float                      m_yPos                     = 0.0f;
            float                      m_zPos                     = 0.0f;
            float                      m_Distance                 = 1.4f;
            float                      m_Angle                    = 0.0f;
            float                      m_Gravity                  = 0.0025f;
            float                      m_Velocity                 = 0.001f;
            float                      m_WalkOffset               = 1.0f;
            float                      m_PlayerShift              = 0.25f;
            bool                       m_Walking                  = false;
            ITfOnAttachTextureFunction m_fOnAttachTextureFunction = nullptr;

            /**
            * Called when a new frame is calculated in an animation
            *@param pAnim - the animation for which the frame is calculated
            *@param pAnimDesc - animation description
            */
            void OnFrame(const DWF_Scene::SceneItem_AnimAsset* pAnim, const DWF_Scene::SceneItem_AnimAsset::IAnimDesc* pAnimDesc);

            /**
            * Called when an animation end is reached
            *@param pAnim - the animation for which the end was reached
            *@param pAnimDesc - animation description
            */
            void OnEndReached(const DWF_Scene::SceneItem_AnimAsset* pAnim, const DWF_Scene::SceneItem_AnimAsset::IAnimDesc* pAnimDesc);
    };
}
