//---------------------------------------------------------------------------

#ifndef ConnectorFormUnitH
#define ConnectorFormUnitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>  

#include "ConnectorUnit.h"
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TConnectorForm : public TForm
{
__published:	// IDE-managed Components
        TButton *CancelButton;
        TButton *ConnectButton;
        TButton *DisconnectButton;
        TPageControl *PageControl1;
        TTabSheet *StatusTabSheet;
        TLabel *Label2;
        TLabel *ReconnectRepeatLabel;
        TLabel *ConnectingTimerLabel;
        TLabel *Label5;
        TLabel *Label1;
        TLabel *Label4;
        TLabel *Label6;
        TComboBox *StatusCombo;
        TEdit *ReconnectRepeatEdit;
        TEdit *ConnectingTimerEdit;
        TEdit *SendCountEdit;
        TEdit *ReceiveCountEdit;
        TEdit *TimeEdit;
        TEdit *PingEdit;
        TTabSheet *InterfaceTabSheet;
        TPageControl *ConnectPageControl;
        TTabSheet *IPTabSheet;
        TLabel *Label12;
        TLabel *Label13;
        TLabel *Label14;
        TLabel *Label15;
        TComboBox *IpTypeComboBox;
        TEdit *IpAddrEdit;
        TComboBox *IpAddrComboBox;
        TEdit *IpPortEdit;
        TComboBox *ProtokolComboBox;
        TButton *IpAddrButton;
        TButton *Button1;
        TTabSheet *TtyTabSheet;
        TLabel *Label10;
        TLabel *Label11;
        TComboBox *TtyRateCombo;
        TComboBox *TtyPortCombo;
        TEdit *TtyEdit;
        TTabSheet *ATTabSheet;
        TLabel *Label7;
        TLabel *Label8;
        TLabel *InitStringLabel;
        TLabel *DialLabel;
        TLabel *Label9;
        TComboBox *AtRateCombo;
        TEdit *AtInitStringEdit;
        TComboBox *AtPortCombo;
        TComboBox *AtDialCombo;
        TEdit *AtCallingNumberEdit;
        TEdit *AtModemEdit;
        TCheckBox *DefaultInterfaceCheck;
        TCheckBox *UseTunnelCheck;
        TTabSheet *SettingsTabSheet;
        TCheckBox *ReconnectCheck;
        TEdit *ReconnectEdit;
        TUpDown *ReconnectUpDown;
        TUpDown *DisconnectUpDown;
        TEdit *DisconnectEdit;
        TCheckBox *DisconnectCheck;
        TCheckBox *ConnectingCheck;
        TEdit *ConnectingEdit;
        TUpDown *ConnectingUpDown;
        TCheckBox *PingCheck;
        TEdit *PingTimeEdit;
        TUpDown *PingTimeUpDown;
        TTimer *DrawTimer;
        void __fastcall DrawTimerTimer(TObject *Sender);
        void __fastcall ConnectButtonClick(TObject *Sender);
        void __fastcall DisconnectButtonClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
 __fastcall TConnectorForm(TComponent* Owner);
 TConnector *_Connector;
 void Connector(TConnector *);
 void DrawParams();
};
//---------------------------------------------------------------------------
extern PACKAGE TConnectorForm *ConnectorForm;
//---------------------------------------------------------------------------
#endif
