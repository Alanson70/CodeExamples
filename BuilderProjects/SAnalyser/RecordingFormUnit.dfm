object RecordingForm: TRecordingForm
  Left = 352
  Top = 311
  BorderIcons = []
  BorderStyle = bsSingle
  BorderWidth = 2
  Caption = #1042#1099#1087#1086#1083#1085#1077#1085#1080#1077' '#1079#1072#1087#1080#1089#1080
  ClientHeight = 226
  ClientWidth = 372
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poOwnerFormCenter
  DesignSize = (
    372
    226)
  PixelsPerInch = 96
  TextHeight = 13
  object Label33: TLabel
    Left = 32
    Top = 130
    Width = 104
    Height = 13
    Caption = #1055#1088#1086#1076#1086#1083#1078#1080#1090#1077#1083#1100#1085#1086#1089#1090#1100
  end
  object Label34: TLabel
    Left = 31
    Top = 160
    Width = 43
    Height = 13
    Caption = #1047#1072#1087#1080#1089#1077#1081
  end
  object Button1: TButton
    Left = 72
    Top = 56
    Width = 217
    Height = 49
    Caption = #1054#1089#1090#1072#1085#1086#1074#1080#1090#1100'?'
    TabOrder = 0
    OnClick = Button1Click
  end
  object RecStaticText: TStaticText
    Left = 30
    Top = 16
    Width = 297
    Height = 25
    Alignment = taCenter
    Anchors = []
    AutoSize = False
    Caption = #1048#1044#1025#1058' '#1047#1040#1055#1048#1057#1068'!'
    Color = clRed
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clYellow
    Font.Height = -15
    Font.Name = 'Arial Narrow'
    Font.Style = [fsBold]
    ParentColor = False
    ParentFont = False
    TabOrder = 1
    Visible = False
  end
  object RecTimeEdit: TEdit
    Left = 167
    Top = 125
    Width = 81
    Height = 21
    ReadOnly = True
    TabOrder = 2
  end
  object RecCountEdit: TEdit
    Left = 167
    Top = 157
    Width = 81
    Height = 21
    TabOrder = 3
  end
  object RecTimer: TTimer
    OnTimer = RecTimerTimer
    Left = 128
    Top = 40
  end
end
