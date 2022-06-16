#ifndef TVectorTableH
#define TVectorTableH

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
#include "DWF_Geometry_Vector.h"

/**
* A component showing a vector content
*@author Jean-Milost Reymond
*/
class TVectorTable : public TGenericTable
{
    __published:
        TGridPanel *gpVector;
        TPanel *paBackground;
        TLabel *laColumn1;
        TLabel *laColumn2;
        TLabel *laColumn3;
        TEdit *edValueX;
        TEdit *edValueY;
        TEdit *edValueZ;

        void __fastcall edValueChange(TObject* pSender);

    public:
        __fastcall TVectorTable(TComponent* pOwner);

        /**
        * Sets vector 2D table
        */
        void SetVec2D();

        /**
        * Gets the 2D vector
        *@return the vector
        */
        DWF_Geometry::DWF_Vector2DF GetVector2D() const;

        /**
        * Gets the 3D vector
        *@return the vector
        */
        DWF_Geometry::DWF_Vector3DF GetVector3D() const;

        /**
        * Realign the grid content manually, because the VCL grid component is so stupidly bugged
        * that it is simply unable to do that
        */
        void RealignContent();
};
extern PACKAGE TVectorTable* VectorTable;
#endif
