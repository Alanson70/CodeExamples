object ChooseDateForm: TChooseDateForm
  Left = 473
  Top = 170
  BorderIcons = [biSystemMenu]
  BorderStyle = bsSingle
  Caption = #1042#1099#1073#1086#1088' '#1076#1072#1090#1099
  ClientHeight = 294
  ClientWidth = 318
  Color = clBtnFace
  Font.Charset = RUSSIAN_CHARSET
  Font.Color = clWindowText
  Font.Height = -13
  Font.Name = 'Comic Sans MS'
  Font.Style = [fsBold]
  OldCreateOrder = False
  Position = poMainFormCenter
  PixelsPerInch = 96
  TextHeight = 19
  object Calendar: TCCalendar
    Left = 0
    Top = 0
    Width = 318
    Height = 129
    Align = alTop
    TabOrder = 0
    OnChange = CalendarChange
  end
  object OkButton: TButton
    Left = 120
    Top = 248
    Width = 81
    Height = 33
    Caption = #1042#1099#1073#1088#1072#1090#1100
    ModalResult = 1
    TabOrder = 1
  end
  object CancelButton: TButton
    Left = 232
    Top = 248
    Width = 81
    Height = 33
    Caption = #1054#1090#1084#1077#1085#1072
    ModalResult = 2
    TabOrder = 2
  end
  object LeftButton: TButton
    Left = 24
    Top = 136
    Width = 65
    Height = 28
    Caption = #1053#1072#1079#1072#1076
    TabOrder = 3
    OnClick = LeftButtonClick
  end
  object RightButton: TButton
    Left = 232
    Top = 136
    Width = 65
    Height = 28
    Caption = #1042#1087#1077#1088#1077#1076
    TabOrder = 4
    OnClick = RightButtonClick
  end
  object MonthComboBox: TComboBox
    Left = 96
    Top = 136
    Width = 129
    Height = 27
    Style = csDropDownList
    ItemHeight = 19
    ItemIndex = 0
    TabOrder = 5
    Text = #1071#1085#1074#1072#1088#1100
    OnChange = MonthComboBoxChange
    Items.Strings = (
      #1071#1085#1074#1072#1088#1100
      #1060#1077#1074#1088#1072#1083#1100
      #1052#1072#1088#1090
      #1040#1087#1088#1077#1083#1100
      #1052#1072#1081
      #1048#1102#1085#1100
      #1048#1102#1083#1100
      #1040#1074#1075#1091#1089#1090
      #1057#1077#1085#1090#1103#1073#1088#1100
      #1054#1082#1090#1103#1073#1088#1100
      #1053#1086#1103#1073#1088#1100
      #1044#1077#1082#1072#1073#1088#1100)
  end
  object YearEdit: TEdit
    Left = 96
    Top = 168
    Width = 129
    Height = 73
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -48
    Font.Name = 'Comic Sans MS'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 6
    Text = '2007'
    OnChange = YearEditChange
  end
end
