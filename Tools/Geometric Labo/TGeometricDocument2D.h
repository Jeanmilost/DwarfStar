/****************************************************************************
 * ==> TGeometricDocument2D ------------------------------------------------*
 ****************************************************************************
 * Description : This module provides a geometric 2D shapes document        *
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

#ifndef TGeometricDocument2DH
#define TGeometricDocument2DH

// vcl
#include <Vcl.Graphics.hpp>

// std
#include <vector>

// dwarfstar engine
#include "DWF_Common_Types.h"
#include "DWF_Graphics_Color.h"
#include "DWF_Geometry_Shape.h"

// interface
#include "TGeometricDocument.h"

// xml library
#include "sxmlc.h"

using namespace DWF_Geometry;
using namespace DWF_Graphics;

/**
* Geometric document for 2D shapes
*@author Jean-Milost Reymond
*/
class TGeometricDocument2D : public TGeometricDocument
{
    public:
        TGeometricDocument2D();
        virtual ~TGeometricDocument2D();

        /**
        * Adds a line to the document
        *@param point - a point on the line
        *@param dir - the line direction
        */
        virtual void AddLine(const DWF_Vector2DR& point, const DWF_Vector2DR& dir);

        /**
        * Adds a line to the document
        *@param point - the point where the ray starts
        *@param dir - the ray direction
        */
        virtual void AddRay(const DWF_Vector2DR& point, const DWF_Vector2DR& dir);

        /**
        * Adds a line segment to the document
        *@param start - the point where the line segment starts
        *@param end - the point where the line segment ends
        */
        virtual void AddSegment(const DWF_Vector2DR& start, const DWF_Vector2DR& end);

        /**
        * Adds a polygon to the document
        *@param v1 - the first polygon vertex
        *@param v2 - the second polygon vertex
        *@param v3 - the third polygon vertex
        */
        virtual void AddPolygon(const DWF_Vector2DR& v1,
                                const DWF_Vector2DR& v2,
                                const DWF_Vector2DR& v3);

        /**
        * Adds a circle to the document
        *@param center - the center of the circle
        *@param radius - the circle radius
        */
        virtual void AddCircle(const DWF_Vector2DR& center, M_Real radius);

        /**
        * Adds a rectangle to the document
        *@param left - the rectangle left coordinate
        *@param top - the rectangle top coordinate
        *@param right - the rectangle right coordinate
        *@param bottom - the rectangle bottom coordinate
        */
        virtual void AddRect(M_Real left, M_Real top, M_Real right, M_Real bottom);

        /**
        * Selects the shape at index
        *@param index - index
        *@param selected - if true, the shape is selected, unselected otherwise
        */
        virtual void Select(std::size_t index, bool selected) const;

        /**
        * Resets the shape at index
        *@param index - index
        */
        virtual void Reset(std::size_t index) const;

        /**
        * Resets the shape
        *@param pShape - shape
        */
        virtual void Reset(void* pShape) const;

        /**
        * Gets the shape at the current index
        *@param index - index
        *@return shape at current index, NULL if not found or on error
        */
        virtual void* GetShape(std::size_t index) const;

        /**
        * Gets the shape count on the document
        *@return the shape count on the document
        */
        virtual std::size_t GetShapeCount() const;

        /**
        * Gets the currently focused shape
        *@return the currently focused shape
        */
        virtual DWF_Shape2D<M_Real>* GetFocused() const;

        /**
        * Inflates or deflates the currently focused shape
        *@param offsetX - inflating offset on the X axis, on negative value the shape will be deflated
        *@param offsetY - inflating offset on the Y axis, on negative value the shape will be deflated
        */
        virtual void InflateFocused(M_Real offsetX, M_Real offsetY);

        /**
        * Moves the currently focused shape
        *@param offsetX - moving offset on the X axis
        *@param offsetY - moving offset on the Y axis
        */
        virtual void MoveFocused(M_Real offsetX, M_Real offsetY);

        /**
        * Rotates the currently focused shape
        *@param offset - rotating offset
        */
        virtual void RotateFocused(M_Real offset);

        /**
        * Draws the document content on the canvas
        *@param rect - rectangle surrounding the document to draw
        *@param pCanvas - canvas to draw on
        */
        virtual void Draw(const TRect& rect, TCanvas* pCanvas) const;

    protected:
        /**
        * Called when the content of a document should be read
        *@param doc - xml document root node to read from
        *@return true on success, otherwise false
        */
        virtual bool DoReadContent(XMLNode* pNode);

        /**
        * Called when the content of a document should be written
        *@param doc - xml document to write to
        *@return true on success, otherwise false
        */
        virtual bool DoWriteContent(XMLDoc& doc) const;

    private:
        /**
        * Shape on the document
        */
        struct IShape
        {
            DWF_Shape2D<M_Real>* m_pShape;
            DWF_Color            m_Color;
            float                m_FadeOffset;
            float                m_FadeValue;
            bool                 m_Selected;

            IShape();
            ~IShape();
        };

        typedef std::vector<IShape*> IShapes;

        IShapes m_Shapes;

        /**
        * Reads a vector content from a XML node
        *@param pNode - node containing the vector to read
        *@return read vector
        */
        DWF_Vector2DR ReadVectorFromXML(XMLNode* pNode) const;

        /**
        * Adds a tag containing a vector in a document
        *@param pParent - parent node in document to add to
        *@param name - vector name
        *@param vector - vector containing the values to write
        *@return true on success, otherwise false
        */
        bool AddTag(XMLNode* pParent, const std::string& name, const DWF_Vector2DR& vector) const;

        /**
        * Draws document background
        *@param rect - document rect
        *@param hDC - device context to draw on
        */
        void DrawBackground(const TRect& rect, HDC hDC) const;

        /**
        * Draws an ending point
        *@param point - point to draw
        *@param fillSize - fill size
        *@param strokeSize - stroke size
        *@param fillColor - fill color
        *@param strokeColor - stroke color
        *@param pCanvas - canvas to draw on
        */
        void DrawPoint(const DWF_Vector2DR& point,
                             int            fillSize,
                             int            strokeSize,
                             TColor         fillColor,
                             TColor         strokeColor,
                             TCanvas*       pCanvas) const;

        /**
        * Fades in or out the color in a shape
        *@param pShape - shape for which color should be faded in or out
        */
        void FadeColor(IShape* pShape) const;
};

#endif
