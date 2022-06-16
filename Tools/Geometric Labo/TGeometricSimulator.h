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

#ifndef TGeometricSimulatorH
#define TGeometricSimulatorH

// std
#include <set>

// dwarfstar engine
#include "DWF_Geometry_Vector.h"

// interface
#include "TGeometricDocument.h"

/**
* Geometric simulator, that can process several test scenarios on a document
*@author Jean-Milost Reymond
*/
class TGeometricSimulator
{
    public:
        TGeometricSimulator();
        virtual ~TGeometricSimulator();

        /**
        * Tests inside which shape the point is
        *@param pDocument - document containing shapes to test
        *@param mousePos - mouse position on the screen, not used for 3d documents
        */
        virtual void TestInside(TGeometricDocument* pDocument, const TPoint& mousePos);

        /**
        * Tests all intersections on the document
        *@param pDocument - document for which intersections should be tested
        */
        virtual void TestIntersections(TGeometricDocument* pDocument);

        /**
        * Resets the simulator to his original state
        *@param pDocument - document used by the simulator
        */
        virtual void Reset(TGeometricDocument* pDocument) const;

    private:
        typedef std::set<void*> IShapes;

        IShapes m_Shapes;
};

#endif
