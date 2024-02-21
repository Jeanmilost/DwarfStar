/****************************************************************************
 * ==> DWF_SceneItem -------------------------------------------------------*
 ****************************************************************************
 * Description : Basic scene item                                           *
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

#include "DWF_SceneItem.h"

using namespace DWF_Scene;

//---------------------------------------------------------------------------
// SceneItem
//---------------------------------------------------------------------------
SceneItem::SceneItem(const std::wstring& name) :
    m_Name(name)
{}
//---------------------------------------------------------------------------
SceneItem::~SceneItem()
{
    // iterate through colliders to delete, and delete each of them
    for (std::size_t i = 0; i < m_Colliders.size(); ++i)
        delete m_Colliders[i];

    // clear the colliders
    m_Colliders.clear();
}
//---------------------------------------------------------------------------
void SceneItem::AddCollider(DWF_Collider::Collider* pCollider)
{
    // search if collider already exists, in order to not add it twice
    for (std::size_t i = 0; i < m_Colliders.size(); ++i)
        if (m_Colliders[i] == pCollider)
            return;

    // add collider to item
    m_Colliders.push_back(pCollider);
}
//---------------------------------------------------------------------------
void SceneItem::DeleteCollider(DWF_Collider::Collider* pCollider)
{
    // iterate through colliders and find collider to delete
    for (std::size_t i = 0; i < m_Colliders.size(); ++i)
        // found collider to delete?
        if (m_Colliders[i] == pCollider)
        {
            DeleteColliderAt(i);
            return;
        }
}
//---------------------------------------------------------------------------
void SceneItem::DeleteColliderAt(std::size_t index)
{
    // is collider out of bounds?
    if (index >= m_Colliders.size())
        return;

    // delete collider from item
    delete m_Colliders[index];
    m_Colliders.erase(m_Colliders.begin() + index);
}
//---------------------------------------------------------------------------
DWF_Collider::Collider* SceneItem::GetCollider(std::size_t index) const
{
    // is index out of bounds?
    if (index >= m_Colliders.size())
        return nullptr;

    // get collider
    return m_Colliders[index];
}
//---------------------------------------------------------------------------
std::size_t SceneItem::GetColliderCount() const
{
    return m_Colliders.size();
}
//---------------------------------------------------------------------------
