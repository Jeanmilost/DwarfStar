/****************************************************************************
 * ==> DWF_Material --------------------------------------------------------*
 ****************************************************************************
 * Description:  Material                                                   *
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

#include "DWF_Material.h"

//---------------------------------------------------------------------------
// DWF_Material
//---------------------------------------------------------------------------
DWF_Material::DWF_Material() :
    DWF_Object()
{}
//---------------------------------------------------------------------------
DWF_Material::~DWF_Material()
{
    if (m_pTexture)
        delete m_pTexture;
}
//---------------------------------------------------------------------------
DWF_Material& DWF_Material::operator = (const DWF_Material& other)
{
    m_Color       = other.m_Color;
    m_Transparent = other.m_Transparent;
    m_Wireframe   = other.m_Wireframe;

    if (m_pTexture)
        delete m_pTexture;

    m_pTexture = nullptr;

    return *this;
}
//---------------------------------------------------------------------------
