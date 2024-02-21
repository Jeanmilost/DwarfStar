/****************************************************************************
 * ==> DWF_SceneAudioItem --------------------------------------------------*
 ****************************************************************************
 * Description : Scene audio item                                           *
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

// std
#include <string>
#include <vector>

// classes
#include "DWF_Sound.h"

#pragma once

namespace DWF_Scene
{
    /**
    * Scene audio item
    *@author Jean-Milost Reymond
    */
    class SceneAudioItem
    {
        public:
            /**
            * Constructor
            *@param name - item name
            */
            SceneAudioItem(const std::wstring& name);

            virtual ~SceneAudioItem();

            /**
            * Gets the item name
            *@return the item name
            */
            virtual inline std::wstring GetName() const;

            /**
            * Gets the sound
            *@return the sound
            */
            virtual inline DWF_Audio::Sound* GetSound() const;

            /**
            * Sets the sound
            *@param pSound - the sound to set
            *@note The sound will be deleted internally, don't delete it from outside
            */
            virtual inline void SetSound(DWF_Audio::Sound* pSound);

        private:
            std::wstring      m_Name;
            DWF_Audio::Sound* m_pSound = nullptr;
    };

    /**
    * Scene audio items
    *@author Jean-Milost Reymond
    */
    typedef std::vector<SceneAudioItem*> SceneAudioItems;

    //---------------------------------------------------------------------------
    // SceneAudioItem
    //---------------------------------------------------------------------------
    inline std::wstring SceneAudioItem::GetName() const
    {
        return m_Name;
    }
    //---------------------------------------------------------------------------
    inline DWF_Audio::Sound* SceneAudioItem::GetSound() const
    {
        return m_pSound;
    }
    //---------------------------------------------------------------------------
    inline void SceneAudioItem::SetSound(DWF_Audio::Sound* pSound)
    {
        if (m_pSound)
            delete m_pSound;

        m_pSound = pSound;
    }
    //---------------------------------------------------------------------------
}
