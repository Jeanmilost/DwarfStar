/****************************************************************************
 * ==> DWF_SceneItemAnimAsset ----------------------------------------------*
 ****************************************************************************
 * Description : Scene item containing an animated asset                    *
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

#include "DWF_SceneItemAnimAsset.h"

// classes
#include "DWF_SceneTimer.h"
#include "DWF_FBX.h"
#include "DWF_IQM.h"
#include "DWF_MDL.h"

using namespace DWF_Scene;

//---------------------------------------------------------------------------
// SceneItem_AnimAsset::IAnimDesc
//---------------------------------------------------------------------------
SceneItem_AnimAsset::IAnimDesc::IAnimDesc()
{}
//---------------------------------------------------------------------------
SceneItem_AnimAsset::IAnimDesc::~IAnimDesc()
{}
//---------------------------------------------------------------------------
// SceneItem_AnimAsset
//---------------------------------------------------------------------------
SceneItem_AnimAsset::SceneItem_AnimAsset(const std::wstring& name) :
    SceneItem_ModelBase(name)
{}
//---------------------------------------------------------------------------
SceneItem_AnimAsset::~SceneItem_AnimAsset()
{
    if (m_ShaderIsLocal && m_pShader)
        delete m_pShader;

    // delete all animated models
    for (std::size_t i = 0; i < m_Animations.size(); ++i)
        delete m_Animations[i];
}
//---------------------------------------------------------------------------
void SceneItem_AnimAsset::AddAnim(std::size_t animSetIndex,
                                  std::size_t frameStart,
                                  std::size_t frameCount,
                                  double      frameDuration,
                                  bool        loop)
{
    // create new animation description
    std::unique_ptr<IAnimDesc> pAnimDesc = std::make_unique<IAnimDesc>();
    pAnimDesc->m_AnimSetIndex            = animSetIndex;
    pAnimDesc->m_FrameStart              = frameStart;
    pAnimDesc->m_FrameCount              = frameCount;
    pAnimDesc->m_FrameDuration           = frameDuration;
    pAnimDesc->m_Loop                    = loop;

    // add animation to item
    m_Animations.push_back(pAnimDesc.get());
    pAnimDesc.release();
}
//---------------------------------------------------------------------------
void SceneItem_AnimAsset::AddAnim(const std::shared_ptr<DWF_Model::AnimModelFormat>& pModelFormat,
                                        std::size_t                                  animSetIndex,
                                        std::size_t                                  frameCount,
                                        double                                       frameDuration,
                                        bool                                         loop)
{
    // create new animation description
    std::unique_ptr<IAnimDesc> pAnimDesc = std::make_unique<IAnimDesc>();
    pAnimDesc->m_pModelFormat            = pModelFormat;
    pAnimDesc->m_AnimSetIndex            = animSetIndex;
    pAnimDesc->m_FrameCount              = frameCount;
    pAnimDesc->m_FrameDuration           = frameDuration;
    pAnimDesc->m_Loop                    = loop;

    // search if animation already exists, in order to not add it twice
    for (std::size_t i = 0; i < m_Animations.size(); ++i)
        if (m_Animations[i]->m_pModelFormat == pModelFormat)
            return;

    // add animation to item
    m_Animations.push_back(pAnimDesc.get());
    pAnimDesc.release();
}
//---------------------------------------------------------------------------
void SceneItem_AnimAsset::DeleteAnim(const std::shared_ptr<DWF_Model::AnimModelFormat>& pModelFormat)
{
    // iterate through animations and find animation to delete
    for (std::size_t i = 0; i < m_Animations.size(); ++i)
        // found animation to delete?
        if (m_Animations[i]->m_pModelFormat == pModelFormat)
        {
            DeleteAnimAt(i);
            return;
        }
}
//---------------------------------------------------------------------------
void SceneItem_AnimAsset::DeleteAnimAt(std::size_t index)
{
    // is animation out of bounds?
    if (index >= m_Animations.size())
        return;

    // delete animation from item
    delete m_Animations[index];
    m_Animations.erase(m_Animations.begin() + index);
}
//---------------------------------------------------------------------------
SceneItem_AnimAsset::IAnimDesc* SceneItem_AnimAsset::GetAnim(std::size_t index) const
{
    // is index out of bounds?
    if (index >= m_Animations.size())
        return nullptr;

    // get animation
    return m_Animations[index];
}
//---------------------------------------------------------------------------
std::size_t SceneItem_AnimAsset::GetAnimCount() const
{
    return m_Animations.size();
}
//---------------------------------------------------------------------------
std::size_t SceneItem_AnimAsset::GetSelectedAnim() const
{
    return m_Index;
}
//---------------------------------------------------------------------------
void SceneItem_AnimAsset::SelectAnim(std::size_t index)
{
    // is index out of bounds?
    if (index >= m_Animations.size())
        return;

    m_Index = index;

    // reset the animation once selected
    ResetAnim(m_Index);
}
//---------------------------------------------------------------------------
void SceneItem_AnimAsset::SelectAnimSet(std::size_t index, std::size_t animSetIndex)
{
    // is index out of bounds?
    if (index >= m_Animations.size())
        return;

    m_Animations[index]->m_AnimSetIndex = animSetIndex;

    // reset the animation once selected
    ResetAnim(index);
}
//---------------------------------------------------------------------------
void SceneItem_AnimAsset::ResetAnim(std::size_t index)
{
    // is index out of bounds?
    if (index >= m_Animations.size())
        return;

    // restart the timer associated with the model
    DWF_Scene::Timer::GetInstance()->StartTimerForItem
            (m_Animations[index]->m_pModelFormat ? m_Animations[index]->m_pModelFormat.get() : m_pModelFormat.get());

    // reset the frame count
    m_Animations[index]->m_FrameIndex     = 0;
    m_Animations[index]->m_FrameTimeStamp = 0.0;
    m_Animations[index]->m_FrameAnimTime  = 0.0;
}
//---------------------------------------------------------------------------
void SceneItem_AnimAsset::Render(const DWF_Math::Matrix4x4F&   viewMatrix,
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

    DWF_Model::AnimModelFormat* pModelFormat =
            m_Animations[m_Index]->m_pModelFormat ? m_Animations[m_Index]->m_pModelFormat.get() : m_pModelFormat.get();

    // get elapsed time
    const double timeStamp                   = DWF_Scene::Timer::GetInstance()->GetElapsedTimeForItem(pModelFormat);
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
    DrawModel(pModelFormat,
              m_Animations[m_Index]->m_AnimSetIndex,
              m_Animations[m_Index]->m_FrameStart + m_Animations[m_Index]->m_FrameIndex,
              m_Animations[m_Index]->m_FrameCount,
              elapsedTime,
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
void SceneItem_AnimAsset::Set_OnFrame(ITfOnFrame fHandler)
{
    m_fOnFrame = fHandler;
}
//---------------------------------------------------------------------------
void SceneItem_AnimAsset::Set_OnEndReached(ITfOnEndReached fHandler)
{
    m_fOnEndReached = fHandler;
}
//---------------------------------------------------------------------------
void SceneItem_AnimAsset::DrawModel(const DWF_Model::AnimModelFormat* pModelFormat,
                                          std::size_t                 animSetIndex,
                                          std::size_t                 frameIndex,
                                          std::size_t                 frameCount,
                                          double                      elapsedTime,
                                    const DWF_Renderer::Shader*       pShader,
                                    const DWF_Renderer::Renderer*     pRenderer) const
{
    if (!pModelFormat)
        return;

    if (!pShader)
        return;

    if (!pRenderer)
        return;

    // get the model
    const DWF_Model::Model* pModel = pModelFormat->GetModel((int)animSetIndex, (int)frameCount, (int)frameIndex);

    // no model to draw?
    if (!pModel)
        return;

    const std::size_t meshCount = pModel->m_Mesh.size();

    // iterate through the meshes to draw
    for (std::size_t i = 0; i < meshCount; ++i)
        // draw the model mesh
        pRenderer->Draw(*pModel->m_Mesh[i], GetMatrix(), pShader, false);

    // draw the skeleton
    if (m_DrawSkeleton && pModelFormat->GetFormat() != DWF_Model::ModelFormat::IEFormat::IE_F_MDL)
        DrawBone(pModelFormat, pModel, pModel->m_pSkeleton, animSetIndex, frameIndex, frameCount, elapsedTime, pShader, pRenderer);
}
//---------------------------------------------------------------------------
void SceneItem_AnimAsset::DrawBone(const DWF_Model::AnimModelFormat* pModelFormat,
                                   const DWF_Model::Model*           pModel,
                                   const DWF_Model::Model::IBone*    pBone,
                                         std::size_t                 animSetIndex,
                                         std::size_t                 frameIndex,
                                         std::size_t                 frameCount,
                                         double                      elapsedTime,
                                   const DWF_Renderer::Shader*       pShader,
                                   const DWF_Renderer::Renderer*     pRenderer) const
{
    if (!pModelFormat)
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
            switch (pModelFormat->GetFormat())
            {
                case DWF_Model::ModelFormat::IEFormat::IE_F_FBX:
                    static_cast<const DWF_Model::FBX*>(pModelFormat)->GetBoneAnimMatrix(pBone,
                                                                                        pModel->m_AnimationSet[animSetIndex],
                                                                                        elapsedTime,
                                                                                        DWF_Math::Matrix4x4F::Identity(),
                                                                                        topMatrix);
                    break;

                case DWF_Model::ModelFormat::IEFormat::IE_F_IQM:
                    static_cast<const DWF_Model::IQM*>(pModelFormat)->GetBoneAnimMatrix(pBone,
                                                                                        pModel->m_AnimationSet[animSetIndex],
                                                                                        frameIndex,
                                                                                        DWF_Math::Matrix4x4F::Identity(),
                                                                                        topMatrix);
                    break;

                default:
                    return;
            }

        DWF_Math::Matrix4x4F bottomMatrix;

        // get the bone bottom matrix
        if (pModel->m_PoseOnly)
            pModel->GetBoneMatrix(pChild, DWF_Math::Matrix4x4F::Identity(), bottomMatrix);
        else
        if (pModel->m_AnimationSet.size())
            switch (pModelFormat->GetFormat())
            {
                case DWF_Model::ModelFormat::IEFormat::IE_F_FBX:
                    static_cast<const DWF_Model::FBX*>(pModelFormat)->GetBoneAnimMatrix(pChild,
                                                                                        pModel->m_AnimationSet[animSetIndex],
                                                                                        elapsedTime,
                                                                                        DWF_Math::Matrix4x4F::Identity(),
                                                                                        bottomMatrix);
                    break;

                case DWF_Model::ModelFormat::IEFormat::IE_F_IQM:
                    static_cast<const DWF_Model::IQM*>(pModelFormat)->GetBoneAnimMatrix(pChild,
                                                                                        pModel->m_AnimationSet[animSetIndex],
                                                                                        frameIndex,
                                                                                        DWF_Math::Matrix4x4F::Identity(),
                                                                                        bottomMatrix);
                    break;

                default:
                    return;
            }

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
        DrawBone(pModelFormat, pModel, pChild, animSetIndex, frameIndex, frameCount, elapsedTime, pShader, pRenderer);
    }
}
//---------------------------------------------------------------------------
