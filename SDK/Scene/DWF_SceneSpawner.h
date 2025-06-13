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

#pragma once

// std
#include <functional>
#include <vector>

// classes
#include "DWF_SceneItem.h"
#include "DWF_Model.h"
#include "DWF_ModelFormat.h"
#include "DWF_Collider.h"

namespace DWF_Scene
{
    /**
    * Scene spawner
    *@author Jean-Milost Reymond
    */
    class Spawner
    {
        public:
            /**
            * Spawned item
            */
            struct IItem
            {
                SceneItem*   m_pModel    = nullptr;
                SceneItem*   m_pCollider = nullptr;
                std::wstring m_Name;
            };

            /**
            * Called to check if a new model should be spawn
            *@param arg1 - scene spawner
            *@return true if a new model should be spawn, otherwise false
            */
            typedef std::function<bool(Spawner*)> ITfOnDoSpawn;

            /**
            * Called to check if a new model was spawned
            *@param arg1 - scene spawner
            *@param arg2 - spawned model
            */
            typedef std::function<void(Spawner*, IItem*)> ITfOnSpawned;

            /**
            * Called to check if a model owned by the spawner manager should be deleted
            *@param arg1 - scene spawner
            *@param arg2 - spawned model
            *@return true if the model should be deleted, otherwise false
            */
            typedef std::function<bool(Spawner*, IItem*)> ITfOnDoDelete;

            /**
            * Called when the next position should be calculated for a model owned by the spawner manager
            *@param arg1 - scene spawner
            *@param arg2 - spawned model
            *@param arg3 - elapsed time since last calculated position
            */
            typedef std::function<void(Spawner*, IItem*, double)> ITfOnCalculateMotion;

            /**
            * Constructor
            *@param name - spawner name
            */
            Spawner(const std::wstring& name);

            virtual ~Spawner();

            /**
            * Gets the spawner name
            *@return spawner name
            */
            virtual inline std::wstring GetName() const;

            /**
            * Animates the particles
            *@param elapsedTime - elapsed time since last frame
            */
            virtual void Animate(double elapsedTime);

            /**
            * Sets the OnDoSpawn callback
            *@param fOnDoSpawn - callback function handle
            */
            void Set_OnDoSpawn(ITfOnDoSpawn fOnDoSpawn);

            /**
            * Sets the OnSpawned callback
            *@param fOnSpawned - callback function handle
            */
            void Set_OnSpawned(ITfOnSpawned fOnSpawned);

            /**
            * Sets the OnDoDelete callback
            *@param fOnDoDelete - callback function handle
            */
            void Set_OnDoDelete(ITfOnDoDelete fOnDoDelete);

            /**
            * Sets the OnCalculateMotion callback
            *@param fOnCalculateMotion - callback function handle
            */
            void Set_OnCalculateMotion(ITfOnCalculateMotion fOnCalculateMotion);

        private:
            typedef std::vector<IItem*> IItems;

            std::wstring         m_Name;
            IItems               m_Items;
            ITfOnDoSpawn         m_fOnDoSpawn         = nullptr;
            ITfOnSpawned         m_fOnSpawned         = nullptr;
            ITfOnDoDelete        m_fOnDoDelete        = nullptr;
            ITfOnCalculateMotion m_fOnCalculateMotion = nullptr;
    };

    //---------------------------------------------------------------------------
    // Spawner
    //---------------------------------------------------------------------------
    inline std::wstring Spawner::GetName() const
    {
        return m_Name;
    }
    //---------------------------------------------------------------------------
}
