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

                case '3':
                    if (Main::GetInstance())
                        Main::GetInstance()->ChangeCameraType();

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
    if (m_SkyboxTexId != -1)
        glDeleteTextures(1, &m_SkyboxTexId);
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
    wcex.lpszClassName = L"PlatformerDemo";

    if (!RegisterClassEx(&wcex))
        return 0;

    // create main window
    HWND hWnd = ::CreateWindowEx(0,
                                 L"PlatformerDemo",
                                 L"DwarfStar Platformer Demo",
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

    DWF_Math::Matrix4x4F projMatrix;

    // create the viewport
    m_Renderer.CreateViewport(float(clientRect.right - clientRect.left),
                              float(clientRect.bottom - clientRect.top),
                              0.1f,
                              100.0f,
                              pTexShader.get(),
                              projMatrix);

    // connect the projection matrix to the other shaders
    m_Renderer.ConnectProjectionMatrixToShader(pColShader.get(), projMatrix);
    m_Renderer.ConnectProjectionMatrixToShader(pSkyboxShader.get(), projMatrix);

    // create and configure the scene
    LoadScene(pTexShader, pColShader, pSkyboxShader, clientRect);

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
DWF_Model::Texture* Main::OnLoadCharTexture(const std::string& textureName, bool is32bit)
{
    // search for an existing texture
    Textures::iterator it = m_TextureItems.find(textureName);

    // is texture already loaded?
    if (it == m_TextureItems.end())
    {
        std::unique_ptr<DWF_Buffer::PixelBuffer> pPixelBuffer = std::make_unique<DWF_Buffer::PixelBuffer>();

        // load the texture
        if (!pPixelBuffer->FromPng("..\\..\\Resources\\Model\\Platformer\\Player\\Textures\\" + textureName, true))
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

        m_TextureItems[textureName] = pTexture.get();

        return pTexture.release();
    }

    // clone the texture, thus it will point on the same already loaded one
    std::unique_ptr<DWF_Model::Texture_OpenGL> pTexture(static_cast<DWF_Model::Texture_OpenGL*>(it->second->Clone()));

    return pTexture.release();
}
//------------------------------------------------------------------------------
DWF_Model::Texture* Main::OnLoadPlatformTexture(const std::string& textureName, bool is32bit)
{
    // search for an existing texture
    Textures::iterator it = m_TextureItems.find(textureName);

    // is texture already loaded?
    if (it == m_TextureItems.end())
    {
        std::unique_ptr<DWF_Buffer::PixelBuffer> pPixelBuffer = std::make_unique<DWF_Buffer::PixelBuffer>();

        // load the texture
        if (!pPixelBuffer->FromPng("..\\..\\Resources\\Model\\Platformer\\Platform\\" + textureName, true))
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

        m_TextureItems[textureName] = pTexture.get();

        return pTexture.release();
    }

    // clone the texture, thus it will point on the same already loaded one
    std::unique_ptr<DWF_Model::Texture_OpenGL> pTexture(static_cast<DWF_Model::Texture_OpenGL*>(it->second->Clone()));

    return pTexture.release();
}
//---------------------------------------------------------------------------
bool Main::OnOpenMaterialFile(const std::string& fileName, DWF_Buffer::Buffer*& pFileBuffer)
{
    std::unique_ptr<DWF_Buffer::StdFileBuffer> pBuffer = std::make_unique<DWF_Buffer::StdFileBuffer>();
    pBuffer->Open("..\\..\\Resources\\Model\\Platformer\\Platform\\" + fileName, DWF_Buffer::StdFileBuffer::IEMode::IE_M_Read);

    pFileBuffer = pBuffer.release();

    return true;
}
//---------------------------------------------------------------------------
void Main::OnFrame(const DWF_Scene::SceneItem_AnimAsset* pAnim, const DWF_Scene::SceneItem_AnimAsset::IAnimDesc* pAnimDesc)
{}
//---------------------------------------------------------------------------
void Main::OnEndReached(const DWF_Scene::SceneItem_AnimAsset* pAnim, const DWF_Scene::SceneItem_AnimAsset::IAnimDesc* pAnimDesc)
{}
//------------------------------------------------------------------------------
void Main::OnSceneUpdatePhysics(const DWF_Scene::Scene* pScene, double elapsedTime)
{
    if (!pScene)
        return;

    // get the objects of interest from scene
    DWF_Scene::SceneItem_PointOfView* pArcballItem   = static_cast<DWF_Scene::SceneItem_PointOfView*>(pScene->SearchItem (L"scene_arcball"));
    DWF_Scene::SceneItem_AnimAsset*   pModelItem     = static_cast<DWF_Scene::SceneItem_AnimAsset*>  (pScene->SearchItem (L"scene_player_model"));
    DWF_Scene::SceneItem_Model*       pModelCollider = static_cast<DWF_Scene::SceneItem_Model*>      (pScene->SearchItem (L"scene_player_collider"));
    DWF_Scene::SceneAudioItem*        pSoundItem     =                                                pScene->SearchAudio(L"sound_footsteps");

    if (!pArcballItem || !pModelItem || !pModelCollider || !pSoundItem)
        return;

    // player is jumping?
    if (m_Grounded)
        // space bar pressed?
        if (::GetKeyState(VK_SPACE) & 0x8000)
        {
            // add jump force to scene force
            m_Force.Add(DWF_Math::Vector3F(0.0f, m_JumpVelocity * (float)elapsedTime, 0.0f));

            m_Jumping = true;
        }
        else
            m_Jumping = false;

    // left (or "A") or right (or "D") key pressed?
    if ((::GetKeyState(m_CameraType == IECameraType::IE_CT_Follow ? VK_DOWN : VK_LEFT) & 0x8000) ||
        (::GetKeyState(m_CameraType == IECameraType::IE_CT_Follow ? 83 : 65) & 0x8000))
    {
        m_Walking    =  true;
        m_WalkOffset = -1.0f;

        // add left move force to scene force
        m_Force.Add(DWF_Math::Vector3F(0.0f, 0.0f, m_Velocity * (float)elapsedTime));
    }
    else
    if ((::GetKeyState(m_CameraType == IECameraType::IE_CT_Follow ? VK_UP : VK_RIGHT) & 0x8000) ||
        (::GetKeyState(m_CameraType == IECameraType::IE_CT_Follow ? 87 : 68) & 0x8000))
    {
        m_Walking    = true;
        m_WalkOffset = 1.0f;

        // add right move force to scene force
        m_Force.Add(DWF_Math::Vector3F(0.0f, 0.0f , -m_Velocity * (float)elapsedTime));
    }
    else
        m_Walking = false;

    // apply state machine
    if (m_Jumping)
    {
        if (pModelItem->GetSelectedAnim() != 3)
            pModelItem->SelectAnim(3);

        pSoundItem->GetSound()->Stop();
    }
    else
    if (m_Walking)
    {
        if (pModelItem->GetSelectedAnim() != 2)
            pModelItem->SelectAnim(2);

        if (!pSoundItem->GetSound()->IsPlaying())
            pSoundItem->GetSound()->Play();
    }
    else
    {
        if (pModelItem->GetSelectedAnim() != 0)
            pModelItem->SelectAnim(0);

        pSoundItem->GetSound()->Stop();
    }

    // update gravity and friction depending on time
    m_Force.SetGravity (0.0025f * (float)elapsedTime);
    m_Force.SetFriction(0.0003f * (float)elapsedTime);

    // calculate the resulting force
    const DWF_Math::Vector3F force = m_Force.Calculate();

    // apply it to the player position
    m_xPos += force.m_X;
    m_yPos += force.m_Y;
    m_zPos += force.m_Z;

    // is player walking or was previously walking before jumping?
    if (m_Walking)
        // rotate the player
        if (m_WalkOffset < 0.0f)
            pModelItem->SetY(-(float)(M_PI / 2.0) - (float)(M_PI / 2.0));
        else
        if (m_WalkOffset > 0.0f)
            pModelItem->SetY((float)(M_PI / 2.0) - (float)(M_PI / 2.0));

    switch (m_CameraType)
    {
        case IECameraType::IE_CT_Static:
            // set the x position
            m_xPos = 0.5f;

            // set the camera rotation
            pArcballItem->SetY((float)(M_PI / 2.0));
            break;

        case IECameraType::IE_CT_Rotate:
            // set the x position
            m_xPos = 0.5f;

            // apply a rotation on the camera
            pArcballItem->SetY(((float)M_PI / 2.0f) - (((m_zPos + 4.0f) / 100.0f) * (float)M_PI * 2.0f) / 1.0f);
            break;

        case IECameraType::IE_CT_Follow:
            // set the x position
            m_xPos = -0.25f;

            // place the camera below the player
            pArcballItem->SetY((float)M_PI);
            break;
    }

    // calculate the next player position (arcball, model and collider)
    pArcballItem->SetPos  (DWF_Math::Vector3F( m_xPos, -m_yPos - 0.5f,  2.0f + m_zPos));
    pModelItem->SetPos    (DWF_Math::Vector3F(-m_xPos,  m_yPos,        -2.0f - m_zPos));
    pModelCollider->SetPos(DWF_Math::Vector3F(-m_xPos,  m_yPos,        -2.0f - m_zPos));

    // player is falling too low?
    if (m_yPos < -3.0f)
    {
        // reset the pos to start
        m_xPos = 0.5f;
        m_yPos = 0.5f;
        m_zPos = 0.0f;
    }

    // reset the grounded state, in order to test it on the next collision detection
    m_Grounded = false;
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
    DWF_Scene::SceneItem_AnimAsset* pPlayer = static_cast<DWF_Scene::SceneItem_AnimAsset*>(pScene->SearchItem(L"scene_player_model"));

    if (!pPlayer)
        return;

    // apply modifications to player (to avoid a parasite thrill effect)
    pPOV->SetPos      (DWF_Math::Vector3F( m_xPos, -m_yPos - 0.5f,  2.0f + m_zPos));
    pPlayer->SetPos   (DWF_Math::Vector3F(-m_xPos,  m_yPos,        -2.0f - m_zPos));
    pItem1->SetPos    (DWF_Math::Vector3F(-m_xPos,  m_yPos,        -2.0f - m_zPos));
    pCollider1->SetPos(DWF_Math::Vector3F(-m_xPos,  m_yPos,        -2.0f - m_zPos));
}
//---------------------------------------------------------------------------
GLuint Main::LoadCubemap(const IFilenames fileNames, bool convertPixels)
{
    try
    {
        GLuint textureID = -1;

        // create new OpenGL texture
        glGenTextures(1, &textureID);
        glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

        const std::size_t fileNameCount = fileNames.size();

        // iterate through the cubemap texture files to load
        for (std::size_t i = 0; i < fileNameCount; ++i)
        {
            std::unique_ptr<DWF_Buffer::PixelBuffer> pPixelBuffer = std::make_unique<DWF_Buffer::PixelBuffer>();

            // load the texture
            if (!pPixelBuffer->FromPng(fileNames[i], false))
                return -1;

            GLint pixelType;

            // select the correct pixel type to use
            switch (pPixelBuffer->m_BytePerPixel)
            {
                case 24:  pixelType = GL_RGB;  break;
                case 32:  pixelType = GL_RGBA; break;
                default: return -1;
            }

            // do convert pixels?
            if (convertPixels)
            {
                // calculate image stride
                const std::size_t stride = ((((std::size_t)pPixelBuffer->m_Width) * 3 + 3) / 4) * 4 - (((std::size_t)pPixelBuffer->m_Width) * 3 % 4);

                // reorder the pixels
                unsigned char* pPixels = new unsigned char[(std::size_t)pPixelBuffer->m_Width * (std::size_t)pPixelBuffer->m_Height * 3];

                try
                {
                    // get bitmap data into right format
                    for (unsigned y = 0; y < pPixelBuffer->m_Height; ++y)
                        for (unsigned x = 0; x < pPixelBuffer->m_Width; ++x)
                            for (unsigned char c = 0; c < 3; ++c)
                                pPixels[3 * (pPixelBuffer->m_Width * y + x) + c] =
                                        ((unsigned char*)pPixelBuffer->m_pData)[stride * y + 3 * ((std::size_t)pPixelBuffer->m_Width - x - 1) + (2 - c)];

                    // load the texture on the GPU
                    glTexImage2D((GLenum)(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i),
                                 0,
                                 pixelType,
                                 (GLsizei)pPixelBuffer->m_Width,
                                 (GLsizei)pPixelBuffer->m_Height,
                                 0,
                                 pixelType,
                                 GL_UNSIGNED_BYTE,
                                 pPixels);
                }
                catch (...)
                {
                    delete[] pPixels;
                    throw;
                }

                delete[] pPixels;
            }
            else
                // load the texture on the GPU
                glTexImage2D((GLenum)(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i),
                             0,
                             pixelType,
                             (GLsizei)pPixelBuffer->m_Width,
                             (GLsizei)pPixelBuffer->m_Height,
                             0,
                             pixelType,
                             GL_UNSIGNED_BYTE,
                             (unsigned char*)pPixelBuffer->m_pData);
        }

        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S,     GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T,     GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R,     GL_CLAMP_TO_EDGE);

        return textureID;
    }
    catch (...)
    {
        return -1;
    }
}
//------------------------------------------------------------------------------
bool Main::LoadScene(const std::shared_ptr<DWF_Renderer::Shader>& pTexShader,
                     const std::shared_ptr<DWF_Renderer::Shader>& pColShader,
                     const std::shared_ptr<DWF_Renderer::Shader>& pCubemapShader,
                     const RECT&                                  clientRect)
{
    // configure the background color
    DWF_Model::ColorF bgColor;
    bgColor.m_R = 0.08f;
    bgColor.m_G = 0.12f;
    bgColor.m_B = 0.17f;
    bgColor.m_A = 1.0f;

    m_Scene.SetRenderer(m_Renderer);
    m_Scene.SetColor(bgColor);

    IFilenames cubemapFilenames;
    cubemapFilenames.push_back("..\\..\\Resources\\Skybox\\Exterior\\Day\\Mountains\\right.png");
    cubemapFilenames.push_back("..\\..\\Resources\\Skybox\\Exterior\\Day\\Mountains\\left.png");
    cubemapFilenames.push_back("..\\..\\Resources\\Skybox\\Exterior\\Day\\Mountains\\top.png");
    cubemapFilenames.push_back("..\\..\\Resources\\Skybox\\Exterior\\Day\\Mountains\\bottom.png");
    cubemapFilenames.push_back("..\\..\\Resources\\Skybox\\Exterior\\Day\\Mountains\\front.png");
    cubemapFilenames.push_back("..\\..\\Resources\\Skybox\\Exterior\\Day\\Mountains\\back.png");

    // load the skybox textures
    std::unique_ptr<DWF_Model::Texture_OpenGL> pTexture = std::make_unique<DWF_Model::Texture_OpenGL>();
    pTexture->m_Target = DWF_Model::Texture::IETarget::IE_TT_Cubemap;
    m_SkyboxTexId = LoadCubemap(cubemapFilenames, false);
    pTexture->SetID(m_SkyboxTexId);

    // set the skybox in scene
    m_Scene.SetSkybox(pTexture.get(), pCubemapShader);
    pTexture.release();

    // create the player arcball
    std::unique_ptr<DWF_Scene::Arcball> pArcball = std::make_unique<DWF_Scene::Arcball>();
    pArcball->m_AngleX = 0.25f;
    pArcball->m_AngleY = (float)(M_PI / 2.0);
    pArcball->m_Radius = 4.0f;

    // create an arcball point of view
    std::unique_ptr<DWF_Scene::SceneItem_PointOfView> pPOV = std::make_unique<DWF_Scene::SceneItem_PointOfView>(L"scene_arcball");
    pPOV->Set(pArcball.get());
    pArcball.release();

    // set the point of view to the scene
    m_Scene.Add(pPOV.get());
    pPOV.release();

    // load player IQM model
    std::shared_ptr<DWF_Model::IQM> pIqm = std::make_shared<DWF_Model::IQM>();
    pIqm->Set_OnLoadTexture(std::bind(&Main::OnLoadCharTexture, this, std::placeholders::_1, std::placeholders::_2));
    pIqm->Open("..\\..\\Resources\\Model\\Platformer\\Player\\player.iqm");

    // create the background model item
    std::unique_ptr<DWF_Scene::SceneItem_AnimAsset> pAnim = std::make_unique<DWF_Scene::SceneItem_AnimAsset>(L"scene_player_model");
    pAnim->SetStatic(true);
    pAnim->SetShader(pTexShader);
    pAnim->SetPos(DWF_Math::Vector3F(m_xPos, m_yPos, m_zPos));
    pAnim->SetRoll(-(float)M_PI / 2.0f);
    pAnim->SetPitch(0.0f);
    pAnim->SetYaw(0.0f);
    pAnim->SetScale(DWF_Math::Vector3F(0.05f, 0.05f, 0.05f));
    pAnim->SetModel(pIqm);
    pAnim->AddAnim((std::size_t)0, 0,   60, 0.025, true);  // idle
    pAnim->AddAnim((std::size_t)0, 60,  70, 0.025, false); // idle jump
    pAnim->AddAnim((std::size_t)0, 130, 19, 0.025, true);  // run
    pAnim->AddAnim((std::size_t)0, 149, 26, 0.025, false); // run jump
    pAnim->Set_OnFrame(std::bind(&Main::OnFrame, this, std::placeholders::_1, std::placeholders::_2));
    pAnim->Set_OnEndReached(std::bind(&Main::OnEndReached, this, std::placeholders::_1, std::placeholders::_2));

    pAnim->SelectAnim(0);

    // set the model to the scene
    m_Scene.Add(pAnim.get(), false);
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
    std::shared_ptr<DWF_Model::Model> pPlayerCapsule(DWF_Model::Factory::GetCapsule(0.85f, 0.17f, 16.0f, vf, vc, mat));

    // create the capsule model item
    std::unique_ptr<DWF_Scene::SceneItem_Model> pModel = std::make_unique<DWF_Scene::SceneItem_Model>(L"scene_player_collider");
    pModel->SetStatic(false);
    pModel->SetVisible(false);
    pModel->SetModel(pPlayerCapsule);
    pModel->SetShader(pColShader);
    pModel->SetPos(DWF_Math::Vector3F(m_xPos, m_yPos, m_zPos));
    pModel->SetRoll(0.0f);
    pModel->SetPitch(0.0f);
    pModel->SetYaw(0.0f);
    pModel->SetScale(DWF_Math::Vector3F(1.0f, 1.0f, 1.0f));

    // create the player collider
    std::unique_ptr<DWF_Collider::Capsule_Collider> pPlayerCollider = std::make_unique<DWF_Collider::Capsule_Collider>();
    pPlayerCollider->SetCapsule(0.17f, 0.85f, 0.0f, true);
    pModel->AddCollider(pPlayerCollider.get());
    pPlayerCollider.release();

    // set the model to the scene
    m_Scene.Add(pModel.get(), false);
    pModel.release();

    // load first platform
    std::shared_ptr<DWF_Model::Wavefront> pPlatform = std::make_shared<DWF_Model::Wavefront>();
    pPlatform->Set_OnOpenMaterialFile(std::bind(&Main::OnOpenMaterialFile, this, std::placeholders::_1, std::placeholders::_2));
    pPlatform->Set_OnLoadTexture(std::bind(&Main::OnLoadPlatformTexture, this, std::placeholders::_1, std::placeholders::_2));
    pPlatform->Open("..\\..\\Resources\\Model\\Platformer\\Platform\\Platform.obj");

    // create the first platform model item
    std::unique_ptr<DWF_Scene::SceneItem_StaticAsset> pStaticModel = std::make_unique<DWF_Scene::SceneItem_StaticAsset>(L"scene_player_collider");
    pStaticModel = std::make_unique<DWF_Scene::SceneItem_StaticAsset>(L"scene_platform");
    pStaticModel->SetStatic(true);
    pStaticModel->SetModel(pPlatform);
    pStaticModel->SetShader(pTexShader);
    pStaticModel->SetPos(DWF_Math::Vector3F(0.25f, -0.25f, -2.0f));
    pStaticModel->SetRoll(0.0f);
    pStaticModel->SetPitch(0.0f);
    pStaticModel->SetYaw(0.0f);
    pStaticModel->SetScale(DWF_Math::Vector3F(0.8f, 0.8f, 0.8f));

    // set the model to the scene
    m_Scene.Add(pStaticModel.get(), false);
    pStaticModel.release();

    // set material
    mat.m_Color.m_B = 0.0f;
    mat.m_Color.m_G = 0.0f;
    mat.m_Color.m_R = 1.0f;
    mat.m_Color.m_A = 1.0f;

    // create the matching collision box model
    std::shared_ptr<DWF_Model::Model> pBox(DWF_Model::Factory::GetBox(1.61f, 0.5f, 3.05f, false, vf, vc, mat));

    // create the box model item
    pModel = std::make_unique<DWF_Scene::SceneItem_Model>(L"scene_platform_collider");
    pModel->SetStatic(true);
    pModel->SetVisible(false);
    pModel->SetModel(pBox);
    pModel->SetShader(pColShader);
    pModel->SetPos(DWF_Math::Vector3F(0.25f, -0.25f, -2.0f));
    pModel->SetRoll(0.0f);
    pModel->SetPitch(0.0f);
    pModel->SetYaw(0.0f);
    pModel->SetScale(DWF_Math::Vector3F(1.0f, 1.0f, 1.0f));

    // box collider
    std::unique_ptr<DWF_Collider::Box_Collider> pBoxCol =
            std::make_unique<DWF_Collider::Box_Collider>(DWF_Math::Vector3F(),
                                                         DWF_Math::Matrix4x4F::Identity(),
                                                         DWF_Math::Vector3F(-0.805f, -0.25f, -1.525f),
                                                         DWF_Math::Vector3F( 0.805f,  0.25f,  1.525f));
    pModel->AddCollider(pBoxCol.get());
    pBoxCol.release();

    // set the model to the scene
    m_Scene.Add(pModel.get(), false);
    pModel.release();

    // create the second platform model item
    pStaticModel = std::make_unique<DWF_Scene::SceneItem_StaticAsset>(L"scene_platform_2");
    pStaticModel->SetStatic(true);
    pStaticModel->SetModel(pPlatform);
    pStaticModel->SetShader(pTexShader);
    pStaticModel->SetPos(DWF_Math::Vector3F(0.25f, 0.0f, 2.0f));
    pStaticModel->SetRoll(0.0f);
    pStaticModel->SetPitch(0.0f);
    pStaticModel->SetYaw(0.0f);
    pStaticModel->SetScale(DWF_Math::Vector3F(0.8f, 0.8f, 0.8f));

    // set the model to the scene
    m_Scene.Add(pStaticModel.get(), false);
    pStaticModel.release();

    // create the box model item
    pModel = std::make_unique<DWF_Scene::SceneItem_Model>(L"scene_platform_collider_2");
    pModel->SetStatic(true);
    pModel->SetVisible(false);
    pModel->SetModel(pBox);
    pModel->SetShader(pColShader);
    pModel->SetPos(DWF_Math::Vector3F(0.25, 0.0f, 2.0f));
    pModel->SetRoll(0.0f);
    pModel->SetPitch(0.0f);
    pModel->SetYaw(0.0f);
    pModel->SetScale(DWF_Math::Vector3F(1.0f, 1.0f, 1.0f));

    // box collider
    pBoxCol.reset(new DWF_Collider::Box_Collider(DWF_Math::Vector3F(),
                                                 DWF_Math::Matrix4x4F::Identity(),
                                                 DWF_Math::Vector3F(-0.805f, -0.25f, -1.525f),
                                                 DWF_Math::Vector3F( 0.805f,  0.25f,  1.525f)));
    pModel->AddCollider(pBoxCol.get());
    pBoxCol.release();

    // set the model to the scene
    m_Scene.Add(pModel.get(), false);
    pModel.release();

    // create the third platform model item
    pStaticModel = std::make_unique<DWF_Scene::SceneItem_StaticAsset>(L"scene_platform_3");
    pStaticModel->SetStatic(true);
    pStaticModel->SetModel(pPlatform);
    pStaticModel->SetShader(pTexShader);
    pStaticModel->SetPos(DWF_Math::Vector3F(0.25f, 0.25f, 6.0f));
    pStaticModel->SetRoll(0.0f);
    pStaticModel->SetPitch(0.0f);
    pStaticModel->SetYaw(0.0f);
    pStaticModel->SetScale(DWF_Math::Vector3F(0.8f, 0.8f, 0.8f));

    // set the model to the scene
    m_Scene.Add(pStaticModel.get(), false);
    pStaticModel.release();

    // create the box model item
    pModel = std::make_unique<DWF_Scene::SceneItem_Model>(L"scene_platform_collider_3");
    pModel->SetStatic(true);
    pModel->SetVisible(false);
    pModel->SetModel(pBox);
    pModel->SetShader(pColShader);
    pModel->SetPos(DWF_Math::Vector3F(0.25f, 0.25f, 6.0f));
    pModel->SetRoll(0.0f);
    pModel->SetPitch(0.0f);
    pModel->SetYaw(0.0f);
    pModel->SetScale(DWF_Math::Vector3F(1.0f, 1.0f, 1.0f));

    // box collider
    pBoxCol.reset(new DWF_Collider::Box_Collider(DWF_Math::Vector3F(),
                                                 DWF_Math::Matrix4x4F::Identity(),
                                                 DWF_Math::Vector3F(-0.805f, -0.25f, -1.525f),
                                                 DWF_Math::Vector3F( 0.805f,  0.25f,  1.525f)));
    pModel->AddCollider(pBoxCol.get());
    pBoxCol.release();

    // set the model to the scene
    m_Scene.Add(pModel.get(), false);
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

    // load footsteps sound
    std::unique_ptr<DWF_Audio::Sound_OpenAL> pSound = std::make_unique<DWF_Audio::Sound_OpenAL>();
    pSound->OpenWav(L"..\\..\\Resources\\Sound\\footsteps_run_grass.wav");
    pSound->Loop(false);

    // create a sound item
    std::unique_ptr<DWF_Scene::SceneAudioItem> pSoundItem = std::make_unique<DWF_Scene::SceneAudioItem>(L"sound_footsteps");
    pSoundItem->SetSound(pSound.get());
    pSound.release();

    // add sound to scene
    m_Scene.Add(pSoundItem.get());
    pSoundItem.release();

    return true;
}
//---------------------------------------------------------------------------
