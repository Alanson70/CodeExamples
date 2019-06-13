object DateCalcFrame: TDateCalcFrame
  Left = 0
  Top = 0
  Width = 437
  Height = 297
  TabOrder = 0
  object DateTimeStringEdit1: TEdit
    Left = 64
    Top = 24
    Width = 193
    Height = 31
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Comic Sans MS'
    Font.Style = [fsBold]
    ParentFont = False
    PopupMenu = PopupMenu1
    ReadOnly = True
    TabOrder = 0
    Text = '0'
    OnChange = DateTimeStringEditChange
  end
  object DateTimeStringEdit2: TEdit
    Tag = 1
    Left = 64
    Top = 96
    Width = 193
    Height = 31
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Comic Sans MS'
    Font.Style = [fsBold]
    ParentFont = False
    PopupMenu = PopupMenu1
    ReadOnly = True
    TabOrder = 1
    Text = '0'
    OnChange = DateTimeStringEditChange
  end
  object DateTimeStringEdit3: TEdit
    Tag = 2
    Left = 64
    Top = 184
    Width = 193
    Height = 31
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Comic Sans MS'
    Font.Style = [fsBold]
    ParentFont = False
    PopupMenu = PopupMenu1
    ReadOnly = True
    TabOrder = 2
    Text = '0'
  end
  object SumButton: TButton
    Left = 88
    Top = 144
    Width = 25
    Height = 25
    Hint = 'Sum'
    Caption = '+'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    ParentShowHint = False
    ShowHint = True
    TabOrder = 3
    OnClick = SumButtonClick
  end
  object DiffButton: TButton
    Tag = 1
    Left = 196
    Top = 144
    Width = 25
    Height = 25
    Hint = 'Difference'
    Caption = '-'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    ParentShowHint = False
    ShowHint = True
    TabOrder = 4
    OnClick = SumButtonClick
  end
  object PopupMenu1: TPopupMenu
    Left = 312
    Top = 104
    object CutMenuItem: TMenuItem
      Caption = 'Zeroize'
    end
    object CopyMenuItem: TMenuItem
      Tag = 1
      Caption = 'Copy'
      OnClick = PopupMenuItemClick
    end
    object PasteMenuItem: TMenuItem
      Tag = 2
      Caption = 'Paste'
      OnClick = PopupMenuItemClick
    end
  end
end
