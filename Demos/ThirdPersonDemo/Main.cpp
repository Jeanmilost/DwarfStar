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
                        Main::GetInstance()->SetShowPlayerCap(!Main::GetInstance()->GetShowPlayerCap());

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
    wcex.lpszClassName = L"ThirdPersonDemo";

    if (!RegisterClassEx(&wcex))
        return 0;

    // create main window
    HWND hWnd = ::CreateWindowEx(0,
                                 L"ThirdPersonDemo",
                                 L"DwarfStar Third-Person Demo",
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
    DWF_Renderer::Shader_OpenGL texShader;
    texShader.CreateProgram();
    texShader.Attach(DWF_Renderer::Shader_Collection_OpenGL::GetVertexShader(DWF_Renderer::Shader_Collection_OpenGL::IEShaderType::IE_ST_Texture),
            DWF_Renderer::Shader::IEType::IE_ST_Vertex);
    texShader.Attach(DWF_Renderer::Shader_Collection_OpenGL::GetFragmentShader(DWF_Renderer::Shader_Collection_OpenGL::IEShaderType::IE_ST_Texture),
            DWF_Renderer::Shader::IEType::IE_ST_Fragment);
    texShader.Link(true);

    // load color shader
    DWF_Renderer::Shader_OpenGL colShader;
    colShader.CreateProgram();
    colShader.Attach(DWF_Renderer::Shader_Collection_OpenGL::GetVertexShader(DWF_Renderer::Shader_Collection_OpenGL::IEShaderType::IE_ST_Color),
            DWF_Renderer::Shader::IEType::IE_ST_Vertex);
    colShader.Attach(DWF_Renderer::Shader_Collection_OpenGL::GetFragmentShader(DWF_Renderer::Shader_Collection_OpenGL::IEShaderType::IE_ST_Color),
            DWF_Renderer::Shader::IEType::IE_ST_Fragment);
    colShader.Link(true);

    // load skybox shader
    DWF_Renderer::Shader_OpenGL skyboxShader;
    skyboxShader.CreateProgram();
    skyboxShader.Attach(DWF_Renderer::Shader_Collection_OpenGL::GetVertexShader(DWF_Renderer::Shader_Collection_OpenGL::IEShaderType::IE_ST_Skybox),
            DWF_Renderer::Shader::IEType::IE_ST_Vertex);
    skyboxShader.Attach(DWF_Renderer::Shader_Collection_OpenGL::GetFragmentShader(DWF_Renderer::Shader_Collection_OpenGL::IEShaderType::IE_ST_Skybox),
            DWF_Renderer::Shader::IEType::IE_ST_Fragment);
    skyboxShader.Link(true);

    DWF_Math::Matrix4x4F projMatrix;

    // create the viewport
    m_Renderer.CreateViewport(float(clientRect.right  - clientRect.left),
                              float(clientRect.bottom - clientRect.top),
                              0.1f,
                              100.0f,
                              &texShader,
                              projMatrix);

    // connect the projection matrix to the other shaders
    m_Renderer.ConnectProjectionMatrixToShader(&colShader, projMatrix);
    m_Renderer.ConnectProjectionMatrixToShader(&skyboxShader, projMatrix);

    // create and configure the scene
    LoadScene(texShader, colShader, skyboxShader, clientRect);

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

            // do show or hide the player collider?
            if (m_ShowPlayerCap != m_OldShowPlayerCap)
            {
                DWF_Scene::SceneItem_Model* pModelCollider = static_cast<DWF_Scene::SceneItem_Model*>(m_Scene.SearchItem(L"scene_player_collider"));

                if (pModelCollider)
                    pModelCollider->SetVisible(m_ShowPlayerCap);

                m_OldShowPlayerCap = m_ShowPlayerCap;
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
DWF_Model::Texture* Main::OnLoadTexture(const std::string& textureName, bool is32bit)
{
    // search for an existing texture
    Textures::iterator it = m_TextureItems.find(textureName);

    // is texture already loaded?
    if (it == m_TextureItems.end())
    {
        std::unique_ptr<DWF_Buffer::PixelBuffer> pPixelBuffer = std::make_unique<DWF_Buffer::PixelBuffer>();

        // load the texture
        if (!pPixelBuffer->FromTga("..\\..\\Resources\\Model\\Deborah\\Textures\\" + textureName))
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
void Main::OnFrame(const DWF_Scene::SceneItem_AnimAsset* pAnim, const DWF_Scene::SceneItem_AnimAsset::IAnimDesc* pAnimDesc)
{
    if (!m_Jumping)
        return;

    if (!pAnimDesc)
        return;

    m_yPos = std::sinf((pAnimDesc->m_FrameIndex * (float)M_PI) / 23.0f) * 0.5f;
}
//---------------------------------------------------------------------------
void Main::OnEndReached(const DWF_Scene::SceneItem_AnimAsset* pAnim, const DWF_Scene::SceneItem_AnimAsset::IAnimDesc* pAnimDesc)
{
    m_Jumping = false;
    m_yPos    = 0.0f;

    if (!pAnim)
        return;

    // gain write access to animation item
    DWF_Scene::SceneItem_AnimAsset* pAnimItem = const_cast<DWF_Scene::SceneItem_AnimAsset*>(pAnim);

    // reset the jump animation
    pAnimItem->ResetAnim(2);
}
//------------------------------------------------------------------------------
void Main::OnSceneUpdate(const DWF_Scene::Scene* pScene, double elapsedTime)
{
    if (!pScene)
        return;

    // get the objects of interest from scene
    DWF_Scene::SceneItem_PointOfView* pArcballItem   = static_cast<DWF_Scene::SceneItem_PointOfView*>(pScene->SearchItem(L"scene_arcball"));
    DWF_Scene::SceneItem_AnimAsset*   pModelItem     = static_cast<DWF_Scene::SceneItem_AnimAsset*>  (pScene->SearchItem(L"scene_player_model"));
    DWF_Scene::SceneItem_Model*       pModelCollider = static_cast<DWF_Scene::SceneItem_Model*>      (pScene->SearchItem(L"scene_player_collider"));
    DWF_Scene::SceneAudioItem*        pSoundItem     = pScene->SearchAudio(L"sound_footsteps");

    if (!pArcballItem || !pModelItem || !pModelCollider || !pSoundItem)
        return;

    POINT p;

    // get current mouse position
    ::GetCursorPos(&p);

    // calculate delta on x and y axis
    m_xDelta = m_LastMouseXPos - p.x;
    m_yDelta = m_LastMouseYPos - p.y;

    // update the last known position
    m_LastMouseXPos = p.x;
    m_LastMouseYPos = p.y;

    // calculate the new direction from last mouse move
    pArcballItem->SetY(pArcballItem->GetY() - std::fmodf((float)m_xDelta * 0.01f, (float)M_PI * 2.0f));

    // reset the deltas (otherwise the player will turn forever)
    m_xDelta = 0;
    m_yDelta = 0;

    // get the pressed key, if any, and convert it to the matching player state
    if (::GetKeyState(VK_SPACE) & 0x8000)
    {
        if (pModelItem->GetSelectedAnim() != 2)
            pModelItem->SelectAnim(2);

        m_Jumping = true;

        pSoundItem->GetSound()->Stop();
    }
    else
    if (!m_Jumping)
        if ((::GetKeyState(VK_UP) & 0x8000) || (::GetKeyState(87) & 0x8000) || (::GetKeyState(119) & 0x8000))
        {
            if (pModelItem->GetSelectedAnim() != 1)
                pModelItem->SelectAnim(1);

            if (!pSoundItem->GetSound()->IsPlaying())
                pSoundItem->GetSound()->Play();

            m_Walking = true;
        }
        else
        {
            if (pModelItem->GetSelectedAnim() != 0)
                pModelItem->SelectAnim(0);

            pSoundItem->GetSound()->Stop();

            m_Walking = false;
        }

    // is player walking or was previously walking before jumping?
    if (m_Walking)
    {
        // move player forward
        m_xPos += m_Velocity * std::cosf(pArcballItem->GetY() + (float)(M_PI * 0.5)) * (float)(elapsedTime * 0.025);
        m_zPos += m_Velocity * std::sinf(pArcballItem->GetY() + (float)(M_PI * 0.5)) * (float)(elapsedTime * 0.025);
    }

    // calculate the next arcball position
    pArcballItem->SetPos  (DWF_Math::Vector3F(m_xPos, -0.5f, 2.0f + m_zPos));
    pModelItem->SetPos    (DWF_Math::Vector3F(-m_xPos, 0.0f, -2.0f - m_zPos));
    pModelItem->SetY      (-pArcballItem->GetY() + (float)M_PI);
    pModelCollider->SetPos(DWF_Math::Vector3F(-m_xPos, m_yPos, -2.0f - m_zPos));
}
//------------------------------------------------------------------------------
void Main::OnCollision(const DWF_Scene::Scene*       pScene,
                             DWF_Scene::SceneItem*   pItem1,
                             DWF_Collider::Collider* pCollider1,
                             DWF_Scene::SceneItem*   pItem2,
                             DWF_Collider::Collider* pCollider2,
                       const DWF_Math::Vector3F&     mtv)
{
    if (!pItem1)
        return;

    // get the point of view from the scene
    DWF_Scene::SceneItem_PointOfView* pPOV = static_cast<DWF_Scene::SceneItem_PointOfView*>(pScene->SearchItem(L"scene_arcball"));

    if (!pPOV)
        return;

    // use the minimum translation vector to correct the position
    pPOV->SetPos(pPOV->GetPos() - DWF_Math::Vector3F(mtv.m_X, 0.0f, mtv.m_Z));

    // also correct the collider position
    pItem1->SetPos(pItem1->GetPos() + DWF_Math::Vector3F(mtv.m_X, 0.0f, mtv.m_Z));

    // and finally, correct the cached position
    m_xPos -= mtv.m_X;
    m_zPos -= mtv.m_Z;
}
//---------------------------------------------------------------------------
GLuint Main::LoadCubemap(const IFilenames fileNames)
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
            if (!pPixelBuffer->FromBitmap(fileNames[i]))
                return -1;

            GLint pixelType;

            // select the correct pixel type to use
            switch (pPixelBuffer->m_BytePerPixel)
            {
                case 3:  pixelType = GL_RGB;  break;
                case 4:  pixelType = GL_RGBA; break;
                default: return -1;
            }

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

        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
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
bool Main::LoadScene(DWF_Renderer::Shader_OpenGL& texShader,
                     DWF_Renderer::Shader_OpenGL& colShader,
                     DWF_Renderer::Shader_OpenGL& cubemapShader,
               const RECT&                        clientRect)
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
    cubemapFilenames.push_back("..\\..\\Resources\\Skybox\\Exterior\\Day\\Storm\\right.bmp");
    cubemapFilenames.push_back("..\\..\\Resources\\Skybox\\Exterior\\Day\\Storm\\left.bmp");
    cubemapFilenames.push_back("..\\..\\Resources\\Skybox\\Exterior\\Day\\Storm\\top.bmp");
    cubemapFilenames.push_back("..\\..\\Resources\\Skybox\\Exterior\\Day\\Storm\\bottom.bmp");
    cubemapFilenames.push_back("..\\..\\Resources\\Skybox\\Exterior\\Day\\Storm\\front.bmp");
    cubemapFilenames.push_back("..\\..\\Resources\\Skybox\\Exterior\\Day\\Storm\\back.bmp");

    // load the skybox textures
    std::unique_ptr<DWF_Model::Texture_OpenGL> pTexture = std::make_unique<DWF_Model::Texture_OpenGL>();
    pTexture->m_Target = DWF_Model::Texture::IETarget::IE_TT_Cubemap;
    m_SkyboxTexId = LoadCubemap(cubemapFilenames);
    pTexture->SetID(m_SkyboxTexId);

    // set the skybox in scene
    m_Scene.SetSkybox(pTexture.get() , &cubemapShader);
    pTexture.release();

    // create the player arcball
    std::unique_ptr<DWF_Scene::Arcball> pArcball = std::make_unique<DWF_Scene::Arcball>();
    pArcball->m_AngleX = 0.25f;
    pArcball->m_Radius = 2.0f;

    // create an arcball point of view
    std::unique_ptr<DWF_Scene::SceneItem_PointOfView> pPOV = std::make_unique<DWF_Scene::SceneItem_PointOfView>(L"scene_arcball");
    pPOV->Set(pArcball.get());
    pArcball.release();

    // set the point of view to the scene
    m_Scene.Add(pPOV.get());
    pPOV.release();

    // load idle IQM
    std::shared_ptr<DWF_Model::IQM> pIqmIdle = std::make_shared<DWF_Model::IQM>();
    pIqmIdle->Set_OnLoadTexture(std::bind(&Main::OnLoadTexture, this, std::placeholders::_1, std::placeholders::_2));
    pIqmIdle->Open("..\\..\\Resources\\Model\\Deborah\\Idle\\Deborah_Idle.iqm");

    // load walking IQM
    std::shared_ptr<DWF_Model::IQM> pIqmWalk = std::make_shared<DWF_Model::IQM>();
    pIqmWalk->Set_OnLoadTexture(std::bind(&Main::OnLoadTexture, this, std::placeholders::_1, std::placeholders::_2));
    pIqmWalk->Open("..\\..\\Resources\\Model\\Deborah\\Walk\\Deborah_Walk.iqm");

    // load jumping IQM
    std::shared_ptr<DWF_Model::IQM> pIqmJump = std::make_shared<DWF_Model::IQM>();
    pIqmJump->Set_OnLoadTexture(std::bind(&Main::OnLoadTexture, this, std::placeholders::_1, std::placeholders::_2));
    pIqmJump->Open("..\\..\\Resources\\Model\\Deborah\\Jump\\Deborah_Jump.iqm");

    // create the background model item
    std::unique_ptr<DWF_Scene::SceneItem_AnimAsset> pAnim = std::make_unique<DWF_Scene::SceneItem_AnimAsset>(L"scene_player_model");
    pAnim->SetStatic(true);
    pAnim->SetShader(&texShader);
    pAnim->SetPos(DWF_Math::Vector3F(0.0f, 0.0f, -2.0f));
    pAnim->SetRoll(-(float)M_PI / 2.0f);
    pAnim->SetPitch(0.0f);
    pAnim->SetYaw(0.0f);
    pAnim->SetScale(DWF_Math::Vector3F(0.005f, 0.005f, 0.005f));
    pAnim->AddAnim(pIqmIdle, 0, 180, 0.025, true);
    pAnim->AddAnim(pIqmWalk, 0, 30, 0.025, true);
    pAnim->AddAnim(pIqmJump, 0, 24, 0.025, false);
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

    // set material
    mat.m_Color.m_B = 1.0f;
    mat.m_Color.m_G = 1.0f;
    mat.m_Color.m_R = 1.0f;
    mat.m_Color.m_A = 1.0f;

    // create the background surface
    std::shared_ptr<DWF_Model::Model> pBackground(DWF_Model::Factory::GetSurface(20.0f, 20.0f, vf, vc, mat));
    pBackground->m_Mesh[0]->m_VB[0]->m_Material.m_pTexture = OnLoadTexture("background.tga", false);

    // create the background model item
    std::unique_ptr<DWF_Scene::SceneItem_Model> pModel = std::make_unique<DWF_Scene::SceneItem_Model>(L"scene_bg");
    pModel->SetStatic(true);
    pModel->SetModel(pBackground);
    pModel->SetShader(&texShader);
    pModel->SetPos(DWF_Math::Vector3F(0.0f, 0.0f, -2.0f));
    pModel->SetRoll((float)M_PI / 2.0f);
    pModel->SetPitch(0.0f);
    pModel->SetYaw(0.0f);
    pModel->SetScale(DWF_Math::Vector3F(1.0f, 1.0f, 1.0f));

    // set the model to the scene
    m_Scene.Add(pModel.get(), false);
    pModel.release();

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
    pModel = std::make_unique<DWF_Scene::SceneItem_Model>(L"scene_player_collider");
    pModel->SetStatic(false);
    pModel->SetVisible(false);
    pModel->SetModel(pPlayerCapsule);
    pModel->SetShader(&colShader);
    pModel->SetPos(DWF_Math::Vector3F(5.0f, 0.0f, -2.0f));
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

    // set material
    mat.m_Color.m_B = 0.0f;
    mat.m_Color.m_G = 0.0f;
    mat.m_Color.m_R = 1.0f;
    mat.m_Color.m_A = 1.0f;

    // create the capsule
    std::shared_ptr<DWF_Model::Model> pCapsule(DWF_Model::Factory::GetCapsule(0.85f, 0.17f, 16.0f, vf, vc, mat));

    // create the capsule model item
    pModel = std::make_unique<DWF_Scene::SceneItem_Model>(L"scene_capsule");
    pModel->SetStatic(true);
    pModel->SetModel(pCapsule);
    pModel->SetShader(&colShader);
    pModel->SetPos(DWF_Math::Vector3F(5.0f, 0.0f, -2.0f));
    pModel->SetRoll(0.0f);
    pModel->SetPitch(0.0f);
    pModel->SetYaw(0.0f);
    pModel->SetScale(DWF_Math::Vector3F(1.0f, 1.0f, 1.0f));

    // capsule collider
    std::unique_ptr<DWF_Collider::Capsule_Collider> pCapsCol =
            std::make_unique<DWF_Collider::Capsule_Collider>(DWF_Math::Vector3F(),
                                                             DWF_Math::Matrix4x4F::Identity(),
                                                             0.17f,
                                                             0.85f,
                                                             0.0f,
                                                             true);
    pModel->AddCollider(pCapsCol.get());
    pCapsCol.release();

    // set the model to the scene
    m_Scene.Add(pModel.get(), false);
    pModel.release();

    // set front culling
    vc.m_Type = DWF_Model::VertexCulling::IECullingType::IE_CT_Front;

    // set material
    mat.m_Color.m_B = 0.0f;
    mat.m_Color.m_G = 1.0f;
    mat.m_Color.m_R = 0.0f;
    mat.m_Color.m_A = 1.0f;

    // create the box
    std::shared_ptr<DWF_Model::Model> pBox(DWF_Model::Factory::GetBox(0.8f, 3.4f, 2.6f, false, vf, vc, mat));

    // create the box model item
    pModel = std::make_unique<DWF_Scene::SceneItem_Model>(L"scene_box");
    pModel->SetStatic(true);
    pModel->SetModel(pBox);
    pModel->SetShader(&colShader);
    pModel->SetPos(DWF_Math::Vector3F(-5.0f, 0.0f, 3.5f));
    pModel->SetRoll(0.0f);
    pModel->SetPitch((float)M_PI * 0.25);
    pModel->SetYaw((float)M_PI * 0.15);
    pModel->SetScale(DWF_Math::Vector3F(1.0f, 1.0f, 1.0f));

    // box collider
    std::unique_ptr<DWF_Collider::Box_Collider> pBoxCol =
            std::make_unique<DWF_Collider::Box_Collider>(DWF_Math::Vector3F(),
                                                         DWF_Math::Matrix4x4F::Identity(),
                                                         DWF_Math::Vector3F(-0.4f, -1.7f, -1.3f),
                                                         DWF_Math::Vector3F(0.4f, 1.7f, 1.3f));
    pModel->AddCollider(pBoxCol.get());
    pBoxCol.release();

    // set the model to the scene
    m_Scene.Add(pModel.get(), false);
    pModel.release();

    // set material
    mat.m_Color.m_B = 0.0f;
    mat.m_Color.m_G = 1.0f;
    mat.m_Color.m_R = 1.0f;
    mat.m_Color.m_A = 1.0f;

    // create the sphere
    std::shared_ptr<DWF_Model::Model> pSphere(DWF_Model::Factory::GetSphere(1.2f, 20, 20, vf, vc, mat));

    // create the sphere model item
    pModel = std::make_unique<DWF_Scene::SceneItem_Model>(L"scene_sphere");
    pModel->SetStatic(true);
    pModel->SetModel(pSphere);
    pModel->SetShader(&colShader);
    pModel->SetPos(DWF_Math::Vector3F(-5.0f, 0.2f, -3.5f));
    pModel->SetRoll(0.0f);
    pModel->SetPitch(0.0f);
    pModel->SetYaw(0.0f);
    pModel->SetScale(DWF_Math::Vector3F(1.0f, 1.0f, 1.0f));

    // sphere collider
    std::unique_ptr<DWF_Collider::Sphere_Collider> pSphCol =
            std::make_unique<DWF_Collider::Sphere_Collider>(DWF_Math::Vector3F(),
                                                            DWF_Math::Matrix4x4F::Identity(),
                                                            1.2f);
    pModel->AddCollider(pSphCol.get());
    pSphCol.release();

    // set the model to the scene
    m_Scene.Add(pModel.get(), false);
    pModel.release();

    // set material
    mat.m_Color.m_B = 1.0f;
    mat.m_Color.m_G = 1.0f;
    mat.m_Color.m_R = 0.0f;
    mat.m_Color.m_A = 1.0f;

    // create the cylinder
    std::shared_ptr<DWF_Model::Model> pCylinder(DWF_Model::Factory::GetCylinder(2.1f, 2.1f, 1.5f, 20, vf, vc, mat));

    // create the cylinder model item
    pModel = std::make_unique<DWF_Scene::SceneItem_Model>(L"scene_cylinder");
    pModel->SetStatic(true);
    pModel->SetModel(pCylinder);
    pModel->SetShader(&colShader);
    pModel->SetPos(DWF_Math::Vector3F(5.0f, 0.2f, 4.1f));
    pModel->SetRoll(0.0f);
    pModel->SetPitch(0.0f);
    pModel->SetYaw(0.0f);
    pModel->SetScale(DWF_Math::Vector3F(1.0f, 1.0f, 1.0f));

    // cylinder collider
    std::unique_ptr<DWF_Collider::Cylinder_Collider> pCylCol =
            std::make_unique<DWF_Collider::Cylinder_Collider>(DWF_Math::Vector3F(),
                                                              DWF_Math::Matrix4x4F::Identity(),
                                                              2.1f,
                                                              1.5f,
                                                              0.0f);
    pModel->AddCollider(pCylCol.get());
    pCylCol.release();

    // set the model to the scene
    m_Scene.Add(pModel.get(), false);
    pModel.release();

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
    pSound->OpenWav(L"..\\..\\Resources\\Sound\\footsteps.wav");
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
