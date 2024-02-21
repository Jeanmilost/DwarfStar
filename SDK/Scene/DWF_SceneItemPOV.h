/****************************************************************************
 * ==> DWF_SceneItemPOV ----------------------------------------------------*
 ****************************************************************************
 * Description : Scene item containing a point of view                      *
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
#include "DWF_SceneItem.h"
#include "DWF_Matrix4x4.h"
#include "DWF_PointOfView.h"
#include "DWF_Arcball.h"
#include "DWF_Camera.h"

#pragma once

namespace DWF_Scene
{
    /**
    * Scene item containing a point of view
    *@author Jean-Milost Reymond
    */
    class SceneItem_PointOfView : public SceneItem
    {
        public:
            enum class IEType
            {
                IE_T_None = 0,
                IE_T_Arcball,
                IE_T_Camera
            };

            /**
            * Constructor
            *@param name - item name
            */
            SceneItem_PointOfView(const std::wstring& name);

            virtual ~SceneItem_PointOfView();

            /**
            * Gets point of view
            *@return point of view
            */
            virtual inline PointOfView* Get() const;

            /**
            * Sets point of view
            *@param pPOV - point of view to set
            *@note Don't delete the point of view from outside, it will be deleted internally
            */
            virtual inline void Set(Arcball* pPOV);

            /**
            * Sets point of view
            *@param pPOV - point of view to set
            *@note Don't delete the point of view from outside, it will be deleted internally
            */
            virtual inline void Set(Camera* pPOV);

            /**
            * Gets point of view type
            *@return point of view type
            */
            virtual inline IEType GetType() const;

            /**
            * Gets position
            *@return position
            */
            virtual inline DWF_Math::Vector3F GetPos() const;

            /**
            * Sets position
            *@param value - position
            */
            virtual inline void SetPos(const DWF_Math::Vector3F& value);

            /**
            * Gets roll angle
            *@return roll angle (i.e. rotation on the x axis)
            */
            virtual inline float GetRoll() const;

            /**
            * Sets roll angle
            *@param value - roll angle (i.e. rotation on the x axis)
            */
            virtual inline void SetRoll(float value);

            /**
            * Gets pitch angle
            *@return pitch angle (i.e. rotation on the y axis)
            */
            virtual inline float GetPitch() const;

            /**
            * Sets pitch angle
            *@param value - pitch angle (i.e. rotation on the y axis)
            */
            virtual inline void SetPitch(float value);

            /**
            * Gets yaw angle
            *@return yaw angle (i.e. rotation on the z axis)
            */
            virtual inline float GetYaw() const;

            /**
            * Sets yaw angle
            *@param value - yaw angle (i.e. rotation on the z axis)
            */
            virtual inline void SetYaw(float value);

            /**
            * Sets rotation
            *@param roll - roll angle (i.e. rotation on the x axis)
            *@param pitch - pitch angle (i.e. rotation on the y axis)
            *@param yaw - yaw angle (i.e. rotation on the z axis)
            */
            virtual inline void SetRotation(float roll, float pitch, float yaw);

            /**
            * Gets scale factor
            *@return scale factor
            */
            virtual inline DWF_Math::Vector3F GetScale() const;

            /**
            * Sets scale factor
            *@param value - scale factor
            */
            virtual inline void SetScale(const DWF_Math::Vector3F& value);

            /**
            * Gets arcball radius
            *@return arcball radius
            */
            virtual inline float GetRadius() const;

            /**
            * Sets arcball radius
            *@param value - arcball radius
            */
            virtual inline void SetRadius(float value);

            /**
            * Gets the transformation matrix
            *@return the transformation matrix
            */
            virtual inline DWF_Math::Matrix4x4F GetMatrix() const;

            /**
            * Resets the matrix cache
            */
            virtual inline void ResetMatrixCache();

            /**
            * Renders the item
            *@param viewMatrix - view matrix to connect to shader
            *@param pRenderer - renderer to use to render the scene
            */
            virtual void Render(const DWF_Math::Matrix4x4F&   viewMatrix,
                                const DWF_Renderer::Renderer* pRenderer) const;

        private:
            std::unique_ptr<PointOfView> m_pPOV;
            IEType                       m_Type         = IEType::IE_T_None;
            DWF_Math::Matrix4x4F         m_Matrix;
            bool                         m_MatrixCached = false;
    };

    //---------------------------------------------------------------------------
    // SceneItem_PointOfView
    //---------------------------------------------------------------------------
    inline PointOfView* SceneItem_PointOfView::Get() const
    {
        return m_pPOV.get();
    }
    //---------------------------------------------------------------------------
    inline void SceneItem_PointOfView::Set(Arcball* pPOV)
    {
        m_pPOV.reset(pPOV);
        m_Type = IEType::IE_T_Arcball;
    }
    //---------------------------------------------------------------------------
    inline void SceneItem_PointOfView::Set(Camera* pPOV)
    {
        m_pPOV.reset(pPOV);
        m_Type = IEType::IE_T_Camera;
    }
    //---------------------------------------------------------------------------
    inline SceneItem_PointOfView::IEType SceneItem_PointOfView::GetType() const
    {
        return m_Type;
    }
    //---------------------------------------------------------------------------
    inline DWF_Math::Vector3F SceneItem_PointOfView::GetPos() const
    {
        if (!m_pPOV)
            return DWF_Math::Vector3F();

        switch (m_Type)
        {
            case IEType::IE_T_Arcball: return static_cast<Arcball*>(m_pPOV.get())->m_Position;
            case IEType::IE_T_Camera:  return static_cast<Camera*> (m_pPOV.get())->m_Position;
        }

        return DWF_Math::Vector3F();
    }
    //---------------------------------------------------------------------------
    inline void SceneItem_PointOfView::SetPos(const DWF_Math::Vector3F& value)
    {
        if (!m_pPOV)
            return;

        switch (m_Type)
        {
            case IEType::IE_T_Arcball: m_MatrixCached = false; static_cast<Arcball*>(m_pPOV.get())->m_Position = value; break;
            case IEType::IE_T_Camera:  m_MatrixCached = false; static_cast<Camera*> (m_pPOV.get())->m_Position = value; break;
        }
    }
    //---------------------------------------------------------------------------
    inline float SceneItem_PointOfView::GetRoll() const
    {
        if (!m_pPOV)
            return 0.0f;

        switch (m_Type)
        {
            case IEType::IE_T_Arcball: return static_cast<Arcball*>(m_pPOV.get())->m_AngleX;
            case IEType::IE_T_Camera:  return static_cast<Camera*> (m_pPOV.get())->m_AngleX;
        }

        return 0.0f;
    }
    //---------------------------------------------------------------------------
    inline void SceneItem_PointOfView::SetRoll(float value)
    {
        if (!m_pPOV)
            return;

        switch (m_Type)
        {
            case IEType::IE_T_Arcball: m_MatrixCached = false; static_cast<Arcball*>(m_pPOV.get())->m_AngleX = std::fmodf(value, 2.0f * (float)M_PI); break;
            case IEType::IE_T_Camera:  m_MatrixCached = false; static_cast<Camera*> (m_pPOV.get())->m_AngleX = std::fmodf(value, 2.0f * (float)M_PI); break;
        }
    }
    //---------------------------------------------------------------------------
    inline float SceneItem_PointOfView::GetPitch() const
    {
        if (!m_pPOV)
            return 0.0f;

        switch (m_Type)
        {
            case IEType::IE_T_Arcball: return static_cast<Arcball*>(m_pPOV.get())->m_AngleY;
            case IEType::IE_T_Camera:  return static_cast<Camera*> (m_pPOV.get())->m_AngleY;
        }

        return 0.0f;
    }
    //---------------------------------------------------------------------------
    inline void SceneItem_PointOfView::SetPitch(float value)
    {
        if (!m_pPOV)
            return;

        switch (m_Type)
        {
            case IEType::IE_T_Arcball: m_MatrixCached = false; static_cast<Arcball*>(m_pPOV.get())->m_AngleY = std::fmodf(value, 2.0f * (float)M_PI); break;
            case IEType::IE_T_Camera:  m_MatrixCached = false; static_cast<Camera*> (m_pPOV.get())->m_AngleY = std::fmodf(value, 2.0f * (float)M_PI); break;
        }
    }
    //---------------------------------------------------------------------------
    inline float SceneItem_PointOfView::GetYaw() const
    {
        if (!m_pPOV)
            return 0.0f;

        switch (m_Type)
        {
            case IEType::IE_T_Camera: return static_cast<Camera*> (m_pPOV.get())->m_AngleZ;
        }

        return 0.0f;
    }
    //---------------------------------------------------------------------------
    inline void SceneItem_PointOfView::SetYaw(float value)
    {
        if (!m_pPOV)
            return;

        switch (m_Type)
        {
            case IEType::IE_T_Camera: m_MatrixCached = false; static_cast<Camera*> (m_pPOV.get())->m_AngleZ = std::fmodf(value, 2.0f * (float)M_PI); break;
        }
    }
    //---------------------------------------------------------------------------
    inline void SceneItem_PointOfView::SetRotation(float roll, float pitch, float yaw)
    {
        if (!m_pPOV)
            return;

        switch (m_Type)
        {
            case IEType::IE_T_Arcball:
            {
                Arcball* pArcball = static_cast<Arcball*>(m_pPOV.get());

                pArcball->m_AngleX = std::fmodf(roll,  2.0f * (float)M_PI);
                pArcball->m_AngleY = std::fmodf(pitch, 2.0f * (float)M_PI);

                m_MatrixCached = false;
                break;
            }

            case IEType::IE_T_Camera:
            {
                Camera* pCamera = static_cast<Camera*>(m_pPOV.get());

                pCamera->m_AngleX = std::fmodf(roll,  2.0f * (float)M_PI);
                pCamera->m_AngleY = std::fmodf(pitch, 2.0f * (float)M_PI);
                pCamera->m_AngleZ = std::fmodf(yaw,   2.0f * (float)M_PI);

                m_MatrixCached = false;
                break;
            }
        }
    }
    //---------------------------------------------------------------------------
    inline DWF_Math::Vector3F SceneItem_PointOfView::GetScale() const
    {
        if (!m_pPOV)
            return DWF_Math::Vector3F();

        switch (m_Type)
        {
            case IEType::IE_T_Camera: return static_cast<Camera*> (m_pPOV.get())->m_Factor;
        }

        return DWF_Math::Vector3F();
    }
    //---------------------------------------------------------------------------
    inline void SceneItem_PointOfView::SetScale(const DWF_Math::Vector3F& value)
    {
        if (!m_pPOV)
            return;

        switch (m_Type)
        {
            case IEType::IE_T_Camera: m_MatrixCached = false; static_cast<Camera*> (m_pPOV.get())->m_Factor = value; break;
        }
    }
    //---------------------------------------------------------------------------
    inline float SceneItem_PointOfView::GetRadius() const
    {
        if (!m_pPOV)
            return 0.0f;

        switch (m_Type)
        {
            case IEType::IE_T_Arcball: return static_cast<Arcball*>(m_pPOV.get())->m_Radius;
        }

        return 0.0f;
    }
    //---------------------------------------------------------------------------
    inline void SceneItem_PointOfView::SetRadius(float value)
    {
        if (!m_pPOV)
            return;

        switch (m_Type)
        {
            case IEType::IE_T_Camera: m_MatrixCached = false; static_cast<Arcball*>(m_pPOV.get())->m_Radius = value; break;
        }
    }
    //---------------------------------------------------------------------------
    inline DWF_Math::Matrix4x4F SceneItem_PointOfView::GetMatrix() const
    {
        if (!m_pPOV)
            return DWF_Math::Matrix4x4F::Identity();

        // cached matrix changed?
        if (!m_MatrixCached)
        {
            const_cast<DWF_Math::Matrix4x4F&>(m_Matrix)       = m_pPOV->ToMatrix();
            const_cast<bool&>                (m_MatrixCached) = true;
        }

        return m_Matrix;
    }
    //---------------------------------------------------------------------------
    inline void SceneItem_PointOfView::ResetMatrixCache()
    {
        m_MatrixCached = true;
    }
    //---------------------------------------------------------------------------
}
