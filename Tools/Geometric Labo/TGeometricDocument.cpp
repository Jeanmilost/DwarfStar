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

#pragma hdrstop
#include "TGeometricDocument.h"

// interface
#include "TGeometricDocument2D.h"
#include "TGeometricDocument3D.h"
#include "TGeometricDocumentTags.h"

//---------------------------------------------------------------------------
// TGeometricDocument
//---------------------------------------------------------------------------
TGeometricDocument::TGeometricDocument() :
    m_FocusedIndex(0),
    m_BackgroundColor(clWhite),
    m_GridColor(clSilver),
    m_GridOffset(20),
    m_Touched(false)
{
    // initialize the random seed, to allow document to pick a random color for the new shapes
    std::srand(::GetTickCount());
}
//---------------------------------------------------------------------------
TGeometricDocument::~TGeometricDocument()
{}
//---------------------------------------------------------------------------
DWF_Color TGeometricDocument::GetBackgroundColor() const
{
    return m_BackgroundColor;
}
//---------------------------------------------------------------------------
void TGeometricDocument::SetBackgroundColor(const DWF_Color& color)
{
    m_BackgroundColor = color;
}
//---------------------------------------------------------------------------
DWF_Color TGeometricDocument::GetGridColor() const
{
    return m_GridColor;
}
//---------------------------------------------------------------------------
void TGeometricDocument::SetGridColor(const DWF_Color& color)
{
    m_GridColor = color;
}
//---------------------------------------------------------------------------
std::size_t TGeometricDocument::GetGridOffset() const
{
    return m_GridOffset;
}
//---------------------------------------------------------------------------
void TGeometricDocument::SetGridOffset(std::size_t offset)
{
    m_GridOffset = offset;
}
//---------------------------------------------------------------------------
void TGeometricDocument::Focus(std::size_t index)
{
    // get the shape count the document contains
    const std::size_t shapeCount = GetShapeCount();

    // is index out of bounds?
    if (index >= shapeCount)
        return;

    // focus the shape at index
    m_FocusedIndex = index;
}
//---------------------------------------------------------------------------
void TGeometricDocument::FocusPrev()
{
    // get the shape count the document contains
    const std::size_t shapeCount = GetShapeCount();

    // no shape on the document?
    if (!shapeCount)
    {
        m_FocusedIndex = 0;
        return;
    }

    // focused index is becoming out of bounds?
    if (!m_FocusedIndex)
        // rectify it
        m_FocusedIndex = shapeCount;

    // focus the previous shape
    --m_FocusedIndex;
}
//---------------------------------------------------------------------------
void TGeometricDocument::FocusNext()
{
    // get the shape count the document contains
    const std::size_t shapeCount = GetShapeCount();

    // no shape on the document?
    if (!shapeCount)
    {
        m_FocusedIndex = 0;
        return;
    }

    // focus the next shape
    ++m_FocusedIndex;

    // focused index is becoming out of bounds?
    if (m_FocusedIndex >= shapeCount)
        // rectify it
        m_FocusedIndex = 0;
}
//---------------------------------------------------------------------------
void TGeometricDocument::Touch()
{
    m_Touched = true;
}
//---------------------------------------------------------------------------
void TGeometricDocument::Untouch()
{
    m_Touched = false;
}
//---------------------------------------------------------------------------
bool TGeometricDocument::IsTouched() const
{
    return m_Touched;
}
//---------------------------------------------------------------------------
TGeometricDocument* TGeometricDocument::Load(const std::string& fileName, HWND hWnd)
{
    std::auto_ptr<TGeometricDocument> pDocument;
    XMLDoc                            doc;

    try
    {
        // initialize the xml document
        XMLDoc_init(&doc);

        // read the document file content
        if (!XMLDoc_parse_file_DOM(fileName.c_str(), &doc))
            return false;

        // get the root node
        XMLNode* pNode = XMLDoc_root(&doc);

        // found it?
        if (!pNode)
            return false;

        // is the correct node?
        if (std::strcmp(pNode->tag, M_Geometric_Doc_Document_Tag) != 0)
            return false;

        // iterate through attributes
        for (int i = 0; i < pNode->n_attributes; ++i)
        {
            // get attribute
            XMLAttribute* pAttribute = &pNode->attributes[i];

            // found it?
            if (!pAttribute)
                continue;

            // found the document type attribute?
            if (std::strcmp(pAttribute->name, M_Geometric_Doc_Type_Tag) != 0)
                continue;

            // create the correct document type
            if (std::strcmp(pAttribute->value, M_Geometric_Doc_2D_Value) == 0)
                pDocument.reset(new TGeometricDocument2D());
            else
            if (std::strcmp(pAttribute->value, M_Geometric_Doc_3D_Value) == 0)
                pDocument.reset(new TGeometricDocument3D(hWnd));
        }

        // was document created correctly?
        if (pDocument.get())
            // read the document content
            if (pDocument->Read(pNode))
                pDocument->Untouch();
            else
                pDocument.reset();
    }
    catch (...)
    {
        XMLDoc_free(&doc);
        return NULL;
    }

    XMLDoc_free(&doc);

    return pDocument.release();
}
//---------------------------------------------------------------------------
bool TGeometricDocument::Save(const std::string& fileName)
{
    XMLDoc doc;

    try
    {
        // write the document content
        if (!Write(doc))
            return false;

        std::FILE* pFile;

        // open file for write
        pFile = std::fopen(fileName.c_str(), "w");

        // succeeded?
        if (!pFile)
            return false;

        // write the xml document
        if (!XMLDoc_print(&doc, pFile, "\n", "\t", 0, 0, 0))
            return false;

        std::fclose(pFile);
    }
    catch (...)
    {
        XMLDoc_free(&doc);
        return false;
    }

    XMLDoc_free(&doc);
    Untouch();

    return true;
}
//---------------------------------------------------------------------------
bool TGeometricDocument::Read(XMLNode* pNode)
{
    // no root node?
    if (!pNode)
        return false;

    return DoReadContent(pNode);
}
//---------------------------------------------------------------------------
bool TGeometricDocument::Write(XMLDoc& doc) const
{
    // create and initialize new xml document
    XMLDoc_init(&doc);

    // create new xml node to contain the header
    XMLNode* pNode = XMLNode_alloc();

    // succeeded?
    if (!pNode)
        return false;

    try
    {
        // set xml header content
        if (!XMLNode_set_tag(pNode, M_Geometric_Doc_Xml_Header))
            return false;

        // configure header node
        if (!XMLNode_set_type(pNode, TAG_INSTR))
            return false;

        // add xml header
        if (!XMLDoc_add_node(&doc, pNode))
            return false;
    }
    catch (...)
    {
        XMLNode_free(pNode);
        throw;
    }

    return DoWriteContent(doc);
}
//---------------------------------------------------------------------------
DWF_Color TGeometricDocument::GetRandomColor() const
{
    DWF_Color color;

    do
    {
        // generate a random RGB color
        color.SetColor(std::rand() % 255, std::rand() % 255, std::rand() % 255);
    }
    while (color.GetRGB() >= 0xDDDDDD);

    return color;
}
//---------------------------------------------------------------------------
