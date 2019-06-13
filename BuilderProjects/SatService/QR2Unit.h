//---------------------------------------------------------------------------
#ifndef QR2UnitH
#define QR2UnitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Qrctrls.hpp>
#include <quickrpt.hpp>
#include <DBCtrls.hpp>
#include <qrprntr.hpp>
#include <Dialogs.hpp>
#include <ComCtrls.hpp>
#include <Menus.hpp>
//---------------------------------------------------------------------------
class TRForm2 : public TForm
{
__published:	// IDE-managed Components
    TQRDBText *QRDBText1;
    TPrintDialog *PrintDialog1;
    TButton *Button1;
    TRichEdit *RichEdit1;
    TButton *Button2;
    TSaveDialog *SaveDialog1;
    TButton *Button3;
    TPopupMenu *PopupMenu1;
    TMenuItem *CutItem;
    TMenuItem *CopyItem;
    TMenuItem *PasteItem;
    void __fastcall Button1Click(TObject *Sender);
    void __fastcall FormShow(TObject *Sender);
    void __fastcall Button2Click(TObject *Sender);
    void __fastcall Button3Click(TObject *Sender);
    void __fastcall CutItemClick(TObject *Sender);
    void __fastcall CopyItemClick(TObject *Sender);
    void __fastcall PasteItemClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
    __fastcall TRForm2(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TRForm2 *RForm2;
//---------------------------------------------------------------------------
#endif
