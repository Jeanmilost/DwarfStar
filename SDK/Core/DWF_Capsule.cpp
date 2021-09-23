/****************************************************************************
 * ==> DWF_Capsule ---------------------------------------------------------*
 ****************************************************************************
 * Description:  Drawable capsule object                                    *
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

#include "DWF_Capsule.h"

// std
#include <memory>
#define _USE_MATH_DEFINES
#include <math.h>
#include <cmath>

// dwarfstar
#include "DWF_Line.h"

//---------------------------------------------------------------------------
// DWF_Capsule
//---------------------------------------------------------------------------
DWF_Capsule::DWF_Capsule() :
    DWF_Object()
{}
//---------------------------------------------------------------------------
DWF_Capsule::~DWF_Capsule()
{}
//---------------------------------------------------------------------------
bool DWF_Capsule::Intersect(const DWF_Capsule& other, float& penetrationDepth) const
{
    // this capsule
    const DWF_Vector3F firstLineDir       = (m_Top       - m_Bottom).Normalize();
    const DWF_Vector3F firstLineEndOffset = firstLineDir * m_Radius;
    const DWF_Vector3F firstTop           = m_Top        - firstLineEndOffset;
    const DWF_Vector3F firstBottom        = m_Bottom     + firstLineEndOffset;

    // second capsule
    const DWF_Vector3F secondLineDir       = (other.m_Top   - other.m_Bottom).Normalize();
    const DWF_Vector3F secondLineEndOffset = secondLineDir  * other.m_Radius;
    const DWF_Vector3F secondTop           = other.m_Top    - secondLineEndOffset;
    const DWF_Vector3F secondBottom        = other.m_Bottom + secondLineEndOffset;

    // vectors between line endpoints
    const DWF_Vector3F v0 = secondBottom - firstBottom;
    const DWF_Vector3F v1 = secondTop    - firstBottom;
    const DWF_Vector3F v2 = secondBottom - firstTop;
    const DWF_Vector3F v3 = secondTop    - firstTop;

    // squared distances
    const float d0 = v0.Dot(v0);
    const float d1 = v1.Dot(v1);
    const float d2 = v2.Dot(v2);
    const float d3 = v3.Dot(v3);

    DWF_Vector3F bestCandidate;

    // select best candidate for endpoint on first capsule
    if (d2 < d0 || d2 < d1 || d3 < d0 || d3 < d1)
        bestCandidate = firstTop;
    else
        bestCandidate = firstBottom;

    const DWF_LineF line      (firstBottom,  firstTop);
    const DWF_LineF secondLine(secondBottom, secondTop);

    // select best candidate for point on second capsule line segment nearest to best potential endpoint on first capsule
    const DWF_Vector3F secondBestCandidate = secondLine.ClosestPoint(bestCandidate);

    // do the same for first capsule segment
    bestCandidate = line.ClosestPoint(secondBestCandidate);

    // calculate penetration normal and length
    DWF_Vector3F penetrationNormal = bestCandidate - secondBestCandidate;
    const float  len               = penetrationNormal.Length();

    if (len == 0.0f)
        return false;

    // normalize
    penetrationNormal /= len;

    // calculate the penetration depth
    penetrationDepth = (m_Radius + other.m_Radius) - len;

    return (penetrationDepth > 0.0f);
}
//---------------------------------------------------------------------------
void DWF_Capsule::GetMesh(const DWF_VertexBuffer::IFormat&  format,
                          const DWF_VertexBuffer::ICulling& culling,
                          const DWF_Material&               material,
                                DWF_Mesh&                   mesh) const
{
    // this capsule
    const DWF_Vector3F lineDir       = (m_Top   - m_Bottom).Normalize();
    const DWF_Vector3F lineEndOffset = lineDir  * m_Radius;
    const DWF_Vector3F top           = m_Top    - lineEndOffset;
    const DWF_Vector3F bottom        = m_Bottom + lineEndOffset;

    const DWF_Vector3F axis   = bottom - top;
    const float        length = axis.Length();
    const DWF_Vector3F localZ = axis / (length ? length : 1.0f);
    const DWF_Vector3F localX = GetAnyPerpendicularUnitVector(localZ);
    const DWF_Vector3F localY = localZ.Cross(localX);

    const DWF_Vector3F start(0.0f, 0.0f, 0.0f);
    const DWF_Vector3F end  (1.0f, 1.0f, 1.0f);
    const float        resolution = 16.0f;

    const DWF_Vector3F step = (end - start) / resolution;

    // local nested function to calculate cylinder
    auto cylinder = [top, localX, localY, localZ, this, length](const float u, const float v)
    {
        return top                                                   +
               localX * std::cosf(2.0f * (float)M_PI * u) * m_Radius +
               localY * std::sinf(2.0f * (float)M_PI * u) * m_Radius +
               localZ * v * length;

    };

    // local nested function to calculate top half sphere
    auto sphereStart = [top, localX, localY, localZ, this](const float u, const float v)
    {
        const float latitude = (float)(M_PI / 2.0) * (v - 1);

        return top                                                                         +
               localX * std::cosf(2.0f * (float)M_PI * u) * std::cosf(latitude) * m_Radius +
               localY * std::sinf(2.0f * (float)M_PI * u) * std::cosf(latitude) * m_Radius +
               localZ * std::sinf(latitude) * m_Radius;
    };

    // local nested function to calculate bottom half sphere
    auto sphereEnd = [bottom, localX, localY, localZ, this](const float u, const float v)
    {
        const float latitude = (float)(M_PI / 2.0) * v;

        return bottom                                                                    +
               localX * std::cos(2.0f * (float)M_PI * u) * std::cos(latitude) * m_Radius +
               localY * std::sin(2.0f * (float)M_PI * u) * std::cos(latitude) * m_Radius +
               localZ * std::sin(latitude) * m_Radius;
    };

    std::unique_ptr<DWF_VertexBuffer> pVB(new DWF_VertexBuffer());
    pVB->m_Material = material;
    pVB->m_Culling  = culling;
    pVB->m_Format   = format;
    pVB->m_Format.CalculateStride();

    DWF_Vector3F p0, p1, p2, p3, normal0, normal1, normal2, normal3;
    DWF_Vector2F uv0, uv1, uv2, uv3;

    // iterate through latitude and longitude
    for (float i = 0.0f; i < resolution; ++i)
        for (float j = 0.0f; j < resolution; ++j)
        {
            // calculate the current slice
            const float u = i * step.m_X + start.m_X;
            const float v = j * step.m_Y + start.m_Y;

            // calculate the next slice
            const float un = (i + 1 == resolution) ? end.m_X : (i + 1) * step.m_X + start.m_X;
            const float vn = (j + 1 == resolution) ? end.m_Y : (j + 1) * step.m_Y + start.m_Y;

            // create next cylinder face
            p0 = cylinder(u,  v);
            p1 = cylinder(u,  vn);
            p2 = cylinder(un, v);
            p3 = cylinder(un, vn);

            // vertex has UV texture coordinates?
            if (((std::uint32_t)pVB->m_Format.m_Format & (std::uint32_t)DWF_VertexBuffer::IFormat::IEFormat::IE_VF_Normals) != 0)
            {
                // calculate the vertex normals
                normal0 = p0 / m_Radius;
                normal1 = p1 / m_Radius;
                normal2 = p2 / m_Radius;
                normal3 = p3 / m_Radius;
            }

            // vertex has UV texture coordinates?
            if (((std::uint32_t)pVB->m_Format.m_Format & (std::uint32_t)DWF_VertexBuffer::IFormat::IEFormat::IE_VF_TexCoords) != 0)
            {
                uv0.m_X =               (i      / resolution);
                uv0.m_Y = 0.333333f +  ((j      / resolution) * 0.333333f);
                uv1.m_X =               (i      / resolution);
                uv1.m_Y = 0.333333f + (((j + 1) / resolution) * 0.333333f);
                uv2.m_X =              ((i + 1) / resolution);
                uv2.m_Y = 0.333333f +  ((j      / resolution) * 0.333333f);
                uv3.m_X =              ((i + 1) / resolution);
                uv3.m_Y = 0.333333f + (((j + 1) / resolution) * 0.333333f);
            }

            // add face to vertex buffer
            pVB->Add(&p0, &normal0, &uv0, 0, nullptr);
            pVB->Add(&p1, &normal1, &uv1, 0, nullptr);
            pVB->Add(&p2, &normal2, &uv2, 0, nullptr);
            pVB->Add(&p3, &normal3, &uv3, 0, nullptr);
            pVB->Add(&p1, &normal1, &uv1, 0, nullptr);
            pVB->Add(&p2, &normal2, &uv2, 0, nullptr);

            // create next sphere start face
            p0 = sphereStart(u,  v);
            p1 = sphereStart(u,  vn);
            p2 = sphereStart(un, v);
            p3 = sphereStart(un, vn);

            // vertex has UV texture coordinates?
            if (((std::uint32_t)pVB->m_Format.m_Format & (std::uint32_t)DWF_VertexBuffer::IFormat::IEFormat::IE_VF_Normals) != 0)
            {
                // calculate the vertex normals
                normal0 = p0 / m_Radius;
                normal1 = p1 / m_Radius;
                normal2 = p2 / m_Radius;
                normal3 = p3 / m_Radius;
            }

            // vertex has UV texture coordinates?
            if (((std::uint32_t)pVB->m_Format.m_Format & (std::uint32_t)DWF_VertexBuffer::IFormat::IEFormat::IE_VF_TexCoords) != 0)
            {
                uv0.m_X =   (i      / resolution);
                uv0.m_Y =  ((j      / resolution) * 0.333333f);
                uv1.m_X =   (i      / resolution);
                uv1.m_Y = (((j + 1) / resolution) * 0.333333f);
                uv2.m_X =  ((i + 1) / resolution);
                uv2.m_Y =  ((j      / resolution) * 0.333333f);
                uv3.m_X =  ((i + 1) / resolution);
                uv3.m_Y = (((j + 1) / resolution) * 0.333333f);
            }

            // add face to vertex buffer
            pVB->Add(&p0, &normal0, &uv0, 0, nullptr);
            pVB->Add(&p1, &normal1, &uv1, 0, nullptr);
            pVB->Add(&p2, &normal2, &uv2, 0, nullptr);
            pVB->Add(&p3, &normal3, &uv3, 0, nullptr);
            pVB->Add(&p1, &normal1, &uv1, 0, nullptr);
            pVB->Add(&p2, &normal2, &uv2, 0, nullptr);

            // create next sphere end face
            p0 = sphereEnd(u,  v);
            p1 = sphereEnd(u,  vn);
            p2 = sphereEnd(un, v);
            p3 = sphereEnd(un, vn);

            // vertex has UV texture coordinates?
            if (((std::uint32_t)pVB->m_Format.m_Format & (std::uint32_t)DWF_VertexBuffer::IFormat::IEFormat::IE_VF_Normals) != 0)
            {
                // calculate the vertex normals
                normal0 = p0 / m_Radius;
                normal1 = p1 / m_Radius;
                normal2 = p2 / m_Radius;
                normal3 = p3 / m_Radius;
            }

            // vertex has UV texture coordinates?
            if (((std::uint32_t)pVB->m_Format.m_Format & (std::uint32_t)DWF_VertexBuffer::IFormat::IEFormat::IE_VF_TexCoords) != 0)
            {
                uv0.m_X =               (i      / resolution);
                uv0.m_Y = 0.666667f +  ((j      / resolution) * 0.333333f);
                uv1.m_X =               (i      / resolution);
                uv1.m_Y = 0.666667f + (((j + 1) / resolution) * 0.333333f);
                uv2.m_X =              ((i + 1) / resolution);
                uv2.m_Y = 0.666667f +  ((j      / resolution) * 0.333333f);
                uv3.m_X =              ((i + 1) / resolution);
                uv3.m_Y = 0.666667f + (((j + 1) / resolution) * 0.333333f);
            }

            // add face to vertex buffer
            pVB->Add(&p0, &normal0, &uv0, 0, nullptr);
            pVB->Add(&p1, &normal1, &uv1, 0, nullptr);
            pVB->Add(&p2, &normal2, &uv2, 0, nullptr);
            pVB->Add(&p3, &normal3, &uv3, 0, nullptr);
            pVB->Add(&p1, &normal1, &uv1, 0, nullptr);
            pVB->Add(&p2, &normal2, &uv2, 0, nullptr);
        }

    mesh.m_VBs.push_back(pVB.get());
    pVB.release();
}
//---------------------------------------------------------------------------
DWF_Vector3F DWF_Capsule::GetAnyPerpendicularUnitVector(const DWF_Vector3F& vec) const
{
    if (vec.m_Y != 0.0f || vec.m_Z != 0.0f)
        return DWF_Vector3F(1.0f, 0.0f, 0.0f);

    return DWF_Vector3F(0.0f, 1.0f, 0.0f);
}
//---------------------------------------------------------------------------
