/****************************************************************************
 * ==> TGeometricSimulator -------------------------------------------------*
 ****************************************************************************
 * Description : This module provides a geometric simulator, that can       *
 *               process several test scenarios on a document               *
 * Developer   : Jean-Milost Reymond                                        *
 ****************************************************************************
 * MIT License - DwarfStar Engine                                           *
 *                                                                          *
 * Permission is hereby granted, free of charge, to any person obtaining a  *
 * copy of this software and associated documentation files (the            *
 * "Software"), to deal in the Software without restriction, including      *
 * without limitation the rights to use, copy, modify, merge, publish,      *
 * distribute, sublicense, and/or sell copies of the Software, and to       *
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

#include "TGeometricSimulator.h"

// interface
#include "TGeometricDocument2D.h"
#include "TGeometricDocument3D.h"

//---------------------------------------------------------------------------
// TGeometricSimulator
//---------------------------------------------------------------------------
TGeometricSimulator::TGeometricSimulator()
{}
//---------------------------------------------------------------------------
TGeometricSimulator::~TGeometricSimulator()
{}
//---------------------------------------------------------------------------
void TGeometricSimulator::TestInside(TGeometricDocument* pDocument, const TPoint& mousePos)
{
    // get 2D document
    TGeometricDocument2D* pDocument2D = dynamic_cast<TGeometricDocument2D*>(pDocument);

    // do reset simulation on a 2D document?
    if (pDocument2D)
    {
        // get shape count
        const std::size_t shapeCount = pDocument2D->GetShapeCount();

        IShapes shapes;

        // iterate through shapes to check
        for (std::size_t i = 0; i < shapeCount; ++i)
        {
            // get the shape to test
            const DWF_Shape2D<M_Real>* pShape =
                    static_cast<DWF_Shape2D<M_Real>*>(pDocument2D->GetShape(i));

            // check if the mouse cursor is above this shape
            if (pShape->Inside(mousePos.X, mousePos.Y, 0.0))
            {
                pDocument2D->Select(i, true);
                shapes.insert(pDocument2D->GetShape(i));
            }
            else
                pDocument2D->Select(i, false);
        }

        // iterate through the recently detected shapes
        for (IShapes::iterator it = shapes.begin(); it != shapes.end(); ++it)
        {
            // found a new shape in collision
            if (m_Shapes.find(*it) != m_Shapes.end())
                continue;

            // reset the shape
            pDocument2D->Reset(*it);
        }

        // iterate through the previously detected shapes
        for (IShapes::iterator it = m_Shapes.begin(); it != m_Shapes.end(); ++it)
        {
            // found a new shape in collision
            if (shapes.find(*it) != shapes.end())
                continue;

            // reset the shape
            pDocument2D->Reset(*it);
        }

        // keep the newly detected set
        m_Shapes = shapes;

        return;
    }

    // get 3D document
    TGeometricDocument3D* pDocument3D = dynamic_cast<TGeometricDocument3D*>(pDocument);

    // do reset simulation on a 3D document?
    if (pDocument3D)
    {
        // enable the inside simulator mode in the 3d document
        pDocument3D->EnableInsideSimulator(true);

        // get the current simulator point on the document
        const DWF_Vector3DR point = pDocument3D->GetInsideSimulatorPoint();

        // get shape count
        const std::size_t shapeCount = pDocument3D->GetShapeCount();

        IShapes shapes;

        // iterate through shapes to check
        for (std::size_t i = 0; i < shapeCount; ++i)
        {
            // get the shape to test
            const DWF_Shape3D<M_Real>* pShape =
                    static_cast<DWF_Shape3D<M_Real>*>(pDocument3D->GetShape(i));

            // check if the mouse cursor is above this shape
            if (pShape->Inside(point.m_X, point.m_Y, point.m_Z, 0.0f))
            {
                pDocument3D->Select(i, true);
                shapes.insert(pDocument3D->GetShape(i));
            }
            else
                pDocument3D->Select(i, false);
        }

        // iterate through the recently detected shapes
        for (IShapes::iterator it = shapes.begin(); it != shapes.end(); ++it)
        {
            // found a new shape in collision
            if (m_Shapes.find(*it) != m_Shapes.end())
                continue;

            // reset the shape
            pDocument3D->Reset(*it);
        }

        // iterate through the previously detected shapes
        for (IShapes::iterator it = m_Shapes.begin(); it != m_Shapes.end(); ++it)
        {
            // found a new shape in collision
            if (shapes.find(*it) != shapes.end())
                continue;

            // reset the shape
            pDocument3D->Reset(*it);
        }

        // keep the newly detected set
        m_Shapes = shapes;

        return;
    }
}
//---------------------------------------------------------------------------
void TGeometricSimulator::TestIntersections(TGeometricDocument* pDocument)
{
    if (!pDocument)
        return;

    // get shape count
    const std::size_t shapeCount = pDocument->GetShapeCount();

    IShapes shapes;

    // iterate through shapes to check
    for (std::size_t i = 0; i < shapeCount; ++i)
    {
        // reset the selection state for the current shape
        pDocument->Select(i, false);

        // get the shape to test
        const DWF_Shape2D<M_Real>* pShape =
                static_cast<DWF_Shape2D<M_Real>*>(pDocument->GetShape(i));

        // check if the shape intersects another shape
        for (std::size_t j = 0; j < shapeCount; ++j)
        {
            // check if the shape will be tested against itself, skip it if yes
            if (i == j)
                continue;

            // get the shape to test against
            const DWF_Shape2D<M_Real>* pOtherShape =
                    static_cast<DWF_Shape2D<M_Real>*>(pDocument->GetShape(j));

            // are shapes intersecting?
            if (pShape->Intersect(*pOtherShape, M_Epsilon))
            {
                // select the shape
                pDocument->Select(i, true);

                // add it to colliding list, to check differences with previous test
                shapes.insert(pDocument->GetShape(i));

                break;
            }
        }
    }

    // iterate through the recently detected shapes
    for (IShapes::iterator it = shapes.begin(); it != shapes.end(); ++it)
    {
        // found a new shape in collision
        if (m_Shapes.find(*it) != m_Shapes.end())
            continue;

        // reset the shape
        pDocument->Reset(*it);
    }

    // iterate through the previously detected shapes
    for (IShapes::iterator it = m_Shapes.begin(); it != m_Shapes.end(); ++it)
    {
        // found a new shape in collision
        if (shapes.find(*it) != shapes.end())
            continue;

        // reset the shape
        pDocument->Reset(*it);
    }

    // keep the newly detected set
    m_Shapes = shapes;
}
//---------------------------------------------------------------------------
void TGeometricSimulator::Reset(TGeometricDocument* pDocument) const
{
    // get 2D document
    TGeometricDocument2D* pDocument2D = dynamic_cast<TGeometricDocument2D*>(pDocument);

    // do reset simulation on a 2D document?
    if (pDocument2D)
    {
        // get shape count
        const std::size_t shapeCount = pDocument2D->GetShapeCount();

        // iterate through shapes and reset the selection on each of them
        for (std::size_t i = 0; i < shapeCount; ++i)
            pDocument2D->Reset(i);

        return;
    }

    // get 3D document
    TGeometricDocument3D* pDocument3D = dynamic_cast<TGeometricDocument3D*>(pDocument);

    // do reset simulation on a 2D document?
    if (pDocument3D)
    {
        // get shape count
        const std::size_t shapeCount = pDocument3D->GetShapeCount();

        // iterate through shapes and reset the selection on each of them
        for (std::size_t i = 0; i < shapeCount; ++i)
            pDocument3D->Reset(i);

        // disable the inside simulator mode in the 3d document
        pDocument3D->EnableInsideSimulator(false);

        return;
    }
}
//---------------------------------------------------------------------------
