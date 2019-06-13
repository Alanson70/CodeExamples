object ControlForm: TControlForm
  Left = 361
  Top = 104
  BorderIcons = [biSystemMenu]
  BorderStyle = bsSingle
  Caption = #1050#1086#1084#1084#1091#1085#1080#1082#1072#1094#1080#1086#1085#1085#1099#1081' '#1087#1086#1088#1090
  ClientHeight = 309
  ClientWidth = 433
  Color = clBtnFace
  Font.Charset = RUSSIAN_CHARSET
  Font.Color = clWindowText
  Font.Height = -13
  Font.Name = 'Arial'
  Font.Style = []
  OldCreateOrder = False
  Position = poMainFormCenter
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 16
  object CancelButton: TButton
    Left = 306
    Top = 272
    Width = 111
    Height = 27
    Caption = #1054#1090#1084#1077#1085#1072
    ModalResult = 2
    TabOrder = 0
    OnClick = CancelButtonClick
  end
  object PageControl1: TPageControl
    Left = 0
    Top = 0
    Width = 433
    Height = 257
    ActivePage = TtyTabSheet
    Align = alTop
    TabIndex = 0
    TabOrder = 1
    object TtyTabSheet: TTabSheet
      Caption = 'TTY'
      object TtyPanel: TPanel
        Left = 0
        Top = 0
        Width = 425
        Height = 176
        Align = alTop
        BevelOuter = bvNone
        TabOrder = 0
        object Label3: TLabel
          Left = 8
          Top = 60
          Width = 61
          Height = 16
          Caption = 'Baud Rate'
        end
        object Label4: TLabel
          Left = 8
          Top = 28
          Width = 24
          Height = 16
          Caption = 'Port'
        end
        object Label5: TLabel
          Left = 232
          Top = 27
          Width = 47
          Height = 16
          Caption = #1055#1072#1088#1080#1090#1077#1090
        end
        object TtyRateComboBox: TComboBox
          Left = 88
          Top = 56
          Width = 121
          Height = 24
          Style = csDropDownList
          ItemHeight = 16
          ItemIndex = 5
          TabOrder = 0
          Text = '4800'
          Items.Strings = (
            '110'
            '300'
            '600'
            '1200'
            '2400'
            '4800'
            '9600'
            '14400'
            '19200'
            '38400'
            '56000'
            '57600'
            '115200'
            '128000'
            '256000')
        end
        object TtyPortComboBox: TComboBox
          Left = 88
          Top = 24
          Width = 121
          Height = 24
          Style = csDropDownList
          ItemHeight = 16
          ItemIndex = 0
          TabOrder = 1
          Text = 'COM1'
          Items.Strings = (
            'COM1'
            'COM2')
        end
        object TtyParityComboBox: TComboBox
          Left = 296
          Top = 24
          Width = 105
          Height = 24
          ItemHeight = 16
          ItemIndex = 0
          TabOrder = 2
          Text = 'No'
          Items.Strings = (
            'No'
            'Odd'
            'Even')
        end
      end
    end
    object IPTabSheet: TTabSheet
      Caption = 'IP'
      ImageIndex = 1
      object IpPanel: TPanel
        Left = 0
        Top = 0
        Width = 425
        Height = 176
        Align = alTop
        BevelOuter = bvNone
        TabOrder = 0
        object Label6: TLabel
          Left = 184
          Top = 28
          Width = 62
          Height = 16
          Caption = 'Ip Address'
        end
        object Label7: TLabel
          Left = 184
          Top = 60
          Width = 38
          Height = 16
          Caption = 'Ip Port'
        end
        object Label1: TLabel
          Left = 8
          Top = 28
          Width = 48
          Height = 16
          Caption = 'Protocol'
        end
        object IpAddrEdit: TEdit
          Left = 272
          Top = 24
          Width = 121
          Height = 24
          TabOrder = 0
        end
        object IpPortEdit: TEdit
          Left = 272
          Top = 56
          Width = 121
          Height = 24
          TabOrder = 1
        end
        object IpComboBox: TComboBox
          Left = 72
          Top = 25
          Width = 73
          Height = 24
          Style = csDropDownList
          ItemHeight = 16
          ItemIndex = 0
          TabOrder = 2
          Text = 'TCP'
          Items.Strings = (
            'TCP'
            'UDP')
        end
      end
    end
  end
  object OkButton: TButton
    Left = 24
    Top = 272
    Width = 75
    Height = 25
    Caption = 'Ok'
    ModalResult = 1
    TabOrder = 2
  end
  object ConnectButton: TButton
    Left = 10
    Top = 215
    Width = 87
    Height = 27
    Caption = #1057#1086#1077#1076#1080#1085#1080#1090#1100
    ModalResult = 6
    TabOrder = 3
  end
  object DisconnectButton: TButton
    Left = 106
    Top = 215
    Width = 103
    Height = 27
    Caption = #1056#1072#1079#1098#1077#1076#1080#1085#1080#1090#1100
    Enabled = False
    TabOrder = 4
    OnClick = DisconnectButtonClick
  end
  object ParamsButton: TButton
    Left = 328
    Top = 216
    Width = 91
    Height = 25
    Caption = #1053#1072#1089#1090#1088#1086#1081#1082#1080
    TabOrder = 5
    OnClick = ParamsButtonClick
  end
end
