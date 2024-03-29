object MainForm: TMainForm
  Left = 459
  Top = 140
  BorderIcons = [biSystemMenu]
  BorderStyle = bsSingle
  Caption = #1055#1099#1090#1072#1090#1077#1083#1100' '#1090#1072#1073#1083#1080#1094#1099' '#1091#1084#1085#1086#1078#1077#1085#1080#1103
  ClientHeight = 413
  ClientWidth = 460
  Color = clBtnFace
  Font.Charset = RUSSIAN_CHARSET
  Font.Color = clWindowText
  Font.Height = -16
  Font.Name = 'Arial'
  Font.Style = [fsBold]
  OldCreateOrder = False
  Position = poDesktopCenter
  OnClose = FormClose
  OnKeyPress = ResultEditKeyPress
  PixelsPerInch = 96
  TextHeight = 19
  object Label3: TLabel
    Left = 224
    Top = 64
    Width = 28
    Height = 49
    AutoSize = False
    Caption = 'x'
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clNavy
    Font.Height = -37
    Font.Name = 'Arial'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label4: TLabel
    Left = 320
    Top = 64
    Width = 33
    Height = 49
    AutoSize = False
    Caption = '='
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clNavy
    Font.Height = -37
    Font.Name = 'Arial'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object ResultEdit: TEdit
    Left = 352
    Top = 64
    Width = 73
    Height = 52
    Color = clBtnFace
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clNavy
    Font.Height = -37
    Font.Name = 'Arial'
    Font.Style = [fsBold]
    ParentFont = False
    ReadOnly = True
    TabOrder = 0
    Text = '100'
    OnKeyPress = ResultEditKeyPress
  end
  object Value1Edit: TEdit
    Left = 160
    Top = 64
    Width = 57
    Height = 52
    Color = clBtnFace
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clNavy
    Font.Height = -37
    Font.Name = 'Arial'
    Font.Style = [fsBold]
    ParentFont = False
    ReadOnly = True
    TabOrder = 1
    Text = '10'
    OnKeyPress = ResultEditKeyPress
  end
  object Value2Edit: TEdit
    Left = 256
    Top = 64
    Width = 57
    Height = 52
    Color = clBtnFace
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clNavy
    Font.Height = -37
    Font.Name = 'Arial'
    Font.Style = [fsBold]
    ParentFont = False
    ReadOnly = True
    TabOrder = 2
    Text = '10'
    OnKeyPress = ResultEditKeyPress
  end
  object StartButton: TButton
    Left = 144
    Top = 8
    Width = 313
    Height = 49
    Caption = #1053#1040#1063#1040#1058#1068'!'
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -27
    Font.Name = 'Arial'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 3
    OnClick = StartButtonClick
    OnKeyPress = ResultEditKeyPress
  end
  object SourceGroupBox: TGroupBox
    Left = 0
    Top = 0
    Width = 137
    Height = 221
    Caption = ' '#1048#1089#1093#1086#1076#1085#1099#1077' '#1076#1072#1085#1085#1099#1077' '
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Arial'
    Font.Style = []
    ParentFont = False
    TabOrder = 4
    object Label1: TLabel
      Left = 8
      Top = 30
      Width = 15
      Height = 16
      Caption = #1054#1090
    end
    object Label2: TLabel
      Left = 8
      Top = 59
      Width = 16
      Height = 16
      Caption = #1044#1086
    end
    object UserLabel: TLabel
      Left = 11
      Top = 108
      Width = 99
      Height = 16
      Caption = #1055#1077#1088#1077#1084#1085#1086#1078#1072#1090#1077#1083#1100':'
    end
    object FromEdit: TEdit
      Left = 72
      Top = 24
      Width = 25
      Height = 24
      ReadOnly = True
      TabOrder = 0
      Text = '1'
      OnChange = FromEditChange
    end
    object FromUpDown: TUpDown
      Left = 97
      Top = 24
      Width = 24
      Height = 24
      Associate = FromEdit
      Min = 1
      Max = 10
      Position = 1
      TabOrder = 1
      Wrap = False
    end
    object ToEdit: TEdit
      Left = 72
      Top = 55
      Width = 25
      Height = 24
      ReadOnly = True
      TabOrder = 2
      Text = '1'
      OnChange = ToEditChange
    end
    object ToUpDown: TUpDown
      Left = 97
      Top = 55
      Width = 24
      Height = 24
      Associate = ToEdit
      Min = 1
      Max = 10
      Position = 1
      TabOrder = 3
      Wrap = False
    end
    object RandomCheckBox: TCheckBox
      Left = 8
      Top = 85
      Width = 113
      Height = 17
      Alignment = taLeftJustify
      Caption = #1057#1083#1091#1095#1072#1081#1085#1086
      TabOrder = 4
      OnClick = RandomCheckBoxClick
    end
    object ComboBox1: TComboBox
      Left = 8
      Top = 127
      Width = 113
      Height = 24
      Style = csDropDownList
      ItemHeight = 16
      TabOrder = 5
      OnChange = ComboBox1Change
    end
    object AddUserButton: TButton
      Left = 48
      Top = 157
      Width = 75
      Height = 25
      Caption = #1044#1086#1073#1072#1074#1080#1090#1100
      TabOrder = 6
      OnClick = AddUserButtonClick
    end
    object DelButton: TButton
      Left = 48
      Top = 188
      Width = 75
      Height = 25
      Caption = #1059#1076#1072#1083#1080#1090#1100
      Enabled = False
      TabOrder = 7
      OnClick = DelButtonClick
    end
  end
  object ResumeEdit: TEdit
    Left = 144
    Top = 128
    Width = 313
    Height = 52
    AutoSize = False
    Color = clBtnFace
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clRed
    Font.Height = -37
    Font.Name = 'Arial'
    Font.Style = [fsBold]
    ParentFont = False
    ReadOnly = True
    TabOrder = 5
    OnKeyPress = ResultEditKeyPress
  end
  object PointsEdit: TEdit
    Left = 208
    Top = 224
    Width = 177
    Height = 52
    Color = clBtnFace
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clNavy
    Font.Height = -37
    Font.Name = 'Arial'
    Font.Style = [fsBold]
    ParentFont = False
    ReadOnly = True
    TabOrder = 6
    Text = '0 '#1080#1079' 100'
    OnKeyPress = ResultEditKeyPress
  end
  object TimeEdit: TEdit
    Left = 208
    Top = 312
    Width = 177
    Height = 64
    Color = clBtnFace
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -48
    Font.Name = 'Arial'
    Font.Style = [fsBold]
    ParentFont = False
    ReadOnly = True
    TabOrder = 7
    Text = '0:00:00'
    OnKeyPress = ResultEditKeyPress
  end
  object GroupBox1: TGroupBox
    Left = 0
    Top = 224
    Width = 137
    Height = 185
    Caption = ' '#1056#1077#1079#1091#1083#1100#1090#1072#1090#1099' '
    Enabled = False
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Arial'
    Font.Style = []
    ParentFont = False
    TabOrder = 8
    inline UserResultFrame1: TUserResultFrame
      Left = 2
      Top = 18
      Width = 133
      Height = 24
      Align = alTop
      TabOrder = 0
    end
  end
  object Timer1: TTimer
    Enabled = False
    OnTimer = Timer1Timer
    Left = 369
    Top = 40
  end
end
