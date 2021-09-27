/****************************************************************************
 * ==> DWF_Box -------------------------------------------------------------*
 ****************************************************************************
 * Description:  Geometric box                                              *
 * Contained in: Core                                                       *
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

#include "DWF_Box.h"

// std
#include <memory>
#define _USE_MATH_DEFINES
#include <math.h>
#include <cmath>

//---------------------------------------------------------------------------
// DWF_Box
//---------------------------------------------------------------------------
DWF_Box::DWF_Box() :
    DWF_Object()
{}
//---------------------------------------------------------------------------
DWF_Box::DWF_Box(const DWF_Vector3F& min, const DWF_Vector3F& max) :
    DWF_Object(),
    m_Min(min),
    m_Max(max)
{}
//---------------------------------------------------------------------------
DWF_Box::~DWF_Box()
{}
//---------------------------------------------------------------------------
DWF_Vector3F DWF_Box::GetCenter() const
{
    return DWF_Vector3F((m_Min.m_X + m_Max.m_X) / 2.0f,
                        (m_Min.m_Y + m_Max.m_Y) / 2.0f,
                        (m_Min.m_Z + m_Max.m_Z) / 2.0f);
}
//---------------------------------------------------------------------------
DWF_Box::IEAxis DWF_Box::GetLongestAxis() const
{
    // calculate each edge length
    const float x = std::fabs(m_Max.m_X - m_Min.m_X);
    const float y = std::fabs(m_Max.m_Y - m_Min.m_Y);
    const float z = std::fabs(m_Max.m_Z - m_Min.m_Z);

    // search for longest axis
    if (x >= y && x >= z)
        return IEAxis::IE_A_X;
    else
    if (y >= x && y >= z)
        return IEAxis::IE_A_Y;
    else
        return IEAxis::IE_A_Z;
}
//---------------------------------------------------------------------------
DWF_PlaneF DWF_Box::GetSplittingPlane(IEAxis axis) const
{
    switch (axis)
    {
        case IEAxis::IE_A_X: return DWF_PlaneF(1.0f, 0.0f, 0.0f, -GetCenter().m_X);
        case IEAxis::IE_A_Y: return DWF_PlaneF(0.0f, 1.0f, 0.0f, -GetCenter().m_Y);
        case IEAxis::IE_A_Z: return DWF_PlaneF(0.0f, 0.0f, 1.0f, -GetCenter().m_Z);
        default:             return DWF_PlaneF();
    }
}
//---------------------------------------------------------------------------
DWF_PlaneF DWF_Box::GetSplittingPlane(IEAxis axis, const DWF_Vector3F& center) const
{
    switch (axis)
    {
        case IEAxis::IE_A_X: return DWF_PlaneF(1.0f, 0.0f, 0.0f, -center.m_X);
        case IEAxis::IE_A_Y: return DWF_PlaneF(0.0f, 1.0f, 0.0f, -center.m_Y);
        case IEAxis::IE_A_Z: return DWF_PlaneF(0.0f, 0.0f, 1.0f, -center.m_Z);
        default:             return DWF_PlaneF();
    }
}
//-----------------------------------------------------------------------------------------
void DWF_Box::Cut(DWF_Box& leftBox, DWF_Box& rightBox)
{
    // calculate each edge length
    const float x = std::fabs(m_Max.m_X - m_Min.m_X);
    const float y = std::fabs(m_Max.m_Y - m_Min.m_Y);
    const float z = std::fabs(m_Max.m_Z - m_Min.m_Z);

    int longestAxis;

    // search for longest axis
    if ((x >= y) && (x >= z))
        longestAxis = 0;
    else
    if ((y >= x) && (y >= z))
        longestAxis = 1;
    else
        longestAxis = 2;

    // cut box
    switch (longestAxis)
    {
        // cut on x axis
        case 0:
            leftBox.m_Min     = m_Min;
            leftBox.m_Max     = m_Max;
            leftBox.m_Max.m_X = m_Min.m_X + (x * 0.5f);

            rightBox.m_Min     = m_Min;
            rightBox.m_Max     = m_Max;
            rightBox.m_Min.m_X = leftBox.m_Max.m_X;

            return;

        // cut on y axis
        case 1:
            leftBox.m_Min     = m_Min;
            leftBox.m_Max     = m_Max;
            leftBox.m_Max.m_Y = m_Min.m_Y + (y * 0.5f);

            rightBox.m_Min     = m_Min;
            rightBox.m_Max     = m_Max;
            rightBox.m_Min.m_Y = leftBox.m_Max.m_Y;

            return;

        // cut on z axis
        case 2:
            leftBox.m_Min     = m_Min;
            leftBox.m_Max     = m_Max;
            leftBox.m_Max.m_Z = m_Min.m_Z + (z * 0.5f);

            rightBox.m_Min     = m_Min;
            rightBox.m_Max     = m_Max;
            rightBox.m_Min.m_Z = leftBox.m_Max.m_Z;

            return;
    }
}
//---------------------------------------------------------------------------
bool DWF_Box::Inside(float x, float y, float z) const
{
    return Inside(DWF_Vector3F(x, y, z));
}
//---------------------------------------------------------------------------
bool DWF_Box::Inside(const DWF_Vector3F& point) const
{
    return (point.m_X >= m_Min.m_X &&
            point.m_Y >= m_Min.m_Y &&
            point.m_Z >= m_Min.m_Z &&
            point.m_X <= m_Max.m_X &&
            point.m_Y <= m_Max.m_Y &&
            point.m_Z <= m_Max.m_Z);
}
//---------------------------------------------------------------------------
bool DWF_Box::Intersect(const DWF_Box& other) const
{
    return !(m_Min.m_X > other.m_Max.m_X || m_Max.m_X < other.m_Min.m_X ||
             m_Min.m_Y > other.m_Max.m_Y || m_Max.m_Y < other.m_Min.m_Y ||
             m_Min.m_Z > other.m_Max.m_Z || m_Max.m_Z < other.m_Min.m_Z);
}
//---------------------------------------------------------------------------
void DWF_Box::GetMesh(float                                 width,
                      float                                 height,
                      float                                 depth,
                      bool                                  repeatTexOnEachFace,
                const DWF_VertexBuffer::IFormat&            format,
                const DWF_VertexBuffer::ICulling&           culling,
                const DWF_Material&                         material,
                      DWF_Mesh&                             mesh,
                const DWF_VertexBuffer::ITfOnGetVertexColor fOnGetVertexColor)
{
    // calculate half values
    const float halfX = width  / 2.0f;
    const float halfY = height / 2.0f;
    const float halfZ = depth  / 2.0f;

    // iterate through each edges
    for (std::size_t i = 0; i < 6; ++i)
    {
        // create a vertex buffer for each box edges
        std::unique_ptr<DWF_VertexBuffer> pVB(new DWF_VertexBuffer());

        // apply the user wished vertex format, culling and material
        pVB->m_Format   = format;
        pVB->m_Culling  = culling;
        pVB->m_Material = material;

        // set the vertex format type
        pVB->m_Format.m_Type = DWF_VertexBuffer::IFormat::IEType::IE_VT_TriangleStrip;

        // calculate the stride
        pVB->m_Format.CalculateStride();

        mesh.m_VBs.push_back(pVB.get());
        pVB.release();
    }

    DWF_Vector3F vertices[8];

    // iterate through vertices to create. Vertices are generated as follow:
    //     v2 *--------* v6
    //      / |      / |
    // v4 *--------* v8|
    //    |   |    |   |
    //    |v1 *----|---* v5
    //    | /      | /
    // v3 *--------* v7
    for (std::size_t i = 0; i < 8; ++i)
    {
        // generate the 4 first vertices on the left, and 4 last on the right
        if (!(i / 4))
            vertices[i].m_X = -halfX;
        else
            vertices[i].m_X =  halfX;

        // generate 2 vertices on the front, then 2 vertices on the back
        if (!((i / 2) % 2))
            vertices[i].m_Z = -halfZ;
        else
            vertices[i].m_Z =  halfZ;

        // for each vertices, generates one on the top, and one on the bottom
        if (!(i % 2))
            vertices[i].m_Y = -halfY;
        else
            vertices[i].m_Y =  halfY;
    }

    DWF_Vector3F normals[6];

    // calculate normals
    normals[0].m_X = -1.0; normals[0].m_Y =  0.0; normals[0].m_Z =  0.0;
    normals[1].m_X =  1.0; normals[1].m_Y =  0.0; normals[1].m_Z =  0.0;
    normals[2].m_X =  0.0; normals[2].m_Y = -1.0; normals[2].m_Z =  0.0;
    normals[3].m_X =  0.0; normals[3].m_Y =  1.0; normals[3].m_Z =  0.0;
    normals[4].m_X =  0.0; normals[4].m_Y =  0.0; normals[4].m_Z = -1.0;
    normals[5].m_X =  0.0; normals[5].m_Y =  0.0; normals[5].m_Z =  1.0;

    DWF_Vector2F texCoords[24];

    // do repeat texture on each faces?
    if (repeatTexOnEachFace)
    {
        // calculate texture positions
        texCoords[0].m_X  = 0.0; texCoords[0].m_Y  = 0.0;
        texCoords[1].m_X  = 0.0; texCoords[1].m_Y  = 1.0;
        texCoords[2].m_X  = 1.0; texCoords[2].m_Y  = 0.0;
        texCoords[3].m_X  = 1.0; texCoords[3].m_Y  = 1.0;
        texCoords[4].m_X  = 0.0; texCoords[4].m_Y  = 0.0;
        texCoords[5].m_X  = 0.0; texCoords[5].m_Y  = 1.0;
        texCoords[6].m_X  = 1.0; texCoords[6].m_Y  = 0.0;
        texCoords[7].m_X  = 1.0; texCoords[7].m_Y  = 1.0;
        texCoords[8].m_X  = 0.0; texCoords[8].m_Y  = 0.0;
        texCoords[9].m_X  = 0.0; texCoords[9].m_Y  = 1.0;
        texCoords[10].m_X = 1.0; texCoords[10].m_Y = 0.0;
        texCoords[11].m_X = 1.0; texCoords[11].m_Y = 1.0;
        texCoords[12].m_X = 0.0; texCoords[12].m_Y = 0.0;
        texCoords[13].m_X = 0.0; texCoords[13].m_Y = 1.0;
        texCoords[14].m_X = 1.0; texCoords[14].m_Y = 0.0;
        texCoords[15].m_X = 1.0; texCoords[15].m_Y = 1.0;
        texCoords[16].m_X = 0.0; texCoords[16].m_Y = 0.0;
        texCoords[17].m_X = 0.0; texCoords[17].m_Y = 1.0;
        texCoords[18].m_X = 1.0; texCoords[18].m_Y = 0.0;
        texCoords[19].m_X = 1.0; texCoords[19].m_Y = 1.0;
        texCoords[20].m_X = 0.0; texCoords[20].m_Y = 0.0;
        texCoords[21].m_X = 0.0; texCoords[21].m_Y = 1.0;
        texCoords[22].m_X = 1.0; texCoords[22].m_Y = 0.0;
        texCoords[23].m_X = 1.0; texCoords[23].m_Y = 1.0;
    }
    else
    {
        // calculate texture offset
        const float texOffset = 1.0f / 3.0f;

        // calculate texture positions. They are distributed as follow:
        // -------------------
        // |     |     |     |
        // |  1  |  2  |  3  |
        // |     |     |     |
        // |-----------------|
        // |     |     |     |
        // |  4  |  5  |  6  |
        // |     |     |     |
        // -------------------
        // |  This texture   |
        // |  area is not    |
        // |  used           |
        // -------------------
        texCoords[0].m_X  = 0.0f;             texCoords[0].m_Y  = texOffset;
        texCoords[1].m_X  = 0.0f;             texCoords[1].m_Y  = 0.0f;
        texCoords[2].m_X  = texOffset;        texCoords[2].m_Y  = texOffset;
        texCoords[3].m_X  = texOffset;        texCoords[3].m_Y  = 0.0f;
        texCoords[4].m_X  = texOffset;        texCoords[4].m_Y  = texOffset;
        texCoords[5].m_X  = texOffset;        texCoords[5].m_Y  = 0.0f;
        texCoords[6].m_X  = texOffset * 2.0f; texCoords[6].m_Y  = texOffset;
        texCoords[7].m_X  = texOffset * 2.0f; texCoords[7].m_Y  = 0.0f;
        texCoords[8].m_X  = texOffset * 2.0f; texCoords[8].m_Y  = texOffset;
        texCoords[9].m_X  = texOffset * 2.0f; texCoords[9].m_Y  = 0.0f;
        texCoords[10].m_X = 1.0f;             texCoords[10].m_Y = texOffset;
        texCoords[11].m_X = 1.0f;             texCoords[11].m_Y = 0.0f;
        texCoords[12].m_X = 0.0f;             texCoords[12].m_Y = texOffset * 2.0f;
        texCoords[13].m_X = 0.0f;             texCoords[13].m_Y = texOffset;
        texCoords[14].m_X = texOffset;        texCoords[14].m_Y = texOffset * 2.0f;
        texCoords[15].m_X = texOffset;        texCoords[15].m_Y = texOffset;
        texCoords[16].m_X = texOffset;        texCoords[16].m_Y = texOffset * 2.0f;
        texCoords[17].m_X = texOffset;        texCoords[17].m_Y = texOffset;
        texCoords[18].m_X = texOffset * 2.0f; texCoords[18].m_Y = texOffset * 2.0f;
        texCoords[19].m_X = texOffset * 2.0f; texCoords[19].m_Y = texOffset;
        texCoords[20].m_X = texOffset * 2.0f; texCoords[20].m_Y = texOffset * 2.0f;
        texCoords[21].m_X = texOffset * 2.0f; texCoords[21].m_Y = texOffset;
        texCoords[22].m_X = 1.0f;             texCoords[22].m_Y = texOffset * 2.0f;
        texCoords[23].m_X = 1.0f;             texCoords[23].m_Y = texOffset;
    }

    // create box edge 1
    mesh.m_VBs[0]->Add(&vertices[1], &normals[0], &texCoords[4],  0, fOnGetVertexColor);
    mesh.m_VBs[0]->Add(&vertices[0], &normals[0], &texCoords[5],  1, fOnGetVertexColor);
    mesh.m_VBs[0]->Add(&vertices[3], &normals[0], &texCoords[6],  2, fOnGetVertexColor);
    mesh.m_VBs[0]->Add(&vertices[2], &normals[0], &texCoords[7],  3, fOnGetVertexColor);

    // create box edge 2
    mesh.m_VBs[1]->Add(&vertices[3], &normals[5], &texCoords[8],  0, fOnGetVertexColor);
    mesh.m_VBs[1]->Add(&vertices[2], &normals[5], &texCoords[9],  1, fOnGetVertexColor);
    mesh.m_VBs[1]->Add(&vertices[7], &normals[5], &texCoords[10], 2, fOnGetVertexColor);
    mesh.m_VBs[1]->Add(&vertices[6], &normals[5], &texCoords[11], 3, fOnGetVertexColor);

    // create box edge 3
    mesh.m_VBs[2]->Add(&vertices[7], &normals[1], &texCoords[12], 0, fOnGetVertexColor);
    mesh.m_VBs[2]->Add(&vertices[6], &normals[1], &texCoords[13], 1, fOnGetVertexColor);
    mesh.m_VBs[2]->Add(&vertices[5], &normals[1], &texCoords[14], 2, fOnGetVertexColor);
    mesh.m_VBs[2]->Add(&vertices[4], &normals[1], &texCoords[15], 3, fOnGetVertexColor);

    // create box edge 4
    mesh.m_VBs[3]->Add(&vertices[5], &normals[4], &texCoords[16], 0, fOnGetVertexColor);
    mesh.m_VBs[3]->Add(&vertices[4], &normals[4], &texCoords[17], 1, fOnGetVertexColor);
    mesh.m_VBs[3]->Add(&vertices[1], &normals[4], &texCoords[18], 2, fOnGetVertexColor);
    mesh.m_VBs[3]->Add(&vertices[0], &normals[4], &texCoords[19], 3, fOnGetVertexColor);

    // create box edge 5
    mesh.m_VBs[4]->Add(&vertices[1], &normals[3], &texCoords[0], 0, fOnGetVertexColor);
    mesh.m_VBs[4]->Add(&vertices[3], &normals[3], &texCoords[1], 1, fOnGetVertexColor);
    mesh.m_VBs[4]->Add(&vertices[5], &normals[3], &texCoords[2], 2, fOnGetVertexColor);
    mesh.m_VBs[4]->Add(&vertices[7], &normals[3], &texCoords[3], 3, fOnGetVertexColor);

    // create box edge 6
    mesh.m_VBs[5]->Add(&vertices[2], &normals[2], &texCoords[20], 0, fOnGetVertexColor);
    mesh.m_VBs[5]->Add(&vertices[0], &normals[2], &texCoords[21], 1, fOnGetVertexColor);
    mesh.m_VBs[5]->Add(&vertices[6], &normals[2], &texCoords[22], 2, fOnGetVertexColor);
    mesh.m_VBs[5]->Add(&vertices[4], &normals[2], &texCoords[23], 3, fOnGetVertexColor);
}
//---------------------------------------------------------------------------
