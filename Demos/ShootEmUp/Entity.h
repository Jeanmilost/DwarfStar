/****************************************************************************
 * ==> Entity --------------------------------------------------------------*
 ****************************************************************************
 * Description : Shoot-em-up entity                                         *
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
#include <map>
#include <string>

// classes
#include "DWF_Vector3.h"
#include "DWF_Model.h"
#include "DWF_ModelFormat.h"
#include "DWF_SceneSpawner.h"
#include "DWF_Scene.h"
#include "DWF_Shader_OpenGL.h"
#include "Sequencer.h"

namespace ShootEmUp
{
    /**
    * Shoot-em-up entity
    *@author Jean-Milost Reymond
    */
    class Entity
    {
        public:
            /**
            * Available sequence type
            */
            enum class IESequenceType
            {
                IE_ST_BottomToTop,
                IE_ST_TopToBottom
            };

            /**
            * Constructor
            *@param name - entity name
            *@param pModel - entity model
            *@param pColliderModel - entity collider model
            *@param pTexShader - texture shader
            *@param pColShader - color shader
            */
            Entity(const std::wstring&                                 name,
                   const std::shared_ptr<DWF_Model::ModelFormat>&      pModel,
                   const std::shared_ptr<DWF_Model::Model>&            pColliderModel,
                   const std::shared_ptr<DWF_Renderer::Shader_OpenGL>& pTexShader,
                   const std::shared_ptr<DWF_Renderer::Shader_OpenGL>& pColShader);

            virtual ~Entity();

            /**
            * Gets entity name
            *@return the entity name
            */
            inline std::wstring GetName() const;

            /**
            * Gets the model name, as existing in the scene
            *@return the model name, as existing in the scene
            */
            inline std::wstring GetModelNameInScene() const;

            /**
            * Gets the collider name, as existing in the scene
            *@return the collider name, as existing in the scene
            */
            inline std::wstring GetColliderNameInScene() const;

            /**
            * Adds an asset for the entity in the scene
            *@param pItem - spawned item in the scene
            *@param scene - scene in which the asset should be added
            *@param x - entity start x position
            *@param y - entity start y position
            */
            void AddAsset(DWF_Scene::Spawner::IItem* pItem, DWF_Scene::Scene& scene, float x, float y);

            /**
            * Adds a sequence which will be followed by the entity
            *@param pSequencer - sequencer
            *@param sequenceType - sequence type
            *@param startPos - sequence start position
            */
            void AddSequence(Sequencer* pSequencer, IESequenceType sequenceType, const DWF_Math::Vector3F& startPos) const;

            /**
            * Moves the entity to a new position
            *@param pSequencer - sequencer
            *@param pItem - spawned item in the scene
            *@param elapsedTime - elapsed time since last move
            */
            void Move(Sequencer* pSequencer, DWF_Scene::Spawner::IItem* pItem, double elapsedTime);

        private:
            std::shared_ptr<DWF_Model::ModelFormat>      m_pModel;
            std::shared_ptr<DWF_Model::Model>            m_pColliderModel;
            std::shared_ptr<DWF_Renderer::Shader_OpenGL> m_pTexShader;
            std::shared_ptr<DWF_Renderer::Shader_OpenGL> m_pColShader;
            std::wstring                                 m_Name;
            DWF_Math::Vector3F                           m_OldPos;
            float                                        m_Angle = (float)(M_PI / 2.0);
    };

    /**
    * Entities dictionary
    */
    typedef std::map<DWF_Scene::Spawner::IItem*, Entity*> Entities;

    //---------------------------------------------------------------------------
    inline std::wstring Entity::GetName() const
    {
        return m_Name;
    }
    //---------------------------------------------------------------------------
    inline std::wstring Entity::GetModelNameInScene() const
    {
        return m_Name + L"_model_" + std::to_wstring((std::size_t)this);
    }
    //---------------------------------------------------------------------------
    inline std::wstring Entity::GetColliderNameInScene() const
    {
        return m_Name + L"_collider_" + std::to_wstring((std::size_t)this);
    }
    //---------------------------------------------------------------------------
}
