object ValuesFrame: TValuesFrame
  Left = 0
  Top = 0
  Width = 542
  Height = 347
  Font.Charset = RUSSIAN_CHARSET
  Font.Color = clWindowText
  Font.Height = -13
  Font.Name = 'Comic Sans MS'
  Font.Style = [fsBold]
  ParentFont = False
  TabOrder = 0
  object Label6: TLabel
    Left = 384
    Top = 8
    Width = 25
    Height = 19
    Caption = 'DEC'
  end
  object Label7: TLabel
    Left = 293
    Top = 8
    Width = 27
    Height = 19
    Caption = 'HEX'
  end
  object Label1: TLabel
    Left = 2
    Top = 8
    Width = 26
    Height = 19
    Caption = 'BIN'
  end
  object Label2: TLabel
    Left = 7
    Top = 300
    Width = 36
    Height = 19
    Caption = 'Digits'
  end
  object Label3: TLabel
    Left = 384
    Top = 300
    Width = 30
    Height = 19
    Caption = 'Type'
  end
  object DigitsEdit: TEdit
    Left = 48
    Top = 296
    Width = 33
    Height = 27
    TabOrder = 0
    Text = '32'
    OnChange = DigitsEditChange
  end
  object DigitsUpDown: TUpDown
    Left = 81
    Top = 296
    Width = 32
    Height = 27
    Associate = DigitsEdit
    Min = 1
    Max = 32
    Position = 32
    TabOrder = 1
    Wrap = False
  end
  object SignComboBox: TComboBox
    Left = 416
    Top = 296
    Width = 81
    Height = 27
    Style = csDropDownList
    ItemHeight = 19
    ItemIndex = 0
    TabOrder = 2
    Text = 'Unsigned'
    OnChange = SignComboBoxChange
    Items.Strings = (
      'Unsigned'
      'Signed')
  end
  inline BinFrame1: TBinEditFrame
    Left = 0
    Top = 30
    Width = 289
    Height = 27
    AutoSize = True
    TabOrder = 3
    inherited BinEdit: TMemo
      PopupMenu = PopupMenu1
    end
  end
  inline HexFrame1: THexEditFrame
    Left = 293
    Top = 30
    Width = 105
    Height = 27
    AutoSize = True
    TabOrder = 4
    inherited HexEdit: TMemo
      PopupMenu = PopupMenu1
    end
  end
  inline DecFrame1: TDecEditFrame
    Left = 384
    Top = 30
    Width = 120
    Height = 27
    AutoSize = True
    TabOrder = 5
    inherited DecEdit: TMemo
      PopupMenu = PopupMenu1
    end
  end
  inline BinFrame2: TBinEditFrame
    Left = 1
    Top = 97
    Width = 289
    Height = 27
    AutoSize = True
    TabOrder = 6
    inherited BinEdit: TMemo
      Tag = 1
      PopupMenu = PopupMenu1
    end
  end
  inline HexFrame2: THexEditFrame
    Left = 294
    Top = 97
    Width = 105
    Height = 27
    AutoSize = True
    TabOrder = 7
    inherited HexEdit: TMemo
      Tag = 1
      PopupMenu = PopupMenu1
    end
  end
  inline DecFrame2: TDecEditFrame
    Left = 385
    Top = 97
    Width = 120
    Height = 27
    AutoSize = True
    TabOrder = 8
    inherited DecEdit: TMemo
      Tag = 1
      PopupMenu = PopupMenu1
    end
  end
  inline BinFrame3: TBinEditFrame
    Left = 2
    Top = 164
    Width = 289
    Height = 27
    AutoSize = True
    TabOrder = 9
    inherited BinEdit: TMemo
      Tag = 2
      PopupMenu = PopupMenu1
    end
  end
  inline HexFrame3: THexEditFrame
    Left = 295
    Top = 164
    Width = 105
    Height = 27
    AutoSize = True
    TabOrder = 10
    inherited HexEdit: TMemo
      Tag = 2
      PopupMenu = PopupMenu1
    end
  end
  inline DecFrame3: TDecEditFrame
    Left = 386
    Top = 164
    Width = 120
    Height = 27
    AutoSize = True
    TabOrder = 11
    inherited DecEdit: TMemo
      Tag = 2
      PopupMenu = PopupMenu1
    end
  end
  object SumButton: TButton
    Left = 392
    Top = 64
    Width = 25
    Height = 25
    Hint = 'Sum'
    Caption = '+'
    ParentShowHint = False
    ShowHint = True
    TabOrder = 12
    OnClick = OperationButtonClick
  end
  object DiffButton: TButton
    Tag = 1
    Left = 418
    Top = 64
    Width = 25
    Height = 25
    Hint = 'Difference'
    Caption = '-'
    ParentShowHint = False
    ShowHint = True
    TabOrder = 13
    OnClick = OperationButtonClick
  end
  object AndButton: TButton
    Tag = 4
    Left = 294
    Top = 64
    Width = 30
    Height = 25
    Hint = 'AND'
    Caption = 'AND'
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Arial Narrow'
    Font.Style = [fsBold]
    ParentFont = False
    ParentShowHint = False
    ShowHint = True
    TabOrder = 14
    OnClick = OperationButtonClick
  end
  object OrButton: TButton
    Tag = 5
    Left = 324
    Top = 64
    Width = 30
    Height = 25
    Hint = 'OR'
    Caption = 'OR'
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Arial Narrow'
    Font.Style = [fsBold]
    ParentFont = False
    ParentShowHint = False
    ShowHint = True
    TabOrder = 15
    OnClick = OperationButtonClick
  end
  object XorButton: TButton
    Tag = 6
    Left = 354
    Top = 64
    Width = 30
    Height = 25
    Hint = 'XOR'
    Caption = 'XOR'
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Arial Narrow'
    Font.Style = [fsBold]
    ParentFont = False
    ParentShowHint = False
    ShowHint = True
    TabOrder = 16
    OnClick = OperationButtonClick
  end
  object MultButton: TButton
    Tag = 2
    Left = 444
    Top = 64
    Width = 25
    Height = 25
    Hint = 'Multiplication'
    Caption = '*'
    ParentShowHint = False
    ShowHint = True
    TabOrder = 17
    OnClick = OperationButtonClick
  end
  object DivButton: TButton
    Tag = 3
    Left = 470
    Top = 64
    Width = 25
    Height = 25
    Hint = 'Division'
    Caption = '/'
    ParentShowHint = False
    ShowHint = True
    TabOrder = 18
    OnClick = OperationButtonClick
  end
  object SqrtButton: TButton
    Left = 8
    Top = 200
    Width = 29
    Height = 25
    Hint = 'SQRT'
    Caption = 'sqr'
    ParentShowHint = False
    ShowHint = True
    TabOrder = 19
    OnClick = ResultButtonClick
  end
  object SqwButton: TButton
    Tag = 1
    Left = 40
    Top = 200
    Width = 29
    Height = 25
    Hint = 'Squared'
    Caption = '2'
    ParentShowHint = False
    ShowHint = True
    TabOrder = 20
    OnClick = ResultButtonClick
  end
  object LeftButton: TButton
    Tag = 2
    Left = 192
    Top = 200
    Width = 29
    Height = 25
    Hint = 'Left Shift'
    Caption = '<<'
    ParentShowHint = False
    ShowHint = True
    TabOrder = 21
    OnClick = ResultButtonClick
  end
  object RightButton: TButton
    Tag = 3
    Left = 224
    Top = 200
    Width = 29
    Height = 25
    Hint = 'Right Shift'
    Caption = '>>'
    ParentShowHint = False
    ShowHint = True
    TabOrder = 22
    OnClick = ResultButtonClick
  end
  object InvButton: TButton
    Tag = 4
    Left = 256
    Top = 200
    Width = 29
    Height = 25
    Hint = 'Inversion'
    Caption = '~'
    ParentShowHint = False
    ShowHint = True
    TabOrder = 23
    OnClick = ResultButtonClick
  end
  object PopupMenu1: TPopupMenu
    OnPopup = PopupMenu1Popup
    Left = 280
    Top = 256
    object CutMenuItem: TMenuItem
      Caption = 'Zeroize'
      OnClick = PopupMenuItemClick
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
