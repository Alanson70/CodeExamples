object HexEditFrame: THexEditFrame
  Left = 0
  Top = 0
  Width = 90
  Height = 27
  AutoSize = True
  TabOrder = 0
  object HexEdit: TMemo
    Left = 0
    Top = 0
    Width = 90
    Height = 27
    Alignment = taRightJustify
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clGreen
    Font.Height = -13
    Font.Name = 'Comic Sans MS'
    Font.Style = [fsBold]
    Lines.Strings = (
      'AAAAAAAA')
    MaxLength = 8
    ParentFont = False
    ReadOnly = True
    TabOrder = 0
    WordWrap = False
    OnChange = HexEditChange
    OnKeyDown = HexEditKeyDown
  end
end
