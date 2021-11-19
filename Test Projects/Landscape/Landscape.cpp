/****************************************************************************
 * ==> Landscape -----------------------------------------------------------*
 ****************************************************************************
 * Description:  DwarfStar landscape project                                *
 * Contained in: Test Projects                                              *
 * Developer:    Jean-Milost Reymond                                        *
 ****************************************************************************
 * MIT License - DwarfStar engine                                           *
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

 // dwarfstar
#include "Core\DWF_Capsule.h"
#include "Core\DWF_MeshFactory.h"
#include "Core\DWF_Sphere.h"
#include "Core\DWF_AABBTree.h"
#include "Core\DWF_Camera.h"
#include "Rendering\OpenGL\DWF_Texture_OpenGL.h"
#include "Rendering\OpenGL\DWF_Shader_OpenGL.h"
#include "Rendering\OpenGL\DWF_Renderer_OpenGL.h"

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
/*REM
bool         g_Rotate = false;
*/
//------------------------------------------------------------------------------
const char vertexShader[] = "precision mediump float;"
"attribute    vec3 aVertices;"
"attribute    vec2 aTexCoord;"
"uniform      mat4 uProjection;"
"uniform      mat4 uView;"
"uniform      mat4 uModel;"
"varying      vec2 vTexCoord;"
"void main(void)"
"{"
"    vTexCoord   = aTexCoord;"
"    gl_Position = uProjection * uView * uModel * vec4(aVertices, 1.0);"
"}";
//------------------------------------------------------------------------------
const char fragmentShader[] = "precision mediump float;"
"uniform      sampler2D sTexture;"
"varying      vec2      vTexCoord;"
"void main(void)"
"{"
"    gl_FragColor = texture2D(sTexture, vTexCoord);"
"}";
//------------------------------------------------------------------------------
DWF_Capsule g_Capsule1;
DWF_Capsule g_Capsule2;
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

        /*REM
        case WM_KEYDOWN:
            switch (wParam)
            {
                case '1':
                    break;

                case '2':
                    break;

                case VK_SPACE:
                    g_Rotate = !g_Rotate;
                    break;

                case VK_ESCAPE:
                    ::PostQuitMessage(0);
                    break;

                case VK_LEFT:
                    g_Capsule1Pos.m_X += 0.5f;
                    g_Capsule2Pos.m_X -= 0.5f;
                    break;

                case VK_RIGHT:
                    g_Capsule1Pos.m_X -= 0.5f;
                    g_Capsule2Pos.m_X += 0.5f;
                    break;
            }

            break;
            */

        default:
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }

    return 0;
}
//------------------------------------------------------------------------------
DWF_Texture* LoadTexture()
{
    std::size_t width = 0;
    std::size_t height = 0;
    std::size_t format = 0;
    std::size_t length = 0;
    void* pPixels = nullptr;

    if (!DWF_Texture::GetPixelsFromPng("Resources\\soccer_grass.png",
                                       false,
                                       width,
                                       height,
                                       format,
                                       length,
                                       pPixels))
        return nullptr;

    if (!pPixels)
        return nullptr;

    std::unique_ptr<DWF_Texture_OpenGL> pTexture(new DWF_Texture_OpenGL());
    pTexture->m_Width     = (std::int32_t)width;
    pTexture->m_Height    = (std::int32_t)height;
    pTexture->m_Format    = format == 24 ? DWF_Texture::IEFormat::IE_FT_24bit : DWF_Texture::IEFormat::IE_FT_32bit;
    pTexture->m_WrapMode  = DWF_Texture::IEWrapMode::IE_WM_Clamp;
    pTexture->m_MinFilter = DWF_Texture::IEMinFilter::IE_MI_Linear;
    pTexture->m_MagFilter = DWF_Texture::IEMagFilter::IE_MA_Linear;
    pTexture->Create(pPixels);

    return pTexture.release();
}
//---------------------------------------------------------------------------
/*REM
bool ApplyGroundCollision(const DWF_Sphere&     boundingSphere,
                                float           dir,
                                DWF_Matrix4x4F& matrix,
                                DWF_PlaneF&     groundPlane)
{
    DWF_Camera camera;

    // calculate the camera position in the 3d world, without the ground value
    camera.m_Position.m_X = -boundingSphere.m_Center.m_X;
    camera.m_Position.m_Y =  0.0f;
    camera.m_Position.m_Z = -boundingSphere.m_Center.m_Z;
    camera.m_xAngle       =  0.0f;
    camera.m_yAngle       =  dir;
    camera.m_zAngle       =  0.0f;
    camera.m_Factor.m_X   =  1.0f;
    camera.m_Factor.m_Y   =  1.0f;
    camera.m_Factor.m_Z   =  1.0f;
    camera.m_MatCombType  =  DWF_Camera::IEMatCombType::IE_CT_Translate_Scale_Rotate;

    // get the view matrix matching with the camera
    matrix = camera.GetMatrix();

    // get the model center
    DWF_Vector3F modelCenter;
    float        determinant;

    // calculate the current camera position above the landscape
    DWF_Matrix4x4F invertMatrix = matrix.Inverse(determinant);
    modelCenter = invertMatrix.Transform(modelCenter);

    CSR_CollisionOutput collisionOutput;

    // calculate the collisions in the whole scene
    csrSceneDetectCollision(g_pScene, &collisionInput, &collisionOutput, 0);

    // update the ground position directly inside the matrix (this is where the final value is required)
    pMatrix->m_Table[3][1] = -collisionOutput.m_GroundPos;

    // get the resulting plane
    *pGroundPlane = collisionOutput.m_GroundPlane;

    if (collisionOutput.m_Collision & CSR_CO_Ground)
        return 1;

    return 0;
}
*/
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
    wcex.hIcon         = ::LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LANDSCAPE));
    wcex.hIconSm       = ::LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SMALL));
    wcex.hCursor       = ::LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)::GetStockObject(BLACK_BRUSH);
    wcex.lpszMenuName  = nullptr;
    wcex.lpszClassName = L"dwarfstarCollisionsTest";

    if (!RegisterClassEx(&wcex))
        return 0;

    // create main window
    hWnd = ::CreateWindowEx(0,
                            L"dwarfstarCollisionsTest",
                            L"DwarfStar Collisions Test",
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

    DWF_Renderer_OpenGL renderer;

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

    DWF_Shader_OpenGL shader;
    shader.CreateProgram();
    shader.Attach(vertexShader, DWF_Shader::IEType::IE_ST_Vertex);
    shader.Attach(fragmentShader, DWF_Shader::IEType::IE_ST_Fragment);
    shader.Link(true);

    DWF_Camera camera;

    DWF_PixelBuffer pixels;
    pixels.FromBitmap(L"Resources\\level.bmp");

    DWF_VertexBuffer::IFormat format;
    format.m_Format = (DWF_VertexBuffer::IFormat::IEFormat)((std::int32_t)DWF_VertexBuffer::IFormat::IEFormat::IE_VF_TexCoords);
    format.m_Type   = DWF_VertexBuffer::IFormat::IEType::IE_VT_Triangles;

    DWF_VertexBuffer::ICulling culling;

    DWF_Material material;
    material.m_pTexture = LoadTexture();

    /*
    DWF_Mesh landscape;
    DWF_MeshFactory::GetLandscape(&pixels, 3.0f, 0.2f, format, culling, material, landscape, nullptr);
    */

    DWF_Mesh sphereMesh;
    DWF_MeshFactory::GetSphere(0.1f, 10.0f, 10.0f, format, culling, material, sphereMesh, nullptr);

    DWF_Matrix4x4F projMatrix;

    // create the viewport
    renderer.CreateViewport(float(clientRect.right - clientRect.left),
                            float(clientRect.bottom - clientRect.top),
                            0.1f,
                            1000.0f,
                            &shader,
                            projMatrix);

    // connect the projection matrix to the line shader
    renderer.ConnectProjectionMatrixToShader(&shader, projMatrix);

    /*
    // connect the view matrix to the both model and line shaders
    DWF_Matrix4x4F viewMatrix = DWF_Matrix4x4F::Identity();
    renderer.ConnectViewMatrixToShader(&shader, viewMatrix);
    */

    DWF_PolygonsF polygons;

    DWF_AABBTree tree;
    //tree.GetPolygons(landscape.m_VBs[0], polygons);
    tree.GetPolygons(sphereMesh.m_VBs[0], polygons);
    tree.Populate(polygons);

    DWF_ColorF bgColor;
    bgColor.m_R = 0.2f;
    bgColor.m_G = 0.5f;
    bgColor.m_B = 0.75f;
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
            /*
            DWF_Matrix4x4F matrix = DWF_Matrix4x4F::Identity();

            // create the X rotation matrix
            DWF_Matrix4x4F rotMatX;
            DWF_Vector3F   axis;
            axis.m_X = 1.0f;
            axis.m_Y = 0.0f;
            axis.m_Z = 0.0f;
            rotMatX  = matrix.Rotate(0.0f, axis);

            // create the Y rotation matrix
            DWF_Matrix4x4F rotMatY;
            axis.m_X = 0.0f;
            axis.m_Y = 1.0f;
            axis.m_Z = 0.0f;
            rotMatY  = matrix.Rotate(angle, axis);

            // create the Y rotation matrix
            DWF_Matrix4x4F rotMatZ;
            axis.m_X = 0.0f;
            axis.m_Y = 0.0f;
            axis.m_Z = 1.0f;
            rotMatZ  = matrix.Rotate(0.0f, axis);

            DWF_Matrix4x4F rotMat;

            // combine the rotation matrices
            rotMatY.Multiply(rotMatX);
            DWF_Matrix4x4F modelMatrix = rotMatZ.Multiply(rotMatY);

            // place the models in the 3d world (update the matrix directly)
            modelMatrix.m_Table[3][0] =  0.0f;
            modelMatrix.m_Table[3][1] = -2.0f;
            modelMatrix.m_Table[3][2] = 0.0f;// -10.0f;
            */

            //camera.m_Position.m_Z -= 0.01f;

            DWF_Matrix4x4F modelMatrix  = DWF_Matrix4x4F::Identity();
            DWF_Matrix4x4F cameraMatrix = camera.GetMatrix();
            cameraMatrix.m_Table[3][2] = -0.5f;

            // connect the view matrix to the both model and line shaders
            renderer.ConnectViewMatrixToShader(&shader, cameraMatrix);

            // calculate the elapsed time
            double elapsedTime = (double)::GetTickCount64() - lastTime;
            lastTime = (double)::GetTickCount64();

            // draw the scene
            renderer.BeginScene(bgColor, (DWF_Renderer::IESceneFlags)((std::uint32_t)DWF_Renderer::IESceneFlags::IE_SF_ClearColor |
                                                                      (std::uint32_t)DWF_Renderer::IESceneFlags::IE_SF_ClearDepth));

            /*REM
            float          determinant    = 0.0f;
            DWF_Matrix4x4F invModelMatrix = modelMatrix.Inverse(determinant);
            DWF_Vector3F   curPoint       = invModelMatrix.Transform(camera.m_Position);
            */

            /*
            camera.m_Position.m_Y = 0.0f;
            DWF_Sphere sphere(camera.m_Position, 0.1f);
            */

            //DWF_PolygonF gp;
            //float gy = 0.0f;

            /*REM
            DWF_PolygonsF gps;

            DWF_RayF ray(DWF_Vector3F(0.0f, 0.0f, 0.0f), DWF_Vector3F(0.0f, -1.0f, 0.0f));
            tree.Resolve(&ray, gps);

            for (DWF_PolygonsF::iterator it = gps.begin(); it != gps.end(); ++it)
            {
            */
            /*
            DWF_PolygonF polygonHit;// = *(*it);
            float        height = 0.0f;
            */
            //REM float gy = 0.0f;

            /*REM
            if (tree.GroundPosY(sphere, DWF_Vector3F(0.0f, -1.0f, 0.0f), polygonHit, height))
                camera.m_Position.m_Y = height;
            else
                camera.m_Position.m_Y = 0.0f;// 9999.0f;
            */

            /*
            tree.GroundPosY(sphere, DWF_Vector3F(0.0f, -1.0f, 0.0f), polygonHit, height);
            camera.m_Position.m_Y = height;
            */

            //REM int ii = 0;
            //}

            //renderer.Draw(landscape, modelMatrix, &shader);
            renderer.Draw(sphereMesh, modelMatrix, &shader);

            renderer.EndScene();

            /*REM*/
            // calculate the next angle
            //if (g_Rotate)
                //angle = std::fmodf(angle + ((float)elapsedTime * 0.001f), 2.0f * (float)M_PI);
            /**/

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
