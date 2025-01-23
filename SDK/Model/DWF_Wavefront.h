/****************************************************************************
 * ==> DWF_Wavefront -------------------------------------------------------*
 ****************************************************************************
 * Description : Wavefront (.obj) model                                     *
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

#pragma once

// classes
#include "DWF_Buffer.h"
#include "DWF_Color.h"
#include "DWF_Vector2.h"
#include "DWF_Vector3.h"
#include "DWF_Matrix4x4.h"
#include "DWF_Model.h"

namespace DWF_Model
{
    /**
    * Wavefront (.obj) model
    *@author Jean-Milost Reymond
    */
    class Wavefront
    {
        public:
            /**
            * Called when a material file buffer should be opened
            *@param arg1 - material file name to open
            *@param arg2 - file buffer in which the material file should be opened
            */
            typedef std::function<bool(const std::string&, DWF_Buffer::Buffer*&)> ITfOnOpenMaterialFile;

            Wavefront();
            virtual ~Wavefront();

            /**
            * Clears the model
            */
            virtual void Clear();

            /**
            * Opens a Wavefront (.obj) model from file
            *@param fileName - Wavefront file to open
            *@return true on success, otherwise false
            */
            virtual bool Open(const std::string& fileName);

            /**
            * Opens a Wavefront (.obj) model from file
            *@param fileName - Wavefront file to open
            *@return true on success, otherwise false
            */
            virtual bool Open(const std::wstring& fileName);

            /**
            * Opens a Wavefront (.obj) model from buffer
            *@param buffer - buffer containing the Wavefront data to open
            *@return true on success, otherwise false
            *@note the buffer should be positioned to the data start
            */
            virtual bool Open(DWF_Buffer::Buffer& buffer);

            /**
            * Gets the model
            *@return the model, nullptr if no model or on error
            */
            virtual Model* GetModel() const;

            /**
            * Changes the vertex format template
            *@param vertFormatTemplate - new vertex format template
            */
            virtual void SetVertFormatTemplate(const VertexFormat& vertFormatTemplate);

            /**
            * Changes the vertex culling template
            *@param vertCullingTemplate - new vertex culling template
            */
            virtual void SetVertCullingTemplate(const VertexCulling& vertCullingTemplate);

            /**
            * Changes the material template
            *@param materialTemplate - new material template
            */
            virtual void SetMaterial(const Material& materialTemplate);

            /**
            * Sets the OnOpenMaterialFile callback
            *@param fOnOpenMaterialFile - callback function handle
            */
            void Set_OnOpenMaterialFile(ITfOnOpenMaterialFile fOnOpenMaterialFile);

            /**
            * Sets the OnGetVertexColor callback
            *@param fOnGetVertexColor - callback function handle
            */
            void Set_OnGetVertexColor(VertexBuffer::ITfOnGetVertexColor fOnGetVertexColor);

            /**
            * Sets the OnLoadTexture callback
            *@param fOnLoadTexture - callback function handle
            */
            void Set_OnLoadTexture(Texture::ITfOnLoadTexture fOnLoadTexture);

        private:
            /**
            * Helper class to e.g. read from files
            */
            class IHelper
            {
                public:
                    /**
                    * Skip a line and go to the next one
                    *@param data - data to read from
                    *@param[in, out] index - current data index, data index located on the next line on function ends
                    */
                    static void SkipLine(const std::string data, std::size_t& index);

                    /**
                    * Reads a line from the WaveFront material file
                    *@param data - data to read from
                    *@param[in, out] index - current data index, new data index on function ends
                    *@param[in, out] text - text read after the line identifier
                    */
                    static void ReadLine(const std::string data, std::size_t& index, std::string& text);
            };

            /**
            * Wavefront material
            */
            class IMaterial
            {
                public:
                    std::string m_Name;
                    std::string m_TextureFileName;

                    IMaterial();
                    ~IMaterial();

                    /**
                    * Clears the material
                    */
                    void Clear();

                    /**
                    * Reads the buffer content
                    *@param buffer - buffer to read
                    *@return true on success, otherwise false
                    */
                    bool Read(DWF_Buffer::Buffer& buffer);
            };

            typedef std::map<std::string, IMaterial> IMaterials;
            typedef std::vector<float>               IVertexData;
            typedef std::vector<std::int64_t>        IFaceData;

            Model*                            m_pModel              = nullptr;
            VertexFormat                      m_VertFormatTemplate;
            VertexCulling                     m_VertCullingTemplate;
            Material                          m_MaterialTemplate;
            IMaterials                        m_Materials;
            VertexBuffer::ITfOnGetVertexColor m_fOnGetVertexColor   = nullptr;
            Texture::ITfOnLoadTexture         m_fOnLoadTexture      = nullptr;
            ITfOnOpenMaterialFile             m_fOnOpenMaterialFile = nullptr;

            /**
            * Reads the buffer content
            *@param buffer - buffer to read
            *@return true on success, otherwise false
            */
            bool Read(DWF_Buffer::Buffer& buffer);

            /**
            * Reads a line from the WaveFront file
            *@param data - data to read from
            *@param[in, out] index - current data index, new data index on function ends
            *@param[in, out] material - material to populate with the read data
            */
            void ReadLine(const std::string data, std::size_t& index, IMaterial& material) const;

            /**
            * Reads a line from the WaveFront file
            *@param data - data to read from
            *@param[in, out] index - current data index, new data index on function ends
            *@param[in, out] vertexData - vertex data in which the read values should be added
            */
            void ReadLine(const std::string data, std::size_t& index, IVertexData& vertexData) const;

            /**
            * Reads a line from the WaveFront file
            *@param data - data to read from
            *@param[in, out] index - current data index, new data index on function ends
            *@param[in, out] faceData - face data in which the read values should be added
            */
            void ReadLine(const std::string data, std::size_t& index, IFaceData& faceData) const;

            /**
            * Builds a face from WaveFront data
            *@param vertices - vertex array read in WaveFront file
            *@param normals - normal array read in WaveFront file
            *@param uvs - texture coordinates array read in WaveFront file
            *@param faces - face array read in WaveFront file
            *@param objectChanging - if true, a new object should be created
            *@param groupChanging - if true, a new group should be created
            *@return true on success, otherwise false
            */
            bool BuildFace(const IVertexData& vertices,
                           const IVertexData& normals,
                           const IVertexData& uvs,
                           const IFaceData&   faces,
                           const std::string& matName,
                                 bool         objectChanging,
                                 bool         groupChanging) const;

            /**
            * Builds a vertex buffer from a WaveFront data
            *@param vertices - vertex array read in WaveFront file
            *@param normals - normal array read in WaveFront file
            *@param uvs - texture coordinates array read in WaveFront file
            *@param faces - face array read in WaveFront file
            *@param[in, out] pVB - vertex buffer in which the WaveFront data should be built
            */
            void BuildVertexBuffer(const IVertexData&  vertices,
                                   const IVertexData&  normals,
                                   const IVertexData&  uvs,
                                   const IFaceData&    faces,
                                         VertexBuffer* pVB) const;
    };
}
