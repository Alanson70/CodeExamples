object MainForm: TMainForm
  Left = 309
  Top = 329
  Width = 735
  Height = 486
  Caption = 'MainForm'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  Menu = MainMenu1
  OldCreateOrder = False
  OnClose = FormClose
  OnCreate = FormCreate
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object MainMenu1: TMainMenu
    Left = 96
    Top = 56
    object N1: TMenuItem
      Caption = #1055#1088#1086#1092#1080#1083#1100
      object ProfileNewMenuItem: TMenuItem
        Caption = #1053#1086#1074#1099#1081
        OnClick = ProfileNewMenuItemClick
      end
      object ProfileOpenMenuItem: TMenuItem
        Caption = #1054#1090#1082#1088#1099#1090#1100
        OnClick = ProfileOpenMenuItemClick
      end
      object ProfileSaveMenuItem: TMenuItem
        Caption = #1057#1086#1093#1088#1072#1085#1080#1090#1100
        Enabled = False
        OnClick = ProfileSaveMenuItemClick
      end
      object ProfileSaveAsMenuItem: TMenuItem
        Caption = #1057#1086#1093#1088#1072#1085#1080#1090#1100' '#1082#1072#1082
        Enabled = False
        OnClick = ProfileSaveAsMenuItemClick
      end
      object ProfileCloseMenuItem: TMenuItem
        Caption = #1047#1072#1082#1088#1099#1090#1100
        Enabled = False
        OnClick = ProfileCloseMenuItemClick
      end
      object N7: TMenuItem
        Caption = '-'
      end
      object ProfileAutoSaveMenuItem: TMenuItem
        AutoCheck = True
        Caption = #1057#1086#1093#1088#1072#1085#1103#1090#1100' '#1087#1088#1080' '#1074#1099#1093#1086#1076#1077
        Checked = True
      end
      object ProfileAutoLoadMenuItem: TMenuItem
        AutoCheck = True
        Caption = #1047#1072#1075#1088#1091#1078#1072#1090#1100' '#1085#1072' '#1089#1090#1072#1088#1090#1077
        Checked = True
      end
      object N9: TMenuItem
        Caption = '-'
      end
      object ExitMenuItem: TMenuItem
        Caption = #1042#1099#1093#1086#1076
        OnClick = ExitMenuItemClick
      end
    end
    object N2: TMenuItem
      Caption = #1056#1077#1078#1080#1084
      object RecMenuItem: TMenuItem
        Caption = #1046#1080#1074#1100#1105#1084
        Checked = True
        GroupIndex = 5
        RadioItem = True
        OnClick = RecMenuItemClick
      end
      object ViewerMenuItem: TMenuItem
        AutoCheck = True
        Caption = #1048#1079' '#1092#1072#1081#1083#1072
        GroupIndex = 5
        RadioItem = True
        OnClick = ViewerMenuItemClick
      end
    end
  end
end
