#ifndef TMatrixTableH
#define TMatrixTableH

// vcl
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>

// interface
#include "TGenericTable.h"

// std
#include <map>

// dwarfStar engine
#include "DWF_Geometry_Matrix.h"

/**
* A component showing a matrix content
*@author Jean-Milost Reymond
*/
class TMatrixTable : public TGenericTable
{
    __published:
        TPanel *paBackground;
        TGridPanel *gpMatrix;
        TLabel *laColumn1;
        TLabel *laColumn2;
        TLabel *laColumn3;
        TLabel *laHeader;
        TLabel *laColumn4;
        TLabel *laLine1;
        TEdit *edValue11;
        TEdit *edValue12;
        TEdit *edValue13;
        TEdit *edValue14;
        TLabel *laLine2;
        TEdit *edValue21;
        TEdit *edValue22;
        TEdit *edValue23;
        TEdit *edValue24;
        TLabel *laLine3;
        TEdit *edValue31;
        TEdit *edValue32;
        TEdit *edValue33;
        TEdit *edValue34;
        TLabel *laLine4;
        TEdit *edValue41;
        TEdit *edValue42;
        TEdit *edValue43;
        TEdit *edValue44;

        void __fastcall edValueChange(TObject* pSender);

    public:
        __fastcall TMatrixTable(TComponent* pOwner);

        /**
        * Sets 3x3 matrix table
        */
        void Set3x3();

        /**
        * Gets the 3x3 matrix
        *@return the matrix
        */
        DWF_Geometry::DWF_Matrix3x3F GetMatrix3x3() const;

        /**
        * Gets the 4x4 matrix
        *@return the matrix
        */
        DWF_Geometry::DWF_Matrix4x4F GetMatrix4x4() const;

        /**
        * Sets the 3x3 matrix
        *@param matrix - matrix to set
        */
        void TMatrixTable::SetMatrix3x3(const DWF_Geometry::DWF_Matrix3x3F& matrix);

        /**
        * Sets a 4x4 matrix
        *@param matrix - matrix to set
        */
        void TMatrixTable::SetMatrix4x4(const DWF_Geometry::DWF_Matrix4x4F& matrix);

        /**
        * Realign the grid content manually, because the VCL grid component is so stupidly bugged
        * that it is simply unable to do that
        */
        void RealignContent();
};
extern PACKAGE TMatrixTable* MatrixTable;
#endif
