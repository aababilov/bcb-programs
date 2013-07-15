object MainForm: TMainForm
  Left = 194
  Top = 110
  BorderStyle = bsSingle
  Caption = 'AV BAR'
  ClientHeight = 571
  ClientWidth = 765
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  PixelsPerInch = 96
  TextHeight = 13
  object MainMnu: TActionMainMenuBar
    Left = 0
    Top = 0
    Width = 765
    Height = 29
    ActionManager = ActionMgr
    Caption = 'MainMnu'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clMenuText
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
    Spacing = 0
  end
  object pgcProblems: TPageControl
    Left = 0
    Top = 29
    Width = 765
    Height = 523
    ActivePage = tbsMatrix
    Align = alClient
    Style = tsFlatButtons
    TabIndex = 0
    TabOrder = 1
    OnChange = pgcProblemsChange
    object tbsMatrix: TTabSheet
      Caption = 'Matri&x'
      ImageIndex = 1
      DesignSize = (
        757
        492)
      object btnSortCols: TButton
        Left = 652
        Top = 233
        Width = 78
        Height = 25
        Anchors = [akRight, akBottom]
        Caption = 'Sort columns'
        TabOrder = 4
        OnClick = btnSortColsClick
      end
      object btnGetList: TButton
        Left = 652
        Top = 265
        Width = 78
        Height = 25
        Anchors = [akRight, akBottom]
        Caption = 'Get list'
        TabOrder = 5
        OnClick = btnGetListClick
      end
      object edtLayer: TLabeledEdit
        Left = 700
        Top = 153
        Width = 33
        Height = 21
        Anchors = [akRight, akBottom]
        EditLabel.Width = 55
        EditLabel.Height = 13
        EditLabel.Caption = 'Visible layer'
        LabelPosition = lpLeft
        LabelSpacing = 3
        ReadOnly = True
        TabOrder = 2
        Text = '1'
      end
      object udwLayer: TUpDown
        Left = 733
        Top = 153
        Width = 15
        Height = 21
        Anchors = [akRight, akBottom]
        Associate = edtLayer
        Min = 1
        Max = 4
        Position = 1
        TabOrder = 3
        Wrap = False
        OnChanging = udwLayerChanging
        OnClick = udwLayerClick
      end
      object btnRecalculate: TButton
        Left = 652
        Top = 297
        Width = 78
        Height = 25
        Anchors = [akRight, akBottom]
        Caption = 'Recalculate'
        TabOrder = 6
        OnClick = btnRecalculateClick
      end
      object MatrixGrid: TStringGrid
        Left = 0
        Top = 0
        Width = 633
        Height = 492
        Align = alLeft
        Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goEditing]
        TabOrder = 0
      end
      object gbDimensions: TGroupBox
        Left = 640
        Top = 0
        Width = 113
        Height = 129
        Caption = 'Dimensions'
        TabOrder = 1
        object edtLayers: TLabeledEdit
          Left = 50
          Top = 73
          Width = 33
          Height = 21
          EditLabel.Width = 31
          EditLabel.Height = 13
          EditLabel.Caption = 'Layers'
          LabelPosition = lpLeft
          LabelSpacing = 3
          TabOrder = 0
          Text = '4'
        end
        object edtRows: TLabeledEdit
          Left = 50
          Top = 17
          Width = 33
          Height = 21
          EditLabel.Width = 27
          EditLabel.Height = 13
          EditLabel.Caption = 'Rows'
          LabelPosition = lpLeft
          LabelSpacing = 3
          TabOrder = 1
          Text = '4'
        end
        object edtColumns: TLabeledEdit
          Left = 50
          Top = 45
          Width = 33
          Height = 21
          EditLabel.Width = 40
          EditLabel.Height = 13
          EditLabel.Caption = 'Columns'
          LabelPosition = lpLeft
          LabelSpacing = 3
          TabOrder = 2
          Text = '4'
        end
        object udwColumns: TUpDown
          Left = 83
          Top = 45
          Width = 15
          Height = 21
          Associate = edtColumns
          Min = 1
          Max = 50
          Position = 4
          TabOrder = 3
          Wrap = False
          OnClick = DimensionsChange
        end
        object udwRows: TUpDown
          Left = 83
          Top = 17
          Width = 15
          Height = 21
          Associate = edtRows
          Min = 1
          Max = 50
          Position = 4
          TabOrder = 4
          Wrap = False
          OnClick = DimensionsChange
        end
        object udwLayers: TUpDown
          Left = 83
          Top = 73
          Width = 15
          Height = 21
          Associate = edtLayers
          Min = 1
          Max = 50
          Position = 4
          TabOrder = 5
          Wrap = False
          OnClick = DimensionsChange
        end
        object chbCube: TCheckBox
          Left = 8
          Top = 105
          Width = 57
          Height = 17
          Caption = 'Cube'
          TabOrder = 6
          OnClick = chbCubeClick
        end
      end
      object gbFindS: TGroupBox
        Left = 640
        Top = 336
        Width = 113
        Height = 153
        Caption = 'Calculating S'
        TabOrder = 7
        DesignSize = (
          113
          153)
        object btnFindS: TButton
          Left = 19
          Top = 120
          Width = 78
          Height = 25
          Anchors = [akRight, akBottom]
          Caption = 'Find S'
          TabOrder = 4
          OnClick = btnFindSClick
        end
        object edtSX: TLabeledEdit
          Left = 16
          Top = 24
          Width = 81
          Height = 21
          EditLabel.Width = 5
          EditLabel.Height = 13
          EditLabel.Caption = 'x'
          LabelPosition = lpLeft
          LabelSpacing = 3
          TabOrder = 0
          Text = '2'
        end
        object edtSK: TLabeledEdit
          Left = 16
          Top = 56
          Width = 65
          Height = 21
          EditLabel.Width = 6
          EditLabel.Height = 13
          EditLabel.Caption = 'k'
          LabelPosition = lpLeft
          LabelSpacing = 3
          ReadOnly = True
          TabOrder = 1
          Text = '1'
        end
        object udwSK: TUpDown
          Left = 81
          Top = 56
          Width = 15
          Height = 21
          Associate = edtSK
          Min = 1
          Max = 4
          Position = 1
          TabOrder = 2
          Wrap = False
        end
        object edtSS: TLabeledEdit
          Left = 16
          Top = 88
          Width = 81
          Height = 21
          BevelOuter = bvSpace
          EditLabel.Width = 7
          EditLabel.Height = 13
          EditLabel.Caption = 'S'
          LabelPosition = lpLeft
          LabelSpacing = 3
          ReadOnly = True
          TabOrder = 3
        end
      end
    end
    object tbsStudents: TTabSheet
      Caption = '&Students'
      ImageIndex = 4
      DesignSize = (
        757
        492)
      object StudList: TListView
        Left = 0
        Top = 0
        Width = 757
        Height = 457
        Align = alTop
        Columns = <
          item
            Caption = 'Full name'
            Width = 150
          end
          item
            Caption = 'Date of birth'
            Width = 70
          end
          item
            Caption = 'Residence'
            Width = 100
          end
          item
            Caption = 'Place of birth'
            Width = 75
          end
          item
            Caption = 'Test book'
            Width = 60
          end
          item
            Caption = 'Fav. subject'
            Width = 70
          end
          item
            Caption = 'Section'
          end
          item
            Caption = 'Foreign lang.'
            Width = 75
          end
          item
            Caption = 'Grant'
          end>
        HideSelection = False
        ReadOnly = True
        TabOrder = 0
        ViewStyle = vsReport
        OnColumnClick = StudListColumnClick
        OnCompare = StudListCompare
      end
      object btnAddStudent: TButton
        Left = 236
        Top = 462
        Width = 75
        Height = 25
        Anchors = [akLeft, akBottom]
        Caption = 'Add'
        TabOrder = 1
        OnClick = btnAddStudentClick
      end
      object btnEditStudent: TButton
        Left = 408
        Top = 461
        Width = 75
        Height = 25
        Anchors = [akLeft, akBottom]
        Caption = 'Edit'
        TabOrder = 3
        OnClick = btnEditStudentClick
      end
      object btnDeleteStudent: TButton
        Left = 324
        Top = 461
        Width = 75
        Height = 25
        Anchors = [akLeft, akBottom]
        Caption = 'Delete'
        TabOrder = 2
        OnClick = btnDeleteStudentClick
      end
    end
    object tbsMAX: TTabSheet
      Caption = 'The &MAX function'
      object XYField: TGraph2D
        Left = 0
        Top = 0
        Width = 361
        Height = 492
        Align = alLeft
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -16
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentFont = False
        OnMouseMove = GraphMouseMove
        OnMouseUp = XYFieldMouseUp
        AxisPen.Width = 3
        GridPen.Color = clSilver
        GraphPen.Color = clRed
        TickPen.Width = 2
        TipBrush.Style = bsClear
        XAxis.PixelsPerUnit = 3.20909090909091
        XAxis.GridStep = 10
        XAxis.TipStep = 20
        XAxis.ConstValue = 1
        XAxis.TipShift = 8
        XAxis.Name = 'x'
        YAxis.PixelsPerUnit = 3.12389380530973
        YAxis.GridStep = 10
        YAxis.TipStep = 20
        YAxis.ConstValue = 1
        YAxis.TipShift = 8
        YAxis.Name = 'y'
        AutoScroll = False
        AutoScale = False
        OnRedraw = XYFieldRedraw
      end
      object MAXGraph: TGraph2D
        Left = 368
        Top = 0
        Width = 389
        Height = 492
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -19
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentFont = False
        OnMouseMove = GraphMouseMove
        AxisPen.Width = 3
        GridPen.Color = clSilver
        GraphPen.Color = clRed
        GraphPen.Width = 3
        TickPen.Width = 2
        TipBrush.Style = bsClear
        XAxis.Center = 1
        XAxis.PixelsPerUnit = 88.8996960486322
        XAxis.GridStep = 0.5
        XAxis.TipStep = 1
        XAxis.ConstValue = 1
        XAxis.TipShift = 8
        XAxis.Name = 'n'
        YAxis.PixelsPerUnit = 1
        YAxis.GridStep = 50
        YAxis.TipStep = 50
        YAxis.ConstValue = 1
        YAxis.TipShift = 8
        YAxis.Name = 'MAX'
        OnRedraw = MAXGraphRedraw
      end
      object XYShape: TShape
        Left = 256
        Top = 0
        Width = 3
        Height = 3
        Brush.Color = clMenuHighlight
        Shape = stCircle
      end
    end
    object tbsSeries: TTabSheet
      Caption = 'S&um of the series'
      ImageIndex = 3
      object WhiteRect: TShape
        Left = 176
        Top = 8
        Width = 577
        Height = 481
      end
      object lblHere: TLabel
        Left = 280
        Top = 152
        Width = 331
        Height = 37
        Caption = #1047#1076#1077#1089#1100' '#1084#1086#1075#1083#1072' '#1073#1099#1090#1100' '#1074#1072#1096#1072
        Color = clWhite
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clRed
        Font.Height = -35
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentColor = False
        ParentFont = False
      end
      object lblR: TLabel
        Left = 344
        Top = 256
        Width = 226
        Height = 58
        Caption = #1056#1045#1050#1051#1040#1052#1040
        Color = clWhite
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clRed
        Font.Height = -48
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentColor = False
        ParentFont = False
      end
      object btnSeriesCalculate: TButton
        Left = 32
        Top = 104
        Width = 105
        Height = 25
        Caption = 'Calculate'
        TabOrder = 0
        OnClick = btnSeriesCalculateClick
      end
      object edtSeriesX: TLabeledEdit
        Left = 16
        Top = 32
        Width = 132
        Height = 21
        EditLabel.Width = 7
        EditLabel.Height = 13
        EditLabel.Caption = 'X'
        LabelPosition = lpAbove
        LabelSpacing = 3
        TabOrder = 1
        Text = '1'
      end
      object edtSeriesE: TLabeledEdit
        Left = 16
        Top = 72
        Width = 132
        Height = 21
        EditLabel.Width = 7
        EditLabel.Height = 13
        EditLabel.Caption = 'E'
        LabelPosition = lpAbove
        LabelSpacing = 3
        TabOrder = 2
        Text = '0,05'
      end
      object edtSerSum: TLabeledEdit
        Left = 16
        Top = 152
        Width = 132
        Height = 21
        BorderStyle = bsNone
        Color = clBtnFace
        EditLabel.Width = 29
        EditLabel.Height = 13
        EditLabel.Caption = 'Summ'
        LabelPosition = lpAbove
        LabelSpacing = 3
        ReadOnly = True
        TabOrder = 3
      end
      object edtNumMembers: TLabeledEdit
        Left = 16
        Top = 192
        Width = 132
        Height = 21
        BorderStyle = bsNone
        Color = clBtnFace
        EditLabel.Width = 79
        EditLabel.Height = 13
        EditLabel.Caption = 'Num of members'
        LabelPosition = lpAbove
        LabelSpacing = 3
        ReadOnly = True
        TabOrder = 4
      end
      object edtLastMember: TLabeledEdit
        Left = 16
        Top = 232
        Width = 132
        Height = 21
        BorderStyle = bsNone
        Color = clBtnFace
        EditLabel.Width = 60
        EditLabel.Height = 13
        EditLabel.Caption = 'Last member'
        LabelPosition = lpAbove
        LabelSpacing = 3
        ReadOnly = True
        TabOrder = 5
      end
    end
    object tbsPolynom: TTabSheet
      Caption = '&Polynom'
      ImageIndex = 5
      DesignSize = (
        757
        492)
      object PolynomGraph: TGraph2D
        Left = 0
        Top = 0
        Width = 753
        Height = 417
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentFont = False
        OnMouseMove = GraphMouseMove
        AxisPen.Width = 3
        GridPen.Color = clSilver
        GraphPen.Color = clRed
        TickPen.Width = 2
        TipBrush.Style = bsClear
        XAxis.PixelsPerUnit = 32
        XAxis.GridStep = 1
        XAxis.TipStep = 1
        XAxis.ConstValue = 1
        XAxis.TipShift = 8
        XAxis.Name = 'x'
        YAxis.PixelsPerUnit = 32
        YAxis.GridStep = 1
        YAxis.TipStep = 1
        YAxis.ConstValue = 1
        YAxis.TipShift = 8
        YAxis.Name = 'y'
        OnRedraw = PolynomGraphRedraw
        OnScroll = PolynomGraphChanged
        OnScale = PolynomGraphChanged
      end
      object gbTolerance: TGroupBox
        Left = 264
        Top = 432
        Width = 153
        Height = 49
        Anchors = [akLeft, akBottom]
        Caption = 'Tolerance'
        TabOrder = 2
        DesignSize = (
          153
          49)
        object edtTolerance: TEdit
          Left = 8
          Top = 16
          Width = 137
          Height = 21
          Anchors = [akLeft, akTop, akRight]
          TabOrder = 0
          Text = '0,00005'
        end
      end
      object udwZoom: TUpDown
        Left = 553
        Top = 456
        Width = 15
        Height = 21
        Associate = edtZoom
        Min = 1
        Max = 32677
        Position = 10
        TabOrder = 4
        Wrap = False
        OnClick = udwIntvZoomClick
      end
      object edtZoom: TLabeledEdit
        Left = 432
        Top = 456
        Width = 121
        Height = 21
        EditLabel.Width = 27
        EditLabel.Height = 13
        EditLabel.Caption = 'Zoom'
        LabelPosition = lpAbove
        LabelSpacing = 3
        ReadOnly = True
        TabOrder = 3
        Text = '10'
      end
      inline DrawInterval: TIntervalFrame
        Left = 8
        Top = 432
        Width = 121
        Height = 50
        TabOrder = 0
        inherited TheGroupBox: TGroupBox
          Caption = 'Drawing interval'
          inherited edtTo: TEdit
            Text = '50'
          end
          inherited edtFrom: TEdit
            Text = '-50'
          end
          inherited udwFrom: TUpDown
            Position = -50
            OnClick = udwIntvZoomClick
          end
          inherited udwTo: TUpDown
            Position = 50
            OnClick = udwIntvZoomClick
          end
        end
      end
      inline SolveInterval: TIntervalFrame
        Left = 136
        Top = 432
        Width = 121
        Height = 50
        TabOrder = 1
        inherited TheGroupBox: TGroupBox
          Caption = 'Solving interval'
        end
      end
      object btnSolve: TButton
        Left = 664
        Top = 448
        Width = 75
        Height = 25
        Caption = 'Solve'
        TabOrder = 6
        OnClick = btnSolveClick
      end
      object btnCenter: TBitBtn
        Left = 576
        Top = 448
        Width = 75
        Height = 25
        Caption = 'Center'
        TabOrder = 5
        OnClick = btnCenterClick
        Glyph.Data = {
          AA030000424DAA03000000000000360000002800000011000000110000000100
          1800000000007403000000000000000000000000000000000000FFFFFFFFFFFF
          FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF000000FFFFFFFFFFFFFFFFFFFFFF
          FFFFFFFFFFFFFFFFFFFFFFFFFF00FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
          000000000000000000000000000000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
          FF00FFFFFFFFFFFFFFFFFFFFFFFF000000000000FFFFFFFFFFFF000000FFFFFF
          FFFFFF000000000000FFFFFFFFFFFFFFFFFFFFFFFF00FFFFFFFFFFFFFFFFFF00
          0000FFFFFFFFFFFFFFFFFFFFFFFF000000FFFFFFFFFFFFFFFFFFFFFFFF000000
          FFFFFFFFFFFFFFFFFF00FFFFFFFFFFFF000000FFFFFFFFFFFFFFFFFFFFFFFFFF
          FFFF000000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFF000000FFFFFFFFFFFF00FFFF
          FFFFFFFF000000FFFFFFFFFFFFFFFFFFFFFFFF0000FF0000000000FFFFFFFFFF
          FFFFFFFFFFFFFFFF000000FFFFFFFFFFFF00FFFFFF000000FFFFFFFFFFFFFFFF
          FFFFFFFF0000FFFFFFFF000000FFFFFF0000FFFFFFFFFFFFFFFFFFFFFFFFFF00
          0000FFFFFF00FFFFFF000000FFFFFFFFFFFFFFFFFF0000FFFFFFFFFFFFFF0000
          00FFFFFFFFFFFF0000FFFFFFFFFFFFFFFFFFFF000000FFFFFF00000000000000
          0000000000000000000000000000000000000000FF0000000000000000000000
          0000000000000000000000000000FFFFFF000000FFFFFFFFFFFFFFFFFF0000FF
          FFFFFFFFFFFF000000FFFFFFFFFFFF0000FFFFFFFFFFFFFFFFFFFF000000FFFF
          FF00FFFFFF000000FFFFFFFFFFFFFFFFFFFFFFFF0000FFFFFFFF000000FFFFFF
          0000FFFFFFFFFFFFFFFFFFFFFFFFFF000000FFFFFF00FFFFFFFFFFFF000000FF
          FFFFFFFFFFFFFFFFFFFFFF0000FF0000000000FFFFFFFFFFFFFFFFFFFFFFFFFF
          000000FFFFFFFFFFFF00FFFFFFFFFFFF000000FFFFFFFFFFFFFFFFFFFFFFFFFF
          FFFF000000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFF000000FFFFFFFFFFFF00FFFF
          FFFFFFFFFFFFFF000000FFFFFFFFFFFFFFFFFFFFFFFF000000FFFFFFFFFFFFFF
          FFFFFFFFFF000000FFFFFFFFFFFFFFFFFF00FFFFFFFFFFFFFFFFFFFFFFFF0000
          00000000FFFFFFFFFFFF000000FFFFFFFFFFFF000000000000FFFFFFFFFFFFFF
          FFFFFFFFFF00FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF0000000000000000
          00000000000000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF00FFFFFFFFFFFF
          FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF000000FFFFFFFFFFFFFFFFFFFFFF
          FFFFFFFFFFFFFFFFFFFFFFFFFF00}
      end
    end
  end
  object StatusBar: TStatusBar
    Left = 0
    Top = 552
    Width = 765
    Height = 19
    Panels = <>
    SimplePanel = True
  end
  object ActionMgr: TActionManager
    ActionBars = <
      item
        Items = <
          item
            Items = <
              item
                Action = actFileOpen
                ImageIndex = 0
                ShortCut = 16463
              end
              item
                Action = actFileSaveAs
                ImageIndex = 1
                ShortCut = 16467
              end
              item
                Caption = '-'
              end
              item
                Action = actFileExit
                ImageIndex = 2
                ShortCut = 27
              end>
            Caption = '&File'
          end
          item
            Items = <
              item
                Action = actRegister
                ImageIndex = 3
                ShortCut = 16466
              end
              item
                Action = actUnregister
                ImageIndex = 4
                ShortCut = 16469
              end>
            Caption = '&Registry'
          end
          item
            Items = <
              item
                Action = actAbout
                ImageIndex = 5
                ShortCut = 112
              end>
            Caption = '&Help'
          end>
        ActionBar = MainMnu
      end>
    Images = ActionImages
    Left = 600
    Top = 8
    object actFileOpen: TFileOpen
      Category = '&File'
      Caption = '&Open...'
      Dialog.Filter = 
        'Matrixes (*.avm)|*.avm|Student lists (*.avl)|*.avl|Matrixes and ' +
        'student lists (*.avl;*.avm)|*.avm;*.avl|All files (*.*)|*.*'
      Dialog.OnTypeChange = actFileOpenOpenDialogTypeChange
      Hint = 'Open|Opens an existing file'
      ImageIndex = 0
      ShortCut = 16463
      BeforeExecute = actFileOpenBeforeExecute
      OnAccept = actFileOpenAccept
    end
    object actFileSaveAs: TFileSaveAs
      Category = '&File'
      Caption = 'Save &As...'
      Hint = 'Save As|Saves the active file with a new name'
      ImageIndex = 1
      ShortCut = 16467
      BeforeExecute = actFileSaveAsBeforeExecute
      OnAccept = actFileSaveAsAccept
    end
    object actFileExit: TFileExit
      Category = '&File'
      Caption = 'E&xit'
      Hint = 'Exit|Quits the application'
      ImageIndex = 2
      ShortCut = 27
    end
    object actAbout: TAction
      Category = '&Help'
      Caption = '&About'
      ImageIndex = 5
      ShortCut = 112
      OnExecute = actAboutExecute
    end
    object actRegister: TAction
      Category = '&Registry'
      Caption = '&Register'
      ImageIndex = 3
      ShortCut = 16466
      OnExecute = actRegisterExecute
    end
    object actUnregister: TAction
      Category = '&Registry'
      Caption = '&Unregister'
      ImageIndex = 4
      ShortCut = 16469
      OnExecute = actUnregisterExecute
    end
  end
  object ActionImages: TImageList
    Left = 632
    Top = 8
    Bitmap = {
      494C010106000900040010001000FFFFFFFFFF10FFFFFFFFFFFFFFFF424D3600
      0000000000003600000028000000400000003000000001002000000000000030
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000FF0000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000FF000000FF000000000000000000000000000000
      0000CABEBC00CE816700D46D4900D9684200DD785600DF8F7600DAA08D00D1C7
      C500CBD2D6000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000FF000000FF00FFFF00008080
      0000FFFFFF00FFFF000080800000FFFFFF00FFFF000080800000000000000000
      0000000000000000FF000000FF0000000000000000000000000000000000CB78
      5E00CD3A0800D24B1E00D8653E00DF806000E5977E00E8A38C00E69C8300DF7F
      5F00D38E7700CBD3D70000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000808080000000FF000000FF008080
      0000FFFF0000FFFFFF0080800000FFFF0000FFFFFF0080800000000000000000
      00000000FF000000FF00000000000000000000000000CAD1D400CD512800CD37
      0100D1400900D7582500DD734800ECAF9700EFBFAD00EDB7A300F1C4B400F0C0
      AF00E69B8000D6745000CBD3D600000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000080808000808000000000FF000000
      FF00808000008080000080800000FFFFFF00FFFF000080800000000000000000
      FF000000FF00000000000000000000000000CAD1D400CD7A5A00D4450100D94D
      0100DA510100DD5A0D00E3783700FFFFFF00FFFFFF00EEB49600F0BDA400F4CF
      BD00F3CBB800E89B7B00D58C6F00CAD1D4000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000080808000FFFFFF00FFFF00000000
      FF000000FF00FFFF0000808000000000000000000000000000000000FF000000
      FF0000000000000000000000000000000000CCBDB600D74B0100DF5A0100E261
      0100E3640100E4650100E5690700F5C29C00F6D1B500EC975C00EFAC8100F2BF
      A100F5CFB900F1BEA200E17D5000CEC0B8000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000080808000FFFF0000FFFFFF008080
      00000000FF000000FF008080000000000000808000000000FF000000FF008080
      000000000000000000000000000000000000D27A4C00E1650D00EA761300EB76
      0A00EC740200EC750100ED7D1000F1954000EF903A00EC832800EF975100F1AE
      7B00F3C19D00F4C4A400E99A6F00D68360000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000008080800080800000808000000000
      0000808000000000FF000000FF00000000000000FF000000FF00000000000000
      000000000000000000000000000000000000DB692700EA7A1900F18C2600F289
      1900F2810600F27F0100F49C3E00FEFAF600FCE6D000EF841E00ED821F00F098
      4A00F3B17800F5BE9100EEA67700DA7647000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000080808000FFFFFF00FFFF00008080
      000000000000000000000000FF000000FF000000FF0080800000000000008080
      000000000000000000000000000000000000DF5F0B00EF8A2A00F5A14300F59B
      3500F48B1600F3820500F4942F00FEF4EA00FFFEFD00FBE7D400EE924300EB7E
      1D00F0984900F3B07400EEA36E00DA612B000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000080808000FFFF0000FFFFFF008080
      000000000000808000000000FF000000FF000000FF0000000000000000008080
      000000000000000000000000000000000000E0610D00EE882F00F5A34F00F5A3
      4C00F5983100F58B1400F4830500F7B57200FEF9F500FFFFFF00FEF7F200EFA8
      7600E5711D00EA8B4700E6875000D75722000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000080808000FFFF0000FFFF
      FF00000000000000FF000000FF00808000000000FF000000FF00000000008080
      000000000000000000000000000000000000DB722E00EA802A00F19E5100F5A8
      5900FDE6CB00FDE4C300F9951600F4860700F4A04D00FCE9D800FFFEFD00FEF9
      F600E78C5A00DA591800D7582400D15E35000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000808080008080
      00000000FF000000FF00FFFFFF0080800000000000000000FF000000FF000000
      000080808000808000000000000000000000D7875300E7762000F0994C00F5AB
      5E00FFFDFB00FFFEFD00FEC06A00F7951F00F1841200EE882E00FDF3EB00FFFE
      FE00EDAD8C00D1410300CD390700CC7053000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      FF000000FF0080808000808080008080800080808000000000000000FF000000
      FF0080800000FFFF00008080000000000000CCC2BB00E56D1200EE8F3C00F5A8
      5B00FDECD700FFFFFF00FFFDFA00FDE9D100FCE3C900FDF2E700FFFEFD00FEFC
      FB00E4845400D13E0100CC340100CABDBB000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000000000000000FF000000
      FF00000000000000000000000000000000008080800080800000000000000000
      FF000000FF00FFFFFF00000000000000000000000000D8936100EA7C2100F19A
      4A00F7BD8000FEF9F300FFFEFE00FFFEFE00FFFEFD00FFFEFD00FEFAF700F0B7
      9400D84E0B00D03D0200CB785E00000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000FF000000FF000000
      00000000000000000000000000008080800080800000FFFF0000808000000000
      00000000FF000000FF0000000000000000000000000000000000DF7B3100EB81
      2800F0974600F4A65C00F8C99C00FBDEC400F9DAC100F5C6A300EA945E00DD63
      1F00D54A0B00CE552A0000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000FF000000FF00000000000000
      00000000000000000000000000000000000080808000FFFFFF00000000000000
      0000000000000000FF000000FF00000000000000000000000000CAD1D500D995
      6300E8781E00EC863300ED8D3F00EC8C4200E9853C00E5782F00DE661F00D851
      0F00CF7F5F000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000FF0000000000000000000000
      0000000000000000000000000000000000000000000080808000000000000000
      000000000000000000000000FF000000FF000000000000000000000000000000
      0000CDC4BC00D9956500DF7D3900E2691800E0631500D9713400D2876200CBC0
      BB00000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000008484840084848400848484008484
      8400848484008484840084848400848484008484840084848400FFFFFF00C6C6
      C60084848400C6C6C600FFFFFF00C6C6C6000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000008484840084848400848484008484
      840084848400848484008484840084848400848484008484840084848400FFFF
      FF0084848400FFFFFF00848484008484840080808000FFFFFF00FFFF00008080
      0000FFFFFF00FFFF000080800000FFFFFF00FFFF000080800000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000008400000084000000840000008400
      00000000000000000000848484008484840084848400FFFFFF00FFFFFF00FFFF
      FF008400000084000000840000008400000080808000FFFF0000FFFFFF008080
      0000FFFF0000FFFFFF0080800000FFFF0000FFFFFF0080800000000000000000
      0000000000000000000000000000000000000000000000000000008484000084
      8400008484000084840000848400008484000084840000848400008484000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000008484000084840000000000000000000000000000000000C6C6C6000000
      0000008484000000000000000000000000000000000000000000000000008400
      0000FF00000084000000000000000000000084848400FFFFFF00FFFFFF00FFFF
      FF00840000000000000000000000000000008080800080800000808000008080
      0000808000008080000080800000FFFFFF00FFFF000080800000000000008080
      0000000000000000000000000000000000000000000000FFFF00000000000084
      8400008484000084840000848400008484000084840000848400008484000084
      8400000000000000000000000000000000000000000000000000000000000000
      0000008484000084840000000000000000000000000000000000C6C6C6000000
      0000008484000000000000000000000000000000000000000000000000008400
      000084000000FF0000008400000000000000FFFFFF00FFFFFF00FFFFFF00FFFF
      FF008400000000000000000000000000000080808000FFFFFF00FFFF00008080
      0000FFFFFF00FFFF000080800000000000000000000000000000000000008080
      00000000000000000000000000000000000000000000FFFFFF0000FFFF000000
      0000008484000084840000848400008484000084840000848400008484000084
      8400008484000000000000000000000000000000000000000000000000000000
      0000008484000084840000000000000000000000000000000000000000000000
      0000008484000000000000000000000000000000000000000000000000008400
      0000FF00000084000000FF00000000000000FFFFFF00FFFFFF00FFFFFF00FFFF
      FF008400000000000000000000000000000080808000FFFF0000FFFFFF008080
      0000FFFF0000FFFFFF0080800000000000008080000080800000000000008080
      0000000000000000000000000000000000000000000000FFFF00FFFFFF0000FF
      FF00000000000084840000848400008484000084840000848400008484000084
      8400008484000084840000000000000000000000000000000000000000000000
      0000008484000084840000848400008484000084840000848400008484000084
      8400008484000000000000000000000000000000000000000000000000008400
      000084000000FF0000008400000000000000FFFFFF00FFFF0000FFFFFF00FFFF
      0000840000000000000000000000000000008080800080800000808000000000
      000080800000FFFFFF008080000000000000FFFF000080800000000000000000
      00000000000000000000000000000000000000000000FFFFFF0000FFFF00FFFF
      FF0000FFFF000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000008484000084840000000000000000000000000000000000000000000084
      8400008484000000000000000000000000000000000000000000000000008400
      0000FF00000084000000FF00000000000000FFFF0000FFFFFF00FFFF0000FFFF
      FF008400000000000000000000000000000080808000FFFFFF00FFFF00008080
      000000000000000000000000000000000000FFFFFF0080800000000000008080
      0000000000000000000000000000000000000000000000FFFF00FFFFFF0000FF
      FF00FFFFFF0000FFFF00FFFFFF0000FFFF00FFFFFF0000FFFF00000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000084840000000000C6C6C600C6C6C600C6C6C600C6C6C600C6C6C6000000
      0000008484000000000000000000000000000000000000000000000000008400
      000084000000FF0000008400000000000000FFFFFF00FFFF0000FFFFFF00FFFF
      00008400000000000000000000000000000080808000FFFF0000FFFFFF008080
      0000000000008080000080800000808000000000000000000000000000008080
      00000000000000000000000000000000000000000000FFFFFF0000FFFF00FFFF
      FF0000FFFF00FFFFFF0000FFFF00FFFFFF0000FFFF00FFFFFF00000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000084840000000000C6C6C600C6C6C600C6C6C600C6C6C600C6C6C6000000
      0000008484000000000000000000000000000000000000000000000000008400
      0000FF00000084000000FF00000000000000FFFF0000FFFFFF00FFFF0000FFFF
      FF00840000000000000000000000000000000000000080808000FFFF0000FFFF
      FF0000000000FFFF0000FFFFFF00808000000000000080800000000000008080
      0000000000000000000000000000000000000000000000FFFF00FFFFFF0000FF
      FF00000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000084840000000000C6C6C600C6C6C600C6C6C600C6C6C600C6C6C6000000
      0000000000000000000000000000000000000000000000000000000000008400
      0000840000008400000084000000840000008400000084000000840000008400
      0000840000000000000000000000000000000000000000000000808080008080
      000080800000FFFFFF00FFFFFF00808000000000000080800000808080000000
      0000808080008080000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000084840000000000C6C6C600C6C6C600C6C6C600C6C6C600C6C6C6000000
      0000C6C6C6000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000008080
      8000808080008080800080808000808080008080800000000000FFFFFF008080
      800080800000FFFF000080800000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000808080008080000000000000FFFF
      FF0080808000FFFFFF0000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000840000008400000084000000840000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000008080800080800000FFFF0000808000000000
      0000000000008080800000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000080808000FFFFFF00000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000080808000000000000000
      000000000000000000000000000000000000424D3E000000000000003E000000
      2800000040000000300000000100010000000000800100000000000000000000
      000000000000000000000000FFFFFF0000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000003CF007000000000019E00300000000
      0003800100000000000700000000000000070000000000000007000000000000
      0007000000000000000700000000000000070000000000008003000000000000
      C001000000000000E000000000000000CF018001000000009E03C00300000000
      3F19C007000000007FBCF00F00000000FFFFFF7E0000003FFFFFBFFF0000001F
      001FF0030000000F000FE003E00700070007E003E00700070003E003E0070007
      0001E003E007000700002003E0070007001FE002E0070007001FE003E0078003
      001FE003E007C0018FF1E003FFFFE000FFF9E003F81FFF01FF75FFFFF81FFE0B
      FF8FBF7DF81FFF1FFFFF7F7EFFFFFFBF00000000000000000000000000000000
      000000000000}
  end
  object BlinkTimer: TTimer
    Enabled = False
    Interval = 300
    OnTimer = BlinkTimerTimer
    Left = 568
    Top = 8
  end
end
