/****************************************************************************
 * ==> DWF_SceneItemAnimation ----------------------------------------------*
 ****************************************************************************
 * Description : Scene item containing an animation                         *
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

#include "DWF_SceneItemAnimation.h"

// classes
#include "DWF_SceneTimer.h"

using namespace DWF_Scene;

//---------------------------------------------------------------------------
// SceneItem_Animation::IAnimDesc
//---------------------------------------------------------------------------
SceneItem_Animation::IAnimDesc::IAnimDesc()
{}
//---------------------------------------------------------------------------
SceneItem_Animation::IAnimDesc::~IAnimDesc()
{
    if (m_pModel)
        delete m_pModel;
}
//---------------------------------------------------------------------------
// SceneItem_Animation
//---------------------------------------------------------------------------
SceneItem_Animation::SceneItem_Animation(const std::wstring& name) :
    SceneItem_ModelBase(name)
{}
//---------------------------------------------------------------------------
SceneItem_Animation::~SceneItem_Animation()
{
    if (m_ShaderIsLocal && m_pShader)
        delete m_pShader;

    // delete all animated models
    for (std::size_t i = 0; i < m_Animations.size(); ++i)
        delete m_Animations[i];
}
//---------------------------------------------------------------------------
void SceneItem_Animation::AddAnim(DWF_Model::IQM* pAnim,
                                  std::size_t     animSetIndex,
                                  std::size_t     frameCount,
                                  double          frameDuration,
                                  bool            loop)
{
    // create new animation description
    std::unique_ptr<IAnimDesc> pAnimDesc = std::make_unique<IAnimDesc>();
    pAnimDesc->m_pModel                  = pAnim;
    pAnimDesc->m_AnimSetIndex            = animSetIndex;
    pAnimDesc->m_FrameCount              = frameCount;
    pAnimDesc->m_FrameDuration           = frameDuration;
    pAnimDesc->m_Loop                    = loop;

    // search if animation already exists, in order to not add it twice
    for (std::size_t i = 0; i < m_Animations.size(); ++i)
        if (m_Animations[i]->m_pModel == pAnim)
            return;

    // add animation to item
    m_Animations.push_back(pAnimDesc.get());
    pAnimDesc.release();
}
//---------------------------------------------------------------------------
void SceneItem_Animation::DeleteAnim(DWF_Model::IQM* pAnim)
{
    // iterate through animations and find animation to delete
    for (std::size_t i = 0; i < m_Animations.size(); ++i)
        // found animation to delete?
        if (m_Animations[i]->m_pModel == pAnim)
        {
            DeleteAnimAt(i);
            return;
        }
}
//---------------------------------------------------------------------------
void SceneItem_Animation::DeleteAnimAt(std::size_t index)
{
    // is animation out of bounds?
    if (index >= m_Animations.size())
        return;

    // delete animation from item
    delete m_Animations[index];
    m_Animations.erase(m_Animations.begin() + index);
}
//---------------------------------------------------------------------------
SceneItem_Animation::IAnimDesc* SceneItem_Animation::GetAnim(std::size_t index) const
{
    // is index out of bounds?
    if (index >= m_Animations.size())
        return nullptr;

    // get animation
    return m_Animations[index];
}
//---------------------------------------------------------------------------
std::size_t SceneItem_Animation::GetAnimCount() const
{
    return m_Animations.size();
}
//---------------------------------------------------------------------------
std::size_t SceneItem_Animation::GetSelectedAnim() const
{
    return m_Index;
}
//---------------------------------------------------------------------------
void SceneItem_Animation::SelectAnim(std::size_t index)
{
    // is index out of bounds?
    if (index >= m_Animations.size())
        return;

    m_Index = index;

    // reset the animation once selected
    ResetAnim(m_Index);
}
//---------------------------------------------------------------------------
void SceneItem_Animation::SelectAnimSet(std::size_t index, std::size_t animSetIndex)
{
    // is index out of bounds?
    if (index >= m_Animations.size())
        return;

    m_Animations[index]->m_AnimSetIndex = animSetIndex;

    // reset the animation once selected
    ResetAnim(index);
}
//---------------------------------------------------------------------------
void SceneItem_Animation::ResetAnim(std::size_t index)
{
    // is index out of bounds?
    if (index >= m_Animations.size())
        return;

    // restart the timer associated with the model
    DWF_Scene::Timer::GetInstance()->StartTimerForItem(m_Animations[index]->m_pModel);

    // reset the frame count
    m_Animations[index]->m_FrameIndex     = 0;
    m_Animations[index]->m_FrameTimeStamp = 0.0;
    m_Animations[index]->m_FrameAnimTime  = 0.0;
}
//---------------------------------------------------------------------------
void SceneItem_Animation::Render(const DWF_Math::Matrix4x4F&   viewMatrix,
                                 const DWF_Renderer::Renderer* pRenderer) const
{
    // not visible? skip it
    if (!IsVisible())
        return;

    if (!pRenderer)
        return;

    if (!m_pShader)
        return;

    if (m_Index >= m_Animations.size())
        return;

    // bind shader program
    m_pShader->Use(true);

    // connect the view matrix to the shader
    pRenderer->ConnectViewMatrixToShader(m_pShader, viewMatrix);

    // get elapsed time
    const double timeStamp                   = DWF_Scene::Timer::GetInstance()->GetElapsedTimeForItem(m_Animations[m_Index]->m_pModel);
    const double elapsedTime                 = timeStamp - m_Animations[m_Index]->m_FrameTimeStamp;
    m_Animations[m_Index]->m_FrameTimeStamp  = timeStamp;
    m_Animations[m_Index]->m_FrameAnimTime  += (elapsedTime / 1500.0);

    bool endReached;

    // calculate the current frame index
    m_Animations[m_Index]->m_FrameIndex =
            DWF_Scene::Timer::GetInstance()->GetNextFrame(m_Animations[m_Index]->m_FrameAnimTime,
                                                          m_Animations[m_Index]->m_FrameIndex,
                                                          m_Animations[m_Index]->m_FrameCount,
                                                          m_Animations[m_Index]->m_FrameDuration,
                                                          m_Animations[m_Index]->m_Loop,
                                                          endReached);

    // draw the model
    DrawIQM(m_Animations[m_Index]->m_pModel,
            m_Animations[m_Index]->m_AnimSetIndex,
            m_Animations[m_Index]->m_FrameIndex,
            m_Animations[m_Index]->m_FrameCount,
            m_pShader,
            pRenderer);

    // unbind shader program
    m_pShader->Use(false);

    // end reached?
    if (endReached)
    {
        // notify that end was reached
        if (m_fOnEndReached)
            m_fOnEndReached(this, m_Animations[m_Index]);
    }
    else
    // notify that the next frame was processed
    if (m_fOnFrame)
        m_fOnFrame(this, m_Animations[m_Index]);
}
//---------------------------------------------------------------------------
void SceneItem_Animation::Set_OnFrame(ITfOnFrame fHandler)
{
    m_fOnFrame = fHandler;
}
//---------------------------------------------------------------------------
void SceneItem_Animation::Set_OnEndReached(ITfOnEndReached fHandler)
{
    m_fOnEndReached = fHandler;
}
//---------------------------------------------------------------------------
void SceneItem_Animation::DrawIQM(const DWF_Model::IQM*         pIqm,
                                        std::size_t             animSetIndex,
                                        std::size_t             frameIndex,
                                        std::size_t             frameCount,
                                  const DWF_Renderer::Shader*   pShader,
                                  const DWF_Renderer::Renderer* pRenderer) const
{
    if (!pIqm)
        return;

    if (!pShader)
        return;

    if (!pRenderer)
        return;

    // get the model
    const DWF_Model::Model* pModel = pIqm->GetModel((int)animSetIndex, (int)frameCount, (int)frameIndex);

    // no model to draw?
    if (!pModel)
        return;

    const std::size_t meshCount = pModel->m_Mesh.size();

    // iterate through the meshes to draw
    for (std::size_t i = 0; i < meshCount; ++i)
        // draw the model mesh
        pRenderer->Draw(*pModel->m_Mesh[i], GetMatrix(), pShader, false);

    // draw the skeleton
    if (m_DrawSkeleton)
        DrawBone(pIqm, pModel, pModel->m_pSkeleton, animSetIndex, frameIndex, frameCount, pShader, pRenderer);
}
//---------------------------------------------------------------------------
void SceneItem_Animation::DrawBone(const DWF_Model::IQM*          pIqm,
                                   const DWF_Model::Model*        pModel,
                                   const DWF_Model::Model::IBone* pBone,
                                         std::size_t              animSetIndex,
                                         std::size_t              frameIndex,
                                         std::size_t              frameCount,
                                   const DWF_Renderer::Shader*    pShader,
                                   const DWF_Renderer::Renderer*  pRenderer) const
{
    if (!pIqm)
        return;

    if (!pModel)
        return;

    if (!pBone)
        return;

    if (!pShader)
        return;

    if (!pRenderer)
        return;

    // iterate through bone children
    for (std::size_t i = 0; i < pBone->m_Children.size(); ++i)
    {
        // get next child bone
        DWF_Model::Model::IBone* pChild = pBone->m_Children[i];
        DWF_Math::Matrix4x4F     topMatrix;

        // get the bone top matrix
        if (pModel->m_PoseOnly)
            pModel->GetBoneMatrix(pBone, DWF_Math::Matrix4x4F::Identity(), topMatrix);
        else
        if (pModel->m_AnimationSet.size())
            pIqm->GetBoneAnimMatrix(pBone,
                                    pModel->m_AnimationSet[animSetIndex],
                                    frameIndex,
                                    DWF_Math::Matrix4x4F::Identity(),
                                    topMatrix);

        DWF_Math::Matrix4x4F bottomMatrix;

        // get the bone bottom matrix
        if (pModel->m_PoseOnly)
            pModel->GetBoneMatrix(pChild, DWF_Math::Matrix4x4F::Identity(), bottomMatrix);
        else
        if (pModel->m_AnimationSet.size())
            pIqm->GetBoneAnimMatrix(pChild,
                                    pModel->m_AnimationSet[animSetIndex],
                                    frameIndex,
                                    DWF_Math::Matrix4x4F::Identity(),
                                    bottomMatrix);

        // disable the depth test, to allow the bone to be always visible
        pRenderer->EnableDepthTest(false);

        // draw the bone
        pRenderer->DrawLine(DWF_Math::Vector3F(topMatrix.m_Table[3][0], topMatrix.m_Table[3][1], topMatrix.m_Table[3][2]),
                            DWF_Math::Vector3F(bottomMatrix.m_Table[3][0], bottomMatrix.m_Table[3][1], bottomMatrix.m_Table[3][2]),
                            DWF_Model::ColorF(0.25f, 0.12f, 0.1f, 1.0f),
                            DWF_Model::ColorF(0.95f, 0.06f, 0.15f, 1.0f),
                            GetMatrix(),
                            pShader);

        // re-enable the depth test
        pRenderer->EnableDepthTest(true);

        // draw recursively the children bones
        DrawBone(pIqm, pModel, pChild, animSetIndex, frameIndex, frameCount, pShader, pRenderer);
    }
}
//---------------------------------------------------------------------------
