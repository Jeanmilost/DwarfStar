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

#include "DWF_PixelBuffer.h"

// std
#include <memory>

// classes
#include "DWF_StdFileBuffer.h"

using namespace DWF_Buffer;

//---------------------------------------------------------------------------
// PixelBuffer
//---------------------------------------------------------------------------
PixelBuffer::PixelBuffer()
{}
//---------------------------------------------------------------------------
PixelBuffer::~PixelBuffer()
{
    if (m_pData)
        delete[] m_pData;
}
//---------------------------------------------------------------------------
bool PixelBuffer::FromBitmap(const std::string& fileName)
{
    // no file name?
    if (fileName.empty())
        return false;

    // open the file
    std::unique_ptr<StdFileBuffer> pFileBuffer(new StdFileBuffer());
    pFileBuffer->Open(fileName, FileBuffer::IEMode::IE_M_Read);
    pFileBuffer->Seek(0, 0);

    return FromBitmap(*pFileBuffer);
}
//---------------------------------------------------------------------------
bool PixelBuffer::FromBitmap(const std::wstring& fileName)
{
    // no file name?
    if (fileName.empty())
        return false;

    // open the file
    std::unique_ptr<StdFileBuffer> pFileBuffer(new StdFileBuffer());
    pFileBuffer->Open(fileName, FileBuffer::IEMode::IE_M_Read);
    pFileBuffer->Seek(0, 0);

    return FromBitmap(*pFileBuffer);
}
//---------------------------------------------------------------------------
bool PixelBuffer::FromBitmap(Buffer& buffer)
{
    // validate the input
    if (!buffer.GetSize())
        return false;

    if (m_pData)
    {
        delete[] m_pData;
        m_pData = nullptr;
    }

    const std::size_t  startOffset = buffer.GetOffset();
          std::uint8_t signature[2];

    // read bitmap signature
    buffer.Read(&signature[0], 2);

    // is bitmap signature correct?
    if (signature[0] != 'B' || signature[1] != 'M')
        return false;

    // skip 8 next bytes
    buffer.Seek(buffer.GetOffset(), 8);

    std::uint32_t dataOffset = 0;

    // read data offset
    buffer.Read(&dataOffset, sizeof(std::uint32_t));

    std::uint32_t headerSize = 0;

    // read header size
    buffer.Read(&headerSize, sizeof(std::uint32_t));

    std::uint16_t bpp = 0;

    // search for bitmap type
    switch (headerSize)
    {
        // V3
        case 40:
        {
            // read bitmap width
            buffer.Read(&m_Width, sizeof(std::uint32_t));

            // read bitmap height
            buffer.Read(&m_Height, sizeof(std::uint32_t));

            // skip next 2 bytes
            buffer.Seek(buffer.GetOffset(), 2);

            // read bitmap bit per pixels
            buffer.Read(&bpp, sizeof(std::uint16_t));

            // is bpp supported?
            if (bpp != 24)
                return false;

            std::uint32_t compressed = 0;

            // read bitmap compressed flag
            buffer.Read(&compressed, sizeof(std::uint32_t));

            // is compressed?
            if (compressed)
                return false;

            break;
        }

        // OS/2 V1
        case 12:
        {
            std::uint16_t width  = 0;
            std::uint16_t height = 0;

            // read bitmap width
            buffer.Read(&width, sizeof(std::uint16_t));

            // read bitmap height
            buffer.Read(&height, sizeof(std::uint16_t));

            m_Width  = width;
            m_Height = height;

            // skip next 2 bytes
            buffer.Seek(buffer.GetOffset(), 2);

            // read bitmap bit per pixels
            buffer.Read(&bpp, sizeof(std::uint16_t));

            // is bpp supported?
            if (bpp != 24)
                return false;

            break;
        }

        // Windows V4
        case 108:
        {
            // read bitmap width and height
            buffer.Read(&m_Width, sizeof(std::uint32_t));
            buffer.Read(&m_Height, sizeof(std::uint32_t));

            // skip next 4 bytes
            buffer.Seek(buffer.GetOffset(), 2);

            // read bitmap bit per pixels
            buffer.Read(&bpp, sizeof(std::uint16_t));

            // is bpp supported?
            if (bpp != 24)
                return false;

            break;
        }

        // Windows V5
        case 124:
            // unsupported bitmap format
            return false;

        default:
            // unsupported bitmap format
            return false;
    }

    m_ImageType    = PixelBuffer::IEImageType::IE_IT_Bitmap;
    m_PixelType    = PixelBuffer::IEPixelType::IE_PT_BGR;
    m_BytePerPixel = bpp / 8;
    m_Stride       = ((m_Width * 3 + 3) / 4) * 4;
    m_DataLength   = (std::size_t)m_Stride * (std::size_t)m_Height;
    m_pData        = new std::uint8_t[m_DataLength];

    buffer.Seek(startOffset, dataOffset);

    // read bitmap data
    buffer.Read(m_pData, m_DataLength);

    return true;
}
//---------------------------------------------------------------------------
bool PixelBuffer::FromTga(const std::string& fileName)
{
    // no file name?
    if (fileName.empty())
        return false;

    // open the file
    std::unique_ptr<StdFileBuffer> pFileBuffer(new StdFileBuffer());
    pFileBuffer->Open(fileName, FileBuffer::IEMode::IE_M_Read);
    pFileBuffer->Seek(0, 0);

    return FromTga(*pFileBuffer);
}
//---------------------------------------------------------------------------
bool PixelBuffer::FromTga(const std::wstring& fileName)
{
    // no file name?
    if (fileName.empty())
        return false;

    // open the file
    std::unique_ptr<StdFileBuffer> pFileBuffer(new StdFileBuffer());
    pFileBuffer->Open(fileName, FileBuffer::IEMode::IE_M_Read);
    pFileBuffer->Seek(0, 0);

    return FromTga(*pFileBuffer);
}
//---------------------------------------------------------------------------
bool PixelBuffer::FromTga(Buffer& buffer)
{
    // validate the input
    if (!buffer.GetSize())
        return false;

    if (m_pData)
    {
        delete[] m_pData;
        m_pData = nullptr;
    }

    const std::size_t startOffset = buffer.GetOffset();
          ITGAHeader  header;

    // read the header
    buffer.Read(&header, sizeof(ITGAHeader));

    // is image file valid?
    if (header.m_PixelSize != 8 && header.m_PixelSize != 24 && header.m_PixelSize != 32)
        return false;

    buffer.Seek(startOffset, sizeof(ITGAHeader) + header.m_IdentSize);

    // get the image width and height
    m_Width  = header.m_Width[0]  + ((std::size_t)header.m_Width[1]  << 8);
    m_Height = header.m_Height[0] + ((std::size_t)header.m_Height[1] << 8);

    // calculate the stride
    m_Stride = m_Width * (header.m_PixelSize / 8);

    switch (header.m_ImageType)
    {
        case 1:
        {
            // validate the color map entry size
            if (header.m_CMapEntrySize != 8 && header.m_CMapEntrySize != 24 && header.m_CMapEntrySize != 32)
                return false;

            // get the color map size
            unsigned cMapSize = header.m_CMapSize[0] + (header.m_CMapSize[1] << 8);

            // get the pixel format
            m_BytePerPixel = header.m_PixelSize / 8;

            // calculate the byte per pixels, and allocate memory for color map
            const std::size_t    bytePerPixel = header.m_CMapEntrySize / 8;
            const std::size_t    cMapLength   = (std::size_t)bytePerPixel * (std::size_t)cMapSize;
                  unsigned char* pCMap        = new unsigned char[cMapLength];

            // read the color map
            buffer.Read(pCMap, cMapLength);

            // do convert the BGR pixel order to RGB?
            if (bytePerPixel >= 3)
                BGRToRGB(pCMap, (int)bytePerPixel * cMapSize, (int)bytePerPixel);

            // allocate memory for pixels and get indexes pointer
                                 m_DataLength = bytePerPixel * m_Width * m_Height;
                                 m_pData      = new unsigned char[m_DataLength];
                  unsigned char* pIndexes     = &((unsigned char*)m_pData)[(bytePerPixel - 1) * m_Width * m_Height];
            const std::size_t    indexLength  = (std::size_t)m_Width * (std::size_t)m_Height;

            // read the index table
            buffer.Read(pIndexes, indexLength);

            unsigned char* pSrc = pIndexes;
            unsigned char* pDst = &((unsigned char*)m_pData)[m_DataLength];

            // copy the pixels
            for (std::size_t i = 0; i < m_Height; ++i)
            {
                unsigned char* pRow;

                pDst -= bytePerPixel * m_Width;
                pRow  = pDst;

                for (std::size_t j = 0; j < m_Width; ++j)
                {
                    std::memcpy(pRow, &pCMap[*pSrc++ * bytePerPixel], bytePerPixel);
                    pRow += bytePerPixel;
                }
            }

            delete[] pCMap;

            m_ImageType = PixelBuffer::IEImageType::IE_IT_Bitmap;
            m_PixelType = PixelBuffer::IEPixelType::IE_PT_RGB;

            return true;
        }

        case 2:
        {
            // get the pixel format
            m_BytePerPixel = header.m_PixelSize / 8;

            // calculate the data length
            m_DataLength = (std::size_t)m_BytePerPixel * (std::size_t)m_Width * (std::size_t)m_Height;

            // create destination pixel buffer
                                 m_pData = new unsigned char[m_DataLength];
                  unsigned char* pDst    = &((unsigned char*)m_pData)[m_DataLength];
            const std::size_t    size    = (std::size_t)m_BytePerPixel * (std::size_t)m_Width;

            // read the pixels
            for (std::size_t i = 0; i < m_Height; ++i)
            {
                // move to the next row to read
                pDst -= (std::size_t)m_BytePerPixel * (std::size_t)m_Width;

                // read the row
                buffer.Read(pDst, size);
            }

            // do convert the BGR pixel order to RGB?
            if (m_BytePerPixel >= 3)
                BGRToRGB((unsigned char*)m_pData, (int)m_DataLength, (int)m_BytePerPixel);

            m_ImageType = PixelBuffer::IEImageType::IE_IT_Bitmap;
            m_PixelType = PixelBuffer::IEPixelType::IE_PT_RGB;

            return true;
        }

        case 9:
        {
            // validate the color map entry size
            if (header.m_CMapEntrySize != 8 && header.m_CMapEntrySize != 24 && header.m_CMapEntrySize != 32)
                return false;

            // get the color map size
            const unsigned cMapSize = header.m_CMapSize[0] + (header.m_CMapSize[1] << 8);

            // get the pixel format
            m_BytePerPixel = header.m_PixelSize / 8;

            // calculate the byte per pixels, and allocate memory for color map
            const std::size_t    bytePerPixel = header.m_CMapEntrySize / 8;
            const std::size_t    cMapLength   = bytePerPixel * cMapSize;
                  unsigned char* pCMap        = new unsigned char[cMapLength];

            // read the color map
            buffer.Read(pCMap, cMapLength);

            // do convert the BGR pixel order to RGB?
            if (bytePerPixel >= 3)
                BGRToRGB(pCMap, (int)bytePerPixel * cMapSize, (int)bytePerPixel);

            // allocate memory for pixels
            m_DataLength = bytePerPixel * m_Width * m_Height;
            m_pData      = new unsigned char[m_DataLength];

            unsigned char* pEnd            = &((unsigned char*)m_pData)[m_DataLength];
            unsigned char* pDst            = pEnd - (bytePerPixel * m_Width);
            unsigned char  dataBuffer[128] = {0};

            // iterate though pixels to read
            for (; pDst >= (unsigned char*)m_pData; )
            {
                int c;

                // read next char
                buffer.Read(&c, 1);

                // compressed pixel?
                if (c & 0x80)
                {
                    int index;

                    // read next char
                    buffer.Read(&index, 1);

                    unsigned char* pCol = &pCMap[index * bytePerPixel];

                    c -= 0x7F;
                    c *= (int)bytePerPixel;

                    while (c > 0 && pDst >= (unsigned char*)m_pData)
                    {
                        const float nF = std::min((float)c, (float)(pEnd - pDst));
                        const int   n  = (int)nF;

                        for (unsigned char* pRun = pDst + n; pDst < pRun; pDst += bytePerPixel)
                            std::memcpy(pDst, pCol, bytePerPixel);

                        c -= n;

                        if (pDst >= pEnd)
                        {
                            pEnd -=        bytePerPixel * m_Width;
                            pDst  = pEnd - bytePerPixel * m_Width;
                        }
                    }
                }
                else
                {
                    c += 1;

                    while (c > 0 && pDst >= (unsigned char*)m_pData)
                    {
                        const float nF = std::min((float)c, (float)(pEnd - pDst) / bytePerPixel);
                        const int   n  = (int)nF;

                        // read the row
                        buffer.Read(&dataBuffer, n);

                        for (unsigned char* pSrc = dataBuffer; pSrc < &dataBuffer[n]; pDst += bytePerPixel)
                            std::memcpy(pDst, &pCMap[*pSrc++ * bytePerPixel], bytePerPixel);

                        c -= n;

                        if (pDst >= pEnd)
                        {
                            pEnd -=        bytePerPixel * m_Width;
                            pDst  = pEnd - bytePerPixel * m_Width;
                        }
                    }
                }
            }

            delete[] pCMap;

            m_ImageType = PixelBuffer::IEImageType::IE_IT_Bitmap;
            m_PixelType = PixelBuffer::IEPixelType::IE_PT_RGB;

            return true;
        }

        case 10:
        {
            // get the byte per pixels
            m_BytePerPixel = header.m_PixelSize / 8;

            // allocate memory for pixels
            m_DataLength = (std::size_t)m_BytePerPixel * (std::size_t)m_Width * (std::size_t)m_Height;
            m_pData      = new unsigned char[m_DataLength];

            unsigned char* pEnd            = &((unsigned char*)m_pData)[m_DataLength];
            unsigned char* pDst            = pEnd - (std::size_t)m_BytePerPixel * (std::size_t)m_Width;
            unsigned char  dataBuffer[128] = {0};

            // iterate though pixels to read
            for (; pDst >= (unsigned char*)m_pData; )
            {
                int c;

                // read next char
                buffer.Read(&c, 1);

                // compressed pixel?
                if (c & 0x80)
                {
                    // read pixel
                    buffer.Read(&dataBuffer, m_BytePerPixel);

                    c -= 0x7F;

                    if (m_BytePerPixel >= 3)
                    {
                        dataBuffer[0] = dataBuffer[0] ^ dataBuffer[2];
                        dataBuffer[2] = dataBuffer[0] ^ dataBuffer[2];
                        dataBuffer[0] = dataBuffer[2] ^ dataBuffer[0];
                    }

                    c *= (int)m_BytePerPixel;

                    while (c > 0)
                    {
                        const float nF = std::min((float)c, (float)(pEnd - pDst));
                        const int   n  = (int)nF;

                        for (unsigned char* pRun = pDst + n; pDst < pRun; pDst += m_BytePerPixel)
                            std::memcpy(pDst, dataBuffer, m_BytePerPixel);

                        c -= n;

                        if (pDst >= pEnd)
                        {
                            pEnd -=        (std::size_t)m_BytePerPixel * (std::size_t)m_Width;
                            pDst  = pEnd - (std::size_t)m_BytePerPixel * (std::size_t)m_Width;

                            if (pDst < (unsigned char*)m_pData)
                                break;
                        }
                    }
                }
                else
                {
                    c += 1;
                    c *= (int)m_BytePerPixel;

                    while (c > 0)
                    {
                        const float nF = std::min((float)c, (float)(pEnd - pDst));
                        const int   n = (int)nF;

                        // read pixel
                        buffer.Read(pDst, n);

                        if (m_BytePerPixel >= 3)
                            BGRToRGB(pDst, n, (int)m_BytePerPixel);

                        pDst += n;
                        c    -= n;

                        if (pDst >= pEnd)
                        {
                            pEnd -=        (std::size_t)m_BytePerPixel * (std::size_t)m_Width;
                            pDst  = pEnd - (std::size_t)m_BytePerPixel * (std::size_t)m_Width;

                            if (pDst < (unsigned char*)m_pData)
                                break;
                        }
                    }
                }
            }

            m_ImageType = PixelBuffer::IEImageType::IE_IT_Bitmap;
            m_PixelType = PixelBuffer::IEPixelType::IE_PT_RGB;

            return true;
        }

        default:
            return false;
    }
}
//---------------------------------------------------------------------------
#ifdef USE_PNG
    bool PixelBuffer::FromPng(const std::string& fileName, bool is32bit)
    {
        // no file name?
        if (fileName.empty())
            return false;

        // open the file
        std::unique_ptr<StdFileBuffer> pFileBuffer(new StdFileBuffer());
        pFileBuffer->Open(fileName, FileBuffer::IEMode::IE_M_Read);
        pFileBuffer->Seek(0, 0);

        return FromPng(*pFileBuffer, is32bit);
    }
#endif
//---------------------------------------------------------------------------
#ifdef USE_PNG
    bool PixelBuffer::FromPng(const std::wstring& fileName, bool is32bit)
    {
        // no file name?
        if (fileName.empty())
            return false;

        // open the file
        std::unique_ptr<StdFileBuffer> pFileBuffer(new StdFileBuffer());
        pFileBuffer->Open(fileName, FileBuffer::IEMode::IE_M_Read);
        pFileBuffer->Seek(0, 0);

        return FromPng(*pFileBuffer, is32bit);
    }
#endif
//------------------------------------------------------------------------------
#ifdef USE_PNG
    bool PixelBuffer::FromPng(Buffer& buffer, bool is32bit)
    {
        png_image image;

        std::memset(&image, 0, (sizeof image));
        image.version = PNG_IMAGE_VERSION;

        const std::size_t    size       = buffer.GetSize();
              unsigned char* pImageData = new unsigned char[size];
              png_bytep      pBuffer    = nullptr;
              bool           result     = false;

        try
        {
            // read png content
            buffer.Read(pImageData, size);

            // open the png image
            if (png_image_begin_read_from_memory(&image, pImageData, size) != 0)
            {
                // set a simple sRGB format with a non-associated alpha channel as png file format to read
                image.format = is32bit ? PNG_FORMAT_RGBA : PNG_FORMAT_RGB;

                // allocate enough memory to hold the image in this format
                pBuffer = new png_byte[(std::size_t)PNG_IMAGE_SIZE(image)];

                // png was read successfully?
                if (pBuffer && png_image_finish_read(&image, nullptr, pBuffer, 0, nullptr) != 0)
                {
                    std::size_t width;
                    std::size_t height;
                    std::size_t format;

                    // get the pixel buffer
                    result = LoadPngData(image, pBuffer, is32bit, width, height, format, m_DataLength, m_pData);

                    m_ImageType    = PixelBuffer::IEImageType::IE_IT_Bitmap;
                    m_PixelType    = is32bit ? PixelBuffer::IEPixelType::IE_PT_RGBA : PixelBuffer::IEPixelType::IE_PT_RGB;
                    m_Width        = (std::uint32_t)width;
                    m_Height       = (std::uint32_t)height;
                    m_BytePerPixel = (std::uint32_t)(format / 8);
                    m_Stride       = ((m_Width * (is32bit ? 4 : 3) + 3) / 4) * 4;
                }
            }
        }
        catch (...)
        {
            delete[] pImageData;
            throw;
        }

        // delete the image
        png_image_free(&image);

        // delete the image buffer
        if (pBuffer)
            delete[] pBuffer;

        // delete the image data
        if (pImageData)
            delete[] pImageData;

        return result;
    }
#endif
//------------------------------------------------------------------------------
#ifdef USE_PNG
    bool PixelBuffer::LoadPngData(const png_image&   image,
                                  const png_bytep    pBuffer,
                                        bool         is32bit,
                                        std::size_t& width,
                                        std::size_t& height,
                                        std::size_t& format,
                                        std::size_t& length,
                                        void*&       pPixels) const
    {
        width   = image.width;
        height  = image.height;
        format  = is32bit ? 32 : 24;
        length  = (std::size_t)PNG_IMAGE_SIZE(image);
        pPixels = nullptr;

        unsigned char* pPixelArray = new unsigned char[length];

        try
        {
            // search for bitmap format
            switch (format)
            {
                case 24:
                {
                    for (unsigned y = 0; y < height; ++y)
                        std::memcpy(&pPixelArray[y * (width * 3)], &pBuffer[((height - 1) - y) * (width * 3)], width * 3);

                    pPixels = pPixelArray;
                    break;
                }

                case 32:
                {
                    for (unsigned y = 0; y < height; ++y)
                        std::memcpy(&pPixelArray[y * (width * 4)], &pBuffer[((height - 1) - y) * (width * 4)], width * 4);

                    pPixels = pPixelArray;
                    break;
                }

                default: throw new std::exception("Unknown format");
            }
        }
        catch (...)
        {
            // clear memory
            delete[](unsigned char*)pPixels;
            throw;
        }

        return true;
    }
#endif
//---------------------------------------------------------------------------
