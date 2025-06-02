/****************************************************************************
 * ==> DWF_SceneItemModel --------------------------------------------------*
 ****************************************************************************
 * Description : Scene item containing a model                              *
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

#include "DWF_SceneItemModel.h"

using namespace DWF_Scene;

//---------------------------------------------------------------------------
// SceneItem_Model
//---------------------------------------------------------------------------
SceneItem_Model::SceneItem_Model(const std::wstring& name) :
    SceneItem_ModelBase(name)
{}
//---------------------------------------------------------------------------
SceneItem_Model::~SceneItem_Model()
{}
//---------------------------------------------------------------------------
void SceneItem_Model::Render(const DWF_Math::Matrix4x4F&   viewMatrix,
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

    // draw the model
    for (std::size_t i = 0; i < m_pModel->m_Mesh.size(); ++i)
        pRenderer->Draw(*m_pModel->m_Mesh[i], GetMatrix(), m_pShader.get(), false);

    // unbind shader program
    m_pShader->Use(false);
}
//---------------------------------------------------------------------------
