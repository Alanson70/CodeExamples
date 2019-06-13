object FreqParamFrame: TFreqParamFrame
  Left = 0
  Top = 0
  Width = 452
  Height = 131
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  ParentFont = False
  TabOrder = 0
  object PlanParamsPanel: TPanel
    Left = 0
    Top = 0
    Width = 452
    Height = 131
    Align = alClient
    BevelOuter = bvLowered
    TabOrder = 0
    object Label24: TLabel
      Left = 6
      Top = 32
      Width = 98
      Height = 16
      AutoSize = False
      Caption = #1063#1072#1089#1090#1086#1090#1072', '#1043#1094
    end
    object StepLabel: TLabel
      Left = 5
      Top = 98
      Width = 85
      Height = 29
      AutoSize = False
      Caption = #1064#1072#1075' '#1088#1072#1089#1089#1090#1072#1085#1086#1074#1082#1080', '#1043#1094
      WordWrap = True
    end
    object Label1: TLabel
      Left = 4
      Top = 8
      Width = 76
      Height = 13
      Caption = #1053#1072#1080#1084#1077#1085#1086#1074#1072#1085#1080#1077
    end
    object Label2: TLabel
      Left = 6
      Top = 48
      Width = 91
      Height = 16
      AutoSize = False
      Caption = #1055#1086#1083#1086#1089#1072', '#1043#1094
    end
    object Bevel1: TBevel
      Left = 217
      Top = 6
      Width = 5
      Height = 117
      Shape = bsLeftLine
      Style = bsRaised
    end
    object FreqEdit: TEdit
      Left = 101
      Top = 29
      Width = 64
      Height = 22
      AutoSize = False
      MaxLength = 10
      TabOrder = 0
      Text = '50000000'
      OnChange = FreqEditChange
    end
    object StepEdit: TEdit
      Left = 101
      Top = 102
      Width = 42
      Height = 21
      TabOrder = 1
      Text = '22500'
      OnChange = StepEditChange
    end
    object StepUpDown: TUpDown
      Left = 143
      Top = 102
      Width = 21
      Height = 21
      Associate = StepEdit
      Min = 1
      Max = 25000
      Position = 22500
      TabOrder = 2
      Thousands = False
      Wrap = False
    end
    object FreqScrollBar: TScrollBar
      Left = 168
      Top = 28
      Width = 21
      Height = 24
      Kind = sbVertical
      LargeChange = 1000
      Max = 8000000
      Min = 50000
      PageSize = 0
      Position = 50000
      TabOrder = 3
      OnChange = FreqScrollBarChange
    end
    object FreqScrollBarKHZ: TScrollBar
      Left = 192
      Top = 28
      Width = 21
      Height = 24
      Kind = sbVertical
      LargeChange = 1000
      Max = 8000000
      Min = 50000
      PageSize = 0
      Position = 50000
      TabOrder = 4
      OnChange = FreqScrollBarChange
    end
    object NameEdit: TEdit
      Left = 101
      Top = 5
      Width = 106
      Height = 21
      MaxLength = 32
      TabOrder = 5
      Text = 'NameEdit'
      OnChange = NameEditChange
    end
    object ParamPanel: TPanel
      Left = 220
      Top = 2
      Width = 229
      Height = 124
      BevelOuter = bvNone
      TabOrder = 6
      object DataRateLabel: TLabel
        Left = 6
        Top = 8
        Width = 98
        Height = 16
        AutoSize = False
        Caption = #1048#1085#1092'. '#1089#1082#1086#1088#1086#1089#1090#1100', '#1073'/'#1089
        WordWrap = True
      end
      object Label11: TLabel
        Left = 6
        Top = 32
        Width = 98
        Height = 16
        AutoSize = False
        Caption = 'Overhead'
      end
      object Label12: TLabel
        Left = 6
        Top = 56
        Width = 98
        Height = 16
        AutoSize = False
        Caption = #1056#1080#1076'-'#1057#1086#1083#1086#1084#1086#1085
      end
      object Label22: TLabel
        Left = 6
        Top = 82
        Width = 98
        Height = 16
        AutoSize = False
        Caption = #1048#1079#1073#1099#1090'. '#1082#1086#1076#1080#1088'-'#1077
        WordWrap = True
      end
      object Label23: TLabel
        Left = 6
        Top = 104
        Width = 98
        Height = 16
        AutoSize = False
        Caption = #1052#1086#1076#1091#1083#1103#1094#1080#1103
      end
      object Label25: TLabel
        Left = 174
        Top = 30
        Width = 5
        Height = 13
        Caption = '/'
      end
      object Label26: TLabel
        Left = 174
        Top = 52
        Width = 5
        Height = 13
        Caption = '/'
      end
      object Label27: TLabel
        Left = 174
        Top = 76
        Width = 5
        Height = 13
        Caption = '/'
      end
      object CodingCheck: TCheckBox
        Left = 100
        Top = 78
        Width = 18
        Height = 17
        Alignment = taLeftJustify
        TabOrder = 0
        OnClick = CodingCheckClick
      end
      object RSCheck: TCheckBox
        Left = 100
        Top = 54
        Width = 18
        Height = 17
        Alignment = taLeftJustify
        TabOrder = 1
        OnClick = RSCheckClick
      end
      object OverheadCheck: TCheckBox
        Left = 100
        Top = 30
        Width = 18
        Height = 17
        Alignment = taLeftJustify
        TabOrder = 2
        OnClick = OverheadChange
      end
      object InfRateEdit: TEdit
        Left = 124
        Top = 4
        Width = 64
        Height = 21
        TabOrder = 3
        Text = '0'
        OnChange = InfRateEditChange
      end
      object InfRateUpDown: TUpDown
        Left = 188
        Top = 3
        Width = 20
        Height = 24
        Min = 0
        Max = 999
        Position = 0
        TabOrder = 4
        Thousands = False
        Wrap = False
        OnClick = InfRateUpDownClick
      end
      object InfRateUpDownKHZ: TUpDown
        Left = 209
        Top = 3
        Width = 20
        Height = 24
        Min = 0
        Max = 8000
        Position = 128
        TabOrder = 5
        Thousands = False
        Wrap = False
        OnClick = InfRateUpDownClick
      end
      object OverheadFactorEdit: TEdit
        Left = 124
        Top = 28
        Width = 30
        Height = 21
        ReadOnly = True
        TabOrder = 6
        Text = '16'
        OnChange = OverheadChange
      end
      object OverheadFactorUpDown: TUpDown
        Left = 154
        Top = 28
        Width = 19
        Height = 21
        Associate = OverheadFactorEdit
        Min = 1
        Max = 256
        Position = 16
        TabOrder = 7
        Wrap = False
      end
      object OverheadDivisorEdit: TEdit
        Left = 180
        Top = 28
        Width = 30
        Height = 21
        ReadOnly = True
        TabOrder = 8
        Text = '15'
        OnChange = OverheadChange
      end
      object RSFactorEdit: TEdit
        Left = 124
        Top = 52
        Width = 30
        Height = 21
        ReadOnly = True
        TabOrder = 9
        Text = '126'
        OnChange = RSCheckClick
      end
      object RSFactorUpDown: TUpDown
        Left = 154
        Top = 52
        Width = 19
        Height = 21
        Associate = RSFactorEdit
        Min = 1
        Max = 256
        Position = 126
        TabOrder = 10
        Wrap = False
      end
      object RSDivisorEdit: TEdit
        Left = 180
        Top = 52
        Width = 30
        Height = 21
        ReadOnly = True
        TabOrder = 11
        Text = '112'
        OnChange = RSCheckClick
      end
      object OverheadDivisorUpDown: TUpDown
        Left = 210
        Top = 28
        Width = 19
        Height = 21
        Associate = OverheadDivisorEdit
        Min = 1
        Max = 255
        Position = 15
        TabOrder = 12
        Wrap = False
      end
      object RSDivisorUpDown: TUpDown
        Left = 210
        Top = 52
        Width = 19
        Height = 21
        Associate = RSDivisorEdit
        Min = 1
        Max = 255
        Position = 112
        TabOrder = 13
        Wrap = False
      end
      object CodingDivisorUpDown: TUpDown
        Left = 210
        Top = 76
        Width = 19
        Height = 21
        Associate = CodingDivisorEdit
        Min = 2
        Position = 8
        TabOrder = 14
        Wrap = False
      end
      object CodingDivisorEdit: TEdit
        Left = 180
        Top = 76
        Width = 30
        Height = 21
        ReadOnly = True
        TabOrder = 15
        Text = '8'
        OnChange = CodingCheckClick
      end
      object CodingFactorUpDown: TUpDown
        Left = 154
        Top = 76
        Width = 19
        Height = 21
        Associate = CodingFactorEdit
        Min = 1
        Position = 7
        TabOrder = 16
        Wrap = False
      end
      object CodingFactorEdit: TEdit
        Left = 124
        Top = 76
        Width = 30
        Height = 21
        ReadOnly = True
        TabOrder = 17
        Text = '7'
        OnChange = CodingCheckClick
      end
      object ModulationCombo: TComboBox
        Left = 125
        Top = 100
        Width = 63
        Height = 21
        Style = csDropDownList
        ItemHeight = 13
        ItemIndex = 0
        TabOrder = 18
        Text = '  BPSK'
        OnChange = ModulationComboChange
        Items.Strings = (
          '  BPSK'
          '  QPSK'
          ' 8-PSK'
          '16-PSK')
      end
    end
    object BandEdit: TEdit
      Left = 101
      Top = 53
      Width = 64
      Height = 22
      AutoSize = False
      Enabled = False
      MaxLength = 10
      TabOrder = 7
      Text = '200000'
      OnChange = BandEditChange
    end
    object BandScrollBar: TScrollBar
      Left = 168
      Top = 52
      Width = 21
      Height = 24
      Kind = sbVertical
      LargeChange = 1000
      Max = 8000000
      Min = 50000
      PageSize = 0
      Position = 50000
      TabOrder = 8
      OnChange = BandScrollBarChange
    end
    object BandScrollBarKHZ: TScrollBar
      Left = 192
      Top = 52
      Width = 21
      Height = 24
      Kind = sbVertical
      LargeChange = 1000
      Max = 8000000
      Min = 50000
      PageSize = 0
      Position = 50000
      TabOrder = 9
      OnChange = BandScrollBarChange
    end
    object BandHandSetCheckBox: TCheckBox
      Left = 32
      Top = 75
      Width = 81
      Height = 17
      Alignment = taLeftJustify
      Caption = #1042#1088#1091#1095#1085#1091#1102
      TabOrder = 10
      OnClick = BandHandSetCheckBoxClick
    end
  end
end
