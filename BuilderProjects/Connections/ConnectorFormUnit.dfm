object ConnectorForm: TConnectorForm
  Left = 338
  Top = 219
  BorderIcons = [biSystemMenu]
  BorderStyle = bsSingle
  Caption = #1057#1086#1077#1076#1080#1085#1077#1085#1080#1077
  ClientHeight = 318
  ClientWidth = 381
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poOwnerFormCenter
  PixelsPerInch = 96
  TextHeight = 13
  object CancelButton: TButton
    Left = 278
    Top = 280
    Width = 83
    Height = 25
    Cursor = crHandPoint
    Caption = 'OK'
    ModalResult = 1
    TabOrder = 0
  end
  object ConnectButton: TButton
    Left = 16
    Top = 280
    Width = 97
    Height = 25
    Cursor = crHandPoint
    Caption = #1057#1086#1077#1076#1080#1085#1080#1090#1100
    TabOrder = 1
    OnClick = ConnectButtonClick
  end
  object DisconnectButton: TButton
    Left = 120
    Top = 280
    Width = 89
    Height = 25
    Cursor = crHandPoint
    Caption = #1056#1072#1079#1086#1088#1074#1072#1090#1100
    TabOrder = 2
    OnClick = DisconnectButtonClick
  end
  object PageControl1: TPageControl
    Left = 0
    Top = 0
    Width = 381
    Height = 273
    ActivePage = SettingsTabSheet
    Align = alTop
    TabIndex = 2
    TabOrder = 3
    object StatusTabSheet: TTabSheet
      Caption = #1057#1086#1089#1090#1086#1103#1085#1080#1077
      object Label2: TLabel
        Left = 16
        Top = 18
        Width = 34
        Height = 13
        Caption = #1057#1090#1072#1090#1091#1089
      end
      object ReconnectRepeatLabel: TLabel
        Left = 16
        Top = 40
        Width = 162
        Height = 13
        Caption = #1055#1086#1074#1090#1086#1088' '#1089#1086#1077#1076#1080#1085#1077#1085#1080#1103', '#1095#1077#1088#1077#1079' ('#1089#1077#1082')'
      end
      object ConnectingTimerLabel: TLabel
        Left = 16
        Top = 64
        Width = 160
        Height = 13
        Caption = #1059#1089#1090#1072#1085#1086#1074#1083#1077#1085#1080#1077' '#1089#1086#1077#1076#1080#1085#1077#1085#1080#1103'('#1089#1077#1082')'
      end
      object Label5: TLabel
        Left = 16
        Top = 87
        Width = 127
        Height = 13
        Caption = #1055#1086#1089#1083#1072#1085#1086' '#1087#1072#1082#1077#1090#1086#1074' ('#1050#1073#1072#1081#1090')'
      end
      object Label1: TLabel
        Left = 16
        Top = 110
        Width = 126
        Height = 13
        Caption = #1055#1088#1080#1085#1103#1090#1086' '#1087#1072#1082#1077#1090#1086#1074' ('#1050#1073#1072#1081#1090')'
      end
      object Label4: TLabel
        Left = 16
        Top = 137
        Width = 104
        Height = 13
        Caption = #1055#1088#1086#1076#1086#1083#1078#1080#1090#1077#1083#1100#1085#1086#1089#1090#1100
      end
      object Label6: TLabel
        Left = 16
        Top = 159
        Width = 83
        Height = 13
        Caption = #1047#1072#1076#1077#1088#1078#1082#1072', '#1084#1089#1077#1082
      end
      object StatusCombo: TComboBox
        Left = 168
        Top = 12
        Width = 193
        Height = 21
        Style = csSimple
        ItemHeight = 13
        ItemIndex = 1
        TabOrder = 0
        Text = #1059#1089#1090#1072#1085#1072#1074#1083#1080#1074#1072#1077#1090#1089#1103
        Items.Strings = (
          #1053#1077' '#1091#1089#1090#1072#1085#1086#1074#1083#1077#1085#1086
          #1059#1089#1090#1072#1085#1072#1074#1083#1080#1074#1072#1077#1090#1089#1103
          #1059#1089#1090#1072#1085#1086#1074#1083#1077#1085#1086)
      end
      object ReconnectRepeatEdit: TEdit
        Left = 288
        Top = 36
        Width = 73
        Height = 21
        TabOrder = 1
      end
      object ConnectingTimerEdit: TEdit
        Left = 288
        Top = 60
        Width = 73
        Height = 21
        TabOrder = 2
      end
      object SendCountEdit: TEdit
        Left = 168
        Top = 84
        Width = 193
        Height = 21
        TabOrder = 3
      end
      object ReceiveCountEdit: TEdit
        Left = 168
        Top = 108
        Width = 193
        Height = 21
        TabOrder = 4
      end
      object TimeEdit: TEdit
        Left = 168
        Top = 133
        Width = 193
        Height = 21
        ReadOnly = True
        TabOrder = 5
      end
      object PingEdit: TEdit
        Left = 168
        Top = 157
        Width = 193
        Height = 21
        TabOrder = 6
      end
    end
    object InterfaceTabSheet: TTabSheet
      Caption = #1048#1085#1090#1077#1088#1092#1077#1081#1089
      ImageIndex = 1
      object ConnectPageControl: TPageControl
        Left = 0
        Top = 0
        Width = 373
        Height = 201
        ActivePage = IPTabSheet
        Align = alTop
        TabIndex = 0
        TabOrder = 0
        object IPTabSheet: TTabSheet
          Caption = 'IP'
          object Label12: TLabel
            Left = 8
            Top = 16
            Width = 24
            Height = 13
            Caption = #1057#1077#1090#1100
          end
          object Label13: TLabel
            Left = 8
            Top = 40
            Width = 31
            Height = 13
            Caption = #1040#1076#1088#1077#1089
          end
          object Label14: TLabel
            Left = 8
            Top = 64
            Width = 25
            Height = 13
            Caption = #1055#1086#1088#1090
          end
          object Label15: TLabel
            Left = 8
            Top = 88
            Width = 49
            Height = 13
            Caption = #1055#1088#1086#1090#1086#1082#1086#1083
          end
          object IpTypeComboBox: TComboBox
            Left = 144
            Top = 12
            Width = 209
            Height = 21
            ItemHeight = 13
            ItemIndex = 0
            TabOrder = 0
            Text = #1042#1088#1091#1095#1085#1091#1102
            Items.Strings = (
              #1042#1088#1091#1095#1085#1091#1102)
          end
          object IpAddrEdit: TEdit
            Left = 144
            Top = 40
            Width = 121
            Height = 21
            ReadOnly = True
            TabOrder = 1
            Text = '178.1.1.1'
          end
          object IpAddrComboBox: TComboBox
            Left = 145
            Top = 111
            Width = 89
            Height = 21
            Enabled = False
            ItemHeight = 13
            ItemIndex = 0
            TabOrder = 2
            Text = '175.0.0.37'
            Visible = False
            Items.Strings = (
              '175.0.0.37')
          end
          object IpPortEdit: TEdit
            Left = 144
            Top = 64
            Width = 121
            Height = 21
            Enabled = False
            TabOrder = 3
            Text = '8000'
          end
          object ProtokolComboBox: TComboBox
            Left = 144
            Top = 88
            Width = 121
            Height = 21
            Style = csDropDownList
            Enabled = False
            ItemHeight = 13
            ItemIndex = 0
            TabOrder = 4
            Text = 'TCP'
            Items.Strings = (
              'TCP'
              'UDP')
          end
          object IpAddrButton: TButton
            Left = 268
            Top = 40
            Width = 21
            Height = 21
            Caption = '...'
            TabOrder = 5
          end
          object Button1: TButton
            Left = 268
            Top = 64
            Width = 21
            Height = 21
            Caption = '...'
            TabOrder = 6
            Visible = False
          end
        end
        object TtyTabSheet: TTabSheet
          Caption = 'TTY'
          ImageIndex = 1
          TabVisible = False
          object Label10: TLabel
            Left = 16
            Top = 10
            Width = 25
            Height = 13
            Caption = #1055#1086#1088#1090
          end
          object Label11: TLabel
            Left = 16
            Top = 34
            Width = 48
            Height = 13
            Caption = #1057#1082#1086#1088#1086#1089#1090#1100
          end
          object TtyRateCombo: TComboBox
            Left = 152
            Top = 32
            Width = 145
            Height = 21
            ItemHeight = 13
            ItemIndex = 3
            TabOrder = 0
            Text = '9600'
            Items.Strings = (
              '1200'
              '2400'
              '4800'
              '9600'
              '19200'
              '38400'
              '57600')
          end
          object TtyPortCombo: TComboBox
            Left = 152
            Top = 8
            Width = 145
            Height = 21
            ItemHeight = 13
            ItemIndex = 0
            TabOrder = 1
            Text = 'COM1'
            Items.Strings = (
              'COM1'
              'COM2'
              'COM3'
              'COM4'
              'COM5'
              'COM6')
          end
          object TtyEdit: TEdit
            Left = 144
            Top = 128
            Width = 225
            Height = 21
            Enabled = False
            TabOrder = 2
            Text = 'AtModemEdit'
            Visible = False
          end
        end
        object ATTabSheet: TTabSheet
          Caption = 'AT-'#1084#1086#1076#1077#1084
          ImageIndex = 2
          TabVisible = False
          object Label7: TLabel
            Left = 16
            Top = 10
            Width = 25
            Height = 13
            Caption = #1055#1086#1088#1090
          end
          object Label8: TLabel
            Left = 16
            Top = 34
            Width = 48
            Height = 13
            Caption = #1057#1082#1086#1088#1086#1089#1090#1100
          end
          object InitStringLabel: TLabel
            Left = 16
            Top = 58
            Width = 117
            Height = 13
            Caption = #1057#1090#1088#1086#1082#1072' '#1080#1085#1080#1094#1080#1072#1083#1080#1079#1072#1094#1080#1080
            Visible = False
          end
          object DialLabel: TLabel
            Left = 16
            Top = 82
            Width = 58
            Height = 13
            Caption = #1058#1080#1087' '#1085#1072#1073#1086#1088#1072
          end
          object Label9: TLabel
            Left = 16
            Top = 106
            Width = 100
            Height = 13
            Caption = #1053#1086#1084#1077#1088' '#1090#1077#1083#1077#1092#1086#1085#1085#1099#1081
          end
          object AtRateCombo: TComboBox
            Left = 152
            Top = 32
            Width = 145
            Height = 21
            ItemHeight = 13
            ItemIndex = 3
            TabOrder = 0
            Text = '9600'
            Items.Strings = (
              '1200'
              '2400'
              '4800'
              '9600'
              '19200'
              '38400'
              '57600')
          end
          object AtInitStringEdit: TEdit
            Left = 152
            Top = 56
            Width = 225
            Height = 21
            TabOrder = 1
            Text = 'AT'
            Visible = False
          end
          object AtPortCombo: TComboBox
            Left = 152
            Top = 8
            Width = 145
            Height = 21
            ItemHeight = 13
            ItemIndex = 0
            TabOrder = 2
            Text = 'COM1'
            Items.Strings = (
              'COM1'
              'COM2'
              'COM3'
              'COM4'
              'COM5'
              'COM6')
          end
          object AtDialCombo: TComboBox
            Left = 152
            Top = 80
            Width = 137
            Height = 21
            ItemHeight = 13
            ItemIndex = 0
            TabOrder = 3
            Text = #1048#1084#1087#1091#1083#1100#1089#1085#1099#1081
            Items.Strings = (
              #1048#1084#1087#1091#1083#1100#1089#1085#1099#1081
              #1058#1086#1085#1086#1074#1099#1081)
          end
          object AtCallingNumberEdit: TEdit
            Left = 152
            Top = 104
            Width = 137
            Height = 21
            MaxLength = 10
            TabOrder = 4
            Text = '123'
          end
          object AtModemEdit: TEdit
            Left = 152
            Top = 128
            Width = 225
            Height = 21
            Enabled = False
            TabOrder = 5
            Text = 'AtModemEdit'
          end
        end
      end
      object DefaultInterfaceCheck: TCheckBox
        Left = 280
        Top = 214
        Width = 97
        Height = 18
        Caption = #1055#1086' '#1091#1084#1086#1083#1095#1072#1085#1080#1102
        TabOrder = 1
        Visible = False
      end
      object UseTunnelCheck: TCheckBox
        Left = 8
        Top = 212
        Width = 177
        Height = 17
        Alignment = taLeftJustify
        Caption = #1042#1089#1077#1075#1076#1072' '#1080#1089#1087#1086#1083#1100#1079#1086#1074#1072#1090#1100' '#1090#1091#1085#1085#1077#1083#1080
        Enabled = False
        TabOrder = 2
        Visible = False
      end
    end
    object SettingsTabSheet: TTabSheet
      Caption = #1053#1072#1089#1090#1088#1086#1081#1082#1080
      ImageIndex = 2
      object ReconnectCheck: TCheckBox
        Left = 8
        Top = 18
        Width = 249
        Height = 17
        Cursor = crHandPoint
        Caption = #1042#1086#1089#1089#1090#1072#1085#1072#1074#1083#1080#1074#1072#1090#1100' '#1087#1088#1080' '#1086#1073#1088#1099#1074#1077' '#1095#1077#1088#1077#1079' ('#1089#1077#1082')'
        Checked = True
        State = cbChecked
        TabOrder = 0
      end
      object ReconnectEdit: TEdit
        Left = 304
        Top = 16
        Width = 41
        Height = 21
        ReadOnly = True
        TabOrder = 1
        Text = '10'
      end
      object ReconnectUpDown: TUpDown
        Left = 345
        Top = 16
        Width = 15
        Height = 21
        Cursor = crHandPoint
        Associate = ReconnectEdit
        Min = 10
        Max = 3600
        Position = 10
        TabOrder = 2
        Wrap = False
      end
      object DisconnectUpDown: TUpDown
        Left = 345
        Top = 40
        Width = 15
        Height = 21
        Cursor = crHandPoint
        Associate = DisconnectEdit
        Min = 10
        Max = 3600
        Position = 10
        TabOrder = 3
        Wrap = False
      end
      object DisconnectEdit: TEdit
        Left = 304
        Top = 40
        Width = 41
        Height = 21
        ReadOnly = True
        TabOrder = 4
        Text = '10'
      end
      object DisconnectCheck: TCheckBox
        Left = 8
        Top = 42
        Width = 249
        Height = 17
        Cursor = crHandPoint
        Caption = #1054#1073#1088#1099#1074#1072#1090#1100' '#1087#1088#1080' '#1086#1090#1089#1091#1090#1089#1090#1074#1080#1080' '#1076#1072#1085#1085#1099#1093' '#1095#1077#1088#1077#1079' ('#1089#1077#1082')'
        Checked = True
        State = cbChecked
        TabOrder = 5
      end
      object ConnectingCheck: TCheckBox
        Left = 8
        Top = 66
        Width = 249
        Height = 17
        Cursor = crHandPoint
        Caption = #1054#1078#1080#1076#1072#1085#1080#1077' '#1087#1086#1076#1090#1074#1077#1088#1078#1076#1077#1085#1080#1103' '#1089#1074#1103#1079#1080' '#1074' '#1090#1077#1095#1077#1085#1080#1080
        Checked = True
        State = cbChecked
        TabOrder = 6
      end
      object ConnectingEdit: TEdit
        Left = 304
        Top = 64
        Width = 41
        Height = 21
        ReadOnly = True
        TabOrder = 7
        Text = '10'
      end
      object ConnectingUpDown: TUpDown
        Left = 345
        Top = 64
        Width = 15
        Height = 21
        Cursor = crHandPoint
        Associate = ConnectingEdit
        Min = 10
        Max = 3600
        Position = 10
        TabOrder = 8
        Wrap = False
      end
      object PingCheck: TCheckBox
        Left = 8
        Top = 120
        Width = 273
        Height = 17
        Caption = #1050#1086#1085#1090#1088#1086#1083#1100' '#1087#1072#1088#1072#1084#1077#1090#1088#1086#1074' '#1089#1086#1077#1076#1080#1085#1077#1085#1080#1103' '#1089' '#1080#1085#1090#1077#1088#1074#1072#1083#1086#1084' ('#1089#1077#1082')'
        Checked = True
        State = cbChecked
        TabOrder = 9
        Visible = False
      end
      object PingTimeEdit: TEdit
        Left = 304
        Top = 118
        Width = 41
        Height = 21
        ReadOnly = True
        TabOrder = 10
        Text = '10'
        Visible = False
      end
      object PingTimeUpDown: TUpDown
        Left = 345
        Top = 118
        Width = 15
        Height = 21
        Cursor = crHandPoint
        Associate = PingTimeEdit
        Min = 2
        Max = 60
        Position = 10
        TabOrder = 11
        Visible = False
        Wrap = False
      end
    end
  end
  object DrawTimer: TTimer
    Enabled = False
    OnTimer = DrawTimerTimer
    Left = 232
    Top = 280
  end
end
