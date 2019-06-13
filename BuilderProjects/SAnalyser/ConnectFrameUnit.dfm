object ConnectFrame: TConnectFrame
  Left = 0
  Top = 0
  Width = 635
  Height = 153
  Font.Charset = RUSSIAN_CHARSET
  Font.Color = clWindowText
  Font.Height = -13
  Font.Name = 'Arial'
  Font.Style = []
  ParentFont = False
  TabOrder = 0
  object Label13: TLabel
    Left = 430
    Top = 80
    Width = 63
    Height = 16
    Caption = #1057#1086#1089#1090#1086#1103#1085#1080#1077
  end
  object Label14: TLabel
    Left = 432
    Top = 112
    Width = 49
    Height = 16
    Caption = #1055#1088#1080#1085#1103#1090#1086
    Visible = False
  end
  object CommPageControl: TPageControl
    Left = 0
    Top = 0
    Width = 417
    Height = 153
    ActivePage = PortTabSheet
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Arial Narrow'
    Font.Style = []
    MultiLine = True
    ParentFont = False
    TabIndex = 0
    TabOrder = 0
    TabPosition = tpLeft
    object PortTabSheet: TTabSheet
      Caption = #1057#1087#1086#1089#1086#1073
      object TermPageControl: TPageControl
        Left = 0
        Top = 0
        Width = 388
        Height = 145
        ActivePage = IPTabSheet
        Align = alClient
        Style = tsButtons
        TabIndex = 0
        TabOrder = 0
        object IPTabSheet: TTabSheet
          Caption = 'IP'
          ImageIndex = 1
          object IpPanel: TPanel
            Left = 0
            Top = 0
            Width = 380
            Height = 111
            Align = alClient
            BevelOuter = bvNone
            TabOrder = 0
            object Label6: TLabel
              Left = 8
              Top = 36
              Width = 42
              Height = 16
              Caption = 'Ip '#1040#1076#1088#1077#1089
            end
            object Label7: TLabel
              Left = 8
              Top = 68
              Width = 38
              Height = 16
              Caption = 'Ip '#1055#1086#1088#1090
            end
            object Label1: TLabel
              Left = 8
              Top = 4
              Width = 49
              Height = 16
              Caption = #1055#1088#1086#1090#1086#1082#1086#1083
            end
            object IpAddrEdit: TEdit
              Left = 104
              Top = 32
              Width = 89
              Height = 24
              TabOrder = 0
            end
            object IpPortEdit: TEdit
              Left = 104
              Top = 64
              Width = 89
              Height = 24
              TabOrder = 1
            end
            object IpComboBox: TComboBox
              Left = 104
              Top = 1
              Width = 89
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
            object AutoConnectCheckBox: TCheckBox
              Left = 6
              Top = 96
              Width = 243
              Height = 17
              Alignment = taLeftJustify
              Caption = #1042#1086#1089#1089#1090#1072#1085#1072#1074#1083#1080#1074#1072#1090#1100' '#1072#1074#1090#1086#1084#1072#1090#1080#1095#1077#1089#1082#1080
              TabOrder = 3
            end
          end
        end
        object TtyTabSheet: TTabSheet
          Caption = 'TTY'
          object TtyPanel: TPanel
            Left = 0
            Top = 0
            Width = 380
            Height = 113
            Align = alTop
            BevelOuter = bvNone
            TabOrder = 0
            object Label3: TLabel
              Left = 8
              Top = 36
              Width = 81
              Height = 16
              Caption = #1057#1082#1086#1088#1086#1089#1090#1100', '#1041#1080#1090'/'#1089
            end
            object Label4: TLabel
              Left = 8
              Top = 4
              Width = 26
              Height = 16
              Caption = #1055#1086#1088#1090
            end
            object Label5: TLabel
              Left = 8
              Top = 67
              Width = 44
              Height = 16
              Caption = #1055#1072#1088#1080#1090#1077#1090
            end
            object TtyRateComboBox: TComboBox
              Left = 104
              Top = 32
              Width = 89
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
              Left = 104
              Top = 0
              Width = 89
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
              Left = 104
              Top = 64
              Width = 89
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
      end
    end
    object ParamsTabSheet: TTabSheet
      Caption = #1053#1072#1089#1090#1088#1086#1081#1082#1080
      ImageIndex = 1
      object ParamPanel: TPanel
        Left = 0
        Top = 0
        Width = 388
        Height = 145
        Align = alClient
        BevelOuter = bvNone
        TabOrder = 0
        object Label8: TLabel
          Left = 8
          Top = 21
          Width = 65
          Height = 16
          Caption = #1053#1072' '#1087#1077#1088#1077#1076#1072#1095#1091
        end
        object Label9: TLabel
          Left = 8
          Top = 47
          Width = 48
          Height = 16
          Caption = #1053#1072' '#1087#1088#1080#1105#1084
        end
        object Label10: TLabel
          Left = 8
          Top = 0
          Width = 130
          Height = 16
          Caption = #1044#1086#1087#1086#1083#1085#1077#1085#1080#1077' '#1082#1086#1085#1094#1072' '#1089#1090#1088#1086#1082#1080
        end
        object Label11: TLabel
          Left = 8
          Top = 72
          Width = 137
          Height = 16
          Caption = #1044#1086#1087#1086#1083#1085#1077#1085#1080#1077' '#1085#1072#1095#1072#1083#1072' '#1089#1090#1088#1086#1082#1080
        end
        object Label2: TLabel
          Left = 8
          Top = 95
          Width = 65
          Height = 16
          Caption = #1053#1072' '#1087#1077#1088#1077#1076#1072#1095#1091
        end
        object Label12: TLabel
          Left = 8
          Top = 120
          Width = 48
          Height = 16
          Caption = #1053#1072' '#1087#1088#1080#1105#1084
        end
        object AdditionSendingOptionComboBox: TComboBox
          Left = 104
          Top = 18
          Width = 65
          Height = 24
          ItemHeight = 16
          ItemIndex = 0
          TabOrder = 0
          Text = 'CR+LF'
          OnChange = AdditionOptionComboBoxChange
          Items.Strings = (
            'CR+LF'
            'CR'
            'LF'
            #1076#1088#1091#1075#1086#1077)
        end
        object AdditionReceivingOptionComboBox: TComboBox
          Left = 104
          Top = 46
          Width = 65
          Height = 24
          ItemHeight = 16
          TabOrder = 1
          Text = 'CR+LF'
          OnChange = AdditionOptionComboBoxChange
          Items.Strings = (
            'CR+LF'
            'CR'
            'LF'
            #1076#1088#1091#1075#1086#1077)
        end
        object StringEndSendingOptionEdit: TEdit
          Left = 168
          Top = 18
          Width = 217
          Height = 24
          MaxLength = 17
          TabOrder = 2
          Text = '00'
          Visible = False
          OnChange = StringEndOptionEditChange
        end
        object StringEndReceivingOptionEdit: TEdit
          Left = 168
          Top = 46
          Width = 217
          Height = 24
          MaxLength = 17
          TabOrder = 3
          Text = '00'
          Visible = False
          OnChange = StringEndOptionEditChange
        end
        object PrefixSendingEdit: TEdit
          Left = 104
          Top = 91
          Width = 281
          Height = 24
          TabOrder = 4
        end
        object PrefixReceivingEdit: TEdit
          Left = 104
          Top = 119
          Width = 281
          Height = 24
          TabOrder = 5
        end
      end
    end
  end
  object ConnectButton: TButton
    Left = 434
    Top = 8
    Width = 111
    Height = 27
    Caption = #1057#1086#1077#1076#1080#1085#1080#1090#1100
    ModalResult = 6
    TabOrder = 1
    OnClick = ConnectButtonClick
  end
  object DisconnectButton: TButton
    Left = 434
    Top = 40
    Width = 111
    Height = 27
    Caption = #1056#1072#1079#1098#1077#1076#1080#1085#1080#1090#1100
    Enabled = False
    TabOrder = 2
    OnClick = DisconnectButtonClick
  end
  object StatusLampPanel: TPanel
    Left = 517
    Top = 74
    Width = 28
    Height = 28
    BevelInner = bvRaised
    BevelWidth = 2
    BorderWidth = 1
    BorderStyle = bsSingle
    TabOrder = 3
  end
  object StatusEdit: TEdit
    Left = 489
    Top = 108
    Width = 58
    Height = 24
    ReadOnly = True
    TabOrder = 4
    Text = '22:44:55'
    Visible = False
  end
  object IPConnectTimer: TTimer
    Interval = 60000
    OnTimer = IPConnectTimerTimer
    Left = 96
    Top = 8
  end
  object StatusTimer: TTimer
    Enabled = False
    OnTimer = StatusTimerTimer
    Left = 56
    Top = 56
  end
  object CanWriteTimer: TTimer
    Enabled = False
    Interval = 10000
    OnTimer = CanWriteTimerTimer
    Left = 232
    Top = 48
  end
end
