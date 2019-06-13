inherited AnalyserMeterFrame: TAnalyserMeterFrame
  Width = 803
  inherited APanel: TPanel
    Width = 803
    inherited ChartPanel: TPanel
      Width = 689
      inherited Chart1: TChart
        Width = 687
      end
      inherited InfoPanel: TPanel
        Width = 687
        inherited SignalInfoLabel: TLabel
          Width = 687
        end
      end
    end
    inherited FreqGroupBox: TGroupBox
      Width = 687
    end
    inherited ButtonsPanel: TPanel
      inherited SettsButton: TSpeedButton
        Down = True
      end
    end
  end
  inherited SettsPageControl: TPageControl
    Width = 803
    ActivePage = TabSheet6
    TabIndex = 3
    inherited PlanTabSheet: TTabSheet
      inherited PageControl2: TPageControl
        Width = 795
      end
    end
    inherited TabSheet5: TTabSheet
      inherited BeamWidthComboBox: TComboBox
        ItemIndex = 1
        Text = '2'
      end
      inherited BeamFadingEdit: TEdit
        Text = '4'
      end
      inherited BeamFadingUpDown: TUpDown
        Position = 4
      end
      inherited BeamColorsGroupBox: TGroupBox
        inherited BeamColorCheckBox: TCheckBox
          Checked = True
          State = cbChecked
        end
      end
      inherited BeamRefreshCheckBox: TCheckBox
        Checked = True
        State = cbChecked
      end
    end
    inherited TabSheet6: TTabSheet
      inherited FonGroupBox: TGroupBox
        inherited FonColorComboBox: TComboBox
          ItemIndex = 3
          Text = #1057#1080#1085#1080#1081
        end
      end
      inherited GridGroupBox: TGroupBox
        inherited GridColorComboBox: TComboBox
          ItemIndex = 9
          Text = #1047#1077#1083#1077#1085#1086#1074#1072#1090#1099#1081
        end
        inherited GridColorAdaptCheckBox: TCheckBox
          Checked = False
          State = cbUnchecked
        end
        inherited GridColorNoCheckBox: TCheckBox
          Checked = False
          State = cbUnchecked
        end
        inherited GridColorSplashCheckBox: TCheckBox
          Checked = False
          State = cbUnchecked
        end
      end
    end
    inherited AboutTabSheet: TTabSheet
      inherited ScrollBox1: TScrollBox
        Width = 795
      end
    end
  end
  inherited CtrlPanel: TPanel
    Width = 803
    BevelOuter = bvNone
    object CtrlPageControl: TPageControl
      Left = 0
      Top = 0
      Width = 803
      Height = 197
      ActivePage = ConnectTabSheet
      Align = alClient
      TabIndex = 3
      TabOrder = 0
      object QualTabSheet: TTabSheet
        Caption = #1050#1072#1095#1077#1089#1090#1074#1086
        object QualRadioGroup: TRadioGroup
          Left = 8
          Top = 8
          Width = 169
          Height = 101
          Caption = ' '#1050#1072#1095#1077#1089#1090#1074#1086' '#1080#1079#1084#1077#1088#1077#1085#1080#1081'  '
          ItemIndex = 1
          Items.Strings = (
            #1042#1099#1089#1086#1082#1086#1077
            #1054#1087#1090#1080#1084#1072#1083#1100#1085#1086#1077
            #1053#1080#1079#1082#1086#1077
            #1056#1091#1095#1085#1072#1103' '#1085#1072#1089#1090#1088#1086#1081#1082#1072)
          TabOrder = 0
          OnClick = QualRadioGroupClick
        end
        object StepPanel: TPanel
          Left = 180
          Top = 16
          Width = 309
          Height = 91
          TabOrder = 1
          DesignSize = (
            309
            91)
          object Label5: TLabel
            Left = 13
            Top = 43
            Width = 30
            Height = 16
            Caption = #1058#1086#1095#1077#1082
          end
          object Label4: TLabel
            Left = 13
            Top = 12
            Width = 44
            Height = 16
            Caption = #1064#1072#1075', '#1082#1043#1094
          end
          object CountEdit: TEdit
            Left = 72
            Top = 40
            Width = 41
            Height = 24
            ReadOnly = True
            TabOrder = 0
            Text = '20'
          end
          object StepEdit: TEdit
            Left = 72
            Top = 8
            Width = 41
            Height = 24
            ReadOnly = True
            TabOrder = 1
            Text = '20'
          end
          object CountScrollBar: TScrollBar
            Left = 120
            Top = 40
            Width = 153
            Height = 25
            Anchors = [akLeft, akTop, akRight]
            Max = 1000
            Min = 10
            PageSize = 0
            Position = 20
            TabOrder = 2
            OnChange = CountScrollBarChange
          end
          object StepScrollBar: TScrollBar
            Left = 120
            Top = 8
            Width = 153
            Height = 25
            Anchors = [akLeft, akTop, akRight]
            Max = 10000
            Min = 1
            PageSize = 0
            Position = 2000
            TabOrder = 3
            OnChange = StepScrollBarChange
          end
        end
      end
      object WorkTabSheet: TTabSheet
        Caption = #1056#1072#1073#1086#1090#1072
        ImageIndex = 1
        DesignSize = (
          795
          166)
        object Label15: TLabel
          Left = 152
          Top = 44
          Width = 16
          Height = 16
          Caption = #1089#1077#1082
        end
        object Label37: TLabel
          Left = 12
          Top = 116
          Width = 55
          Height = 16
          Caption = #1057#1086#1089#1090#1086#1103#1085#1080#1077
        end
        object WorkContRadioButton: TRadioButton
          Left = 8
          Top = 16
          Width = 113
          Height = 17
          Alignment = taLeftJustify
          Caption = #1053#1077#1087#1088#1077#1088#1099#1074#1085#1086
          Checked = True
          TabOrder = 0
          TabStop = True
          OnClick = WorkRadioButtonClick
        end
        object WorkIntervalRadioButton: TRadioButton
          Tag = 1
          Left = 8
          Top = 45
          Width = 113
          Height = 17
          Alignment = taLeftJustify
          Caption = #1057' '#1080#1085#1090#1077#1088#1074#1072#1083#1086#1084
          TabOrder = 1
          OnClick = WorkRadioButtonClick
        end
        object WorkOnceRadioButton: TRadioButton
          Tag = 2
          Left = 8
          Top = 72
          Width = 113
          Height = 17
          Alignment = taLeftJustify
          Caption = #1054#1076#1085#1086#1082#1088#1072#1090#1085#1086
          TabOrder = 2
          OnClick = WorkRadioButtonClick
        end
        object WorkIntervalEdit: TEdit
          Left = 176
          Top = 40
          Width = 33
          Height = 24
          ReadOnly = True
          TabOrder = 3
          Text = '5'
          OnChange = WorkIntervalEditChange
        end
        object WorkIntervalUpDown: TUpDown
          Left = 209
          Top = 40
          Width = 15
          Height = 24
          Associate = WorkIntervalEdit
          Min = 1
          Max = 600
          Position = 5
          TabOrder = 4
          Wrap = False
        end
        object RunButton: TButton
          Left = 152
          Top = 68
          Width = 73
          Height = 25
          Caption = #1047#1072#1087#1091#1089#1082
          TabOrder = 5
          OnClick = RunButtonClick
        end
        object AscingInfoLabel: TEdit
          Left = 80
          Top = 112
          Width = 704
          Height = 24
          Anchors = [akLeft, akTop, akRight]
          Color = clBtnFace
          ReadOnly = True
          TabOrder = 6
        end
      end
      object RecTabSheet: TTabSheet
        Caption = #1057#1072#1084#1086#1087#1080#1089#1077#1094
        ImageIndex = 2
        DesignSize = (
          795
          166)
        object Label36: TLabel
          Left = 16
          Top = 73
          Width = 111
          Height = 16
          Caption = #1052#1072#1082#1089#1080#1084#1072#1083#1100#1085#1086' '#1079#1072#1087#1080#1089#1077#1081
        end
        object Label38: TLabel
          Left = 131
          Top = 43
          Width = 12
          Height = 16
          Caption = #1085#1072
        end
        object Label35: TLabel
          Left = 16
          Top = 110
          Width = 26
          Height = 16
          Caption = #1055#1091#1090#1100
        end
        object Label32: TLabel
          Left = 16
          Top = 136
          Width = 26
          Height = 16
          Caption = #1060#1072#1081#1083
        end
        object Label31: TLabel
          Left = 264
          Top = 8
          Width = 99
          Height = 16
          Caption = #1057#1087#1086#1089#1086#1073' '#1089#1086#1093#1088#1072#1085#1077#1085#1080#1103
        end
        object RecIntervalCheckBox: TCheckBox
          Left = 16
          Top = 16
          Width = 105
          Height = 17
          Alignment = taLeftJustify
          Caption = #1057' '#1080#1085#1090#1077#1088#1074#1072#1083#1086#1084
          TabOrder = 0
        end
        object RecDivCheckBox: TCheckBox
          Left = 16
          Top = 44
          Width = 105
          Height = 17
          Alignment = taLeftJustify
          Caption = #1055#1088#1080' '#1086#1090#1082#1083#1086#1085#1077#1085#1080#1080
          Checked = True
          State = cbChecked
          TabOrder = 1
        end
        object RecIntervalEdit: TEdit
          Left = 152
          Top = 12
          Width = 25
          Height = 24
          ReadOnly = True
          TabOrder = 2
          Text = '1'
        end
        object RecIntervalUpDown: TUpDown
          Left = 177
          Top = 12
          Width = 15
          Height = 24
          Associate = RecIntervalEdit
          Min = 1
          Max = 60
          Position = 1
          TabOrder = 3
          Wrap = False
        end
        object RecDivEdit: TEdit
          Left = 152
          Top = 40
          Width = 25
          Height = 24
          ReadOnly = True
          TabOrder = 4
          Text = '1'
        end
        object RecDivUpDown: TUpDown
          Left = 177
          Top = 40
          Width = 16
          Height = 24
          Min = 1
          Max = 60
          Position = 10
          TabOrder = 5
          Wrap = False
          OnChangingEx = RecDivUpDownChangingEx
        end
        object RecIntervalComboBox: TComboBox
          Left = 195
          Top = 13
          Width = 54
          Height = 24
          Style = csDropDownList
          ItemHeight = 16
          ItemIndex = 1
          TabOrder = 6
          Text = #1052#1080#1085'.'
          Items.Strings = (
            #1057#1077#1082'.'
            #1052#1080#1085'.'
            #1063#1072#1089'.')
        end
        object RecDivComboBox: TComboBox
          Left = 195
          Top = 41
          Width = 54
          Height = 24
          Style = csDropDownList
          ItemHeight = 16
          ItemIndex = 1
          TabOrder = 7
          Text = 'dB'
          Items.Strings = (
            '%'
            'dB')
        end
        object RecMaxCountEdit: TEdit
          Left = 144
          Top = 69
          Width = 49
          Height = 24
          MaxLength = 5
          TabOrder = 8
          Text = '8000'
          OnChange = RecMaxCountEditChange
        end
        object RecPathEdit: TEdit
          Left = 64
          Top = 105
          Width = 642
          Height = 24
          Anchors = [akLeft, akTop, akRight]
          TabOrder = 9
          OnChange = RecFileNameEditChange
        end
        object RecFileNameEdit: TEdit
          Left = 64
          Top = 133
          Width = 298
          Height = 24
          Anchors = [akLeft, akTop, akRight]
          TabOrder = 10
          OnChange = RecFileNameEditChange
        end
        object RecStartButton: TButton
          Left = 370
          Top = 133
          Width = 113
          Height = 25
          Anchors = [akTop, akRight]
          Caption = #1053#1072#1095#1072#1090#1100' '#1079#1072#1087#1080#1089#1100
          Enabled = False
          TabOrder = 11
          OnClick = RecStartButtonClick
        end
        object RecPathButton: TButton
          Left = 715
          Top = 105
          Width = 75
          Height = 25
          Anchors = [akTop, akRight]
          Caption = #1042#1099#1073#1088#1072#1090#1100
          TabOrder = 12
          OnClick = RecPathButtonClick
        end
        object Panel1: TPanel
          Left = 480
          Top = 8
          Width = 209
          Height = 81
          TabOrder = 13
          Visible = False
          object Label39: TLabel
            Left = 41
            Top = 7
            Width = 94
            Height = 16
            Caption = #1055#1086#1089#1083#1077#1076#1085#1103#1103' '#1088#1072#1073#1086#1090#1072
          end
          object Label33: TLabel
            Left = 9
            Top = 34
            Width = 104
            Height = 16
            Caption = #1055#1088#1086#1076#1086#1083#1078#1080#1090#1077#1083#1100#1085#1086#1089#1090#1100
          end
          object Label34: TLabel
            Left = 10
            Top = 54
            Width = 102
            Height = 16
            Caption = #1050#1086#1083#1080#1095#1077#1089#1090#1074#1086' '#1079#1072#1087#1080#1089#1077#1081
          end
          object RecTimeEdit: TEdit
            Left = 120
            Top = 29
            Width = 81
            Height = 24
            ReadOnly = True
            TabOrder = 0
          end
          object RecCountEdit: TEdit
            Left = 120
            Top = 53
            Width = 81
            Height = 24
            TabOrder = 1
          end
        end
        object RecToCSVCheckBox: TCheckBox
          Left = 264
          Top = 32
          Width = 161
          Height = 17
          Alignment = taLeftJustify
          Caption = #1060#1072#1081#1083#1099' '#1089' '#1090#1072#1073#1083#1080#1094#1077#1081' CSV'
          TabOrder = 14
        end
        object RecToSA4CheckBox: TCheckBox
          Left = 264
          Top = 56
          Width = 161
          Height = 17
          Alignment = taLeftJustify
          Caption = #1060#1072#1081#1083' CSV '#1085#1077#1087#1088#1077#1088#1099#1074#1085#1099#1081
          Checked = True
          State = cbChecked
          TabOrder = 15
        end
        object RecToJPEGCheckBox: TCheckBox
          Left = 264
          Top = 80
          Width = 161
          Height = 17
          Alignment = taLeftJustify
          Caption = #1060#1072#1081#1083#1099' '#1082#1072#1088#1090#1080#1085#1086#1082' JPEG'
          TabOrder = 16
        end
      end
      object ConnectTabSheet: TTabSheet
        Caption = #1057#1086#1077#1076#1080#1085#1077#1085#1080#1077
        ImageIndex = 3
        inline ConnectFrame1: TConnectFrame
          Left = 0
          Top = 0
          Width = 795
          Height = 166
          Align = alClient
          Font.Charset = RUSSIAN_CHARSET
          Font.Color = clWindowText
          Font.Height = -13
          Font.Name = 'Arial'
          Font.Style = []
          ParentFont = False
          TabOrder = 0
        end
      end
    end
  end
  object WorkIntervalTimer: TTimer
    Enabled = False
    OnTimer = WorkIntervalTimerTimer
    Left = 184
    Top = 360
  end
  object RecTimer: TTimer
    Enabled = False
    OnTimer = RecTimerTimer
    Left = 552
    Top = 96
  end
  object InfoTimer: TTimer
    OnTimer = InfoTimerTimer
    Left = 216
    Top = 16
  end
end
