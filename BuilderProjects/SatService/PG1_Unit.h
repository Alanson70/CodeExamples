//---------------------------------------------------------------------------
#ifndef PG1_UnitH
#define PG1_UnitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TPG1Form : public TForm
{
__published:	// IDE-managed Components
    TEdit *KURZSEdit;
    TEdit *KUTZSEdit;
    TEdit *QZSEdit;
    TEdit *LSNEdit;
    TEdit *LAFUEdit;
    TEdit *SSEdit;
    TEdit *POUTEdit;
    TEdit *KUKAEdit;
    TEdit *EKAEdit;
    TEdit *QKAEdit;
    TEdit *FUPEdit;
    TEdit *FDNEdit;
    TScrollBar *KUTZSScrollBar;
    TScrollBar *KURZSScrollBar;
    TScrollBar *QZSScrollBar;
    TScrollBar *LSNScrollBar;
    TScrollBar *LAFUScrollBar;
    TScrollBar *SSScrollBar;
    TScrollBar *POUTScrollBar;
    TScrollBar *KUKAScrollBar;
    TScrollBar *EKAScrollBar;
    TScrollBar *QKAScrollBar;
    TScrollBar *FUPScrollBar;
    TScrollBar *FDNScrollBar;
    TEdit *SSKAEdit;
    TEdit *dEdit;
    TEdit *KBEdit;
    TEdit *BEdit;
    TScrollBar *SSKAScrollBar;
    TScrollBar *dScrollBar;
    TScrollBar *BScrollBar;
    TEdit *LZSKAEdit;
    TEdit *LKAZSEdit;
    TScrollBar *LZSKAScrollBar;
    TScrollBar *LKAZSScrollBar;
    TEdit *EZSEdit;
    TEdit *PPKAEdit;
    TEdit *EZSEditM;
    TEdit *PPKAEditM;
    TEdit *EMZSEdit;
    TEdit *PPMKAEdit;
    TEdit *EMZSEditM;
    TEdit *PPMKAEditM;
    TEdit *EZSEditS;
    TEdit *PPKAEditS;
    TImage *Image1;
    TLabel *Label2;
    TLabel *Label3;
    TLabel *Label6;
    TLabel *Label9;
    TLabel *Label10;
    TLabel *Label11;
    TLabel *Label12;
    TLabel *Label13;
    TLabel *Label14;
    TLabel *Label15;
    TLabel *Label16;
    TLabel *Label18;
    TLabel *Label19;
    TLabel *Label23;
    TLabel *Label24;
    TLabel *Label28;
    TLabel *Label29;
    TLabel *Label1;
    TLabel *Label27;
    TLabel *Label4;
    TLabel *Label5;
    TLabel *Label7;
    TLabel *Label8;
    TLabel *Label17;
    TLabel *Label21;
    TLabel *Label25;
    TLabel *Label26;
    TLabel *Label30;
    void __fastcall ScrollBarChange(TObject *Sender);
    void __fastcall FormShow(TObject *Sender);
    
private:	// User declarations
public:		// User declarations
    __fastcall TPG1Form(TComponent* Owner);
  struct
  {
   double KUT;
   double KUR;
   double Q;
   double LSN;
   double LAFU;
   double SS;
   double P;
   double E;
   double B;
   double EM;
  }ZS;
  struct
  {
   double KU;
   double E;
   double Q;
   double FUP;
   double FDN;
   double SS;
   double d;
   double KB;
   double KB1;
   double LZSKA;
   double LKAZS;
   double WZSKA;
   double WKAZS;
   double PP;
   double PPM;
  }KA;
};
//---------------------------------------------------------------------------
extern PACKAGE TPG1Form *PG1Form;
//---------------------------------------------------------------------------
#endif
