object ValueEditFrame: TValueEditFrame
  Left = 0
  Top = 0
  Width = 128
  Height = 26
  TabOrder = 0
  object Edit: TMemo
    Left = 0
    Top = 0
    Width = 128
    Height = 26
    Align = alClient
    Alignment = taRightJustify
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Comic Sans MS'
    Font.Style = [fsBold]
    Lines.Strings = (
      '0')
    ParentFont = False
    ReadOnly = True
    TabOrder = 0
    WantReturns = False
    OnKeyDown = EditKeyDown
  end
end
