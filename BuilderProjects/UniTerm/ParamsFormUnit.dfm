object ParamsForm: TParamsForm
  Left = 1100
  Top = 188
  BorderIcons = [biSystemMenu]
  BorderStyle = bsSingle
  Caption = #1053#1072#1089#1090#1088#1086#1081#1082#1080' '#1089#1086#1077#1076#1080#1085#1077#1085#1080#1103
  ClientHeight = 303
  ClientWidth = 365
  Color = clBtnFace
  Font.Charset = RUSSIAN_CHARSET
  Font.Color = clWindowText
  Font.Height = -13
  Font.Name = 'Arial'
  Font.Style = []
  OldCreateOrder = False
  Position = poMainFormCenter
  PixelsPerInch = 96
  TextHeight = 16
  object CancelButton: TButton
    Left = 234
    Top = 259
    Width = 111
    Height = 27
    Caption = #1054#1090#1084#1077#1085#1072
    ModalResult = 2
    TabOrder = 0
  end
  object OkButton: TButton
    Left = 16
    Top = 256
    Width = 75
    Height = 25
    Caption = 'Ok'
    ModalResult = 1
    TabOrder = 1
  end
  object SendingGroupBox: TGroupBox
    Left = 2
    Top = 13
    Width = 351
    Height = 124
    Caption = ' Sending '
    TabOrder = 2
    object Label2: TLabel
      Left = 8
      Top = 27
      Width = 47
      Height = 16
      Caption = 'Addition'
    end
    object AdditionSendingOptionComboBox: TComboBox
      Left = 112
      Top = 24
      Width = 89
      Height = 24
      ItemHeight = 16
      ItemIndex = 0
      TabOrder = 0
      Text = 'CR+LF'
      OnChange = AdditionSendingOptionComboBoxChange
      Items.Strings = (
        'CR+LF'
        'CR'
        'LF'
        'other')
    end
    object StringEndSendingOptionEdit: TEdit
      Left = 8
      Top = 56
      Width = 193
      Height = 24
      MaxLength = 17
      TabOrder = 1
      Text = '00'
      Visible = False
      OnChange = StringEndOptionEditChange
    end
    object EchoCheckBox: TCheckBox
      Left = 8
      Top = 88
      Width = 121
      Height = 17
      Alignment = taLeftJustify
      Caption = 'Print Echo'
      TabOrder = 2
    end
  end
  object ReceivingGroupBox: TGroupBox
    Left = 3
    Top = 141
    Width = 351
    Height = 100
    Caption = 'Receiving'
    TabOrder = 3
    object Label9: TLabel
      Left = 8
      Top = 28
      Width = 84
      Height = 16
      Caption = 'String ends by'
    end
    object AdditionReceivingOptionComboBox: TComboBox
      Left = 112
      Top = 24
      Width = 89
      Height = 24
      ItemHeight = 16
      ItemIndex = 0
      TabOrder = 0
      Text = 'CR+LF'
      OnChange = AdditionReceivingOptionComboBoxChange
      Items.Strings = (
        'CR+LF'
        'CR'
        'LF'
        'other')
    end
    object StringEndReceivingOptionEdit: TEdit
      Left = 8
      Top = 56
      Width = 193
      Height = 24
      MaxLength = 17
      TabOrder = 1
      Text = '00'
      Visible = False
      OnChange = StringEndOptionEditChange
    end
  end
end
