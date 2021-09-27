/****************************************************************************
 * ==> DWF_Sphere ----------------------------------------------------------*
 ****************************************************************************
 * Description : Geometric sphere                                           *
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

#include "DWF_Sphere.h"

// std
#include <memory>
#define _USE_MATH_DEFINES
#include <math.h>
#include <cmath>

//---------------------------------------------------------------------------
// DWF_Sphere
//---------------------------------------------------------------------------
DWF_Sphere::DWF_Sphere() :
    DWF_Object()
{}
//---------------------------------------------------------------------------
DWF_Sphere::DWF_Sphere(const DWF_Vector3F& center, float radius) :
    DWF_Object(),
    m_Center(center),
    m_Radius(radius)
{}
//---------------------------------------------------------------------------
DWF_Sphere::~DWF_Sphere()
{}
//---------------------------------------------------------------------------
bool DWF_Sphere::Inside(float x, float y, float z) const
{
    return Inside(DWF_Vector3F(x, y, z));
}
//---------------------------------------------------------------------------
bool DWF_Sphere::Inside(const DWF_Vector3F& point) const
{
    // calculate the distance between test point and the center of the sphere
    const DWF_Vector3F length   = point - m_Center;
    const float        distance = length.Length();

    // check if distance is shorter than the sphere radius and return result
    return (distance <= m_Radius);
}
//---------------------------------------------------------------------------
bool DWF_Sphere::Intersect(const DWF_Sphere& other) const
{
    const DWF_Vector3F dist(std::fabs(m_Center.m_X - other.m_Center.m_X),
                            std::fabs(m_Center.m_Y - other.m_Center.m_Y),
                            std::fabs(m_Center.m_Z - other.m_Center.m_Z));

    const float length = dist.Length();

    return (length <= (m_Radius + other.m_Radius));
}
//---------------------------------------------------------------------------
void DWF_Sphere::GetMesh(float                                 radius,
                         std::size_t                           slices,
                         std::size_t                           stacks,
                   const DWF_VertexBuffer::IFormat&            format,
                   const DWF_VertexBuffer::ICulling&           culling,
                   const DWF_Material&                         material,
                         DWF_Mesh&                             mesh,
                   const DWF_VertexBuffer::ITfOnGetVertexColor fOnGetVertexColor)
{
    if (!slices || !stacks)
        return;

    // initialize global values
    const float majorStep = ((float)       M_PI  / slices);
    const float minorStep = ((float)(2.0 * M_PI) / stacks);

    // iterate through vertex slices
    for (std::size_t i = 0; i < slices; ++i)
    {
        // create a new vertex buffer to contain the next slice
        std::unique_ptr<DWF_VertexBuffer> pVB(new DWF_VertexBuffer());

        // apply the user wished vertex format, culling and material
        pVB->m_Format   = format;
        pVB->m_Culling  = culling;
        pVB->m_Material = material;

        // set the vertex format type
        pVB->m_Format.m_Type = DWF_VertexBuffer::IFormat::IEType::IE_VT_TriangleStrip;

        // calculate the stride
        pVB->m_Format.CalculateStride();

        // calculate next slice values
        const float a  = i * majorStep;
        const float b  = a + majorStep;
        const float r0 = radius * std::sinf(a);
        const float r1 = radius * std::sinf(b);
        const float z0 = radius * std::cosf(a);
        const float z1 = radius * std::cosf(b);

        // iterate through vertex stacks
        for (std::size_t j = 0; j <= stacks; ++j)
        {
            const float c = j * minorStep;
            const float x = std::cosf(c);
            const float y = std::sinf(c);

            DWF_Vector3F vertex;

            // calculate vertex
            vertex.m_X = x * r0;
            vertex.m_Y = y * r0;
            vertex.m_Z = z0;

            DWF_Vector3F normal;

            // vertex has a normal?
            if (((std::size_t)pVB->m_Format.m_Format & (std::size_t)DWF_VertexBuffer::IFormat::IEFormat::IE_VF_Normals) != 0)
            {
                normal.m_X = (x * r0) / radius;
                normal.m_Y = (y * r0) / radius;
                normal.m_Z =      z0  / radius;
            }

            DWF_Vector2F uv;

            // vertex has UV texture coordinates?
            if (((std::size_t)pVB->m_Format.m_Format & (std::size_t)DWF_VertexBuffer::IFormat::IEFormat::IE_VF_TexCoords) != 0)
            {
                uv.m_X = ((float)j / (float)stacks);
                uv.m_Y = ((float)i / (float)slices);
            }

            // add the vertex to the buffer
            pVB->Add(&vertex,
                     &normal,
                     &uv,
                      j * 2,
                      fOnGetVertexColor);

            // calculate vertex
            vertex.m_X = x * r1;
            vertex.m_Y = y * r1;
            vertex.m_Z =     z1;

            // vertex has a normal?
            if (((std::size_t)pVB->m_Format.m_Format & (std::size_t)DWF_VertexBuffer::IFormat::IEFormat::IE_VF_Normals) != 0)
            {
                normal.m_X = (x * r1) / radius;
                normal.m_Y = (y * r1) / radius;
                normal.m_Z =      z1  / radius;
            }

            // vertex has UV texture coordinates?
            if (((std::size_t)pVB->m_Format.m_Format & (std::size_t)DWF_VertexBuffer::IFormat::IEFormat::IE_VF_TexCoords) != 0)
            {
                uv.m_X =  ((float)j         / (float)stacks);
                uv.m_Y = (((float)i + 1.0f) / (float)slices);
            }

            // add the vertex to the buffer
            pVB->Add(&vertex,
                     &normal,
                     &uv,
                     (j * 2) + 1,
                     fOnGetVertexColor);
        }

        mesh.m_VBs.push_back(pVB.get());
        pVB.release();
    }
}
//---------------------------------------------------------------------------
