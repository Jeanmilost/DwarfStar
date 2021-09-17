/****************************************************************************
 * ==> DWF_Model -----------------------------------------------------------*
 ****************************************************************************
 * Description:  Generic 3D model                                           *
 * Contained in: Model                                                      *
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

#include "DWF_Model.h"

// dwarfstar
#include "DWF_Quaternion.h"

//---------------------------------------------------------------------------
// DWF_Model::IBone
//---------------------------------------------------------------------------
DWF_Model::IBone::IBone()
{}
//---------------------------------------------------------------------------
DWF_Model::IBone::~IBone()
{
    const std::size_t count = m_Children.size();

    for (std::size_t i = 0; i < count; ++i)
        delete m_Children[i];
}
//---------------------------------------------------------------------------
// DWF_Model::IWeightInfluence
//---------------------------------------------------------------------------
DWF_Model::IWeightInfluence::IWeightInfluence()
{}
//---------------------------------------------------------------------------
DWF_Model::IWeightInfluence::~IWeightInfluence()
{}
//---------------------------------------------------------------------------
// DWF_Model::ISkinWeights
//---------------------------------------------------------------------------
DWF_Model::ISkinWeights::ISkinWeights()
{}
//---------------------------------------------------------------------------
DWF_Model::ISkinWeights::~ISkinWeights()
{
    const std::size_t count = m_WeightInfluences.size();

    for (std::size_t i = 0; i < count; ++i)
        delete m_WeightInfluences[i];
}
//---------------------------------------------------------------------------
// DWF_Model::IDeformers
//---------------------------------------------------------------------------
DWF_Model::IDeformers::IDeformers()
{}
//---------------------------------------------------------------------------
DWF_Model::IDeformers::~IDeformers()
{
    const std::size_t count = m_SkinWeights.size();

    for (std::size_t i = 0; i < count; ++i)
        delete m_SkinWeights[i];
}
//---------------------------------------------------------------------------
// DWF_Model::IAnimationKey
//---------------------------------------------------------------------------
DWF_Model::IAnimationKey::IAnimationKey()
{}
//---------------------------------------------------------------------------
DWF_Model::IAnimationKey::~IAnimationKey()
{}
//---------------------------------------------------------------------------
// DWF_Model::IAnimationKeys
//---------------------------------------------------------------------------
DWF_Model::IAnimationKeys::IAnimationKeys()
{}
//---------------------------------------------------------------------------
DWF_Model::IAnimationKeys::~IAnimationKeys()
{
    const std::size_t count = m_Keys.size();

    for (std::size_t i = 0; i < count; ++i)
        delete m_Keys[i];
}
//---------------------------------------------------------------------------
// DWF_Model::IAnimation
//---------------------------------------------------------------------------
DWF_Model::IAnimation::IAnimation()
{}
//---------------------------------------------------------------------------
DWF_Model::IAnimation::~IAnimation()
{
    const std::size_t count = m_Keys.size();

    for (std::size_t i = 0; i < count; ++i)
        delete m_Keys[i];
}
//---------------------------------------------------------------------------
// DWF_Model::IAnimationSet
//---------------------------------------------------------------------------
DWF_Model::IAnimationSet::IAnimationSet()
{}
//---------------------------------------------------------------------------
DWF_Model::IAnimationSet::~IAnimationSet()
{
    const std::size_t count = m_Animations.size();

    for (std::size_t i = 0; i < count; ++i)
        delete m_Animations[i];
}
//---------------------------------------------------------------------------
// DWF_Model
//---------------------------------------------------------------------------
DWF_Model::DWF_Model() :
    DWF_Drawable()
{}
//---------------------------------------------------------------------------
DWF_Model::~DWF_Model()
{
    const std::size_t meshCount = m_Mesh.size();

    for (std::size_t i = 0; i < meshCount; ++i)
        delete m_Mesh[i];
}
//---------------------------------------------------------------------------
DWF_Model::IBone* DWF_Model::FindBone(IBone* pBone, const std::string& name) const
{
    // no bone?
    if (!pBone)
        return nullptr;

    // found the bone?
    if (!pBone->m_Name.empty() && pBone->m_Name == name)
        return pBone;

    // iterate through the bone children
    for (std::size_t i = 0; i < pBone->m_Children.size(); ++i)
    {
        // search in next children bone
        IBone* pChildBone = FindBone(pBone->m_Children[i], name);

        // found the bone?
        if (pChildBone)
            return pChildBone;
    }

    return nullptr;
}
//---------------------------------------------------------------------------
void DWF_Model::GetBoneMatrix(const IBone* pBone, const DWF_Matrix4x4F& initialMatrix, DWF_Matrix4x4F& matrix) const
{
    // no bone?
    if (!pBone)
        return;

    // set the output matrix as identity
    matrix = DWF_Matrix4x4F::Identity();

    // iterate through bones
    while (pBone)
    {
        // get the previously stacked matrix as base to calculate the new one
        const DWF_Matrix4x4F localMatrix = matrix;

        // stack the previously calculated matrix with the current bone one
        matrix = localMatrix.Multiply(pBone->m_Matrix);

        // go to parent bone
        pBone = pBone->m_pParent;
    }

    // initial matrix provided?
    if (!initialMatrix.IsIdentity())
    {
        // get the previously stacked matrix as base to calculate the new one
        const DWF_Matrix4x4F localMatrix = matrix;

        // stack the previously calculated matrix with the initial one
        matrix = localMatrix.Multiply(initialMatrix);
    }
}
//---------------------------------------------------------------------------
void DWF_Model::Draw(const DWF_Renderer& renderer, const DWF_Matrix4x4F& matrix, const DWF_Shader& shader) const
{
    const std::size_t meshCount = m_Mesh.size();

    // iterate through the meshes to draw
    for (std::size_t i = 0; i < meshCount; ++i)
        // draw the model mesh
        renderer.Draw(*m_Mesh[i], matrix, &shader);
}
//---------------------------------------------------------------------------
