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
void Entity::AddAsset(DWF_Scene::Spawner::IItem* pItem, DWF_Scene::Scene& scene, float x, float y, bool showColliders)
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
    pModel->SetVisible(showColliders);
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
void Entity::AddSequence(Sequencer* pSequencer, IESequenceType sequenceType, const DWF_Math::Vector3F& startPos) const
{
    // create a sequence
    std::unique_ptr<ShootEmUp::Sequencer::ISequence> pSequence = std::make_unique<ShootEmUp::Sequencer::ISequence>();
    pSequence->m_Name                                          = m_Name;
    pSequence->m_Position                                      = startPos;

    // dispatch the sequence type
    switch (sequenceType)
    {
        case IESequenceType::IE_ST_BottomToTop:
        {
            // first command, move the entity from the screen right on the bottom
            std::unique_ptr<ShootEmUp::Sequencer::ICommand> pCmd = std::make_unique<ShootEmUp::Sequencer::ICommand>();
            pCmd->m_Direction                                    = DWF_Math::Vector3F(-1.0f, 0.0f, 0.0f);
            pCmd->m_Length                                       = 35.0f;
            pCmd->m_Time                                         = 2000.0;
            pSequence->m_Pattern.push_back(pCmd.get());
            pCmd.release();

            // second command, move the entity from the bottom-left to the top-right
            pCmd              = std::make_unique<ShootEmUp::Sequencer::ICommand>();
            pCmd->m_Direction = DWF_Math::Vector3F(1.0f, 0.75f, 0.0f);
            pCmd->m_Length    = 35.0f;
            pCmd->m_Time      = 2000.0;
            pSequence->m_Pattern.push_back(pCmd.get());
            pCmd.release();

            // third command, move the entity from the screen right on the top
            pCmd              = std::make_unique<ShootEmUp::Sequencer::ICommand>();
            pCmd->m_Direction = DWF_Math::Vector3F(-1.0f, 0.0f, 0.0f);
            pCmd->m_Length    = 45.0f;
            pCmd->m_Time      = 2000.0;
            pSequence->m_Pattern.push_back(pCmd.get());
            pCmd.release();

            // add the sequence to the sequencer
            pSequencer->Add(pSequence.get());
            pSequence.release();

            break;
        }

        case IESequenceType::IE_ST_TopToBottom:
        {
            // first command, move the entity from the screen right on the bottom
            std::unique_ptr<ShootEmUp::Sequencer::ICommand> pCmd = std::make_unique<ShootEmUp::Sequencer::ICommand>();
            pCmd->m_Direction                                    = DWF_Math::Vector3F(-1.0f, 0.0f, 0.0f);
            pCmd->m_Length                                       = 35.0f;
            pCmd->m_Time                                         = 2000.0;
            pSequence->m_Pattern.push_back(pCmd.get());
            pCmd.release();

            // second command, move the entity from the bottom-left to the top-right
            pCmd              = std::make_unique<ShootEmUp::Sequencer::ICommand>();
            pCmd->m_Direction = DWF_Math::Vector3F(1.0f, -0.75f, 0.0f);
            pCmd->m_Length    = 35.0f;
            pCmd->m_Time      = 2000.0;
            pSequence->m_Pattern.push_back(pCmd.get());
            pCmd.release();

            // third command, move the entity from the screen right on the top
            pCmd              = std::make_unique<ShootEmUp::Sequencer::ICommand>();
            pCmd->m_Direction = DWF_Math::Vector3F(-1.0f, 0.0f, 0.0f);
            pCmd->m_Length    = 45.0f;
            pCmd->m_Time      = 2000.0;
            pSequence->m_Pattern.push_back(pCmd.get());
            pCmd.release();

            // add the sequence to the sequencer
            pSequencer->Add(pSequence.get());
            pSequence.release();

            break;
        }

        case IESequenceType::IE_ST_BezierCurve1:
        {
            // first command, move the entity from the screen right on the bottom
            std::unique_ptr<ShootEmUp::Sequencer::ICommand> pCmd = std::make_unique<ShootEmUp::Sequencer::ICommand>();
            pCmd->m_Curve     = ShootEmUp::Sequencer::IECurve::IE_C_CubicBezierCurve;
            pCmd->m_Direction = DWF_Math::Vector3F(-1.0f,  0.0f,   0.0f);
            pCmd->m_Control1  = DWF_Math::Vector3F( 9.0f,  15.0f, -40.0f);
            pCmd->m_Control2  = DWF_Math::Vector3F(-9.0f, -15.0f, -40.0f);
            pCmd->m_Length    = 45.0f;
            pCmd->m_Time      = 2000.0;
            pSequence->m_Pattern.push_back(pCmd.get());
            pCmd.release();

            // add the sequence to the sequencer
            pSequencer->Add(pSequence.get());
            pSequence.release();

            break;
        }

        case IESequenceType::IE_ST_BezierCurve2:
        {
            // first command, move the entity from the screen right on the bottom
            std::unique_ptr<ShootEmUp::Sequencer::ICommand> pCmd = std::make_unique<ShootEmUp::Sequencer::ICommand>();
            pCmd->m_Curve     = ShootEmUp::Sequencer::IECurve::IE_C_QuadraticBezierCurve;
            pCmd->m_Direction = DWF_Math::Vector3F(-1.0f,   0.6f,   0.0f);
            pCmd->m_Control1  = DWF_Math::Vector3F( 19.0f, 15.0f, -40.0f);
            pCmd->m_Length    = 45.0f;
            pCmd->m_Time      = 2000.0;
            pSequence->m_Pattern.push_back(pCmd.get());
            pCmd.release();

            // add the sequence to the sequencer
            pSequencer->Add(pSequence.get());
            pSequence.release();

            break;
        }

        default:
            break;
    }
}
//---------------------------------------------------------------------------
void Entity::Move(Sequencer* pSequencer, DWF_Scene::Spawner::IItem* pItem, double elapsedTime)
{
    // get the current rotation speed and entity position
    const float              rotationSpeed = 0.0025f;
    const DWF_Math::Vector3F position      = pSequencer->GetPosition(m_Name, elapsedTime);

    // check if entity moved vertically, if yes, rotate the model
    if (position.m_Y != m_OldPos.m_Y)
        m_Angle = std::max(m_Angle - (rotationSpeed * (float)elapsedTime), 0.0f);
    else
        m_Angle = std::min(m_Angle + (rotationSpeed * (float)elapsedTime), (float)(M_PI / 2.0));

    // apply the position to the model
    if (pItem->m_pModel)
    {
        pItem->m_pModel->SetPos(position);
        pItem->m_pModel->SetPitch(m_Angle);
    }

    // apply the rotation to the collider
    if (pItem->m_pCollider)
    {
        pItem->m_pCollider->SetPos(position);
        pItem->m_pCollider->SetRoll(m_Angle);
    }

    // keep old position and elapsed time
    m_OldPos          = position;
    m_LastElapsedTime = elapsedTime;
}
//---------------------------------------------------------------------------
void Entity::Break(Sequencer* pSequencer)
{
    // get the current known position
    const DWF_Math::Vector3F position = pSequencer->GetPosition(m_Name, m_LastElapsedTime);

    // delete the currently running sequence
    pSequencer->Delete(m_Name);

    // create the dying sequence
    std::unique_ptr<ShootEmUp::Sequencer::ISequence> pSequence = std::make_unique<ShootEmUp::Sequencer::ISequence>();
    pSequence->m_Name     = m_Name;
    pSequence->m_Position = position;

    // add the sequence command
    std::unique_ptr<ShootEmUp::Sequencer::ICommand> pCmd = std::make_unique<ShootEmUp::Sequencer::ICommand>();
    pCmd->m_Direction = DWF_Math::Vector3F(0.0f, 0.0f, -1.0f);
    pCmd->m_Length    = 50.0f;
    pCmd->m_Time      = 500.0;
    pSequence->m_Pattern.push_back(pCmd.get());
    pCmd.release();

    // add the sequence to the sequencer
    pSequencer->Add(pSequence.get());
    pSequence.release();
}
//---------------------------------------------------------------------------
