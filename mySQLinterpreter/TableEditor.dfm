object table_editor: Ttable_editor
  Left = 326
  Top = 155
  Width = 736
  Height = 472
  Caption = 'table_editor'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object tbl_grid: TStringGrid
    Left = 0
    Top = 0
    Width = 728
    Height = 385
    Align = alClient
    DefaultRowHeight = 16
    Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goRowSizing, goEditing]
    TabOrder = 0
    OnGetEditText = tbl_gridGetEditText
    OnSelectCell = tbl_gridSelectCell
    OnSetEditText = tbl_gridSetEditText
  end
  object Panel1: TPanel
    Left = 0
    Top = 385
    Width = 728
    Height = 41
    Align = alBottom
    BevelOuter = bvNone
    TabOrder = 1
    object btnAdd: TButton
      Left = 8
      Top = 8
      Width = 75
      Height = 25
      Caption = #1044#1086#1073#1072#1074#1080#1090#1100
      TabOrder = 0
      OnClick = btnAddClick
    end
    object btnRemove: TButton
      Left = 96
      Top = 8
      Width = 75
      Height = 25
      Caption = #1059#1076#1072#1083#1080#1090#1100
      TabOrder = 1
      OnClick = btnRemoveClick
    end
    object btnSave: TButton
      Left = 184
      Top = 8
      Width = 75
      Height = 25
      Caption = #1057#1086#1093#1088#1072#1085#1080#1090#1100
      TabOrder = 2
      OnClick = btnSaveClick
    end
    object btnReload: TButton
      Left = 360
      Top = 8
      Width = 89
      Height = 25
      Caption = #1055#1077#1088#1077#1079#1072#1075#1088#1091#1079#1080#1090#1100
      TabOrder = 4
      OnClick = btnReloadClick
    end
    object btnCancel: TButton
      Left = 272
      Top = 8
      Width = 75
      Height = 25
      Caption = #1054#1090#1084#1077#1085#1080#1090#1100
      TabOrder = 3
      OnClick = btnCancelClick
    end
  end
  object status: TStatusBar
    Left = 0
    Top = 426
    Width = 728
    Height = 19
    Panels = <>
    SimplePanel = True
  end
end
