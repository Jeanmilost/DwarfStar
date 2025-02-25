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

#include "DWF_Scene.h"

// classes
#include "DWF_ModelFactory.h"
#include "DWF_GJK.h"

using namespace DWF_Scene;

//---------------------------------------------------------------------------
// Scene::IItemID
//---------------------------------------------------------------------------
Scene::IItemID::IItemID()
{}
//---------------------------------------------------------------------------
Scene::IItemID::IItemID(IEGroupType group, std::size_t index) :
    m_Group(group),
    m_Index(index)
{}
//---------------------------------------------------------------------------
Scene::IItemID::~IItemID()
{}
//---------------------------------------------------------------------------
// Scene::IGroup
//---------------------------------------------------------------------------
Scene::IGroup::IGroup()
{}
//---------------------------------------------------------------------------
Scene::IGroup::~IGroup()
{
    // iterate through items to delete, and delete each of them
    for (std::size_t i = 0; i < m_Items.size(); ++i)
        delete m_Items[i];
}
//---------------------------------------------------------------------------
// Scene
//---------------------------------------------------------------------------
Scene::Scene() :
    m_FrameDuration(1000.0 / m_FPS)
{}
//---------------------------------------------------------------------------
Scene::~Scene()
{
    // clear the scene. NOTE use the fully qualified name to avoid to use an inherited function)
    Scene::Clear();
}
//---------------------------------------------------------------------------
void Scene::Clear()
{
    // clear the caches
    m_ItemCache.clear();
    m_AudioCache.clear();

    // iterate through groups to delete, and delete each of them
    for (std::size_t i = 0; i < m_Groups.size(); ++i)
        delete m_Groups[i];

    // iterate through audio items to delete, and delete each of them
    for (std::size_t i = 0; i < m_AudioItems.size(); ++i)
        delete m_AudioItems[i];

    // clear the groups
    m_Groups.clear();

    // clear the skybox
    if (m_pSkybox)
        delete m_pSkybox;
}
//---------------------------------------------------------------------------
void Scene::SetSkybox(DWF_Model::Texture* pTexture, DWF_Renderer::Shader* pShader)
{
    if (!pTexture)
        return;

    if (!pShader)
        return;

    // get the skybox model to use
    if (!m_pSkybox)
        m_pSkybox = DWF_Model::Factory::GetSkybox(1.0f, 1.0f, 1.0f, false);

    // if a previous texture existed, delete it
    if (m_pSkybox->m_Mesh[0]->m_VB[0]->m_Material.m_pTexture)
        delete m_pSkybox->m_Mesh[0]->m_VB[0]->m_Material.m_pTexture;

    // set the new texture to use
    m_pSkybox->m_Mesh[0]->m_VB[0]->m_Material.m_pTexture = pTexture;

    // set the shader to use to draw the skybox
    m_pSkyboxShader = pShader;
}
//---------------------------------------------------------------------------
void Scene::Add(SceneItem_PointOfView* pItem)
{
    if (!pItem)
        return;

    IGroup* pGroup = nullptr;

    // iterate through groups and search for scene items in which the item should be added
    for (std::size_t i = 0; i < m_Groups.size(); ++i)
        // found the point of views group?
        if (m_Groups[i]->m_Type == IEGroupType::IE_GT_POV)
        {
            pGroup = m_Groups[i];
            break;
        }

    // group still not created?
    if (!pGroup)
    {
        // create it
        std::unique_ptr<IGroup> pNewGroup = std::make_unique<IGroup>();
        m_Groups.push_back(pNewGroup.get());
        pNewGroup->m_Type = IEGroupType::IE_GT_POV;
        pGroup            = pNewGroup.release();
    }

    AddItem(pGroup, pItem);
}
//---------------------------------------------------------------------------
void Scene::Add(SceneItem_ModelBase* pItem, bool transparent)
{
    if (!pItem)
        return;

    IGroup* pGroup = nullptr;

    // iterate through groups and search for scene items in which the item should be added
    for (std::size_t i = 0; i < m_Groups.size(); ++i)
        // transparent model?
        if (transparent)
        {
            // found the transparent models group?
            if (m_Groups[i]->m_Type == IEGroupType::IE_GT_Transparent)
            {
                pGroup = m_Groups[i];
                break;
            }
        }
        else
        // found the models group?
        if (m_Groups[i]->m_Type == IEGroupType::IE_GT_Model)
        {
            pGroup = m_Groups[i];
            break;
        }

    // group still not created?
    if (!pGroup)
    {
        // create it
        std::unique_ptr<IGroup> pNewGroup = std::make_unique<IGroup>();
        m_Groups.push_back(pNewGroup.get());
        pNewGroup->m_Type = IEGroupType::IE_GT_Model;
        pGroup            = pNewGroup.release();
    }

    AddItem(pGroup, pItem);
}
//---------------------------------------------------------------------------
void Scene::Add(SceneAudioItem* pItem)
{
    if (!pItem)
        return;

    // search if audio item already exists, in order to not add it twice
    for (std::size_t i = 0; i < m_AudioItems.size(); ++i)
        if (m_AudioItems[i] == pItem)
            return;

    // get audio item name
    const std::wstring itemName = pItem->GetName();

    // item name should be defined
    if (itemName.empty())
        throw new std::exception("The audio item name is empty");

    // check if an item with the same name already exists
    if (SearchAudio(itemName))
        throw new std::exception("An audio item with the same name already exists. The audio item name should be unique in the scene");

    // add audio item to scene
    m_AudioItems.push_back(pItem);

    // also add it to the cache
    m_AudioCache[itemName] = pItem;
}
//---------------------------------------------------------------------------
void Scene::Delete(SceneItem* pItem)
{
    if (!pItem)
        return;

    // iterate through groups and find item to delete
    for (std::size_t i = 0; i < m_Groups.size(); ++i)
        // iterate through scene items and find item to delete
        for (std::size_t j = 0; j < m_Groups[i]->m_Items.size(); ++j)
            // found item to delete?
            if (m_Groups[i]->m_Items[j] == pItem)
            {
                // search the item in the cache
                IItemDictionary::iterator it = m_ItemCache.find(m_Groups[i]->m_Items[j]->GetName());

                // if found, remove it from cache
                if (it != m_ItemCache.end())
                    m_ItemCache.erase(it);

                // delete item from scene
                delete m_Groups[i]->m_Items[j];
                m_Groups[i]->m_Items.erase(m_Groups[i]->m_Items.begin() + j);

                return;
            }
}
//---------------------------------------------------------------------------
void Scene::Delete(SceneAudioItem* pItem)
{
    if (!pItem)
        return;

    // iterate through scene audio items and find item to delete
    for (std::size_t i = 0; i < m_AudioItems.size(); ++i)
        // found item to delete?
        if (m_AudioItems[i] == pItem)
        {
            // search the audio item in the cache
            IAudioDictionary::iterator it = m_AudioCache.find(m_AudioItems[i]->GetName());

            // if found, remove it from cache
            if (it != m_AudioCache.end())
                m_AudioCache.erase(it);

            // delete item from scene
            delete m_AudioItems[i];
            m_AudioItems.erase(m_AudioItems.begin() + i);

            return;
        }
}
//---------------------------------------------------------------------------
void Scene::DeleteAt(const IItemID& id)
{
    // iterate through groups and find item to delete
    for (std::size_t i = 0; i < m_Groups.size(); ++i)
    {
        // not the group in which the item should be deleted?
        if (m_Groups[i]->m_Type != id.m_Group)
            continue;

        // is index out of bounds?
        if (id.m_Index >= m_Groups[i]->m_Items.size())
            continue;

        // search the item in the cache
        IItemDictionary::iterator it = m_ItemCache.find(m_Groups[i]->m_Items[id.m_Index]->GetName());

        // if found, remove it from cache
        if (it != m_ItemCache.end())
            m_ItemCache.erase(it);

        // delete item from scene
        delete m_Groups[i]->m_Items[id.m_Index];
        m_Groups[i]->m_Items.erase(m_Groups[i]->m_Items.begin() + id.m_Index);
    }
}
//---------------------------------------------------------------------------
void Scene::DeleteAt(std::size_t index)
{
    // is index out of bounds?
    if (index >= m_AudioItems.size())
        return;

    // search the audio item in the cache
    IAudioDictionary::iterator it = m_AudioCache.find(m_AudioItems[index]->GetName());

    // if found, remove it from cache
    if (it != m_AudioCache.end())
        m_AudioCache.erase(it);

    // delete audio item from scene
    delete m_AudioItems[index];
    m_AudioItems.erase(m_AudioItems.begin() + index);
}
//---------------------------------------------------------------------------
SceneItem* Scene::Get(const IItemID& id) const
{
    // iterate through groups and find item to get
    for (std::size_t i = 0; i < m_Groups.size(); ++i)
    {
        // not the group in which the item should be deleted?
        if (m_Groups[i]->m_Type != id.m_Group)
            continue;

        // is index out of bounds?
        if (id.m_Index >= m_Groups[i]->m_Items.size())
            return nullptr;

        // get scene item
        return m_Groups[i]->m_Items[id.m_Index];
    }

    return nullptr;
}
//---------------------------------------------------------------------------
SceneAudioItem* Scene::Get(std::size_t index) const
{
    // is index out of bounds?
    if (index >= m_AudioItems.size())
        return nullptr;

    // get audio scene item
    return m_AudioItems[index];
}
//---------------------------------------------------------------------------
std::size_t Scene::GetCount(IEGroupType group) const
{
    // iterate through groups and find item to get
    for (std::size_t i = 0; i < m_Groups.size(); ++i)
    {
        // not the group in which the item should be deleted?
        if (m_Groups[i]->m_Type != group)
            continue;

        return m_Groups[i]->m_Items.size();
    }

    return 0;
}
//---------------------------------------------------------------------------
std::size_t Scene::GetCount() const
{
    return m_AudioItems.size();
}
//---------------------------------------------------------------------------
SceneItem* Scene::SearchItem(const std::wstring& name) const
{
    // search for item in the cache
    IItemDictionary::const_iterator it = m_ItemCache.find(name);

    // found it?
    if (it != m_ItemCache.end())
        return it->second;

    // iterate through groups and search item in each of them
    for (std::size_t i = 0; i < m_Groups.size(); ++i)
        // iterate through items contained in group
        for (std::size_t j = 0; j < m_Groups[i]->m_Items.size(); ++j)
            // found the item?
            if (m_Groups[i]->m_Items[j]->GetName() == name)
            {
                // cache the item
                const_cast<IItemDictionary&>(m_ItemCache)[name] = m_Groups[i]->m_Items[j];

                return m_Groups[i]->m_Items[j];
            }

    return nullptr;
}
//---------------------------------------------------------------------------
SceneAudioItem* Scene::SearchAudio(const std::wstring& name) const
{
    // search for item in the cache
    IAudioDictionary::const_iterator it = m_AudioCache.find(name);

    // found it?
    if (it != m_AudioCache.end())
        return it->second;

    // iterate through audio items
    for (std::size_t i = 0; i < m_AudioItems.size(); ++i)
        // found the item?
        if (m_AudioItems[i]->GetName() == name)
        {
            // cache the item
            const_cast<IAudioDictionary&>(m_AudioCache)[name] = m_AudioItems[i];

            return m_AudioItems[i];
        }

    return nullptr;
}
//---------------------------------------------------------------------------
void Scene::DetectCollisions() const
{
    if (!m_fOnCollision)
        return;

    // iterate through groups
    for (std::size_t i = 0; i < m_Groups.size(); ++i)
        // iterate through scene items in group
        for (std::size_t j = 0; j < m_Groups[i]->m_Items.size(); ++j)
            // dynamic item?
            if (!m_Groups[i]->m_Items[j]->IsStatic())
                // iterate through item colliders
                for (std::size_t k = 0; k < m_Groups[i]->m_Items[j]->GetColliderCount(); ++k)
                    // detect collision between this item and all other items
                    DetectCollisionsForItem(m_Groups[i]->m_Items[j], m_Groups[i]->m_Items[j]->GetCollider(k));
}
//---------------------------------------------------------------------------
void Scene::Render(double elapsedTime)
{
    m_Time += elapsedTime;

    // process the missing frames in case elapsed time is higher than a frame duration
    while (m_Time >= m_FrameDuration)
    {
        ProcessPhysics(m_Time);
        m_Time -= m_FrameDuration;
    }

    ProcessPhysics(m_Time);

    if (m_fOnUpdateScene)
        m_fOnUpdateScene(this, elapsedTime);

    // no renderer?
    if (!m_pRenderer)
        return;

    // draw the scene
    m_pRenderer->BeginScene(m_Color,
                            (DWF_Renderer::Renderer::IESceneFlags)((unsigned)DWF_Renderer::Renderer::IESceneFlags::IE_SF_ClearColor |
                                                                   (unsigned)DWF_Renderer::Renderer::IESceneFlags::IE_SF_ClearDepth));

    if (m_fOnBeginScene)
        m_fOnBeginScene();

    IGroup* pPOVs = GetGroup(IEGroupType::IE_GT_POV);

    // no point of views?
    if (!pPOVs)
    {
        if (m_fOnEndScene)
            m_fOnEndScene();

        m_pRenderer->EndScene();
        return;
    }

    IGroup* pModels            = GetGroup(IEGroupType::IE_GT_Model);
    IGroup* pTransparentModels = GetGroup(IEGroupType::IE_GT_Transparent);

    // iterate through point of views
    for (std::size_t i = 0; i < pPOVs->m_Items.size(); ++i)
    {
        DWF_Math::Matrix4x4F viewMatrix = DWF_Math::Matrix4x4F::Identity();

        // calculate the view matrix to connect to the shaders
        if (pPOVs->m_Items[i])
            viewMatrix = pPOVs->m_Items[i]->GetMatrix();

        // do draw the skybox?
        if (m_pSkybox && m_pSkyboxShader)
            m_pRenderer->DrawSkybox(*m_pSkybox->m_Mesh[0], viewMatrix, m_pSkyboxShader);

        // iterate through models to render, and render each of them
        if (pModels)
            for (std::size_t j = 0; j < pModels->m_Items.size(); ++j)
                pModels->m_Items[j]->Render(viewMatrix, m_pRenderer);

        // iterate through transparent models to render, and render each of them
        if (pTransparentModels)
            for (std::size_t j = 0; j < pTransparentModels->m_Items.size(); ++j)
                pTransparentModels->m_Items[j]->Render(viewMatrix, m_pRenderer);
    }

    if (m_fOnEndScene)
        m_fOnEndScene();

    m_pRenderer->EndScene();
}
//---------------------------------------------------------------------------
void Scene::Set_OnBeginScene(ITfOnBeginScene fOnBeginScene)
{
    m_fOnBeginScene = fOnBeginScene;
}
//---------------------------------------------------------------------------
void Scene::Set_OnEndScene(ITfOnEndScene fOnEndScene)
{
    m_fOnEndScene = fOnEndScene;
}
//---------------------------------------------------------------------------
void Scene::Set_OnUpdatePhysics(ITfOnUpdatePhysics fOnUpdatePhysics)
{
    m_fOnUpdatePhysics = fOnUpdatePhysics;
}
//---------------------------------------------------------------------------
void Scene::Set_OnUpdateScene(ITfOnUpdateScene fOnUpdateScene)
{
    m_fOnUpdateScene = fOnUpdateScene;
}
//---------------------------------------------------------------------------
void Scene::Set_OnCollision(ITfOnCollision fOnCollision)
{
    m_fOnCollision = fOnCollision;
}
//---------------------------------------------------------------------------
Scene::IGroup* Scene::GetGroup(IEGroupType type) const
{
    // iterate through groups
    for (std::size_t i = 0; i < m_Groups.size(); ++i)
    {
        // is the group type to get?
        if (m_Groups[i]->m_Type != type)
            continue;

        return m_Groups[i];
    }

    return nullptr;
}
//---------------------------------------------------------------------------
void Scene::AddItem(IGroup* pGroup, SceneItem* pItem)
{
    // group does not exist?
    if (!pGroup)
        throw new std::exception("Invalid parameter - pGroup");

    // scene item is undefined?
    if (!pItem)
        throw new std::exception("Invalid parameter - pItem");

    // get the item name
    const std::wstring itemName = pItem->GetName();

    // item name should be defined
    if (itemName.empty())
        throw new std::exception("The item name is empty");

    // check if an item with the same name already exists
    if (SearchItem(itemName))
        throw new std::exception("An item with the same name already exists. The item name should be unique in the scene");

    // search if item already exists, in order to not add it twice
    for (std::size_t i = 0; i < pGroup->m_Items.size(); ++i)
        if (pGroup->m_Items[i] == pItem)
            return;

    // add item to scene
    pGroup->m_Items.push_back(pItem);

    // also add it to the cache
    m_ItemCache[itemName] = pItem;
}
//---------------------------------------------------------------------------
void Scene::ProcessPhysics(double elapsedTime) const
{
    // update the physics in the scene
    if (m_fOnUpdatePhysics)
        m_fOnUpdatePhysics(this, elapsedTime);

    // detect the collisions after scene objects have moved
    DetectCollisions();
}
//---------------------------------------------------------------------------
void Scene::DetectCollisionsForItem(SceneItem* pItem, DWF_Collider::Collider* pCollider) const
{
    if (!pItem)
        return;

    if (!pCollider)
        return;

    if (!m_fOnCollision)
        return;

    // get the item matrix and extract the position
    DWF_Math::Matrix4x4F itemMatrix = pItem->GetMatrix();
    DWF_Math::Vector3F   itemPos(itemMatrix.m_Table[3][0], itemMatrix.m_Table[3][1], itemMatrix.m_Table[3][2]);

    // reset the position in the matrix in order to keep only the rotation and scaling
    itemMatrix.m_Table[3][0] = 0.0f;
    itemMatrix.m_Table[3][1] = 0.0f;
    itemMatrix.m_Table[3][2] = 0.0f;

    // get the transformed collider
    std::unique_ptr<DWF_Collider::Collider> pModifiedCollider(pCollider->Transform(itemPos, itemMatrix));

    DWF_Math::Vector3F mtv;

    // iterate through groups
    for (std::size_t i = 0; i < m_Groups.size(); ++i)
        // iterate through scene items in group
        for (std::size_t j = 0; j < m_Groups[i]->m_Items.size(); ++j)
        {
            // found itself?
            if (m_Groups[i]->m_Items[j] == pItem)
                continue;

            // iterate through item colliders
            for (std::size_t k = 0; k < m_Groups[i]->m_Items[j]->GetColliderCount(); ++k)
            {
                // get collider
                DWF_Collider::Collider* pOtherCollider = m_Groups[i]->m_Items[j]->GetCollider(k);

                // get the item matrix and extract the position
                DWF_Math::Matrix4x4F otherItemMatrix = m_Groups[i]->m_Items[j]->GetMatrix();
                DWF_Math::Vector3F   otherItemPos(otherItemMatrix.m_Table[3][0], otherItemMatrix.m_Table[3][1], otherItemMatrix.m_Table[3][2]);

                // reset the position in the matrix in order to keep only the rotation and scaling
                otherItemMatrix.m_Table[3][0] = 0.0f;
                otherItemMatrix.m_Table[3][1] = 0.0f;
                otherItemMatrix.m_Table[3][2] = 0.0f;

                // get the transformed collider
                std::unique_ptr<DWF_Collider::Collider> pOtherModifiedCollider(pOtherCollider->Transform(otherItemPos, otherItemMatrix));

                // found a collision?
                if (DWF_Collider::GJK::Resolve(*pModifiedCollider, *pOtherModifiedCollider, mtv))
                    // raise collision event
                    m_fOnCollision(this, pItem, pModifiedCollider.get(), m_Groups[i]->m_Items[j], pOtherModifiedCollider.get(), mtv);
            }
        }
}
//---------------------------------------------------------------------------
