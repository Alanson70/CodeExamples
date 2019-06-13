//---------------------------------------------------------------------------

#ifndef ParamsFormUnitH
#define ParamsFormUnitH
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
class TParamsForm : public TForm
{
__published:	// IDE-managed Components
        TButton *CancelButton;
        TButton *OkButton;
        TGroupBox *SendingGroupBox;
        TLabel *Label2;
        TComboBox *AdditionSendingOptionComboBox;
        TEdit *StringEndSendingOptionEdit;
        TCheckBox *EchoCheckBox;
        TGroupBox *ReceivingGroupBox;
        TLabel *Label9;
        TComboBox *AdditionReceivingOptionComboBox;
        TEdit *StringEndReceivingOptionEdit;
        void __fastcall StringEndOptionEditChange(TObject *Sender);
        void __fastcall AdditionSendingOptionComboBoxChange(
          TObject *Sender);
        void __fastcall AdditionReceivingOptionComboBoxChange(
          TObject *Sender);
private:	// User declarations
public:		// User declarations
  __fastcall TParamsForm(TComponent* Owner);
//  bool _connecting;
 // bool _connected;

 // TComponent *_outputClient;
//  void __fastcall ReadReady(TObject *Sender);
//  void __fastcall CanWrite(TObject *Sender);
//  void __fastcall IsError(TObject *Sender);

 // void Write(char *buffer,int count);
//  int Read(char *buffer,int count);

//  Callback OnReadReady;
 // Callback OnChangeStatus;

 // void Connect();

  //AnsiString SendingAddition();
 // AnsiString ReceivingAddition();

 // void LoadProfile(ASS fileName);
//  void SaveProfileAs(ASS fileName);
 // void SaveProfile();
  //void CloseProfile();

  //ASS _fileName;
};
//---------------------------------------------------------------------------
extern PACKAGE TParamsForm *ParamsForm;
//---------------------------------------------------------------------------
#endif
