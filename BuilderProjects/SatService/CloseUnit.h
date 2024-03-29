//---------------------------------------------------------------------------
#ifndef CloseUnitH
#define CloseUnitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class TCloseForm : public TForm
{
__published:	// IDE-managed Components
    TLabel *Label1;
    TLabel *Label2;
    TButton *Button1;
    TButton *Button2;
    TButton *Button3;
    void __fastcall Button1Click(TObject *Sender);
    void __fastcall Button2Click(TObject *Sender);
    void __fastcall Button3Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
    __fastcall TCloseForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TCloseForm *CloseForm;
//---------------------------------------------------------------------------
#endif
