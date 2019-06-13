//---------------------------------------------------------------------------

#ifndef ControlFormUnitH
#define ControlFormUnitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <ComCtrls.hpp> 
#include "Functions.h"

typedef void __fastcall (__closure *Callback)(TObject *Sender);
//---------------------------------------------------------------------------
class TControlForm : public TForm
{
__published:	// IDE-managed Components
        TButton *CancelButton;
        TPageControl *PageControl1;
        TTabSheet *TtyTabSheet;
        TButton *OkButton;
        TTabSheet *IPTabSheet;
        TPanel *IpPanel;
        TLabel *Label6;
        TLabel *Label7;
        TLabel *Label1;
        TEdit *IpAddrEdit;
        TEdit *IpPortEdit;
        TComboBox *IpComboBox;
        TButton *ConnectButton;
        TButton *DisconnectButton;
        TPanel *TtyPanel;
        TLabel *Label3;
        TLabel *Label4;
        TLabel *Label5;
        TComboBox *TtyRateComboBox;
        TComboBox *TtyPortComboBox;
        TComboBox *TtyParityComboBox;
        TButton *ParamsButton;
        void __fastcall CancelButtonClick(TObject *Sender);
        void __fastcall FormShow(TObject *Sender);
        void __fastcall DisconnectButtonClick(TObject *Sender);
        void __fastcall StringEndOptionEditChange(TObject *Sender);
        void __fastcall ParamsButtonClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
  __fastcall TControlForm(TComponent* Owner);
 // bool _connecting;
 // bool _connected;

 // TComponent *_outputClient;
 // void __fastcall ReadReady(TObject *Sender);
 // void __fastcall CanWrite(TObject *Sender);
 // void __fastcall IsError(TObject *Sender);


  //Callback OnReadReady;
  //Callback OnChangeStatus;


  Callback OnApply;
  Callback OnParams;
  Callback OnDisconnect;

  //void Connect();

 // AnsiString SendingAddition();
  //AnsiString ReceivingAddition();

 // void LoadProfile(ASS fileName);
  //void SaveProfileAs(ASS fileName);
  //void SaveProfile();
  //void CloseProfile();

  //ASS _fileName;
  void TtyRate(ASS rate);
  ASS TtyRate();
  void TtyName(ASS name);
  ASS TtyName();
  void TtyParity(ASS par);
  ASS TtyParity();

  void Mode(int mode);

};
//---------------------------------------------------------------------------
extern PACKAGE TControlForm *ControlForm;
//---------------------------------------------------------------------------
#endif
