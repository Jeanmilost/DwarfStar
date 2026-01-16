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
#include "DWF_IQM.h"
#include "DWF_Wavefront.h"
#include "DWF_BoxCollider.h"
#include "DWF_SphereCollider.h"
#include "DWF_CylinderCollider.h"
#include "DWF_CapsuleCollider.h"
#include "DWF_GJK.h"
#include "DWF_Camera.h"
#include "DWF_Arcball.h"
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
                        Main::GetInstance()->SetShowSkeleton(!Main::GetInstance()->GetShowSkeleton());

                    break;

                case '2':
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

    m_pSkybox    = new Nebulus::Skybox   (&m_Scene);
    m_pTower     = new Nebulus::Tower    (&m_Scene);
    m_pPlatforms = new Nebulus::Platforms(&m_Scene);
    m_pWater     = new Nebulus::Water    (&m_Scene);
    m_pPlayer    = new Nebulus::Player   (&m_Scene);
}
//---------------------------------------------------------------------------
Main::~Main()
{
    if (m_pSkybox)
        delete m_pSkybox;

    if (m_pTower)
        delete m_pTower;

    if (m_pPlatforms)
        delete m_pPlatforms;

    if (m_pWater)
        delete m_pWater;

    if (m_pPlayer)
        delete m_pPlayer;
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
    wcex.lpszClassName = L"NebulusTowerDemo";

    if (!RegisterClassEx(&wcex))
        return 0;

    // create main window
    HWND hWnd = ::CreateWindowEx(0,
                                 L"NebulusTowerDemo",
                                 L"DwarfStar Nebulus Tower Demo",
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

    // load texture shader
    std::shared_ptr<DWF_Renderer::Shader_OpenGL> pTexShader = std::make_unique<DWF_Renderer::Shader_OpenGL>();
    pTexShader->CreateProgram();
    pTexShader->Attach(DWF_Renderer::Shader_Collection_OpenGL::GetVertexShader(DWF_Renderer::Shader_Collection_OpenGL::IEShaderType::IE_ST_Texture),
            DWF_Renderer::Shader::IEType::IE_ST_Vertex);
    pTexShader->Attach(DWF_Renderer::Shader_Collection_OpenGL::GetFragmentShader(DWF_Renderer::Shader_Collection_OpenGL::IEShaderType::IE_ST_Texture),
            DWF_Renderer::Shader::IEType::IE_ST_Fragment);
    pTexShader->Link(true);

    // load color shader
    std::shared_ptr<DWF_Renderer::Shader_OpenGL> pColShader = std::make_unique<DWF_Renderer::Shader_OpenGL>();
    pColShader->CreateProgram();
    pColShader->Attach(DWF_Renderer::Shader_Collection_OpenGL::GetVertexShader(DWF_Renderer::Shader_Collection_OpenGL::IEShaderType::IE_ST_Color),
            DWF_Renderer::Shader::IEType::IE_ST_Vertex);
    pColShader->Attach(DWF_Renderer::Shader_Collection_OpenGL::GetFragmentShader(DWF_Renderer::Shader_Collection_OpenGL::IEShaderType::IE_ST_Color),
            DWF_Renderer::Shader::IEType::IE_ST_Fragment);
    pColShader->Link(true);

    // load skybox shader
    std::shared_ptr<DWF_Renderer::Shader_OpenGL> pSkyboxShader = std::make_unique<DWF_Renderer::Shader_OpenGL>();
    pSkyboxShader->CreateProgram();
    pSkyboxShader->Attach(DWF_Renderer::Shader_Collection_OpenGL::GetVertexShader(DWF_Renderer::Shader_Collection_OpenGL::IEShaderType::IE_ST_Skybox),
            DWF_Renderer::Shader::IEType::IE_ST_Vertex);
    pSkyboxShader->Attach(DWF_Renderer::Shader_Collection_OpenGL::GetFragmentShader(DWF_Renderer::Shader_Collection_OpenGL::IEShaderType::IE_ST_Skybox),
            DWF_Renderer::Shader::IEType::IE_ST_Fragment);
    pSkyboxShader->Link(true);

    // load water shader
    std::shared_ptr<DWF_Renderer::Shader_OpenGL> pWaterShader = std::make_unique<DWF_Renderer::Shader_OpenGL>();
    pWaterShader->CreateProgram();
    pWaterShader->Attach(DWF_Renderer::Shader_Collection_OpenGL::GetVertexShader(DWF_Renderer::Shader_Collection_OpenGL::IEShaderType::IE_ST_Water),
            DWF_Renderer::Shader::IEType::IE_ST_Vertex);
    pWaterShader->Attach(DWF_Renderer::Shader_Collection_OpenGL::GetFragmentShader(DWF_Renderer::Shader_Collection_OpenGL::IEShaderType::IE_ST_Water),
            DWF_Renderer::Shader::IEType::IE_ST_Fragment);
    pWaterShader->Link(true);

    DWF_Math::Matrix4x4F projMatrix;

    // create the viewport
    m_Renderer.CreateViewport(float(clientRect.right - clientRect.left),
                              float(clientRect.bottom - clientRect.top),
                              0.1f,
                              100.0f,
                              pTexShader.get(),
                              projMatrix);

    // connect the projection matrix to the other shaders
    m_Renderer.ConnectProjectionMatrixToShader(pColShader.get(),    projMatrix);
    m_Renderer.ConnectProjectionMatrixToShader(pSkyboxShader.get(), projMatrix);
    m_Renderer.ConnectProjectionMatrixToShader(pWaterShader.get(),  projMatrix);

    IShaders shaders;
    shaders.push_back(pTexShader);
    shaders.push_back(pColShader);
    shaders.push_back(pSkyboxShader);
    shaders.push_back(pWaterShader);

    // create and configure the scene
    LoadScene(shaders, clientRect);

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

            // do show or hide the skeleton?
            if (m_ShowSkeleton != m_OldShowSkeleton)
            {
                DWF_Scene::SceneItem_AnimAsset* pModelItem = static_cast<DWF_Scene::SceneItem_AnimAsset*>(m_Scene.SearchItem(L"scene_player_model"));

                if (pModelItem)
                    pModelItem->SetDrawSkeleton(m_ShowSkeleton);

                m_OldShowSkeleton = m_ShowSkeleton;
            }

            // do show or hide the colliders?
            if (m_ShowColliders != m_OldShowColliders)
            {
                DWF_Scene::SceneItem_Model* pModelCollider = static_cast<DWF_Scene::SceneItem_Model*>(m_Scene.SearchItem(L"scene_player_collider"));

                if (pModelCollider)
                    pModelCollider->SetVisible(m_ShowColliders);

                pModelCollider = static_cast<DWF_Scene::SceneItem_Model*>(m_Scene.SearchItem(L"scene_platform_collider"));

                if (pModelCollider)
                    pModelCollider->SetVisible(m_ShowColliders);

                pModelCollider = static_cast<DWF_Scene::SceneItem_Model*>(m_Scene.SearchItem(L"scene_platform_collider_2"));

                if (pModelCollider)
                    pModelCollider->SetVisible(m_ShowColliders);

                pModelCollider = static_cast<DWF_Scene::SceneItem_Model*>(m_Scene.SearchItem(L"scene_platform_collider_3"));

                if (pModelCollider)
                    pModelCollider->SetVisible(m_ShowColliders);

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
DWF_Model::Texture* Main::LoadTexture(const Nebulus::Item& item, const std::string& texturePath, const std::string& textureName, bool is32bit)
{
    // search for an existing texture
    ITextures::iterator it = m_TextureItems.find(textureName);

    // is texture already loaded?
    if (it == m_TextureItems.end())
    {
        std::unique_ptr<DWF_Model::Texture_OpenGL> pTexture(item.LoadTexture(texturePath + textureName, is32bit));

        m_TextureItems[textureName] = pTexture.get();

        return pTexture.release();
    }

    // clone the texture, thus it will point on the same already loaded one
    std::unique_ptr<DWF_Model::Texture_OpenGL> pTexture(static_cast<DWF_Model::Texture_OpenGL*>(it->second->Clone()));

    return pTexture.release();
}
//------------------------------------------------------------------------------
DWF_Model::Texture* Main::OnLoadPlayerTexture(const std::string& textureName, bool is32bit)
{
    return LoadTexture(*m_pPlayer, "..\\..\\Resources\\Model\\Robot\\Textures\\", textureName, is32bit);
}
//------------------------------------------------------------------------------
DWF_Model::Texture* Main::OnLoadTowerTexture(const std::string& textureName, bool is32bit)
{
    return LoadTexture(*m_pTower, "..\\..\\Resources\\Texture\\", textureName, is32bit);
}
//------------------------------------------------------------------------------
void Main::OnSceneUpdatePhysics(const DWF_Scene::Scene* pScene, double elapsedTime)
{
    if (!pScene)
        return;

    // animate the player
    m_pPlayer->Animate(pScene, elapsedTime);

    // animate the water
    m_pWater->Animate(pScene, elapsedTime);
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
    // apply the collision on player
    m_pPlayer->ApplyCollision(pScene, pItem1, pCollider1, pItem2, pCollider2, mtv);
}
//------------------------------------------------------------------------------
void Main::OnAttachTowerTextureFn(std::shared_ptr<DWF_Model::Model>& pModel)
{
    pModel->m_Mesh[0]->m_VB[0]->m_Material.m_pTexture = OnLoadTowerTexture("NebulusTowerBlue.png", true);
}
//------------------------------------------------------------------------------
void Main::OnAttachPlayerTextureFn(std::shared_ptr<DWF_Model::IQM>& pIqm)
{
    pIqm->Set_OnLoadTexture(std::bind(&Main::OnLoadPlayerTexture, this, std::placeholders::_1, std::placeholders::_2));
}
//------------------------------------------------------------------------------
bool Main::LoadScene(const IShaders& shaders, const RECT& clientRect)
{
    // configure the background color
    DWF_Model::ColorF bgColor;
    bgColor.m_R = 0.08f;
    bgColor.m_G = 0.12f;
    bgColor.m_B = 0.17f;
    bgColor.m_A = 1.0f;

    m_Scene.SetRenderer(m_Renderer);
    m_Scene.SetColor(bgColor);

    // load the skybox and add it to the scene
    if (!m_pSkybox->Load(shaders[2]))
        return false;

    // attach the player texture loader
    m_pPlayer->Set_OnAttachTextureFunction(std::bind(&Main::OnAttachPlayerTextureFn, this, std::placeholders::_1));

    // load the player model and add it to the scene
    if (!m_pPlayer->Load(shaders[0], shaders[1]))
        return false;

    // attach the tower texture loader
    m_pTower->Set_OnAttachTextureFunction(std::bind(&Main::OnAttachTowerTextureFn, this, std::placeholders::_1));

    // load the tower model and add it to the scene
    if (!m_pTower->Load(shaders[0]))
        return false;

    // create platforms and add them to scene
    if (!m_pPlatforms->Load(shaders[1]))
        return false;

    // create water and add it to scene
    if (!m_pWater->Load(shaders[3]))
        return false;

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

    return true;
}
//---------------------------------------------------------------------------
