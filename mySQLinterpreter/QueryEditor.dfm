object query_editor: Tquery_editor
  Left = 0
  Top = 0
  Width = 443
  Height = 277
  Align = alClient
  TabOrder = 0
  object Splitter1: TSplitter
    Left = 0
    Top = 153
    Width = 443
    Height = 8
    Cursor = crVSplit
    Align = alTop
  end
  object query_text: TMemo
    Left = 0
    Top = 0
    Width = 443
    Height = 153
    Align = alTop
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Courier New'
    Font.Style = []
    ParentFont = False
    ScrollBars = ssBoth
    TabOrder = 0
  end
  object query_log: TMemo
    Left = 0
    Top = 161
    Width = 443
    Height = 75
    Align = alClient
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Courier New'
    Font.Style = []
    ParentFont = False
    ScrollBars = ssBoth
    TabOrder = 1
  end
  object query_grid: TStringGrid
    Left = 0
    Top = 161
    Width = 443
    Height = 75
    Align = alClient
    DefaultRowHeight = 16
    Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goColSizing]
    TabOrder = 2
    Visible = False
  end
  object Panel1: TPanel
    Left = 0
    Top = 236
    Width = 443
    Height = 41
    Align = alBottom
    TabOrder = 3
    object btn_exec: TButton
      Left = 8
      Top = 8
      Width = 75
      Height = 25
      Caption = #1042#1099#1087#1086#1083#1085#1080#1090#1100
      TabOrder = 0
      OnClick = btn_execClick
    end
    object edt_filename: TEdit
      Left = 88
      Top = 8
      Width = 521
      Height = 21
      Color = clBtnFace
      ReadOnly = True
      TabOrder = 1
    end
  end
end
