/****************************************************************************
 * ==> Water ---------------------------------------------------------------*
 ****************************************************************************
 * Description : Nebulus water effect                                       *
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

#include "Water.h"

// classes
#include "DWF_ModelFactory.h"

using namespace Nebulus;

//---------------------------------------------------------------------------
// Water
//---------------------------------------------------------------------------
Water::Water(DWF_Scene::Scene* pScene) :
    Item(pScene)
{}
//---------------------------------------------------------------------------
Water::~Water()
{}
//------------------------------------------------------------------------------
DWF_Model::Texture_OpenGL* Water::LoadTexture(const std::string& fileName, bool is32bit) const
{
    return nullptr;
}
//------------------------------------------------------------------------------
bool Water::Load(const std::shared_ptr<DWF_Renderer::Shader>& pShader)
{
    // get the scene
    DWF_Scene::Scene* pScene = GetScene();

    if (!pScene)
        return false;

    DWF_Model::VertexFormat  vf;
    DWF_Model::VertexCulling vc;
    DWF_Model::Material      mat;

    // set vertex format for colored models
    vf.m_Format = DWF_Model::VertexFormat::IEFormat::IE_VF_TexCoords;

    // create material
    mat.m_Color.m_B = 1.0f;
    mat.m_Color.m_G = 1.0f;
    mat.m_Color.m_R = 1.0f;
    mat.m_Color.m_A = 1.0f;

    // create the water plan
    std::shared_ptr<DWF_Model::Model> pWater(DWF_Model::Factory::GetWaterSurface(100.0f, 100.0f, 750, vf, vc, mat));

    // create the water item
    std::unique_ptr<DWF_Scene::SceneItem_Model> pModel = std::make_unique<DWF_Scene::SceneItem_Model>(L"scene_water");
    pModel->SetStatic(true);
    pModel->SetVisible(true);
    pModel->SetModel(pWater);
    pModel->SetShader(pShader);
    pModel->SetPos(DWF_Math::Vector3F(0.0f, -1.0f, 0.0f));
    pModel->SetRoll(0.0f);
    pModel->SetPitch(0.0f);
    pModel->SetYaw(0.0f);
    pModel->SetScale(DWF_Math::Vector3F(1.0f, 1.0f, 1.0f));

    // set the model to the scene
    pScene->Add(pModel.get(), false);
    pModel.release();

    pShader->Use(true);

    // configure water
    glUniform1f(glGetUniformLocation((GLuint)pShader->GetProgramID(), "dwf_uWaveStrength"),  0.1f);
    glUniform3f(glGetUniformLocation((GLuint)pShader->GetProgramID(), "dwf_LightDir"),      -0.3f, -1.0f, -0.3f);
    glUniform3f(glGetUniformLocation((GLuint)pShader->GetProgramID(), "dwf_WaterColor"),     0.1f,  0.3f,  0.4f);
    glUniform3f(glGetUniformLocation((GLuint)pShader->GetProgramID(), "dwf_DeepWaterColor"), 0.0f,  0.1f,  0.2f);
    glUniform1f(glGetUniformLocation((GLuint)pShader->GetProgramID(), "dwf_WaterClearness"), 0.15f);

    pShader->Use(false);

    return true;
}
//------------------------------------------------------------------------------
