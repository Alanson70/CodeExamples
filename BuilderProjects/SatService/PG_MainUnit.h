//---------------------------------------------------------------------------
#ifndef PG_MainUnitH
#define PG_MainUnitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TPGForm : public TForm
{
__published:	// IDE-managed Components
    TLabel *Label1;
    TEdit *Edit1;
    TScrollBar *ScrollBar1;
    TLabel *Label2;
    TEdit *Edit2;
    TScrollBar *ScrollBar2;
    TLabel *Label3;
    TEdit *Edit3;
    TScrollBar *ScrollBar3;
    TLabel *Label4;
    TEdit *Edit4;
    TScrollBar *ScrollBar4;
    TLabel *Label5;
    TEdit *Edit5;
    TScrollBar *ScrollBar5;
    TLabel *Label6;
    TEdit *Edit6;
    TScrollBar *ScrollBar6;
    TLabel *Label7;
    TEdit *Edit7;
    TScrollBar *ScrollBar7;
    TLabel *Label8;
    TEdit *Edit8;
    TScrollBar *ScrollBar8;
    TLabel *Label9;
    TEdit *Edit9;
    TScrollBar *ScrollBar9;
    TLabel *Label10;
    TEdit *Edit10;
    TScrollBar *ScrollBar10;
    TLabel *Label21;
    TEdit *Edit11;
    TScrollBar *ScrollBar11;
    TLabel *Label11;
    TEdit *Edit12;
    TScrollBar *ScrollBar12;
    TLabel *Label12;
    TEdit *Edit13;
    TScrollBar *ScrollBar13;
    TLabel *Label13;
    TEdit *Edit14;
    TScrollBar *ScrollBar14;
    TLabel *Label14;
    TEdit *Edit15;
    TScrollBar *ScrollBar15;
    TLabel *Label15;
    TEdit *Edit16;
    TScrollBar *ScrollBar16;
    TLabel *Label16;
    TEdit *Edit17;
    TScrollBar *ScrollBar17;
    TLabel *Label17;
    TEdit *Edit18;
    TScrollBar *ScrollBar18;
    TLabel *Label18;
    TEdit *Edit19;
    TScrollBar *ScrollBar19;
    TLabel *Label19;
    TEdit *Edit20;
    TLabel *Label20;
    TEdit *Edit21;
    TLabel *Label22;
    TEdit *Edit22;
    TScrollBar *ScrollBar22;
    TLabel *Label23;
    TEdit *Edit23;
    TScrollBar *ScrollBar23;
    TLabel *Label24;
    TEdit *Edit24;
    TLabel *Label25;
    TEdit *Edit25;
    TLabel *Label26;
    TEdit *Edit26;
    TLabel *Label27;
    TEdit *Edit27;
    TLabel *Label28;
    TEdit *Edit28;
    TLabel *Label29;
    TEdit *Edit29;
    TLabel *Label30;
    TEdit *Edit30;
    TLabel *Label31;
    TEdit *Edit31;
    TLabel *Label32;
    TEdit *Edit32;
    TLabel *Label33;
    TEdit *Edit33;
    TLabel *Label34;
    TEdit *Edit34;
    TLabel *Label35;
    TEdit *Edit35;
    TLabel *Label36;
    TEdit *Edit36;
    TLabel *Label37;
    TEdit *Edit37;
    TLabel *Label38;
    TEdit *Edit38;
    TLabel *Label39;
    TEdit *Edit39;
    TLabel *Label40;
    TEdit *Edit40;
    TBevel *Bevel1;
    TComboBox *ComboBox21;
    TEdit *Edit20db;
    TEdit *Edit26a;
    void __fastcall FormShow(TObject *Sender); 
    void __fastcall OnChange(TObject *Sender);
    void __fastcall Recount(TObject *Sender);
private:	// User declarations
public:		// User declarations
    __fastcall TPGForm(TComponent* Owner);

   bool ChangeFlag;

   double TNKA;
   double TNZS;
   double EKA;
   double GTKA;
   double GKA;
   double GTZS;
   double GRZS;
   double PXY;
   double PAF;
   double PSN;
   double FTM;
   double FRM;
   double LT;
   double LR;
   double PLZSKA;
   double PLKAZS;
   double PKZSKA;
   double PKKAZS;
   double RINF;
   double B;
   double FEC;
   double W;
   double KU;
   double KB;
   double D;
   double L0;
   double L0a;
   double PZS;
   double EZS;
   double PINKA;
   double PINNKA;
   double PSNKA;
   double POUTKA;
   double POUTNKA;
   double EPKA;
   double PINZS;
   double PNZS;
   double PSNZS;
   double PINNZS;
   double PNCZS;
   double SNNC;
};
//---------------------------------------------------------------------------
extern PACKAGE TPGForm *PGForm;
//---------------------------------------------------------------------------
#endif
