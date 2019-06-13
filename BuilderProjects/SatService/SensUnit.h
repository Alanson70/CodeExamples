//---------------------------------------------------------------------------
#ifndef SensUnitH
#define SensUnitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class TSensForm : public TForm
{
__published:	// IDE-managed Components
    TLabel *Label1;
    TLabel *Label2;
    TLabel *Label3;
    TLabel *Label4;
    TEdit *GMINEdit;
    TLabel *Label5;
    TEdit *GMAXEdit;
    TEdit *IMINEdit;
    TEdit *IMAXEdit;
    TEdit *GEdit;
    TEdit *IEdit;
    TEdit *SensEdit;
    TScrollBar *GMINScrollBar;
    TScrollBar *GMAXScrollBar;
    TScrollBar *GScrollBar;
    TScrollBar *IMINScrollBar;
    TScrollBar *IMAXScrollBar;
    TScrollBar *IScrollBar;
    TLabel *Label6;
    TScrollBar *GMINScrollBar1;
    TScrollBar *GMAXScrollBar1;
    TScrollBar *GScrollBar1;
    TLabel *Label7;
    TLabel *Label8;
    TLabel *Label9;
    TButton *Button1;
    TButton *Button2;
    void __fastcall GScrollBarChange(TObject *Sender);
    void __fastcall GMINScrollBarChange(TObject *Sender);
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall IScrollBarChange(TObject *Sender);
    void __fastcall IMINScrollBarChange(TObject *Sender);
    void __fastcall IEditChange(TObject *Sender);
    void __fastcall Button2Click(TObject *Sender);
    void __fastcall Button1Click(TObject *Sender);
    
private:	// User declarations
public:		// User declarations
    __fastcall TSensForm(TComponent* Owner);
    AnsiString __fastcall MinToText(long);
    long G;
    int I;
    double Sens;
};
//---------------------------------------------------------------------------
extern PACKAGE TSensForm *SensForm;
//---------------------------------------------------------------------------
#endif
