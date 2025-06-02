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

// std
#include <vector>

// classes
#include "DWF_Collider.h"
#include "DWF_Renderer.h"

#pragma once

namespace DWF_Scene
{
    /**
    * Basic scene item
    *@author Jean-Milost Reymond
    */
    class SceneItem
    {
        public:
            /**
            * Constructor
            *@param name - item name
            */
            SceneItem(const std::wstring& name);

            virtual ~SceneItem();

            /**
            * Gets the item name
            *@return the item name
            */
            virtual inline std::wstring GetName() const;

            /**
            * Gets if the item is static
            *@return true if the item is static, otherwise false
            */
            virtual inline bool IsStatic() const;

            /**
            * Sets if the item is static
            *@param value - if true, the item is static
            */
            virtual inline void SetStatic(bool value);

            /**
            * Gets if the item is visible
            *@return true if the item is visible, otherwise false
            */
            virtual inline bool IsVisible() const;

            /**
            * Sets if the item is visible
            *@param value - if true, the item is visible
            */
            virtual inline void SetVisible(bool value);

            /**
            * Gets position
            *@return position
            */
            virtual DWF_Math::Vector3F GetPos() const = 0;

            /**
            * Sets position
            *@param value - position
            */
            virtual void SetPos(const DWF_Math::Vector3F& value) = 0;

            /**
            * Gets roll angle
            *@return roll angle (i.e. rotation on the x axis)
            */
            virtual float GetRoll() const = 0;

            /**
            * Sets roll angle
            *@param value - roll angle (i.e. rotation on the x axis)
            */
            virtual void SetRoll(float value) = 0;

            /**
            * Gets pitch angle
            *@return pitch angle (i.e. rotation on the y axis)
            */
            virtual float GetPitch() const = 0;

            /**
            * Sets pitch angle
            *@param value - pitch angle (i.e. rotation on the y axis)
            */
            virtual void SetPitch(float value) = 0;

            /**
            * Gets yaw angle
            *@return yaw angle (i.e. rotation on the z axis)
            */
            virtual float GetYaw() const = 0;

            /**
            * Sets yaw angle
            *@param value - yaw angle (i.e. rotation on the z axis)
            */
            virtual void SetYaw(float value) = 0;

            /**
            * Gets rotation angle on X axis
            *@return rotation angle on X axis
            */
            virtual inline float GetX() const;

            /**
            * Sets rotation angle on X axis
            *@param value - rotation angle on X axis
            */
            virtual inline void SetX(float value);

            /**
            * Gets rotation angle on Y axis
            *@return rotation angle on Y axis
            */
            virtual inline float GetY() const;

            /**
            * Sets rotation angle on Y axis
            *@param value - rotation angle on Y axis
            */
            virtual inline void SetY(float value);

            /**
            * Gets rotation angle on Z axis
            *@return rotation angle on Z axis
            */
            virtual inline float GetZ() const;

            /**
            * Sets rotation angle on Z axis
            *@param value - rotation angle on Z axis
            */
            virtual inline void SetZ(float value);

            /**
            * Sets rotation
            *@param roll - roll angle (i.e. rotation on the x axis)
            *@param pitch - pitch angle (i.e. rotation on the y axis)
            *@param yaw - yaw angle (i.e. rotation on the z axis)
            */
            virtual void SetRotation(float roll, float pitch, float yaw) = 0;

            /**
            * Gets scale factor
            *@return scale factor
            */
            virtual DWF_Math::Vector3F GetScale() const = 0;

            /**
            * Sets scale factor
            *@param value - scale factor
            */
            virtual void SetScale(const DWF_Math::Vector3F& value) = 0;

            /**
            * Gets the transformation matrix
            *@return the transformation matrix
            */
            virtual DWF_Math::Matrix4x4F GetMatrix() const = 0;

            /**
            * Adds a collider to the item
            *@param pCollider - collider to add
            *@note The item will be deleted internally, don't delete it from outside
            */
            virtual void AddCollider(DWF_Collider::Collider* pCollider);

            /**
            * Deletes a collider from the item
            *@param pCollider - collider to delete
            */
            virtual void DeleteCollider(DWF_Collider::Collider* pItem);

            /**
            * Deletes a collider from the item at index
            *@param index - collider index to delete
            */
            virtual void DeleteColliderAt(std::size_t index);

            /**
            * Gets a collider at index
            *@param index - collider index to get
            *@return collider, nullptr if not found or on error
            */
            virtual DWF_Collider::Collider* GetCollider(std::size_t index) const;

            /**
            * Gets the collider count
            *@return the collider count
            */
            virtual std::size_t GetColliderCount() const;

            /**
            * Gets the shader to use to render the model
            *@return the shader to use to render the model
            */
            virtual inline DWF_Renderer::Shader* GetShader() const;

            /**
            * Sets the shader to use to render the model
            *@param pShader - the shader to use to render the model
            *@note Don't delete the shader from outside, it will be deleted internally
            */
            virtual inline void SetShader(const std::shared_ptr<DWF_Renderer::Shader>& pShader);

            /**
            * Renders the item
            *@param viewMatrix - view matrix to connect to shader
            *@param pRenderer - renderer to use to render the scene
            */
            virtual void Render(const DWF_Math::Matrix4x4F&   viewMatrix,
                                const DWF_Renderer::Renderer* pRenderer) const = 0;

        protected:
            std::shared_ptr<DWF_Renderer::Shader> m_pShader;

        private:
            DWF_Collider::Colliders m_Colliders;
            std::wstring            m_Name;
            bool                    m_Static  = false;
            bool                    m_Visible = true;
    };

    /**
    * Scene items
    *@author Jean-Milost Reymond
    */
    typedef std::vector<SceneItem*> SceneItems;

    //---------------------------------------------------------------------------
    // SceneItem
    //---------------------------------------------------------------------------
    inline std::wstring SceneItem::GetName() const
    {
        return m_Name;
    }
    //---------------------------------------------------------------------------
    inline bool SceneItem::IsStatic() const
    {
        return m_Static;
    }
    //---------------------------------------------------------------------------
    inline void SceneItem::SetStatic(bool value)
    {
        m_Static = value;
    }
    //---------------------------------------------------------------------------
    inline bool SceneItem::IsVisible() const
    {
        return m_Visible;
    }
    //---------------------------------------------------------------------------
    inline void SceneItem::SetVisible(bool value)
    {
        m_Visible = value;
    }
    //---------------------------------------------------------------------------
    inline float SceneItem::GetX() const
    {
        return GetRoll();
    }
    //---------------------------------------------------------------------------
    inline void SceneItem::SetX(float value)
    {
        SetRoll(value);
    }
    //---------------------------------------------------------------------------
    inline float SceneItem::GetY() const
    {
        return GetPitch();
    }
    //---------------------------------------------------------------------------
    inline void SceneItem::SetY(float value)
    {
        SetPitch(value);
    }
    //---------------------------------------------------------------------------
    inline float SceneItem::GetZ() const
    {
        return GetYaw();
    }
    //---------------------------------------------------------------------------
    inline void SceneItem::SetZ(float value)
    {
        SetYaw(value);
    }
    //---------------------------------------------------------------------------
    inline DWF_Renderer::Shader* SceneItem::GetShader() const
    {
        return m_pShader.get();
    }
    //---------------------------------------------------------------------------
    inline void SceneItem::SetShader(const std::shared_ptr<DWF_Renderer::Shader>& pShader)
    {
        m_pShader = pShader;
    }
    //---------------------------------------------------------------------------
}
