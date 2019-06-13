object SymbolsFrame: TSymbolsFrame
  Left = 0
  Top = 0
  Width = 537
  Height = 264
  Font.Charset = RUSSIAN_CHARSET
  Font.Color = clWindowText
  Font.Height = -16
  Font.Name = 'Comic Sans MS'
  Font.Style = []
  ParentFont = False
  TabOrder = 0
  object Label1: TLabel
    Left = 40
    Top = 16
    Width = 47
    Height = 23
    Caption = 'Letter'
  end
  object Label2: TLabel
    Left = 160
    Top = 16
    Width = 29
    Height = 23
    Caption = 'Hex'
  end
  object Label3: TLabel
    Left = 272
    Top = 16
    Width = 28
    Height = 23
    Caption = 'Dec'
  end
  object Edit2: TEdit
    Left = 8
    Top = 128
    Width = 361
    Height = 33
    AutoSize = False
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clMaroon
    Font.Height = -21
    Font.Name = 'Comic Sans MS'
    Font.Style = []
    MaxLength = 25
    ParentFont = False
    PopupMenu = SymbolsPopupMenu
    TabOrder = 0
    Text = 'Edit2'
    OnChange = Edit2Change
  end
  inline HexEditFrame1: THexEditFrame
    Left = 144
    Top = 48
    Width = 59
    Height = 57
    AutoSize = True
    TabOrder = 1
    inherited HexEdit: TMemo
      Left = 2
      Width = 55
      Height = 49
      Font.Height = -27
      Lines.Strings = (
        'AA'
        'AA')
    end
  end
  inline DecEditFrame1: TDecEditFrame
    Left = 248
    Top = 48
    Width = 71
    Height = 57
    AutoSize = True
    TabOrder = 2
    inherited DecEdit: TMemo
      Width = 65
      Height = 49
      Font.Height = -27
      Lines.Strings = (
        '012'
        '345'
        '67')
    end
  end
  object Panel1: TPanel
    Left = 40
    Top = 48
    Width = 55
    Height = 49
    BevelInner = bvRaised
    BevelOuter = bvLowered
    BorderStyle = bsSingle
    Color = clBtnHighlight
    TabOrder = 3
    object LetterEdit: TEdit
      Left = 10
      Top = 1
      Width = 37
      Height = 40
      AutoSize = False
      BorderStyle = bsNone
      Font.Charset = RUSSIAN_CHARSET
      Font.Color = clRed
      Font.Height = -37
      Font.Name = 'Times New Roman'
      Font.Style = [fsBold]
      MaxLength = 1
      ParentFont = False
      TabOrder = 0
      Text = 'A'
      OnChange = LetterEditChange
    end
  end
  object Edit1: TEdit
    Left = 8
    Top = 208
    Width = 505
    Height = 24
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Arial Narrow'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 4
    Text = 'Edit1'
  end
  object SymbolsPopupMenu: TPopupMenu
    Left = 440
    Top = 118
    object CopyMenuItem: TMenuItem
      Caption = 'Copy'
      OnClick = CopyMenuItemClick
    end
    object PasteMenuItem: TMenuItem
      Tag = 1
      Caption = 'Paste'
      OnClick = PasteMenuItemClick
    end
  end
end
