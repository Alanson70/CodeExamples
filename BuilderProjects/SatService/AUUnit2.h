//---------------------------------------------------------------------------
#ifndef AUUnit2H
#define AUUnit2H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Db.hpp>
#include <DBTables.hpp>
//---------------------------------------------------------------------------
class TAUDataModule1 : public TDataModule
{
__published:	// IDE-managed Components
    TTable *AUTable;
    TDataSource *AUDataSource;
    TDatabase *Database;
private:	// User declarations
public:		// User declarations
    __fastcall TAUDataModule1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TAUDataModule1 *AUDataModule1;
//---------------------------------------------------------------------------
#endif
