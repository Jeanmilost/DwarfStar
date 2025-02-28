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

#include "DWF_MDL.h"

// std
#include <stdlib.h>
#include <math.h>
#include <string.h>

// classes
#include "DWF_StdFileBuffer.h"

using namespace DWF_Model;

//---------------------------------------------------------------------------
// Global defines
//---------------------------------------------------------------------------
#define M_MDL_Mesh_File_Version 6
#define M_MDL_ID                (('O' << 24) + ('P' << 16) + ('D' << 8) + 'I')

//---------------------------------------------------------------------------
// Global values
//---------------------------------------------------------------------------
const float g_NormalTable[] =
{
    -0.525731f,  0.000000f,  0.850651f,
    -0.442863f,  0.238856f,  0.864188f,
    -0.295242f,  0.000000f,  0.955423f,
    -0.309017f,  0.500000f,  0.809017f,
    -0.162460f,  0.262866f,  0.951056f,
     0.000000f,  0.000000f,  1.000000f,
     0.000000f,  0.850651f,  0.525731f,
    -0.147621f,  0.716567f,  0.681718f,
     0.147621f,  0.716567f,  0.681718f,
     0.000000f,  0.525731f,  0.850651f,
     0.309017f,  0.500000f,  0.809017f,
     0.525731f,  0.000000f,  0.850651f,
     0.295242f,  0.000000f,  0.955423f,
     0.442863f,  0.238856f,  0.864188f,
     0.162460f,  0.262866f,  0.951056f,
    -0.681718f,  0.147621f,  0.716567f,
    -0.809017f,  0.309017f,  0.500000f,
    -0.587785f,  0.425325f,  0.688191f,
    -0.850651f,  0.525731f,  0.000000f,
    -0.864188f,  0.442863f,  0.238856f,
    -0.716567f,  0.681718f,  0.147621f,
    -0.688191f,  0.587785f,  0.425325f,
    -0.500000f,  0.809017f,  0.309017f,
    -0.238856f,  0.864188f,  0.442863f,
    -0.425325f,  0.688191f,  0.587785f,
    -0.716567f,  0.681718f, -0.147621f,
    -0.500000f,  0.809017f, -0.309017f,
    -0.525731f,  0.850651f,  0.000000f,
     0.000000f,  0.850651f, -0.525731f,
    -0.238856f,  0.864188f, -0.442863f,
     0.000000f,  0.955423f, -0.295242f,
    -0.262866f,  0.951056f, -0.162460f,
     0.000000f,  1.000000f,  0.000000f,
     0.000000f,  0.955423f,  0.295242f,
    -0.262866f,  0.951056f,  0.162460f,
     0.238856f,  0.864188f,  0.442863f,
     0.262866f,  0.951056f,  0.162460f,
     0.500000f,  0.809017f,  0.309017f,
     0.238856f,  0.864188f, -0.442863f,
     0.262866f,  0.951056f, -0.162460f,
     0.500000f,  0.809017f, -0.309017f,
     0.850651f,  0.525731f,  0.000000f,
     0.716567f,  0.681718f,  0.147621f,
     0.716567f,  0.681718f, -0.147621f,
     0.525731f,  0.850651f,  0.000000f,
     0.425325f,  0.688191f,  0.587785f,
     0.864188f,  0.442863f,  0.238856f,
     0.688191f,  0.587785f,  0.425325f,
     0.809017f,  0.309017f,  0.500000f,
     0.681718f,  0.147621f,  0.716567f,
     0.587785f,  0.425325f,  0.688191f,
     0.955423f,  0.295242f,  0.000000f,
     1.000000f,  0.000000f,  0.000000f,
     0.951056f,  0.162460f,  0.262866f,
     0.850651f, -0.525731f,  0.000000f,
     0.955423f, -0.295242f,  0.000000f,
     0.864188f, -0.442863f,  0.238856f,
     0.951056f, -0.162460f,  0.262866f,
     0.809017f, -0.309017f,  0.500000f,
     0.681718f, -0.147621f,  0.716567f,
     0.850651f,  0.000000f,  0.525731f,
     0.864188f,  0.442863f, -0.238856f,
     0.809017f,  0.309017f, -0.500000f,
     0.951056f,  0.162460f, -0.262866f,
     0.525731f,  0.000000f, -0.850651f,
     0.681718f,  0.147621f, -0.716567f,
     0.681718f, -0.147621f, -0.716567f,
     0.850651f,  0.000000f, -0.525731f,
     0.809017f, -0.309017f, -0.500000f,
     0.864188f, -0.442863f, -0.238856f,
     0.951056f, -0.162460f, -0.262866f,
     0.147621f,  0.716567f, -0.681718f,
     0.309017f,  0.500000f, -0.809017f,
     0.425325f,  0.688191f, -0.587785f,
     0.442863f,  0.238856f, -0.864188f,
     0.587785f,  0.425325f, -0.688191f,
     0.688191f,  0.587785f, -0.425325f,
    -0.147621f,  0.716567f, -0.681718f,
    -0.309017f,  0.500000f, -0.809017f,
     0.000000f,  0.525731f, -0.850651f,
    -0.525731f,  0.000000f, -0.850651f,
    -0.442863f,  0.238856f, -0.864188f,
    -0.295242f,  0.000000f, -0.955423f,
    -0.162460f,  0.262866f, -0.951056f,
     0.000000f,  0.000000f, -1.000000f,
     0.295242f,  0.000000f, -0.955423f,
     0.162460f,  0.262866f, -0.951056f,
    -0.442863f, -0.238856f, -0.864188f,
    -0.309017f, -0.500000f, -0.809017f,
    -0.162460f, -0.262866f, -0.951056f,
     0.000000f, -0.850651f, -0.525731f,
    -0.147621f, -0.716567f, -0.681718f,
     0.147621f, -0.716567f, -0.681718f,
     0.000000f, -0.525731f, -0.850651f,
     0.309017f, -0.500000f, -0.809017f,
     0.442863f, -0.238856f, -0.864188f,
     0.162460f, -0.262866f, -0.951056f,
     0.238856f, -0.864188f, -0.442863f,
     0.500000f, -0.809017f, -0.309017f,
     0.425325f, -0.688191f, -0.587785f,
     0.716567f, -0.681718f, -0.147621f,
     0.688191f, -0.587785f, -0.425325f,
     0.587785f, -0.425325f, -0.688191f,
     0.000000f, -0.955423f, -0.295242f,
     0.000000f, -1.000000f,  0.000000f,
     0.262866f, -0.951056f, -0.162460f,
     0.000000f, -0.850651f,  0.525731f,
     0.000000f, -0.955423f,  0.295242f,
     0.238856f, -0.864188f,  0.442863f,
     0.262866f, -0.951056f,  0.162460f,
     0.500000f, -0.809017f,  0.309017f,
     0.716567f, -0.681718f,  0.147621f,
     0.525731f, -0.850651f,  0.000000f,
    -0.238856f, -0.864188f, -0.442863f,
    -0.500000f, -0.809017f, -0.309017f,
    -0.262866f, -0.951056f, -0.162460f,
    -0.850651f, -0.525731f,  0.000000f,
    -0.716567f, -0.681718f, -0.147621f,
    -0.716567f, -0.681718f,  0.147621f,
    -0.525731f, -0.850651f,  0.000000f,
    -0.500000f, -0.809017f,  0.309017f,
    -0.238856f, -0.864188f,  0.442863f,
    -0.262866f, -0.951056f,  0.162460f,
    -0.864188f, -0.442863f,  0.238856f,
    -0.809017f, -0.309017f,  0.500000f,
    -0.688191f, -0.587785f,  0.425325f,
    -0.681718f, -0.147621f,  0.716567f,
    -0.442863f, -0.238856f,  0.864188f,
    -0.587785f, -0.425325f,  0.688191f,
    -0.309017f, -0.500000f,  0.809017f,
    -0.147621f, -0.716567f,  0.681718f,
    -0.425325f, -0.688191f,  0.587785f,
    -0.162460f, -0.262866f,  0.951056f,
     0.442863f, -0.238856f,  0.864188f,
     0.162460f, -0.262866f,  0.951056f,
     0.309017f, -0.500000f,  0.809017f,
     0.147621f, -0.716567f,  0.681718f,
     0.000000f, -0.525731f,  0.850651f,
     0.425325f, -0.688191f,  0.587785f,
     0.587785f, -0.425325f,  0.688191f,
     0.688191f, -0.587785f,  0.425325f,
    -0.955423f,  0.295242f,  0.000000f,
    -0.951056f,  0.162460f,  0.262866f,
    -1.000000f,  0.000000f,  0.000000f,
    -0.850651f,  0.000000f,  0.525731f,
    -0.955423f, -0.295242f,  0.000000f,
    -0.951056f, -0.162460f,  0.262866f,
    -0.864188f,  0.442863f, -0.238856f,
    -0.951056f,  0.162460f, -0.262866f,
    -0.809017f,  0.309017f, -0.500000f,
    -0.864188f, -0.442863f, -0.238856f,
    -0.951056f, -0.162460f, -0.262866f,
    -0.809017f, -0.309017f, -0.500000f,
    -0.681718f,  0.147621f, -0.716567f,
    -0.681718f, -0.147621f, -0.716567f,
    -0.850651f,  0.000000f, -0.525731f,
    -0.688191f,  0.587785f, -0.425325f,
    -0.587785f,  0.425325f, -0.688191f,
    -0.425325f,  0.688191f, -0.587785f,
    -0.425325f, -0.688191f, -0.587785f,
    -0.587785f, -0.425325f, -0.688191f,
    -0.688191f, -0.587785f, -0.425325f
};
//---------------------------------------------------------------------------
const unsigned char g_ColorTable[] =
{
    0,   0,   0,   15,  15,  15,  31,  31,  31,
    47,  47,  47,  63,  63,  63,  75,  75,  75,
    91,  91,  91,  107, 107, 107, 123, 123, 123,
    139, 139, 139, 155, 155, 155, 171, 171, 171,
    187, 187, 187, 203, 203, 203, 219, 219, 219,
    235, 235, 235, 15,  11,  7,   23,  15,  11,
    31,  23,  11,  39,  27,  15,  47,  35,  19,
    55,  43,  23,  63,  47,  23,  75,  55,  27,
    83,  59,  27,  91,  67,  31,  99,  75,  31,
    107, 83,  31,  115, 87,  31,  123, 95,  35,
    131, 103, 35,  143, 111, 35,  11,  11,  15,
    19,  19,  27,  27,  27,  39,  39,  39,  51,
    47,  47,  63,  55,  55,  75,  63,  63,  87,
    71,  71,  103, 79,  79,  115, 91,  91,  127,
    99,  99,  139, 107, 107, 151, 115, 115, 163,
    123, 123, 175, 131, 131, 187, 139, 139, 203,
    0,   0,   0,   7,   7,   0,   11,  11,  0,
    19,  19,  0,   27,  27,  0,   35,  35,  0,
    43,  43,  7,   47,  47,  7,   55,  55,  7,
    63,  63,  7,   71,  71,  7,   75,  75,  11,
    83,  83,  11,  91,  91,  11,  99,  99,  11,
    107, 107, 15,  7,   0,   0,   15,  0,   0,
    23,  0,   0,   31,  0,   0,   39,  0,   0,
    47,  0,   0,   55,  0,   0,   63,  0,   0,
    71,  0,   0,   79,  0,   0,   87,  0,   0,
    95,  0,   0,   103, 0,   0,   111, 0,   0,
    119, 0,   0,   127, 0,   0,   19,  19,  0,
    27,  27,  0,   35,  35,  0,   47,  43,  0,
    55,  47,  0,   67,  55,  0,   75,  59,  7,
    87,  67,  7,   95,  71,  7,   107, 75,  11,
    119, 83,  15,  131, 87,  19,  139, 91,  19,
    151, 95,  27,  163, 99,  31,  175, 103, 35,
    35,  19,  7,   47,  23,  11,  59,  31,  15,
    75,  35,  19,  87,  43,  23,  99,  47,  31,
    115, 55,  35,  127, 59,  43,  143, 67,  51,
    159, 79,  51,  175, 99,  47,  191, 119, 47,
    207, 143, 43,  223, 171, 39,  239, 203, 31,
    255, 243, 27,  11,  7,   0,   27,  19,  0,
    43,  35,  15,  55,  43,  19,  71,  51,  27,
    83,  55,  35,  99,  63,  43,  111, 71,  51,
    127, 83,  63,  139, 95,  71,  155, 107, 83,
    167, 123, 95,  183, 135, 107, 195, 147, 123,
    211, 163, 139, 227, 179, 151, 171, 139, 163,
    159, 127, 151, 147, 115, 135, 139, 103, 123,
    127, 91,  111, 119, 83,  99,  107, 75,  87,
    95,  63,  75,  87,  55,  67,  75,  47,  55,
    67,  39,  47,  55,  31,  35,  43,  23,  27,
    35,  19,  19,  23,  11,  11,  15,  7,   7,
    187, 115, 159, 175, 107, 143, 163, 95,  131,
    151, 87,  119, 139, 79,  107, 127, 75,  95,
    115, 67,  83,  107, 59,  75,  95,  51,  63,
    83,  43,  55,  71,  35,  43,  59,  31,  35,
    47,  23,  27,  35,  19,  19,  23,  11,  11,
    15,  7,   7,   219, 195, 187, 203, 179, 167,
    191, 163, 155, 175, 151, 139, 163, 135, 123,
    151, 123, 111, 135, 111, 95,  123, 99,  83,
    107, 87,  71,  95,  75,  59,  83,  63,  51,
    67,  51,  39,  55,  43,  31,  39,  31,  23,
    27,  19,  15,  15,  11,  7,   111, 131, 123,
    103, 123, 111, 95,  115, 103, 87,  107, 95,
    79,  99,  87,  71,  91,  79,  63,  83,  71,
    55,  75,  63,  47,  67,  55,  43,  59,  47,
    35,  51,  39,  31,  43,  31,  23,  35,  23,
    15,  27,  19,  11,  19,  11,  7,   11,  7,
    255, 243, 27,  239, 223, 23,  219, 203, 19,
    203, 183, 15,  187, 167, 15,  171, 151, 11,
    155, 131, 7,   139, 115, 7,   123, 99,  7,
    107, 83,  0,   91,  71,  0,   75,  55,  0,
    59,  43,  0,   43,  31,  0,   27,  15,  0,
    11,  7,   0,   0,   0,   255, 11,  11,  239,
    19,  19,  223, 27,  27,  207, 35,  35,  191,
    43,  43,  175, 47,  47,  159, 47,  47,  143,
    47,  47,  127, 47,  47,  111, 47,  47,  95,
    43,  43,  79,  35,  35,  63,  27,  27,  47,
    19,  19,  31,  11,  11,  15,  43,  0,   0,
    59,  0,   0,   75,  7,   0,   95,  7,   0,
    111, 15,  0,   127, 23,  7,   147, 31,  7,
    163, 39,  11,  183, 51,  15,  195, 75,  27,
    207, 99,  43,  219, 127, 59,  227, 151, 79,
    231, 171, 95,  239, 191, 119, 247, 211, 139,
    167, 123, 59,  183, 155, 55,  199, 195, 55,
    231, 227, 87,  127, 191, 255, 171, 231, 255,
    215, 255, 255, 103, 0,   0,   139, 0,   0,
    179, 0,   0,   215, 0,   0,   255, 0,   0,
    255, 243, 147, 255, 247, 199, 255, 255, 255,
    159, 91,  83
};

//---------------------------------------------------------------------------
// MDL::IHeader
//---------------------------------------------------------------------------
MDL::IHeader::IHeader()
{}
//---------------------------------------------------------------------------
MDL::IHeader::~IHeader()
{}
//---------------------------------------------------------------------------
bool MDL::IHeader::IHeader::Read(DWF_Buffer::Buffer& buffer)
{
    bool success = true;

    // read header from buffer
    success = success && buffer.Read(&m_ID,             sizeof(m_ID));
    success = success && buffer.Read(&m_Version,        sizeof(m_Version));
    success = success && buffer.Read(&m_Scale,          sizeof(m_Scale));
    success = success && buffer.Read(&m_Translate,      sizeof(m_Translate));
    success = success && buffer.Read(&m_BoundingRadius, sizeof(m_BoundingRadius));
    success = success && buffer.Read(&m_EyePosition,    sizeof(m_EyePosition));
    success = success && buffer.Read(&m_SkinCount,      sizeof(m_SkinCount));
    success = success && buffer.Read(&m_SkinWidth,      sizeof(m_SkinWidth));
    success = success && buffer.Read(&m_SkinHeight,     sizeof(m_SkinHeight));
    success = success && buffer.Read(&m_VertexCount,    sizeof(m_VertexCount));
    success = success && buffer.Read(&m_PolygonCount,   sizeof(m_PolygonCount));
    success = success && buffer.Read(&m_FrameCount,     sizeof(m_FrameCount));
    success = success && buffer.Read(&m_SyncType,       sizeof(m_SyncType));
    success = success && buffer.Read(&m_Flags,          sizeof(m_Flags));
    success = success && buffer.Read(&m_Size,           sizeof(m_Size));

    #ifdef CONVERT_ENDIANNESS
        // the read bytes are inverted and should be swapped if the target system is big endian
        if (success && GetEndianness() == IEEndianness::IE_E_BigEndian)
        {
            // swap the read values in the memory (thus 0xAABBCCDD will become 0xDDCCBBAA)
            SwapMemory(&m_ID,             sizeof(m_ID));
            SwapMemory(&m_Version,        sizeof(m_Version));
            SwapMemory(&m_Scale[0],       sizeof(m_Scale[0]));
            SwapMemory(&m_Scale[1],       sizeof(m_Scale[1]));
            SwapMemory(&m_Scale[2],       sizeof(m_Scale[2]));
            SwapMemory(&m_Translate[0],   sizeof(m_Translate[0]));
            SwapMemory(&m_Translate[1],   sizeof(m_Translate[1]));
            SwapMemory(&m_Translate[2],   sizeof(m_Translate[2]));
            SwapMemory(&m_BoundingRadius, sizeof(m_BoundingRadius));
            SwapMemory(&m_EyePosition[0], sizeof(m_EyePosition[0]));
            SwapMemory(&m_EyePosition[1], sizeof(m_EyePosition[1]));
            SwapMemory(&m_EyePosition[2], sizeof(m_EyePosition[2]));
            SwapMemory(&m_SkinCount,      sizeof(m_SkinCount));
            SwapMemory(&m_SkinWidth,      sizeof(m_SkinWidth));
            SwapMemory(&m_SkinHeight,     sizeof(m_SkinHeight));
            SwapMemory(&m_VertexCount,    sizeof(m_VertexCount));
            SwapMemory(&m_PolygonCount,   sizeof(m_PolygonCount));
            SwapMemory(&m_FrameCount,     sizeof(m_FrameCount));
            SwapMemory(&m_SyncType,       sizeof(m_SyncType));
            SwapMemory(&m_Flags,          sizeof(m_Flags));
            SwapMemory(&m_Size,           sizeof(m_Size));
        }
    #endif

    return success;
}
//---------------------------------------------------------------------------
// MDL::ISkin
//---------------------------------------------------------------------------
MDL::ISkin::ISkin()
{}
//---------------------------------------------------------------------------
MDL::ISkin::~ISkin()
{
    if (m_pData)
        delete[] m_pData;

    if (m_pTime)
        delete[] m_pTime;
}
//---------------------------------------------------------------------------
bool MDL::ISkin::Read(const IHeader& header, DWF_Buffer::Buffer& buffer)
{
    // calculate texture size
    m_TexLen = header.m_SkinWidth * header.m_SkinHeight;

    // read the skin group flag
    if (!buffer.Read(&m_Group, sizeof(m_Group)))
        return false;

    #ifdef CONVERT_ENDIANNESS
        // the read bytes are inverted and should be swapped if the target system is big endian
        if (GetEndianness() == IEEndianness::IE_E_BigEndian)
            // swap the read value in the memory (thus 0xAABBCCDD will become 0xDDCCBBAA)
            SwapMemory(&m_Group, sizeof(m_Group));
    #endif

    m_pTime = 0;

    // is a group of textures?
    if (!m_Group)
    {
        m_Count = 1;

        // create memory for texture
        m_pData = new unsigned char[m_TexLen];

        // read texture from buffer. NOTE 8 bit array, same in all endianness
        return buffer.Read(m_pData, m_TexLen);
    }

    // read the skin count
    if (!buffer.Read(&m_Count, sizeof(m_Count)))
        return false;

    #ifdef CONVERT_ENDIANNESS
        // the read bytes are inverted and should be swapped if the target system is big endian
        if (GetEndianness() == IEEndianness::IE_E_BigEndian)
            // swap the read value in the memory (thus 0xAABBCCDD will become 0xDDCCBBAA)
            SwapMemory(&m_Count, sizeof(m_Count));
    #endif

    // no skin to read?
    if (!m_Count)
        return true;

    // create memory for time table
    m_pTime = new float[m_Count];

    // read time table from buffer
    if (!buffer.Read(m_pTime, m_Count * sizeof(float)))
        return 0;

    #ifdef CONVERT_ENDIANNESS
        // the read bytes are inverted and should be swapped if the target system is big endian
        if (GetEndianness() == IEEndianness::IE_E_BigEndian)
            // iterate through time values to swap
            for (std::size_t i = 0; i < m_Count; ++i)
                // swap the value in the memory (thus 0xAABBCCDD will become 0xDDCCBBAA)
                SwapMemory(&m_pTime[i], sizeof(float));
    #endif

    const std::size_t dataSize = (std::size_t)m_TexLen * (std::size_t)m_Count;

    // create memory for texture
    m_pData = new unsigned char[dataSize];

    // read texture from buffer. NOTE 8 bit array, same in all endianness
    return buffer.Read(m_pData, dataSize);
}
//---------------------------------------------------------------------------
// MDL::ITextureCoord
//---------------------------------------------------------------------------
MDL::ITextureCoord::ITextureCoord()
{}
//---------------------------------------------------------------------------
MDL::ITextureCoord::~ITextureCoord()
{}
//---------------------------------------------------------------------------
bool MDL::ITextureCoord::Read(DWF_Buffer::Buffer& buffer)
{
    bool success = true;

    // read texture coordinates from buffer
    success = success && buffer.Read(&m_OnSeam, sizeof(m_OnSeam));
    success = success && buffer.Read(&m_U,      sizeof(m_U));
    success = success && buffer.Read(&m_V,      sizeof(m_V));

    #ifdef CONVERT_ENDIANNESS
        // the read bytes are inverted and should be swapped if the target system is big endian
        if (success && GetEndianness() == IEEndianness::IE_E_BigEndian)
        {
            // swap the read values in the memory (thus 0xAABBCCDD will become 0xDDCCBBAA)
            SwapMemory(&m_OnSeam, sizeof(m_OnSeam));
            SwapMemory(&m_U,      sizeof(m_U));
            SwapMemory(&m_V,      sizeof(m_V));
        }
    #endif

    return success;
}
//---------------------------------------------------------------------------
// MDL::IPolygon
//---------------------------------------------------------------------------
MDL::IPolygon::IPolygon()
{}
//---------------------------------------------------------------------------
MDL::IPolygon::~IPolygon()
{}
//---------------------------------------------------------------------------
bool MDL::IPolygon::Read(DWF_Buffer::Buffer& buffer)
{
    bool success = true;

    // read polygon from buffer
    success = success && buffer.Read(&m_FacesFront,  sizeof(m_FacesFront));
    success = success && buffer.Read(&m_VertexIndex, sizeof(m_VertexIndex));

    #ifdef CONVERT_ENDIANNESS
        // the read bytes are inverted and should be swapped if the target system is big endian
        if (success && GetEndianness() == IEEndianness::IE_E_BigEndian)
        {
            // swap the read values in the memory (thus 0xAABBCCDD will become 0xDDCCBBAA)
            SwapMemory(&m_FacesFront,     sizeof(m_FacesFront));
            SwapMemory(&m_VertexIndex[0], sizeof(m_VertexIndex[0]));
            SwapMemory(&m_VertexIndex[1], sizeof(m_VertexIndex[1]));
            SwapMemory(&m_VertexIndex[2], sizeof(m_VertexIndex[2]));
        }
    #endif

    return success;
}
//---------------------------------------------------------------------------
// MDL::IVertex
//---------------------------------------------------------------------------
MDL::IVertex::IVertex()
{}
//---------------------------------------------------------------------------
MDL::IVertex::~IVertex()
{}
//---------------------------------------------------------------------------
bool MDL::IVertex::Read(DWF_Buffer::Buffer& buffer)
{
    bool success = true;

    // read vertex from buffer. NOTE 8 bit values, same in all endianness
    success = success && buffer.Read(&m_Vertex,      sizeof(m_Vertex));
    success = success && buffer.Read(&m_NormalIndex, sizeof(m_NormalIndex));

    return success;
}
//---------------------------------------------------------------------------
// MDL::IFrame
//---------------------------------------------------------------------------
MDL::IFrame::IFrame()
{}
//---------------------------------------------------------------------------
MDL::IFrame::~IFrame()
{
    if (m_pVertex)
        delete[] m_pVertex;
}
//---------------------------------------------------------------------------
bool MDL::IFrame::Read(const IHeader& header, DWF_Buffer::Buffer& buffer)
{
    bool success = true;

    // read frame bounding box
    success = success && m_BoundingBoxMin.Read(buffer);
    success = success && m_BoundingBoxMax.Read(buffer);

    // succeeded?
    if (!success)
        return false;

    // read frame name. NOTE 8 bit array, same in all endianness
    if (!buffer.Read(&m_Name, sizeof(m_Name)))
        return false;

    // create frame vertex buffer
    m_pVertex = new IVertex[header.m_VertexCount];

    // read frame vertices
    for (std::size_t i = 0; i < header.m_VertexCount; ++i)
        if (!m_pVertex[i].Read(buffer))
            return false;

    return true;
}
//---------------------------------------------------------------------------
// MDL::IFrameGroup
//---------------------------------------------------------------------------
MDL::IFrameGroup::IFrameGroup()
{}
//---------------------------------------------------------------------------
MDL::IFrameGroup::~IFrameGroup()
{
    if (m_pFrame)
        delete[] m_pFrame;

    if (m_pTime)
        delete[] m_pTime;
}
//---------------------------------------------------------------------------
bool MDL::IFrameGroup::Read(const IHeader& header, DWF_Buffer::Buffer& buffer)
{
    // read the group type
    if (!buffer.Read(&m_Type, sizeof(m_Type)))
        return false;

    #ifdef CONVERT_ENDIANNESS
        // the read bytes are inverted and should be swapped if the target system is big endian
        if (GetEndianness() == IEEndianness::IE_E_BigEndian)
            // swap the read value in the memory (thus 0xAABBCCDD will become 0xDDCCBBAA)
            SwapMemory(&m_Type, sizeof(m_Type));
    #endif

    // is a single frame or a group of frames?
    if (!m_Type)
    {
        m_Count = 1;

        // create frame and time buffers
        m_pFrame = new IFrame[m_Count];
        m_pTime  = new float [m_Count];

        // succeeded?
        if (!m_pFrame || !m_pTime)
            return false;

        // read the frame
        if (!m_pFrame[0].Read(header, buffer))
            return false;

        // for 1 frame there is no time
        m_pTime[0] = 0.0f;

        // get the group bounding box (for 1 frame, the group has the same box as the frame)
        m_BoundingBoxMin = m_pFrame[0].m_BoundingBoxMin;
        m_BoundingBoxMax = m_pFrame[0].m_BoundingBoxMax;

        return true;
    }

    // frame group count from buffer
    if (!buffer.Read(&m_Count, sizeof(m_Count)))
        return false;

    #ifdef CONVERT_ENDIANNESS
        // the read bytes are inverted and should be swapped if the target system is big endian
        if (GetEndianness() == IEEndianness::IE_E_BigEndian)
            // swap the value in the memory (thus 0xAABBCCDD will become 0xDDCCBBAA)
            SwapMemory(&m_Count, sizeof(m_Count));
    #endif

    // read the group bounding box min frame
    if (!m_BoundingBoxMin.Read(buffer))
        return false;

    // read the group bounding box max frame
    if (!m_BoundingBoxMax.Read(buffer))
        return false;

    // create frame and time buffers
    m_pFrame = new IFrame[m_Count];
    m_pTime  = new float [m_Count];

    // read the time table from buffer
    if (!buffer.Read(m_pTime, m_Count * sizeof(float)))
        return false;

    #ifdef CONVERT_ENDIANNESS
        // the read bytes are inverted and should be swapped if the target system is big endian
        if (GetEndianness() == IEEndianness::IE_E_BigEndian)
            // iterate through time values to swap
            for (std::size_t i = 0; i < m_Count; ++i)
                // swap the value in the memory (thus 0xAABBCCDD will become 0xDDCCBBAA)
                SwapMemory(&m_pTime[i], sizeof(float));
    #endif

    // read the frames
    for (std::size_t i = 0; i < m_Count; ++i)
        if (!m_pFrame[i].Read(header, buffer))
            return false;

    return true;
}
//---------------------------------------------------------------------------
// MDL::IAnimation
//---------------------------------------------------------------------------
MDL::IAnimation::IAnimation()
{}
//---------------------------------------------------------------------------
MDL::IAnimation::~IAnimation()
{}
//---------------------------------------------------------------------------
// MDL
//---------------------------------------------------------------------------
MDL::MDL()
{
    // configure the default vertex format
    m_VertFormatTemplate.m_Format = (VertexFormat::IEFormat)((unsigned)VertexFormat::IEFormat::IE_VF_Colors |
                                                             (unsigned)VertexFormat::IEFormat::IE_VF_TexCoords);
    m_VertFormatTemplate.m_Type   =  VertexFormat::IEType::IE_VT_Triangles;

    // configure the default vertex culling
    m_VertCullingTemplate.m_Type = VertexCulling::IECullingType::IE_CT_Back;
    m_VertCullingTemplate.m_Face = VertexCulling::IECullingFace::IE_CF_CW;

    // configure the default material
    m_MaterialTemplate.m_Color = ColorF(1.0f, 1.0f, 1.0f, 1.0f);
}
//---------------------------------------------------------------------------
MDL::~MDL()
{
    // cached model?
    if (m_pCachedModel.get())
    {
        // remove the references to textures, otherwise they will be wrongly deleted with the cached model
        for (std::size_t i = 0; i < m_pCachedModel->m_Mesh.size(); ++i)
            for (std::size_t j = 0; j < m_pCachedModel->m_Mesh[i]->m_VB.size(); ++j)
                m_pCachedModel->m_Mesh[i]->m_VB[j]->m_Material.m_pTexture = nullptr;

        // delete the cached model
        m_pCachedModel.reset();
    }

    const std::size_t modelCount = m_Models.size();

    for (std::size_t i = 0; i < modelCount; ++i)
        delete m_Models[i];

    const std::size_t animFrameCount = m_Animations.size();

    for (std::size_t i = 0; i < animFrameCount; ++i)
        delete m_Animations[i];

    const std::size_t textureCount = m_Textures.size();

    for (std::size_t i = 0; i < textureCount; ++i)
        delete m_Textures[i];
}
//---------------------------------------------------------------------------
void MDL::Clear()
{
    // cached model?
    if (m_pCachedModel.get())
    {
        // remove the references to textures, otherwise they will be wrongly deleted with the cached model
        for (std::size_t i = 0; i < m_pCachedModel->m_Mesh.size(); ++i)
            for (std::size_t j = 0; j < m_pCachedModel->m_Mesh[i]->m_VB.size(); ++j)
                m_pCachedModel->m_Mesh[i]->m_VB[j]->m_Material.m_pTexture = nullptr;

        // delete the cached model
        m_pCachedModel.reset();
    }

    const std::size_t modelCount = m_Models.size();

    for (std::size_t i = 0; i < modelCount; ++i)
        delete m_Models[i];

    m_Models.clear();

    const std::size_t animFrameCount = m_Animations.size();

    for (std::size_t i = 0; i < animFrameCount; ++i)
        delete m_Animations[i];

    m_Animations.clear();

    const std::size_t textureCount = m_Textures.size();

    for (std::size_t i = 0; i < textureCount; ++i)
        delete m_Textures[i];

    m_Textures.clear();
}
//---------------------------------------------------------------------------
bool MDL::Open(const std::string& fileName)
{
    // clear the previous model, if exists
    Clear();

    // no file name?
    if (fileName.empty())
        return false;

    DWF_Buffer::StdFileBuffer fileBuffer;

    // open the file
    if (!fileBuffer.Open(fileName, DWF_Buffer::FileBuffer::IEMode::IE_M_Read))
        return false;

    // seek to start
    fileBuffer.Seek(0, 0);

    // read the content
    return Read(fileBuffer);
}
//---------------------------------------------------------------------------
bool MDL::Open(const std::wstring& fileName)
{
    // clear the previous model, if exists
    Clear();

    // no file name?
    if (fileName.empty())
        return false;

    DWF_Buffer::StdFileBuffer fileBuffer;

    // open the file
    if (!fileBuffer.Open(fileName, DWF_Buffer::FileBuffer::IEMode::IE_M_Read))
        return false;

    // seek to start
    fileBuffer.Seek(0, 0);

    // read the content
    return Read(fileBuffer);
}
//---------------------------------------------------------------------------
bool MDL::Open(DWF_Buffer::Buffer& buffer)
{
    // clear the previous model, if exists
    Clear();

    // read the buffer content
    return Read(buffer);
}
//---------------------------------------------------------------------------
Model* MDL::GetModel(std::size_t  fps,
                     std::size_t  animationIndex,
                     std::size_t& textureIndex,
                     std::size_t& modelIndex,
                     double&      textureLastTime,
                     double&      modelLastTime,
                     double       elapsedTime) const
{
    // previous cached model?
    if (m_pCachedModel.get())
    {
        // remove the references to textures, otherwise they will be wrongly deleted with the cached model
        for (std::size_t i = 0; i < m_pCachedModel->m_Mesh.size(); ++i)
            for (std::size_t j = 0; j < m_pCachedModel->m_Mesh[i]->m_VB.size(); ++j)
                m_pCachedModel->m_Mesh[i]->m_VB[j]->m_Material.m_pTexture = nullptr;

        // force the cached model to be deleted (bypass the const statement)
        const_cast<std::unique_ptr<Model>&>(m_pCachedModel).reset();
    }

    // are textures animated?
    if (m_Textures.size() > 1)
    {
        // apply the elapsed time
        textureLastTime += elapsedTime;

        // certify that the skin index is inside the limits
        textureIndex = (textureIndex % m_Textures.size());

        // do get the next skin?
        if ((double)m_TextureTimes[textureIndex] > 0.0)
            while (textureLastTime >= ((double)m_TextureTimes[textureIndex]))
            {
                // decrease the counted time
                textureLastTime -= (double)m_TextureTimes[textureIndex];

                // go to next index
                textureIndex = ((textureIndex + 1) % m_Textures.size());
            }
    }

    // no fps?
    if (!fps)
    {
        // reset all values
        textureIndex    = 0;
        modelIndex      = 0;
        textureLastTime = 0.0;
        modelLastTime   = 0.0;

        return nullptr;
    }

    // calculate the running animation length
    std::size_t animLength = m_Animations[animationIndex]->m_End - m_Animations[animationIndex]->m_Start;

    // is animation empty?
    if (!animLength)
        // animation length should contain at least 1 frame
        animLength = 1;

    // apply the elapsed time
    modelLastTime += elapsedTime;

    // calculate the frame interval
    const double interval = 1.0 / (double)fps;

    // calculate the model animation index, and certify that is it inside the limits
    std::size_t animIndex = ((modelIndex - m_Animations[animationIndex]->m_Start) % animLength);

    // do get the next model?
    while (modelLastTime >= interval)
    {
        // decrease the counted time
        modelLastTime -= interval;

        // go to next index
        animIndex = ((animIndex + 1) % animLength);
    }

    const std::size_t nextModelIndex = m_Animations[animationIndex]->m_Start + animIndex;

    // current and next model mesh count should match, otherwise it's an error
    if (m_Models[modelIndex]->m_Mesh.size() != m_Models[nextModelIndex]->m_Mesh.size())
    {
        // reset all values
        textureIndex    = 0;
        modelIndex      = 0;
        textureLastTime = 0.0;
        modelLastTime   = 0.0;

        return nullptr;
    }

    // force the cached model to be created (bypass the const statement)
    const_cast<std::unique_ptr<Model>&>(m_pCachedModel).reset(new Model());

    // iterate through model meshes
    for (std::size_t i = 0; i < m_Models[modelIndex]->m_Mesh.size(); ++i)
    {
        // current and next vertex buffer count should match, otherwise it's an error
        if (m_Models[modelIndex]->m_Mesh[i]->m_VB.size() != m_Models[nextModelIndex]->m_Mesh[i]->m_VB.size())
        {
            // reset all values
            textureIndex    = 0;
            modelIndex      = 0;
            textureLastTime = 0.0;
            modelLastTime   = 0.0;

            return nullptr;
        }

        // add a new mesh in the cached model
        m_pCachedModel->m_Mesh.push_back(new Mesh());

        // iterate through vertex buffers
        for (std::size_t j = 0; j < m_Models[modelIndex]->m_Mesh[i]->m_VB.size(); ++j)
        {
            // add a new vertex buffer in the mesh
            m_pCachedModel->m_Mesh[i]->m_VB.push_back(new VertexBuffer());

            // copy the format, culling and material, and set the texture to render
            m_pCachedModel->m_Mesh[i]->m_VB[j]->m_Format              = m_Models[modelIndex]->m_Mesh[i]->m_VB[j]->m_Format;
            m_pCachedModel->m_Mesh[i]->m_VB[j]->m_Culling             = m_Models[modelIndex]->m_Mesh[i]->m_VB[j]->m_Culling;
            m_pCachedModel->m_Mesh[i]->m_VB[j]->m_Material            = m_Models[modelIndex]->m_Mesh[i]->m_VB[j]->m_Material;
            m_pCachedModel->m_Mesh[i]->m_VB[j]->m_Material.m_pTexture = m_Textures[textureIndex];

            // iterate through vertices
            for (std::size_t k = 0; k < m_Models[modelIndex]->m_Mesh[i]->m_VB[j]->m_Data.size(); ++k)
            {
                // get the current and next vertex data
                const float curData  = m_Models[modelIndex]->m_Mesh[i]->m_VB[j]->m_Data[k];
                const float nextData = m_Models[nextModelIndex]->m_Mesh[i]->m_VB[j]->m_Data[k];

                // interpolate the data
                m_pCachedModel->m_Mesh[i]->m_VB[j]->m_Data.push_back(curData + ((nextData - curData) * (float)(modelLastTime / interval)));
            }
        }
    }

    modelIndex = nextModelIndex;

    return m_pCachedModel.get();
}
//---------------------------------------------------------------------------
void MDL::SetVertFormatTemplate(const VertexFormat& vertFormatTemplate)
{
    m_VertFormatTemplate = vertFormatTemplate;
}
//---------------------------------------------------------------------------
void MDL::SetVertCullingTemplate(const VertexCulling& vertCullingTemplate)
{
    m_VertCullingTemplate = vertCullingTemplate;
}
//---------------------------------------------------------------------------
void MDL::SetMaterial(const Material& materialTemplate)
{
    m_MaterialTemplate = materialTemplate;
}
//---------------------------------------------------------------------------
void MDL::Set_OnGetVertexColor(VertexBuffer::ITfOnGetVertexColor fOnGetVertexColor)
{
    m_fOnGetVertexColor = fOnGetVertexColor;
}
//---------------------------------------------------------------------------
void MDL::Set_OnCreateTexture(ITfOnCreateTexture fOnCreateTexture)
{
    m_fOnCreateTexture = fOnCreateTexture;
}
//---------------------------------------------------------------------------
bool MDL::Read(DWF_Buffer::Buffer& buffer)
{
    IHeader header;

    // read file header
    if (!header.Read(buffer))
        return false;

    // is mdl file and version correct?
    if ((header.m_ID != M_MDL_ID) || ((float)header.m_Version != M_MDL_Mesh_File_Version))
    {
        Clear();
        return false;
    }

    ISkins skins;

    // read skins
    if (header.m_SkinCount)
    {
        skins.resize(header.m_SkinCount);

        for (std::size_t i = 0; i < header.m_SkinCount; ++i)
            if (!skins[i].Read(header, buffer))
            {
                Clear();
                return false;
            }
    }

    ITextureCoords texCoords;

    // read texture coordinates
    if (header.m_VertexCount)
    {
        texCoords.resize(header.m_VertexCount);

        for (std::size_t i = 0; i < header.m_VertexCount; ++i)
            if (!texCoords[i].Read(buffer))
            {
                Clear();
                return false;
            }
    }

    IPolygons polygons;

    // read polygons
    if (header.m_PolygonCount)
    {
        polygons.resize(header.m_PolygonCount);

        for (std::size_t i = 0; i < header.m_PolygonCount; ++i)
            if (!polygons[i].Read(buffer))
            {
                Clear();
                return false;
            }
    }

    IFrameGroups frameGroups;

    // read frames
    if (header.m_FrameCount)
    {
        frameGroups.resize(header.m_FrameCount);

        for (std::size_t i = 0; i < header.m_FrameCount; ++i)
            if (!frameGroups[i].Read(header, buffer))
            {
                Clear();
                return false;
            }
    }

    // do generate skins?
    if (skins.size() && ((std::size_t)m_VertFormatTemplate.m_Format & (std::size_t)VertexFormat::IEFormat::IE_VF_TexCoords))
    {
        double lastKnownTime = 0.0f;

        // iterate through textures to extract
        for (std::size_t i = 0; i < skins.size(); ++i)
        {
            // extract texture from model
            std::unique_ptr<DWF_Buffer::PixelBuffer> pTexture(UncompressTexture(skins[i],
                                                                                header.m_SkinWidth,
                                                                                header.m_SkinHeight,
                                                                                i));

            // is a default texture?
            if (pTexture->m_DataLength <= 48)
            {
                // cleanup the texture data, if any
                delete pTexture->m_pData;
                pTexture->m_pData = nullptr;

                // recreate a 4 * 4 * 3 pixel buffer
                pTexture->m_DataLength = 48;
                pTexture->m_pData      = new unsigned char[pTexture->m_DataLength];

                // initialize the buffer
                for (std::size_t j = 0; j < 16; ++j)
                {
                    // set color data
                    ((unsigned char*)pTexture->m_pData)[ j * 3]      = (unsigned char)(m_MaterialTemplate.m_Color.m_R * 255.0f);
                    ((unsigned char*)pTexture->m_pData)[(j * 3) + 1] = (unsigned char)(m_MaterialTemplate.m_Color.m_G * 255.0f);
                    ((unsigned char*)pTexture->m_pData)[(j * 3) + 2] = (unsigned char)(m_MaterialTemplate.m_Color.m_B * 255.0f);
                }
            }

            // notify that a texture should be created for the skin
            if (m_fOnCreateTexture)
                m_Textures.push_back(m_fOnCreateTexture(pTexture.get()));

            // also get the animation time
            if (skins[i].m_pTime)
            {
                double time = *(skins[i].m_pTime);
                m_TextureTimes.push_back(time - lastKnownTime);
                lastKnownTime = time;
            }
            else
                m_TextureTimes.push_back(0.0f);
        }
    }

          char        prevSkinName[16];
          char        skinName[16];
    const std::size_t prevSkinNameLength = sizeof(prevSkinName);
    const std::size_t skinNameLength     = sizeof(skinName);

    // initialize the previous skin name (needed to detect the animations)
    std::memset(prevSkinName, 0x0, prevSkinNameLength);

    // initialize the animation start index
    std::size_t animationStartIndex = 0;

    // iterate through MDL model frame group
    for (std::size_t i = 0; i < header.m_FrameCount; ++i)
    {
        std::unique_ptr<Model> pModel = std::make_unique<Model>();

        // the frame group contains at least 1 sub-frame?
        if (frameGroups[i].m_Count > 0)
        {
            std::memset(skinName, 0x0, skinNameLength);

            // get the skin name
            if (skinName)
                strcpy_s(skinName, sizeof(skinName), frameGroups[i].m_pFrame[0].m_Name);

            // reset the array content to 0x0 after the string end mark (required to find the animation group below)
            for (std::size_t j = 0; j < skinNameLength; ++j)
            {
                // calculate the skin name index
                const unsigned skinNameIndex = (unsigned)((skinNameLength - 1) - j);

                if (skinName[skinNameIndex] != 0x0)
                {
                    skinName[skinNameIndex] = 0x0;
                    continue;
                }

                break;
            }

            // revert iterate through the skin name and remove all the trailing numbers
            for (std::size_t j = 0; j < skinNameLength; ++j)
            {
                // calculate the skin name index
                const unsigned skinNameIndex = (unsigned)((skinNameLength - 1) - j);

                // is char empty or is a number?
                if (skinName[skinNameIndex] == 0x0 ||
                    (skinName[skinNameIndex] >= '0' && skinName[skinNameIndex] <= '9'))
                {
                    // erase it
                    skinName[skinNameIndex] = 0x0;
                    continue;
                }

                break;
            }

            // is previous skin name already initialized?
            if (prevSkinName[0] == 0x0)
                // no, initialize it
                std::memcpy(prevSkinName, skinName, skinNameLength);

            // do begin a new animation?
            if (i == (std::size_t)header.m_FrameCount - 1 || std::memcmp(skinName, prevSkinName, skinNameLength) != 0)
            {
                std::unique_ptr<IAnimation> pAnimation = std::make_unique<IAnimation>();

                // succeeded?
                if (!pAnimation)
                {
                    Clear();
                    return false;
                }

                // get the animation name
                std::memcpy(pAnimation->m_Name, prevSkinName, skinNameLength);

                // only one frame?
                if (header.m_FrameCount == 1)
                {
                    // populate the animation
                    pAnimation->m_Start = 0;
                    pAnimation->m_End   = 0;
                }
                else
                {
                    // populate the animation
                    pAnimation->m_Start = animationStartIndex;
                    pAnimation->m_End   = i - 1;
                }

                m_Animations.push_back(pAnimation.get());
                pAnimation.release();

                // prepare the values for the next animation
                animationStartIndex = (unsigned)i;
                std::memset(prevSkinName, 0x0, skinNameLength);
            }
        }

        // extract model from file content
        if (!PopulateModel(header,
                           frameGroups[i],
                           polygons,
                           texCoords,
                           pModel.get()))
        {
            Clear();
            return false;
        }

        m_Models.push_back(pModel.get());
        pModel.release();
    }

    return true;
}
//---------------------------------------------------------------------------
bool MDL::PopulateModel(const IHeader&        header,
                        const IFrameGroup&    frameGroup,
                        const IPolygons&      polygons,
                        const ITextureCoords& texCoords,
                              Model*          pModel) const
{
    // model contains no frame?
    if (!header.m_FrameCount)
        return true;

    // no frame group?
    if (!frameGroup.m_Count)
        return true;

    // no model to populate?
    if (!pModel)
        return false;

    std::unique_ptr<Mesh> pMesh         = std::make_unique<Mesh>();
    double                lastKnownTime = 0.0;

    // iterate through sub-frames contained in group
    for (std::size_t i = 0; i < frameGroup.m_Count; ++i)
    {
        // create the vertex buffers required for the sub-frames
        std::unique_ptr<VertexBuffer> pVB = std::make_unique<VertexBuffer>();

        // apply the user wished vertex format
        pVB->m_Format = m_VertFormatTemplate;

        // apply the user wished vertex culling
        pVB->m_Culling = m_VertCullingTemplate;

        // apply the user wished material
        pVB->m_Material = m_MaterialTemplate;

        // set the vertex format type
        pVB->m_Format.m_Type = VertexFormat::IEType::IE_VT_Triangles;

        // calculate the vertex stride
        pVB->m_Format.CalculateStride();

        // configure the frame time
        if (frameGroup.m_pTime)
        {
            pMesh->m_Time = frameGroup.m_pTime[i] - lastKnownTime;
            lastKnownTime = frameGroup.m_pTime[i];
        }
        else
            pMesh->m_Time = 0.0;

        // iterate through polygons to process
        for (std::size_t j = 0; j < header.m_PolygonCount; ++j)
            // iterate through polygon vertices
            for (std::size_t k = 0; k < 3; ++k)
            {
                // get source vertex
                const IVertex* pSrcVertex = &frameGroup.m_pFrame[i].m_pVertex[polygons[j].m_VertexIndex[k]];

                if (!pSrcVertex)
                    return false;

                // uncompress vertex
                const DWF_Math::Vector3F vertex = UncompressVertex(header, *pSrcVertex);

                DWF_Math::Vector3F normal;

                // get normal
                normal.m_X = g_NormalTable[pSrcVertex->m_NormalIndex];
                normal.m_Y = g_NormalTable[pSrcVertex->m_NormalIndex + 1];
                normal.m_Z = g_NormalTable[pSrcVertex->m_NormalIndex + 2];

                DWF_Math::Vector2F uv;

                // get vertex texture coordinates
                uv.m_X = (float)texCoords[polygons[j].m_VertexIndex[k]].m_U;
                uv.m_Y = (float)texCoords[polygons[j].m_VertexIndex[k]].m_V;

                // is texture coordinate on the back face?
                if (!polygons[j].m_FacesFront && texCoords[polygons[j].m_VertexIndex[k]].m_OnSeam)
                    // correct the texture coordinate to put it on the back face
                    uv.m_X += header.m_SkinWidth * 0.5f;

                // scale s and t to range from 0.0 to 1.0
                uv.m_X = (uv.m_X + 0.5f) / header.m_SkinWidth;
                uv.m_Y = (uv.m_Y + 0.5f) / header.m_SkinHeight;

                // add vertex to frame buffer
                if (!pVB->Add(&vertex,
                              &normal,
                              &uv,
                               (j * 3) + k,
                               m_fOnGetVertexColor))
                    return false;
            }

        // add frame buffer to mesh
        pMesh->m_VB.push_back(pVB.get());
        pVB.release();
    }

    // add mesh to model
    pModel->m_Mesh.push_back(pMesh.get());
    pMesh.release();

    return true;
}
//---------------------------------------------------------------------------
DWF_Buffer::PixelBuffer* MDL::UncompressTexture(const ISkin&      skin,
                                                      std::size_t width,
                                                      std::size_t height,
                                                      std::size_t index) const
{
    if (!skin.m_TexLen)
        return nullptr;

    // create a new pixel buffer
    std::unique_ptr<DWF_Buffer::PixelBuffer> pPB = std::make_unique< DWF_Buffer::PixelBuffer>();

    // succeeded?
    if (!pPB.get())
        return nullptr;

    // populate the pixel buffer and calculate the start offset
    pPB->m_ImageType    = DWF_Buffer::PixelBuffer::IEImageType::IE_IT_Raw;
    pPB->m_PixelType    = DWF_Buffer::PixelBuffer::IEPixelType::IE_PT_RGB;
    pPB->m_Width        = (unsigned)width;
    pPB->m_Height       = (unsigned)height;
    pPB->m_BytePerPixel = 3;
    pPB->m_Stride       = (unsigned)(width * pPB->m_BytePerPixel);
    pPB->m_DataLength   = (std::size_t)skin.m_TexLen * 3;

    const std::size_t offset = skin.m_TexLen * index;

    // allocate memory for the pixels
    pPB->m_pData = new unsigned char[pPB->m_DataLength];

    // convert indexed 8 bits texture to RGB 24 bits
    for (std::size_t i = 0; i < skin.m_TexLen; ++i)
    {
        ((unsigned char*)pPB->m_pData)[(i * pPB->m_BytePerPixel)]     = g_ColorTable[(skin.m_pData[offset + i] * pPB->m_BytePerPixel)];
        ((unsigned char*)pPB->m_pData)[(i * pPB->m_BytePerPixel) + 1] = g_ColorTable[(skin.m_pData[offset + i] * pPB->m_BytePerPixel) + 1];
        ((unsigned char*)pPB->m_pData)[(i * pPB->m_BytePerPixel) + 2] = g_ColorTable[(skin.m_pData[offset + i] * pPB->m_BytePerPixel) + 2];
    }

    return pPB.release();
}
//---------------------------------------------------------------------------
DWF_Math::Vector3F MDL::UncompressVertex(const IHeader& header, const IVertex& vertex) const
{
    float vector[3] = {0};

    // iterate through vertex coordinates
    for (std::size_t i = 0; i < 3; ++i)
        // uncompress vertex using frame scale and translate values
        vector[i] = (header.m_Scale[i] * vertex.m_Vertex[i]) + header.m_Translate[i];

    return DWF_Math::Vector3F(vector[0], vector[1], vector[2]);
}
//---------------------------------------------------------------------------
#ifdef CONVERT_ENDIANNESS
    MDL::IEEndianness MDL::GetEndianness()
    {
        const int i = 1;

        return (!*((char*)&i)) ? MDL::IEEndianness::IE_E_BigEndian : MDL::IEEndianness::IE_E_LittleEndian;
    }
#endif
//---------------------------------------------------------------------------
#ifdef CONVERT_ENDIANNESS
    void MDL::SwapMemory(void* pMemory, size_t size)
    {
              unsigned char* pBytes   = static_cast<unsigned char*>(pMemory);
        const std::size_t    halfSize = size >> 1;

        // iterate through bytes to swap
        for (std::size_t i = 0; i < halfSize; ++i)
        {
            const std::size_t lastIndex = (size - 1) - i;

            // swap the byte content (XOR method)
            pBytes[i]         = pBytes[i] ^ pBytes[lastIndex];
            pBytes[lastIndex] = pBytes[i] ^ pBytes[lastIndex];
            pBytes[i]         = pBytes[i] ^ pBytes[lastIndex];
        }
    }
#endif
//---------------------------------------------------------------------------
