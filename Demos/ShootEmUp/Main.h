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
#include <vector>
#include <map>
#include <set>

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
#include "Bullet.h"
#include "Entity.h"
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

        typedef std::vector<std::pair<int, ShootEmUp::Entity::IESequenceType>> IEvents;
        typedef std::set<int>                                                  IRaisedEvents;
        typedef std::vector<std::string>                                       IFilenames;

        static Main* m_This;

        HWND                                         m_hWnd             = nullptr;
        DWF_Scene::Scene                             m_Scene;
        DWF_Renderer::Renderer_OpenGL                m_Renderer;
        std::shared_ptr<DWF_Model::MDL>              m_pEnemyMdl;
        std::shared_ptr<DWF_Model::Model>            m_pEnemyBox;
        std::shared_ptr<DWF_Model::Model>            m_pBullet;
        std::shared_ptr<DWF_Renderer::Shader_OpenGL> m_pTexShader;
        std::shared_ptr<DWF_Renderer::Shader_OpenGL> m_pColShader;
        std::shared_ptr<DWF_Renderer::Shader_OpenGL> m_pStarShader;
        std::shared_ptr<DWF_Renderer::Shader_OpenGL> m_pExplosionShader;
        ShootEmUp::Sequencer                         m_Sequencer;
        ShootEmUp::Entities                          m_Entities;
        ShootEmUp::Bullets                           m_Bullets;
        IEvents                                      m_Events;
        IRaisedEvents                                m_RaisedEvents;
        GLint                                        m_AlphaSlot        = 0;
        std::size_t                                  m_Index            = 0;
        std::size_t                                  m_Difficulty       = 0;
        float                                        m_xPos             = 0.0f;
        float                                        m_yPos             = 0.0f;
        float                                        m_Angle            = (float)(-M_PI / 2.0);
        double                                       m_CurrentTime      = 0.0;
        double                                       m_GameOverTime     = 0.0;
        double                                       m_LastBulletTime   = 0.0;
        bool                                         m_ShowColliders    = false;
        bool                                         m_OldShowColliders = false;
        bool                                         m_GameOver         = false;
        bool                                         m_CanRestart       = false;

        /**
        * Called when a texture should be created for a .mdl model file
        *@param pPixelBuffer - pixel buffer containing the texture
        *@return texture
        */
        DWF_Model::Texture* OnCreateTexture(const DWF_Buffer::PixelBuffer* pPixelBuffer);

        /**
        * Called when a texture should be loaded
        *@param textureName - texture name to load
        *@param is32bit - if true, the texture is a 32 bit (RGBA) texture
        *@return texture
        */
        DWF_Model::Texture* OnLoadTexture(const std::string& textureName, bool is32bit);

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

        /**
        * Called when the next position should be calculated for a star particle
        *@param pParticles - particles system
        *@param pParticle - particle for which the new position should be calculated
        *@param elapsedTime - elapsed time since last calculated position
        */
        void OnCalculateStarMotion(DWF_Particles::Particles* pParticles, DWF_Particles::Particle* pParticle, double elapsedTime);

        /**
        * Called when the next position should be calculated for an explosion particle
        *@param pParticles - particles system
        *@param pParticle - particle for which the new position should be calculated
        *@param elapsedTime - elapsed time since last calculated position
        */
        void OnCalculateExplosionMotion(DWF_Particles::Particles* pParticles, DWF_Particles::Particle* pParticle, double elapsedTime);

        /**
        * Called to notify that the sequence end was reached
        *@param pSequencer - sequencer at which belongs the sequence
        *@param pSequence - sequence which reached the end
        */
        void OnSequenceEndReached(const ShootEmUp::Sequencer* pSequencer, const ShootEmUp::Sequencer::ISequence* pSequence);

        /**
        * Checks if an event should be raised (e.g. if an enemy should spawn)
        *@param index - event index
        *@return true if event should be raised, otherwise false
        */
        bool DoRaiseEvent(std::size_t index) const;

        /**
        * Adds a bullet to the scene
        *@param pItem - item from which the bullet should be fired
        *@param pCollider -item collider
        *@param fromPlayer - if true, the bullet was fired by the player
        */
        void AddBullet(DWF_Scene::SceneItem_StaticAsset* pItem, DWF_Scene::SceneItem_Model* pCollider, bool fromPlayer);

        /**
        * Deletes a bullet from the scene
        *@param pBullet - bullet to delete
        */
        void DeleteBullet(ShootEmUp::Bullet* pBullet);

        /**
        * Adds an entity to the scene
        *@param pItem - spawned item
        *@param evt - entity raising event
        */
        void AddEntity(DWF_Scene::Spawner::IItem* pItem, const std::pair<int, ShootEmUp::Entity::IESequenceType>& evt);

        /**
        * Deletes an entity from the scene
        *@param pItem - spawned item belonging to the entity
        */
        void DeleteEntity(DWF_Scene::Spawner::IItem* pItem);

        /**
        * Checks if a bullet do ignore the collider and if an enemy was hit
        *@param pItem1 - the item containing the bullet
        *@param pItem2 - the hit spaceship, may be either the player or any enemy
        *@return true if the collision should be ignored, otherwise false
        */
        bool CheckBulletIsIgnoredOrHitEnemy(const DWF_Scene::SceneItem* pItem1, const DWF_Scene::SceneItem* pItem2);

        /**
        * Runs the game over sequence
        *@param pScene - scene
        */
        void RunGameOver(const DWF_Scene::Scene* pScene);

        /**
        * Resets the game
        */
        void ResetGame();

        /**
        * Loads the scene
        *@param clientRect - application client rectangle
        */
        bool LoadScene(const RECT& clientRect);
};

//---------------------------------------------------------------------------
// Main
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
