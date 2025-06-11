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

#include "Entity.h"

// std
#include <algorithm>

// classes
#include "DWF_BoxCollider.h"
#include "DWF_SceneItemStaticAsset.h"

using namespace ShootEmUp;

//---------------------------------------------------------------------------
// Entity
//---------------------------------------------------------------------------
Entity::Entity(const std::wstring&                                 name,
               const std::shared_ptr<DWF_Model::ModelFormat>&      pModel,
               const std::shared_ptr<DWF_Model::Model>&            pColliderModel,
               const std::shared_ptr<DWF_Renderer::Shader_OpenGL>& pTexShader,
               const std::shared_ptr<DWF_Renderer::Shader_OpenGL>& pColShader) :
    m_pModel(pModel),
    m_pColliderModel(pColliderModel),
    m_pTexShader(pTexShader),
    m_pColShader(pColShader),
    m_Name(name)
{}
//---------------------------------------------------------------------------
Entity::~Entity()
{}
//---------------------------------------------------------------------------
void Entity::AddAsset(DWF_Scene::Spawner::IItem* pItem, DWF_Scene::Scene& scene, float x, float y)
{
    m_OldPos = DWF_Math::Vector3F(x, y, -40.0f);

    // create the asset scene model item
    std::unique_ptr<DWF_Scene::SceneItem_StaticAsset> pStaticModel = std::make_unique<DWF_Scene::SceneItem_StaticAsset>(GetModelNameInScene());
    pStaticModel->SetStatic(true);
    pStaticModel->SetModel(m_pModel);
    pStaticModel->SetShader(m_pTexShader);
    pStaticModel->SetPos(DWF_Math::Vector3F(x, y, -40.0f));
    pStaticModel->SetRoll(-0.25f);
    pStaticModel->SetPitch((float)(M_PI / 2.0));
    pStaticModel->SetYaw((float)(M_PI / 2.0));
    pStaticModel->SetScale(DWF_Math::Vector3F(2.0f, 2.0f, 2.0f));

    // set the model to the scene
    scene.Add(pStaticModel.get(), false);
    pItem->m_pModel = pStaticModel.release();

    // create the asset collider model item
    std::unique_ptr<DWF_Scene::SceneItem_Model> pModel = std::make_unique<DWF_Scene::SceneItem_Model>(GetColliderNameInScene());
    pModel->SetStatic(false);
    pModel->SetVisible(false);
    pModel->SetModel(m_pColliderModel);
    pModel->SetShader(m_pColShader);
    pModel->SetPos(DWF_Math::Vector3F(x - 0.35f, y, -40.0f));
    pModel->SetRoll(m_Angle);
    pModel->SetPitch(0.0f);
    pModel->SetYaw(0.0f);
    pModel->SetScale(DWF_Math::Vector3F(1.0f, 1.0f, 1.0f));

    // create the asset box collider
    std::unique_ptr<DWF_Collider::Box_Collider> pBoxCol = std::make_unique<DWF_Collider::Box_Collider>(DWF_Math::Vector3F(),
                                                                                                       DWF_Math::Matrix4x4F::Identity(),
                                                                                                       DWF_Math::Vector3F(-2.0f, -1.0f, -0.5f),
                                                                                                       DWF_Math::Vector3F(2.0f, 1.0f, 0.75f));
    pModel->AddCollider(pBoxCol.get());
    pBoxCol.release();

    // set the model to the scene
    scene.Add(pModel.get(), false);
    pItem->m_pCollider = pModel.release();
}
//---------------------------------------------------------------------------
void Entity::Move(Sequencer* pSequencer, DWF_Scene::Spawner::IItem* pItem, double elapsedTime)
{
    const float spaceshipRotationSpeed = 0.0025f;

    const DWF_Math::Vector3F position = pSequencer->GetPosition(m_Name, elapsedTime);

    if (position.m_Y != m_OldPos.m_Y)
        m_Angle = std::max(m_Angle - (spaceshipRotationSpeed * (float)elapsedTime), 0.0f);
    else
        m_Angle = std::min(m_Angle + (spaceshipRotationSpeed * (float)elapsedTime), (float)(M_PI / 2.0));

    if (pItem->m_pCollider)
    {
        pItem->m_pCollider->SetPos(position);
        pItem->m_pCollider->SetRoll(m_Angle);
    }

    if (pItem->m_pModel)
    {
        pItem->m_pModel->SetPos(position);
        pItem->m_pModel->SetPitch(m_Angle);
    }

    m_OldPos = position;
}
//---------------------------------------------------------------------------
