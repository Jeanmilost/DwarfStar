/****************************************************************************
 * ==> DWF_VoxelAsset ------------------------------------------------------*
 ****************************************************************************
 * Description: Voxel asset                                                 *
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

#include "DWF_VoxelAsset.h"

// classes
#include "DWF_ModelFactory.h"

using namespace DWF_Voxel;

//---------------------------------------------------------------------------
// VoxelAsset
//---------------------------------------------------------------------------
VoxelAsset::VoxelAsset(DWF_Renderer::Shader* pShader, DWF_Renderer::Renderer* pRenderer) :
    Voxels(pShader, pRenderer)
{}
//---------------------------------------------------------------------------
VoxelAsset::~VoxelAsset()
{}
//---------------------------------------------------------------------------
bool VoxelAsset::Load(const DWF_Buffer::PixelBuffer& bitmap)
{
    std::map<std::uint32_t, DWF_Model::Model*> modelDictionary;

    // iterate through bitmap pixels
    for (std::size_t y = 0; y < bitmap.m_Height; ++y)
        for (std::size_t x = 0; x < bitmap.m_Width; ++x)
        {
            const std::size_t i = (y * bitmap.m_Stride) + (x * bitmap.m_BytePerPixel);

            const std::uint8_t b = (std::uint8_t)(static_cast<unsigned char*>(bitmap.m_pData)[i]);
            const std::uint8_t g = (std::uint8_t)(static_cast<unsigned char*>(bitmap.m_pData)[i + 1]);
            const std::uint8_t r = (std::uint8_t)(static_cast<unsigned char*>(bitmap.m_pData)[i + 2]);

            // color key to ignore?
            if (r == 255 && g == 0 && b == 255)
                continue;

            // calculate the color
            const std::uint32_t color = (r << 16) | (g << 8) | b;

            DWF_Model::Model* pModel;

            // search for an already created matching model
            auto it = modelDictionary.find(color);

            // a matching model already exists?
            if (it == modelDictionary.end())
            {
                // no, create a new model and add it to the list
                DWF_Model::Material material;
                material.m_Color = DWF_Model::ColorF((float)r / 255.0f, (float)g / 255.0f, (float)b / 255.0f, 1.0f);

                DWF_Model::VertexCulling culling;

                DWF_Model::VertexFormat format;
                format.m_Format = (DWF_Model::VertexFormat::IEFormat)((std::int32_t)DWF_Model::VertexFormat::IEFormat::IE_VF_Colors);
                format.m_Type   =  DWF_Model::VertexFormat::IEType::IE_VT_TriangleStrip;

                std::unique_ptr<DWF_Model::Model> pBoxModel(DWF_Model::Factory::GetBox(1.0f,
                                                                                       1.0f,
                                                                                       1.0f,
                                                                                       false,
                                                                                       format,
                                                                                       culling,
                                                                                       material));

                m_Models.push_back(pBoxModel.get());

                modelDictionary[color] = pBoxModel.get();
                pModel                 = pBoxModel.release();
            }
            else
                // yes, get it
                pModel = it->second;

            // calculate x and y position
            const float xPos = (float)(bitmap.m_Width  / 2.0f) - x - 0.5f;
            const float yPos = (float)(bitmap.m_Height / 2.0f) - y - 0.5f;

            // create the Voxel
            std::unique_ptr<Voxel> pVoxel = std::make_unique<Voxel>(pModel, m_pShader, m_pRenderer);
            pVoxel->SetPos(DWF_Math::Vector3F(xPos, yPos, 0.0f));
            m_Voxels.push_back(pVoxel.get());
            pVoxel.release();

            // calculate the min bounding box edge
            m_pBox->m_Min.m_X = std::min(m_pBox->m_Min.m_X, xPos - 0.5f);
            m_pBox->m_Min.m_Y = std::min(m_pBox->m_Min.m_Y, yPos - 0.5f);

            // calculate the max bounding box edge
            m_pBox->m_Max.m_X = std::max(m_pBox->m_Max.m_X, xPos + 0.5f);
            m_pBox->m_Max.m_Y = std::max(m_pBox->m_Max.m_Y, yPos + 0.5f);
        }

    return true;
}
//---------------------------------------------------------------------------
