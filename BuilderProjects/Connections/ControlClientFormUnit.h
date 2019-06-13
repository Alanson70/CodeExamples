//---------------------------------------------------------------------------

#ifndef ControlClientFormUnitH
#define ControlClientFormUnitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include "Functions.h"
#include "OutputClient.h"
#include "ControlClientUnit.h"
//---------------------------------------------------------------------------
class TControlClientForm : public TForm
{
__published:	// IDE-managed Components
        TPageControl *CommPageControl;
        TTabSheet *PortTabSheet;
        TPageControl *TermPageControl;
        TTabSheet *IPTabSheet;
        TPanel *IpPanel;
        TLabel *Label6;
        TLabel *Label7;
        TLabel *Label1;
        TEdit *IpAddrEdit;
        TEdit *IpPortEdit;
        TComboBox *IpComboBox;
        TCheckBox *AutoConnectCheckBox;
        TTabSheet *TtyTabSheet;
        TPanel *TtyPanel;
        TLabel *Label3;
        TLabel *Label4;
        TLabel *Label5;
        TComboBox *TtyRateComboBox;
        TComboBox *TtyPortComboBox;
        TComboBox *TtyParityComboBox;
        TTabSheet *ParamsTabSheet;
        TPanel *ParamPanel;
        TLabel *Label8;
        TLabel *Label9;
        TLabel *Label10;
        TLabel *Label11;
        TLabel *Label2;
        TLabel *Label12;
        TComboBox *AdditionSendingOptionComboBox;
        TComboBox *AdditionReceivingOptionComboBox;
        TEdit *StringEndSendingOptionEdit;
        TEdit *StringEndReceivingOptionEdit;
        TEdit *PrefixSendingEdit;
        TEdit *PrefixReceivingEdit;
        TButton *ConnectButton;
        TButton *DisconnectButton;
        TPanel *StatusLampPanel;
        TLabel *Label13;
        TLabel *StatusLabel;
        TEdit *StatusEdit;
        TTimer *StatusTimer;
        TTimer *IPConnectTimer;
        void __fastcall AdditionOptionComboBoxChange(
          TObject *Sender);
        void __fastcall StringEndOptionEditChange(TObject *Sender);
        void __fastcall ConnectButtonClick(TObject *Sender);
        void __fastcall DisconnectButtonClick(TObject *Sender);
        void __fastcall PrefixEditChange(TObject *Sender);
        void __fastcall IPConnectTimerTimer(TObject *Sender);
        void __fastcall StatusTimerTimer(TObject *Sender);
private:	// User declarations
public:		// User declarations
  __fastcall TControlClientForm(TComponent* Owner); 
  void LoadInits(ASS fileName);
  void SaveInits(ASS fileName);



  TControlClient *_Client;

  int _connectStatus;
  void ConnectStatus(int status);
  int ConnectStatus();
  void Connect();
  void Disconnect();
  //void  __fastcall OnClientConnected(TObject *Sender);
  //void  __fastcall OnClientError(TObject *Sender);
 // void  __fastcall OnClientDisconnected(TObject *Sender);
  void  __fastcall OnClientCanWrite(TObject *Sender);
  void  __fastcall OnClientReadReady(TObject *Sender);
  void  __fastcall OnClientChangeConnectStatus(TObject *Sender);

  int Write(char *buffer,int count);
  int Read(char *buffer,int count);
  ASS Read();

//  Callback OnConnecting;
//  Callback OnConnected;
//  Callback OnDisconnected;
  Callback OnReadReady;
  Callback OnCanWrite;
//  Callback OnError;
  Callback OnChangeConnectStatus;
};
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
#endif
