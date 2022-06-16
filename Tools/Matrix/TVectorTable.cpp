#include <vcl.h>
#pragma hdrstop
#include "TVectorTable.h"

#pragma package(smart_init)
#pragma link "TGenericTable"
#pragma resource "*.dfm"

//---------------------------------------------------------------------------
TVectorTable* VectorTable;
//---------------------------------------------------------------------------
__fastcall TVectorTable::TVectorTable(TComponent* pOwner) :
    TGenericTable(pOwner)
{
    BuildLastKnownValueCache(gpVector);
}
//---------------------------------------------------------------------------
void TVectorTable::SetVec2D()
{
    // get control contained in last cell as an edit control
    TEdit* pEdit = dynamic_cast<TEdit*>(gpVector->ControlCollection->ControlItems[2][1]->Control);

    // succeeded?
    if (pEdit)
        // disable it
        pEdit->Enabled = false;
}
//---------------------------------------------------------------------------
void __fastcall TVectorTable::edValueChange(TObject* pSender)
{
    OnValueChange(pSender);
}
//---------------------------------------------------------------------------
DWF_Geometry::DWF_Vector2DF TVectorTable::GetVector2D() const
{
    DWF_Geometry::DWF_Vector2DF vector;

    // get edit control containing the X value
    TEdit* pEdit = dynamic_cast<TEdit*>(gpVector->ControlCollection->ControlItems[0][1]->Control);

    // succeeded?
    if (pEdit)
        // get the value
        vector.m_X = ::StrToFloat(pEdit->Text);

    // get edit control containing the Y value
    pEdit = dynamic_cast<TEdit*>(gpVector->ControlCollection->ControlItems[1][1]->Control);

    // succeeded?
    if (pEdit)
        // get the value
        vector.m_Y = ::StrToFloat(pEdit->Text);

    return vector;
}
//---------------------------------------------------------------------------
DWF_Geometry::DWF_Vector3DF TVectorTable::GetVector3D() const
{
    DWF_Geometry::DWF_Vector3DF vector;

    // get edit control containing the X value
    TEdit* pEdit = dynamic_cast<TEdit*>(gpVector->ControlCollection->ControlItems[0][1]->Control);

    // succeeded?
    if (pEdit)
        // get the value
        vector.m_X = ::StrToFloat(pEdit->Text);

    // get edit control containing the Y value
    pEdit = dynamic_cast<TEdit*>(gpVector->ControlCollection->ControlItems[1][1]->Control);

    // succeeded?
    if (pEdit)
        // get the value
        vector.m_Y = ::StrToFloat(pEdit->Text);

    // get edit control containing the Z value
    pEdit = dynamic_cast<TEdit*>(gpVector->ControlCollection->ControlItems[2][1]->Control);

    // succeeded?
    if (pEdit)
        // get the value
        vector.m_Z = ::StrToFloat(pEdit->Text);

    return vector;
}
//---------------------------------------------------------------------------
void TVectorTable::RealignContent()
{
    // iterate through the grid items
    for (int i = 0; i < gpVector->ColumnCollection->Count; ++i)
        for (int j = 0; j < gpVector->RowCollection->Count; ++j)
        {
            // get control contained in cell
            TControl* pControl = gpVector->ControlCollection->ControlItems[i][j]->Control;

            // succeeded?
            if (!pControl)
                continue;

            // get the cell rect
            const TRect cellRect = gpVector->CellRect[i][j];

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
