/****************************************************************************
 * ==> DWF_SceneSpawner ----------------------------------------------------*
 ****************************************************************************
 * Description: Scene spawner                                               *
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

#include "DWF_SceneSpawner.h"

// classes
#include "DWF_Scene.h"

using namespace DWF_Scene;

//---------------------------------------------------------------------------
// Spawner
//---------------------------------------------------------------------------
Spawner::Spawner(const std::wstring& name) :
    m_Name(name)
{}
//---------------------------------------------------------------------------
Spawner::~Spawner()
{
    for (std::size_t i = 0; i < m_Items.size(); ++i)
        delete m_Items[i];

    /*REM
    if (m_pCollider)
        delete m_pCollider;
    */
}
//---------------------------------------------------------------------------
void Spawner::Animate(Scene* pScene, double elapsedTime)
{
    if (!pScene)
        return;

    // do add a new item?
    if (m_fOnDoSpawn && m_fOnDoSpawn(this))
    {
        std::unique_ptr<IItem> pItem = std::make_unique<IItem>();

        // configure the newly added item
        if (m_fOnSpawned)
            m_fOnSpawned(this, pItem.get());

        m_Items.push_back(pItem.get());

        pItem.release();
    }

    if (m_Items.size())
    {
        std::size_t index = m_Items.size() - 1;

        // revert iterate through spawned items, thus they can be deleted if required
        do
        {
            // do delete the item, or calculate its motion?
            if (m_fOnDoDelete && m_fOnDoDelete(this, m_Items[index]))
            {
                // delete the collider item from the scene
                if (m_Items[index]->m_pCollider)
                    pScene->Delete(m_Items[index]->m_pCollider);

                // delete the model item from the scene
                if (m_Items[index]->m_pModel)
                    pScene->Delete(m_Items[index]->m_pModel);

                // delete the item at index
                delete m_Items[index];
                m_Items.erase(m_Items.begin() + index);
            }
            else
            if (m_fOnCalculateMotion)
                m_fOnCalculateMotion(this, m_Items[index], elapsedTime);

            if (index == 0)
                break;

            --index;
        }
        while (1);
    }
}
//---------------------------------------------------------------------------
void Spawner::Set_OnDoSpawn(ITfOnDoSpawn fOnDoSpawn)
{
    m_fOnDoSpawn = fOnDoSpawn;
}
//---------------------------------------------------------------------------
void Spawner::Set_OnSpawned(ITfOnSpawned fOnSpawned)
{
    m_fOnSpawned = fOnSpawned;
}
//---------------------------------------------------------------------------
void Spawner::Set_OnDoDelete(ITfOnDoDelete fOnDoDelete)
{
    m_fOnDoDelete = fOnDoDelete;
}
//---------------------------------------------------------------------------
void Spawner::Set_OnCalculateMotion(ITfOnCalculateMotion fOnCalculateMotion)
{
    m_fOnCalculateMotion = fOnCalculateMotion;
}
//---------------------------------------------------------------------------
