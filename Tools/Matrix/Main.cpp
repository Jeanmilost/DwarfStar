#include <vcl.h>
#pragma hdrstop
#include "Main.h"

#pragma package(smart_init)
#pragma link "TGenericTable"
#pragma link "TMatrixTable"
#pragma link "TVectorTable"
#pragma resource "*.dfm"

//---------------------------------------------------------------------------
TMainForm* MainForm;
//---------------------------------------------------------------------------
__fastcall TMainForm::TMainForm(TComponent* pOwner) :
    TForm(pOwner)
{
    mt3x3Matrix->Set3x3();
    vtVec2DToTransform->SetVec2D();
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::btMat3x3InverseClick(TObject* pSender)
{
    float determinant;

    // inverse the matrix
    DWF_Geometry::DWF_Matrix3x3F invMat = mt3x3Matrix->GetMatrix3x3().Inverse(determinant);

    // show it
    mt3x3Matrix->SetMatrix3x3(invMat);
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::btMat3x3TransformClick(TObject* pSender)
{
    // apply the transformation
    const DWF_Geometry::DWF_Matrix3x3F matrix = mt3x3Matrix->GetMatrix3x3();
    const DWF_Geometry::DWF_Vector2DF  vector = vtVec2DToTransform->GetVector2D();
    const DWF_Geometry::DWF_Vector2DF  result = matrix.Transform(vector);

    // show the result
    vtVec2DResult->edValueX->Text = ::FloatToStr(result.m_X);
    vtVec2DResult->edValueY->Text = ::FloatToStr(result.m_Y);
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::btMat4x4InverseClick(TObject* pSender)
{
    float determinant;

    // inverse the matrix
    DWF_Geometry::DWF_Matrix4x4F invMat = mt4x4Matrix->GetMatrix4x4().Inverse(determinant);

    // show it
    mt4x4Matrix->SetMatrix4x4(invMat);
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::btMat4x4TransformClick(TObject* pSender)
{
    // apply the transformation
    const DWF_Geometry::DWF_Matrix4x4F matrix = mt4x4Matrix->GetMatrix4x4();
    const DWF_Geometry::DWF_Vector3DF  vector = vtVec3DToTransform->GetVector3D();
    const DWF_Geometry::DWF_Vector3DF  result = matrix.Transform(vector);

    // show the result
    vtVec3DResult->edValueX->Text = ::FloatToStr(result.m_X);
    vtVec3DResult->edValueY->Text = ::FloatToStr(result.m_Y);
    vtVec3DResult->edValueZ->Text = ::FloatToStr(result.m_Z);
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::pcMainChange(TObject* pSender)
{
    // realign the vector content, because the stupid VCL does not do his job
    vtVec2DToTransform->RealignContent();
    vtVec2DResult->RealignContent();
    vtVec3DToTransform->RealignContent();
    vtVec3DResult->RealignContent();

    // also realign the matrix content, for the exactly same reason
    mt3x3Matrix->RealignContent();
    mt4x4Matrix->RealignContent();

    // sort the controls manually, after they were completely broken by the stupid VCL
    IControls controls3x3;
    controls3x3.push_back(laTransformMatrix3x3);
    controls3x3.push_back(mt3x3Matrix);
    controls3x3.push_back(btMat3x3Inverse);
    controls3x3.push_back(laVec2DToTransform);
    controls3x3.push_back(vtVec2DToTransform);
    controls3x3.push_back(btMat3x3Transform);
    controls3x3.push_back(laVec2DResult);
    controls3x3.push_back(vtVec2DResult);
    DistributeCtrlsTopToBottom(controls3x3);

    // same thing for the 4x4 interface
    IControls controls4x4;
    controls4x4.push_back(laTransformMatrix4x4);
    controls4x4.push_back(mt4x4Matrix);
    controls4x4.push_back(btMat4x4Inverse);
    controls4x4.push_back(laVec3DToTransform);
    controls4x4.push_back(vtVec3DToTransform);
    controls4x4.push_back(btMat4x4Transform);
    controls4x4.push_back(laVec3DResult);
    controls4x4.push_back(vtVec3DResult);
    DistributeCtrlsTopToBottom(controls4x4);
}
//---------------------------------------------------------------------------
void TMainForm::DistributeCtrlsTopToBottom(IControls& controls)
{
    int pos = 0;

    // iterate through controls to distribute
    for (std::size_t i = 0; i < controls.size(); ++i)
    {
        // is control visible?
        if (!controls[i]->Visible)
            continue;

        // place the control on the left
        controls[i]->Top = pos;

        // calculate the next position
        pos += controls[i]->Margins->ControlHeight;
    }
}
//---------------------------------------------------------------------------
