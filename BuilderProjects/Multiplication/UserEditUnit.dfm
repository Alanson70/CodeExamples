object UserEditForm: TUserEditForm
  Left = 368
  Top = 229
  BorderIcons = [biSystemMenu]
  BorderStyle = bsDialog
  Caption = #1055#1077#1088#1077#1084#1085#1086#1078#1072#1090#1077#1083#1100
  ClientHeight = 108
  ClientWidth = 216
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poMainFormCenter
  PixelsPerInch = 96
  TextHeight = 13
  object UserEdit: TEdit
    Left = 16
    Top = 16
    Width = 177
    Height = 21
    TabOrder = 0
    OnChange = UserEditChange
  end
  object EditButton: TButton
    Left = 112
    Top = 56
    Width = 75
    Height = 25
    Caption = #1044#1086#1073#1072#1074#1080#1090#1100
    Enabled = False
    ModalResult = 1
    TabOrder = 1
  end
end
