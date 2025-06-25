/****************************************************************************
 * ==> Main ----------------------------------------------------------------*
 ****************************************************************************
 * Description : Main application class                                     *
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

#include "Main.h"

// classes
#include "DWF_Model.h"
#include "DWF_ModelFactory.h"
#include "DWF_Wavefront.h"
#include "DWF_BoxCollider.h"
#include "DWF_SphereCollider.h"
#include "DWF_CylinderCollider.h"
#include "DWF_CapsuleCollider.h"
#include "DWF_GJK.h"
#include "DWF_Camera.h"
#include "DWF_Arcball.h"
#include "DWF_SceneSpawner.h"
#include "DWF_SceneTimer.h"
#include "DWF_Sound_OpenAL.h"
#include "DWF_Sound_MiniAudio.h"
#include "DWF_Shader_Collection_OpenGL.h"
#include "DWF_Logger.h"

// libraries
#include <windowsx.h>

// openGL
#include <gl/gl.h>
#define GLEW_STATIC
#include <GL/glew.h>

// resources
#include "Resource.h"

//------------------------------------------------------------------------------
// Shader
//------------------------------------------------------------------------------
const std::string starVS = "#version 130\n"
                           "precision mediump float;\n"
                           "attribute    vec3 dwf_aVertices;\n"
                           "attribute    vec4 dwf_aColor;\n"
                           "uniform      mat4 dwf_uProjection;\n"
                           "uniform      mat4 dwf_uView;\n"
                           "uniform      mat4 dwf_uModel;\n"
                           "varying lowp vec4 dwf_vColor;\n"
                           "void main(void)\n"
                           "{\n"
                           "    float factor = clamp((dwf_uModel[3][2] + 60.0) / 20.0, 0.2, 1.0);"
                           "    dwf_vColor   = vec4(dwf_aColor.x * factor, dwf_aColor.y * factor, dwf_aColor.z * factor, dwf_aColor.w);\n"
                           "    gl_Position  = dwf_uProjection * dwf_uView * dwf_uModel * vec4(dwf_aVertices, 1.0);\n"
                           "}";
//------------------------------------------------------------------------------
const std::string starFS = "#version 130\n"
                           "precision mediump float;\n"
                           "varying lowp vec4 dwf_vColor;\n"
                           "void main(void)\n"
                           "{\n"
                           "    gl_FragColor = dwf_vColor;\n"
                           "}";
//------------------------------------------------------------------------------
const std::string explosionVS = "#version 130\n"
                                "precision mediump float;\n"
                                "attribute    vec3  dwf_aVertices;\n"
                                "attribute    vec4  dwf_aColor;\n"
                                "uniform      mat4  dwf_uProjection;\n"
                                "uniform      mat4  dwf_uView;\n"
                                "uniform      mat4  dwf_uModel;\n"
                                "uniform      float dwf_uAlpha;\n"
                                "varying lowp vec4  dwf_vColor;\n"
                                "varying      float dwf_fAlpha;\n"
                                "void main(void)\n"
                                "{\n"
                                "    dwf_vColor  = dwf_aColor;\n"
                                "    dwf_fAlpha  = dwf_uAlpha;\n"
                                "    gl_Position = dwf_uProjection * dwf_uView * dwf_uModel * vec4(dwf_aVertices, 1.0);\n"
                                "}";
//------------------------------------------------------------------------------
const std::string explosionFS = "#version 130\n"
                                "precision mediump float;\n"
                                "varying lowp vec4  dwf_vColor;\n"
                                "varying      float dwf_fAlpha;\n"
                                "void main(void)\n"
                                "{\n"
                                "    gl_FragColor = vec4(dwf_vColor.r, 0.3f + 0.7f * dwf_fAlpha, 0.2f * dwf_fAlpha, dwf_fAlpha);\n"
                                "}";;

//------------------------------------------------------------------------------
// Global functions
//------------------------------------------------------------------------------
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
        case WM_CLOSE:
            ::PostQuitMessage(0);
            break;

        case WM_DESTROY:
            return 0;

        case WM_KEYDOWN:
            switch (wParam)
            {
                case '1':
                    if (Main::GetInstance())
                        Main::GetInstance()->SetShowColliders(!Main::GetInstance()->GetShowColliders());

                    break;

                case VK_ESCAPE:
                    ::PostQuitMessage(0);
                    break;
            }

            break;

        default:
            return ::DefWindowProc(hWnd, uMsg, wParam, lParam);
    }

    return 0;
}
//---------------------------------------------------------------------------
Main* Main::m_This = nullptr;
//---------------------------------------------------------------------------
// Main
//---------------------------------------------------------------------------
Main::Main()
{
    m_This = this;
}
//---------------------------------------------------------------------------
Main::~Main()
{
    // delete the remaining entities
    for (ShootEmUp::Entities::iterator it = m_Entities.begin(); it != m_Entities.end(); ++it)
        delete it->second;

    // delete the remaining bullets
    for (auto pBullet : m_Bullets)
        delete pBullet;
}
//---------------------------------------------------------------------------
Main* Main::GetInstance()
{
    return m_This;
}
//---------------------------------------------------------------------------
int Main::Run(HINSTANCE hInstance, int nCmdShow)
{
    WNDCLASSEX wcex  = {0};
    MSG        msg;
    BOOL       bQuit = FALSE;

    // register window class
    wcex.cbSize        = sizeof(WNDCLASSEX);
    wcex.style         = CS_OWNDC;
    wcex.lpfnWndProc   = WindowProc;
    wcex.cbClsExtra    = 0;
    wcex.cbWndExtra    = 0;
    wcex.hInstance     = hInstance;
    wcex.hIcon         = ::LoadIcon(::GetModuleHandle(nullptr), MAKEINTRESOURCE(IDI_APPICON));
    wcex.hIconSm       = ::LoadIcon(::GetModuleHandle(nullptr), MAKEINTRESOURCE(IDI_APPICON_SMALL));
    wcex.hCursor       = ::LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)::GetStockObject(BLACK_BRUSH);
    wcex.lpszMenuName  = nullptr;
    wcex.lpszClassName = L"ShootEmUpDemo";

    if (!RegisterClassEx(&wcex))
        return 0;

    // create main window
    m_hWnd = ::CreateWindowEx(0,
                              L"ShootEmUpDemo",
                              L"DwarfStar Shoot Em Up Demo",
                              WS_DLGFRAME | WS_CAPTION | WS_SYSMENU,
                              CW_USEDEFAULT,
                              CW_USEDEFAULT,
                              800,
                              650,
                              nullptr,
                              nullptr,
                              hInstance,
                              nullptr);

    ::ShowWindow(m_hWnd, nCmdShow);

    // get the window client rect
    RECT clientRect;
    ::GetClientRect(m_hWnd, &clientRect);

    // get the window device context
    HDC hDC = ::GetDC(m_hWnd);

    // please wait text background
    HBRUSH hBrush = ::CreateSolidBrush(RGB(20, 30, 43));
    ::FillRect(hDC, &clientRect, hBrush);
    ::DeleteObject(hBrush);

    // please wait text
    ::SetBkMode(hDC, TRANSPARENT);
    ::SetBkColor(hDC, 0x000000);
    ::SetTextColor(hDC, 0xffffff);
    ::DrawText(hDC, L"Please wait...", 14, &clientRect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
    ::ReleaseDC(m_hWnd, hDC);

    DWF_Audio::OpenAL* pOpenALInstance = DWF_Audio::OpenAL::GetInstance();

    // enable OpenGL for the window
    m_Renderer.EnableOpenGL(m_hWnd);

    // stop GLEW crashing on OSX :-/
    glewExperimental = GL_TRUE;

    // initialize GLEW
    if (glewInit() != GLEW_OK)
    {
        // shutdown OpenGL
        m_Renderer.DisableOpenGL(m_hWnd);

        // destroy the window explicitly
        ::DestroyWindow(m_hWnd);

        return 1;
    }

    // create and configure the scene
    LoadScene(clientRect);

    double lastTime  = DWF_Scene::Timer::GetInstance()->GetElapsedTimeSinceStart();
    int    idleIndex = 0;
    int    walkIndex = 0;
    int    jumpIndex = 0;

    // program main loop
    while (!bQuit)
        // check for messages
        if (::PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            // handle or dispatch messages
            if (msg.message == WM_QUIT)
                bQuit = TRUE;
            else
            {
                ::TranslateMessage(&msg);
                ::DispatchMessage(&msg);
            }
        }
        else
        {
            // calculate the elapsed time
            const double curTime     = DWF_Scene::Timer::GetInstance()->GetElapsedTimeSinceStart();
            const double elapsedTime = DWF_Scene::Timer::GetInstance()->GetElapsedTimeSinceStart() - lastTime;
                         lastTime    = curTime;

            // do show or hide the colliders?
            if (m_ShowColliders != m_OldShowColliders)
            {
                // get the player spaceship collider
                DWF_Scene::SceneItem_Model* pModelCollider = static_cast<DWF_Scene::SceneItem_Model*>(m_Scene.SearchItem(L"scene_spaceship_collider"));

                // show or hide the spaceship collider
                if (pModelCollider)
                    pModelCollider->SetVisible(m_ShowColliders);

                // iterate through the scene models
                for (std::size_t i = 0; i < m_Scene.GetCount(DWF_Scene::Scene::IEGroupType::IE_GT_Model); ++i)
                {
                    // build the model identifier
                    DWF_Scene::Scene::IItemID id;
                    id.m_Group = DWF_Scene::Scene::IEGroupType::IE_GT_Model;
                    id.m_Index = i;

                    // get the model
                    DWF_Scene::SceneItem* pItem = m_Scene.Get(id);

                    // not found?
                    if (!pItem)
                        continue;

                    // is not a collider?
                    if (pItem->GetName().find(L"_collider_") == pItem->GetName().npos)
                        continue;

                    // Show or hide the collider
                    pItem->SetVisible(m_ShowColliders);
                }

                m_OldShowColliders = m_ShowColliders;
            }

            // render the scene
            m_Scene.Render(elapsedTime);
        }

    // shutdown OpenGL
    m_Renderer.DisableOpenGL(m_hWnd);

    // destroy the window explicitly
    ::DestroyWindow(m_hWnd);

    return (int)msg.wParam;
}
//------------------------------------------------------------------------------
DWF_Model::Texture* Main::OnCreateTexture(const DWF_Buffer::PixelBuffer* pPixelBuffer)
{
    if (!pPixelBuffer)
        return nullptr;

    if (!pPixelBuffer->m_pData)
        return nullptr;

    std::unique_ptr<DWF_Model::Texture_OpenGL> pTexture(new DWF_Model::Texture_OpenGL());
    pTexture->m_Width     = (std::int32_t)pPixelBuffer->m_Width;
    pTexture->m_Height    = (std::int32_t)pPixelBuffer->m_Height;
    pTexture->m_Format    = pPixelBuffer->m_BytePerPixel == 3 ? DWF_Model::Texture::IEFormat::IE_FT_24bit : DWF_Model::Texture::IEFormat::IE_FT_32bit;
    pTexture->m_WrapMode  = DWF_Model::Texture::IEWrapMode::IE_WM_Clamp;
    pTexture->m_MinFilter = DWF_Model::Texture::IEMinFilter::IE_MI_Linear;
    pTexture->m_MagFilter = DWF_Model::Texture::IEMagFilter::IE_MA_Linear;
    pTexture->Create(pPixelBuffer->m_pData);

    return pTexture.release();
}
//---------------------------------------------------------------------------
DWF_Model::Texture* Main::OnLoadTexture(const std::string& textureName, bool is32bit)
{
    std::unique_ptr<DWF_Buffer::PixelBuffer> pPixelBuffer = std::make_unique<DWF_Buffer::PixelBuffer>();

    // load the texture
    if (!pPixelBuffer->FromPng(textureName, true))
        return nullptr;

    if (!pPixelBuffer->m_pData)
        return nullptr;

    // create the texture
    std::unique_ptr<DWF_Model::Texture_OpenGL> pTexture(new DWF_Model::Texture_OpenGL());
    pTexture->m_Width     = (int)pPixelBuffer->m_Width;
    pTexture->m_Height    = (int)pPixelBuffer->m_Height;
    pTexture->m_Format    = pPixelBuffer->m_BytePerPixel == 3 ? DWF_Model::Texture::IEFormat::IE_FT_24bit : DWF_Model::Texture::IEFormat::IE_FT_32bit;
    pTexture->m_WrapMode  = DWF_Model::Texture::IEWrapMode::IE_WM_Clamp;
    pTexture->m_MinFilter = DWF_Model::Texture::IEMinFilter::IE_MI_Linear;
    pTexture->m_MagFilter = DWF_Model::Texture::IEMagFilter::IE_MA_Linear;
    pTexture->Create(pPixelBuffer->m_pData);

    return pTexture.release();
}
//------------------------------------------------------------------------------
void Main::OnSceneUpdatePhysics(const DWF_Scene::Scene* pScene, double elapsedTime)
{
    if (!pScene)
        return;

    // iterate through the bullets
    for (std::int64_t i = m_Bullets.size() - 1; i >= 0; --i)
    {
        // bullet sequence end was reached?
        if (m_Sequencer.EndReached(m_Bullets[i]->GetName()))
        {
            // delete the bullet
            DeleteBullet(m_Bullets[i]);
            m_Bullets.erase(m_Bullets.begin() + i);
            continue;
        }

        // move the bullet
        m_Bullets[i]->Move(&m_Sequencer, elapsedTime);
    }

    // do nothing if game over
    if (m_GameOver)
    {
        // check if game should be restarted
        if (m_CanRestart && ::GetKeyState(VK_SPACE) & 0x8000)
            ResetGame();

        return;
    }

    // get the objects of interest from scene
    DWF_Scene::SceneItem_StaticAsset* pModelItem     = static_cast<DWF_Scene::SceneItem_StaticAsset*>(pScene->SearchItem(L"scene_spaceship"));
    DWF_Scene::SceneItem_Model*       pModelCollider = static_cast<DWF_Scene::SceneItem_Model*>      (pScene->SearchItem(L"scene_spaceship_collider"));

    const float spaceshipSpeed         = 0.25f;
    const float spaceshipRotationSpeed = 0.05f;

    // fire
    if (::GetKeyState(VK_SPACE) & 0x8000)
    {
        if (m_CurrentTime >= m_LastBulletTime + 200.0)
        {
            AddBullet(pModelItem, pModelCollider, true);
            m_LastBulletTime = m_CurrentTime;
        }
    }

    // move the spaceship left or right
    if ((::GetKeyState(VK_LEFT) & 0x8000) || (::GetKeyState(65) & 0x8000))
        m_xPos = std::max(m_xPos - spaceshipSpeed, -19.0f);
    else
    if ((::GetKeyState(VK_RIGHT) & 0x8000) || (::GetKeyState(68) & 0x8000))
        m_xPos = std::min(m_xPos + spaceshipSpeed, 19.0f);

    // move the spaceship top or bottom, and rotate it
    if ((::GetKeyState(VK_UP) & 0x8000) || (::GetKeyState(87) & 0x8000))
    {
        m_yPos  = std::min(m_yPos  + spaceshipSpeed,         15.0f);
        m_Angle = std::min(m_Angle + spaceshipRotationSpeed, 0.0f);
    }
    else
    if ((::GetKeyState(VK_DOWN) & 0x8000) || (::GetKeyState(83) & 0x8000))
    {
        m_yPos  = std::max(m_yPos  - spaceshipSpeed,        -15.0f);
        m_Angle = std::min(m_Angle + spaceshipRotationSpeed, 0.0f);
    }
    else
        m_Angle = std::max(m_Angle - spaceshipRotationSpeed, (float)(-M_PI / 2.0));

    // move the spaceship
    pModelItem->SetPos(DWF_Math::Vector3F(m_xPos, m_yPos, -40.0f));
    pModelCollider->SetPos(DWF_Math::Vector3F(m_xPos + 0.35f, m_yPos, -40.0f));

    // rotate the spaceship
    pModelItem->SetPitch(m_Angle);
    pModelCollider->SetRoll(m_Angle);
}
//------------------------------------------------------------------------------
void Main::OnSceneUpdate(const DWF_Scene::Scene* pScene, double elapsedTime)
{
    // as enemies are raised based on time, get current time but limit to 10 milliseconds for each frame. This way there is no possible high jump
    // in case e.g. the window loses the activation
    m_CurrentTime += std::min(elapsedTime, 10.0);

    // if game over, show the game over notification after 2 seconds
    if (m_GameOver && !m_CanRestart && m_CurrentTime >= m_GameOverTime + 2000.0)
    {
        DWF_Scene::SceneItem_Model* pModelItem = static_cast<DWF_Scene::SceneItem_Model*>(pScene->SearchItem(L"scene_game_over"));

        if (pModelItem)
            pModelItem->SetVisible(true);

        m_CanRestart = true;
    }
}
//------------------------------------------------------------------------------
void Main::OnCollision(const DWF_Scene::Scene*       pScene,
                             DWF_Scene::SceneItem*   pItem1,
                             DWF_Collider::Collider* pCollider1,
                             DWF_Scene::SceneItem*   pItem2,
                             DWF_Collider::Collider* pCollider2,
                       const DWF_Math::Vector3F&     mtv)
{
    // do nothing if game over
    if (m_GameOver)
        return;

    // hit a bullet?
    if (pItem1->GetName().find(L"bullet_") == 0)
    {
        if (CheckBulletIsIgnoredOrHitEnemy(pItem1, pItem2))
            return;
    }
    else
    if (pItem2->GetName().find(L"bullet_") == 0)
        if (CheckBulletIsIgnoredOrHitEnemy(pItem2, pItem1))
            return;

    // one of the collider belongs to the player spaceship?
    if (pItem1->GetName() != L"scene_spaceship_collider" && pItem2->GetName() != L"scene_spaceship_collider")
        return;

    // player was hit by a bullet?
    if (pItem1->GetName().find(L"bullet_") == 0 || pItem2->GetName().find(L"bullet_") == 0)
    {
        // run the game over sequence onto the player spaceship. Can do that from here because no item is removed from the scene, only hidden
        RunGameOver(pScene);
        return;
    }

    std::wstring spawnedItemName;

    // player hit an enemy?
    if (pItem1->GetName().find(L"enemy_") == 0)
    {
        const std::size_t sepPos = pItem1->GetName().find(L"_", 6);

        if (sepPos != pItem1->GetName().npos)
            spawnedItemName = pItem1->GetName().substr(0, sepPos);
    }
    else
    if (pItem2->GetName().find(L"enemy_") == 0)
    {
        const std::size_t sepPos = pItem2->GetName().find(L"_", 6);

        if (sepPos != pItem2->GetName().npos)
            spawnedItemName = pItem2->GetName().substr(0, sepPos);
    }

    // found hit enemy name?
    if (!spawnedItemName.empty())
        // run the game over sequence onto the player spaceship. Can do that from here because no item is removed from the scene, only hidden
        RunGameOver(pScene);
}
//------------------------------------------------------------------------------
bool Main::OnDoSpawn(DWF_Scene::Spawner* pSpawner)
{
    // no longer spawn nothing if game over
    if (m_GameOver)
        return false;

    // iterate through events
    for (std::size_t i = 0; i < m_Events.size(); ++i)
        // do raise an event?
        if (DoRaiseEvent(i))
        {
            // wave ended?
            if (m_Events[i].second == ShootEmUp::Entity::IESequenceType::IE_ST_NextLevel)
            {
                // reset all raised events
                m_RaisedEvents.clear();

                // go to next level
                m_CurrentTime    = 0.0;
                m_LastBulletTime = 0.0;
                ++m_Difficulty;
                return false;
            }

            return true;
        }

    return false;
}
//------------------------------------------------------------------------------
void Main::OnSpawned(DWF_Scene::Spawner* pSpawner, DWF_Scene::Spawner::IItem* pItem)
{
    // iterate through events
    for (std::size_t i = 0; i < m_Events.size(); ++i)
        // event was raised?
        if (DoRaiseEvent(i))
        {
            // add an entity to own the item in the scene
            AddEntity(pItem, m_Events[i]);
            return;
        }
}
//------------------------------------------------------------------------------
bool Main::OnDoDelete(DWF_Scene::Spawner* pSpawner, DWF_Scene::Spawner::IItem* pItem)
{
    // check if the sequence reached the end for the current item
    if (m_Sequencer.EndReached(pItem->m_Name) || !m_Sequencer.Exists(pItem->m_Name))
    {
        // delete the entity matching the item from scene
        DeleteEntity(pItem);

        // returning true, the spawned item will be deleted by the spawner
        return true;
    }

    return false;
}
//------------------------------------------------------------------------------
void Main::OnCalculateMotion(DWF_Scene::Spawner* pSpawner, DWF_Scene::Spawner::IItem* pItem, double elapsedTime)
{
    // find the moving entity
    ShootEmUp::Entities::iterator it = m_Entities.find(pItem);

    if (it == m_Entities.end())
        return;

    // move it
    it->second->Move(&m_Sequencer, pItem, elapsedTime);

    // select the difficulty
    switch (m_Difficulty)
    {
        case 0:
            // randomly fire a bullet against the player
            if (std::rand() % 2000 == 912)
                AddBullet(static_cast<DWF_Scene::SceneItem_StaticAsset*>(pItem->m_pModel), static_cast<DWF_Scene::SceneItem_Model*>(pItem->m_pCollider), false);

            break;

        case 1:
            // randomly fire a bullet against the player
            if (std::rand() % 1000 == 525 || std::rand() % 1000 == 124)
                AddBullet(static_cast<DWF_Scene::SceneItem_StaticAsset*>(pItem->m_pModel), static_cast<DWF_Scene::SceneItem_Model*>(pItem->m_pCollider), false);

            break;

        case 2:
        default:
            // randomly fire a bullet against the player
            if (std::rand() % 300 == 255 || std::rand() % 300 == 124)
                AddBullet(static_cast<DWF_Scene::SceneItem_StaticAsset*>(pItem->m_pModel), static_cast<DWF_Scene::SceneItem_Model*>(pItem->m_pCollider), false);

            break;
    }
}
//------------------------------------------------------------------------------
void Main::OnCalculateStarMotion(DWF_Particles::Particles* pParticles, DWF_Particles::Particle* pParticle, double elapsedTime)
{
    // calculate next star position, adds a small scrolling effect on y axis
    pParticle->m_Matrix.m_Table[3][0] += pParticle->m_Velocity.m_X * (float)elapsedTime;
    pParticle->m_Matrix.m_Table[3][1]  = pParticle->m_StartPos.m_Y + (m_yPos * 0.5f);

    // limit x pos inside the star box
    if (pParticle->m_Matrix.m_Table[3][0] <= pParticles->m_Area.m_Min.m_X)
        pParticle->m_Matrix.m_Table[3][0] += (pParticles->m_Area.m_Max.m_X - pParticles->m_Area.m_Min.m_X);
    else
    if (pParticle->m_Matrix.m_Table[3][0] >= pParticles->m_Area.m_Max.m_X)
        pParticle->m_Matrix.m_Table[3][0] -= (pParticles->m_Area.m_Max.m_X - pParticles->m_Area.m_Min.m_X);

    // limit y pos inside the star box
    if (pParticle->m_Matrix.m_Table[3][1] <= pParticles->m_Area.m_Min.m_Y)
        pParticle->m_Matrix.m_Table[3][1] += (pParticles->m_Area.m_Max.m_Y - pParticles->m_Area.m_Min.m_Y);
    else
    if (pParticle->m_Matrix.m_Table[3][1] >= pParticles->m_Area.m_Max.m_Y)
        pParticle->m_Matrix.m_Table[3][1] -= (pParticles->m_Area.m_Max.m_Y - pParticles->m_Area.m_Min.m_Y);

    // limit z pos inside the star box
    if (pParticle->m_Matrix.m_Table[3][2] <= pParticles->m_Area.m_Min.m_Z)
        pParticle->m_Matrix.m_Table[3][2] += (pParticles->m_Area.m_Max.m_Z - pParticles->m_Area.m_Min.m_Z);
    else
    if (pParticle->m_Matrix.m_Table[3][2] >= pParticles->m_Area.m_Max.m_Z)
        pParticle->m_Matrix.m_Table[3][2] -= (pParticles->m_Area.m_Max.m_Z - pParticles->m_Area.m_Min.m_Z);
}
//------------------------------------------------------------------------------
void Main::OnCalculateExplosionMotion(DWF_Particles::Particles* pParticles, DWF_Particles::Particle* pParticle, double elapsedTime)
{
    // particle lifetime reached?
    if (pParticle->m_ElapsedTime >= pParticle->m_Lifetime)
    {
        // put it out of screen, this way it will not be removed from particle system
        pParticle->m_Matrix.m_Table[3][0] = 999.0f;
        pParticle->m_Matrix.m_Table[3][1] = 999.0f;
        return;
    }

    // calculate next particle position
    pParticle->m_Matrix.m_Table[3][0] +=  pParticle->m_Velocity.m_X                         * (float)elapsedTime;
    pParticle->m_Matrix.m_Table[3][1] += (pParticle->m_Velocity.m_Y - pParticle->m_Gravity) * (float)elapsedTime;

    // set the particle transparency, stronger as time is elapsed
    if (m_AlphaSlot != -1)
    {
        m_pExplosionShader->Use(true);
        glUniform1f(m_AlphaSlot, 1.0f - (float)(pParticle->m_ElapsedTime / pParticle->m_Lifetime));
    }

    // update particle elapsed time
    pParticle->m_ElapsedTime += elapsedTime;
}
//------------------------------------------------------------------------------
void Main::OnSequenceEndReached(const ShootEmUp::Sequencer* pSequencer, const ShootEmUp::Sequencer::ISequence* pSequence)
{}
//------------------------------------------------------------------------------
bool Main::DoRaiseEvent(std::size_t index) const
{
    if (index >= m_Events.size())
        return false;

    return ((std::size_t)(m_CurrentTime * 0.1) >= m_Events[index].first && m_RaisedEvents.find(m_Events[index].first) == m_RaisedEvents.end());
}
//------------------------------------------------------------------------------
void Main::AddBullet(DWF_Scene::SceneItem_StaticAsset* pItem, DWF_Scene::SceneItem_Model* pCollider, bool fromPlayer)
{
    if (!pItem)
        return;

    if (!pCollider)
        return;

    // create a name for the new entity/sequence/spawned item group
    const std::wstring name = L"bullet_" + std::to_wstring(m_Index);
    ++m_Index;

    const DWF_Math::Vector3F pos = pItem->GetPos();
    const float              x   = pos.m_X;
    const float              y   = pos.m_Y;

    DWF_Math::Vector3F dir;

    // calculate the bullet direction
    if (fromPlayer)
        dir = DWF_Math::Vector3F(1.0f, 0.0f, 0.0f);
    else
    {
        DWF_Scene::SceneItem_StaticAsset* pPlayerItem = static_cast<DWF_Scene::SceneItem_StaticAsset*>(m_Scene.SearchItem(L"scene_spaceship"));

        if (!pPlayerItem)
            return;

        dir = (pPlayerItem->GetPos() - pItem->GetPos()).Normalize();
    }

    // create a new entity, add the assets to use and sequence to follow
    std::unique_ptr<ShootEmUp::Bullet> pBullet = std::make_unique<ShootEmUp::Bullet>(name, m_pBullet, m_pColShader);
    pBullet->AddAsset(m_Scene, x, y);
    pBullet->AddSequence(&m_Sequencer, DWF_Math::Vector3F(x, y, -40.0f), dir);
    pBullet->AddColliderToIgnore(pCollider->GetName());

    // if an enemy fired, add all the other enemies colliders to ignore
    if (!fromPlayer)
        // iterate through running entities
        for (ShootEmUp::Entities::iterator it = m_Entities.begin(); it != m_Entities.end(); ++it)
            // Found the hit entity?
            if (it->first->m_pModel != pItem)
                pBullet->AddColliderToIgnore(it->first->m_pCollider->GetName());

    m_Bullets.push_back(pBullet.get());
    pBullet.release();
}
//------------------------------------------------------------------------------
void Main::DeleteBullet(ShootEmUp::Bullet* pBullet)
{
    // delete the sequence, if exists
    m_Sequencer.Delete(pBullet->GetName());

    // remove the bullet asset from the scene
    pBullet->DeleteAsset(m_Scene);

    // delete the bullet
    delete pBullet;
}
//------------------------------------------------------------------------------
void Main::AddEntity(DWF_Scene::Spawner::IItem* pItem, const std::pair<int, ShootEmUp::Entity::IESequenceType>& evt)
{
    float x, y;

    switch (evt.second)
    {
        case ShootEmUp::Entity::IESequenceType::IE_ST_BottomToTop:
            x = 20.0f;
            y = 14.0f;
            break;

        case ShootEmUp::Entity::IESequenceType::IE_ST_TopToBottom:
            x =  20.0f;
            y = -14.0f;
            break;

        case ShootEmUp::Entity::IESequenceType::IE_ST_BezierCurve1:
            x = 20.0f;
            y = 0.0f;
            break;

        case ShootEmUp::Entity::IESequenceType::IE_ST_BezierCurve2:
            x = 20.0f;
            y = 15.0f;
            break;

        default:
            x = 999.0f;
            y = 999.0f;
            break;
    }

    // create a name for the new entity/sequence/spawned item group
    const std::wstring name = L"enemy_" + std::to_wstring(evt.first);

    // set the spawned item name
    pItem->m_Name = name;

    // create a new entity, add the assets to use and sequence to follow
    std::unique_ptr<ShootEmUp::Entity> pEntity = std::make_unique<ShootEmUp::Entity>(name,
                                                                                     m_pEnemyMdl,
                                                                                     m_pEnemyBox,
                                                                                     m_pTexShader,
                                                                                     m_pColShader);
    pEntity->AddAsset(pItem, m_Scene, x, y, m_ShowColliders);
    pEntity->AddSequence(&m_Sequencer, evt.second, DWF_Math::Vector3F(x, -y, -40.0f));
    m_Entities[pItem] = pEntity.get();
    pEntity.release();

    // notify that the event was raised
    m_RaisedEvents.insert(evt.first);
}
//------------------------------------------------------------------------------
void Main::DeleteEntity(DWF_Scene::Spawner::IItem* pItem)
{
    // delete the sequence, if exists
    m_Sequencer.Delete(pItem->m_Name);

    // search for the entity to delete
    ShootEmUp::Entities::iterator it = m_Entities.find(pItem);

    // delete it
    if (it != m_Entities.end())
    {
        delete it->second;
        m_Entities.erase(it);
    }

    // delete the collider item from the scene
    if (pItem->m_pCollider)
        m_Scene.Delete(pItem->m_pCollider);

    // delete the model item from the scene
    if (pItem->m_pModel)
        m_Scene.Delete(pItem->m_pModel);
}
//------------------------------------------------------------------------------
bool Main::CheckBulletIsIgnoredOrHitEnemy(const DWF_Scene::SceneItem* pItem1, const DWF_Scene::SceneItem* pItem2)
{
    // iterate through bullets
    for (auto pBullet : m_Bullets)
        // found the hitting bullet?
        if (pItem1->GetName() == pBullet->GetModelNameInScene())
            // do bullet ignore the other collider?
            if (pBullet->DoIgnoreCollider(pItem2->GetName()))
                return true;
            else
            {
                pBullet->Break();
                break;
            }

    // iterate through running entities
    for (ShootEmUp::Entities::const_iterator it = m_Entities.begin(); it != m_Entities.end(); ++it)
        // Found the hit entity?
        if (it->first->m_pCollider == pItem2)
        {
            // breaks its sequence and run the dying one
            it->second->Break(&m_Sequencer);
            break;
        }

    return false;
}
//------------------------------------------------------------------------------
void Main::RunGameOver(const DWF_Scene::Scene* pScene)
{
    // get the objects of interest from scene
    DWF_Scene::SceneItem_StaticAsset* pModelItem     = static_cast<DWF_Scene::SceneItem_StaticAsset*>(pScene->SearchItem(L"scene_spaceship"));
    DWF_Scene::SceneItem_Model*       pModelCollider = static_cast<DWF_Scene::SceneItem_Model*>      (pScene->SearchItem(L"scene_spaceship_collider"));
    DWF_Scene::SceneItem_Particles*   pExplosionItem = static_cast<DWF_Scene::SceneItem_Particles*>  (pScene->SearchItem(L"scene_explosion_particles"));

    // get the explosion point and the particle system
    const DWF_Math::Vector3F  explosionPoint = pModelItem->GetPos();
    DWF_Particles::Particles* pParticles     = pExplosionItem->GetParticles();

    // iterate through each explosion particles and set the start position
    for (std::size_t i = 0; i < pParticles->GetCount(); ++i)
    {
        DWF_Particles::Particle* pParticle = pParticles->Get(i);
        pParticle->m_StartPos              = explosionPoint;
        pParticle->m_Matrix.m_Table[3][0]  = explosionPoint.m_X;
        pParticle->m_Matrix.m_Table[3][1]  = explosionPoint.m_Y;
        pParticle->m_ElapsedTime           = 0.0;
    }

    // hide the player spaceship
    pModelItem->SetVisible(false);
    pModelCollider->SetVisible(false);

    // show the explosion
    pExplosionItem->SetVisible(true);

    // notify that the game is over and get game over timestamp
    m_GameOver     = true;
    m_GameOverTime = m_CurrentTime;
}
//------------------------------------------------------------------------------
void Main::ResetGame()
{
    // clear all the running sequences
    m_Sequencer.Clear();

    // clear all the spawner
    for (std::size_t i = 0; i < m_Scene.GetSpawnerCount(); ++i)
    {
        // get spawner
        DWF_Scene::Spawner* pSpawner = m_Scene.GetSpawner(i);

        // clear it
        if (pSpawner)
            pSpawner->Clear();
    }

    // delete all raised entities
    for (ShootEmUp::Entities::iterator it = m_Entities.begin(); it != m_Entities.end(); ++it)
        delete it->second;

    m_Entities.clear();

    // delete all fired bullets
    for (std::size_t i = 0; i < m_Bullets.size(); ++i)
        DeleteBullet(m_Bullets[i]);

    m_Bullets.clear();

    // reset all raised events
    m_RaisedEvents.clear();

    // reset all other time and position values, and all flags
    m_Index          = 0;
    m_Difficulty     = 0;
    m_xPos           = 0.0f;
    m_yPos           = 0.0f;
    m_Angle          = (float)(-M_PI / 2.0);
    m_CurrentTime    = 0.0;
    m_GameOverTime   = 0.0;
    m_LastBulletTime = 0.0;
    m_GameOver       = false;
    m_CanRestart     = false;

    // get the spaceship asset and its collider
    DWF_Scene::SceneItem_StaticAsset* pSpaceshipItem     = static_cast<DWF_Scene::SceneItem_StaticAsset*>(m_Scene.SearchItem(L"scene_spaceship"));
    DWF_Scene::SceneItem_Model*       pSpaceshipCollider = static_cast<DWF_Scene::SceneItem_Model*>      (m_Scene.SearchItem(L"scene_spaceship_collider"));

    // show the player spaceship
    if (pSpaceshipItem)
        pSpaceshipItem->SetVisible(true);

    // and its collider (if required)
    if (pSpaceshipItem)
        pSpaceshipCollider->SetVisible(m_ShowColliders);

    // get the game over panel
    DWF_Scene::SceneItem_Model* pModelItem = static_cast<DWF_Scene::SceneItem_Model*>(m_Scene.SearchItem(L"scene_game_over"));

    // hide it
    if (pModelItem)
        pModelItem->SetVisible(false);

    // get the explosion particle system
    DWF_Scene::SceneItem_Particles* pExplosionItem = static_cast<DWF_Scene::SceneItem_Particles*>(m_Scene.SearchItem(L"scene_explosion_particles"));

    // hide it
    if (pExplosionItem)
        pExplosionItem->SetVisible(false);
}
//------------------------------------------------------------------------------
bool Main::LoadScene(const RECT& clientRect)
{
    // load texture shader
    m_pTexShader = std::make_shared<DWF_Renderer::Shader_OpenGL>();
    m_pTexShader->CreateProgram();
    m_pTexShader->Attach(DWF_Renderer::Shader_Collection_OpenGL::GetVertexShader(DWF_Renderer::Shader_Collection_OpenGL::IEShaderType::IE_ST_Texture),
            DWF_Renderer::Shader::IEType::IE_ST_Vertex);
    m_pTexShader->Attach(DWF_Renderer::Shader_Collection_OpenGL::GetFragmentShader(DWF_Renderer::Shader_Collection_OpenGL::IEShaderType::IE_ST_Texture),
            DWF_Renderer::Shader::IEType::IE_ST_Fragment);
    m_pTexShader->Link(true);

    // load color shader
    m_pColShader = std::make_shared<DWF_Renderer::Shader_OpenGL>();
    m_pColShader->CreateProgram();
    m_pColShader->Attach(DWF_Renderer::Shader_Collection_OpenGL::GetVertexShader(DWF_Renderer::Shader_Collection_OpenGL::IEShaderType::IE_ST_Color),
            DWF_Renderer::Shader::IEType::IE_ST_Vertex);
    m_pColShader->Attach(DWF_Renderer::Shader_Collection_OpenGL::GetFragmentShader(DWF_Renderer::Shader_Collection_OpenGL::IEShaderType::IE_ST_Color),
            DWF_Renderer::Shader::IEType::IE_ST_Fragment);
    m_pColShader->Link(true);

    // load stars shader
    m_pStarShader = std::make_shared<DWF_Renderer::Shader_OpenGL>();
    m_pStarShader->CreateProgram();
    m_pStarShader->Attach(starVS, DWF_Renderer::Shader::IEType::IE_ST_Vertex);
    m_pStarShader->Attach(starFS, DWF_Renderer::Shader::IEType::IE_ST_Fragment);
    m_pStarShader->Link(true);

    // load explosion shader
    m_pExplosionShader = std::make_shared<DWF_Renderer::Shader_OpenGL>();
    m_pExplosionShader->CreateProgram();
    m_pExplosionShader->Attach(explosionVS, DWF_Renderer::Shader::IEType::IE_ST_Vertex);
    m_pExplosionShader->Attach(explosionFS, DWF_Renderer::Shader::IEType::IE_ST_Fragment);
    m_pExplosionShader->Link(true);

    m_pExplosionShader->Use(true);
    m_AlphaSlot = glGetUniformLocation((GLuint)m_pExplosionShader->GetProgramID(), "dwf_uAlpha");

    DWF_Math::Matrix4x4F projMatrix;

    // create the viewport
    m_Renderer.CreateViewport(float(clientRect.right  - clientRect.left),
                              float(clientRect.bottom - clientRect.top),
                              0.1f,
                              100.0f,
                              m_pTexShader.get(),
                              projMatrix);

    // connect the projection matrix to the other shaders
    m_Renderer.ConnectProjectionMatrixToShader(m_pColShader.get(),       projMatrix);
    m_Renderer.ConnectProjectionMatrixToShader(m_pStarShader.get(),      projMatrix);
    m_Renderer.ConnectProjectionMatrixToShader(m_pExplosionShader.get(), projMatrix);

    // configure the background color
    DWF_Model::ColorF bgColor;
    bgColor.m_R = 0.0f;
    bgColor.m_G = 0.0f;
    bgColor.m_B = 0.0f;
    bgColor.m_A = 1.0f;

    m_Scene.SetRenderer(m_Renderer);
    m_Scene.SetColor(bgColor);

    // create the player arcball
    std::unique_ptr<DWF_Scene::Camera> pCamera = std::make_unique<DWF_Scene::Camera>();

    // create an arcball point of view
    std::unique_ptr<DWF_Scene::SceneItem_PointOfView> pPOV = std::make_unique<DWF_Scene::SceneItem_PointOfView>(L"scene_camera");
    pPOV->Set(pCamera.get());
    pCamera.release();

    // set the point of view to the scene
    m_Scene.Add(pPOV.get());
    pPOV.release();

    // load player spaceship
    std::shared_ptr<DWF_Model::MDL> pPlayerMdl = std::make_shared<DWF_Model::MDL>();
    pPlayerMdl->Set_OnCreateTexture(std::bind(&Main::OnCreateTexture, this, std::placeholders::_1));
    pPlayerMdl->Open("..\\..\\Resources\\Model\\Spaceships\\spaceship_blue.mdl");

    // create the player spaceship scene model item
    std::unique_ptr<DWF_Scene::SceneItem_StaticAsset> pStaticModel = std::make_unique<DWF_Scene::SceneItem_StaticAsset>(L"scene_spaceship");
    pStaticModel->SetStatic(true);
    pStaticModel->SetModel(pPlayerMdl);
    pStaticModel->SetShader(m_pTexShader);
    pStaticModel->SetPos(DWF_Math::Vector3F(m_xPos, m_yPos, -40.0f));
    pStaticModel->SetRoll(-0.25f);
    pStaticModel->SetPitch(m_Angle);
    pStaticModel->SetYaw((float)(-M_PI / 2.0));
    pStaticModel->SetScale(DWF_Math::Vector3F(2.0f, 2.0f, 2.0f));

    // set the model to the scene
    m_Scene.Add(pStaticModel.get(), false);
    pStaticModel.release();

    DWF_Model::VertexFormat  vf;
    DWF_Model::VertexCulling vc;
    DWF_Model::Material      mat;

    // set vertex format for colored models
    vf.m_Type   = DWF_Model::VertexFormat::IEType::IE_VT_Triangles;
    vf.m_Format = DWF_Model::VertexFormat::IEFormat::IE_VF_Colors;

    // create material
    mat.m_Color.m_B = 1.0f;
    mat.m_Color.m_G = 0.0f;
    mat.m_Color.m_R = 0.0f;
    mat.m_Color.m_A = 1.0f;

    // create the spaceship box model
    std::shared_ptr<DWF_Model::Model> pSpaceshipBox(DWF_Model::Factory::GetBox(4.0f, 2.0f, 1.5f, false, vf, vc, mat));

    // create the spaceship model item
    std::unique_ptr<DWF_Scene::SceneItem_Model> pModel = std::make_unique<DWF_Scene::SceneItem_Model>(L"scene_spaceship_collider");
    pModel->SetStatic(false);
    pModel->SetVisible(false);
    pModel->SetModel(pSpaceshipBox);
    pModel->SetShader(m_pColShader);
    pModel->SetPos(DWF_Math::Vector3F(m_xPos + 0.35f, m_yPos, -40.0f));
    pModel->SetRoll(m_Angle);
    pModel->SetPitch(0.0f);
    pModel->SetYaw(0.0f);
    pModel->SetScale(DWF_Math::Vector3F(1.0f, 1.0f, 1.0f));

    // create the spaceship box collider
    std::unique_ptr<DWF_Collider::Box_Collider> pBoxCol =
            std::make_unique<DWF_Collider::Box_Collider>(DWF_Math::Vector3F(),
                                                         DWF_Math::Matrix4x4F::Identity(),
                                                         DWF_Math::Vector3F(-2.0f, -1.0f, -0.5f),
                                                         DWF_Math::Vector3F( 2.0f,  1.0f,  0.75f));
    pModel->AddCollider(pBoxCol.get());
    pBoxCol.release();

    // set the model to the scene
    m_Scene.Add(pModel.get(), false);
    pModel.release();

    // create material
    mat.m_Color.m_B = 0.02f;
    mat.m_Color.m_G = 0.8f;
    mat.m_Color.m_R = 0.84f;
    mat.m_Color.m_A = 1.0f;

    // create the bullet model, keep it globally in order to allow new bullet to be spawned on runtime
    m_pBullet.reset(DWF_Model::Factory::GetSphere(0.25f, 5, 5, vf, vc, mat));

    // load enemy spaceship, keep it globally in order to allow new spaceship to be spawned on runtime
    m_pEnemyMdl = std::make_shared<DWF_Model::MDL>();
    m_pEnemyMdl->Set_OnCreateTexture(std::bind(&Main::OnCreateTexture, this, std::placeholders::_1));
    m_pEnemyMdl->Open("..\\..\\Resources\\Model\\Spaceships\\spaceship_red.mdl");

    // create material
    mat.m_Color.m_B = 0.0f;
    mat.m_Color.m_G = 0.0f;
    mat.m_Color.m_R = 1.0f;

    // create the spaceship box model
    m_pEnemyBox.reset(DWF_Model::Factory::GetBox(4.0f, 2.0f, 1.5f, false, vf, vc, mat));

    // create a spawner for the entities and add it to scene
    std::unique_ptr<DWF_Scene::Spawner> pSpawner = std::make_unique<DWF_Scene::Spawner>(L"scene_entity_spawner");
    pSpawner->Set_OnDoSpawn(std::bind(&Main::OnDoSpawn, this, std::placeholders::_1));
    pSpawner->Set_OnSpawned(std::bind(&Main::OnSpawned, this, std::placeholders::_1, std::placeholders::_2));
    pSpawner->Set_OnDoDelete(std::bind(&Main::OnDoDelete, this, std::placeholders::_1, std::placeholders::_2));
    pSpawner->Set_OnCalculateMotion(std::bind(&Main::OnCalculateMotion, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
    m_Scene.AddSpawner(pSpawner.get());
    pSpawner.release();

    // create material
    mat.m_Color.m_B = 1.0f;
    mat.m_Color.m_G = 1.0f;
    mat.m_Color.m_R = 1.0f;
    mat.m_Color.m_A = 1.0f;

    // create the star model
    std::shared_ptr<DWF_Model::Model> pStarModel(DWF_Model::Factory::GetSphere(0.1f, 5, 5, vf, vc, mat));

    // create the stars particle system
    std::shared_ptr<DWF_Particles::Particles> pStars = std::make_shared<DWF_Particles::Particles>();
    pStars->SetModel(pStarModel);
    pStars->Set_OnCalculateMotion(std::bind(&Main::OnCalculateStarMotion, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));

    // configure the star box
    pStars->m_Area.m_Min.m_X = -30.0f;
    pStars->m_Area.m_Min.m_Y = -25.0f;
    pStars->m_Area.m_Min.m_Z = -60.0f;
    pStars->m_Area.m_Max.m_X =  30.0f;
    pStars->m_Area.m_Max.m_Y =  25.0f;
    pStars->m_Area.m_Max.m_Z = -40.0f;

    // set random seed
    std::srand(0);

    // iterate through the particles to create
    for (std::size_t i = 0; i < 50; ++i)
    {
        // add a new particle
        DWF_Particles::Particle* pParticle = pStars->Add();

        // calculate the particle start position
        pParticle->m_StartPos.m_X = pStars->m_Area.m_Min.m_X + (((float)(rand() % (int)6000.0f)) * 0.01f);
        pParticle->m_StartPos.m_Y = pStars->m_Area.m_Min.m_Y + (((float)(rand() % (int)5000.0f)) * 0.01f);
        pParticle->m_StartPos.m_Z = pStars->m_Area.m_Min.m_Z + (((float)(rand() % (int)2000.0f)) * 0.01f);

        // calculate the particle initial force
        pParticle->m_Velocity.m_X = -0.05f;
        pParticle->m_Velocity.m_Y =  0.0f;
        pParticle->m_Velocity.m_Z =  0.0f;

        // configure the particle matrix (was set to identity while the particle was created)
        pParticle->m_Matrix.m_Table[3][0] = pParticle->m_StartPos.m_X;
        pParticle->m_Matrix.m_Table[3][1] = pParticle->m_StartPos.m_Y;
        pParticle->m_Matrix.m_Table[3][2] = pParticle->m_StartPos.m_Z;
    }

    // create the star particles model item
    std::unique_ptr<DWF_Scene::SceneItem_Particles> pParticles = std::make_unique<DWF_Scene::SceneItem_Particles>(L"scene_stars_particles");
    pParticles->SetStatic(true);
    pParticles->SetVisible(true);
    pParticles->SetParticles(pStars);
    pParticles->SetShader(m_pStarShader);

    // set the particles system to the scene
    m_Scene.Add(pParticles.get(), false);
    pParticles.release();

    // create material
    mat.m_Color.m_B   = 0.99f;
    mat.m_Color.m_G   = 1.0f;
    mat.m_Color.m_R   = 0.93f;
    mat.m_Color.m_A   = 1.0f;
    mat.m_Transparent = true;

    // create the explosion model
    std::shared_ptr<DWF_Model::Model> pExplosionModel(DWF_Model::Factory::GetSphere(0.1f, 5, 5, vf, vc, mat));

    // create the explosion particle system
    std::shared_ptr<DWF_Particles::Particles> pExplosion = std::make_shared<DWF_Particles::Particles>();
    pExplosion->SetModel(pExplosionModel);
    pExplosion->Set_OnCalculateMotion(std::bind(&Main::OnCalculateExplosionMotion, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));

    // iterate through the particles to create
    for (std::size_t i = 0; i < 50; ++i)
    {
        // add a new particle
        DWF_Particles::Particle* pParticle = pExplosion->Add();

        const float angle = float(std::rand()) / RAND_MAX * (float)(M_PI * 2.0);
        const float speed = float(std::rand()) / RAND_MAX * 0.03f + 0.003f;

        // calculate the particle start position
        pParticle->m_StartPos.m_X =  0.0f;
        pParticle->m_StartPos.m_Y =  0.0f;
        pParticle->m_StartPos.m_Z = -40.0f;

        // calculate the particle initial force
        pParticle->m_Velocity.m_X = std::cosf(angle) * speed;
        pParticle->m_Velocity.m_Y = std::sinf(angle) * speed * 0.95f;
        pParticle->m_Velocity.m_Z = 0.0f;

        pParticle->m_Gravity  = 0.015f;
        pParticle->m_Lifetime = 2000.0f;

        // configure the particle matrix (was set to identity while the particle was created)
        pParticle->m_Matrix.m_Table[3][0] = pParticle->m_StartPos.m_X;
        pParticle->m_Matrix.m_Table[3][1] = pParticle->m_StartPos.m_Y;
        pParticle->m_Matrix.m_Table[3][2] = pParticle->m_StartPos.m_Z;
    }

    // create the explosion particles model item
    pParticles = std::make_unique<DWF_Scene::SceneItem_Particles>(L"scene_explosion_particles");
    pParticles->SetStatic(true);
    pParticles->SetVisible(false);
    pParticles->SetParticles(pExplosion);
    pParticles->SetShader(m_pExplosionShader);

    // set the particles system to the scene
    m_Scene.Add(pParticles.get(), true);
    pParticles.release();

    // create vertex format
    vf.m_Format = (DWF_Model::VertexFormat::IEFormat)((int)DWF_Model::VertexFormat::IEFormat::IE_VF_Colors |
                                                      (int)DWF_Model::VertexFormat::IEFormat::IE_VF_TexCoords);

    // create material
    mat.m_Color.m_B = 1.0f;
    mat.m_Color.m_G = 1.0f;
    mat.m_Color.m_R = 1.0f;
    mat.m_Color.m_A = 1.0f;

    // create the game over surface model
    std::shared_ptr<DWF_Model::Model> pGameOverSurface(DWF_Model::Factory::GetSurface(0.32f, 0.106f, vf, vc, mat));
    pGameOverSurface->m_Mesh[0]->m_VB[0]->m_Material.m_pTexture = OnLoadTexture("..\\..\\Resources\\Texture\\GameOver.png", true);

    // create the game over model item
    pModel = std::make_unique<DWF_Scene::SceneItem_Model>(L"scene_game_over");
    pModel->SetStatic(false);
    pModel->SetVisible(false);
    pModel->SetModel(pGameOverSurface);
    pModel->SetShader(m_pTexShader);
    pModel->SetPos(DWF_Math::Vector3F(0.0f, 0.0f, -1.0f));
    pModel->SetRoll(0.0f);
    pModel->SetPitch(0.0f);
    pModel->SetYaw(0.0f);
    pModel->SetScale(DWF_Math::Vector3F(1.0f, 1.0f, 1.0f));

    // set the model to the scene
    m_Scene.Add(pModel.get(), true);
    pModel.release();

    // bind the update physics callback to the scene
    m_Scene.Set_OnUpdatePhysics(std::bind(&Main::OnSceneUpdatePhysics, this, std::placeholders::_1, std::placeholders::_2));

    // bind the update scene callback to the scene
    m_Scene.Set_OnUpdateScene(std::bind(&Main::OnSceneUpdate, this, std::placeholders::_1, std::placeholders::_2));

    // bind the collision notification callback to the scene
    m_Scene.Set_OnCollision(std::bind(&Main::OnCollision,
                                      this,
                                      std::placeholders::_1,
                                      std::placeholders::_2,
                                      std::placeholders::_3,
                                      std::placeholders::_4,
                                      std::placeholders::_5,
                                      std::placeholders::_6));

    // bind the end reached callback to the sequencer
    m_Sequencer.Set_OnEndReached(std::bind(&Main::OnSequenceEndReached, this, std::placeholders::_1, std::placeholders::_2));

    // load background music
    std::unique_ptr<DWF_Audio::Sound_OpenAL> pSound = std::make_unique<DWF_Audio::Sound_OpenAL>();
    pSound->OpenWav(L"..\\..\\Resources\\Sound\\Music\\Electro-Jazz\\electro-jazz.wav");
    pSound->ChangeVolume(0.2f);
    pSound->Loop(true);
    pSound->Play();

    // create a sound item
    std::unique_ptr<DWF_Scene::SceneAudioItem> pSoundItem = std::make_unique<DWF_Scene::SceneAudioItem>(L"scene_background_music");
    pSoundItem->SetSound(pSound.get());
    pSound.release();

    // add sound to scene
    m_Scene.Add(pSoundItem.get());
    pSoundItem.release();

    // create events
    m_Events.push_back(std::pair<int, ShootEmUp::Entity::IESequenceType>(250,  ShootEmUp::Entity::IESequenceType::IE_ST_BottomToTop));
    m_Events.push_back(std::pair<int, ShootEmUp::Entity::IESequenceType>(300,  ShootEmUp::Entity::IESequenceType::IE_ST_BottomToTop));
    m_Events.push_back(std::pair<int, ShootEmUp::Entity::IESequenceType>(350,  ShootEmUp::Entity::IESequenceType::IE_ST_BottomToTop));
    m_Events.push_back(std::pair<int, ShootEmUp::Entity::IESequenceType>(400,  ShootEmUp::Entity::IESequenceType::IE_ST_BottomToTop));
    m_Events.push_back(std::pair<int, ShootEmUp::Entity::IESequenceType>(450,  ShootEmUp::Entity::IESequenceType::IE_ST_BottomToTop));
    m_Events.push_back(std::pair<int, ShootEmUp::Entity::IESequenceType>(1250, ShootEmUp::Entity::IESequenceType::IE_ST_TopToBottom));
    m_Events.push_back(std::pair<int, ShootEmUp::Entity::IESequenceType>(1300, ShootEmUp::Entity::IESequenceType::IE_ST_TopToBottom));
    m_Events.push_back(std::pair<int, ShootEmUp::Entity::IESequenceType>(1350, ShootEmUp::Entity::IESequenceType::IE_ST_TopToBottom));
    m_Events.push_back(std::pair<int, ShootEmUp::Entity::IESequenceType>(1400, ShootEmUp::Entity::IESequenceType::IE_ST_TopToBottom));
    m_Events.push_back(std::pair<int, ShootEmUp::Entity::IESequenceType>(1450, ShootEmUp::Entity::IESequenceType::IE_ST_TopToBottom));
    m_Events.push_back(std::pair<int, ShootEmUp::Entity::IESequenceType>(2250, ShootEmUp::Entity::IESequenceType::IE_ST_BezierCurve1));
    m_Events.push_back(std::pair<int, ShootEmUp::Entity::IESequenceType>(2300, ShootEmUp::Entity::IESequenceType::IE_ST_BezierCurve1));
    m_Events.push_back(std::pair<int, ShootEmUp::Entity::IESequenceType>(2350, ShootEmUp::Entity::IESequenceType::IE_ST_BezierCurve1));
    m_Events.push_back(std::pair<int, ShootEmUp::Entity::IESequenceType>(2400, ShootEmUp::Entity::IESequenceType::IE_ST_BezierCurve1));
    m_Events.push_back(std::pair<int, ShootEmUp::Entity::IESequenceType>(2450, ShootEmUp::Entity::IESequenceType::IE_ST_BezierCurve1));
    m_Events.push_back(std::pair<int, ShootEmUp::Entity::IESequenceType>(3250, ShootEmUp::Entity::IESequenceType::IE_ST_BezierCurve2));
    m_Events.push_back(std::pair<int, ShootEmUp::Entity::IESequenceType>(3300, ShootEmUp::Entity::IESequenceType::IE_ST_BezierCurve2));
    m_Events.push_back(std::pair<int, ShootEmUp::Entity::IESequenceType>(3350, ShootEmUp::Entity::IESequenceType::IE_ST_BezierCurve2));
    m_Events.push_back(std::pair<int, ShootEmUp::Entity::IESequenceType>(3400, ShootEmUp::Entity::IESequenceType::IE_ST_BezierCurve2));
    m_Events.push_back(std::pair<int, ShootEmUp::Entity::IESequenceType>(3450, ShootEmUp::Entity::IESequenceType::IE_ST_BezierCurve2));
    m_Events.push_back(std::pair<int, ShootEmUp::Entity::IESequenceType>(4000, ShootEmUp::Entity::IESequenceType::IE_ST_NextLevel));

    return true;
}
//---------------------------------------------------------------------------
