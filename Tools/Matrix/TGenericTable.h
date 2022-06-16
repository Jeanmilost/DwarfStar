#ifndef TGenericTableH
#define TGenericTableH

// vcl
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>

// std
#include <map>

/**
* A frame showing a generic content as a table
*@author Jean-Milost Reymond
*/
class TGenericTable : public TFrame
{
    __published:

    public:
        __fastcall TGenericTable(TComponent* pOwner);

    protected:
        /**
        * Build the last known values cache
        *@param pTable - table containing the values to cache
        */
        void BuildLastKnownValueCache(TGridPanel* pTable);

        /**
        * Called when a value changed in an edit box
        *@param pSender - event sender
        */
        void OnValueChange(TObject* pSender);

    private:
        typedef std::map<TObject*, std::wstring> IValueDictionary;

        IValueDictionary m_LastKnowValidValueDictionary;
};
extern PACKAGE TGenericTable* GenericTable;
#endif
