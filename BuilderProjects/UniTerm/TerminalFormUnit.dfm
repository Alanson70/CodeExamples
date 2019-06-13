object TerminalForm: TTerminalForm
  Left = 658
  Top = 192
  Width = 603
  Height = 421
  Caption = 'TerminalForm'
  Color = clBtnFace
  Font.Charset = RUSSIAN_CHARSET
  Font.Color = clWindowText
  Font.Height = -13
  Font.Name = 'Arial'
  Font.Style = []
  FormStyle = fsMDIChild
  OldCreateOrder = False
  Position = poDefaultPosOnly
  Visible = True
  OnActivate = FormShow
  OnClose = FormClose
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 16
  object Memo: TMemo
    Left = 0
    Top = 31
    Width = 595
    Height = 331
    Align = alClient
    BevelKind = bkFlat
    BorderStyle = bsNone
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Arial'
    Font.Style = []
    ParentFont = False
    ScrollBars = ssBoth
    TabOrder = 0
  end
  object CommandPanel: TPanel
    Left = 0
    Top = 0
    Width = 595
    Height = 31
    Align = alTop
    TabOrder = 1
    DesignSize = (
      595
      31)
    object SendButton: TButton
      Left = 528
      Top = 2
      Width = 62
      Height = 24
      Anchors = [akTop, akRight]
      Caption = #1055#1089#1083#1072#1090#1100'!'
      Default = True
      Enabled = False
      TabOrder = 0
      OnClick = SendButtonClick
    end
    object CommandCombo: TComboBox
      Left = 3
      Top = 2
      Width = 522
      Height = 24
      Anchors = [akLeft, akTop, akRight]
      ItemHeight = 16
      TabOrder = 1
    end
  end
  object StatusPanel: TPanel
    Left = 0
    Top = 362
    Width = 595
    Height = 32
    Align = alBottom
    BevelInner = bvLowered
    BevelOuter = bvNone
    TabOrder = 2
    DesignSize = (
      595
      32)
    object StatusLabel: TLabel
      Left = 392
      Top = 8
      Width = 113
      Height = 16
      Anchors = [akLeft, akTop, akRight]
      AutoSize = False
      Caption = #1085#1077' '#1086#1090#1082#1088#1099#1090
      Visible = False
    end
    object ControlButton: TButton
      Left = 2
      Top = 2
      Width = 95
      Height = 28
      Caption = #1059#1087#1088#1072#1074#1083#1077#1085#1080#1077
      TabOrder = 0
      OnClick = ControlButtonClick
    end
    object StatusLampPanel: TPanel
      Left = 103
      Top = 2
      Width = 28
      Height = 28
      BevelInner = bvRaised
      BevelWidth = 2
      BorderWidth = 1
      BorderStyle = bsSingle
      TabOrder = 1
    end
    object EchoCheckBox: TCheckBox
      Left = 144
      Top = 8
      Width = 57
      Height = 17
      Alignment = taLeftJustify
      Caption = #1069#1093#1086
      Checked = True
      State = cbChecked
      TabOrder = 2
    end
  end
  object StatusTimer: TTimer
    Enabled = False
    OnTimer = StatusTimerTimer
    Left = 56
    Top = 56
  end
end
