/****************************************************************************
 * ==> DWF_Capsule ---------------------------------------------------------*
 ****************************************************************************
 * Description:  Geometric capsule                                          *
 * Contained in: Core                                                       *
 * Developer:    Jean-Milost Reymond                                        *
 ****************************************************************************
 * MIT License - DwarfStar engine                                           *
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

// dwarfstar
#include "DWF_Object.h"
#include "DWF_Mesh.h"

/**
* Geometric capsule
*@author Jean-Milost Reymond
*/
class DWF_Capsule : public DWF_Object
{
    public:
        DWF_Vector3F m_Top;
        DWF_Vector3F m_Bottom;
        float        m_Radius = 0.0f;

        DWF_Capsule();
        virtual ~DWF_Capsule();

        /**
        * Checks if capsule intersects with another capsule
        *@param other - other capsule to check
        *@param[out] penetrationDepth - penetration depth, in case of collisions
        *@return true if capsules are in collision, otherwise false
        */
        virtual bool Intersect(const DWF_Capsule& other, float& penetrationDepth) const;

        /**
        * Gets the capsule mesh
        *@param[out] mesh - the mesh to fill with capsule
        */
        virtual void GetMesh(DWF_Mesh& mesh) const;

    private:
        DWF_Vector3F GetAnyPerpendicularUnitVector(const DWF_Vector3F& vec) const;
};
