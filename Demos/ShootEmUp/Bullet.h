/****************************************************************************
 * ==> Bullet --------------------------------------------------------------*
 ****************************************************************************
 * Description : Shoot-em-up bullet                                         *
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
#include <vector>
#include <set>
#include <string>

// classes
#include "DWF_Vector3.h"
#include "DWF_Model.h"
#include "DWF_ModelFormat.h"
#include "DWF_Scene.h"
#include "DWF_Shader_OpenGL.h"
#include "Sequencer.h"

namespace ShootEmUp
{
    /**
    * Shoot-em-up bullet
    *@author Jean-Milost Reymond
    */
    class Bullet
    {
        public:
            /**
            * Constructor
            *@param name - bullet name
            *@param pModel - bullet model
            *@param pColShader - color shader
            */
            Bullet(const std::wstring&                                 name,
                   const std::shared_ptr<DWF_Model::Model>&            pModel,
                   const std::shared_ptr<DWF_Renderer::Shader_OpenGL>& pColShader);

            virtual ~Bullet();

            /**
            * Gets bullet name
            *@return the bullet name
            */
            inline std::wstring GetName() const;

            /**
            * Gets the model name, as existing in the scene
            *@return the model name, as existing in the scene
            */
            inline std::wstring GetModelNameInScene() const;

            /**
            * Adds a collider name to ignore by the bullet
            *@param name - collider name to ignore
            */
            void AddColliderToIgnore(const std::wstring& name);

            /**
            * Checks if a collider should be ignored by the bullet
            *@param name - collider name to check
            *@returns true if the collider should be ignored by the bullet, otherwise false
            */
            bool DoIgnoreCollider(const std::wstring& name) const;

            /**
            * Adds an asset for the bullet in the scene
            *@param scene - scene in which the asset should be added
            *@param x - bullet start x position
            *@param y - bullet start y position
            */
            void AddAsset(DWF_Scene::Scene& scene, float x, float y);

            /**
            * Adds a sequence which will be followed by the bullet
            *@param pSequencer - sequencer
            *@param startPos - bullet start position
            *@param dir - bullet direction
            */
            void AddSequence(Sequencer* pSequencer, const DWF_Math::Vector3F& startPos, const DWF_Math::Vector3F& dir) const;

            /**
            * Removes the bullet asset from the scene
            *@param scene - scene in which the asset should be deleted
            */
            void DeleteAsset(DWF_Scene::Scene& scene);

            /**
            * Moves the bullet to a new position
            *@param pSequencer - sequencer
            *@param elapsedTime - elapsed time since last move
            */
            void Move(Sequencer* pSequencer, double elapsedTime);

            /**
            * Breaks the bullet sequence and remove it on next move
            */
            void Break();

        private:
            typedef std::set<std::wstring> IColliderNames;

            DWF_Scene::SceneItem_Model*                  m_pSceneItem = nullptr;
            std::shared_ptr<DWF_Model::Model>            m_pModel;
            std::shared_ptr<DWF_Renderer::Shader_OpenGL> m_pColShader;
            IColliderNames                               m_CollidersToIgnore;
            std::wstring                                 m_Name;
            DWF_Math::Vector3F                           m_OldPos;
            bool                                         m_Broken = false;
    };

    /**
    * Bullets dictionary
    */
    typedef std::vector<Bullet*> Bullets;

    //---------------------------------------------------------------------------
    inline std::wstring Bullet::GetName() const
    {
        return m_Name;
    }
    //---------------------------------------------------------------------------
    inline std::wstring Bullet::GetModelNameInScene() const
    {
        return m_Name + L"_model_" + std::to_wstring((std::size_t)this);
    }
    //---------------------------------------------------------------------------
}
