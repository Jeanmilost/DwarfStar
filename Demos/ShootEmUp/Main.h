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
#include "DWF_MDL.h"

// demo specific classes
#include "Sequencer.h"

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
        //REM virtual inline bool GetShowSkeleton();

        /**
        * Sets if animated model skeleton should be shown
        *@param @value - if true, animated model skeleton will be shown
        */
        //REM virtual inline void SetShowSkeleton(bool value);

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
        * Changes the camera type
        */
        //REM virtual inline void ChangeCameraType();

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

        typedef std::vector<std::string> IFilenames;

        static Main* m_This;

        DWF_Scene::Scene                             m_Scene;
        DWF_Renderer::Renderer_OpenGL                m_Renderer;
        std::shared_ptr<DWF_Model::MDL>              m_pEnemyMdl;
        std::shared_ptr<DWF_Model::Model>            m_pEnemyBox;
        std::shared_ptr<DWF_Renderer::Shader_OpenGL> m_pTexShader;
        std::shared_ptr<DWF_Renderer::Shader_OpenGL> m_pColShader;
        std::shared_ptr<DWF_Renderer::Shader_OpenGL> m_pStarShader;
        float                                        m_xPos             = 0.0f;
        float                                        m_yPos             = 0.0f;
        float                                        m_Angle            = (float)(-M_PI / 2.0);
        bool                                         m_ShowColliders    = false;
        bool                                         m_OldShowColliders = false;

        std::size_t m_Index = 0;
        std::vector<std::size_t> m_Enemies;

        Sequencer m_Sequencer;

        /**
        * Called when a texture should be created for a .mdl model file
        *@param pPixelBuffer - pixel buffer containing the texture
        *@return texture
        */
        DWF_Model::Texture* OnCreateTexture(const DWF_Buffer::PixelBuffer* pPixelBuffer);

        /**
        * Called when a new frame is calculated in an animation
        *@param pAnim - the animation for which the frame is calculated
        *@param pAnimDesc - animation description
        */
        //REM void OnFrame(const DWF_Scene::SceneItem_Animation* pAnim, const DWF_Scene::SceneItem_Animation::IAnimDesc* pAnimDesc);

        /**
        * Called when an animation end is reached
        *@param pAnim - the animation for which the end was reached
        *@param pAnimDesc - animation description
        */
        //REM void OnEndReached(const DWF_Scene::SceneItem_Animation* pAnim, const DWF_Scene::SceneItem_Animation::IAnimDesc* pAnimDesc);

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
        * Called to check if a new model should be spawn
        *@param pSpawner - scene spawner
        *@return true if a new model should be spawn, otherwise false
        */
        bool OnDoSpawn(DWF_Scene::Spawner* pSpawner);

        /**
        * Called to check if a new model was spawned
        *@param pSpawner - scene spawner
        *@param pItem - spawned model
        */
        void OnSpawned(DWF_Scene::Spawner* pSpawner, DWF_Scene::Spawner::IItem* pItem);

        /**
        * Called to check if a model owned by the spawner manager should be deleted
        *@param pSpawner - scene spawner
        *@param pItem - spawned model
        *@return true if the model should be deleted, otherwise false
        */
        bool OnDoDelete(DWF_Scene::Spawner* pSpawner, DWF_Scene::Spawner::IItem* pItem);

        /**
        * Called when the next position should be calculated for a model owned by the spawner manager
        *@param pSpawner - scene spawner
        *@param pItem - spawned model
        *@param elapsedTime - elapsed time since last calculated position
        */
        void OnCalculateMotion(DWF_Scene::Spawner* pSpawner, DWF_Scene::Spawner::IItem* pItem, double elapsedTime);

        void AddEnemy(std::size_t index, float x, float y);

        void DelEnemy(std::size_t index);

        /**
        * Called when the next position should be calculated for a star particle
        *@param pParticles - particles system
        *@param pParticle - particle for which the new position should be calculated
        *@param elapsedTime - elapsed time since last calculated position
        */
        void OnCalculateStarMotion(DWF_Particles::Particles* pParticles, DWF_Particles::Particle* pParticle, double elapsedTime);

        /**
        * Loads the scene
        *@param clientRect - application client rectangle
        */
        bool LoadScene(const RECT& clientRect);
};

//---------------------------------------------------------------------------
// Main
//---------------------------------------------------------------------------
/*REM
inline bool Main::GetShowSkeleton()
{
    return m_ShowSkeleton;
}
//---------------------------------------------------------------------------
inline void Main::SetShowSkeleton(bool value)
{
    m_ShowSkeleton = value;
}
*/
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
/*REM
inline void Main::ChangeCameraType()
{
    switch (m_CameraType)
    {
        case IECameraType::IE_CT_Static:
            m_CameraType = IECameraType::IE_CT_Follow;
            break;

        case IECameraType::IE_CT_Rotate:
            m_CameraType = IECameraType::IE_CT_Static;
            break;

        case IECameraType::IE_CT_Follow:
            m_CameraType = IECameraType::IE_CT_Rotate;
            break;
    }
}
//---------------------------------------------------------------------------
*/
