/****************************************************************************
 * ==> DWF_Voxel -----------------------------------------------------------*
 ****************************************************************************
 * Description: Voxel                                                       *
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

#include "DWF_Voxel.h"

using namespace DWF_Voxel;

//---------------------------------------------------------------------------
// Voxel
//---------------------------------------------------------------------------
Voxel::Voxel(DWF_Model::Model* pModel, DWF_Renderer::Shader* pShader, DWF_Renderer::Renderer* pRenderer) :
    m_pModel(pModel),
    m_pShader(pShader),
    m_pRenderer(pRenderer)
{
    m_pBox = std::make_unique<DWF_Geometry::Box>(DWF_Math::Vector3F(-0.5f, -0.5f, -0.5f),
                                                 DWF_Math::Vector3F( 0.5f,  0.5f,  0.5f));
}
//---------------------------------------------------------------------------
Voxel::~Voxel()
{}
//---------------------------------------------------------------------------
DWF_Math::Vector3F Voxel::GetPos() const
{
    return m_Pos;
}
//---------------------------------------------------------------------------
void Voxel::SetPos(const DWF_Math::Vector3F& pos)
{
    m_Pos = pos;
}
//---------------------------------------------------------------------------
DWF_Geometry::Box* Voxel::GetBoundingBox(const DWF_Math::Matrix4x4F& matrix) const
{
    if (!m_pBox)
        return nullptr;

    return m_pBox->ApplyMatrix(matrix);
}
//---------------------------------------------------------------------------
void Voxel::Draw(const DWF_Math::Matrix4x4F& matrix) const
{
    if (!m_pModel)
        return;

    if (!m_pShader)
        return;

    if (!m_pRenderer)
        return;

    // enable the shader
    m_pShader->Use(true);

    // draw the Voxel
    for (auto pMesh : m_pModel->m_Mesh)
        m_pRenderer->Draw(*pMesh, matrix, m_pShader, false);

    // disable the shader
    m_pShader->Use(false);
}
//---------------------------------------------------------------------------
