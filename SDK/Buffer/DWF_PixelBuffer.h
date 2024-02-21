/****************************************************************************
 * ==> DWF_PixelBuffer -----------------------------------------------------*
 ****************************************************************************
 * Description: Pixel buffer                                                *
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

#pragma once

// std
#include <string>

// classes
#include "DWF_Buffer.h"

// libraries
#ifdef USE_PNG
    #include <png.h>
#endif

namespace DWF_Buffer
{
    /**
    * Pixel buffer
    *@author Jean-Milost Reymond
    */
    class PixelBuffer
    {
        public:
            /**
            * Image type
            */
            enum class IEImageType
            {
                IE_IT_Raw,
                IE_IT_Bitmap
            };

            /**
            * Pixel type
            */
            enum class IEPixelType
            {
                IE_PT_RGB,
                IE_PT_BGR,
                IE_PT_RGBA,
                IE_PT_BGRA,
                IE_PT_ARGB,
                IE_PT_ABGR
            };

            IEImageType   m_ImageType    = PixelBuffer::IEImageType::IE_IT_Raw;
            IEPixelType   m_PixelType    = PixelBuffer::IEPixelType::IE_PT_RGBA;
            std::uint32_t m_Width        = 0;
            std::uint32_t m_Height       = 0;
            std::uint32_t m_Stride       = 0;
            std::uint32_t m_BytePerPixel = 0;
            std::size_t   m_DataLength   = 0;
            void*         m_pData        = nullptr;

            PixelBuffer();
            virtual ~PixelBuffer();

            /**
            * Read pixel buffer from a bitmap file
            *@param fileName - bitmap file name to read from
            */
            virtual bool FromBitmap(const std::string& fileName);

            /**
            * Read pixel buffer from a bitmap file
            *@param fileName - bitmap file name to read from
            */
            virtual bool FromBitmap(const std::wstring& fileName);

            /**
            * Read pixel buffer from a bitmap buffer
            *@param buffer - buffer containing bitmap to read
            */
            virtual bool FromBitmap(Buffer& buffer);

            /**
            * Read pixel buffer from a Targa file
            *@param fileName - Targa file name to read from
            */
            virtual bool FromTga(const std::string& fileName);

            /**
            * Read pixel buffer from a Targa file
            *@param fileName - Targa file name to read from
            */
            virtual bool FromTga(const std::wstring& fileName);

            /**
            * Read pixel buffer from a Targa buffer
            *@param buffer - buffer containing Targa to read
            */
            virtual bool FromTga(Buffer& buffer);

            /**
            * Read pixel buffer from a png file
            *@param fileName - png file name to read from
            *@param is32bit - if true, the image should be opened in 32 bit BGRA format
            */
            #ifdef USE_PNG
                virtual bool FromPng(const std::string& fileName, bool is32bit);
            #endif

            /**
            * Read pixel buffer from a png file
            *@param fileName - png file name to read from
            *@param is32bit - if true, the image should be opened in 32 bit BGRA format
            */
            #ifdef USE_PNG
                virtual bool FromPng(const std::wstring& fileName, bool is32bit);
            #endif

            /**
            * Read pixel buffer from a png buffer
            *@param buffer - buffer containing png to read
            *@param is32bit - if true, the image should be opened in 32 bit BGRA format
            */
            #ifdef USE_PNG
                virtual bool FromPng(Buffer& buffer, bool is32bit);
            #endif

        private:
            /**
            * Targa (.tga) header
            */
            struct ITGAHeader
            {
                unsigned char m_IdentSize     =  0;
                unsigned char m_CMapType      =  0;
                unsigned char m_ImageType     =  0;
                unsigned char m_CMapOrigin[2] = {0};
                unsigned char m_CMapSize[2]   = {0};
                unsigned char m_CMapEntrySize =  0;
                unsigned char m_XOrigin[2]    = {0};
                unsigned char m_YOrigin[2]    = {0};
                unsigned char m_Width[2]      = {0};
                unsigned char m_Height[2]     = {0};
                unsigned char m_PixelSize     =  0;
                unsigned char m_DescByte      =  0;
            };

            /**
            * Loads png from buffer and convert to pixel array
            *@param image - source png image
            *@param pBuffer - buffer containing bitmap data to load
            *@param is32bit - if true, the image should be opened in 32 bit BGRA format
            *@param[out] width - bitmap width, in pixels
            *@param[out] height - bitmap height, in pixels
            *@param[out] format - bitmap format (i.e. byte per pixels)
            *@param[out] length - pixels length in bytes
            *@param[out] pPixels - bitmap pixel array
            *@return true on success, otherwise false
            *@note Pixel array must be deleted when useless
            */
            #ifdef USE_PNG
                bool LoadPngData(const png_image&   image,
                                 const png_bytep    pBuffer,
                                       bool         is32bit,
                                       std::size_t& width,
                                       std::size_t& height,
                                       std::size_t& format,
                                       std::size_t& length,
                                       void*&       pPixels) const;
            #endif

            /**
            * Converts RGB to BGR
            *@param pData - data to convert, converted data on function ends
            *@param len - data length
            *@param bpp - byte per pixels
            */
            inline void BGRToRGB(unsigned char* pData, int len, int bpp);
    };

    //---------------------------------------------------------------------------
    // PixelBuffer
    //---------------------------------------------------------------------------
    inline void PixelBuffer::BGRToRGB(unsigned char* pData, int len, int bpp)
    {
        unsigned char* pEnd;

        for (pEnd = &pData[len]; pData < pEnd; pData += bpp)
        {
            pData[0] = pData[0] ^ pData[2];
            pData[2] = pData[0] ^ pData[2];
            pData[0] = pData[2] ^ pData[0];
        }
    }
    //---------------------------------------------------------------------------
}
