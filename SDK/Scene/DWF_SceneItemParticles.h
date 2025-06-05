/****************************************************************************
 * ==> DWF_SceneItemParticles ----------------------------------------------*
 ****************************************************************************
 * Description : Scene item containing a particles system                   *
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
#include <functional>
#include <vector>

// classes
#include "DWF_SceneItem.h"
#include "DWF_Particles.h"
#include "DWF_Shader.h"
#include "DWF_Renderer.h"

#pragma once

namespace DWF_Scene
{
    /**
    * Scene item containing a particles system
    *@author Jean-Milost Reymond
    */
    class SceneItem_Particles : public SceneItem
    {
        public:
            /**
            * Constructor
            *@param name - item name
            */
            SceneItem_Particles(const std::wstring& name);

            virtual ~SceneItem_Particles();

            /**
            * Sets the particle system to use
            *@param pParticles - the particle system to set
            */
            virtual inline void SetParticles(const std::shared_ptr<DWF_Particles::Particles>& pParticles);

            /**
            * Gets position
            *@return position
            */
            virtual DWF_Math::Vector3F GetPos() const { return DWF_Math::Vector3F(); }

            /**
            * Sets position
            *@param value - position
            */
            virtual void SetPos(const DWF_Math::Vector3F& value) {};

            /**
            * Gets roll angle
            *@return roll angle (i.e. rotation on the x axis)
            */
            virtual float GetRoll() const { return 0.0f; }

            /**
            * Sets roll angle
            *@param value - roll angle (i.e. rotation on the x axis)
            */
            virtual void SetRoll(float value) {};

            /**
            * Gets pitch angle
            *@return pitch angle (i.e. rotation on the y axis)
            */
            virtual float GetPitch() const { return 0.0f; }

            /**
            * Sets pitch angle
            *@param value - pitch angle (i.e. rotation on the y axis)
            */
            virtual void SetPitch(float value) {};

            /**
            * Gets yaw angle
            *@return yaw angle (i.e. rotation on the z axis)
            */
            virtual float GetYaw() const { return 0.0f; }

            /**
            * Sets yaw angle
            *@param value - yaw angle (i.e. rotation on the z axis)
            */
            virtual void SetYaw(float value) {};

            /**
            * Sets rotation
            *@param roll - roll angle (i.e. rotation on the x axis)
            *@param pitch - pitch angle (i.e. rotation on the y axis)
            *@param yaw - yaw angle (i.e. rotation on the z axis)
            */
            virtual void SetRotation(float roll, float pitch, float yaw) {};

            /**
            * Gets scale factor
            *@return scale factor
            */
            virtual DWF_Math::Vector3F GetScale() const { return DWF_Math::Vector3F(); };

            /**
            * Sets scale factor
            *@param value - scale factor
            */
            virtual void SetScale(const DWF_Math::Vector3F& value) {};

            /**
            * Gets the transformation matrix
            *@return the transformation matrix
            */
            virtual DWF_Math::Matrix4x4F GetMatrix() const { return DWF_Math::Matrix4x4F(); };

            /**
            * Animates the particles
            *@param elapsedTime - elapsed time since last frame
            */
            virtual void Animate(double elapsedTime);

            /**
            * Renders the item
            *@param viewMatrix - view matrix to connect to shader
            *@param pRenderer - renderer to use to render the scene
            */
            virtual void Render(const DWF_Math::Matrix4x4F&   viewMatrix,
                                const DWF_Renderer::Renderer* pRenderer) const;

        private:
            std::shared_ptr<DWF_Particles::Particles> m_pParticles;
    };

    //---------------------------------------------------------------------------
    // SceneItem_Particles
    //---------------------------------------------------------------------------
    inline void SceneItem_Particles::SetParticles(const std::shared_ptr<DWF_Particles::Particles>& pParticles)
    {
        m_pParticles = pParticles;
    }
    //---------------------------------------------------------------------------
}
