/****************************************************************************
 * ==> DirectionalLight ----------------------------------------------------*
 ****************************************************************************
 * Description: This project is a test of a directional light               *
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
#include "DWF_Vector3.h"
#include "DWF_Polygon.h"
#include "DWF_Capsule.h"
#include "DWF_ModelFactory.h"
#include "DWF_Texture_OpenGL.h"
#include "DWF_Shader_OpenGL.h"
#include "DWF_Renderer_OpenGL.h"

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
const DWF_Math::Vector3F    g_DefCapsule1Top   (  0.0f,  40.0f,    0.0f);
const DWF_Math::Vector3F    g_DefCapsule1Bottom(  0.0f,   0.0f,    0.0f);
const DWF_Math::Vector3F    g_DefCapsule2Top   (  0.0f,  40.0f,    0.0f);
const DWF_Math::Vector3F    g_DefCapsule2Bottom(  0.0f,   0.0f,    0.0f);
      DWF_Math::Vector3F    g_Capsule1Pos      (-25.0f, -10.0f, -100.0f);
      DWF_Math::Vector3F    g_Capsule2Pos      ( 25.0f, -10.0f, -100.0f);
      DWF_Math::Vector3F    g_LightDir;
      bool                  g_Rotate = false;
//------------------------------------------------------------------------------
const char dirLightVertShader[] = "precision mediump float;"
                                  "attribute    vec3 dwf_aVertices;"
                                  "attribute    vec3 dwf_aNormal;"
                                  "attribute    vec4 dwf_aColor;"
                                  "uniform      vec3 dwf_aDirLight;"
                                  "uniform      mat4 dwf_uProjection;"
                                  "uniform      mat4 dwf_uView;"
                                  "uniform      mat4 dwf_uModel;"
                                  "varying lowp vec4 dwf_vColor;"
                                  "void main(void)"
                                  "{"
                                  "    float intensity = dot(dwf_aDirLight, dwf_aNormal);"
                                  "    dwf_vColor      = dwf_aColor * intensity;"
                                  "    gl_Position     = dwf_uProjection * dwf_uView * dwf_uModel * vec4(dwf_aVertices, 1.0);"
                                  "}";
//------------------------------------------------------------------------------
const char dirLightFragShader[] = "precision mediump float;"
                                  "varying lowp vec4 dwf_vColor;"
                                  "void main(void)"
                                  "{"
                                  "    gl_FragColor = dwf_vColor;"
                                  "}";
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
                case VK_SPACE:
                    g_Rotate = !g_Rotate;
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
int APIENTRY wWinMain(_In_     HINSTANCE hInstance,
                      _In_opt_ HINSTANCE hPrevInstance,
                      _In_     LPWSTR    lpCmdLine,
                      _In_     int       nCmdShow)
{
    WNDCLASSEX wcex = {};
    HWND       hWnd = 0;
    MSG        msg = {};
    BOOL       bQuit = FALSE;

    // register window class
    wcex.cbSize        = sizeof(WNDCLASSEX);
    wcex.style         = CS_OWNDC;
    wcex.lpfnWndProc   = WindowProc;
    wcex.cbClsExtra    = 0;
    wcex.cbWndExtra    = 0;
    wcex.hInstance     = hInstance;
    wcex.hIcon         = ::LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APPICON));
    wcex.hIconSm       = ::LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APPICON_SMALL));
    wcex.hCursor       = ::LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)::GetStockObject(BLACK_BRUSH);
    wcex.lpszMenuName  = nullptr;
    wcex.lpszClassName = L"dwarfstarDirLight";

    if (!RegisterClassEx(&wcex))
        return 0;

    // create main window
    hWnd = ::CreateWindowEx(0,
                            L"dwarfstarDirLight",
                            L"DwarfStar Directional Light",
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

    // compile the lighting shader
    DWF_Renderer::Shader_OpenGL dirLightShader;
    dirLightShader.CreateProgram();
    dirLightShader.Attach(dirLightVertShader, DWF_Renderer::Shader::IEType::IE_ST_Vertex);
    dirLightShader.Attach(dirLightFragShader, DWF_Renderer::Shader::IEType::IE_ST_Fragment);
    dirLightShader.Link(true);

    // configure the material for the first capsule
    DWF_Model::Material material;
    material.m_Color = DWF_Model::ColorF(1.0f, 0.1f, 0.05f, 1.0f);

    // configure the culling
    DWF_Model::VertexCulling culling;

    // configure the vertex format
    DWF_Model::VertexFormat format;
    format.m_Format = (DWF_Model::VertexFormat::IEFormat)((std::int32_t)DWF_Model::VertexFormat::IEFormat::IE_VF_Normals |
                                                          (std::int32_t)DWF_Model::VertexFormat::IEFormat::IE_VF_Colors);
    format.m_Type   =  DWF_Model::VertexFormat::IEType::IE_VT_Triangles;

    // create first capsule
    std::unique_ptr<DWF_Model::Model> pCapsuleModel1;
    pCapsuleModel1.reset(DWF_Model::Factory::GetCapsule(20.0f, 7.5f, 16.0f, format, culling, material));

    // configure the material for the second capsule
    material.m_Color = DWF_Model::ColorF(0.05f, 0.1f, 1.0f, 1.0f);

    // create second capsule
    std::unique_ptr<DWF_Model::Model> pCapsuleModel2;
    pCapsuleModel2.reset(DWF_Model::Factory::GetCapsule(20.0f, 7.5f, 16.0f, format, culling, material));

    DWF_Math::Matrix4x4F projMatrix;

    // create the viewport
    renderer.CreateViewport(float(clientRect.right  - clientRect.left),
                            float(clientRect.bottom - clientRect.top),
                            0.1f,
                            1000.0f,
                            &dirLightShader,
                            projMatrix);

    // connect the projection matrix to the shader
    renderer.ConnectProjectionMatrixToShader(&dirLightShader, projMatrix);

    // connect the view matrix to the both model and line shaders
    DWF_Math::Matrix4x4F viewMatrix = DWF_Math::Matrix4x4F::Identity();
    renderer.ConnectViewMatrixToShader(&dirLightShader, viewMatrix);

    // create a light direction from a polygon normal
    DWF_Geometry::Polygon polygon(DWF_Math::Vector3F(-1.0f, 0.0f, -0.2f),
                                  DWF_Math::Vector3F( 0.0f, 1.0f,  6.4f),
                                  DWF_Math::Vector3F( 1.0f, 0.0f, -3.7f));
    g_LightDir = polygon.GetNormal();

    dirLightShader.Use(true);

    // get the directional light slot
    const GLint lightDirSlot = renderer.GetUniform(&dirLightShader, DWF_Renderer::Shader::IEAttribute::IE_SA_DirLight);

    // found it?
    if (lightDirSlot != -1)
        // set the light direction
        glUniform3f(lightDirSlot, g_LightDir.m_X, g_LightDir.m_Y, g_LightDir.m_Z);

    dirLightShader.Use(false);

    DWF_Model::ColorF bgColor;
    bgColor.m_R = 0.08f;
    bgColor.m_G = 0.12f;
    bgColor.m_B = 0.17f;
    bgColor.m_A = 1.0f;

    float  angle    = 0.0f;
    double lastTime = 0.0f;

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

            // create the X rotation matrix
            DWF_Math::Matrix4x4F rotMatX;
            DWF_Math::Vector3F   axis;
            axis.m_X = 1.0f;
            axis.m_Y = 0.0f;
            axis.m_Z = 0.0f;
            rotMatX = matrix.Rotate(0.0f, axis);

            // create the Y rotation matrix
            DWF_Math::Matrix4x4F rotMatY;
            axis.m_X = 0.0f;
            axis.m_Y = 1.0f;
            axis.m_Z = 0.0f;
            rotMatY = matrix.Rotate(0.0f, axis);

            // create the Z rotation matrix
            DWF_Math::Matrix4x4F rotMatZ;
            axis.m_X = 0.0f;
            axis.m_Y = 0.0f;
            axis.m_Z = 1.0f;
            rotMatZ = matrix.Rotate(angle, axis);

            DWF_Math::Matrix4x4F rotMat;

            // combine the rotation matrices
                     rotMatY.Multiply(rotMatX);
            rotMat = rotMatZ.Multiply(rotMatY);

            // build first capsule matrix
            DWF_Math::Matrix4x4F modelMatrixC1 = rotMat;
            modelMatrixC1.m_Table[3][0]        = g_Capsule1Pos.m_X;
            modelMatrixC1.m_Table[3][1]        = g_Capsule1Pos.m_Y;
            modelMatrixC1.m_Table[3][2]        = g_Capsule1Pos.m_Z;

            // combine the invert rotation matrix
            matrix = DWF_Math::Matrix4x4F::Identity();
            rotMatZ = matrix.Rotate(-angle, axis);
            rotMat  = rotMatZ.Multiply(rotMatY);

            // build second capsule matrix
            DWF_Math::Matrix4x4F modelMatrixC2 = rotMat;
            modelMatrixC2.m_Table[3][0]        = g_Capsule2Pos.m_X;
            modelMatrixC2.m_Table[3][1]        = g_Capsule2Pos.m_Y;
            modelMatrixC2.m_Table[3][2]        = g_Capsule2Pos.m_Z;

            // calculate the elapsed time
            double elapsedTime = (double)::GetTickCount64() - lastTime;
            lastTime = (double)::GetTickCount64();

            // draw the scene
            renderer.BeginScene(bgColor, (DWF_Renderer::Renderer::IESceneFlags)((std::uint32_t)DWF_Renderer::Renderer::IESceneFlags::IE_SF_ClearColor |
                                                                                (std::uint32_t)DWF_Renderer::Renderer::IESceneFlags::IE_SF_ClearDepth));

            dirLightShader.Use(true);

            // update the light direction in relation to the capsule matrix
            if (lightDirSlot != -1)
            {
                float                    determinant;
                const DWF_Math::Vector3F lightDir = modelMatrixC1.Inverse(determinant).TransformNormal(g_LightDir);

                glUniform3f(lightDirSlot, lightDir.m_X, lightDir.m_Y, lightDir.m_Z);
            }

            dirLightShader.Use(false);

            // draw the first capsules
            renderer.Draw(*pCapsuleModel1->m_Mesh[0], modelMatrixC1, &dirLightShader, false);

            dirLightShader.Use(true);

            // update the light direction in relation to the capsule matrix
            if (lightDirSlot != -1)
            {
                float                    determinant;
                const DWF_Math::Vector3F lightDir = modelMatrixC2.Inverse(determinant).TransformNormal(g_LightDir);

                glUniform3f(lightDirSlot, lightDir.m_X, lightDir.m_Y, lightDir.m_Z);
            }

            dirLightShader.Use(false);

            // draw the second capsules
            renderer.Draw(*pCapsuleModel2->m_Mesh[0], modelMatrixC2, &dirLightShader, false);

            renderer.EndScene();

            // calculate the next angle
            if (g_Rotate)
                angle = std::fmodf(angle + ((float)elapsedTime * 0.001f), 2.0f * (float)M_PI);

            ::Sleep(1);
        }
    }

    // shutdown OpenGL
    renderer.DisableOpenGL(hWnd);

    // destroy the window explicitly
    ::DestroyWindow(hWnd);

    return (int)msg.wParam;
}
//------------------------------------------------------------------------------
