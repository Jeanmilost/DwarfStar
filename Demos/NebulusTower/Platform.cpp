/****************************************************************************
 * ==> Platform ------------------------------------------------------------*
 ****************************************************************************
 * Description : Nebulus tower platform                                     *
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

#include "Platform.h"

// classes
#include "DWF_CylinderCollider.h"
#include "DWF_ModelFactory.h"

using namespace Nebulus;

//---------------------------------------------------------------------------
// Platform
//---------------------------------------------------------------------------
Platform::Platform(DWF_Scene::Scene* pScene, const DWF_Math::Vector3F& pos) :
    Item(pScene),
    m_Pos(pos)
{}
//---------------------------------------------------------------------------
Platform::~Platform()
{}
//---------------------------------------------------------------------------
DWF_Model::Texture_OpenGL* Platform::LoadTexture(const std::string& fileName, bool is32bit) const
{
    return nullptr;
}
//---------------------------------------------------------------------------
bool Platform::Load(std::size_t                            i,
                    std::shared_ptr<DWF_Model::Model>&     pPlatform,
                    std::shared_ptr<DWF_Model::Model>&     pPlatformClosure,
              const std::shared_ptr<DWF_Renderer::Shader>& pShader)
{
    // get the scene
    DWF_Scene::Scene* pScene = GetScene();

    if (!pScene)
        return false;

    // create the platform item
    std::unique_ptr<DWF_Scene::SceneItem_Model> pModel = std::make_unique<DWF_Scene::SceneItem_Model>(L"scene_platform_" + std::to_wstring(i));
    pModel->SetStatic(false);
    pModel->SetVisible(true);
    pModel->SetModel(pPlatform);
    pModel->SetShader(pShader);
    pModel->SetPos(m_Pos);
    pModel->SetRoll(0.0f);
    pModel->SetPitch(0.0f);
    pModel->SetYaw(0.0f);
    pModel->SetScale(DWF_Math::Vector3F(1.0f, 1.0f, 1.0f));

    // create the platform collider
    std::unique_ptr<DWF_Collider::Cylinder_Collider> pPlatformCollider = std::make_unique<DWF_Collider::Cylinder_Collider>();
    pPlatformCollider->SetCylinder(0.2f, 0.05f, -0.05f);
    pModel->AddCollider(pPlatformCollider.get());
    pPlatformCollider.release();

    // set the model to the scene
    pScene->Add(pModel.get(), false);
    pModel.release();

    // create the platform top item
    pModel = std::make_unique<DWF_Scene::SceneItem_Model>(L"scene_platform_top_" + std::to_wstring(i));
    pModel->SetStatic(false);
    pModel->SetVisible(true);
    pModel->SetModel(pPlatformClosure);
    pModel->SetShader(pShader);
    pModel->SetPos(DWF_Math::Vector3F(m_Pos.m_X, m_Pos.m_Y + 0.05f, m_Pos.m_Z));
    pModel->SetRoll(-(float)M_PI / 2.0f);
    pModel->SetPitch(0.0f);
    pModel->SetYaw(0.0f);
    pModel->SetScale(DWF_Math::Vector3F(1.0f, 1.0f, 1.0f));

    // set the model to the scene
    pScene->Add(pModel.get(), false);
    pModel.release();

    // create the platform bottom item
    pModel = std::make_unique<DWF_Scene::SceneItem_Model>(L"scene_platform_bottom_" + std::to_wstring(i));
    pModel->SetStatic(false);
    pModel->SetVisible(true);
    pModel->SetModel(pPlatformClosure);
    pModel->SetShader(pShader);
    pModel->SetPos(DWF_Math::Vector3F(m_Pos.m_X, m_Pos.m_Y - 0.05f, m_Pos.m_Z));
    pModel->SetRoll((float)M_PI / 2.0f);
    pModel->SetPitch(0.0f);
    pModel->SetYaw(0.0f);
    pModel->SetScale(DWF_Math::Vector3F(1.0f, 1.0f, 1.0f));

    // set the model to the scene
    pScene->Add(pModel.get(), false);
    pModel.release();

    return true;
}
//---------------------------------------------------------------------------
