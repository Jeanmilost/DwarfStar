/****************************************************************************
 * ==> TGeometricDocument --------------------------------------------------*
 ****************************************************************************
 * Description : This module provides a geometric shapes document           *
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

#ifndef TGeometricDocumentH
#define TGeometricDocumentH

// vcl
#include <Vcl.Graphics.hpp>

// std
#include <string>

// dwarfstar engine
#include "DWF_Common_Types.h"
#include "DWF_Graphics_Color.h"

// xml library
#include "sxmlc.h"

using namespace DWF_Graphics;

/**
* Geometric document
*@author Jean-Milost Reymond
*/
class TGeometricDocument
{
    public:
        TGeometricDocument();
        virtual ~TGeometricDocument();

        /**
        * Gets the background color
        *@return background color
        */
        virtual DWF_Color GetBackgroundColor() const;

        /**
        * Sets background color
        *@param color - color
        */
        virtual void SetBackgroundColor(const DWF_Color& color);

        /**
        * Gets the grid color
        *@return grid color
        */
        virtual DWF_Color GetGridColor() const;

        /**
        * Sets grid color
        *@param color - color
        */
        virtual void SetGridColor(const DWF_Color& color);

        /**
        * Gets the grid offset
        *@return grid offset
        */
        virtual std::size_t GetGridOffset() const;

        /**
        * Sets the grid offset
        *@param offset - offset
        */
        virtual void SetGridOffset(std::size_t offset);

        /**
        * Focuses the shape at index on the document
        */
        virtual void Focus(std::size_t index);

        /**
        * Focuses the previous shape on the document
        */
        virtual void FocusPrev();

        /**
        * Focuses the next shape on the document
        */
        virtual void FocusNext();

        /**
        * Selects the shape at index
        *@param index - index
        *@param selected - if true, the shape is selected, unselected otherwise
        */
        virtual void Select(std::size_t index, bool selected) const = 0;

        /**
        * Resets the shape at index
        *@param index - index
        */
        virtual void Reset(std::size_t index) const = 0;

        /**
        * Resets the shape
        *@param pShape - shape
        */
        virtual void Reset(void* pShape) const = 0;

        /**
        * Gets the shape at the current index
        *@param index - index
        *@return shape at current index, NULL if not found or on error
        */
        virtual void* GetShape(std::size_t index) const = 0;

        /**
        * Gets the shape count on the document
        *@return the shape count on the document
        */
        virtual std::size_t GetShapeCount() const = 0;

        /**
        * Sets the document touched (i.e. modified)
        */
        virtual void Touch();

        /**
        * Sets the document untouched (i.e. unmodified)
        */
        virtual void Untouch();

        /**
        * Checks if the document was touched (i.e. modified)
        */
        virtual bool IsTouched() const;

        /**
        * Loads the document content from a file
        *@param fileName - file name
        *@param hWnd - handle of the window owning the document
        *@return newly created geometric document from file, NULL on error
        */
        static TGeometricDocument* Load(const std::string& fileName, HWND hWnd);

        /**
        * Saves the document content to a file
        *@param fileName - file name
        *@return true on success, otherwise false
        */
        virtual bool Save(const std::string& fileName);

    protected:
        std::size_t m_FocusedIndex;

        /**
        * Reads the document content from a xml object
        *@param pNode - xml document root node to read from
        *@return true on success, otherwise false
        */
        virtual bool Read(XMLNode* pNode);

        /**
        * Writes the document content to a xml object
        *@param doc - xml document to write to
        *@return true on success, otherwise false
        */
        virtual bool Write(XMLDoc& doc) const;

        /**
        * Called when the content of a document should be read
        *@param doc - xml document root node to read from
        *@return true on success, otherwise false
        */
        virtual bool DoReadContent(XMLNode* pNode) = 0;

        /**
        * Called when the content of a document should be written
        *@param doc - xml document to write to
        *@return true on success, otherwise false
        */
        virtual bool DoWriteContent(XMLDoc& doc) const = 0;

        /**
        * Gets a random color
        *@return random color
        */
        virtual DWF_Color GetRandomColor() const;

    private:
        DWF_Color   m_BackgroundColor;
        DWF_Color   m_GridColor;
        std::size_t m_GridOffset;
        bool        m_Touched;
};

#endif
