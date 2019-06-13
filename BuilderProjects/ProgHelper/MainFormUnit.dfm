object MainForm: TMainForm
  Left = 272
  Top = 216
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsSingle
  Caption = #1055#1086#1084#1086#1097#1085#1080#1082' '#1087#1088#1086#1075#1088#1072#1084#1084#1080#1089#1090#1072
  ClientHeight = 368
  ClientWidth = 530
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  Menu = MainMenu1
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object PageControl1: TPageControl
    Left = 0
    Top = 0
    Width = 530
    Height = 368
    ActivePage = ColorsTabSheet
    Align = alClient
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Comic Sans MS'
    Font.Style = [fsBold]
    ParentFont = False
    TabIndex = 0
    TabOrder = 0
    object ColorsTabSheet: TTabSheet
      Caption = #1062#1074#1077#1090#1072
      inline ColorsFrame1: TColorsFrame
        Left = 0
        Top = 0
        Width = 522
        Height = 334
        Align = alClient
        Font.Charset = RUSSIAN_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Comic Sans MS'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 0
      end
    end
    object ValuesTabSheet: TTabSheet
      Caption = #1050#1072#1083#1100#1082#1091#1083#1103#1090#1086#1088
      ImageIndex = 2
      inline ValuesFrame1: TValuesFrame
        Left = 0
        Top = 0
        Width = 522
        Height = 334
        Align = alClient
        Font.Charset = RUSSIAN_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Comic Sans MS'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 0
        inherited BinFrame1: TBinEditFrame
          inherited BinEdit: TMemo
            PopupMenu = ValuesFrame1.PopupMenu1
          end
        end
        inherited HexFrame1: THexEditFrame
          inherited HexEdit: TMemo
            PopupMenu = ValuesFrame1.PopupMenu1
          end
        end
        inherited DecFrame1: TDecEditFrame
          inherited DecEdit: TMemo
            PopupMenu = ValuesFrame1.PopupMenu1
          end
        end
        inherited BinFrame2: TBinEditFrame
          inherited BinEdit: TMemo
            PopupMenu = ValuesFrame1.PopupMenu1
          end
        end
        inherited HexFrame2: THexEditFrame
          inherited HexEdit: TMemo
            PopupMenu = ValuesFrame1.PopupMenu1
          end
        end
        inherited DecFrame2: TDecEditFrame
          inherited DecEdit: TMemo
            PopupMenu = ValuesFrame1.PopupMenu1
          end
        end
        inherited BinFrame3: TBinEditFrame
          inherited BinEdit: TMemo
            PopupMenu = ValuesFrame1.PopupMenu1
          end
        end
        inherited HexFrame3: THexEditFrame
          inherited HexEdit: TMemo
            PopupMenu = ValuesFrame1.PopupMenu1
          end
        end
        inherited DecFrame3: TDecEditFrame
          inherited DecEdit: TMemo
            PopupMenu = ValuesFrame1.PopupMenu1
          end
        end
      end
    end
    object SymbolsTabSheet: TTabSheet
      Caption = #1057#1080#1084#1074#1086#1083#1099
      ImageIndex = 3
      inline SymbolsFrame1: TSymbolsFrame
        Left = 0
        Top = 0
        Width = 522
        Height = 334
        Align = alClient
        Font.Charset = RUSSIAN_CHARSET
        Font.Color = clWindowText
        Font.Height = -16
        Font.Name = 'Comic Sans MS'
        Font.Style = []
        ParentFont = False
        TabOrder = 0
        inherited HexEditFrame1: THexEditFrame
          Width = 55
          Height = 49
          inherited HexEdit: TMemo
            Left = 0
          end
        end
        inherited DecEditFrame1: TDecEditFrame
          Width = 65
          Height = 49
        end
        inherited SymbolsPopupMenu: TPopupMenu
          inherited CopyMenuItem: TMenuItem
            OnClick = nil
          end
          inherited PasteMenuItem: TMenuItem
            OnClick = nil
          end
        end
      end
    end
    object DatesTabSheet: TTabSheet
      Caption = #1044#1072#1090#1072' '#1080' '#1074#1088#1077#1084#1103
      ImageIndex = 1
      inline DatesFrame1: TDatesFrame
        Left = 0
        Top = 0
        Width = 522
        Height = 334
        Align = alClient
        Font.Charset = RUSSIAN_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Comic Sans MS'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 0
        inherited DosHexEditFrame: THexEditFrame
          inherited HexEdit: TMemo
            PopupMenu = DatesFrame1.DatesPopupMenu
          end
        end
        inherited LinuxHexEditFrame: THexEditFrame
          inherited HexEdit: TMemo
            PopupMenu = DatesFrame1.DatesPopupMenu
          end
        end
      end
    end
    object DateCalcTabSheet: TTabSheet
      Caption = #1050#1072#1083#1100#1082#1091#1083#1103#1090#1086#1088' '#1076#1072#1090
      ImageIndex = 4
      TabVisible = False
      inline DateCalcFrame1: TDateCalcFrame
        Left = 0
        Top = 0
        Width = 457
        Height = 334
        Align = alCustom
        TabOrder = 0
        Visible = False
      end
    end
  end
  object MainMenu1: TMainMenu
    Left = 192
    Top = 328
    object AboutMenuItem: TMenuItem
      Caption = 'About'
      OnClick = AboutMenuItemClick
    end
  end
end
