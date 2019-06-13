object ProfileDialogForm: TProfileDialogForm
  Left = 668
  Top = 148
  BorderIcons = [biSystemMenu]
  BorderStyle = bsSingle
  Caption = 'ProfileDialogForm'
  ClientHeight = 248
  ClientWidth = 331
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object FileListBox1: TFileListBox
    Left = 8
    Top = 8
    Width = 313
    Height = 153
    FileEdit = Edit1
    ItemHeight = 16
    Mask = '*.sa3'
    TabOrder = 0
  end
  object Edit1: TEdit
    Left = 8
    Top = 168
    Width = 313
    Height = 21
    ReadOnly = True
    TabOrder = 1
    Text = '*.sa3'
    OnChange = Edit1Change
  end
  object OkButton: TButton
    Left = 160
    Top = 208
    Width = 75
    Height = 25
    Caption = 'Ok'
    ModalResult = 1
    TabOrder = 2
  end
  object CancelButton: TButton
    Left = 248
    Top = 208
    Width = 75
    Height = 25
    Cancel = True
    Caption = 'Cancel'
    ModalResult = 2
    TabOrder = 3
  end
end
