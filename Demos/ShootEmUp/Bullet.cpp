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

#include "Bullet.h"

// std
#include <algorithm>

// classes
#include "DWF_SphereCollider.h"
#include "DWF_SceneItemStaticAsset.h"

using namespace ShootEmUp;

//---------------------------------------------------------------------------
// Bullet
//---------------------------------------------------------------------------
Bullet::Bullet(const std::wstring&                                 name,
               const std::shared_ptr<DWF_Model::Model>&            pModel,
               const std::shared_ptr<DWF_Renderer::Shader_OpenGL>& pColShader) :
    m_pModel(pModel),
    m_pColShader(pColShader),
    m_Name(name)
{}
//---------------------------------------------------------------------------
Bullet::~Bullet()
{}
//---------------------------------------------------------------------------
void Bullet::AddColliderToIgnore(const std::wstring& name)
{
    m_CollidersToIgnore.insert(name);
}
//---------------------------------------------------------------------------
bool Bullet::DoIgnoreCollider(const std::wstring& name) const
{
    return (m_CollidersToIgnore.find(name) != m_CollidersToIgnore.end());
}
//---------------------------------------------------------------------------
void Bullet::AddAsset(DWF_Scene::Scene& scene, float x, float y)
{
    m_OldPos = DWF_Math::Vector3F(x, y, -40.0f);

    // create the asset scene model item
    std::unique_ptr<DWF_Scene::SceneItem_Model> pModel = std::make_unique<DWF_Scene::SceneItem_Model>(GetModelNameInScene());
    pModel->SetStatic(false);
    pModel->SetVisible(true);
    pModel->SetModel(m_pModel);
    pModel->SetShader(m_pColShader);
    pModel->SetPos(DWF_Math::Vector3F(x, y, -40.0f));
    pModel->SetRoll(0.0f);
    pModel->SetPitch(0.0f);
    pModel->SetYaw(0.0f);
    pModel->SetScale(DWF_Math::Vector3F(1.0f, 1.0f, 1.0f));

    // create the asset collider
    std::unique_ptr<DWF_Collider::Sphere_Collider> pSphereCol =
            std::make_unique<DWF_Collider::Sphere_Collider>(DWF_Math::Vector3F(),
                                                            DWF_Math::Matrix4x4F::Identity(),
                                                            0.25f);
    pModel->AddCollider(pSphereCol.get());
    pSphereCol.release();

    // set the model to the scene
    scene.Add(pModel.get(), false);
    m_pSceneItem = pModel.release();
}
//---------------------------------------------------------------------------
void Bullet::AddSequence(Sequencer* pSequencer, const DWF_Math::Vector3F& startPos) const
{
    // create a sequence
    std::unique_ptr<ShootEmUp::Sequencer::ISequence> pSequence = std::make_unique<ShootEmUp::Sequencer::ISequence>();
    pSequence->m_Name                                          = m_Name;
    pSequence->m_Position                                      = startPos;

    // add the sequence command
    std::unique_ptr<ShootEmUp::Sequencer::ICommand> pCmd = std::make_unique<ShootEmUp::Sequencer::ICommand>();
    pCmd->m_Direction                                    = DWF_Math::Vector3F(1.0f, 0.0f, 0.0f);
    pCmd->m_Length                                       = 40.0f;
    pCmd->m_Time                                         = 1000.0;
    pSequence->m_Pattern.push_back(pCmd.get());
    pCmd.release();

    // add the sequence to the sequencer
    pSequencer->Add(pSequence.get());
    pSequence.release();
}
//---------------------------------------------------------------------------
void Bullet::DeleteAsset(DWF_Scene::Scene& scene)
{
    if (!m_pSceneItem)
        return;

    scene.Delete(m_pSceneItem);
}
//---------------------------------------------------------------------------
void Bullet::Move(Sequencer* pSequencer, double elapsedTime)
{
    // get the entity position
    const DWF_Math::Vector3F position = pSequencer->GetPosition(m_Name, elapsedTime);

    // apply the position to the model
    if (m_pSceneItem)
        // was bullet sequence broken? (i.e. it have hit something)
        if (!m_Broken)
            m_pSceneItem->SetPos(position);
        else
            // yes, just move the asset out of the screen and let the sequence finish. This is a lazy way, not very elegant, but it avoid several
            // more complicated operations to reach the same result
            m_pSceneItem->SetPos(DWF_Math::Vector3F(999.0f, 999.0f, 999.0f));

    // keep old position
    m_OldPos = position;
}
//---------------------------------------------------------------------------
void Bullet::Break()
{
    m_Broken = true;
}
//---------------------------------------------------------------------------
