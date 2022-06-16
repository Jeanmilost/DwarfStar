#ifndef MainH
#define MainH

// vcl
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ComCtrls.hpp>

// interface
#include "TGenericTable.h"
#include "TMatrixTable.h"
#include "TVectorTable.h"

// dwarfStar engine
#include "DWF_Geometry_Vector.h"
#include "DWF_Geometry_Matrix.h"
#include <Vcl.ExtCtrls.hpp>

class TMainForm : public TForm
{
    __published:
        TPageControl *pcMain;
        TTabSheet *tsMatrix3x3;
        TTabSheet *tsMatrix4x4;
        TMatrixTable *mt3x3Matrix;
        TLabel *laVec2DToTransform;
        TVectorTable *vtVec2DToTransform;
        TLabel *laTransformMatrix3x3;
        TVectorTable *vtVec2DResult;
        TLabel *laVec2DResult;
        TButton *btMat3x3Transform;
        TMatrixTable *mt4x4Matrix;
        TLabel *laVec3DToTransform;
        TVectorTable *vtVec3DToTransform;
        TLabel *laTransformMatrix4x4;
        TVectorTable *vtVec3DResult;
        TLabel *laVec3DResult;
        TButton *btMat4x4Transform;
        TButton *btMat3x3Inverse;
        TButton *btMat4x4Inverse;

        void __fastcall pcMainChange(TObject* pSender);
        void __fastcall btMat3x3InverseClick(TObject* pSender);
        void __fastcall btMat3x3TransformClick(TObject* pSender);
        void __fastcall btMat4x4InverseClick(TObject* pSender);
        void __fastcall btMat4x4TransformClick(TObject* pSender);

    public:
        __fastcall TMainForm(TComponent* pOwner);

    private:
        typedef std::vector<TControl*> IControls;

        /**
        * Distribute the VCL controls from top to bottom
        *@param controls - controls to distribute
        */
        void DistributeCtrlsTopToBottom(IControls& controls);
};
extern PACKAGE TMainForm* MainForm;
#endif
