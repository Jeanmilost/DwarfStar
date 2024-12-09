/****************************************************************************
 * ==> DWF_Scene -----------------------------------------------------------*
 ****************************************************************************
 * Description : The scene                                                  *
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

// classes
#include "DWF_PointOfView.h"
#include "DWF_Camera.h"
#include "DWF_Arcball.h"
#include "DWF_SceneItem.h"
#include "DWF_SceneItemModel.h"
#include "DWF_SceneItemPOV.h"
#include "DWF_SceneAudioItem.h"
#include "DWF_Renderer.h"

#pragma once

namespace DWF_Scene
{
    /**
    * The scene
    *@author Jean-Milost Reymond
    */
    // FIXME for Jean: The scene isn't an inspector. In the scene, the items are organized linearly
    //                 in the order they should be rendered (opaque/transparent, ...), while in the
    //                 inspector, the items are organized as a tree and can encapsulate other items,
    //                 in which a parent item may influence its children
    class Scene
    {
        public:
            /**
            * Items group type
            */
            enum class IEGroupType
            {
                IE_GT_Unknown = 0,
                IE_GT_POV,
                IE_GT_Model,
                IE_GT_Transparent
            };

            /**
            * Scene item identifier
            */
            struct IItemID
            {
                IItemID();

                /**
                * Constructor
                *@param group - group in which item was added
                *@param index - item index in the group
                */
                IItemID(IEGroupType group, std::size_t index);

                virtual ~IItemID();

                IEGroupType m_Group = IEGroupType::IE_GT_Unknown;
                std::size_t m_Index = 0;
            };

            /**
            * Called when a scene begins
            */
            typedef std::function<void()> ITfOnBeginScene;

            /**
            * Called when a scene ends
            */
            typedef std::function<void()> ITfOnEndScene;

            /**
            * Called when a collision happened between 2 scene items
            *@param arg1 - scene in which the collision was detected
            *@param arg2 - first item in collision
            *@param arg3 - collider in collision, belonging to the first item
            *@param arg4 - second item in collision
            *@param arg5 - collider in collision, belonging to the second item
            *@param arg6 - minimum translation vector between the 2 colliders
            */
            typedef std::function<void(const Scene*,
                                             SceneItem*,
                                             DWF_Collider::Collider*,
                                             SceneItem*,
                                             DWF_Collider::Collider*,
                                       const DWF_Math::Vector3F&)> ITfOnCollision;

            Scene();
            virtual ~Scene();

            /**
            * Clears the scene
            */
            virtual void Clear();

            /**
            * Gets the renderer to use
            *@return the renderer to use
            */
            virtual inline DWF_Renderer::Renderer* GetRenderer() const;

            /**
            * Sets the renderer to use
            *@param renderer - the renderer to use
            */
            virtual inline void SetRenderer(DWF_Renderer::Renderer& renderer);

            /**
            * Gets the background color
            *@return the background color
            */
            virtual inline DWF_Model::ColorF GetColor() const;

            /**
            * Sets the background color
            *@param color - the background color to set
            */
            virtual inline void SetColor(const DWF_Model::ColorF& color);

            /**
            * Set the scene skybox
            *@param pTexture - skybox texture
            *@param pShader - shader to use to draw the skybox
            *@note Don't delete the texture from outside, it will be deleted internally
            */
            virtual void SetSkybox(DWF_Model::Texture* pTexture, DWF_Renderer::Shader* pShader);

            /**
            * Adds an item containing a point of view to the scene
            *@param pItem - scene item to add
            *@note The item will be deleted internally, don't delete it from outside
            */
            virtual void Add(SceneItem_PointOfView* pItem);

            /**
            * Adds an item containing a model to the scene
            *@param pItem - scene item to add
            *@param transparent - if true, the item should be drawn with transparency support enabled
            *@note The item will be deleted internally, don't delete it from outside
            */
            virtual void Add(SceneItem_ModelBase* pItem, bool transparent);

            /**
            * Adds an item containing an audio to the scene
            *@param pItem - audio item to add
            *@note The item will be deleted internally, don't delete it from outside
            */
            virtual void Add(SceneAudioItem* pItem);

            /**
            * Deletes an item from the scene
            *@param pItem - scene item to delete
            */
            virtual void Delete(SceneItem* pItem);

            /**
            * Deletes an audio item from the scene
            *@param pItem - scene audio item to delete
            */
            virtual void Delete(SceneAudioItem* pItem);

            /**
            * Deletes an item from the scene at index
            *@param id - item identifier to delete
            */
            virtual void DeleteAt(const IItemID& id);

            /**
            * Deletes an audio item from the scene at index
            *@param index - audio item index to delete
            */
            virtual void DeleteAt(std::size_t index);

            /**
            * Gets a scene item at index
            *@param id - item identifier to set
            *@return scene item, nullptr if not found or on error
            */
            virtual SceneItem* Get(const IItemID& id) const;

            /**
            * Gets an audio item at index
            *@param index - audio item index to get
            *@return audio item, nullptr if not found or on error
            */
            virtual SceneAudioItem* Get(std::size_t index) const;

            /**
            * Gets the scene item count
            *@param group - group for which the items should be count
            *@return scene item count
            */
            virtual std::size_t GetCount(IEGroupType group) const;

            /**
            * Gets the audio item count
            *@return audio item count
            */
            virtual std::size_t GetCount() const;

            /**
            * Searches an item in the whole scene
            *@param name - item name to search
            *@return scene item, nullptr if not found or on error
            */
            virtual SceneItem* SearchItem(const std::wstring& name) const;

            /**
            * Searches an audio item in the whole scene
            *@param name - item audio name to search
            *@return audio item, nullptr if not found or on error
            */
            virtual SceneAudioItem* SearchAudio(const std::wstring& name) const;

            /**
            * Detects the collisions in the scene
            */
            virtual void DetectCollisions() const;

            /**
            * Renders the scene
            */
            virtual void Render() const;

            /**
            * Set OnBeginScene function handler
            *@param fOnBeginScene - function handler
            */
            void Set_OnBeginScene(ITfOnBeginScene fOnBeginScene);

            /**
            * Set OnEndScene function handler
            *@param fOnEndScene - function handler
            */
            void Set_OnEndScene(ITfOnEndScene fOnEndScene);

            /**
            * Set OnCollision function handler
            *@param fOnCollision - function handler
            */
            void Set_OnCollision(ITfOnCollision fOnCollision);

        private:
            /**
            * Items group
            */
            struct IGroup
            {
                SceneItems  m_Items;
                IEGroupType m_Type = IEGroupType::IE_GT_Unknown;

                IGroup();
                virtual ~IGroup();
            };

            typedef std::vector<IGroup*>                    IGroups;
            typedef std::map<std::wstring, SceneItem*>      IItemDictionary;
            typedef std::map<std::wstring, SceneAudioItem*> IAudioDictionary;

            DWF_Renderer::Renderer* m_pRenderer     = nullptr;
            DWF_Model::Model*       m_pSkybox       = nullptr;
            DWF_Renderer::Shader*   m_pSkyboxShader = nullptr;
            IGroups                 m_Groups;
            SceneAudioItems         m_AudioItems;
            IItemDictionary         m_ItemCache;
            IAudioDictionary        m_AudioCache;
            DWF_Model::ColorF       m_Color;
            ITfOnBeginScene         m_fOnBeginScene = nullptr;
            ITfOnEndScene           m_fOnEndScene   = nullptr;
            ITfOnCollision          m_fOnCollision  = nullptr;

            /**
            * Get the group from the groups
            *@param type - group type to get
            *@return the group matching with type, nullptr if not found or on error
            */
            IGroup* GetGroup(IEGroupType type) const;

            /**
            * Adds a scene item to a group
            *@param pGroup - group in which the item should be added
            *@param pItem - item to add
            */
            void AddItem(IGroup* pGroup, SceneItem* pItem);

            /**
            * Detects the collisions in the scene
            *@param pItem - item for which collisions against other items should be detected
            *@param pCollider - collider belonging to scene item being tested
            */
            virtual void DetectCollisionsForItem(SceneItem* pItem, DWF_Collider::Collider* pCollider) const;
    };

    //---------------------------------------------------------------------------
    // Scene
    //---------------------------------------------------------------------------
    inline DWF_Renderer::Renderer* Scene::GetRenderer() const
    {
        return m_pRenderer;
    }
    //---------------------------------------------------------------------------
    inline void Scene::SetRenderer(DWF_Renderer::Renderer& renderer)
    {
        m_pRenderer = &renderer;
    }
    //---------------------------------------------------------------------------
    inline DWF_Model::ColorF Scene::GetColor() const
    {
        return m_Color;
    }
    //---------------------------------------------------------------------------
    inline void Scene::SetColor(const DWF_Model::ColorF& color)
    {
        m_Color = color;
    }
    //---------------------------------------------------------------------------
}
