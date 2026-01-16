/****************************************************************************
 * ==> Main ----------------------------------------------------------------*
 ****************************************************************************
 * Description : Main application class                                     *
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
#include <string>
#include <map>

// classes
#include "DWF_PixelBuffer.h"
#include "DWF_Texture_OpenGL.h"
#include "DWF_Shader_OpenGL.h"
#include "DWF_Renderer_OpenGL.h"
#include "DWF_Scene.h"
#include "DWF_SceneItemPOV.h"
#include "DWF_SceneItemModel.h"
#include "DWF_SceneItemStaticAsset.h"
#include "DWF_SceneItemAnimAsset.h"
#include "DWF_Force.h"

// demo
#include "Skybox.h"
#include "Tower.h"
#include "Platforms.h"
#include "Water.h"
#include "Player.h"

// libraries
#include <windows.h>

/**
* Main application
*@author Jean-Milost Reymond
*/
class Main
{
    public:
        Main();
        virtual ~Main();

        /**
        * Gets the main form instance
        *@return the main form instance
        */
        static Main* GetInstance();

        /**
        * Gets if animated model skeleton should be shown
        *@return true if animated model skeleton should be shown, otherwise false
        */
        virtual inline bool GetShowSkeleton();

        /**
        * Sets if animated model skeleton should be shown
        *@param @value - if true, animated model skeleton will be shown
        */
        virtual inline void SetShowSkeleton(bool value);

        /**
        * Gets if colliders should be shown
        *@return true if colliders should be shown, otherwise false
        */
        virtual inline bool GetShowColliders();

        /**
        * Sets if colliders should be shown
        *@param value - if true, colliders should be shown
        */
        virtual inline void SetShowColliders(bool value);

        /**
        * Runs the form
        *@param hInstance - app instance
        *@param nCmdShow - flags specifying how the application should be displayed when opened
        */
        virtual int Run(HINSTANCE hInstance, int nCmdShow);

    private:
        /**
        * Camera types
        */
        enum class IECameraType
        {
            IE_CT_Static,
            IE_CT_Rotate,
            IE_CT_Follow
        };

        typedef std::map<std::string, DWF_Model::Texture*>                ITextures;
        typedef std::vector<std::shared_ptr<DWF_Renderer::Shader_OpenGL>> IShaders;

        static Main* m_This;

        DWF_Scene::Scene              m_Scene;
        DWF_Renderer::Renderer_OpenGL m_Renderer;
        ITextures                     m_TextureItems;
        Nebulus::Skybox*              m_pSkybox          = nullptr;
        Nebulus::Tower*               m_pTower           = nullptr;
        Nebulus::Platforms*           m_pPlatforms       = nullptr;
        Nebulus::Water*               m_pWater           = nullptr;
        Nebulus::Player*              m_pPlayer          = nullptr;
        /*REM
        float m_PlayerShift = 0.25f; // player
        float                         m_xPos             =  0.0f; // player
        float                         m_yPos             =  0.0f; // player
        float                         m_zPos             =  0.0f; // player
        float                         m_Distance         =  1.4f; // player
        float                         m_Angle            =  0.0f; // player?
        float m_Gravity = 0.0025f; // player
        float                         m_Velocity         =  0.001f; // player
        float                         m_WalkOffset       =  1.0f; // player
        bool                          m_Walking          =  false;
        */
        bool                          m_ShowSkeleton     =  false;
        bool                          m_OldShowSkeleton  =  false;
        bool                          m_ShowColliders    =  false;
        bool                          m_OldShowColliders =  false;

        /**
        * Loads a texture for an item
        *@param texturePath - texture path
        *@param textureName - texture file name, without path
        *@param is32bit - if true, the texture is a 32 bit texture
        */
        DWF_Model::Texture* LoadTexture(const Nebulus::Item& item, const std::string& texturePath, const std::string& textureName, bool is32bit);

        /**
        * Called when a texture should be loaded for the player model
        *@param textureName - texture file name, without path
        *@param is32bit - if true, the texture is a 32 bit texture
        */
        DWF_Model::Texture* OnLoadPlayerTexture(const std::string& textureName, bool is32bit);

        /**
        * Called when a texture should be loaded for the tower
        *@param textureName - texture file name, without path
        *@param is32bit - if true, the texture is a 32 bit texture
        */
        DWF_Model::Texture* OnLoadTowerTexture(const std::string& textureName, bool is32bit);

        /**
        * Called when a new frame is calculated in an animation
        *@param pAnim - the animation for which the frame is calculated
        *@param pAnimDesc - animation description
        */
        //REM void OnFrame(const DWF_Scene::SceneItem_AnimAsset* pAnim, const DWF_Scene::SceneItem_AnimAsset::IAnimDesc* pAnimDesc);

        /**
        * Called when an animation end is reached
        *@param pAnim - the animation for which the end was reached
        *@param pAnimDesc - animation description
        */
        //REM void OnEndReached(const DWF_Scene::SceneItem_AnimAsset* pAnim, const DWF_Scene::SceneItem_AnimAsset::IAnimDesc* pAnimDesc);

        /**
        * Called when a scene physics should be updated
        *@param elapsedTime - elapsed time since the last update
        */
        void OnSceneUpdatePhysics(const DWF_Scene::Scene* pScene, double elapsedTime);

        /**
        * Called when a scene should be updated
        *@param elapsedTime - elapsed time since the last update
        */
        void OnSceneUpdate(const DWF_Scene::Scene* pScene, double elapsedTime);

        /**
        * Called when a collision was detected in the scene
        *@param pScene - the scene in which the collision happened
        *@param pItem1 - first item in collision
        *@param pCollider1 - collider belonging to the first item
        *@param pItem2 - second item in collision
        *@param pCollider2 - collider belonging to the second item
        *@param mtv - minimum translation vector resulting from the collision
        */
        void OnCollision(const DWF_Scene::Scene*       pScene,
                               DWF_Scene::SceneItem*   pItem1,
                               DWF_Collider::Collider* pCollider1,
                               DWF_Scene::SceneItem*   pItem2,
                               DWF_Collider::Collider* pCollider2,
                         const DWF_Math::Vector3F&     mtv);

        /**
        * Called when a texture loader function should be attached to the tower model
        *@param pModel - the model for which the texture function should be attached
        */
        void OnAttachTowerTextureFn(std::shared_ptr<DWF_Model::Model>& pModel);

        /**
        * Called when a texture loader function should be attached to the player model
        *@param pIQM - the model for which the texture function should be attached
        */
        void OnAttachPlayerTextureFn(std::shared_ptr<DWF_Model::IQM>& pIQM);

        /**
        * Loads the scene
        *@param shaders - scene shaders
        *@param clientRect - application client rectangle
        */
        bool LoadScene(const IShaders& shaders, const RECT& clientRect);
};

//---------------------------------------------------------------------------
// Main
//---------------------------------------------------------------------------
inline bool Main::GetShowSkeleton()
{
    return m_ShowSkeleton;
}
//---------------------------------------------------------------------------
inline void Main::SetShowSkeleton(bool value)
{
    m_ShowSkeleton = value;
}
//---------------------------------------------------------------------------
inline bool Main::GetShowColliders()
{
    return m_ShowColliders;
}
//---------------------------------------------------------------------------
inline void Main::SetShowColliders(bool value)
{
    m_ShowColliders = value;
}
//---------------------------------------------------------------------------
