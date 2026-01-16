/****************************************************************************
 * ==> Tower ---------------------------------------------------------------*
 ****************************************************************************
 * Description : Nebulus tower                                              *
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

#include "Tower.h"

// std
#include <memory>

// classes
#include "DWF_Buffer.h"
#include "DWF_PixelBuffer.h"
#include "DWF_Texture.h"
#include "DWF_ModelFactory.h"

using namespace Nebulus;

//---------------------------------------------------------------------------
// Tower
//---------------------------------------------------------------------------
Tower::Tower(DWF_Scene::Scene* pScene) :
    Item(pScene)
{}
//---------------------------------------------------------------------------
Tower::~Tower()
{}
//------------------------------------------------------------------------------
DWF_Model::Texture_OpenGL* Tower::LoadTexture(const std::string& fileName, bool is32bit) const
{
    std::unique_ptr<DWF_Buffer::PixelBuffer> pPixelBuffer = std::make_unique<DWF_Buffer::PixelBuffer>();

    // load the texture
    if (!pPixelBuffer->FromPng(fileName, true))
        return nullptr;

    if (!pPixelBuffer->m_pData)
        return nullptr;

    // create the texture
    std::unique_ptr<DWF_Model::Texture_OpenGL> pTexture(new DWF_Model::Texture_OpenGL());
    pTexture->m_Width     = (int)pPixelBuffer->m_Width;
    pTexture->m_Height    = (int)pPixelBuffer->m_Height;
    pTexture->m_Format    = pPixelBuffer->m_BytePerPixel == 3 ? DWF_Model::Texture::IEFormat::IE_FT_24bit : DWF_Model::Texture::IEFormat::IE_FT_32bit;
    pTexture->m_WrapMode  = DWF_Model::Texture::IEWrapMode::IE_WM_Repeat;
    pTexture->m_MinFilter = DWF_Model::Texture::IEMinFilter::IE_MI_Linear;
    pTexture->m_MagFilter = DWF_Model::Texture::IEMagFilter::IE_MA_Linear;
    pTexture->Create(pPixelBuffer->m_pData);

    return pTexture.release();
}
//---------------------------------------------------------------------------
bool Tower::Load(const std::shared_ptr<DWF_Renderer::Shader>& pShader)
{
    // get the scene
    DWF_Scene::Scene* pScene = GetScene();

    if (!pScene)
        return false;

    DWF_Model::VertexFormat  vf;
    DWF_Model::VertexCulling vc;
    DWF_Model::Material      mat;

    // set vertex format for textured models
    vf.m_Type   = DWF_Model::VertexFormat::IEType::IE_VT_Triangles;
    vf.m_Format = (DWF_Model::VertexFormat::IEFormat)((int)DWF_Model::VertexFormat::IEFormat::IE_VF_Colors |
                                                      (int)DWF_Model::VertexFormat::IEFormat::IE_VF_TexCoords);

    vc.m_Type = DWF_Model::VertexCulling::IECullingType::IE_CT_Front;

    // create material
    mat.m_Color.m_B = 1.0f;
    mat.m_Color.m_G = 1.0f;
    mat.m_Color.m_R = 1.0f;
    mat.m_Color.m_A = 1.0f;
    mat.m_uScale    = 10.0f;
    mat.m_vScale    = 10.0f;

    // create the tower
    std::shared_ptr<DWF_Model::Model> pTower(DWF_Model::Factory::GetCylinder(1.2f, 1.2f, 10.0f, 50, vf, vc, mat));

    // attach a function to the model to load the texture
    if (m_fOnAttachTextureFunction)
        m_fOnAttachTextureFunction(pTower);

    // create the tower model item
    std::unique_ptr<DWF_Scene::SceneItem_Model> pModel = std::make_unique<DWF_Scene::SceneItem_Model>(L"scene_tower");
    pModel->SetStatic(true);
    pModel->SetVisible(true);
    pModel->SetModel(pTower);
    pModel->SetShader(pShader);
    pModel->SetPos(DWF_Math::Vector3F(m_X, m_Y, m_Z));
    pModel->SetRoll(0.0f);
    pModel->SetPitch(0.0f);
    pModel->SetYaw(0.0f);
    pModel->SetScale(DWF_Math::Vector3F(1.0f, 1.0f, 1.0f));

    // set the model to the scene
    pScene->Add(pModel.get(), false);
    pModel.release();

    return true;
}
//---------------------------------------------------------------------------
void Tower::Set_OnAttachTextureFunction(ITfOnAttachTextureFunction fHandler)
{
    m_fOnAttachTextureFunction = fHandler;
}
//---------------------------------------------------------------------------
