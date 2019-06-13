object AnalyserBaseFrame: TAnalyserBaseFrame
  Left = 0
  Top = 0
  Width = 804
  Height = 726
  Font.Charset = RUSSIAN_CHARSET
  Font.Color = clWindowText
  Font.Height = -13
  Font.Name = 'Arial Narrow'
  Font.Style = []
  ParentFont = False
  TabOrder = 0
  object APanel: TPanel
    Left = 0
    Top = 0
    Width = 804
    Height = 332
    Align = alClient
    TabOrder = 0
    DesignSize = (
      804
      332)
    object LevelGroupBox: TGroupBox
      Left = 4
      Top = 2
      Width = 101
      Height = 243
      Anchors = [akLeft, akTop, akBottom]
      Caption = ' '#1059#1088#1086#1074#1077#1085#1100' '
      TabOrder = 0
      DesignSize = (
        101
        243)
      object LevelAutoFitCheckBox: TCheckBox
        Left = 2
        Top = 219
        Width = 97
        Height = 19
        Anchors = [akBottom]
        Caption = #1040#1074#1090#1086#1084#1072#1090#1080#1095#1077#1089#1082#1080
        Checked = True
        State = cbChecked
        TabOrder = 0
        OnClick = LevelAutoFitCheckBoxClick
      end
      object LevelHandsPanel: TPanel
        Left = 2
        Top = 18
        Width = 97
        Height = 202
        Align = alTop
        Anchors = [akLeft, akTop, akRight, akBottom]
        BevelOuter = bvNone
        TabOrder = 1
        DesignSize = (
          97
          202)
        object Label1: TLabel
          Left = 51
          Top = 0
          Width = 37
          Height = 16
          Caption = #1056#1072#1079#1084#1072#1093
        end
        object Label2: TLabel
          Left = 8
          Top = 0
          Width = 32
          Height = 16
          Caption = #1062#1077#1085#1090#1088
        end
        object LevelAmpScrollBar: TScrollBar
          Left = 51
          Top = 24
          Width = 37
          Height = 173
          Anchors = [akTop, akBottom]
          Kind = sbVertical
          Max = 200
          PageSize = 0
          TabOrder = 0
          OnChange = LevelAmpScrollBarChange
        end
        object LevelCenterScrollBar: TScrollBar
          Left = 8
          Top = 24
          Width = 37
          Height = 173
          Anchors = [akTop, akBottom]
          Kind = sbVertical
          Min = -100
          PageSize = 0
          TabOrder = 1
          OnChange = LevelCenterScrollBarChange
        end
      end
    end
    object ChartPanel: TPanel
      Left = 108
      Top = 8
      Width = 690
      Height = 238
      Anchors = [akLeft, akTop, akRight, akBottom]
      BevelOuter = bvLowered
      TabOrder = 1
      object Chart1: TChart
        Left = 1
        Top = 22
        Width = 688
        Height = 215
        AllowPanning = pmNone
        AllowZoom = False
        BackWall.Brush.Color = clWhite
        Foot.AdjustFrame = False
        Foot.Text.Strings = (
          'fvfdvfdvd')
        Foot.Visible = False
        Gradient.EndColor = 10485760
        Gradient.StartColor = 4194304
        Gradient.Visible = True
        LeftWall.Size = 13
        MarginBottom = 2
        MarginLeft = 2
        MarginRight = 2
        MarginTop = 2
        Title.AdjustFrame = False
        Title.Brush.Color = clWhite
        Title.Brush.Style = bsClear
        Title.Color = clGray
        Title.Font.Charset = RUSSIAN_CHARSET
        Title.Font.Color = clWhite
        Title.Font.Height = -11
        Title.Font.Name = 'Arial'
        Title.Font.Style = []
        Title.Text.Strings = (
          'noname')
        Title.Visible = False
        BottomAxis.Automatic = False
        BottomAxis.AutomaticMaximum = False
        BottomAxis.AutomaticMinimum = False
        BottomAxis.Axis.Width = 1
        BottomAxis.AxisValuesFormat = ' # ###,##0'
        BottomAxis.ExactDateTime = False
        BottomAxis.Increment = 10
        BottomAxis.LabelsAngle = 90
        BottomAxis.LabelsFont.Charset = RUSSIAN_CHARSET
        BottomAxis.LabelsFont.Color = clAqua
        BottomAxis.LabelsFont.Height = -11
        BottomAxis.LabelsFont.Name = 'Arial'
        BottomAxis.LabelsFont.Style = [fsBold]
        BottomAxis.LabelsSize = 49
        BottomAxis.LabelStyle = talValue
        BottomAxis.Maximum = 100000
        BottomAxis.Minimum = 50000
        BottomAxis.MinorTickCount = 4
        BottomAxis.MinorTickLength = 3
        BottomAxis.TickLength = 6
        BottomAxis.TicksInner.Visible = False
        BottomAxis.Title.Font.Charset = DEFAULT_CHARSET
        BottomAxis.Title.Font.Color = clAqua
        BottomAxis.Title.Font.Height = -13
        BottomAxis.Title.Font.Name = 'Arial'
        BottomAxis.Title.Font.Style = [fsBold]
        LeftAxis.Automatic = False
        LeftAxis.AutomaticMaximum = False
        LeftAxis.AutomaticMinimum = False
        LeftAxis.Axis.Width = 1
        LeftAxis.AxisValuesFormat = '#0.#'
        LeftAxis.ExactDateTime = False
        LeftAxis.Increment = 1
        LeftAxis.LabelsFont.Charset = DEFAULT_CHARSET
        LeftAxis.LabelsFont.Color = clRed
        LeftAxis.LabelsFont.Height = -11
        LeftAxis.LabelsFont.Name = 'Arial'
        LeftAxis.LabelsFont.Style = [fsBold]
        LeftAxis.LabelsSeparation = 20
        LeftAxis.LabelsSize = 16
        LeftAxis.LabelStyle = talValue
        LeftAxis.Maximum = 100
        LeftAxis.Minimum = -100
        LeftAxis.MinorTickCount = 4
        LeftAxis.MinorTickLength = 3
        LeftAxis.TickLength = 6
        LeftAxis.TicksInner.Visible = False
        LeftAxis.Title.Angle = 0
        LeftAxis.Title.Font.Charset = RUSSIAN_CHARSET
        LeftAxis.Title.Font.Color = clRed
        LeftAxis.Title.Font.Height = -13
        LeftAxis.Title.Font.Name = 'Arial'
        LeftAxis.Title.Font.Style = [fsBold]
        LeftAxis.TitleSize = 14
        Legend.Visible = False
        RightAxis.Automatic = False
        RightAxis.AutomaticMaximum = False
        RightAxis.AutomaticMinimum = False
        RightAxis.ExactDateTime = False
        RightAxis.Increment = 10
        RightAxis.Labels = False
        RightAxis.LabelsOnAxis = False
        RightAxis.LabelsSize = 6
        RightAxis.Maximum = 96
        RightAxis.RoundFirstLabel = False
        RightAxis.Visible = False
        TopAxis.Automatic = False
        TopAxis.AutomaticMaximum = False
        TopAxis.AutomaticMinimum = False
        TopAxis.ExactDateTime = False
        TopAxis.Increment = 10
        TopAxis.LabelsOnAxis = False
        TopAxis.RoundFirstLabel = False
        TopAxis.TickOnLabelsOnly = False
        TopAxis.Title.Caption = 'yjyuyuy'
        TopAxis.Visible = False
        View3D = False
        View3DWalls = False
        Align = alClient
        BevelOuter = bvNone
        Color = clSkyBlue
        PopupMenu = ChartPopupMenu
        TabOrder = 0
        OnResize = Chart1Resize
        DesignSize = (
          688
          215)
        object DBLabel: TLabel
          Left = 8
          Top = 162
          Width = 13
          Height = 13
          Anchors = [akLeft, akBottom]
          Caption = #1076#1041
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clRed
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ParentFont = False
          Transparent = True
        end
        object FreqLabel: TLabel
          Left = 4
          Top = 176
          Width = 18
          Height = 13
          Anchors = [akLeft, akBottom]
          Caption = #1082#1043#1094
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clAqua
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ParentFont = False
          Transparent = True
        end
        object MainSeries1: TLineSeries
          Marks.Arrow.Visible = False
          Marks.ArrowLength = 32
          Marks.Font.Charset = RUSSIAN_CHARSET
          Marks.Font.Color = clYellow
          Marks.Font.Height = -13
          Marks.Font.Name = 'Arial Narrow'
          Marks.Font.Style = []
          Marks.Frame.Visible = False
          Marks.Transparent = True
          Marks.Visible = False
          SeriesColor = clYellow
          ShowInLegend = False
          Title = 'MainSeries1'
          Dark3D = False
          LinePen.Color = clRed
          LinePen.Width = 2
          Pointer.InflateMargins = True
          Pointer.Style = psRectangle
          Pointer.Visible = False
          XValues.DateTime = False
          XValues.Name = 'X'
          XValues.Multiplier = 1
          XValues.Order = loAscending
          YValues.DateTime = False
          YValues.Name = 'Y'
          YValues.Multiplier = 1
          YValues.Order = loNone
        end
        object PlanLineSeries: TLineSeries
          Marks.ArrowLength = 8
          Marks.Font.Charset = DEFAULT_CHARSET
          Marks.Font.Color = clLime
          Marks.Font.Height = -11
          Marks.Font.Name = 'Arial'
          Marks.Font.Style = []
          Marks.Visible = False
          SeriesColor = clRed
          ShowInLegend = False
          VertAxis = aRightAxis
          Pointer.InflateMargins = True
          Pointer.Style = psRectangle
          Pointer.Visible = False
          XValues.DateTime = False
          XValues.Name = 'X'
          XValues.Multiplier = 1
          XValues.Order = loAscending
          YValues.DateTime = False
          YValues.Name = 'Y'
          YValues.Multiplier = 1
          YValues.Order = loNone
        end
        object PlanTitleSeries: TLineSeries
          Marks.Arrow.Color = clSilver
          Marks.ArrowLength = 4
          Marks.Clip = True
          Marks.Font.Charset = DEFAULT_CHARSET
          Marks.Font.Color = clSilver
          Marks.Font.Height = -11
          Marks.Font.Name = 'Arial'
          Marks.Font.Style = []
          Marks.Frame.Visible = False
          Marks.Transparent = True
          Marks.Visible = True
          SeriesColor = clGreen
          ShowInLegend = False
          VertAxis = aRightAxis
          Dark3D = False
          LinePen.Visible = False
          Pointer.InflateMargins = True
          Pointer.Style = psCircle
          Pointer.Visible = True
          XValues.DateTime = False
          XValues.Name = 'X'
          XValues.Multiplier = 1
          XValues.Order = loAscending
          YValues.DateTime = False
          YValues.Name = 'Y'
          YValues.Multiplier = 1
          YValues.Order = loNone
        end
        object ShadowSeries: TAreaSeries
          Marks.ArrowLength = 8
          Marks.Visible = False
          SeriesColor = 8404992
          ShowInLegend = False
          AreaLinesPen.Style = psDash
          AreaLinesPen.Visible = False
          DrawArea = True
          LinePen.Visible = False
          Pointer.InflateMargins = True
          Pointer.Style = psRectangle
          Pointer.Visible = False
          XValues.DateTime = False
          XValues.Name = 'X'
          XValues.Multiplier = 1
          XValues.Order = loAscending
          YValues.DateTime = False
          YValues.Name = 'Y'
          YValues.Multiplier = 1
          YValues.Order = loNone
        end
      end
      object InfoPanel: TPanel
        Left = 1
        Top = 1
        Width = 688
        Height = 21
        Align = alTop
        BevelOuter = bvNone
        TabOrder = 1
        object SignalInfoLabel: TLabel
          Left = 0
          Top = 0
          Width = 688
          Height = 21
          Align = alClient
          Alignment = taRightJustify
          Color = clNavy
          ParentColor = False
        end
      end
    end
    object FreqGroupBox: TGroupBox
      Left = 109
      Top = 246
      Width = 689
      Height = 81
      Anchors = [akLeft, akRight, akBottom]
      Caption = ' '#1063#1072#1089#1090#1086#1090#1072' '
      TabOrder = 2
      object FreqSpanPanel: TPanel
        Left = 8
        Top = 13
        Width = 256
        Height = 64
        BevelOuter = bvNone
        TabOrder = 0
        DesignSize = (
          256
          64)
        object Label9: TLabel
          Left = 4
          Top = 5
          Width = 55
          Height = 16
          Caption = #1062#1077#1085#1090#1088', '#1082#1043#1094
        end
        object Label10: TLabel
          Left = 4
          Top = 35
          Width = 71
          Height = 16
          Caption = #1044#1080#1072#1087#1072#1079#1086#1085', '#1082#1043#1094
        end
        object CentralFreqEdit: TEdit
          Left = 80
          Top = 0
          Width = 64
          Height = 28
          AutoSize = False
          Font.Charset = RUSSIAN_CHARSET
          Font.Color = clWindowText
          Font.Height = -16
          Font.Name = 'Arial Narrow'
          Font.Style = []
          MaxLength = 7
          ParentFont = False
          TabOrder = 0
          Text = '70000'
        end
        object SpanEdit: TEdit
          Left = 80
          Top = 32
          Width = 64
          Height = 28
          Font.Charset = RUSSIAN_CHARSET
          Font.Color = clWindowText
          Font.Height = -16
          Font.Name = 'Arial Narrow'
          Font.Style = []
          MaxLength = 7
          ParentFont = False
          TabOrder = 1
          Text = '70000'
        end
        object CentralScrollBar: TScrollBar
          Left = 146
          Top = 0
          Width = 104
          Height = 28
          Anchors = [akLeft, akTop, akRight]
          Max = 800000
          PageSize = 0
          Position = 72000
          TabOrder = 2
          OnChange = CentralScrollBarChange
        end
        object SpanScrollBar: TScrollBar
          Left = 146
          Top = 32
          Width = 104
          Height = 28
          Anchors = [akLeft, akTop, akRight]
          Max = 800000
          PageSize = 0
          Position = 4000
          TabOrder = 3
          OnChange = SpanScrollBarChange
        end
      end
      object FreqInterPanel: TPanel
        Left = 272
        Top = 13
        Width = 256
        Height = 64
        BevelOuter = bvNone
        TabOrder = 1
        Visible = False
        DesignSize = (
          256
          64)
        object Label6: TLabel
          Left = 4
          Top = 5
          Width = 54
          Height = 16
          Caption = #1051#1077#1074#1072#1103', '#1082#1043#1094
        end
        object Label7: TLabel
          Left = 4
          Top = 35
          Width = 61
          Height = 16
          Caption = #1055#1088#1072#1074#1072#1103', '#1082#1043#1094
        end
        object LeftFreqEdit: TEdit
          Left = 80
          Top = 0
          Width = 64
          Height = 28
          Font.Charset = RUSSIAN_CHARSET
          Font.Color = clWindowText
          Font.Height = -16
          Font.Name = 'Arial Narrow'
          Font.Style = []
          MaxLength = 7
          ParentFont = False
          TabOrder = 0
          Text = '70000'
        end
        object RightFreqEdit: TEdit
          Left = 80
          Top = 32
          Width = 64
          Height = 28
          Font.Charset = RUSSIAN_CHARSET
          Font.Color = clWindowText
          Font.Height = -16
          Font.Name = 'Arial Narrow'
          Font.Style = []
          MaxLength = 7
          ParentFont = False
          TabOrder = 1
          Text = '70000'
        end
        object LeftScrollBar: TScrollBar
          Left = 146
          Top = 0
          Width = 104
          Height = 28
          Anchors = [akLeft, akTop, akRight]
          Max = 800000
          PageSize = 0
          Position = 72000
          TabOrder = 2
          OnChange = LeftScrollBarChange
        end
        object RightScrollBar: TScrollBar
          Left = 146
          Top = 32
          Width = 104
          Height = 28
          Anchors = [akLeft, akTop, akRight]
          Max = 800000
          PageSize = 0
          Position = 72000
          TabOrder = 3
          OnChange = RightScrollBarChange
        end
      end
    end
    object ButtonsPanel: TPanel
      Left = 5
      Top = 252
      Width = 99
      Height = 72
      Anchors = [akLeft, akBottom]
      BevelOuter = bvNone
      TabOrder = 3
      DesignSize = (
        99
        72)
      object SettsButton: TSpeedButton
        Left = 6
        Top = 7
        Width = 87
        Height = 26
        AllowAllUp = True
        Anchors = [akLeft, akBottom]
        GroupIndex = 1
        Caption = #1053#1072#1089#1090#1088#1086#1081#1082#1080
        OnClick = SettsButtonClick
      end
      object CtrlButton: TSpeedButton
        Left = 7
        Top = 39
        Width = 87
        Height = 26
        AllowAllUp = True
        Anchors = [akLeft, akBottom]
        GroupIndex = 1
        Caption = #1059#1087#1088#1072#1074#1083#1077#1085#1080#1077
        OnClick = CtrlButtonClick
      end
    end
  end
  object SettsPageControl: TPageControl
    Left = 0
    Top = 529
    Width = 804
    Height = 197
    ActivePage = TabSheet5
    Align = alBottom
    TabIndex = 2
    TabOrder = 1
    OnChanging = SettsPageControlChanging
    object PlanTabSheet: TTabSheet
      Caption = #1055#1083#1072#1085
      ImageIndex = 7
      object PageControl2: TPageControl
        Left = 0
        Top = 0
        Width = 796
        Height = 166
        ActivePage = TabSheet7
        Align = alClient
        MultiLine = True
        TabIndex = 0
        TabOrder = 0
        TabPosition = tpLeft
        object TabSheet7: TTabSheet
          Caption = #1057#1087#1080#1089#1086#1082
          object PlanListBox: TListBox
            Left = 0
            Top = 0
            Width = 137
            Height = 158
            Align = alLeft
            ItemHeight = 16
            PopupMenu = FreqPlanPopupMenu
            TabOrder = 0
            OnClick = PlanListBoxClick
          end
          object FreqPlanNameEdit: TStaticText
            Left = 144
            Top = 0
            Width = 459
            Height = 20
            AutoSize = False
            BorderStyle = sbsSunken
            TabOrder = 1
          end
          inline FreqParamFrame1: TFreqParamFrame
            Left = 144
            Top = 21
            Width = 459
            Height = 136
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'MS Sans Serif'
            Font.Style = []
            ParentFont = False
            TabOrder = 2
            inherited PlanParamsPanel: TPanel
              Width = 459
              Height = 136
            end
          end
        end
        object TabSheet8: TTabSheet
          Caption = #1054#1090#1086#1073#1088#1072#1078#1077#1085#1080#1077
          ImageIndex = 1
          object Label11: TLabel
            Left = 8
            Top = 8
            Width = 79
            Height = 16
            Caption = #1058#1086#1083#1097#1080#1085#1072' '#1083#1080#1085#1080#1080
          end
          object Label12: TLabel
            Left = 8
            Top = 32
            Width = 59
            Height = 16
            Caption = #1062#1074#1077#1090' '#1083#1080#1085#1080#1080
          end
          object Label22: TLabel
            Left = 8
            Top = 56
            Width = 70
            Height = 16
            Caption = #1062#1074#1077#1090' '#1085#1072#1076#1087#1080#1089#1080
          end
          object CheckBox1: TCheckBox
            Left = 304
            Top = 8
            Width = 217
            Height = 17
            Caption = #1042' '#1086#1090#1076#1077#1083#1100#1085#1086#1084' '#1075#1088#1072#1092#1080#1082#1077
            TabOrder = 0
            Visible = False
          end
          object FreqPlanLineWidthComboBox: TComboBox
            Left = 104
            Top = 4
            Width = 41
            Height = 24
            ItemHeight = 16
            ItemIndex = 0
            TabOrder = 1
            Text = '1'
            OnChange = FreqPlanLineWidthComboBoxChange
            Items.Strings = (
              '1'
              '2'
              '3'
              '4'
              '5'
              '6'
              '7'
              '8'
              '9')
          end
          object FreqPlanLineColorBox: TColorBox
            Left = 104
            Top = 29
            Width = 105
            Height = 22
            Selected = clSkyBlue
            ItemHeight = 16
            TabOrder = 2
            OnChange = FreqPlanLineColorBoxChange
          end
          object FreqPlanNameColorBox: TColorBox
            Left = 104
            Top = 53
            Width = 105
            Height = 22
            Selected = clSkyBlue
            ItemHeight = 16
            TabOrder = 3
            OnChange = FreqPlanNameColorBoxChange
          end
        end
      end
    end
    object TabSheet1: TTabSheet
      Caption = #1044#1080#1072#1087#1072#1079#1086#1085
      TabVisible = False
      object BandsRadioGroup: TRadioGroup
        Left = 8
        Top = 0
        Width = 145
        Height = 161
        ItemIndex = 0
        Items.Strings = (
          '70 '#1052#1043#1094
          '140 '#1052#1043#1094
          'L-'#1076#1080#1072#1087#1072#1079#1086#1085
          'C-'#1076#1080#1072#1087#1072#1079#1086#1085' '#1074#1074#1077#1088#1093
          'C-'#1076#1080#1072#1087#1072#1079#1086#1085' '#1074#1085#1080#1079
          '  '#1044#1088#1091#1075#1086#1077)
        TabOrder = 0
        OnClick = BandsRadioGroupClick
      end
      object BandPanel: TPanel
        Left = 160
        Top = 6
        Width = 225
        Height = 155
        TabOrder = 1
        object Label13: TLabel
          Left = 16
          Top = 26
          Width = 61
          Height = 16
          Caption = #1053#1072#1095#1072#1083#1086', '#1082#1043#1094
        end
        object Label14: TLabel
          Left = 16
          Top = 58
          Width = 53
          Height = 16
          Caption = #1050#1086#1085#1077#1094', '#1082#1043#1094
        end
        object UserMinFreqEdit: TEdit
          Left = 136
          Top = 20
          Width = 69
          Height = 24
          TabOrder = 0
          OnChange = UserMinFreqEditChange
        end
        object UserMaxFreqEdit: TEdit
          Left = 136
          Top = 52
          Width = 69
          Height = 24
          TabOrder = 1
          OnChange = UserMinFreqEditChange
        end
      end
      object BandEditButton: TButton
        Left = 176
        Top = 120
        Width = 97
        Height = 25
        Caption = #1048#1079#1084#1077#1085#1080#1090#1100
        TabOrder = 2
        OnClick = BandEditButtonClick
      end
      object BandCancelButton: TButton
        Left = 300
        Top = 120
        Width = 75
        Height = 25
        Caption = #1054#1090#1084#1077#1085#1080#1090#1100
        Enabled = False
        TabOrder = 3
        OnClick = BandCancelButtonClick
      end
    end
    object TabSheet2: TTabSheet
      Caption = #1063#1072#1089#1090#1086#1090#1072
      ImageIndex = 1
      object Label19: TLabel
        Left = 18
        Top = 48
        Width = 99
        Height = 16
        Caption = #1064#1072#1075' '#1091#1089#1090#1072#1085#1086#1074#1082#1080', '#1082#1043#1094
      end
      object Label29: TLabel
        Left = 16
        Top = 16
        Width = 92
        Height = 16
        Caption = #1057#1087#1086#1089#1086#1073' '#1091#1089#1090#1072#1085#1086#1074#1082#1080
      end
      object RatioComboBox: TComboBox
        Left = 153
        Top = 43
        Width = 44
        Height = 24
        ItemHeight = 16
        ItemIndex = 1
        TabOrder = 0
        Text = '10'
        OnChange = RatioComboBoxChange
        Items.Strings = (
          '1'
          '10'
          '100'
          '1000')
      end
      object FreqSetComboBox: TComboBox
        Left = 152
        Top = 14
        Width = 225
        Height = 24
        Style = csDropDownList
        ItemHeight = 16
        ItemIndex = 0
        TabOrder = 1
        Text = #1055#1088#1086#1084#1077#1078#1091#1090#1082#1086#1084' '#1084#1077#1078#1076#1091' '#1076#1074#1091#1084#1103' '#1090#1086#1095#1082#1072#1084#1080
        OnChange = FreqSetComboBoxChange
        Items.Strings = (
          #1055#1088#1086#1084#1077#1078#1091#1090#1082#1086#1084' '#1084#1077#1078#1076#1091' '#1076#1074#1091#1084#1103' '#1090#1086#1095#1082#1072#1084#1080
          #1054#1090#1082#1083#1086#1085#1077#1085#1080#1077#1084' '#1086#1090' '#1094#1077#1085#1090#1088#1072#1083#1100#1085#1086#1081)
      end
    end
    object TabSheet5: TTabSheet
      Caption = #1051#1091#1095
      ImageIndex = 4
      object Label3: TLabel
        Left = 9
        Top = 16
        Width = 74
        Height = 16
        Caption = #1064#1080#1088#1080#1085#1072' '#1083#1080#1085#1080#1081
      end
      object Label8: TLabel
        Left = 8
        Top = 51
        Width = 96
        Height = 16
        Caption = #1054#1090#1086#1073#1088#1072#1078#1072#1090#1100' '#1083#1091#1095#1077#1081
      end
      object Image1: TImage
        Left = 480
        Top = 0
        Width = 145
        Height = 161
        Visible = False
      end
      object BeamWidthComboBox: TComboBox
        Left = 136
        Top = 12
        Width = 41
        Height = 24
        ItemHeight = 16
        ItemIndex = 0
        TabOrder = 0
        Text = '1'
        OnChange = BeamWidthComboBoxChange
        Items.Strings = (
          '1'
          '2'
          '3'
          '4'
          '5'
          '6'
          '7'
          '8'
          '9')
      end
      object BeamFadingEdit: TEdit
        Left = 136
        Top = 48
        Width = 33
        Height = 24
        ReadOnly = True
        TabOrder = 1
        Text = '1'
        OnChange = BeamFadingEditChange
      end
      object BeamFadingUpDown: TUpDown
        Left = 169
        Top = 48
        Width = 24
        Height = 24
        Associate = BeamFadingEdit
        Min = 1
        Max = 16
        Position = 1
        TabOrder = 2
        Wrap = False
      end
      object BeamCheckBox: TCheckBox
        Left = 6
        Top = 84
        Width = 143
        Height = 17
        Alignment = taLeftJustify
        Caption = #1069#1092#1092#1077#1082#1090' '#1086#1076#1085#1086#1075#1086' '#1083#1091#1095#1072
        TabOrder = 3
      end
      object BeamShadowCheckBox: TCheckBox
        Left = 8
        Top = 112
        Width = 141
        Height = 17
        Alignment = taLeftJustify
        Caption = #1047#1072#1090#1077#1084#1085#1077#1085#1080#1077
        TabOrder = 4
        OnClick = BeamShadowCheckBoxClick
      end
      object BeamColorsGroupBox: TGroupBox
        Left = 216
        Top = -3
        Width = 249
        Height = 72
        Caption = ' '#1062#1074#1077#1090'  '
        TabOrder = 5
        object Label17: TLabel
          Left = 10
          Top = 22
          Width = 26
          Height = 16
          Caption = #1062#1074#1077#1090
        end
        object BeamColorCheckBox: TCheckBox
          Left = 8
          Top = 46
          Width = 233
          Height = 17
          Alignment = taLeftJustify
          Caption = #1048#1085#1074#1077#1088#1089#1085#1086' '#1082' '#1092#1086#1085#1091
          TabOrder = 0
          OnClick = BeamColorRadioGroupClick
        end
        object BeamColorComboBox: TComboBox
          Left = 136
          Top = 20
          Width = 105
          Height = 24
          ItemHeight = 16
          ItemIndex = 0
          TabOrder = 1
          Text = #1041#1077#1083#1099#1081
          OnClick = BeamColorRadioGroupClick
          Items.Strings = (
            #1041#1077#1083#1099#1081
            #1057#1074#1077#1090#1083#1099#1081
            #1050#1088#1072#1089#1085#1099#1081
            #1046#1077#1083#1090#1099#1081
            #1047#1077#1083#1077#1085#1099#1081
            #1043#1086#1083#1091#1073#1086#1081
            #1058#1077#1084#1085#1099#1081
            #1063#1077#1088#1085#1099#1081)
        end
      end
      object BeamRefreshCheckBox: TCheckBox
        Left = 216
        Top = 80
        Width = 241
        Height = 17
        Alignment = taLeftJustify
        Caption = #1056#1080#1089#1086#1074#1072#1090#1100' '#1090#1086#1083#1100#1082#1086' '#1087#1088#1080' '#1086#1073#1085#1086#1074#1083#1077#1085#1080#1080' '#1076#1072#1085#1085#1099#1093
        TabOrder = 6
      end
    end
    object TabSheet6: TTabSheet
      Caption = #1062#1074#1077#1090#1072
      ImageIndex = 6
      object FonGroupBox: TGroupBox
        Left = 0
        Top = -3
        Width = 209
        Height = 73
        Caption = ' '#1060#1086#1085' '
        TabOrder = 0
        object Label16: TLabel
          Left = 10
          Top = 22
          Width = 26
          Height = 16
          Caption = #1062#1074#1077#1090
        end
        object FonColorComboBox: TComboBox
          Left = 96
          Top = 20
          Width = 105
          Height = 24
          ItemHeight = 16
          ItemIndex = 0
          TabOrder = 0
          Text = #1063#1105#1088#1085#1099#1081
          OnClick = FonRadioGroupClick
          Items.Strings = (
            #1063#1105#1088#1085#1099#1081
            #1057#1077#1088#1099#1081
            #1050#1088#1072#1089#1085#1099#1081
            #1057#1080#1085#1080#1081
            #1047#1077#1083#1105#1085#1099#1081
            #1041#1077#1083#1099#1081
            #1057#1077#1088#1086#1074#1072#1090#1099#1081
            #1056#1086#1079#1086#1074#1072#1090#1099#1081
            #1043#1086#1083#1091#1073#1086#1074#1072#1090#1099#1081
            #1047#1077#1083#1077#1085#1086#1074#1072#1090#1099#1081)
        end
        object FonGradientCheckBox: TCheckBox
          Left = 8
          Top = 46
          Width = 193
          Height = 17
          Alignment = taLeftJustify
          Caption = #1057' '#1087#1077#1088#1077#1093#1086#1076#1086#1084' '#1082' '#1090#1077#1084#1085#1086#1084#1091'/'#1089#1074#1077#1090#1083#1086#1084#1091
          Checked = True
          State = cbChecked
          TabOrder = 1
          OnClick = FonRadioGroupClick
        end
      end
      object LegendGroupBox: TGroupBox
        Left = 0
        Top = 69
        Width = 209
        Height = 92
        Caption = ' '#1053#1072#1076#1087#1080#1089#1100' '
        TabOrder = 1
        object Label20: TLabel
          Left = 10
          Top = 19
          Width = 51
          Height = 16
          Caption = #1062#1074#1077#1090' '#1087#1086' X'
        end
        object Label21: TLabel
          Left = 10
          Top = 46
          Width = 51
          Height = 16
          Caption = #1062#1074#1077#1090' '#1087#1086' Y'
        end
        object LegendYColorBox: TColorBox
          Left = 104
          Top = 44
          Width = 97
          Height = 22
          Selected = clSilver
          ItemHeight = 16
          TabOrder = 0
          OnClick = LegendColorCheckBoxClick
        end
        object LegendXColorBox: TColorBox
          Left = 104
          Top = 16
          Width = 97
          Height = 22
          DefaultColorColor = clSilver
          Selected = clSilver
          ItemHeight = 16
          TabOrder = 1
          OnClick = LegendColorCheckBoxClick
        end
        object LegendColorCheckBox: TCheckBox
          Left = 8
          Top = 68
          Width = 193
          Height = 17
          Alignment = taLeftJustify
          Caption = #1042#1089#1090#1088#1086#1077#1085#1085#1099#1077
          Checked = True
          State = cbChecked
          TabOrder = 2
          OnClick = LegendColorCheckBoxClick
        end
      end
      object GridGroupBox: TGroupBox
        Left = 216
        Top = -3
        Width = 209
        Height = 164
        Caption = ' '#1057#1077#1090#1082#1072' '
        TabOrder = 2
        object Label18: TLabel
          Left = 10
          Top = 22
          Width = 26
          Height = 16
          Caption = #1062#1074#1077#1090
        end
        object GridColorComboBox: TComboBox
          Left = 96
          Top = 20
          Width = 105
          Height = 24
          ItemHeight = 16
          ItemIndex = 6
          TabOrder = 0
          Text = #1057#1077#1088#1086#1074#1072#1090#1099#1081
          OnChange = GridColorAdaptCheckBoxClick
          Items.Strings = (
            #1063#1105#1088#1085#1099#1081
            #1057#1077#1088#1099#1081
            #1050#1088#1072#1089#1085#1099#1081
            #1057#1080#1085#1080#1081
            #1047#1077#1083#1105#1085#1099#1081
            #1041#1077#1083#1099#1081
            #1057#1077#1088#1086#1074#1072#1090#1099#1081
            #1056#1086#1079#1086#1074#1072#1090#1099#1081
            #1043#1086#1083#1091#1073#1086#1074#1072#1090#1099#1081
            #1047#1077#1083#1077#1085#1086#1074#1072#1090#1099#1081)
        end
        object GridColorAdaptCheckBox: TCheckBox
          Left = 8
          Top = 54
          Width = 193
          Height = 17
          Alignment = taLeftJustify
          Caption = #1040#1076#1072#1087#1090#1080#1088#1086#1074#1072#1090#1100' '#1082' '#1092#1086#1085#1091
          Checked = True
          State = cbChecked
          TabOrder = 1
          OnClick = GridColorAdaptCheckBoxClick
        end
        object GridColorNoCheckBox: TCheckBox
          Left = 8
          Top = 76
          Width = 193
          Height = 17
          Alignment = taLeftJustify
          Caption = #1053#1077' '#1088#1080#1089#1086#1074#1072#1090#1100
          Checked = True
          State = cbChecked
          TabOrder = 2
          OnClick = GridColorNoCheckBoxClick
        end
        object GridColorSplashCheckBox: TCheckBox
          Left = 8
          Top = 100
          Width = 193
          Height = 17
          Alignment = taLeftJustify
          Caption = #1057#1087#1083#1086#1096#1085#1099#1077' '#1083#1080#1085#1080#1080
          Checked = True
          State = cbChecked
          TabOrder = 3
          OnClick = GridColorSplashCheckBoxClick
        end
      end
    end
    object AboutTabSheet: TTabSheet
      Caption = #1054' '#1087#1088#1086#1075#1088#1072#1084#1084#1077
      ImageIndex = 7
      object ScrollBox1: TScrollBox
        Left = 0
        Top = 0
        Width = 796
        Height = 166
        Align = alClient
        BevelOuter = bvNone
        BevelKind = bkSoft
        TabOrder = 0
        object ProgramIcon: TImage
          Left = 8
          Top = 72
          Width = 64
          Height = 64
          Picture.Data = {
            07544269746D6170362C0100424D362C0100000000003600000028000000A000
            0000A00000000100180000000000002C0100C40E0000C40E0000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000C0C0C0
            C0C0C0C0C0C00000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C00000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C00000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C00000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C00000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C00000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C00000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C00000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C00000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C00000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C00000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C00000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C00000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0
            C0C0000000000000000000C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0
            C0C0000000000000000000C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0
            C0C0000000000000000000C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0
            C0C0000000000000000000000000C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0
            C0C0000000000000000000000000000000000000000000000000C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C00000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C00000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C00000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C00000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C00000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C00000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C00000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C00000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C00000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C00000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C00000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C00000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C00000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C00000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C00000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C00000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C00000000000000000000000000000000000000000000000
            0000000000000000000000000000000000FF0000FF0000FF0000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            000000FF0000FF0000FF00000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            00000000000000000000000000FF0000FF0000FF000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C00000000000000000000000000000000000000000000000
            0000000000000000000000000000000000FF0000FF0000FF0000FF0000FF0000
            FF00000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            FF0000FF0000FF0000FF0000FF0000FF0000FF00000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            00000000000000000000FF0000FF0000FF0000FF0000FF0000FF0000FF000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C00000000000000000000000000000000000000000000000
            0000000000000000000000000000000000FF0000FF0000FF0000FF0000FF0000
            FF0000FF0000FF0000FF00000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF00000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            00000000000000000000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF
            0000FF0000FF0000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C00000000000000000000000000000000000000000000000
            0000000000000000000000000000000000FF0000FF0000FF0000FF0000FF0000
            FF0000FF0000FF0000FF0000FF00000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF00
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            00000000000000000000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF
            0000FF0000FF0000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C00000000000000000000000000000000000000000000000
            0000000000000000000000000000000000FF0000FF0000FF0000FF0000FF0000
            FF0000FF0000FF0000FF0000FF00000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF00
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            00000000000000000000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF
            0000FF0000FF0000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C00000000000000000000000000000000000000000000000
            0000000000000000000000000000000000FF0000FF0000FF0000FF0000FF0000
            FF0000FF0000FF0000FF0000FF00000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF00
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            00000000000000000000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF
            0000FF0000FF0000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C00000000000000000000000000000000000000000000000
            0000000000000000000000000000000000FF0000FF0000FF0000FF0000FF0000
            FF0000FF0000FF0000FF0000FF00000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF00
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            00000000000000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF
            0000FF0000FF0000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C00000000000000000000000000000000000000000000000
            0000000000000000000000000000000000FF0000FF0000FF0000FF0000FF0000
            FF0000FF0000FF0000FF0000FF00000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000FF0000
            FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF00
            00FF000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            00000000000000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF
            0000FF0000FF0000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C00000000000000000000000000000000000000000000000
            0000000000000000000000000000000000FF0000FF0000FF0000FF0000FF0000
            FF0000FF0000FF0000FF0000FF00000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000FF0000
            FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF00
            00FF000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            00000000000000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF
            0000FF0000FF0000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C00000000000000000000000000000000000000000000000
            0000000000000000000000000000000000FF0000FF0000FF0000FF0000FF0000
            FF0000FF0000FF0000FF0000FF00000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000FF0000
            FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF00
            00FF000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            00000000000000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF
            0000FF0000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C00000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000FF0000FF0000FF0000FF0000
            FF0000FF0000FF0000FF0000FF00000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000FF0000
            FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF00
            00FF000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            00000000000000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF
            0000FF0000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C00000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000FF0000FF0000FF0000FF0000
            FF0000FF0000FF0000FF0000FF0000FF00000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000FF0000
            FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF00
            00FF0000FF000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            00000000000000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF
            0000FF0000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C00000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000FF0000FF0000FF0000FF0000
            FF0000FF0000FF0000FF0000FF0000FF00000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000FF0000
            FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF00
            00FF0000FF000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            00000000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF
            0000FF0000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C00000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000FF0000FF0000FF0000FF0000
            FF0000FF0000FF0000FF0000FF0000FF00000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000FF0000
            FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF00
            00FF0000FF000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            00000000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF
            0000FF0000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C00000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000FF0000FF0000FF0000FF0000
            FF0000FF0000FF0000FF0000FF0000FF00000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000FF0000FF0000
            FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF00
            00FF0000FF000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            00000000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF
            0000FF0000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C00000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000FF0000FF0000FF0000FF0000
            FF0000FF0000FF0000FF0000FF0000FF00000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000FF0000FF0000
            FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF00
            00FF0000FF0000FF000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            00000000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C00000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000FF0000FF0000FF0000FF0000
            FF0000FF0000FF0000FF0000FF0000FF00000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000FF0000FF0000
            FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF00
            00FF0000FF0000FF000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            00000000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C00000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000FF0000FF0000FF0000FF0000
            FF0000FF0000FF0000FF0000FF0000FF00000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000FF0000FF0000
            FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF00
            00FF0000FF0000FF000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            00FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C00000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000FF0000FF0000FF0000
            FF0000FF0000FF0000FF0000FF0000FF00000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000FF0000FF0000
            FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF00
            00FF0000FF0000FF0000FF000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            00FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C00000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000FF0000FF0000FF0000
            FF0000FF0000FF0000FF0000FF0000FF0000FF00000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000FF0000FF0000
            FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF00
            00FF0000FF0000FF0000FF000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            00FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C00000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000FF0000FF0000FF0000
            FF0000FF0000FF0000FF0000FF0000FF0000FF00000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000FF0000FF0000FF0000
            FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF00
            00FF0000FF0000FF0000FF000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            00FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C00000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000FF0000FF0000FF0000
            FF0000FF0000FF0000FF0000FF0000FF0000FF00000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000FF0000FF0000FF0000
            FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF00
            00FF0000FF0000FF0000FF000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            00FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C00000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000FF0000FF0000FF0000
            FF0000FF0000FF0000FF0000FF0000FF0000FF00000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000FF0000FF0000FF0000
            FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF00
            00FF0000FF0000FF0000FF0000FF000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            000000000000000000000000000000000000000000000000000000000000FF00
            00FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C00000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000FF0000FF0000FF0000
            FF0000FF0000FF0000FF0000FF0000FF0000FF00000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000FF0000FF0000FF0000
            FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF00
            00FF0000FF0000FF0000FF0000FF000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            000000000000000000000000000000000000000000000000000000000000FF00
            00FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C00000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000FF0000FF0000FF0000
            FF0000FF0000FF0000FF0000FF0000FF0000FF00000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000FF0000FF0000FF0000
            FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF00
            00FF0000FF0000FF0000FF0000FF000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            000000000000000000000000000000000000000000000000000000000000FF00
            00FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C00000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000FF0000FF0000FF0000
            FF0000FF0000FF0000FF0000FF0000FF0000FF00000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000FF0000FF0000FF0000
            FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF00
            00FF0000FF0000FF0000FF0000FF000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            000000000000000000000000000000000000000000000000000000000000FF00
            00FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C00000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000FF0000FF0000
            FF0000FF0000FF0000FF0000FF0000FF0000FF00000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000FF0000FF0000FF0000FF0000
            FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF00
            00FF0000FF0000FF0000FF0000FF0000FF000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            000000000000000000000000000000000000000000000000000000000000FF00
            00FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C00000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000FF0000FF0000
            FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF00000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000FF0000FF0000FF0000FF0000
            FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF00
            00FF0000FF0000FF0000FF0000FF0000FF000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            000000000000000000000000000000000000000000000000000000FF0000FF00
            00FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C00000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000FF0000FF0000
            FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF00000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000FF0000FF0000FF0000FF0000
            FF0000FF0000FF0000FF0000FF0000FF0000FF0000000000FF0000FF0000FF00
            00FF0000FF0000FF0000FF0000FF0000FF000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            000000000000000000000000000000000000000000000000000000FF0000FF00
            00FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C00000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000FF0000FF0000
            FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF00000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000FF0000FF0000FF0000FF0000
            FF0000FF0000FF0000FF0000FF0000FF0000000000000000FF0000FF0000FF00
            00FF0000FF0000FF0000FF0000FF0000FF0000FF000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            000000000000000000000000000000000000000000000000000000FF0000FF00
            00FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C00000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000FF0000FF0000
            FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF00000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000FF0000FF0000FF0000FF0000
            FF0000FF0000FF0000FF0000FF0000FF0000000000000000FF0000FF0000FF00
            00FF0000FF0000FF0000FF0000FF0000FF0000FF000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            000000000000000000000000000000000000000000000000000000FF0000FF00
            00FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C00000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000FF0000FF0000
            FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF00000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000FF0000FF0000FF0000FF0000
            FF0000FF0000FF0000FF0000FF0000FF0000000000000000000000FF0000FF00
            00FF0000FF0000FF0000FF0000FF0000FF0000FF000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            000000000000000000000000000000000000000000000000000000FF0000FF00
            00FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C00000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000FF0000FF0000
            FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF00000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000FF0000FF0000FF0000FF0000FF0000
            FF0000FF0000FF0000FF0000FF0000FF0000000000000000000000FF0000FF00
            00FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            000000000000000000000000000000000000000000000000FF0000FF0000FF00
            00FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C00000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000FF0000FF0000
            FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF00000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000FF0000FF0000FF0000FF0000FF0000
            FF0000FF0000FF0000FF0000FF0000FF0000000000000000000000FF0000FF00
            00FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            000000000000000000000000000000000000000000000000FF0000FF0000FF00
            00FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C00000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000FF0000
            FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF00000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000FF0000FF0000FF0000FF0000FF0000
            FF0000FF0000FF0000FF0000FF0000FF0000000000000000000000FF0000FF00
            00FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            000000000000000000000000000000000000000000000000FF0000FF0000FF00
            00FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C00000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000FF0000
            FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF00000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000FF0000FF0000FF0000FF0000FF0000
            FF0000FF0000FF0000FF0000FF0000000000000000000000000000000000FF00
            00FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            000000000000000000000000000000000000000000000000FF0000FF0000FF00
            00FF0000FF0000FF0000FF0000FF0000FF0000FF000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C00000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000FF0000
            FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF00000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000FF0000FF0000FF0000FF0000FF0000
            FF0000FF0000FF0000FF0000FF0000000000000000000000000000000000FF00
            00FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            000000000000000000000000000000000000000000000000FF0000FF0000FF00
            00FF0000FF0000FF0000FF0000FF0000FF0000FF000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C00000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000FF0000
            FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF00000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000FF0000FF0000FF0000FF0000FF0000
            FF0000FF0000FF0000FF0000FF0000000000000000000000000000000000FF00
            00FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            000000000000000000000000000000000000000000FF0000FF0000FF0000FF00
            00FF0000FF0000FF0000FF0000FF0000FF0000FF000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C00000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000FF0000
            FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF00000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000FF0000FF0000FF0000FF0000FF0000
            FF0000FF0000FF0000FF0000FF00000000000000000000000000000000000000
            00FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            000000000000000000000000000000000000000000FF0000FF0000FF0000FF00
            00FF0000FF0000FF0000FF0000FF0000FF0000FF000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C00000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000FF0000
            FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF00000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000FF0000FF0000FF0000FF0000FF0000FF0000
            FF0000FF0000FF0000FF0000FF00000000000000000000000000000000000000
            00FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            000000000000000000000000000000000000000000FF0000FF0000FF0000FF00
            00FF0000FF0000FF0000FF0000FF0000FF0000FF000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C00000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000FF0000
            FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF00000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000FF0000FF0000FF0000FF0000FF0000FF0000
            FF0000FF0000FF0000FF0000FF00000000000000000000000000000000000000
            00FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            000000000000000000000000000000000000000000FF0000FF0000FF0000FF00
            00FF0000FF0000FF0000FF0000FF0000FF000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C00000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000FF0000
            FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF00000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000FF0000FF0000FF0000FF0000FF0000FF0000
            FF0000FF0000FF0000FF0000FF00000000000000000000000000000000000000
            00000000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            000000000000000000000000000000000000FF0000FF0000FF0000FF0000FF00
            00FF0000FF0000FF0000FF0000FF0000FF000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C00000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF00000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000FF0000FF0000FF0000FF0000FF0000FF0000
            FF0000FF0000FF0000FF00000000000000000000000000000000000000000000
            00000000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            000000000000000000000000000000000000FF0000FF0000FF0000FF0000FF00
            00FF0000FF0000FF0000FF0000FF0000FF000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C00000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF00000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000FF0000FF0000FF0000FF0000FF0000FF0000
            FF0000FF0000FF0000FF00000000000000000000000000000000000000000000
            00000000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            000000000000000000000000000000000000FF0000FF0000FF0000FF0000FF00
            00FF0000FF0000FF0000FF0000FF0000FF000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C00000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF00000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000FF0000FF0000FF0000FF0000FF0000FF0000
            FF0000FF0000FF0000FF00000000000000000000000000000000000000000000
            00000000000000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            000000000000000000000000000000000000FF0000FF0000FF0000FF0000FF00
            00FF0000FF0000FF0000FF0000FF000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C00000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF00000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000FF0000FF0000FF0000FF0000FF0000FF0000FF0000
            FF0000FF0000FF0000FF00000000000000000000000000000000000000000000
            00000000000000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF
            0000FF0000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            000000000000000000000000000000FF0000FF0000FF0000FF0000FF0000FF00
            00FF0000FF0000FF0000FF0000FF000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C00000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF00000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000FF0000FF0000FF0000FF0000FF0000FF0000FF0000
            FF0000FF0000FF0000FF00000000000000000000000000000000000000000000
            00000000000000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF
            0000FF0000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            000000000000000000000000000000FF0000FF0000FF0000FF0000FF0000FF00
            00FF0000FF0000FF0000FF0000FF000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C00000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF00000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000FF0000FF0000FF0000FF0000FF0000FF0000FF0000
            FF0000FF0000FF0000FF00000000000000000000000000000000000000000000
            00000000000000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF
            0000FF0000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            000000000000000000000000000000FF0000FF0000FF0000FF0000FF0000FF00
            00FF0000FF0000FF0000FF0000FF000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C00000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF00000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000FF0000FF0000FF0000FF0000FF0000FF0000FF0000
            FF0000FF0000FF00000000000000000000000000000000000000000000000000
            00000000000000000000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF
            0000FF0000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            000000000000000000000000000000FF0000FF0000FF0000FF0000FF0000FF00
            00FF0000FF0000FF0000FF000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C00000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            000000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF00000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000FF0000FF0000FF0000FF0000FF0000FF0000FF0000
            FF0000FF0000FF00000000000000000000000000000000000000000000000000
            00000000000000000000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF
            0000FF0000FF0000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            000000000000000000000000FF0000FF0000FF0000FF0000FF0000FF0000FF00
            00FF0000FF0000FF0000FF000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C00000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            000000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF00
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000FF0000FF0000FF0000FF0000FF0000FF0000FF0000
            FF0000FF0000FF00000000000000000000000000000000000000000000000000
            00000000000000000000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF
            0000FF0000FF0000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            000000000000000000000000FF0000FF0000FF0000FF0000FF0000FF0000FF00
            00FF0000FF0000FF0000FF000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C00000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            000000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF00
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000
            FF0000FF0000FF00000000000000000000000000000000000000000000000000
            00000000000000000000000000FF0000FF0000FF0000FF0000FF0000FF0000FF
            0000FF0000FF0000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            000000000000000000000000FF0000FF0000FF0000FF0000FF0000FF0000FF00
            00FF0000FF0000FF0000FF000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C00000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            000000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF00
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000
            FF0000FF0000FF00000000000000000000000000000000000000000000000000
            00000000000000000000000000FF0000FF0000FF0000FF0000FF0000FF0000FF
            0000FF0000FF0000FF0000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            000000000000000000000000FF0000FF0000FF0000FF0000FF0000FF0000FF00
            00FF0000FF0000FF000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C00000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            000000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF00
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000
            FF0000FF0000FF00000000000000000000000000000000000000000000000000
            00000000000000000000000000000000FF0000FF0000FF0000FF0000FF0000FF
            0000FF0000FF0000FF0000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            000000000000000000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF00
            00FF0000FF0000FF000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C00000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            000000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF00
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000
            FF0000FF00000000000000000000000000000000000000000000000000000000
            00000000000000000000000000000000FF0000FF0000FF0000FF0000FF0000FF
            0000FF0000FF0000FF0000FF0000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            000000000000000000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF00
            00FF0000FF0000FF000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C00000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            000000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF00
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000
            FF0000FF00000000000000000000000000000000000000000000000000000000
            00000000000000000000000000000000FF0000FF0000FF0000FF0000FF0000FF
            0000FF0000FF0000FF0000FF0000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            000000000000000000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF00
            00FF0000FF0000FF000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C00000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            000000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF00
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000
            FF0000FF00000000000000000000000000000000000000000000000000000000
            00000000000000000000000000000000000000FF0000FF0000FF0000FF0000FF
            0000FF0000FF0000FF0000FF0000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            000000000000000000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF00
            00FF0000FF000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C00000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            000000000000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF00
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000
            FF0000FF00000000000000000000000000000000000000000000000000000000
            00000000000000000000000000000000000000FF0000FF0000FF0000FF0000FF
            0000FF0000FF0000FF0000FF0000FF0000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            000000000000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF00
            00FF0000FF000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C00000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            000000000000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF00
            00FF000000000000000000000000000000000000000000000000000000000000
            0000000000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000
            FF0000FF00000000000000000000000000000000000000000000000000000000
            00000000000000000000000000000000000000FF0000FF0000FF0000FF0000FF
            0000FF0000FF0000FF0000FF0000FF0000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            000000000000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF00
            00FF0000FF000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C00000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            000000000000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF00
            00FF000000000000000000000000000000000000000000000000000000000000
            0000000000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000
            FF0000FF00000000000000000000000000000000000000000000000000000000
            00000000000000000000000000000000000000000000FF0000FF0000FF0000FF
            0000FF0000FF0000FF0000FF0000FF0000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            000000000000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF00
            00FF0000FF000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C00000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            000000000000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF00
            00FF000000000000000000000000000000000000000000000000000000000000
            0000000000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000
            FF00000000000000000000000000000000000000000000000000000000000000
            00000000000000000000000000000000000000000000FF0000FF0000FF0000FF
            0000FF0000FF0000FF0000FF0000FF0000FF0000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            000000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF00
            00FF000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C00000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            000000000000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF00
            00FF000000000000000000000000000000000000000000000000000000000000
            0000000000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000
            FF00000000000000000000000000000000000000000000000000000000000000
            00000000000000000000000000000000000000000000FF0000FF0000FF0000FF
            0000FF0000FF0000FF0000FF0000FF0000FF0000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            000000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF00
            00FF000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C00000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            000000000000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF00
            00FF000000000000000000000000000000000000000000000000000000000000
            0000000000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000
            FF00000000000000000000000000000000000000000000000000000000000000
            00000000000000000000000000000000000000000000000000FF0000FF0000FF
            0000FF0000FF0000FF0000FF0000FF0000FF0000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            000000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF00
            00FF000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C00000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            000000000000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF00
            00FF000000000000000000000000000000000000000000000000000000000000
            0000000000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000
            FF00000000000000000000000000000000000000000000000000000000000000
            00000000000000000000000000000000000000000000000000FF0000FF0000FF
            0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            000000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF00
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C00000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            000000000000000000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF00
            00FF000000000000000000000000000000000000000000000000000000000000
            0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000
            FF00000000000000000000000000000000000000000000000000000000000000
            00000000000000000000000000000000000000000000000000FF0000FF0000FF
            0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF00
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C00000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            000000000000000000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF00
            00FF0000FF000000000000000000000000000000000000000000000000000000
            0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000
            FF00000000000000000000000000000000000000000000000000000000000000
            00000000000000000000000000000000000000000000000000000000FF0000FF
            0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF00
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C00000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            000000000000000000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF00
            00FF0000FF000000000000000000000000000000000000000000000000000000
            0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000
            FF00000000000000000000000000000000000000000000000000000000000000
            00000000000000000000000000000000000000000000000000000000FF0000FF
            0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF00
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C00000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            000000000000000000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF00
            00FF0000FF000000000000000000000000000000000000000000000000000000
            0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000
            0000000000000000000000000000000000000000000000000000000000000000
            00000000000000000000000000000000000000000000000000000000000000FF
            0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000FF0000
            FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF00000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C00000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            000000000000000000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF00
            00FF0000FF000000000000000000000000000000000000000000000000000000
            0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000
            0000000000000000000000000000000000000000000000000000000000000000
            00000000000000000000000000000000000000000000000000000000000000FF
            0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000FF0000
            FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF00000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C00000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            000000000000000000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF00
            00FF0000FF0000000000000000000000000000000000000000000000000000FF
            0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000FF0000
            FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF00000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C00000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            000000000000000000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF00
            00FF0000FF0000000000000000000000000000000000000000000000000000FF
            0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000FF0000FF0000
            FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF00000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C00000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            000000000000000000000000FF0000FF0000FF0000FF0000FF0000FF0000FF00
            00FF0000FF0000000000000000000000000000000000000000000000000000FF
            0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000FF0000FF0000
            FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF00000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C00000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            000000000000000000000000FF0000FF0000FF0000FF0000FF0000FF0000FF00
            00FF0000FF0000FF0000000000000000000000000000000000000000000000FF
            0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000FF0000FF0000
            FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF00000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C00000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            000000000000000000000000FF0000FF0000FF0000FF0000FF0000FF0000FF00
            00FF0000FF0000FF0000000000000000000000000000000000000000000000FF
            0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000
            FF00000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000FF0000FF0000FF0000
            FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF00000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C00000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            000000000000000000000000FF0000FF0000FF0000FF0000FF0000FF0000FF00
            00FF0000FF0000FF0000000000000000000000000000000000000000000000FF
            0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000
            FF00000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000FF0000FF0000FF0000
            FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF00000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C00000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            000000000000000000000000FF0000FF0000FF0000FF0000FF0000FF0000FF00
            00FF0000FF0000FF0000000000000000000000000000000000000000FF0000FF
            0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000
            FF0000FF00000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000FF0000FF0000FF0000FF0000
            FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF00000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C00000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            000000000000000000000000FF0000FF0000FF0000FF0000FF0000FF0000FF00
            00FF0000FF0000FF0000000000000000000000000000000000000000FF0000FF
            0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000FF0000FF0000FF0000FF0000FF0000FF0000FF0000
            FF0000FF00000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000FF0000FF0000FF0000FF0000
            FF0000FF0000FF0000FF0000FF0000FF0000FF00000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C00000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            000000000000000000000000FF0000FF0000FF0000FF0000FF0000FF0000FF00
            00FF0000FF0000FF0000000000000000000000000000000000000000FF0000FF
            0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000FF0000FF0000FF0000FF0000FF0000FF0000FF0000
            FF0000FF0000FF00000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000FF0000FF0000FF0000FF0000
            FF0000FF0000FF0000FF0000FF0000FF0000FF00000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C00000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            000000000000000000000000000000FF0000FF0000FF0000FF0000FF0000FF00
            00FF0000FF0000FF0000000000000000000000000000000000000000FF0000FF
            0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000FF0000FF0000FF0000FF0000FF0000FF0000
            FF0000FF0000FF00000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000FF0000FF0000FF0000FF0000FF0000
            FF0000FF0000FF0000FF0000FF0000FF00000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C00000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            000000000000000000000000000000FF0000FF0000FF0000FF0000FF0000FF00
            00FF0000FF0000FF0000FF0000000000000000000000000000000000FF0000FF
            0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000FF0000FF0000FF0000FF0000FF0000FF0000
            FF0000FF0000FF0000FF00000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000FF0000FF0000FF0000FF0000FF0000
            FF0000FF0000FF0000FF0000FF0000FF00000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C00000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            000000000000000000000000000000FF0000FF0000FF0000FF0000FF0000FF00
            00FF0000FF0000FF0000FF0000000000000000000000000000FF0000FF0000FF
            0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000FF0000FF0000FF0000FF0000FF0000
            FF0000FF0000FF0000FF00000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000FF0000FF0000FF0000FF0000FF0000FF0000
            FF0000FF0000FF0000FF0000FF0000FF00000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C00000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            000000000000000000000000000000FF0000FF0000FF0000FF0000FF0000FF00
            00FF0000FF0000FF0000FF0000000000000000000000000000FF0000FF0000FF
            0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000FF0000FF0000FF0000FF0000FF0000
            FF0000FF0000FF0000FF0000FF00000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000FF0000FF0000FF0000FF0000FF0000FF0000
            FF0000FF0000FF0000FF0000FF00000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C00000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            000000000000000000000000000000FF0000FF0000FF0000FF0000FF0000FF00
            00FF0000FF0000FF0000FF0000000000000000000000000000FF0000FF0000FF
            0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000FF0000FF0000FF0000FF0000
            FF0000FF0000FF0000FF0000FF00000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000FF0000FF0000FF0000FF0000FF0000FF0000FF0000
            FF0000FF0000FF0000FF0000FF00000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C00000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            000000000000000000000000000000FF0000FF0000FF0000FF0000FF0000FF00
            00FF0000FF0000FF0000FF0000000000000000000000000000FF0000FF0000FF
            0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000FF0000FF0000FF0000FF0000
            FF0000FF0000FF0000FF0000FF0000FF00000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000FF0000FF0000FF0000FF0000FF0000FF0000FF0000
            FF0000FF0000FF0000FF00000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C00000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            000000000000000000000000000000000000FF0000FF0000FF0000FF0000FF00
            00FF0000FF0000FF0000FF0000000000000000000000000000FF0000FF0000FF
            0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000FF0000FF0000FF0000
            FF0000FF0000FF0000FF0000FF0000FF00000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000
            FF0000FF0000FF0000FF00000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C00000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            000000000000000000000000000000000000FF0000FF0000FF0000FF0000FF00
            00FF0000FF0000FF0000FF0000FF0000000000000000000000FF0000FF0000FF
            0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000FF0000FF0000FF0000
            FF0000FF0000FF0000FF0000FF0000FF0000FF00000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000
            FF0000FF0000FF00000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C00000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            000000000000000000000000000000000000FF0000FF0000FF0000FF0000FF00
            00FF0000FF0000FF0000FF0000FF0000000000000000FF0000FF0000FF0000FF
            0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000FF0000FF0000
            FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF00000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000
            FF0000FF0000FF00000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C00000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            000000000000000000000000000000000000FF0000FF0000FF0000FF0000FF00
            00FF0000FF0000FF0000FF0000FF0000000000000000FF0000FF0000FF0000FF
            0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000FF0000
            FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF00000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000
            FF0000FF00000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C00000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            000000000000000000000000000000000000FF0000FF0000FF0000FF0000FF00
            00FF0000FF0000FF0000FF0000FF0000000000000000FF0000FF0000FF0000FF
            0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000FF0000
            FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF00000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000
            FF0000FF00000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C00000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            000000000000000000000000000000000000FF0000FF0000FF0000FF0000FF00
            00FF0000FF0000FF0000FF0000FF0000000000000000FF0000FF0000FF0000FF
            0000FF0000FF0000FF0000FF0000FF0000FF0000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF00000000
            00000000000000000000000000000000000000000000000000000000000000FF
            0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000
            FF00000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C00000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            000000000000000000000000000000000000000000FF0000FF0000FF0000FF00
            00FF0000FF0000FF0000FF0000FF0000000000FF0000FF0000FF0000FF0000FF
            0000FF0000FF0000FF0000FF0000FF0000FF0000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            000000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF00
            00000000000000000000000000000000000000000000000000000000FF0000FF
            0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000
            FF00000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C00000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            000000000000000000000000000000000000000000FF0000FF0000FF0000FF00
            00FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF
            0000FF0000FF0000FF0000FF0000FF0000FF0000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            000000000000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF00
            00FF0000000000000000000000000000000000000000000000FF0000FF0000FF
            0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C00000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            000000000000000000000000000000000000000000FF0000FF0000FF0000FF00
            00FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF
            0000FF0000FF0000FF0000FF0000FF0000FF0000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            000000000000000000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF00
            00FF0000000000000000000000000000000000000000FF0000FF0000FF0000FF
            0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C00000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            000000000000000000000000000000000000000000FF0000FF0000FF0000FF00
            00FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF
            0000FF0000FF0000FF0000FF0000FF0000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            000000000000000000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF00
            00FF0000FF0000000000000000000000FF0000FF0000FF0000FF0000FF0000FF
            0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C00000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            000000000000000000000000000000000000000000000000FF0000FF0000FF00
            00FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF
            0000FF0000FF0000FF0000FF0000FF0000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            000000000000000000000000FF0000FF0000FF0000FF0000FF0000FF0000FF00
            00FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF
            0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C00000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            000000000000000000000000000000000000000000000000FF0000FF0000FF00
            00FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF
            0000FF0000FF0000FF0000FF0000FF0000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            000000000000000000000000000000000000FF0000FF0000FF0000FF0000FF00
            00FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF
            0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C00000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            000000000000000000000000000000000000000000000000FF0000FF0000FF00
            00FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF
            0000FF0000FF0000FF0000FF0000FF0000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            000000000000000000000000000000000000000000FF0000FF0000FF0000FF00
            00FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF
            0000FF0000FF0000FF0000FF0000FF0000FF0000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C00000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            000000000000000000000000000000000000000000000000FF0000FF0000FF00
            00FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF
            0000FF0000FF0000FF0000FF0000FF0000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            000000000000000000000000000000000000000000000000000000FF0000FF00
            00FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF
            0000FF0000FF0000FF0000FF0000FF0000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C00000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            000000000000000000000000000000000000000000000000FF0000FF0000FF00
            00FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF
            0000FF0000FF0000FF0000FF0000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            00000000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF
            0000FF0000FF0000FF0000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C00000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            000000000000000000000000000000000000000000000000000000FF0000FF00
            00FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF
            0000FF0000FF0000FF0000FF0000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            00000000000000000000000000FF0000FF0000FF0000FF0000FF0000FF0000FF
            0000FF0000FF0000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C00000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            000000000000000000000000000000000000000000000000000000FF0000FF00
            00FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF
            0000FF0000FF0000FF0000FF0000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C00000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            000000000000000000000000000000000000000000000000000000FF0000FF00
            00FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF
            0000FF0000FF0000FF0000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C00000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            000000000000000000000000000000000000000000000000000000000000FF00
            00FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF
            0000FF0000FF0000FF0000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C00000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            000000000000000000000000000000000000000000000000000000000000FF00
            00FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF
            0000FF0000FF0000FF0000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C00000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            00FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF
            0000FF0000FF0000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C00000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            00FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF
            0000FF0000FF0000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C00000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            00000000000000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF
            0000FF0000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C00000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            00000000000000000000000000000000FF0000FF0000FF0000FF0000FF0000FF
            0000FF0000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C00000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            00000000000000000000000000000000000000000000000000FF0000FF0000FF
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C00000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C00000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C00000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C00000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C00000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C00000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C00000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000C0C0C0
            C0C0C0C0C0C00000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000}
          Stretch = True
          IsControl = True
        end
        object Label30: TLabel
          Left = 146
          Top = 197
          Width = 105
          Height = 19
          AutoSize = False
          Caption = 'saa@rossv.ru'
          Font.Charset = RUSSIAN_CHARSET
          Font.Color = clBlue
          Font.Height = -13
          Font.Name = 'Comic Sans MS'
          Font.Style = [fsBold, fsItalic, fsUnderline]
          ParentFont = False
        end
        object Label28: TLabel
          Left = 8
          Top = 200
          Width = 124
          Height = 16
          Caption = #1047#1040#1054' "'#1056#1054#1057#1089#1074#1103#1079#1100#1089#1080#1089#1090#1077#1084#1072'"'
        end
        object Label27: TLabel
          Left = 8
          Top = 180
          Width = 201
          Height = 21
          AutoSize = False
          Caption = 'Copyright: Shaposhnikov A.A.  10.2015'
        end
        object Label26: TLabel
          Left = 8
          Top = 163
          Width = 229
          Height = 16
          Caption = #1040#1074#1090#1086#1088': '#1064#1072#1087#1086#1096#1085#1080#1082#1086#1074' '#1040#1083#1077#1082#1089#1072#1085#1076#1088' '#1040#1085#1072#1090#1086#1083#1100#1077#1074#1080#1095
        end
        object Label25: TLabel
          Left = 88
          Top = 79
          Width = 177
          Height = 50
          Alignment = taCenter
          AutoSize = False
          Caption = 
            #1055#1088#1086#1075#1088#1072#1084#1084#1072' '#1076#1083#1103' '#1086#1090#1086#1073#1088#1072#1078#1077#1085#1080#1103' '#1076#1080#1072#1075#1088#1072#1084#1084' '#1089#1080#1075#1085#1072#1083#1086#1074', '#1089#1085#1080#1084#1072#1077#1084#1099#1093' '#1089' '#1072#1085#1072#1083#1080#1079#1072 +
            #1090#1086#1088#1086#1074' '#1088#1072#1079#1085#1099#1093' '#1084#1086#1076#1077#1083#1077#1081
          WordWrap = True
        end
        object Label24: TLabel
          Left = 2
          Top = 17
          Width = 210
          Height = 68
          Alignment = taCenter
          AutoSize = False
          Caption = #1059#1085#1080#1074#1077#1088#1089#1072#1083#1100#1085#1099#1081' '#1089#1087#1077#1082#1090#1088#1086#1072#1085#1072#1083#1080#1079#1072#1090#1086#1088
          Font.Charset = RUSSIAN_CHARSET
          Font.Color = clBlue
          Font.Height = -21
          Font.Name = 'Arial'
          Font.Style = [fsItalic]
          ParentFont = False
          Transparent = True
          WordWrap = True
        end
        object Label23: TLabel
          Left = 4
          Top = 18
          Width = 210
          Height = 68
          Alignment = taCenter
          AutoSize = False
          Caption = #1059#1085#1080#1074#1077#1088#1089#1072#1083#1100#1085#1099#1081' '#1089#1087#1077#1082#1090#1088#1086#1072#1085#1072#1083#1080#1079#1072#1090#1086#1088
          Font.Charset = RUSSIAN_CHARSET
          Font.Color = clBlack
          Font.Height = -21
          Font.Name = 'Arial'
          Font.Style = [fsItalic]
          ParentFont = False
          Transparent = True
          WordWrap = True
        end
      end
    end
  end
  object CtrlPanel: TPanel
    Left = 0
    Top = 332
    Width = 804
    Height = 197
    Align = alBottom
    TabOrder = 2
  end
  object BeamTimer: TTimer
    Enabled = False
    OnTimer = BeamTimerTimer
    Left = 152
    Top = 16
  end
  object ChartPopupMenu: TPopupMenu
    Left = 224
    Top = 104
    object CopyImageMenuItem: TMenuItem
      Caption = #1050#1086#1087#1080#1088#1086#1074#1072#1090#1100' '#1082#1072#1088#1090#1080#1085#1082#1091
      OnClick = CopyImageMenuItemClick
    end
    object SaveImgMenuItem: TMenuItem
      Caption = #1057#1086#1093#1088#1072#1085#1080#1090#1100' '#1082#1072#1088#1090#1080#1085#1082#1091
      OnClick = SaveImgMenuItemClick
    end
    object SaveAsGridMenuItem: TMenuItem
      Caption = #1057#1086#1093#1088#1072#1085#1080#1090#1100' '#1082#1072#1082' '#1090#1072#1073#1083#1080#1094#1091
      OnClick = SaveAsGridMenuItemClick
    end
    object SaveAsTextMenuItem: TMenuItem
      Caption = #1057#1086#1093#1088#1072#1085#1080#1090#1100' '#1082#1072#1082' '#1090#1077#1082#1089#1090
      OnClick = SaveAsTextMenuItemClick
    end
  end
  object SaveDialog1: TSaveDialog
    Filter = 
      'JPEG Image File (*.jpg)|*.jpg|JPEG Image File (*.jpeg)|*.jpeg|Bi' +
      'tmaps (*.bmp)|*.bmp|Icons (*.ico)|*.ico|Enhanced Metafiles (*.em' +
      'f)|*.emf|Metafiles (*.wmf)|*.wmf'
    FilterIndex = 0
    Options = [ofOverwritePrompt, ofHideReadOnly, ofEnableSizing]
    Title = #1057#1086#1093#1088#1072#1085#1077#1085#1080#1077
    Left = 224
    Top = 48
  end
  object FreqPlanPopupMenu: TPopupMenu
    Left = 72
    Top = 536
    object FreqPlanAddMenuItem: TMenuItem
      Caption = #1044#1086#1073#1072#1074#1080#1090#1100' '#1087#1086#1083#1086#1089#1091
      OnClick = FreqPlanEditMenuItemClick
    end
    object FreqPlanEditMenuItem: TMenuItem
      Tag = 1
      Caption = #1048#1079#1084#1077#1085#1080#1090#1100' '#1087#1086#1083#1086#1089#1091
      Visible = False
      OnClick = FreqPlanEditMenuItemClick
    end
    object FreqPlanDeleteMenuItem: TMenuItem
      Tag = 2
      Caption = #1059#1076#1072#1083#1080#1090#1100' '#1087#1086#1083#1086#1089#1091
      OnClick = FreqPlanEditMenuItemClick
    end
    object N1: TMenuItem
      Caption = '-'
    end
    object FreqPlanSaveMenuItem: TMenuItem
      Caption = #1057#1086#1093#1088#1072#1085#1080#1090#1100' '#1087#1083#1072#1085
      OnClick = FreqPlanMenuItemClick
    end
    object FreqPlanLoadMenuItem: TMenuItem
      Tag = 1
      Caption = #1047#1072#1075#1088#1091#1079#1080#1090#1100' '#1087#1083#1072#1085
      OnClick = FreqPlanMenuItemClick
    end
    object FreqPlanClearMenuItem: TMenuItem
      Tag = 2
      Caption = #1054#1095#1080#1089#1090#1080#1090#1100' '#1087#1083#1072#1085
      OnClick = FreqPlanMenuItemClick
    end
    object FreqPlanRedrawMenuItem: TMenuItem
      Tag = 3
      Caption = #1055#1077#1088#1077#1088#1080#1089#1086#1074#1072#1090#1100
      OnClick = FreqPlanMenuItemClick
    end
    object N2: TMenuItem
      Caption = '-'
    end
    object FreqPlanAutoSaveMenuItem: TMenuItem
      Caption = #1057#1086#1093#1088#1072#1085#1103#1090#1100' '#1087#1088#1080' '#1074#1099#1093#1086#1076#1077
      Checked = True
    end
    object FreqPlanAutoLoadMenuItem: TMenuItem
      Caption = #1047#1072#1075#1088#1091#1078#1072#1090#1100' '#1087#1088#1080' '#1089#1090#1072#1088#1090#1077
      Checked = True
    end
  end
end
