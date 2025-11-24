/****************************************************************************
 * ==> IQMModelTest --------------------------------------------------------*
 ****************************************************************************
 * Description: DwarfStar IQM model test project                            *
 * Developer:   Jean-Milost Reymond                                         *
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

// classes
#include "DWF_PixelBuffer.h"
#include "DWF_Model.h"
#include "DWF_IQM.h"
#include "DWF_Texture_OpenGL.h"
#include "DWF_Shader_OpenGL.h"
#include "DWF_Renderer_OpenGL.h"
#include "DWF_Shader_Collection_OpenGL.h"

// openGL
#define GLEW_STATIC
#include <GL/glew.h>
#include <gl/gl.h>

// libraries
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

// resources
#include "Resource.h"

//------------------------------------------------------------------------------
bool g_ShowSkeleton = false;
bool g_PauseAnim    = false;
bool g_Rotate       = true;
//------------------------------------------------------------------------------
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
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
                    g_ShowSkeleton = !g_ShowSkeleton;
                    break;

                case '2':
                    g_Rotate = !g_Rotate;
                    break;

                case VK_SPACE:
                    g_PauseAnim = !g_PauseAnim;
                    break;

                case VK_ESCAPE:
                    ::PostQuitMessage(0);
                    break;
            }

            break;

        default:
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }

    return 0;
}
//------------------------------------------------------------------------------
DWF_Model::Texture* OnLoadTexture(const std::string& textureName, bool is32bit)
{
    const std::size_t separator = textureName.rfind('/');
    const std::string fileName  = textureName.substr(separator + 1, textureName.length() - (separator + 1));

    std::unique_ptr<DWF_Buffer::PixelBuffer> pPixelBuffer = std::make_unique<DWF_Buffer::PixelBuffer>();

    // load the texture
    if (!pPixelBuffer->FromTga("..\\..\\Resources\\Model\\Deborah\\Textures\\" + textureName))
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
void DrawIQM(const DWF_Model::IQM&         iqmModel,
             const DWF_Math::Matrix4x4F&   modelMatrix,
             const DWF_Renderer::Shader*   pShader,
             const DWF_Renderer::Renderer* pRenderer,
                   int                     animSetIndex,
                   int                     frameCount,
                   int                     frameIndex)
{
    if (!pRenderer)
        return;

    if (!pShader)
        return;

    DWF_Model::Model* pModel = iqmModel.GetModel(animSetIndex, frameCount, frameIndex);

    // draw the model
    for (std::size_t i = 0; i < pModel->m_Mesh.size(); ++i)
        pRenderer->Draw(*pModel->m_Mesh[i], modelMatrix, pShader, false);
}
//---------------------------------------------------------------------------
void DrawBone(const DWF_Model::IQM&          iqmModel,
              const DWF_Model::Model*        pModel,
              const DWF_Model::Model::IBone* pBone,
              const DWF_Math::Matrix4x4F&    modelMatrix,
              const DWF_Renderer::Shader*    pShader,
              const DWF_Renderer::Renderer*  pRenderer,
                    int                      animSetIndex,
                    int                      frameCount,
                    int                      frameIndex)
{
    if (!pModel)
        return;

    if (!pBone)
        return;

    if (!pRenderer)
        return;

    if (!pShader)
        return;

    for (std::size_t i = 0; i < pBone->m_Children.size(); ++i)
    {
        DWF_Model::Model::IBone* pChild = pBone->m_Children[i];

        DWF_Math::Matrix4x4F topMatrix;

        if (pModel->m_PoseOnly)
            pModel->GetBoneMatrix(pBone, DWF_Math::Matrix4x4F::Identity(), topMatrix);
        else
            iqmModel.GetBoneAnimMatrix(pBone,
                                       pModel->m_AnimationSet[animSetIndex],
                                       frameIndex,
                                       DWF_Math::Matrix4x4F::Identity(),
                                       topMatrix);

        DWF_Math::Matrix4x4F bottomMatrix;

        if (pModel->m_PoseOnly)
            pModel->GetBoneMatrix(pChild, DWF_Math::Matrix4x4F::Identity(), bottomMatrix);
        else
            iqmModel.GetBoneAnimMatrix(pChild,
                                       pModel->m_AnimationSet[animSetIndex],
                                       frameIndex,
                                       DWF_Math::Matrix4x4F::Identity(),
                                       bottomMatrix);

        glDisable(GL_DEPTH_TEST);
        pRenderer->DrawLine(DWF_Math::Vector3F(topMatrix.m_Table[3][0],    topMatrix.m_Table[3][1],    topMatrix.m_Table[3][2]),
                            DWF_Math::Vector3F(bottomMatrix.m_Table[3][0], bottomMatrix.m_Table[3][1], bottomMatrix.m_Table[3][2]),
                            DWF_Model::ColorF(0.25f, 0.12f, 0.1f, 1.0f),
                            DWF_Model::ColorF(0.95f, 0.06f, 0.15f, 1.0f),
                            modelMatrix,
                            pShader);
        glEnable(GL_DEPTH_TEST);

        DrawBone(iqmModel, pModel, pChild, modelMatrix, pShader, pRenderer, animSetIndex, frameCount, frameIndex);
    }
}
//---------------------------------------------------------------------------
void DrawSkeleton(const DWF_Model::IQM&         iqmModel,
                  const DWF_Math::Matrix4x4F&   modelMatrix,
                  const DWF_Renderer::Shader*   pShader,
                  const DWF_Renderer::Renderer* pRenderer,
                        int                     animSetIndex,
                        int                     frameCount,
                        int                     frameIndex)
{
    if (!pRenderer)
        return;

    if (!pShader)
        return;

    DWF_Model::Model* pModel = iqmModel.GetModel(animSetIndex, frameCount, frameIndex);

    DrawBone(iqmModel, pModel, pModel->m_pSkeleton, modelMatrix, pShader, pRenderer, animSetIndex, frameCount, frameIndex);
}
//------------------------------------------------------------------------------
int APIENTRY wWinMain(_In_     HINSTANCE hInstance,
                      _In_opt_ HINSTANCE hPrevInstance,
                      _In_     LPWSTR    lpCmdLine,
                      _In_     int       nCmdShow)
{
    WNDCLASSEX wcex  = {};
    HWND       hWnd  = 0;
    MSG        msg   = {};
    BOOL       bQuit = FALSE;

    // register window class
    wcex.cbSize        = sizeof(WNDCLASSEX);
    wcex.style         = CS_OWNDC;
    wcex.lpfnWndProc   = WindowProc;
    wcex.cbClsExtra    = 0;
    wcex.cbWndExtra    = 0;
    wcex.hInstance     = hInstance;
    wcex.hIcon         = ::LoadIcon(hInstance, MAKEINTRESOURCE(IDI_IQMMODELTEST));
    wcex.hIconSm       = ::LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SMALL));
    wcex.hCursor       = ::LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)::GetStockObject(BLACK_BRUSH);
    wcex.lpszMenuName  = nullptr;
    wcex.lpszClassName = L"dwarfstarIQMModelTest";

    if (!RegisterClassEx(&wcex))
        return 0;

    // create main window
    hWnd = ::CreateWindowEx(0,
                            L"dwarfstarIQMModelTest",
                            L"DwarfStar IQM Model Test",
                            WS_DLGFRAME | WS_CAPTION | WS_SYSMENU,
                            CW_USEDEFAULT,
                            CW_USEDEFAULT,
                            800,
                            600,
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

    DWF_Renderer::Renderer_OpenGL renderer;

    // enable OpenGL for the window
    renderer.EnableOpenGL(hWnd);

    // stop GLEW crashing on OSX :-/
    glewExperimental = GL_TRUE;

    // initialize GLEW
    if (glewInit() != GLEW_OK)
    {
        // shutdown OpenGL
        renderer.DisableOpenGL(hWnd);

        // destroy the window explicitly
        ::DestroyWindow(hWnd);

        return 0;
    }

    DWF_Renderer::Shader_OpenGL shader;
    shader.CreateProgram();
    shader.Attach(DWF_Renderer::Shader_Collection_OpenGL::GetVertexShader(DWF_Renderer::Shader_Collection_OpenGL::IEShaderType::IE_ST_Texture),
            DWF_Renderer::Shader::IEType::IE_ST_Vertex);
    shader.Attach(DWF_Renderer::Shader_Collection_OpenGL::GetFragmentShader(DWF_Renderer::Shader_Collection_OpenGL::IEShaderType::IE_ST_Texture_Alpha_Cut),
            DWF_Renderer::Shader::IEType::IE_ST_Fragment);
    shader.Link(true);

    DWF_Renderer::Shader_OpenGL lineShader;
    lineShader.CreateProgram();
    lineShader.Attach(DWF_Renderer::Shader_Collection_OpenGL::GetVertexShader(DWF_Renderer::Shader_Collection_OpenGL::IEShaderType::IE_ST_Line),
            DWF_Renderer::Shader::IEType::IE_ST_Vertex);
    lineShader.Attach(DWF_Renderer::Shader_Collection_OpenGL::GetFragmentShader(DWF_Renderer::Shader_Collection_OpenGL::IEShaderType::IE_ST_Line),
            DWF_Renderer::Shader::IEType::IE_ST_Fragment);
    lineShader.Link(true);

    DWF_Model::IQM iqm;
    iqm.Set_OnLoadTexture(OnLoadTexture);
    //iqm.SetPoseOnly(true);
    iqm.Open("..\\..\\Resources\\Model\\Deborah\\Walk\\Deborah_Walk.iqm");

    DWF_Math::Matrix4x4F projMatrix;

    // create the viewport
    renderer.CreateViewport(float(clientRect.right  - clientRect.left),
                            float(clientRect.bottom - clientRect.top),
                            0.1f,
                            1000.0f,
                            &shader,
                            projMatrix);

    // connect the projection matrix to the line shader
    renderer.ConnectProjectionMatrixToShader(&lineShader, projMatrix);

    // connect the view matrix to the both model and line shaders
    DWF_Math::Matrix4x4F viewMatrix = DWF_Math::Matrix4x4F::Identity();
    renderer.ConnectViewMatrixToShader(&shader,     viewMatrix);
    renderer.ConnectViewMatrixToShader(&lineShader, viewMatrix);

    DWF_Model::ColorF bgColor;
    bgColor.m_R = 0.08f;
    bgColor.m_G = 0.12f;
    bgColor.m_B = 0.17f;
    bgColor.m_A = 1.0f;

    float  angle         = 0.0f;
    double lastTime      = (double)::GetTickCount64();
    double modelLastTime = 0.0;
    double fps           = 25.0f;
    int    frame         = 0;

    // program main loop
    while (!bQuit)
    {
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
            DWF_Math::Matrix4x4F matrix = DWF_Math::Matrix4x4F::Identity();
            DWF_Math::Vector3F   axis;

            // create the X rotation matrix
            DWF_Math::Matrix4x4F rotMatX;
            axis.m_X = 1.0f;
            axis.m_Y = 0.0f;
            axis.m_Z = 0.0f;
            rotMatX  = matrix.Rotate(-(float)(M_PI / 2.0), axis);

            // create the Z rotation matrix (will give a rotation on the Y axis, as the model was rotated on the X axis)
            DWF_Math::Matrix4x4F rotMatZ;
            axis.m_X = 0.0f;
            axis.m_Y = 0.0f;
            axis.m_Z = 1.0f;
            rotMatZ  = matrix.Rotate(angle, axis);

            // create the scale matrix
            DWF_Math::Matrix4x4F scaleMat = DWF_Math::Matrix4x4F::Identity();
            scaleMat.m_Table[0][0]        = 0.2f;
            scaleMat.m_Table[1][1]        = 0.2f;
            scaleMat.m_Table[2][2]        = 0.2f;

            // combine the rotation matrices
            rotMatZ.Multiply(rotMatX);

            // place the model in the 3d world (update the matrix directly)
            DWF_Math::Matrix4x4F modelMatrix =  rotMatZ.Multiply(scaleMat);
            modelMatrix.m_Table[3][1]        = -17.5f;
            modelMatrix.m_Table[3][2]        = -50.0f;

            // calculate the elapsed time
            double elapsedTime = (double)::GetTickCount64() - lastTime;
                   lastTime    = (double)::GetTickCount64();

            // apply the elapsed time
            modelLastTime += elapsedTime * 0.001;

            // calculate the frame interval
            const double interval = 1.0 / fps;

            // do get the next model?
            while (modelLastTime >= interval)
            {
                // decrease the counted time
                modelLastTime -= interval;

                // go to next frame
                frame = (frame + 1) % 30;
            }

            // draw the scene
            renderer.BeginScene(bgColor, (DWF_Renderer::Renderer::IESceneFlags)((std::uint32_t)DWF_Renderer::Renderer::IESceneFlags::IE_SF_ClearColor |
                                                                                (std::uint32_t)DWF_Renderer::Renderer::IESceneFlags::IE_SF_ClearDepth));

            // draw the model
            DrawIQM(iqm, modelMatrix, &shader, &renderer, 0, 30, g_PauseAnim ? 0 : frame);

            // draw the skeleton
            if (g_ShowSkeleton)
                DrawSkeleton(iqm, modelMatrix, &lineShader, &renderer, 0, 30, g_PauseAnim ? 0 : frame);

            renderer.EndScene();

            // calculate the next angle
            if (g_Rotate)
                angle = std::fmodf(angle + ((float)elapsedTime * 0.001f), 2.0f * (float)M_PI);

            Sleep(1);
        }
    }

    // shutdown OpenGL
    renderer.DisableOpenGL(hWnd);

    // destroy the window explicitly
    ::DestroyWindow(hWnd);

    return (int)msg.wParam;
}
//------------------------------------------------------------------------------
