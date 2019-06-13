object DatesFrame: TDatesFrame
  Left = 0
  Top = 0
  Width = 437
  Height = 319
  Font.Charset = RUSSIAN_CHARSET
  Font.Color = clWindowText
  Font.Height = -13
  Font.Name = 'Comic Sans MS'
  Font.Style = [fsBold]
  ParentFont = False
  TabOrder = 0
  object Label1: TLabel
    Left = 0
    Top = 24
    Width = 87
    Height = 38
    Alignment = taCenter
    Caption = 'Object Pascal TDateTime'
    WordWrap = True
  end
  object Label2: TLabel
    Left = 0
    Top = 96
    Width = 81
    Height = 41
    Alignment = taCenter
    AutoSize = False
    Caption = 'DOS and Files Time'
    WordWrap = True
  end
  object Label3: TLabel
    Left = 0
    Top = 168
    Width = 81
    Height = 49
    Alignment = taCenter
    AutoSize = False
    Caption = 'UNIX Time'
    WordWrap = True
  end
  object Label4: TLabel
    Left = 96
    Top = 0
    Width = 25
    Height = 19
    Caption = 'DEC'
  end
  object Label5: TLabel
    Left = 256
    Top = 0
    Width = 27
    Height = 19
    Caption = 'HEX'
  end
  object Label6: TLabel
    Left = 96
    Top = 56
    Width = 249
    Height = 19
    Caption = 'Integral part - days from 30.12.1899'
    Enabled = False
  end
  object Label7: TLabel
    Left = 96
    Top = 128
    Width = 162
    Height = 19
    Caption = 'Seconds From 1.01.1980'
    Enabled = False
  end
  object Label8: TLabel
    Left = 96
    Top = 200
    Width = 162
    Height = 19
    Caption = 'Seconds From 1.01.1970'
    Enabled = False
  end
  object DateTimeStringEdit: TEdit
    Tag = 3
    Left = 96
    Top = 232
    Width = 297
    Height = 46
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -27
    Font.Name = 'Comic Sans MS'
    Font.Style = [fsBold]
    ParentFont = False
    PopupMenu = DatesPopupMenu
    ReadOnly = True
    TabOrder = 4
    Text = '22.04.2008-12:20:40'
  end
  object WindowsEdit: TEdit
    Left = 96
    Top = 24
    Width = 153
    Height = 27
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clNavy
    Font.Height = -13
    Font.Name = 'Comic Sans MS'
    Font.Style = [fsBold]
    MaxLength = 20
    ParentFont = False
    PopupMenu = DatesPopupMenu
    TabOrder = 0
    Text = 'WindowsEdit'
    OnChange = WindowsEditChange
  end
  object NowButton: TButton
    Left = 96
    Top = 280
    Width = 81
    Height = 25
    Caption = 'Now'
    TabOrder = 5
    OnClick = NowButtonClick
  end
  object ChooseDateButton: TButton
    Left = 216
    Top = 280
    Width = 65
    Height = 25
    Caption = 'Date'
    TabOrder = 6
    OnClick = ChooseDateButtonClick
  end
  object ChooseTimeButton: TButton
    Left = 320
    Top = 280
    Width = 73
    Height = 25
    Caption = 'Time'
    TabOrder = 7
    OnClick = ChooseTimeButtonClick
  end
  inline DosHexEditFrame: THexEditFrame
    Left = 256
    Top = 96
    Width = 90
    Height = 27
    AutoSize = True
    TabOrder = 2
    inherited HexEdit: TMemo
      PopupMenu = DatesPopupMenu
    end
  end
  inline LinuxHexEditFrame: THexEditFrame
    Left = 256
    Top = 168
    Width = 90
    Height = 27
    AutoSize = True
    TabOrder = 3
    inherited HexEdit: TMemo
      PopupMenu = DatesPopupMenu
    end
  end
  object WindowsHexEdit: TEdit
    Left = 256
    Top = 24
    Width = 169
    Height = 27
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clGreen
    Font.Height = -13
    Font.Name = 'Comic Sans MS'
    Font.Style = [fsBold]
    ParentFont = False
    PopupMenu = DatesPopupMenu
    TabOrder = 1
    Text = 'AAAAAAAAAAAAAAAA'
    OnChange = WindowsEditChange
  end
  object LinuxEdit: TMemo
    Left = 96
    Top = 168
    Width = 153
    Height = 25
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clNavy
    Font.Height = -13
    Font.Name = 'Comic Sans MS'
    Font.Style = [fsBold]
    Lines.Strings = (
      'LinuxEdit')
    MaxLength = 10
    ParentFont = False
    PopupMenu = DatesPopupMenu
    TabOrder = 8
    WordWrap = False
    OnChange = LinuxEditChange
  end
  object DosEdit: TMemo
    Left = 96
    Top = 96
    Width = 153
    Height = 25
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clNavy
    Font.Height = -13
    Font.Name = 'Comic Sans MS'
    Font.Style = [fsBold]
    Lines.Strings = (
      '')
    MaxLength = 10
    ParentFont = False
    PopupMenu = DatesPopupMenu
    TabOrder = 9
    WordWrap = False
    OnChange = DosEditChange
  end
  object DatesPopupMenu: TPopupMenu
    OnPopup = DatesPopupMenuPopup
    Left = 40
    Top = 238
    object CopyMenuItem: TMenuItem
      Caption = 'Copy'
      OnClick = DatesMenuItemClick
    end
    object PasteMenuItem: TMenuItem
      Tag = 1
      Caption = 'Paste'
      OnClick = DatesMenuItemClick
    end
  end
end
