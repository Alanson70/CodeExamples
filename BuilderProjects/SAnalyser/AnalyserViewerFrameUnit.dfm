inherited AnalyserViewerFrame: TAnalyserViewerFrame
  Width = 784
  inherited APanel: TPanel
    Width = 784
    inherited ChartPanel: TPanel
      Width = 670
      inherited Chart1: TChart
        Width = 668
      end
      inherited InfoPanel: TPanel
        Width = 668
        inherited SignalInfoLabel: TLabel
          Width = 668
        end
      end
    end
    inherited FreqGroupBox: TGroupBox
      Width = 668
    end
  end
  inherited SettsPageControl: TPageControl
    Width = 784
    inherited PlanTabSheet: TTabSheet
      inherited PageControl2: TPageControl
        Width = 776
      end
    end
  end
  inherited CtrlPanel: TPanel
    Width = 784
    BevelOuter = bvNone
    object CtrlPageControl: TPageControl
      Left = 0
      Top = 0
      Width = 784
      Height = 197
      ActivePage = WorkTabSheet
      Align = alClient
      TabIndex = 0
      TabOrder = 0
      object WorkTabSheet: TTabSheet
        Caption = #1042#1086#1089#1087#1088#1086#1080#1079#1074#1077#1076#1077#1085#1080#1077
        ImageIndex = 1
        DesignSize = (
          776
          166)
        object Label15: TLabel
          Left = 240
          Top = 88
          Width = 91
          Height = 16
          Caption = #1089' '#1080#1085#1090#1077#1088#1074#1072#1083#1086#1084', '#1089#1077#1082
        end
        object Label37: TLabel
          Left = 12
          Top = 124
          Width = 54
          Height = 16
          Caption = #1055#1088#1086#1082#1088#1091#1090#1082#1072
        end
        object Label4: TLabel
          Left = 16
          Top = 16
          Width = 26
          Height = 16
          Caption = #1060#1072#1081#1083
        end
        object Label5: TLabel
          Left = 8
          Top = 48
          Width = 66
          Height = 16
          Caption = #1048#1085#1092#1086#1088#1084#1072#1094#1080#1103
        end
        object PlayIntervalEdit: TEdit
          Left = 336
          Top = 84
          Width = 33
          Height = 24
          ReadOnly = True
          TabOrder = 0
          Text = '1'
          OnChange = PlayIntervalEditChange
        end
        object PlayIntervalUpDown: TUpDown
          Left = 369
          Top = 84
          Width = 15
          Height = 24
          Associate = PlayIntervalEdit
          Min = 1
          Max = 600
          Position = 1
          TabOrder = 1
          Wrap = False
        end
        object PlayButton: TButton
          Left = 80
          Top = 84
          Width = 153
          Height = 25
          Caption = #1047#1072#1087#1091#1089#1082
          Enabled = False
          TabOrder = 2
          OnClick = PlayButtonClick
        end
        object PlayScrollBar: TScrollBar
          Left = 80
          Top = 120
          Width = 685
          Height = 33
          Anchors = [akLeft, akTop, akRight]
          Enabled = False
          Max = 8000
          PageSize = 0
          TabOrder = 3
          OnScroll = PlayScrollBarScroll
        end
        object FileNameEdit: TEdit
          Left = 80
          Top = 12
          Width = 607
          Height = 24
          Anchors = [akLeft, akTop, akRight]
          ReadOnly = True
          TabOrder = 4
          OnChange = FileNameEditChange
        end
        object FileChooseButton: TButton
          Left = 695
          Top = 12
          Width = 75
          Height = 25
          Anchors = [akTop, akRight]
          Caption = #1042#1099#1073#1088#1072#1090#1100
          TabOrder = 5
          OnClick = FileChooseButtonClick
        end
        object PlayerFileInfEdit: TEdit
          Left = 80
          Top = 44
          Width = 607
          Height = 24
          Anchors = [akLeft, akTop, akRight]
          Color = clBtnFace
          ReadOnly = True
          TabOrder = 6
          OnChange = FileNameEditChange
        end
      end
    end
  end
  object PlayTimer: TTimer
    Enabled = False
    OnTimer = PlayTimerTimer
    Left = 184
    Top = 360
  end
end
