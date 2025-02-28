/****************************************************************************
 * ==> DWF_MDL -------------------------------------------------------------*
 ****************************************************************************
 * Description : Quake I model (.mdl)                                       *
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
#include "DWF_PixelBuffer.h"
#include "DWF_Color.h"
#include "DWF_Vector2.h"
#include "DWF_Vector3.h"
#include "DWF_Matrix4x4.h"
#include "DWF_Model.h"

#define CONVERT_ENDIANNESS

namespace DWF_Model
{
    /**
    * Quake I model (.mdl)
    *@author Jean-Milost Reymond
    */
    class MDL
    {
        public:
            /**
            * Called when a texture should be created
            *@param arg1 - pixel buffer containing the texture to load
            *@return texture
            */
            typedef std::function<DWF_Model::Texture*(const DWF_Buffer::PixelBuffer* pPixelBuffer)> ITfOnCreateTexture;

            MDL();
            virtual ~MDL();

            /**
            * Clears the model
            */
            virtual void Clear();

            /**
            * Opens an .mdl model from file
            *@param fileName - mdl file to open
            *@return true on success, otherwise false
            */
            virtual bool Open(const std::string& fileName);

            /**
            * Opens an .mdl model from file
            *@param fileName - mdl file to open
            *@return true on success, otherwise false
            */
            virtual bool Open(const std::wstring& fileName);

            /**
            * Opens an .mdl model from buffer
            *@param buffer - buffer containing the mdl data to open
            *@return true on success, otherwise false
            *@note the buffer should be positioned to the data start
            */
            virtual bool Open(DWF_Buffer::Buffer& buffer);

            /**
            * Gets the model
            *@param fps - frame per seconds
            *@param animationIndex - animation index
            *@param[in, out] textureIndex - texture index, new texture index on function ends
            *@param[in, out] modelIndex - model index, new model index on function ends
            *@param[in, out] textureLastTime - texture last time, new texture last time on function ends
            *@param[in, out] modelLastTime - model last time, new model last time on function ends
            *@param elapsedTime - elapsed time since last frame, in milliseconds
            *@return a ready-to-draw copy of the model, nullptr on error
            *@note The model will be deleted internally, do not delete it from outside
            */
            virtual Model* GetModel(std::size_t  fps,
                                    std::size_t  animationIndex,
                                    std::size_t& textureIndex,
                                    std::size_t& modelIndex,
                                    double&      textureLastTime,
                                    double&      modelLastTime,
                                    double       elapsedTime) const;

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
            * Sets the OnCreateTexture callback
            *@param fOnCreateTexture - callback function handle
            */
            void Set_OnCreateTexture(ITfOnCreateTexture fOnCreateTexture);

        private:
            /**
            * Memory endianness type
            */
            enum class IEEndianness
            {
                IE_E_LittleEndian,
                IE_E_BigEndian
            };

            /**
            * MDL header
            */
            struct IHeader
            {
                unsigned m_ID             =  0;
                unsigned m_Version        =  0;
                float    m_Scale[3]       = {0.0f};
                float    m_Translate[3]   = {0.0f};
                float    m_BoundingRadius =  0.0f;
                float    m_EyePosition[3] = {0.0f};
                unsigned m_SkinCount      =  0;
                unsigned m_SkinWidth      =  0;
                unsigned m_SkinHeight     =  0;
                unsigned m_VertexCount    =  0;
                unsigned m_PolygonCount   =  0;
                unsigned m_FrameCount     =  0;
                unsigned m_SyncType       =  0;
                unsigned m_Flags          =  0;
                float    m_Size           =  0.0f;

                IHeader();
                ~IHeader();

                /**
                * Reads the structure content
                *@param buffer - buffer to read from
                *@return true on success, otherwise false
                */
                bool Read(DWF_Buffer::Buffer& buffer);
            };

            /**
            * MDL skin
            */
            struct ISkin
            {
                unsigned       m_Group  = 0;
                unsigned       m_Count  = 0;
                unsigned       m_TexLen = 0;
                float*         m_pTime  = nullptr;
                unsigned char* m_pData  = nullptr;

                ISkin();
                ~ISkin();

                /**
                * Reads the structure content
                *@param header - mdl header
                *@param buffer - buffer to read from
                *@return true on success, otherwise false
                */
                bool Read(const IHeader& header, DWF_Buffer::Buffer& buffer);
            };

            typedef std::vector<ISkin> ISkins;

            /**
            * MDL texture coordinate
            */
            struct ITextureCoord
            {
                unsigned m_OnSeam = 0;
                unsigned m_U      = 0;
                unsigned m_V      = 0;

                ITextureCoord();
                ~ITextureCoord();

                /**
                * Reads the structure content
                *@param buffer - buffer to read from
                *@return true on success, otherwise false
                */
                bool Read(DWF_Buffer::Buffer& buffer);
            };

            typedef std::vector<ITextureCoord> ITextureCoords;

            /**
            * MDL polygon
            */
            struct IPolygon
            {
                unsigned m_FacesFront     =  0;
                unsigned m_VertexIndex[3] = {0};

                IPolygon();
                ~IPolygon();

                /**
                * Reads the structure content
                *@param buffer - buffer to read from
                *@return true on success, otherwise false
                */
                bool Read(DWF_Buffer::Buffer& buffer);
            };

            typedef std::vector<IPolygon> IPolygons;

            /**
            * MDL vertex
            */
            struct IVertex
            {
                unsigned char m_Vertex[3]   = {0};
                unsigned char m_NormalIndex =  0;

                IVertex();
                ~IVertex();

                /**
                * Reads the structure content
                *@param buffer - buffer to read from
                *@return true on success, otherwise false
                */
                bool Read(DWF_Buffer::Buffer& buffer);
            };

            typedef std::vector<IVertex> IVertices;

            /**
            * MDL frame
            */
            struct IFrame
            {
                IVertex  m_BoundingBoxMin;
                IVertex  m_BoundingBoxMax;
                char     m_Name[16] = {0};
                IVertex* m_pVertex  =  nullptr;

                IFrame();
                ~IFrame();

                /**
                * Reads the structure content
                *@param header - mdl header
                *@param buffer - buffer to read from
                *@return true on success, otherwise false
                */
                bool Read(const IHeader& header, DWF_Buffer::Buffer& buffer);
            };

            /**
            * MDL frame group
            */
            struct IFrameGroup
            {
                unsigned m_Type   = 0;
                unsigned m_Count  = 0;
                IVertex  m_BoundingBoxMin;
                IVertex  m_BoundingBoxMax;
                float*   m_pTime  = nullptr;
                IFrame*  m_pFrame = nullptr;

                IFrameGroup();
                ~IFrameGroup();

                /**
                * Reads the structure content
                *@param header - mdl header
                *@param buffer - buffer to read from
                *@return true on success, otherwise false
                */
                bool Read(const IHeader& header, DWF_Buffer::Buffer& buffer);
            };

            typedef std::vector<IFrameGroup> IFrameGroups;

            /**
            * Model animation
            */
            struct IAnimation
            {
                char        m_Name[16] = {0}; // animation name
                std::size_t m_Start    =  0;  // animation start frame
                std::size_t m_End      =  0;  // animation end frame

                IAnimation();
                virtual ~IAnimation();
            };

            typedef std::vector<IAnimation*> IAnimations;

            std::vector<Model*>               m_Models;
            std::unique_ptr<Model>            m_pCachedModel;
            std::vector<DWF_Model::Texture*>  m_Textures;
            std::vector<double>               m_TextureTimes;
            std::vector<std::string>          m_TextureNames;
            IAnimations                       m_Animations;
            VertexFormat                      m_VertFormatTemplate;
            VertexCulling                     m_VertCullingTemplate;
            Material                          m_MaterialTemplate;
            VertexBuffer::ITfOnGetVertexColor m_fOnGetVertexColor = nullptr;
            ITfOnCreateTexture                m_fOnCreateTexture  = nullptr;

            /**
            * Reads the buffer content
            *@param buffer - buffer to read
            *@return true on success, otherwise false
            */
            bool Read(DWF_Buffer::Buffer& buffer);

            /**
            * Populates the model
            *@param header - mdl header
            *@param frameGroup - current mdl frame group
            *@param polygons - mdl polygons
            *@param texCoords - mdl texture coordinates
            *@return true on success, otherwise false
            *@param[in, out] pModel - model to populate
            */
            bool PopulateModel(const IHeader&        header,
                               const IFrameGroup&    frameGroup,
                               const IPolygons&      polygons,
                               const ITextureCoords& texCoords,
                                     Model*          pModel) const;

            /**
            * Uncompresses a texture read from the .mdl file
            *@param skin - mdl skin containing the texture
            *@param width - texture width
            *@param height - texture height
            *@param index - texture index
            *@return pixel buffer containing the texture
            */
            DWF_Buffer::PixelBuffer* UncompressTexture(const ISkin&      skin,
                                                             std::size_t width,
                                                             std::size_t height,
                                                             std::size_t index) const;

            /**
            * Uncompresses a vertex
            *@param header - mdl header
            *@param vertex - mdl vertex
            *@return uncompressed vertex
            */
            DWF_Math::Vector3F UncompressVertex(const IHeader& header, const IVertex& vertex) const;

            /**
            * Gets the memory endianness
            *@return the memory endianness
            */
            #ifdef CONVERT_ENDIANNESS
                static IEEndianness GetEndianness();
            #endif

            /**
            * Swaps the memory content between big and little endian
            *@param[in, out] pMemory - memory to swap, swapped memory on function ends
            *@paran size - size of memory to swap in bytes
            */
            #ifdef CONVERT_ENDIANNESS
                static void SwapMemory(void* pMemory, std::size_t size);
            #endif
    };
}
