/****************************************************************************
 * ==> TGeometricVectorFrame -----------------------------------------------*
 ****************************************************************************
 * Description : This module provides a frame to edit a vector content      *
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

#ifndef TGeometricVectorFrameH
#define TGeometricVectorFrameH

// vcl
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>

// std
#include <string>

/**
* Frame to edit a vector content
*@author Jean-Milost Reymond
*/
class TGeometricVectorFrame : public TFrame
{
    __published:
        TPanel *paMain;
        TLabel *laX;
        TEdit *edX;
        TEdit *edY;
        TLabel *laY;
        TEdit *edZ;
        TLabel *laZ;

        void __fastcall edXChange(TObject* pSender);
        void __fastcall edYChange(TObject* pSender);
        void __fastcall edZChange(TObject* pSender);

    public:
        /**
        * Constructor
        *@param pOwner - frame owner
        */
        __fastcall TGeometricVectorFrame(TComponent* pOwner);

        /**
        * Hides the vector Z component
        */
        void HideZ();

        /**
        * Gets the vector X value
        *@return the vector X value
        */
        float GetX() const;

        /**
        * Sets the vector X value
        *@param value - the vector X value
        */
        void SetX(float value);

        /**
        * Gets the vector Y value
        *@return the vector Y value
        */
        float GetY() const;

        /**
        * Sets the vector Y value
        *@param value - the vector Y value
        */
        void SetY(float value);

        /**
        * Gets the vector Z value
        *@return the vector Z value
        */
        float GetZ() const;

        /**
        * Sets the vector Z value
        *@param value - the vector Z value
        */
        void SetZ(float value);

    private:
        std::wstring m_LastValidX;
        std::wstring m_LastValidY;
        std::wstring m_LastValidZ;
};
extern PACKAGE TGeometricVectorFrame* GeometricVectorFrame;
#endif
