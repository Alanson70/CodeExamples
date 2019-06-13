object ColorsFrame: TColorsFrame
  Left = 0
  Top = 0
  Width = 498
  Height = 317
  Font.Charset = RUSSIAN_CHARSET
  Font.Color = clWindowText
  Font.Height = -13
  Font.Name = 'Comic Sans MS'
  Font.Style = [fsBold]
  ParentFont = False
  TabOrder = 0
  object Label5: TLabel
    Left = 10
    Top = 46
    Width = 56
    Height = 19
    Caption = 'Summary'
  end
  object Label6: TLabel
    Left = 88
    Top = 8
    Width = 25
    Height = 19
    Caption = 'DEC'
  end
  object Label7: TLabel
    Left = 168
    Top = 10
    Width = 27
    Height = 19
    Caption = 'HEX'
  end
  object SummaryShape: TShape
    Left = 264
    Top = 43
    Width = 40
    Height = 27
  end
  object RedShape: TShape
    Left = 264
    Top = 91
    Width = 40
    Height = 27
  end
  object GreenShape: TShape
    Left = 264
    Top = 147
    Width = 40
    Height = 27
  end
  object BlueShape: TShape
    Left = 264
    Top = 203
    Width = 40
    Height = 27
  end
  object Label3: TLabel
    Left = 8
    Top = 208
    Width = 26
    Height = 19
    Caption = 'Blue'
  end
  object Label2: TLabel
    Left = 8
    Top = 152
    Width = 36
    Height = 19
    Caption = 'Green'
  end
  object Label1: TLabel
    Left = 8
    Top = 96
    Width = 23
    Height = 19
    Caption = 'Red'
  end
  object Label4: TLabel
    Left = 8
    Top = 264
    Width = 44
    Height = 19
    Caption = 'Palette'
  end
  object IntShape: TShape
    Left = 264
    Top = 259
    Width = 40
    Height = 27
  end
  object SummaryEdit: TEdit
    Left = 72
    Top = 43
    Width = 97
    Height = 27
    MaxLength = 8
    PopupMenu = ColorsPopupMenu
    TabOrder = 0
    Text = '0'
    OnChange = SummaryEditChange
  end
  object SummaryHexEdit: TEdit
    Left = 176
    Top = 43
    Width = 81
    Height = 27
    MaxLength = 6
    PopupMenu = ColorsPopupMenu
    TabOrder = 1
    Text = '0'
    OnChange = SummaryHexEditChange
  end
  object RedScrollBar: TScrollBar
    Left = 312
    Top = 91
    Width = 177
    Height = 27
    Max = 255
    PageSize = 0
    TabOrder = 5
    OnChange = ScrollBarChange
  end
  object GreenScrollBar: TScrollBar
    Left = 312
    Top = 147
    Width = 177
    Height = 27
    Max = 255
    PageSize = 0
    TabOrder = 8
    OnChange = ScrollBarChange
  end
  object BlueScrollBar: TScrollBar
    Left = 312
    Top = 203
    Width = 177
    Height = 27
    Max = 255
    PageSize = 0
    TabOrder = 11
    OnChange = ScrollBarChange
  end
  object BlueHexEdit: TEdit
    Left = 176
    Top = 203
    Width = 81
    Height = 27
    MaxLength = 2
    PopupMenu = ColorsPopupMenu
    TabOrder = 10
    Text = '0'
    OnChange = HexEditChange
  end
  object GreenHexEdit: TEdit
    Left = 176
    Top = 147
    Width = 81
    Height = 27
    MaxLength = 2
    PopupMenu = ColorsPopupMenu
    TabOrder = 7
    Text = '0'
    OnChange = HexEditChange
  end
  object RedHexEdit: TEdit
    Left = 176
    Top = 91
    Width = 81
    Height = 27
    MaxLength = 2
    PopupMenu = ColorsPopupMenu
    TabOrder = 4
    Text = '0'
    OnChange = HexEditChange
  end
  object RedEdit: TEdit
    Left = 72
    Top = 91
    Width = 97
    Height = 27
    MaxLength = 3
    PopupMenu = ColorsPopupMenu
    TabOrder = 3
    Text = '0'
    OnChange = EditChange
  end
  object GreenEdit: TEdit
    Left = 72
    Top = 147
    Width = 97
    Height = 27
    MaxLength = 3
    PopupMenu = ColorsPopupMenu
    TabOrder = 6
    Text = '0'
    OnChange = EditChange
  end
  object BlueEdit: TEdit
    Left = 72
    Top = 203
    Width = 97
    Height = 27
    MaxLength = 3
    PopupMenu = ColorsPopupMenu
    TabOrder = 9
    Text = '0'
    OnChange = EditChange
  end
  object StandartColorBox: TColorBox
    Left = 312
    Top = 43
    Width = 177
    Height = 27
    Style = [cbStandardColors, cbExtendedColors, cbSystemColors, cbCustomColor]
    ItemHeight = 21
    TabOrder = 2
    OnChange = StandartColorBoxChange
  end
  object IntEdit: TEdit
    Left = 72
    Top = 259
    Width = 97
    Height = 27
    MaxLength = 3
    PopupMenu = ColorsPopupMenu
    TabOrder = 12
    Text = '0'
    OnChange = EditChange
  end
  object IntHexEdit: TEdit
    Left = 176
    Top = 259
    Width = 81
    Height = 27
    MaxLength = 2
    PopupMenu = ColorsPopupMenu
    TabOrder = 13
    Text = '0'
    OnChange = HexEditChange
  end
  object IntScrollBar: TScrollBar
    Left = 312
    Top = 259
    Width = 177
    Height = 27
    Max = 255
    PageSize = 0
    TabOrder = 14
    OnChange = ScrollBarChange
  end
  object ColorsPopupMenu: TPopupMenu
    OnPopup = ColorsPopupMenuPopup
    Left = 32
    Top = 118
    object CopyMenuItem: TMenuItem
      Caption = 'Copy'
      OnClick = ColorsMenuItemClick
    end
    object PasteMenuItem: TMenuItem
      Tag = 1
      Caption = 'Paste'
      OnClick = ColorsMenuItemClick
    end
  end
end
