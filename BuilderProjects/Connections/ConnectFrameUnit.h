//---------------------------------------------------------------------------


#ifndef ConnectFrameUnitH
#define ConnectFrameUnitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>     
#include "Functions.h"  
#include "OutputClient.h"
//---------------------------------------------------------------------------
class TConnectFrame : public TFrame
{
__published:	// IDE-managed Components
        TPageControl *CommPageControl;
        TTabSheet *PortTabSheet;
        TPageControl *TermPageControl;
        TTabSheet *TtyTabSheet;
        TPanel *TtyPanel;
        TLabel *Label3;
        TLabel *Label4;
        TLabel *Label5;
        TComboBox *TtyRateComboBox;
        TComboBox *TtyPortComboBox;
        TComboBox *TtyParityComboBox;
        TTabSheet *IPTabSheet;
        TPanel *IpPanel;
        TLabel *Label6;
        TLabel *Label7;
        TLabel *Label1;
        TEdit *IpAddrEdit;
        TEdit *IpPortEdit;
        TComboBox *IpComboBox;
        TCheckBox *AutoConnectCheckBox;
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
        TLabel *Label13;
        TPanel *StatusLampPanel;
        TTimer *IPConnectTimer;
        TTimer *StatusTimer;
        TTimer *CanWriteTimer;
        TLabel *Label14;
        TEdit *StatusEdit;
        void __fastcall AdditionOptionComboBoxChange(
          TObject *Sender);
        void __fastcall DisconnectButtonClick(TObject *Sender);
        void __fastcall ConnectButtonClick(TObject *Sender);
        void __fastcall StatusTimerTimer(TObject *Sender);
        void __fastcall CanWriteTimerTimer(TObject *Sender);
        void __fastcall StringEndOptionEditChange(TObject *Sender);
        void __fastcall IPConnectTimerTimer(TObject *Sender);
private:	// User declarations
public:		// User declarations
  __fastcall TConnectFrame(TComponent* Owner);
  __fastcall ~TConnectFrame();
  void LoadInits(ASS fileName);
  void SaveInits(ASS fileName);

  TComponent *_outputClient;
  int _connectStatus;
  void ConnectStatus(int status); 
  int ConnectStatus();

  ASS _sendAddition;
  ASS _recAddition;

  char _receiveBuffer[OC_MAX_COUNT];
  int _receiveCount;
  void __fastcall ReadReady(TObject *Sender);
  void __fastcall CanWrite(TObject *Sender);
  void __fastcall IsError(TObject *Sender);
  bool _canWrite;
  void __fastcall OnCanSend(TObject *Sender);

  void Connect();
  void Disconnect();
  void Write(char *buffer,int count);
  int Read(char *buffer,int count);
};
//---------------------------------------------------------------------------
extern PACKAGE TConnectFrame *ConnectFrame;
//---------------------------------------------------------------------------
#endif
