/****************************************************************************
 * ==> DWF_SceneItemStaticAsset --------------------------------------------*
 ****************************************************************************
 * Description : Scene item containing a static asset                       *
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

#include "DWF_SceneItemStaticAsset.h"

// classes
#include "DWF_SceneTimer.h"
#include "DWF_FBX.h"
#include "DWF_IQM.h"
#include "DWF_MDL.h"

using namespace DWF_Scene;

//---------------------------------------------------------------------------
// SceneItem_StaticAsset
//---------------------------------------------------------------------------
SceneItem_StaticAsset::SceneItem_StaticAsset(const std::wstring& name) :
    SceneItem_ModelBase(name)
{}
//---------------------------------------------------------------------------
SceneItem_StaticAsset::~SceneItem_StaticAsset()
{}
//---------------------------------------------------------------------------
void SceneItem_StaticAsset::Render(const DWF_Math::Matrix4x4F&   viewMatrix,
                                   const DWF_Renderer::Renderer* pRenderer) const
{
    // not visible? skip it
    if (!IsVisible())
        return;

    if (!pRenderer)
        return;

    if (!m_pShader)
        return;

    // bind shader program
    m_pShader->Use(true);

    // connect the view matrix to the shader
    pRenderer->ConnectViewMatrixToShader(m_pShader.get(), viewMatrix);

    DWF_Model::ModelFormat* pModelFormat = m_pModelFormat.get();

    // draw the model
    DrawModel(pModelFormat, m_pShader.get(), pRenderer);

    // unbind shader program
    m_pShader->Use(false);
}
//---------------------------------------------------------------------------
void SceneItem_StaticAsset::DrawModel(const DWF_Model::ModelFormat* pModelFormat,
                                      const DWF_Renderer::Shader*   pShader,
                                      const DWF_Renderer::Renderer* pRenderer) const
{
    if (!pModelFormat)
        return;

    if (!pShader)
        return;

    if (!pRenderer)
        return;

    // get the model
    const DWF_Model::Model* pModel = pModelFormat->GetModel();

    // no model to draw?
    if (!pModel)
        return;

    const std::size_t meshCount = pModel->m_Mesh.size();

    // iterate through the meshes to draw
    for (std::size_t i = 0; i < meshCount; ++i)
        // draw the model mesh
        pRenderer->Draw(*pModel->m_Mesh[i], GetMatrix(), pShader, false);
}
//---------------------------------------------------------------------------
