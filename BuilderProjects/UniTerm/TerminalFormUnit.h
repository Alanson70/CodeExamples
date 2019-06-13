//---------------------------------------------------------------------------

#ifndef TerminalFormUnitH
#define TerminalFormUnitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>

#include <Graphics.hpp> 
#include "Functions.h"    
#include "ControlClientFormUnit.h"
//---------------------------------------------------------------------------
class TTerminalForm : public TForm
{
__published:	// IDE-managed Components
        TMemo *Memo;
        TPanel *CommandPanel;
        TButton *SendButton;
        TComboBox *CommandCombo;
        TButton *ControlButton;
        TPanel *StatusPanel;
        TLabel *StatusLabel;
        TPanel *StatusLampPanel;
        TTimer *StatusTimer;
        TCheckBox *EchoCheckBox;
        void __fastcall SendButtonClick(TObject *Sender);
        void __fastcall ControlButtonClick(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall FormShow(TObject *Sender);
        void __fastcall StatusTimerTimer(TObject *Sender);
private:	// User declarations

public:		// User declarations
  __fastcall TTerminalForm(TComponent* Owner);

  void LoadProfile(ASS fileName);
  void SaveProfileAs(ASS fileName);
  void SaveProfile();
  void CloseProfile();
  ASS _profile;

  Callback OnTerminalCreate;
  Callback OnTerminalDestroy;
  void LoadCommands20();
  void SaveCommands20();

  TControlClientForm *_Client;
 // void  __fastcall OnClientConnected(TObject *Sender);
 // void  __fastcall OnClientError(TObject *Sender);
 // void  __fastcall OnClientDisconnected(TObject *Sender);
  void  __fastcall OnClientCanWrite(TObject *Sender);
  void  __fastcall OnClientReadReady(TObject *Sender);
  void  __fastcall OnClientChangeConnectStatus(TObject *Sender);
  void Connect();
  void ConnectStatus(int status);
  int ConnectStatus();
};
//---------------------------------------------------------------------------
extern PACKAGE TTerminalForm *TerminalForm;
//---------------------------------------------------------------------------
#endif
