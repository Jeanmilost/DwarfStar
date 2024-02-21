/****************************************************************************
 * ==> DWF_SceneItemModelBase ----------------------------------------------*
 ****************************************************************************
 * Description : Scene item containing a base for a model                   *
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

#pragma once

namespace DWF_Scene
{
    /**
    * Scene item containing a base for a model
    *@author Jean-Milost Reymond
    */
    class SceneItem_ModelBase : public SceneItem
    {
        public:
            /**
            * Constructor
            *@param name - item name
            */
            SceneItem_ModelBase(const std::wstring& name);

            virtual ~SceneItem_ModelBase();

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
            * Gets the transformation matrix
            *@return the transformation matrix
            */
            virtual inline DWF_Math::Matrix4x4F GetMatrix() const;

        private:
            DWF_Math::Matrix4x4F m_Matrix       = DWF_Math::Matrix4x4F::Identity();
            DWF_Math::Vector3F   m_Pos;
            DWF_Math::Vector3F   m_Scale        = DWF_Math::Vector3F(1.0f, 1.0f, 1.0f);
            float                m_Roll         = 0.0f;
            float                m_Pitch        = 0.0f;
            float                m_Yaw          = 0.0f;
            bool                 m_MatrixCached = false;

            /**
            * Builds a transformation matrix
            *@param pos - position
            *@param roll - roll angle (i.e. rotation on the x axis)
            *@param pitch - pitch angle (i.e. rotation on the y axis)
            *@param yaw - yaw angle (i.e. rotation on the z axis)
            *@param scale - scale factor
            *@param[out] matrix - the transformation matrix
            */
            DWF_Math::Matrix4x4F BuildMatrix(const DWF_Math::Vector3F& pos,
                                                   float               roll,
                                                   float               pitch,
                                                   float               yaw,
                                             const DWF_Math::Vector3F& scale) const;
    };

    //---------------------------------------------------------------------------
    // SceneItem_ModelBase
    //---------------------------------------------------------------------------
    inline DWF_Math::Vector3F SceneItem_ModelBase::GetPos() const
    {
        return m_Pos;
    }
    //---------------------------------------------------------------------------
    inline void SceneItem_ModelBase::SetPos(const DWF_Math::Vector3F& value)
    {
        m_Pos          = value;
        m_MatrixCached = false;
    }
    //---------------------------------------------------------------------------
    inline float SceneItem_ModelBase::GetRoll() const
    {
        return m_Roll;
    }
    //---------------------------------------------------------------------------
    inline void SceneItem_ModelBase::SetRoll(float value)
    {
        m_Roll         = std::fmodf(value, 2.0f * (float)M_PI);
        m_MatrixCached = false;
    }
    //---------------------------------------------------------------------------
    inline float SceneItem_ModelBase::GetPitch() const
    {
        return m_Pitch;
    }
    //---------------------------------------------------------------------------
    inline void SceneItem_ModelBase::SetPitch(float value)
    {
        m_Pitch        = std::fmodf(value, 2.0f * (float)M_PI);
        m_MatrixCached = false;
    }
    //---------------------------------------------------------------------------
    inline float SceneItem_ModelBase::GetYaw() const
    {
        return m_Yaw;
    }
    //---------------------------------------------------------------------------
    inline void SceneItem_ModelBase::SetYaw(float value)
    {
        m_Yaw          = std::fmodf(value, 2.0f * (float)M_PI);
        m_MatrixCached = false;
    }
    //---------------------------------------------------------------------------
    inline void SceneItem_ModelBase::SetRotation(float roll, float pitch, float yaw)
    {
        const float max = 2.0f * (float)M_PI;
        m_Roll          = std::fmodf(roll, max);
        m_Pitch         = std::fmodf(pitch, max);
        m_Yaw           = std::fmodf(yaw, max);
        m_MatrixCached  = false;
    }
    //---------------------------------------------------------------------------
    inline DWF_Math::Vector3F SceneItem_ModelBase::GetScale() const
    {
        return m_Scale;
    }
    //---------------------------------------------------------------------------
    inline void SceneItem_ModelBase::SetScale(const DWF_Math::Vector3F& value)
    {
        m_Scale        = value;
        m_MatrixCached = false;
    }
    //---------------------------------------------------------------------------
    inline DWF_Math::Matrix4x4F SceneItem_ModelBase::GetMatrix() const
    {
        // cached matrix changed?
        if (!m_MatrixCached)
        {
            const_cast<DWF_Math::Matrix4x4F&>(m_Matrix)       = BuildMatrix(m_Pos, m_Roll, m_Pitch, m_Yaw, m_Scale);
            const_cast<bool&>                (m_MatrixCached) = true;
        }

        return m_Matrix;
    }
    //---------------------------------------------------------------------------
}
