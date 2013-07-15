object SortEditorForm: TSortEditorForm
  Left = 297
  Top = 171
  Width = 727
  Height = 541
  Caption = #1060#1080#1079#1086#1085' - '#1056#1077#1076#1072#1082#1090#1086#1088' '#1079#1072#1076#1072#1095
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object Splttr: TSplitter
    Left = 177
    Top = 0
    Width = 3
    Height = 514
    Cursor = crHSplit
  end
  object ProblemList: TListView
    Left = 0
    Top = 0
    Width = 177
    Height = 514
    Align = alLeft
    Columns = <>
    PopupMenu = ListsMenu
    TabOrder = 0
    ViewStyle = vsList
    OnEdited = ListsEdited
    OnSelectItem = ProblemListSelectItem
  end
  object ProblemTabs: TTabControl
    Left = 180
    Top = 0
    Width = 539
    Height = 514
    Align = alClient
    PopupMenu = GroupsMenu
    TabOrder = 1
    Tabs.Strings = (
      #1043#1088#1091#1087#1087#1072' 1'
      #1043#1088#1091#1087#1087#1072' 2'
      #1043#1088#1091#1087#1087#1072' 3')
    TabIndex = 0
    OnChange = SetWordsList
    object WordsList: TListView
      Left = 4
      Top = 24
      Width = 531
      Height = 486
      Align = alClient
      Columns = <>
      ParentShowHint = False
      PopupMenu = ListsMenu
      ShowHint = False
      TabOrder = 0
      ViewStyle = vsList
      OnEdited = ListsEdited
    end
  end
  object ListsMenu: TPopupMenu
    Left = 136
    Top = 32
    object miAdd: TMenuItem
      Caption = '&'#1044#1086#1073#1072#1074#1080#1090#1100
      ShortCut = 45
      OnClick = miAddClick
    end
    object miDelete: TMenuItem
      Caption = '&'#1059#1076#1072#1083#1080#1090#1100
      ShortCut = 16430
      OnClick = miDeleteClick
    end
  end
  object GroupsMenu: TPopupMenu
    Left = 200
    Top = 32
    object miChangeGN: TMenuItem
      Caption = '&'#1048#1079#1084#1077#1085#1080#1090#1100' '#1085#1072#1079#1074#1072#1085#1080#1077' '#1075#1088#1091#1087#1087#1099
      OnClick = miChangeGNClick
    end
  end
end
