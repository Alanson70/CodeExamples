object ValuesFrame1: TValuesFrame1
  Left = 0
  Top = 0
  Width = 534
  Height = 291
  Font.Charset = RUSSIAN_CHARSET
  Font.Color = clWindowText
  Font.Height = -13
  Font.Name = 'Comic Sans MS'
  Font.Style = [fsBold]
  ParentFont = False
  TabOrder = 0
  object Label6: TLabel
    Left = 48
    Top = 8
    Width = 25
    Height = 19
    Caption = 'DEC'
  end
  object Label7: TLabel
    Left = 160
    Top = 8
    Width = 27
    Height = 19
    Caption = 'HEX'
  end
  object Label1: TLabel
    Left = 296
    Top = 8
    Width = 26
    Height = 19
    Caption = 'BIN'
  end
  object HexEdit: TEdit
    Left = 116
    Top = 35
    Width = 73
    Height = 27
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clGreen
    Font.Height = -13
    Font.Name = 'Comic Sans MS'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 0
    Text = '0'
    OnChange = HexEditChange
  end
  object BinEdit: TEdit
    Left = 192
    Top = 35
    Width = 321
    Height = 25
    Font.Charset = ANSI_CHARSET
    Font.Color = clNavy
    Font.Height = -15
    Font.Name = 'Courier New'
    Font.Style = [fsBold]
    ParentFont = False
    ReadOnly = True
    TabOrder = 1
    Text = '12345678 12345678 12345678 12345678'
  end
  object FormatComboBox: TComboBox
    Left = 8
    Top = 248
    Width = 57
    Height = 27
    Style = csDropDownList
    ItemHeight = 19
    ItemIndex = 0
    TabOrder = 2
    Text = 'DEC'
    OnChange = FormatComboBoxChange
    Items.Strings = (
      'DEC'
      'HEX'
      'BIN')
  end
  object DigitsEdit: TEdit
    Left = 160
    Top = 248
    Width = 33
    Height = 27
    TabOrder = 3
    Text = '32'
    OnChange = DigitsEditChange
  end
  object DigitsUpDown: TUpDown
    Left = 193
    Top = 248
    Width = 32
    Height = 27
    Associate = DigitsEdit
    Min = 1
    Max = 32
    Position = 32
    TabOrder = 4
    Wrap = False
  end
  object ComboBox1: TComboBox
    Left = 272
    Top = 248
    Width = 89
    Height = 27
    Style = csDropDownList
    ItemHeight = 19
    ItemIndex = 1
    TabOrder = 5
    Text = 'Unsigned'
    Items.Strings = (
      'Signed'
      'Unsigned')
  end
  object Edit1: TEdit
    Left = 48
    Top = 152
    Width = 361
    Height = 27
    TabOrder = 6
    Text = 'Edit1'
    OnChange = Edit1Change
  end
  object DecEdit: TMemo
    Left = 0
    Top = 35
    Width = 113
    Height = 25
    Alignment = taRightJustify
    Lines.Strings = (
      '0')
    TabOrder = 7
    WantReturns = False
    OnChange = DecEditChange
  end
  inline ValueEditFrame1: TValueEditFrame
    Left = 104
    Top = 104
    Width = 128
    Height = 26
    TabOrder = 8
  end
end
