/****************************************************************************
 * ==> Player --------------------------------------------------------------*
 ****************************************************************************
 * Description : Nebulus player                                             *
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

#include "Player.h"

 // std
#include <memory>

// classes
#include "DWF_Buffer.h"
#include "DWF_PixelBuffer.h"
#include "DWF_Texture.h"
#include "DWF_Model.h"
#include "DWF_ModelFactory.h"
#include "DWF_CapsuleCollider.h"
#include "DWF_Sound_OpenAL.h"

// demo
#include "Main.h"

using namespace Nebulus;

//---------------------------------------------------------------------------
// Player
//---------------------------------------------------------------------------
Player::Player(DWF_Scene::Scene* pScene) :
    Item(pScene)
{}
//---------------------------------------------------------------------------
Player::~Player()
{}
//---------------------------------------------------------------------------
DWF_Model::Texture_OpenGL* Player::LoadTexture(const std::string& fileName, bool is32bit) const
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
    pTexture->m_WrapMode  = DWF_Model::Texture::IEWrapMode::IE_WM_Clamp;
    pTexture->m_MinFilter = DWF_Model::Texture::IEMinFilter::IE_MI_Nearest;
    pTexture->m_MagFilter = DWF_Model::Texture::IEMagFilter::IE_MA_Nearest;
    pTexture->Create(pPixelBuffer->m_pData);

    return pTexture.release();
}
//---------------------------------------------------------------------------
bool Player::Load(const std::shared_ptr<DWF_Renderer::Shader>& pModelShader,
                  const std::shared_ptr<DWF_Renderer::Shader>& pColliderShader)
{
    // get the scene
    DWF_Scene::Scene* pScene = GetScene();

    if (!pScene)
        return false;

    // create the player arcball
    std::unique_ptr<DWF_Scene::Arcball> pArcball = std::make_unique<DWF_Scene::Arcball>();
    pArcball->m_Position = DWF_Math::Vector3F(m_xPos, m_yPos, m_zPos);
    pArcball->m_AngleX   = 0.0f;
    pArcball->m_AngleY   = (float)(M_PI / 2.0);
    pArcball->m_Radius   = 4.0f;

    // create an arcball point of view
    std::unique_ptr<DWF_Scene::SceneItem_PointOfView> pPOV = std::make_unique<DWF_Scene::SceneItem_PointOfView>(L"scene_arcball");
    pPOV->Set(pArcball.get());
    pArcball.release();

    // set the point of view to the scene
    pScene->Add(pPOV.get());
    pPOV.release();

    std::shared_ptr<DWF_Model::IQM> pIqm = std::make_shared<DWF_Model::IQM>();

    // attach a function to the model to load the texture
    if (m_fOnAttachTextureFunction)
        m_fOnAttachTextureFunction(pIqm);

    // load player IQM model
    if (!pIqm->Open("..\\..\\Resources\\Model\\Robot\\Robot.iqm"))
        return false;

    // create the player model item
    std::unique_ptr<DWF_Scene::SceneItem_AnimAsset> pAnim = std::make_unique<DWF_Scene::SceneItem_AnimAsset>(L"scene_player_model");
    pAnim->SetStatic(true);
    pAnim->SetShader(pModelShader);
    pAnim->SetPos(DWF_Math::Vector3F(m_xPos - m_Distance, m_yPos - 0.25f, m_zPos));
    pAnim->SetRoll(-(float)M_PI / 2.0f);
    pAnim->SetPitch((float)M_PI);
    pAnim->SetYaw(0.0f);
    pAnim->SetScale(DWF_Math::Vector3F(0.1f, 0.1f, 0.1f));
    pAnim->SetModel(pIqm);
    pAnim->AddAnim((std::size_t)0, 0, 0,  0.0,    false); // idle
    pAnim->AddAnim((std::size_t)0, 0, 60, 0.0055, true);  // walk
    pAnim->Set_OnFrame(std::bind(&Player::OnFrame, this, std::placeholders::_1, std::placeholders::_2));
    pAnim->Set_OnEndReached(std::bind(&Player::OnEndReached, this, std::placeholders::_1, std::placeholders::_2));

    pAnim->SelectAnim(0);

    // set the model to the scene
    pScene->Add(pAnim.get(), false);
    pAnim.release();

    DWF_Model::VertexFormat  vf;
    DWF_Model::VertexCulling vc;
    DWF_Model::Material      mat;

    // set vertex format for textured models
    vf.m_Type   =  DWF_Model::VertexFormat::IEType::IE_VT_Triangles;
    vf.m_Format = (DWF_Model::VertexFormat::IEFormat)((int)DWF_Model::VertexFormat::IEFormat::IE_VF_Colors |
                                                      (int)DWF_Model::VertexFormat::IEFormat::IE_VF_TexCoords);

    // set vertex format for colored models
    vf.m_Format = DWF_Model::VertexFormat::IEFormat::IE_VF_Colors;

    // create material
    mat.m_Color.m_B = 1.0f;
    mat.m_Color.m_G = 0.0f;
    mat.m_Color.m_R = 0.0f;
    mat.m_Color.m_A = 1.0f;

    // create the player capsule
    std::shared_ptr<DWF_Model::Model> pPlayerCapsule(DWF_Model::Factory::GetCapsule(0.15f, 0.15f, 15.0f, vf, vc, mat));

    // create the capsule model item
    std::unique_ptr<DWF_Scene::SceneItem_Model> pModel = std::make_unique<DWF_Scene::SceneItem_Model>(L"scene_player_collider");
    pModel->SetStatic(false);
    pModel->SetVisible(false);
    pModel->SetModel(pPlayerCapsule);
    pModel->SetShader(pColliderShader);
    pModel->SetPos(DWF_Math::Vector3F(m_xPos - m_Distance, m_yPos - 0.25f, m_zPos));
    pModel->SetRoll(0.0f);
    pModel->SetPitch(0.0f);
    pModel->SetYaw(0.0f);
    pModel->SetScale(DWF_Math::Vector3F(1.0f, 1.0f, 1.0f));

    // create the player collider
    std::unique_ptr<DWF_Collider::Capsule_Collider> pPlayerCollider = std::make_unique<DWF_Collider::Capsule_Collider>();
    pPlayerCollider->SetCapsule(0.15f, 0.15f, 0.0f, true);
    pModel->AddCollider(pPlayerCollider.get());
    pPlayerCollider.release();

    // set the model to the scene
    pScene->Add(pModel.get(), false);
    pModel.release();

    // load footsteps sound
    std::unique_ptr<DWF_Audio::Sound_OpenAL> pSound = std::make_unique<DWF_Audio::Sound_OpenAL>();
    pSound->OpenWav(L"..\\..\\Resources\\Sound\\footsteps_metal.wav");
    pSound->Loop(false);

    // create a sound item
    std::unique_ptr<DWF_Scene::SceneAudioItem> pSoundItem = std::make_unique<DWF_Scene::SceneAudioItem>(L"sound_player_footsteps");
    pSoundItem->SetSound(pSound.get());
    pSound.release();

    // add sound to scene
    pScene->Add(pSoundItem.get());
    pSoundItem.release();

    return true;
}
//---------------------------------------------------------------------------
void Player::Animate(const DWF_Scene::Scene* pScene, double elapsedTime)
{
    // get the objects of interest from scene
    DWF_Scene::SceneItem_PointOfView* pArcballItem   = static_cast<DWF_Scene::SceneItem_PointOfView*>(pScene->SearchItem (L"scene_arcball"));
    DWF_Scene::SceneItem_AnimAsset*   pModelItem     = static_cast<DWF_Scene::SceneItem_AnimAsset*>  (pScene->SearchItem (L"scene_player_model"));
    DWF_Scene::SceneItem_Model*       pModelCollider = static_cast<DWF_Scene::SceneItem_Model*>      (pScene->SearchItem (L"scene_player_collider"));
    DWF_Scene::SceneAudioItem*        pSoundItem     =                                                pScene->SearchAudio(L"sound_player_footsteps");

    if (!pArcballItem || !pModelItem || !pModelCollider || !pSoundItem)
        return;

    // left (or "A") or right (or "D") key pressed?
    if ((::GetKeyState(VK_LEFT) & 0x8000) || (::GetKeyState(65) & 0x8000))
    {
        m_Walking    = true;
        m_WalkOffset = 1.0f;
    }
    else
    if ((::GetKeyState(VK_RIGHT) & 0x8000) || (::GetKeyState(68) & 0x8000))
    {
        m_Walking    =  true;
        m_WalkOffset = -1.0f;
    }
    else
        m_Walking = false;

    // set the camera position
    pArcballItem->SetPos(DWF_Math::Vector3F(m_xPos, m_yPos, m_zPos));
    pArcballItem->SetY(m_Angle);

    // calculate the player position
    const float x = m_xPos - (m_Distance * std::sinf(m_Angle));
    const float y = m_yPos -  m_PlayerShift;
    const float z = m_zPos + (m_Distance * std::cosf(m_Angle));

    // set the player position
    pModelItem->SetPos(DWF_Math::Vector3F(x, y + 0.022f, z));
    pModelItem->SetPitch(-m_Angle - ((float)M_PI / 2.0f) * m_WalkOffset);

    // set the player collider position
    pModelCollider->SetPos(DWF_Math::Vector3F(x, y, z));
    pModelCollider->SetPitch(-m_Angle - ((float)M_PI / 2.0f) * m_WalkOffset);

    // apply the gravity to the player
    m_yPos -= m_Gravity * (float)elapsedTime;

    // is player walking?
    if (m_Walking)
    {
        // calculate the next position
        m_Angle += m_Velocity * (float)m_WalkOffset * (float)elapsedTime;

        // play the walk animation, if still not running
        if (pModelItem->GetSelectedAnim() != 1)
            pModelItem->SelectAnim(1);

        // play the walk sound, if not playing
        if (!pSoundItem->GetSound()->IsPlaying())
            pSoundItem->GetSound()->Play();
    }
    else
    {
        // play the idle animation, if still not running
        if (pModelItem->GetSelectedAnim() != 0)
            pModelItem->SelectAnim(0);

        // stop the walk sound
        pSoundItem->GetSound()->Stop();
    }
}
//------------------------------------------------------------------------------
void Player::ApplyCollision(const DWF_Scene::Scene*       pScene,
                                  DWF_Scene::SceneItem*   pItem1,
                                  DWF_Collider::Collider* pCollider1,
                                  DWF_Scene::SceneItem*   pItem2,
                                  DWF_Collider::Collider* pCollider2,
                            const DWF_Math::Vector3F&     mtv)
{
    // use the minimum translation vector to correct the cached position
    m_yPos += mtv.m_Y;

    // get the point of view from the scene
    DWF_Scene::SceneItem_PointOfView* pPOV = static_cast<DWF_Scene::SceneItem_PointOfView*>(pScene->SearchItem(L"scene_arcball"));

    if (!pPOV)
        return;

    // get the player model from the scene
    DWF_Scene::SceneItem_AnimAsset* pPlayer = static_cast<DWF_Scene::SceneItem_AnimAsset*>(pScene->SearchItem(L"scene_player_model"));

    if (!pPlayer)
        return;

    DWF_Collider::Collider* pCollider;

    if (pItem1 == pPlayer)
        pCollider = pCollider1;
    else
        pCollider = pCollider2;

    // recalculate the corrected position
    const float x = m_xPos - (m_Distance * std::sinf(m_Angle));
    const float y = m_yPos -  m_PlayerShift;
    const float z = m_zPos + (m_Distance * std::cosf(m_Angle));

    // apply modifications to player (to avoid a parasite thrill effect)
    pPOV->SetPos     (DWF_Math::Vector3F(m_xPos, -m_yPos,     m_zPos));
    pPlayer->SetPos  (DWF_Math::Vector3F(x,       y + 0.022f, z));
    pCollider->SetPos(DWF_Math::Vector3F(x,       y,          z));
}
//---------------------------------------------------------------------------
void Player::Set_OnAttachTextureFunction(ITfOnAttachTextureFunction fHandler)
{
    m_fOnAttachTextureFunction = fHandler;
}
//---------------------------------------------------------------------------
void Player::OnFrame(const DWF_Scene::SceneItem_AnimAsset* pAnim, const DWF_Scene::SceneItem_AnimAsset::IAnimDesc* pAnimDesc)
{}
//---------------------------------------------------------------------------
void Player::OnEndReached(const DWF_Scene::SceneItem_AnimAsset* pAnim, const DWF_Scene::SceneItem_AnimAsset::IAnimDesc* pAnimDesc)
{}
//---------------------------------------------------------------------------
