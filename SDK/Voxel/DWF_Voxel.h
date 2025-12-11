/****************************************************************************
 * ==> DWF_Voxel -----------------------------------------------------------*
 ****************************************************************************
 * Description: Voxel                                                       *
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
#include <memory.h>

// classes
#include "DWF_Matrix4x4.h"
#include "DWF_Box.h"
#include "DWF_Model.h"
#include "DWF_Shader.h"
#include "DWF_Renderer.h"

namespace DWF_Voxel
{
    /**
    * Voxel
    *@author Jean-Milost Reymond
    */
    class Voxel
    {
        public:
            /**
            * Constructor
            *@param pModel - model to use to draw the Voxel
            *@param pShader - shader to use to draw the Voxel
            *@param pRenderer - renderer to use to draw the Voxel
            */
            Voxel(DWF_Model::Model* pModel, DWF_Renderer::Shader* pShader, DWF_Renderer::Renderer* pRenderer);

            virtual ~Voxel();

            /**
            * Gets the Voxel position (absolute, from [0, 0, 0] coordinates)
            *@return position
            */
            virtual DWF_Math::Vector3F GetPos() const;

            /**
            * Sets the Voxel position (absolute, from [0, 0, 0] coordinates)
            *@param pos - position
            */
            virtual void SetPos(const DWF_Math::Vector3F& pos);

            /**
            * Gets the Voxel bounding box
            *@param matrix - Voxel matrix
            *@return the Voxel bounding box
            *@note The returned box should be deleted when useless
            */
            virtual DWF_Geometry::Box* GetBoundingBox(const DWF_Math::Matrix4x4F& matrix) const;

            /**
            * Draws the Voxel
            *@param matrix - Voxel matrix
            */
            virtual void Draw(const DWF_Math::Matrix4x4F& matrix) const;

        private:
            std::unique_ptr<DWF_Geometry::Box> m_pBox;
            DWF_Model::Model*                  m_pModel    = nullptr;
            DWF_Renderer::Shader*              m_pShader   = nullptr;
            DWF_Renderer::Renderer*            m_pRenderer = nullptr;
            DWF_Math::Vector3F                 m_Pos;
    };
}
