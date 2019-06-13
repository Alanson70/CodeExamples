object ServerForm: TServerForm
  Left = 285
  Top = 525
  Width = 575
  Height = 369
  Caption = 'ServerForm'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object Memo1: TMemo
    Left = 40
    Top = 96
    Width = 329
    Height = 161
    TabOrder = 0
  end
  object ClientButton: TButton
    Left = 424
    Top = 56
    Width = 75
    Height = 25
    Caption = 'New Client'
    TabOrder = 1
    OnClick = ClientButtonClick
  end
  object ServerSocket1: TServerSocket
    Active = False
    Port = 8000
    ServerType = stNonBlocking
    OnListen = ServerSocket1Listen
    OnAccept = ServerSocket1Accept
    OnGetSocket = ServerSocket1GetSocket
    OnThreadStart = ServerSocket1ThreadStart
    OnClientConnect = ServerSocket1ClientConnect
    OnClientDisconnect = ServerSocket1ClientDisconnect
    OnClientRead = ServerSocket1ClientRead
    OnClientError = ServerSocket1ClientError
    Left = 40
    Top = 32
  end
end
