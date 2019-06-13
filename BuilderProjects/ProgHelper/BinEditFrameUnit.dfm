object BinEditFrame: TBinEditFrame
  Left = 0
  Top = 0
  Width = 330
  Height = 42
  TabOrder = 0
  object BinEdit: TMemo
    Left = 0
    Top = 0
    Width = 289
    Height = 27
    Alignment = taRightJustify
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clNavy
    Font.Height = -13
    Font.Name = 'Comic Sans MS'
    Font.Style = [fsBold]
    Lines.Strings = (
      '02345678 02345678 02345678 02345678')
    MaxLength = 35
    ParentFont = False
    ReadOnly = True
    TabOrder = 0
    WordWrap = False
    OnChange = BinEditChange
    OnKeyDown = BinEditKeyDown
  end
end
