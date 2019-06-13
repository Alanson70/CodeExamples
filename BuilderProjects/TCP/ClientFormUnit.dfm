object ClientForm: TClientForm
  Left = 988
  Top = 423
  Width = 524
  Height = 403
  Caption = 'ClientForm'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnClose = FormClose
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object SendEdit: TEdit
    Left = 56
    Top = 128
    Width = 121
    Height = 21
    TabOrder = 0
    Text = 'SendEdit'
  end
  object SendButton: TButton
    Left = 216
    Top = 128
    Width = 75
    Height = 25
    Caption = 'Send'
    Enabled = False
    TabOrder = 1
    OnClick = SendButtonClick
  end
  object ClientSocket1: TClientSocket
    Active = False
    ClientType = ctNonBlocking
    Host = 'localhost'
    Port = 8000
    OnConnect = ClientSocket1Connect
    OnDisconnect = ClientSocket1Disconnect
    Left = 72
    Top = 40
  end
end
