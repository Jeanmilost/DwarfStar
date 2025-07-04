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
#include "DWF_SceneItemAnimAsset.h"

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
        * Gets if show player capsule should be shown
        *@return true if show player capsule should be shown, otherwise false
        */
        virtual inline bool GetShowPlayerCap();

        /**
        * Sets if show player capsule should be shown
        *@param value - if true, show player capsule should be shown
        */
        virtual inline void SetShowPlayerCap(bool value);

        /**
        * Runs the form
        *@param hInstance - app instance
        *@param nCmdShow - flags specifying how the application should be displayed when opened
        */
        virtual int Run(HINSTANCE hInstance, int nCmdShow);

    private:
        typedef std::map<std::string, DWF_Model::Texture*> Textures;
        typedef std::vector<std::string>                   IFilenames;

        static Main* m_This;

        DWF_Scene::Scene              m_Scene;
        DWF_Renderer::Renderer_OpenGL m_Renderer;
        Textures                      m_TextureItems;
        GLuint                        m_SkyboxTexId      = -1;
        float                         m_xPos             =  0.0f;
        float                         m_yPos             =  0.0f;
        float                         m_zPos             =  0.0f;
        float                         m_Velocity         =  0.025f;
        int                           m_LastMouseXPos    =  0;
        int                           m_LastMouseYPos    =  0;
        int                           m_xDelta           =  0;
        int                           m_yDelta           =  0;
        bool                          m_Walking          =  false;
        bool                          m_Jumping          =  false;
        bool                          m_ShowSkeleton     =  false;
        bool                          m_OldShowSkeleton  =  false;
        bool                          m_ShowPlayerCap    =  false;
        bool                          m_OldShowPlayerCap =  false;

        /**
        * Called when a texture should be loaded
        *@param textureName - texture file name, without path
        *@param is32bit - if true, the texture is a 32 bit texture
        */
        DWF_Model::Texture* OnLoadTexture(const std::string& textureName, bool is32bit);

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
        * Loads the cubemap textures
        *@param fileNames - texture file names
        *@return texture identifier
        */
        GLuint LoadCubemap(const IFilenames fileNames);

        /**
        * Loads the scene
        *@param pTexShader - texture shader
        *@param pColShader - color shader
        *@param pCubemapShader - cubemap shader
        *@param clientRect - application client rectangle
        */
        bool LoadScene(const std::shared_ptr<DWF_Renderer::Shader_OpenGL>& pTexShader,
                       const std::shared_ptr<DWF_Renderer::Shader_OpenGL>& pColShader,
                       const std::shared_ptr<DWF_Renderer::Shader_OpenGL>& pCubemapShader,
                       const RECT&                                         clientRect);
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
inline bool Main::GetShowPlayerCap()
{
    return m_ShowPlayerCap;
}
//---------------------------------------------------------------------------
inline void Main::SetShowPlayerCap(bool value)
{
    m_ShowPlayerCap = value;
}
//---------------------------------------------------------------------------
