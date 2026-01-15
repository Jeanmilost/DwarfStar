/****************************************************************************
 * ==> Skybox --------------------------------------------------------------*
 ****************************************************************************
 * Description : Nebulus skybox                                             *
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

#include "Skybox.h"

// classes
#include "DWF_PixelBuffer.h"

using namespace Nebulus;

//---------------------------------------------------------------------------
// Skybox
//---------------------------------------------------------------------------
Skybox::Skybox(DWF_Scene::Scene* pScene) :
    Item(pScene)
{}
//---------------------------------------------------------------------------
Skybox::~Skybox()
{
    if (m_SkyboxTexId != -1)
        glDeleteTextures(1, &m_SkyboxTexId);
}
//---------------------------------------------------------------------------
DWF_Model::Texture_OpenGL* Skybox::LoadTexture(const std::string& fileName, bool is32bit) const
{
    return nullptr;
}
//---------------------------------------------------------------------------
bool Skybox::Load(const std::shared_ptr<DWF_Renderer::Shader>& pShader)
{
    // get the scene
    DWF_Scene::Scene* pScene = GetScene();

    if (!pScene)
        return false;

    const std::string folder = "..\\..\\Resources\\Skybox\\Starfield\\";

    IFilenames cubemapFilenames;
    cubemapFilenames.push_back(folder + "right.png");
    cubemapFilenames.push_back(folder + "left.png");
    cubemapFilenames.push_back(folder + "top.png");
    cubemapFilenames.push_back(folder + "bottom.png");
    cubemapFilenames.push_back(folder + "front.png");
    cubemapFilenames.push_back(folder + "back.png");

    // load the skybox textures
    std::unique_ptr<DWF_Model::Texture_OpenGL> pTexture = std::make_unique<DWF_Model::Texture_OpenGL>();
    pTexture->m_Target = DWF_Model::Texture::IETarget::IE_TT_Cubemap;
    m_SkyboxTexId      = LoadCubemap(cubemapFilenames, false);
    pTexture->SetID(m_SkyboxTexId);

    // set the skybox in scene
    pScene->SetSkybox(pTexture.get(), pShader);
    pTexture.release();

    return true;
}
//---------------------------------------------------------------------------
GLuint Skybox::LoadCubemap(const IFilenames fileNames, bool convertPixels) const
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
                case 3:  pixelType = GL_RGB;  break;
                case 4:  pixelType = GL_RGBA; break;
                default: return -1;
            }

            // do convert pixels?
            if (convertPixels)
            {
                // calculate image stride
                const std::size_t stride = pPixelBuffer->m_Stride;

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
