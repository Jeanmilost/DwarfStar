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
            typedef std::vector<float>        IVertexData;
            typedef std::vector<std::int64_t> IFaceData;

            Model*                            m_pModel            = nullptr;
            VertexFormat                      m_VertFormatTemplate;
            VertexCulling                     m_VertCullingTemplate;
            Material                          m_MaterialTemplate;
            VertexBuffer::ITfOnGetVertexColor m_fOnGetVertexColor = nullptr;
            Texture::ITfOnLoadTexture         m_fOnLoadTexture    = nullptr;

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
            *@param[in, out] vertexData - vertex data in which the read values should be added
            */
            void ReadLine(const std::string data, std::size_t& index, IVertexData& vertexData);

            /**
            * Reads a line from the WaveFront file
            *@param data - data to read from
            *@param[in, out] index - current data index, new data index on function ends
            *@param[in, out] faceData - face data in which the read values should be added
            */
            void ReadLine(const std::string data, std::size_t& index, IFaceData& faceData);

            /**
            * Skip a line and go to the next one
            *@param data - data to read from
            *@param[in, out] index - current data index, data index located on the next line on function ends
            */
            void SkipLine(const std::string data, std::size_t& index);

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
                           bool               objectChanging,
                           bool               groupChanging);

            /**
            * Builds a vertex buffer from a WaveFront data
            *@param vertices - vertex array read in WaveFront file
            *@param normals - normal array read in WaveFront file
            *@param uvs - texture coordinates array read in WaveFront file
            *@param faces - face array read in WaveFront file
            *@param[in, out] pVB - vertex buffer in which the WaveFront data should be built
            */
            void BuildVertexBuffer(const IVertexData& vertices,
                                   const IVertexData& normals,
                                   const IVertexData& uvs,
                                   const IFaceData&   faces,
                                   VertexBuffer*      pVB);
    };
}
