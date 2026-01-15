/****************************************************************************
 * ==> Platforms -----------------------------------------------------------*
 ****************************************************************************
 * Description : Nebulus tower platforms                                    *
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

#include "Platforms.h"

// classes
#include "DWF_CylinderCollider.h"
#include "DWF_ModelFactory.h"

using namespace Nebulus;

//---------------------------------------------------------------------------
// Platforms
//---------------------------------------------------------------------------
Platforms::Platforms(DWF_Scene::Scene* pScene) :
    Item(pScene)
{}
//---------------------------------------------------------------------------
Platforms::~Platforms()
{}
//---------------------------------------------------------------------------
DWF_Model::Texture_OpenGL* Platforms::LoadTexture(const std::string& fileName, bool is32bit) const
{
    return nullptr;
}
//---------------------------------------------------------------------------
bool Platforms::Load(const std::shared_ptr<DWF_Renderer::Shader>& pShader)
{
    // get the scene
    DWF_Scene::Scene* pScene = GetScene();

    if (!pScene)
        return false;

    DWF_Model::VertexFormat  vf;
    DWF_Model::VertexCulling vc;
    DWF_Model::Material      mat;

    // set vertex format for colored models
    vf.m_Format = DWF_Model::VertexFormat::IEFormat::IE_VF_Colors;

    // create material
    mat.m_Color.m_B = 0.41f;
    mat.m_Color.m_G = 0.38f;
    mat.m_Color.m_R = 0.37f;
    mat.m_Color.m_A = 1.0f;

    // create the tower platform model
    std::shared_ptr<DWF_Model::Model> pPlatformModel(DWF_Model::Factory::GetCylinder(0.2f, 0.2f, 0.1f, 15, vf, vc, mat));

    // create material
    mat.m_Color.m_B = 0.81f;
    mat.m_Color.m_G = 0.78f;
    mat.m_Color.m_R = 0.77f;
    mat.m_Color.m_A = 1.0f;

    // create the tower platform model
    std::shared_ptr<DWF_Model::Model> pPlatformClosureModel(DWF_Model::Factory::GetDisk(0.0f, 0.0f, 0.2f, 15, vf, vc, mat));

    const std::size_t platformCount = 22;
    const float       step          = ((float)M_PI * 2.0f) / (float)platformCount;
    const float       heightStep    = 0.0f;// 0.05f;

    for (std::size_t i = 0; i < platformCount; ++i)
    {
        const float x =  1.4f  * std::sinf(i * step);
        const float y = -0.44f + (i >= (platformCount >> 1) ? (platformCount - i) * heightStep : i * heightStep);
        const float z =  1.4f  * std::cosf(i * step);

        // create the platform and add it to the scene
        std::unique_ptr<Platform> pPlatform = std::make_unique<Platform>(pScene, DWF_Math::Vector3F(x, y, z));

        if (!pPlatform->Load(i, pPlatformModel, pPlatformClosureModel, pShader))
            return false;
    }

    return true;
}
//---------------------------------------------------------------------------
