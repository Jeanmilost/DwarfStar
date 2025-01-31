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

#include "DWF_Wavefront.h"

// classes
#include "DWF_StdFileBuffer.h"

using namespace DWF_Model;

//---------------------------------------------------------------------------
// Wavefront::IHelper
//---------------------------------------------------------------------------
void Wavefront::IHelper::SkipLine(const std::string data, std::size_t& index)
{
    // skip line
    while (index < data.length() && data[index] != '\r' && data[index] != '\n')
        ++index;
}
//---------------------------------------------------------------------------
void Wavefront::IHelper::ReadLine(const std::string data, std::size_t& index, std::string& text)
{
    bool doExit = false;

    // read the line
    while (index < data.length())
    {
        // dispatch the next char
        switch (data[index])
        {
            case '\r':
            case '\n':
                return;

            default:
                text += data[index];
                break;
        }

        // go to next char
        ++index;
    }
}
//---------------------------------------------------------------------------
// Wavefront::IMaterial
//---------------------------------------------------------------------------
Wavefront::IMaterial::IMaterial()
{}
//---------------------------------------------------------------------------
Wavefront::IMaterial::~IMaterial()
{}
//---------------------------------------------------------------------------
void Wavefront::IMaterial::Clear()
{
    m_Name.clear();
    m_TextureFileName.clear();
}
//---------------------------------------------------------------------------
bool Wavefront::IMaterial::Read(DWF_Buffer::Buffer& buffer)
{
    const std::string data = buffer.ToStr();

    if (!data.length())
        return false;

    Clear();

    bool result = false;

    // iterate through wavefront chars
    for (std::size_t i = 0; i < data.length(); ++i)
    {
        // dispatch next char
        switch (data[i])
        {
            case '#':
                // found commented line
                IHelper::SkipLine(data, i);
                continue;

            case 'm':
                // is a texture file name line?
                if (i + 5 < data.length())
                    if (data[i + 1] == 'a' &&
                        data[i + 2] == 'p' &&
                        data[i + 3] == '_' &&
                        data[i + 4] == 'K' &&
                        data[i + 5] == 'd')
                    {
                        // skip the texture file identifier and the first space
                        i += 7;

                        IHelper::ReadLine(data, i, m_TextureFileName);
                        continue;
                    }

                // unknown data, skip it
                IHelper::SkipLine(data, i);
                continue;

            case 'n':
                // is a material name line?
                if (i + 5 < data.length())
                    if (data[i + 1] == 'e' &&
                        data[i + 2] == 'w' &&
                        data[i + 3] == 'm' &&
                        data[i + 4] == 't' &&
                        data[i + 5] == 'l')
                    {
                        // skip the texture file identifier and the first space
                        i += 7;

                        IHelper::ReadLine(data, i, m_Name);
                        continue;
                    }

                // unknown data, skip it
                IHelper::SkipLine(data, i);
                continue;

            default:
                // unknown line, skip it
                IHelper::SkipLine(data, i);
                continue;
        }
    }

    return result;
}
//---------------------------------------------------------------------------
// Wavefront
//---------------------------------------------------------------------------
Wavefront::Wavefront()
{
    // configure the default vertex format
    m_VertFormatTemplate.m_Format = (VertexFormat::IEFormat)((unsigned)VertexFormat::IEFormat::IE_VF_Colors |
                                                             (unsigned)VertexFormat::IEFormat::IE_VF_TexCoords);
    m_VertFormatTemplate.m_Type = VertexFormat::IEType::IE_VT_Triangles;

    // configure the default vertex culling
    m_VertCullingTemplate.m_Type = VertexCulling::IECullingType::IE_CT_Back;
    m_VertCullingTemplate.m_Face = VertexCulling::IECullingFace::IE_CF_CCW;

    // configure the default material
    m_MaterialTemplate.m_Color = ColorF(1.0f, 1.0f, 1.0f, 1.0f);
}
//---------------------------------------------------------------------------
Wavefront::~Wavefront()
{
    if (m_pModel)
        delete m_pModel;
}
//---------------------------------------------------------------------------
void Wavefront::Clear()
{
    if (m_pModel)
        delete m_pModel;

    m_pModel = nullptr;
}
//---------------------------------------------------------------------------
bool Wavefront::Open(const std::string& fileName)
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
bool Wavefront::Open(const std::wstring& fileName)
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
bool Wavefront::Open(DWF_Buffer::Buffer& buffer)
{
    // clear the previous model, if exists
    Clear();

    // read the buffer content
    return Read(buffer);
}
//---------------------------------------------------------------------------
Model* Wavefront::GetModel() const
{
    return m_pModel;
}
//---------------------------------------------------------------------------
Model* Wavefront::ReleaseModel()
{
    Model* pModel = m_pModel;
    m_pModel      = nullptr;
    return pModel;
}
//---------------------------------------------------------------------------
void Wavefront::SetVertFormatTemplate(const VertexFormat& vertFormatTemplate)
{
    m_VertFormatTemplate = vertFormatTemplate;
}
//---------------------------------------------------------------------------
void Wavefront::SetVertCullingTemplate(const VertexCulling& vertCullingTemplate)
{
    m_VertCullingTemplate = vertCullingTemplate;
}
//---------------------------------------------------------------------------
void Wavefront::SetMaterial(const Material& materialTemplate)
{
    m_MaterialTemplate = materialTemplate;
}
//---------------------------------------------------------------------------
void Wavefront::Set_OnOpenMaterialFile(ITfOnOpenMaterialFile fOnOpenMaterialFile)
{
    m_fOnOpenMaterialFile = fOnOpenMaterialFile;
}
//---------------------------------------------------------------------------
void Wavefront::Set_OnGetVertexColor(VertexBuffer::ITfOnGetVertexColor fOnGetVertexColor)
{
    m_fOnGetVertexColor = fOnGetVertexColor;
}
//---------------------------------------------------------------------------
void Wavefront::Set_OnLoadTexture(Texture::ITfOnLoadTexture fOnLoadTexture)
{
    m_fOnLoadTexture = fOnLoadTexture;
}
//---------------------------------------------------------------------------
bool Wavefront::Read(DWF_Buffer::Buffer& buffer)
{
    const std::string data = buffer.ToStr();

    if (!data.length())
        return false;

    Clear();

    // create the model
    m_pModel = new Model();

    IMaterial   material;
    IVertexData vertex;
    IVertexData normal;
    IVertexData uv;
    IFaceData   face;
    std::string matName;
    bool        objectChanging = false;
    bool        groupChanging  = false;
    bool        result         = false;

    // iterate through wavefront chars
    for (std::size_t i = 0; i < data.length(); ++i)
    {
        // dispatch next char
        switch (data[i])
        {
            case '#':
                // found commented line
                IHelper::SkipLine(data, i);
                continue;

            case 'm':
                // is a material library line?
                if (i + 5 < data.length())
                    if (data[i + 1] == 't' &&
                        data[i + 2] == 'l' &&
                        data[i + 3] == 'l' &&
                        data[i + 4] == 'i' &&
                        data[i + 5] == 'b')
                    {
                        // skip the material identifier
                        i += 7;

                        // read the material
                        ReadLine(data, i, material);

                        // was the material read successfully?
                        if (!material.m_Name.empty())
                            m_Materials[material.m_Name] = material;

                        material.Clear();
                        continue;
                    }

                // unknown data, skip it
                IHelper::SkipLine(data, i);
                continue;

            case 'u':
                // is a material directive line?
                if (i + 5 < data.length())
                    if (data[i + 1] == 's' &&
                        data[i + 2] == 'e' &&
                        data[i + 3] == 'm' &&
                        data[i + 4] == 't' &&
                        data[i + 5] == 'l')
                    {
                        // skip the material identifier and the first space
                        i += 7;

                        // read the material name to use
                        IHelper::ReadLine(data, i, matName);
                        continue;
                    }

                // unknown data, skip it
                IHelper::SkipLine(data, i);
                continue;

            case 'v':
                // do begin to read a new wavefront object or group?
                if (objectChanging || groupChanging)
                {
                    objectChanging = false;
                    groupChanging  = false;
                }

                // check if line contains a normal or a texture coordinate
                if (i + 1 < data.length())
                {
                    // line contains a normal
                    if (data[i + 1] == 'n')
                    {
                        ++i;
                        ReadLine(data, i, normal);
                        continue;
                    }

                    // line contains a texture coordinate
                    if (data[i + 1] == 't')
                    {
                        ++i;
                        ReadLine(data, i, uv);
                        continue;
                    }
                }

                // line contains a vertex
                ReadLine(data, i, vertex);
                continue;

            case 'f':
                // line contains a face
                ReadLine(data, i, face);

                // build the face
                if (!BuildFace(vertex, normal, uv, face, matName, objectChanging, 0))
                {
                    Clear();
                    return false;
                }

                // clear the local face buffer (a new face will be read on the next iteration)
                face.clear();

                groupChanging = true;
                continue;

            case 'o':
                // line contains an object
                IHelper::SkipLine(data, i);

                // clear the local data (a new object will be built)
                matName.clear();
                vertex.clear();
                normal.clear();
                uv.clear();
                face.clear();

                objectChanging = true;
                continue;

            case 'g':
                // line contains a polygon group
                IHelper::SkipLine(data, i);

                // clear the local data (a new group will be built)
                matName.clear();
                vertex.clear();
                normal.clear();
                uv.clear();
                face.clear();

                groupChanging = true;
                continue;

            default:
                // unknown line, skip it
                IHelper::SkipLine(data, i);
                continue;
        }
    }

    return result;
}
//---------------------------------------------------------------------------
void Wavefront::ReadLine(const std::string data, std::size_t& index, IMaterial& material) const
{
    std::string line;
    bool        doExit = false;

    // read the line
    while (index < data.length())
    {
        // dispatch the next char
        switch (data[index])
        {
            case '\r':
            case '\n':
                doExit = true;
                break;

            default:
                line += data[index];
                break;
        }

        if (doExit)
            break;

        // go to next char
        ++index;
    }

    DWF_Buffer::Buffer* pMtlFileBuffer = nullptr;

    if (!m_fOnOpenMaterialFile)
        return;

    // open the material file
    if (!m_fOnOpenMaterialFile(line, pMtlFileBuffer))
        return;

    // received a valid file buffer?
    if (!pMtlFileBuffer)
        return;

    std::unique_ptr<DWF_Buffer::Buffer> pBuffer(pMtlFileBuffer);

    material.Read(*pBuffer.get());
}
//---------------------------------------------------------------------------
void Wavefront::ReadLine(const std::string data, std::size_t& index, IVertexData& vertexData) const
{
    std::string line;
    bool        doExit = false;

    // read the line
    while (index < data.length())
    {
        // dispatch the next char
        switch (data[index])
        {
            case '\r':
            case '\n':
                doExit = true;

            case ' ':
                // something to parse?
                if (line.length())
                    vertexData.push_back(std::stof(line));

                // do exit the loop?
                if (doExit)
                    return;

                line.clear();
                break;

            default:
                // keep only numeric values
                if ((data[index] >= '0' && data[index] <= '9') || data[index] == '-' || data[index] == '.')
                    line += data[index];

                break;
        }

        // go to next char
        ++index;
    }
}
//---------------------------------------------------------------------------
void Wavefront::ReadLine(const std::string data, std::size_t& index, IFaceData& faceData) const
{
    std::string line;
    bool        doExit = false;

    // read the line
    while (index < data.length())
    {
        // dispatch the next char
        switch (data[index])
        {
            case '\r':
            case '\n':
                doExit = true;

            case ' ':
            case '/':
                // something to parse?
                if (line.length())
                    faceData.push_back(std::stoi(line));

                // do exit the loop?
                if (doExit)
                    return;

                line.clear();
                break;

            default:
                // keep only numeric values
                if ((data[index] >= '0' && data[index] <= '9') || data[index] == '-' || data[index] == '.')
                    line += data[index];

                break;
        }

        // go to next char
        ++index;
    }
}
//---------------------------------------------------------------------------
bool Wavefront::BuildFace(const IVertexData& vertices,
                          const IVertexData& normals,
                          const IVertexData& uvs,
                          const IFaceData&   faces,
                          const std::string& matName,
                                bool         objectChanging,
                                bool         groupChanging) const
{
    Mesh*         pMesh = nullptr;
    VertexBuffer* pVB   = nullptr;

    // do build the previous group or object?
    if (vertices.size() && faces.size())
    {
        // do create a new mesh?
        if (objectChanging || !m_pModel->m_Mesh.size())
        {
            std::unique_ptr<Mesh> pNewMesh = std::make_unique<Mesh>();

            m_pModel->m_Mesh.push_back(pNewMesh.get());
            pMesh = pNewMesh.release();
        }
        else
            pMesh = m_pModel->m_Mesh[m_pModel->m_Mesh.size() - 1];

        // do create a new vertex buffer?
        if (groupChanging || !pMesh->m_VB.size())
        {
            std::unique_ptr<VertexBuffer> pNewVB = std::make_unique<VertexBuffer>();

            pNewVB->m_Format   = m_VertFormatTemplate;
            pNewVB->m_Culling  = m_VertCullingTemplate;
            pNewVB->m_Material = m_MaterialTemplate;

            // set the vertex type and format
            pNewVB->m_Format.m_Type   = VertexFormat::IEType::IE_VT_Triangles;
            pNewVB->m_Format.m_Format = VertexFormat::IEFormat::IE_VF_Colors;

            // has normals?
            if (normals.size() && ((int)m_VertFormatTemplate.m_Format & (int)VertexFormat::IEFormat::IE_VF_Normals))
                pNewVB->m_Format.m_Format = (VertexFormat::IEFormat)((int)pNewVB->m_Format.m_Format | (int)VertexFormat::IEFormat::IE_VF_Normals);

            // has texture coordinates?
            if (uvs.size() && ((int)m_VertFormatTemplate.m_Format & (int)VertexFormat::IEFormat::IE_VF_TexCoords))
                pNewVB->m_Format.m_Format = (VertexFormat::IEFormat)((int)pNewVB->m_Format.m_Format | (int)VertexFormat::IEFormat::IE_VF_TexCoords);

            // calculate the vertex stride
            pNewVB->m_Format.CalculateStride();

            // do use a material?
            if (!matName.empty())
            {
                // search it in the list
                IMaterials::const_iterator it = m_Materials.find(matName);

                if (it != m_Materials.end())
                    if (m_fOnLoadTexture)
                        pNewVB->m_Material.m_pTexture = m_fOnLoadTexture(it->second.m_TextureFileName, false);
            }

            pMesh->m_VB.push_back(pNewVB.get());
            pVB = pNewVB.release();
        }
        else
            pVB = pMesh->m_VB[pMesh->m_VB.size() - 1];

        // build the next buffer
        BuildVertexBuffer(vertices, normals, uvs, faces, pVB);
    }

    return true;
}
//---------------------------------------------------------------------------
void Wavefront::BuildVertexBuffer(const IVertexData&  vertices,
                                  const IVertexData&  normals,
                                  const IVertexData&  uvs,
                                  const IFaceData&    faces,
                                        VertexBuffer* pVB) const
{
    // calculate the normal and uv offsets. Be careful, the face values follows one each other in
    // the file, without distinction, so the correct format (v, v/n, v/f or v/n/f) should be
    // determined and used
    std::size_t uvOffset     = uvs.size()     ? 1            : 0;
    std::size_t normalOffset = normals.size() ? uvOffset + 1 : 0;

    // wavefront faces are organized as triangle fan, so get the first vertex
    // and build all others from it
    std::int64_t baseVertexIndex = (faces[0] - 1) * 3;
    std::size_t  faceStride      = 1;

    std::int64_t baseUVIndex = 0;

    // get the first texture coordinate
    if (uvs.size())
    {
        baseUVIndex = (faces[uvOffset] - 1) * 2;
        ++faceStride;
    }

    std::int64_t baseNormalIndex = 0;

    // get the first normal
    if (normals.size())
    {
        baseNormalIndex = (faces[normalOffset] - 1) * 3;
        ++faceStride;
    }

    // iterate through remaining indices
    for (std::size_t i = 1; i <= (faces.size() / faceStride) - 2; ++i)
    {
        DWF_Math::Vector3F vertex;
        DWF_Math::Vector3F normal;
        DWF_Math::Vector2F uv;

        const bool hasNormal    = ((int)pVB->m_Format.m_Format & (int)VertexFormat::IEFormat::IE_VF_Normals);
        const bool hasTexCoords = ((int)pVB->m_Format.m_Format & (int)VertexFormat::IEFormat::IE_VF_TexCoords);

        // build polygon vertex 1
        std::int64_t vertexIndex = baseVertexIndex;
        std::int64_t normalIndex = hasNormal    ? baseNormalIndex : 0;
        std::int64_t uvIndex     = hasTexCoords ? baseUVIndex     : 0;

        // set vertex data
        vertex.m_X = vertices[vertexIndex];
        vertex.m_Y = vertices[vertexIndex + 1];
        vertex.m_Z = vertices[vertexIndex + 2];

        // vertex has a normal?
        if (hasNormal)
        {
            // set normal data
            normal.m_X = normals[normalIndex];
            normal.m_Y = normals[normalIndex + 1];
            normal.m_Z = normals[normalIndex + 2];
        }

        // vertex has UV texture coordinates?
        if (hasTexCoords)
        {
            // set texture data
            uv.m_X = uvs[uvIndex];
            uv.m_Y = uvs[uvIndex + 1];
        }

        // add the vertex to the buffer
        pVB->Add(&vertex,
                 &normal,
                 &uv,
                  vertexIndex,
                  m_fOnGetVertexColor);

        // build polygon vertex 2
        vertexIndex =                (faces[ i * faceStride]                 - 1) * 3;
        normalIndex = hasNormal    ? (faces[(i * faceStride) + normalOffset] - 1) * 3 : 0;
        uvIndex     = hasTexCoords ? (faces[(i * faceStride) + uvOffset]     - 1) * 2 : 0;

        // set vertex data
        vertex.m_X = vertices[vertexIndex];
        vertex.m_Y = vertices[vertexIndex + 1];
        vertex.m_Z = vertices[vertexIndex + 2];

        // vertex has a normal?
        if (hasNormal)
        {
            // set normal data
            normal.m_X = normals[normalIndex];
            normal.m_Y = normals[normalIndex + 1];
            normal.m_Z = normals[normalIndex + 2];
        }

        // vertex has UV texture coordinates?
        if (hasTexCoords)
        {
            // set texture data
            uv.m_X = uvs[uvIndex];
            uv.m_Y = uvs[uvIndex + 1];
        }

        // add the vertex to the buffer
        pVB->Add(&vertex,
                 &normal,
                 &uv,
                  vertexIndex,
                  m_fOnGetVertexColor);

        // build polygon vertex 3
        vertexIndex =                (faces[ (i + 1) * faceStride]                 - 1) * 3;
        normalIndex = hasNormal    ? (faces[((i + 1) * faceStride) + normalOffset] - 1) * 3 : 0;
        uvIndex     = hasTexCoords ? (faces[((i + 1) * faceStride) + uvOffset]     - 1) * 2 : 0;

        // set vertex data
        vertex.m_X = vertices[vertexIndex];
        vertex.m_Y = vertices[vertexIndex + 1];
        vertex.m_Z = vertices[vertexIndex + 2];

        // vertex has a normal?
        if (hasNormal)
        {
            // set normal data
            normal.m_X = normals[normalIndex];
            normal.m_Y = normals[normalIndex + 1];
            normal.m_Z = normals[normalIndex + 2];
        }

        // vertex has UV texture coordinates?
        if (hasTexCoords)
        {
            // set texture data
            uv.m_X = uvs[uvIndex];
            uv.m_Y = uvs[uvIndex + 1];
        }

        // add the vertex to the buffer
        pVB->Add(&vertex,
                 &normal,
                 &uv,
                  vertexIndex,
                  m_fOnGetVertexColor);
    }
}
//---------------------------------------------------------------------------
