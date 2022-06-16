#include <vcl.h>
#pragma hdrstop
#include "TGenericTable.h"

#pragma package(smart_init)
#pragma resource "*.dfm"

//---------------------------------------------------------------------------
TGenericTable* GenericTable;
//---------------------------------------------------------------------------
__fastcall TGenericTable::TGenericTable(TComponent* pOwner) :
    TFrame(pOwner)
{}
//---------------------------------------------------------------------------
void TGenericTable::BuildLastKnownValueCache(TGridPanel* pTable)
{
    if (!pTable)
        return;

    // initialize the last known value table
    for (int i = 0; i < pTable->ColumnCollection->Count; ++i)
        for (int j = 0; j < pTable->RowCollection->Count; ++j)
        {
            // get control contained in cell as an edit control
            TEdit* pEdit =
                    dynamic_cast<TEdit*>(pTable->ControlCollection->ControlItems[i][j]->Control);

            // succeeded?
            if (!pEdit)
                continue;

            m_LastKnowValidValueDictionary[pEdit] = pEdit->Text.c_str();
        }
}
//---------------------------------------------------------------------------
void TGenericTable::OnValueChange(TObject* pSender)
{
    // get the edit containing the text to check
    TEdit* pEdit = dynamic_cast<TEdit*>(pSender);

    if (!pEdit)
        return;

    // is text empty or just containing a "-" value? (Meaning that further info will be entered later)
    if (pEdit->Text.IsEmpty() || pEdit->Text == L"-")
        return;

    // get the last known value for this edit
    IValueDictionary::iterator it = m_LastKnowValidValueDictionary.find(pSender);

    // is value not found? (Should never happen)
    if (it == m_LastKnowValidValueDictionary.end())
        return;

    try
    {
        // try to convert the text to float
        ::StrToFloat(pEdit->Text);
    }
    catch (...)
    {
        // get the caret position
        const int caret = pEdit->SelStart;

        // on failure revert to the last known valid value
        pEdit->Text = UnicodeString(it->second.c_str());

        pEdit->SelStart  = caret ? caret - 1 : 0;
        pEdit->SelLength = 0;
        return;
    }

    // update the last known value
    it->second = pEdit->Text.c_str();
}
//---------------------------------------------------------------------------
