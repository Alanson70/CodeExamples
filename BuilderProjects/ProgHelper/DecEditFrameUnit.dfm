object DecEditFrame: TDecEditFrame
  Left = 0
  Top = 0
  Width = 120
  Height = 27
  AutoSize = True
  TabOrder = 0
  object DecEdit: TMemo
    Left = 0
    Top = 0
    Width = 120
    Height = 27
    Alignment = taRightJustify
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Comic Sans MS'
    Font.Style = [fsBold]
    Lines.Strings = (
      '0123456789')
    MaxLength = 12
    ParentFont = False
    ReadOnly = True
    TabOrder = 0
    WordWrap = False
    OnChange = DecEditChange
    OnClick = DecEditClick
    OnKeyDown = DecEditKeyDown
  end
end
