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

#include "DWF_SceneItemPOV.h"

using namespace DWF_Scene;

//---------------------------------------------------------------------------
// SceneItem_PointOfView
//---------------------------------------------------------------------------
SceneItem_PointOfView::SceneItem_PointOfView(const std::wstring& name) :
    SceneItem(name)
{}
//---------------------------------------------------------------------------
SceneItem_PointOfView::~SceneItem_PointOfView()
{}
//---------------------------------------------------------------------------
void SceneItem_PointOfView::Render(const DWF_Math::Matrix4x4F&   viewMatrix,
                                   const DWF_Renderer::Renderer* pRenderer) const
{}
//---------------------------------------------------------------------------