/****************************************************************************
 * ==> DWF_SceneItemAnimation ----------------------------------------------*
 ****************************************************************************
 * Description : Scene item containing an animation                         *
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
#include "DWF_SceneItemModelBase.h"
#include "DWF_ModelFormat.h"
#include "DWF_IQM.h"
#include "DWF_Shader.h"

#pragma once

namespace DWF_Scene
{
    /**
    * Scene item containing an animation
    *@author Jean-Milost Reymond
    */
    class SceneItem_Animation : public SceneItem_ModelBase
    {
        public:
            /**
            * Animation description
            */
            struct IAnimDesc
            {
                DWF_Model::ModelFormat* m_pModelFormat   = nullptr;
                std::size_t             m_AnimSetIndex   = 0;
                std::size_t             m_FrameIndex     = 0;
                std::size_t             m_FrameStart     = 0;
                std::size_t             m_FrameCount     = 0;
                double                  m_FrameTimeStamp = 0.0;
                double                  m_FrameAnimTime  = 0.0;
                double                  m_FrameDuration  = 0.0;
                bool                    m_Loop           = false;

                IAnimDesc();
                virtual ~IAnimDesc();
            };

            /**
            * Called when the next frame was calculated
            *@param arg1 - scene animation item in which the next frame was calculated
            *@param arg2 - animation description
            */
            typedef std::function<void(const SceneItem_Animation*, const IAnimDesc*)> ITfOnFrame;

            /**
            * Called when an animation end was reached
            *@param arg1 - scene animation item in which the end was reached
            *@param arg2 - animation description
            */
            typedef std::function<void(const SceneItem_Animation*, const IAnimDesc*)> ITfOnEndReached;

            /**
            * Constructor
            *@param name - item name
            */
            SceneItem_Animation(const std::wstring& name);

            virtual ~SceneItem_Animation();

            /**
            * Sets the animation model to use
            *@param pModelFormat - the animation model which contains the animations to play
            *@note The model will be deleted internally, don't delete it from outside
            */
            virtual inline void SetModel(DWF_Model::ModelFormat* pModelFormat);

            /**
            * Gets if the skeleton should be drawn
            *@return true the skeleton should be drawn, otherwise false
            */
            virtual inline bool DoDrawSkeleton() const;

            /**
            * Sets if the skeleton should be drawn
            *@param value - if true, the skeleton will be drawn
            */
            virtual inline void SetDrawSkeleton(bool value);

            /**
            * Adds an animation to the item
            *@param animSetIndex - animation set index to use in the model
            *@param frameStart - frame start index
            *@param frameCount - frame count the animation contains
            *@param frameDuration - frame duration in milliseconds
            *@param loop - if true, the animation will loop
            */
            virtual void AddAnim(std::size_t animSetIndex,
                                 std::size_t frameStart,
                                 std::size_t frameCount,
                                 double      frameDuration,
                                 bool        loop);

            /**
            * Adds an animation to the item
            *@param pModelFormat - animated model containing the animation to add
            *@param animSetIndex - animation set index to use in the model
            *@param frameCount - frame count the animation contains
            *@param frameDuration - frame duration in milliseconds
            *@param loop - if true, the animation will loop
            *@note The animation will be deleted internally, don't delete it from outside
            */
            virtual void AddAnim(DWF_Model::ModelFormat* pModelFormat,
                                 std::size_t             animSetIndex,
                                 std::size_t             frameCount,
                                 double                  frameDuration,
                                 bool                    loop);

            /**
            * Deletes an animation from the item
            *@param pModelFormat - animated model to delete
            */
            virtual void DeleteAnim(DWF_Model::ModelFormat* pModelFormat);

            /**
            * Deletes an animation from the item at index
            *@param index - animation index to delete
            */
            virtual void DeleteAnimAt(std::size_t index);

            /**
            * Gets an animation at index
            *@param index - animation index to get
            *@return animation, nullptr if not found or on error
            */
            virtual IAnimDesc* GetAnim(std::size_t index) const;

            /**
            * Gets the animation count
            *@return the animation count
            */
            virtual std::size_t GetAnimCount() const;

            /**
            * Gets the currently selected animation
            *@return the currently selected animation
            */
            virtual std::size_t GetSelectedAnim() const;

            /**
            * Selects the current animation to play
            *@param index - animation index to select
            */
            virtual void SelectAnim(std::size_t index);

            /**
            * Selects the animation set in an animation
            *@param index - animation index for which the animation set should be modified
            *@param animSetIndex - new animation set index to use in the model
            */
            virtual void SelectAnimSet(std::size_t index, std::size_t animSetIndex);

            /**
            * Resets the animation
            *@param index - animation index to reset
            */
            virtual void ResetAnim(std::size_t index);

            /**
            * Gets the shader to use to render the model
            *@return the shader to use to render the model
            */
            virtual inline DWF_Renderer::Shader* GetShader() const;

            /**
            * Sets the shader to use to render the model
            *@param pShader - the shader to use to render the model
            *@??? Don't delete the model from outside, it will be deleted internally
            */
            virtual inline void SetShader(DWF_Renderer::Shader* pShader);

            /**
            * Renders the item
            *@param viewMatrix - view matrix to connect to shader
            *@param pRenderer - renderer to use to render the scene
            */
            virtual void Render(const DWF_Math::Matrix4x4F&   viewMatrix,
                                const DWF_Renderer::Renderer* pRenderer) const;

            /**
            * Sets the OnFrame callback
            *@param fHandler - function handler
            */
            void Set_OnFrame(ITfOnFrame fHandler);

            /**
            * Sets the OnEndReached callback
            *@param fHandler - function handler
            */
            void Set_OnEndReached(ITfOnEndReached fHandler);

        private:
            typedef std::vector<IAnimDesc*> IAnimations;

            IAnimations             m_Animations;
            DWF_Model::ModelFormat* m_pModelFormat  = nullptr;
            DWF_Renderer::Shader*   m_pShader       = nullptr;
            std::size_t             m_Index         = 0;
            bool                    m_ShaderIsLocal = false;
            bool                    m_DrawSkeleton  = false;
            ITfOnFrame              m_fOnFrame      = nullptr;
            ITfOnEndReached         m_fOnEndReached = nullptr;

            /**
            * Draws a model
            *@param pModelFormat - model to draw
            *@param animSetIndex - animation set index
            *@param frameIndex - animation frame index
            *@param frameCount - animation frame count
            *@param pShader - shader to use to draw the model
            *@param pRenderer - renderer to use to draw the model
            */
            void DrawModel(const DWF_Model::ModelFormat* pModelFormat,
                                 std::size_t             animSetIndex,
                                 std::size_t             frameIndex,
                                 std::size_t             frameCount,
                           const DWF_Renderer::Shader*   pShader,
                           const DWF_Renderer::Renderer* pRenderer) const;

            /**
            * Draws a model bone
            *@param pModelFormat - model format for which the bone should be drawn
            *@param pBone - bone to draw
            *@param animSetIndex - animation set index
            *@param frameIndex - animation frame index
            *@param frameCount - animation frame count
            *@param pShader - shader to use to draw the bone
            *@param pRenderer - renderer to use to draw the bone
            */
            void DrawBone(const DWF_Model::ModelFormat*  pModelFormat,
                          const DWF_Model::Model*        pModel,
                          const DWF_Model::Model::IBone* pBone,
                                std::size_t              animSetIndex,
                                std::size_t              frameIndex,
                                std::size_t              frameCount,
                          const DWF_Renderer::Shader*    pShader,
                          const DWF_Renderer::Renderer*  pRenderer) const;
    };

    //---------------------------------------------------------------------------
    // SceneItem_Animation
    //---------------------------------------------------------------------------
    inline void SceneItem_Animation::SetModel(DWF_Model::ModelFormat* pModelFormat)
    {
        m_pModelFormat = pModelFormat;
    }
    //---------------------------------------------------------------------------
    inline bool SceneItem_Animation::DoDrawSkeleton() const
    {
        return m_DrawSkeleton;
    }
    //---------------------------------------------------------------------------
    inline void SceneItem_Animation::SetDrawSkeleton(bool value)
    {
        m_DrawSkeleton = value;
    }
    //---------------------------------------------------------------------------
    inline DWF_Renderer::Shader* SceneItem_Animation::GetShader() const
    {
        return m_pShader;
    }
    //---------------------------------------------------------------------------
    inline void SceneItem_Animation::SetShader(DWF_Renderer::Shader* pShader)
    {
        m_pShader = pShader;
    }
    //---------------------------------------------------------------------------
}
