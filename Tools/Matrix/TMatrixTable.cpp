#include <vcl.h>
#pragma hdrstop
#include "TMatrixTable.h"

#pragma package(smart_init)
#pragma link "TGenericTable"
#pragma resource "*.dfm"

//---------------------------------------------------------------------------
TMatrixTable* MatrixTable;
//---------------------------------------------------------------------------
__fastcall TMatrixTable::TMatrixTable(TComponent* pOwner) :
    TGenericTable(pOwner)
{
    BuildLastKnownValueCache(gpMatrix);
}
//---------------------------------------------------------------------------
void TMatrixTable::Set3x3()
{
    // disable all rows on last column
    for (int i = 1; i < gpMatrix->RowCollection->Count; ++i)
    {
        // get control contained in cell as an edit control
        TEdit* pEdit = dynamic_cast<TEdit*>(gpMatrix->ControlCollection->ControlItems[4][i]->Control);

        // succeeded?
        if (!pEdit)
            continue;

        // disable it
        pEdit->Enabled = false;
    }

    // disable all columns on last row
    for (int i = 1; i < gpMatrix->ColumnCollection->Count; ++i)
    {
        // get control contained in cell as an edit control
        TEdit* pEdit = dynamic_cast<TEdit*>(gpMatrix->ControlCollection->ControlItems[i][4]->Control);

        // succeeded?
        if (!pEdit)
            continue;

        // disable it
        pEdit->Enabled = false;
    }
}
//---------------------------------------------------------------------------
void __fastcall TMatrixTable::edValueChange(TObject* pSender)
{
    OnValueChange(pSender);
}
//---------------------------------------------------------------------------
DWF_Geometry::DWF_Matrix3x3F TMatrixTable::GetMatrix3x3() const
{
    DWF_Geometry::DWF_Matrix3x3F matrix;

    // get the matrix content
    for (int i = 1; i < gpMatrix->ColumnCollection->Count - 1; ++i)
        for (int j = 1; j < gpMatrix->RowCollection->Count - 1; ++j)
        {
            // get control contained in cell as an edit control
            TEdit* pEdit =
                    dynamic_cast<TEdit*>(gpMatrix->ControlCollection->ControlItems[i][j]->Control);

            // succeeded?
            if (!pEdit)
                continue;

            // get the matrix table item
            matrix.m_Table[i - 1][j - 1] = ::StrToFloat(pEdit->Text);
        }

    return matrix;
}
//---------------------------------------------------------------------------
DWF_Geometry::DWF_Matrix4x4F TMatrixTable::GetMatrix4x4() const
{
    DWF_Geometry::DWF_Matrix4x4F matrix;

    // get the matrix content
    for (int i = 1; i < gpMatrix->ColumnCollection->Count; ++i)
        for (int j = 1; j < gpMatrix->RowCollection->Count; ++j)
        {
            // get control contained in cell as an edit control
            TEdit* pEdit =
                    dynamic_cast<TEdit*>(gpMatrix->ControlCollection->ControlItems[i][j]->Control);

            // succeeded?
            if (!pEdit)
                continue;

            // get the matrix table item
            matrix.m_Table[i - 1][j - 1] = ::StrToFloat(pEdit->Text);
        }

    return matrix;
}
//---------------------------------------------------------------------------
void TMatrixTable::SetMatrix3x3(const DWF_Geometry::DWF_Matrix3x3F& matrix)
{
    // get the matrix content
    for (int i = 1; i < gpMatrix->ColumnCollection->Count - 1; ++i)
        for (int j = 1; j < gpMatrix->RowCollection->Count - 1; ++j)
        {
            // get control contained in cell as an edit control
            TEdit* pEdit =
                    dynamic_cast<TEdit*>(gpMatrix->ControlCollection->ControlItems[i][j]->Control);

            // succeeded?
            if (!pEdit)
                continue;

            // set the matrix table item
            pEdit->Text = ::FloatToStr(matrix.m_Table[i - 1][j - 1]);
        }
}
//---------------------------------------------------------------------------
void TMatrixTable::SetMatrix4x4(const DWF_Geometry::DWF_Matrix4x4F& matrix)
{
    // get the matrix content
    for (int i = 1; i < gpMatrix->ColumnCollection->Count; ++i)
        for (int j = 1; j < gpMatrix->RowCollection->Count; ++j)
        {
            // get control contained in cell as an edit control
            TEdit* pEdit =
                    dynamic_cast<TEdit*>(gpMatrix->ControlCollection->ControlItems[i][j]->Control);

            // succeeded?
            if (!pEdit)
                continue;

            // set the matrix table item
            pEdit->Text = ::FloatToStr(matrix.m_Table[i - 1][j - 1]);
        }
}
//---------------------------------------------------------------------------
void TMatrixTable::RealignContent()
{
    // iterate through the grid items
    for (int i = 0; i < gpMatrix->ColumnCollection->Count; ++i)
        for (int j = 0; j < gpMatrix->RowCollection->Count; ++j)
        {
            // get control contained in cell
            TControl* pControl = gpMatrix->ControlCollection->ControlItems[i][j]->Control;

            // succeeded?
            if (!pControl)
                continue;

            // get the cell rect
            const TRect cellRect = gpMatrix->CellRect[i][j];

            // get control as label
            TLabel* pLabel = dynamic_cast<TLabel*>(pControl);

            // recalculate the correct width, if required
            if (!pLabel || !pLabel->AutoSize)
                pControl->Width  = cellRect.Width() - (pControl->Margins->Left + pControl->Margins->Right);

            // update the control position (to keep it center in the rect)
            pControl->Left = cellRect.Left + (cellRect.Width( ) >> 1 - (pControl->Width  >> 1));
            pControl->Top  = cellRect.Top  + (cellRect.Height() >> 1 - (pControl->Height >> 1));
        }
}
//---------------------------------------------------------------------------
