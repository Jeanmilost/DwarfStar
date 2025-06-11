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
                /*REM
                case '1':
                    if (Main::GetInstance())
                        Main::GetInstance()->SetShowSkeleton(!Main::GetInstance()->GetShowSkeleton());

                    break;
                */

                case '1':
                    if (Main::GetInstance())
                        Main::GetInstance()->SetShowColliders(!Main::GetInstance()->GetShowColliders());

                    break;

                /*REM
                case '3':
                    if (Main::GetInstance())
                        Main::GetInstance()->ChangeCameraType();

                    break;
                */

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
    /*REM
    if (m_SkyboxTexId != -1)
        glDeleteTextures(1, &m_SkyboxTexId);
    */
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
    HWND hWnd = ::CreateWindowEx(0,
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

    ::ShowWindow(hWnd, nCmdShow);

    // get the window client rect
    RECT clientRect;
    ::GetClientRect(hWnd, &clientRect);

    // get the window device context
    HDC hDC = ::GetDC(hWnd);

    // please wait text background
    HBRUSH hBrush = ::CreateSolidBrush(RGB(20, 30, 43));
    ::FillRect(hDC, &clientRect, hBrush);
    ::DeleteObject(hBrush);

    // please wait text
    ::SetBkMode(hDC, TRANSPARENT);
    ::SetBkColor(hDC, 0x000000);
    ::SetTextColor(hDC, 0xffffff);
    ::DrawText(hDC, L"Please wait...", 14, &clientRect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
    ::ReleaseDC(hWnd, hDC);

    DWF_Audio::OpenAL* pOpenALInstance = DWF_Audio::OpenAL::GetInstance();

    // enable OpenGL for the window
    m_Renderer.EnableOpenGL(hWnd);

    // stop GLEW crashing on OSX :-/
    glewExperimental = GL_TRUE;

    // initialize GLEW
    if (glewInit() != GLEW_OK)
    {
        // shutdown OpenGL
        m_Renderer.DisableOpenGL(hWnd);

        // destroy the window explicitly
        ::DestroyWindow(hWnd);

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

            /*REM
            // do show or hide the skeleton?
            if (m_ShowSkeleton != m_OldShowSkeleton)
            {
                DWF_Scene::SceneItem_Animation* pModelItem = static_cast<DWF_Scene::SceneItem_Animation*>(m_Scene.SearchItem(L"scene_player_model"));

                if (pModelItem)
                    pModelItem->SetDrawSkeleton(m_ShowSkeleton);

                m_OldShowSkeleton = m_ShowSkeleton;
            }
            */

            // do show or hide the colliders?
            if (m_ShowColliders != m_OldShowColliders)
            {
                DWF_Scene::SceneItem_Model* pModelCollider = static_cast<DWF_Scene::SceneItem_Model*>(m_Scene.SearchItem(L"scene_spaceship_collider"));

                if (pModelCollider)
                    pModelCollider->SetVisible(m_ShowColliders);

                pModelCollider = static_cast<DWF_Scene::SceneItem_Model*>(m_Scene.SearchItem(L"scene_enemy_collider_0"));

                if (pModelCollider)
                    pModelCollider->SetVisible(m_ShowColliders);

                /*REM
                pModelCollider = static_cast<DWF_Scene::SceneItem_Model*>(m_Scene.SearchItem(L"scene_platform_collider"));

                if (pModelCollider)
                    pModelCollider->SetVisible(m_ShowColliders);

                pModelCollider = static_cast<DWF_Scene::SceneItem_Model*>(m_Scene.SearchItem(L"scene_platform_collider_2"));

                if (pModelCollider)
                    pModelCollider->SetVisible(m_ShowColliders);

                pModelCollider = static_cast<DWF_Scene::SceneItem_Model*>(m_Scene.SearchItem(L"scene_platform_collider_3"));

                if (pModelCollider)
                    pModelCollider->SetVisible(m_ShowColliders);
                */

                m_OldShowColliders = m_ShowColliders;
            }

            // render the scene
            m_Scene.Render(elapsedTime);
        }

    // shutdown OpenGL
    m_Renderer.DisableOpenGL(hWnd);

    // destroy the window explicitly
    ::DestroyWindow(hWnd);

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
/*REM
void Main::OnFrame(const DWF_Scene::SceneItem_Animation* pAnim, const DWF_Scene::SceneItem_Animation::IAnimDesc* pAnimDesc)
{}
*/
//---------------------------------------------------------------------------
/*REM
void Main::OnEndReached(const DWF_Scene::SceneItem_Animation* pAnim, const DWF_Scene::SceneItem_Animation::IAnimDesc* pAnimDesc)
{}
*/
//------------------------------------------------------------------------------
void Main::OnSceneUpdatePhysics(const DWF_Scene::Scene* pScene, double elapsedTime)
{
    if (!pScene)
        return;

    // get the objects of interest from scene
    DWF_Scene::SceneItem_StaticAsset* pModelItem     = static_cast<DWF_Scene::SceneItem_StaticAsset*>(pScene->SearchItem(L"scene_spaceship"));
    DWF_Scene::SceneItem_Model*       pModelCollider = static_cast<DWF_Scene::SceneItem_Model*>      (pScene->SearchItem(L"scene_spaceship_collider"));

    const float spaceshipSpeed         = 0.25f;
    const float spaceshipRotationSpeed = 0.05f;

    /*REM
    // fire
    if (::GetKeyState(VK_SPACE) & 0x8000)
    {
        AddEnemy(m_Index, (float)(-19 + (std::rand() % 38)), (float)(-15 + (std::rand() % 30)));
        ++m_Index;
    }
    else
    if (::GetKeyState(VK_DELETE) & 0x8000)
    {
        --m_Index;
        DelEnemy(m_Index);
    }
    */

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
{}
//------------------------------------------------------------------------------
void Main::OnCollision(const DWF_Scene::Scene*       pScene,
                             DWF_Scene::SceneItem*   pItem1,
                             DWF_Collider::Collider* pCollider1,
                             DWF_Scene::SceneItem*   pItem2,
                             DWF_Collider::Collider* pCollider2,
                       const DWF_Math::Vector3F&     mtv)
{
    if (pItem1->GetName() != L"scene_spaceship_collider" && pItem2->GetName() != L"scene_spaceship_collider")
        return;

    int ii = 0;

    /*REM
    // as in this demo all the objects against which the player may collide are platforms, we can assume that in case of collisions the player is grounded
    m_Grounded = true;

    // use the minimum translation vector to correct the cached position
    m_xPos -= mtv.m_X;
    m_yPos += mtv.m_Y;
    m_zPos -= mtv.m_Z;

    if (!pItem1)
        return;

    // get the point of view from the scene
    DWF_Scene::SceneItem_PointOfView* pPOV = static_cast<DWF_Scene::SceneItem_PointOfView*>(pScene->SearchItem(L"scene_arcball"));

    if (!pPOV)
        return;

    // get the player model from the scene
    DWF_Scene::SceneItem_Animation* pPlayer = static_cast<DWF_Scene::SceneItem_Animation*>(pScene->SearchItem(L"scene_player_model"));

    if (!pPlayer)
        return;

    // apply modifications to player (to avoid a parasite thrill effect)
    pPOV->SetPos      (DWF_Math::Vector3F( m_xPos, -m_yPos - 0.5f,  2.0f + m_zPos));
    pPlayer->SetPos   (DWF_Math::Vector3F(-m_xPos,  m_yPos,        -2.0f - m_zPos));
    pItem1->SetPos    (DWF_Math::Vector3F(-m_xPos,  m_yPos,        -2.0f - m_zPos));
    pCollider1->SetPos(DWF_Math::Vector3F(-m_xPos,  m_yPos,        -2.0f - m_zPos));
    */
}
//------------------------------------------------------------------------------
bool Main::OnDoSpawn(DWF_Scene::Spawner* pSpawner)
{
    ++m_Index;

    if (m_Index == 250 || m_Index == 300 || m_Index == 350 || m_Index == 400 || m_Index == 450)
    {
        std::unique_ptr<ShootEmUp::Sequencer::ISequence> pSequence = std::make_unique<ShootEmUp::Sequencer::ISequence>();
        pSequence->m_Name     = L"enemy_" + std::to_wstring(m_Index);
        pSequence->m_Position = DWF_Math::Vector3F(20.0f, -14.0f, -40.0f);

        std::unique_ptr<ShootEmUp::Sequencer::ICommand> pCmd = std::make_unique<ShootEmUp::Sequencer::ICommand>();
        pCmd->m_Direction = DWF_Math::Vector3F(-1.0f, 0.0f, 0.0f);
        pCmd->m_Length    = 35.0f;
        pCmd->m_Time      = 2000.0;
        pSequence->m_Pattern.push_back(pCmd.get());
        pCmd.release();

        pCmd = std::make_unique<ShootEmUp::Sequencer::ICommand>();
        pCmd->m_Direction = DWF_Math::Vector3F(1.0f, 0.75f, 0.0f);
        pCmd->m_Length    = 35.0f;
        pCmd->m_Time      = 2000.0;
        pSequence->m_Pattern.push_back(pCmd.get());
        pCmd.release();

        pCmd = std::make_unique<ShootEmUp::Sequencer::ICommand>();
        pCmd->m_Direction = DWF_Math::Vector3F(-1.0f, 0.0f, 0.0f);
        pCmd->m_Length    = 45.0f;
        pCmd->m_Time      = 2000.0;
        pSequence->m_Pattern.push_back(pCmd.get());
        pCmd.release();

        m_Sequencer.Add(pSequence.get());
        pSequence.release();

        return true;
    }

    return false;
}
//------------------------------------------------------------------------------
void Main::OnSpawned(DWF_Scene::Spawner* pSpawner, DWF_Scene::Spawner::IItem* pItem)
{
    float x = 20.0f;
    float y = 14.0f;

    std::unique_ptr<ShootEmUp::Entity> pEntity = std::make_unique<ShootEmUp::Entity>(L"enemy_" + std::to_wstring(m_Index),
                                                                                     m_pEnemyMdl,
                                                                                     m_pEnemyBox,
                                                                                     m_pTexShader,
                                                                                     m_pColShader);

    pEntity->AddAsset(pItem, m_Scene, x, y);
    m_Entities[pItem] = pEntity.get();
    pEntity.release();

    /*REM
    m_OldPos = DWF_Math::Vector3F(x, y, -40.0f);

    // create the player spaceship scene model item
    std::unique_ptr<DWF_Scene::SceneItem_StaticAsset> pStaticModel =
            std::make_unique<DWF_Scene::SceneItem_StaticAsset>(L"scene_enemy_1");
    pStaticModel->SetStatic(true);
    pStaticModel->SetModel(m_pEnemyMdl);
    pStaticModel->SetShader(m_pTexShader);
    pStaticModel->SetPos(DWF_Math::Vector3F(x, y, -40.0f));
    pStaticModel->SetRoll(-0.25f);
    pStaticModel->SetPitch((float)(M_PI / 2.0));
    pStaticModel->SetYaw((float)(M_PI / 2.0));
    pStaticModel->SetScale(DWF_Math::Vector3F(2.0f, 2.0f, 2.0f));

    // set the model to the scene
    m_Scene.Add(pStaticModel.get(), false);
    pItem->m_pModel = pStaticModel.release();

    // create the capsule model item
    std::unique_ptr<DWF_Scene::SceneItem_Model> pModel =
            std::make_unique<DWF_Scene::SceneItem_Model>(L"scene_enemy_collider_1");
    pModel->SetStatic(false);
    pModel->SetVisible(false);
    pModel->SetModel(m_pEnemyBox);
    pModel->SetShader(m_pColShader);
    pModel->SetPos(DWF_Math::Vector3F(x - 0.35f, y, -40.0f));
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
    pItem->m_pCollider = pModel.release();
    */
}
//------------------------------------------------------------------------------
bool Main::OnDoDelete(DWF_Scene::Spawner* pSpawner, DWF_Scene::Spawner::IItem* pItem)
{
    /*
    if (m_Index == 2500)
    {
        // delete the collider item from the scene
        if (pItem->m_pCollider)
            m_Scene.Delete(pItem->m_pCollider);

        // delete the model item from the scene
        if (pItem->m_pModel)
            m_Scene.Delete(pItem->m_pModel);

        return true;
    }
    */

    return false;
}
//------------------------------------------------------------------------------
void Main::OnCalculateMotion(DWF_Scene::Spawner* pSpawner, DWF_Scene::Spawner::IItem* pItem, double elapsedTime)
{
    ShootEmUp::Entities::iterator it = m_Entities.find(pItem);

    if (it == m_Entities.end())
        return;

    it->second->Move(&m_Sequencer, pItem, elapsedTime);

    /*REM
    const float spaceshipRotationSpeed = 0.0025f;

    const DWF_Math::Vector3F position = m_Sequencer.GetPosition(L"first_enemy", elapsedTime);

    if (position.m_Y != m_OldPos.m_Y)
        m_EnemyAngle = std::max(m_EnemyAngle - (spaceshipRotationSpeed * (float)elapsedTime), 0.0f);
    else
        m_EnemyAngle = std::min(m_EnemyAngle + (spaceshipRotationSpeed * (float)elapsedTime), (float)(M_PI / 2.0));

    if (pItem->m_pCollider)
    {
        pItem->m_pCollider->SetPos(position);
        pItem->m_pCollider->SetRoll(m_EnemyAngle);
    }

    if (pItem->m_pModel)
    {
        pItem->m_pModel->SetPos(position);
        pItem->m_pModel->SetPitch(m_EnemyAngle);
    }

    m_OldPos = position;
    */
}
//------------------------------------------------------------------------------
/*REM
void Main::AddEnemy(std::size_t index, float x, float y)
{
    // create the player spaceship scene model item
    std::unique_ptr<DWF_Scene::SceneItem_StaticAsset> pStaticModel =
            std::make_unique<DWF_Scene::SceneItem_StaticAsset>(L"scene_enemy_" + std::to_wstring(index));
    pStaticModel->SetStatic(true);
    pStaticModel->SetModel(m_pEnemyMdl);
    pStaticModel->SetShader(m_pTexShader);
    pStaticModel->SetPos(DWF_Math::Vector3F(x, y, -40.0f));
    pStaticModel->SetRoll(-0.25f);
    pStaticModel->SetPitch((float)M_PI + m_Angle);
    pStaticModel->SetYaw((float)(M_PI / 2.0));
    pStaticModel->SetScale(DWF_Math::Vector3F(2.0f, 2.0f, 2.0f));

    // set the model to the scene
    m_Scene.Add(pStaticModel.get(), false);
    pStaticModel.release();

    // create the capsule model item
    std::unique_ptr<DWF_Scene::SceneItem_Model> pModel =
            std::make_unique<DWF_Scene::SceneItem_Model>(L"scene_enemy_collider_" + std::to_wstring(index));
    pModel->SetStatic(false);
    pModel->SetVisible(false);
    pModel->SetModel(m_pEnemyBox);
    pModel->SetShader(m_pColShader);
    pModel->SetPos(DWF_Math::Vector3F(x - 0.35f, y, -40.0f));
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

    m_Enemies.push_back(index);
}
*/
//------------------------------------------------------------------------------
/*REM
void Main::DelEnemy(std::size_t index)
{
    DWF_Scene::SceneItem_StaticAsset* pModel =
            static_cast<DWF_Scene::SceneItem_StaticAsset*>(m_Scene.SearchItem(L"scene_enemy_" + std::to_wstring(index)));

    if (pModel)
        m_Scene.Delete(pModel);

    DWF_Scene::SceneItem_Model* pModelCollider =
            static_cast<DWF_Scene::SceneItem_Model*>(m_Scene.SearchItem(L"scene_enemy_collider_" + std::to_wstring(index)));

    if (pModelCollider)
        m_Scene.Delete(pModelCollider);

    for (std::size_t i = 0; i < m_Enemies.size(); ++i)
        if (m_Enemies[i] == index)
        {
            m_Enemies.erase(m_Enemies.begin() + i);
            break;
        }
}
*/
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

    DWF_Math::Matrix4x4F projMatrix;

    // create the viewport
    m_Renderer.CreateViewport(float(clientRect.right  - clientRect.left),
                              float(clientRect.bottom - clientRect.top),
                              0.1f,
                              100.0f,
                              m_pTexShader.get(),
                              projMatrix);

    // connect the projection matrix to the other shaders
    m_Renderer.ConnectProjectionMatrixToShader(m_pColShader.get(),  projMatrix);
    m_Renderer.ConnectProjectionMatrixToShader(m_pStarShader.get(), projMatrix);

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
    vf.m_Type   =  DWF_Model::VertexFormat::IEType::IE_VT_Triangles;
    vf.m_Format = DWF_Model::VertexFormat::IEFormat::IE_VF_Colors;

    // create material
    mat.m_Color.m_B = 1.0f;
    mat.m_Color.m_G = 0.0f;
    mat.m_Color.m_R = 0.0f;
    mat.m_Color.m_A = 1.0f;

    // create the spaceship box model
    std::shared_ptr<DWF_Model::Model> pSpaceshipBox(DWF_Model::Factory::GetBox(4.0f, 2.0f, 1.5f, false, vf, vc, mat));

    // create the capsule model item
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

    // load enemy spaceship, keep it globally in order to allow new spaceship to be spawned on runtime
    m_pEnemyMdl = std::make_shared<DWF_Model::MDL>();
    m_pEnemyMdl->Set_OnCreateTexture(std::bind(&Main::OnCreateTexture, this, std::placeholders::_1));
    m_pEnemyMdl->Open("..\\..\\Resources\\Model\\Spaceships\\spaceship_red.mdl");

    mat.m_Color.m_B = 0.0f;
    mat.m_Color.m_R = 1.0f;

    // create the spaceship box model
    m_pEnemyBox.reset(DWF_Model::Factory::GetBox(4.0f, 2.0f, 1.5f, false, vf, vc, mat));

    // create a spawner for the enemies and add it to scene
    std::unique_ptr<DWF_Scene::Spawner> pEnemySpawner = std::make_unique<DWF_Scene::Spawner>(L"scene_enemy_spawner");
    pEnemySpawner->Set_OnDoSpawn(std::bind(&Main::OnDoSpawn, this, std::placeholders::_1));
    pEnemySpawner->Set_OnSpawned(std::bind(&Main::OnSpawned, this, std::placeholders::_1, std::placeholders::_2));
    pEnemySpawner->Set_OnDoDelete(std::bind(&Main::OnDoDelete, this, std::placeholders::_1, std::placeholders::_2));
    pEnemySpawner->Set_OnCalculateMotion(std::bind(&Main::OnCalculateMotion, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
    m_Scene.AddSpawner(pEnemySpawner.get());
    pEnemySpawner.release();

    /*REM
    for (std::size_t i = 0; i < 5; ++i)
        AddEnemy(i, 999.0f, 0.0f + i, m_pEnemyMdl, m_pEnemyBox, pTexShader, pColShader);
    */

    // create material
    mat.m_Color.m_B = 0.95f;
    mat.m_Color.m_G = 0.98f;
    mat.m_Color.m_R = 1.0f;
    mat.m_Color.m_A = 1.0f;

    // create the star model
    std::shared_ptr<DWF_Model::Model> pStarModel(DWF_Model::Factory::GetSphere(0.1f, 20, 20, vf, vc, mat));

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

    // create the capsule model item
    std::unique_ptr<DWF_Scene::SceneItem_Particles> pParticles = std::make_unique<DWF_Scene::SceneItem_Particles>(L"scene_stars_particles");
    pParticles->SetStatic(true);
    pParticles->SetVisible(true);
    pParticles->SetParticles(pStars);
    pParticles->SetShader(m_pStarShader);

    // set the particles system to the scene
    m_Scene.Add(pParticles.get(), false);
    pParticles.release();

    // bind the update physics callback to the scene
    m_Scene.Set_OnUpdatePhysics(std::bind(&Main::OnSceneUpdatePhysics, this, std::placeholders::_1, std::placeholders::_2));

    /*REM
    // bind the update scene callback to the scene
    m_Scene.Set_OnUpdateScene(std::bind(&Main::OnSceneUpdate, this, std::placeholders::_1, std::placeholders::_2));
    */

    // bind the collision notification callback to the scene
    m_Scene.Set_OnCollision(std::bind(&Main::OnCollision,
                                      this,
                                      std::placeholders::_1,
                                      std::placeholders::_2,
                                      std::placeholders::_3,
                                      std::placeholders::_4,
                                      std::placeholders::_5,
                                      std::placeholders::_6));

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

    return true;
}
//---------------------------------------------------------------------------
