object MainForm: TMainForm
  Left = 405
  Top = 370
  Width = 713
  Height = 508
  Caption = 'Unificated Terminal'
  Color = clBtnFace
  Font.Charset = RUSSIAN_CHARSET
  Font.Color = clWindowText
  Font.Height = -13
  Font.Name = 'Comic Sans MS'
  Font.Style = [fsBold]
  FormStyle = fsMDIForm
  Menu = MainMenu
  OldCreateOrder = False
  OnClose = FormClose
  PixelsPerInch = 96
  TextHeight = 19
  object MainMenu: TMainMenu
    Left = 88
    Top = 80
    object ProfileMenuItem: TMenuItem
      Caption = #1055#1088#1086#1092#1080#1083#1100
      object FileNewMenuItem: TMenuItem
        Caption = #1053#1086#1074#1099#1081
        OnClick = FileNewMenuItemClick
      end
      object FileOpenMenuItem: TMenuItem
        Caption = #1054#1090#1082#1088#1099#1090#1100
        OnClick = FileOpenMenuItemClick
      end
      object FileCloseMenuItem: TMenuItem
        Caption = #1047#1072#1082#1088#1099#1090#1100
        Enabled = False
        OnClick = FileCloseMenuItemClick
      end
      object FileSaveAsMenuItem: TMenuItem
        Caption = #1057#1086#1093#1088#1072#1085#1080#1090#1100' '#1082#1072#1082
        Enabled = False
        OnClick = FileSaveAsMenuItemClick
      end
      object N1: TMenuItem
        Caption = '-'
      end
      object ExitMenuItem: TMenuItem
        Caption = #1042#1099#1081#1090#1080
      end
    end
    object TermMenuItem: TMenuItem
      Caption = #1058#1077#1088#1084#1080#1085#1072#1083
      object TerminalOpenMenuItem: TMenuItem
        Caption = #1057#1086#1079#1076#1072#1090#1100
        OnClick = TerminalOpenMenuItemClick
      end
      object TerminalCloseMenuItem: TMenuItem
        Caption = #1047#1072#1082#1088#1099#1090#1100
        Enabled = False
        OnClick = TerminalCloseMenuItemClick
      end
      object N2: TMenuItem
        Caption = '-'
      end
      object TerminalControlMenuItem: TMenuItem
        Caption = #1059#1087#1088#1072#1074#1083#1077#1085#1080#1077
        Enabled = False
        OnClick = TerminalControlMenuItemClick
      end
    end
    object AboutMenuItem: TMenuItem
      Caption = #1054' '#1087#1088#1086#1075#1088#1072#1084#1084#1077
      OnClick = AboutMenuItemClick
    end
  end
  object OpenDialog1: TOpenDialog
    DefaultExt = '*.cfg'
    Filter = #1060#1072#1081#1083' '#1095#1072#1089#1090#1086#1090#1085#1086#1075#1086' '#1087#1083#1072#1085#1072'|*.cfg'
    Title = #1054#1090#1082#1088#1099#1090#1100' '#1095#1072#1089#1090#1086#1090#1085#1099#1081' '#1087#1083#1072#1085
    Left = 376
    Top = 136
  end
  object SaveDialog1: TSaveDialog
    DefaultExt = '*.cfg'
    Filter = '|*.cfg'
    Title = #1057#1086#1093#1088#1072#1085#1080#1090#1100' '#1095#1072#1089#1090#1086#1090#1085#1099#1081' '#1087#1083#1072#1085
    Left = 288
    Top = 152
  end
end
