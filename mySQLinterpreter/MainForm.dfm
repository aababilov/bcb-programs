object main_form: Tmain_form
  Left = 224
  Top = 118
  Width = 870
  Height = 500
  Caption = 'SQL Client'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  Menu = MainMenu1
  OldCreateOrder = False
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Splitter1: TSplitter
    Left = 153
    Top = 0
    Width = 8
    Height = 454
    Cursor = crHSplit
  end
  object GroupBox2: TGroupBox
    Left = 161
    Top = 0
    Width = 701
    Height = 454
    Align = alClient
    Caption = #1047#1072#1087#1088#1086#1089#1099
    TabOrder = 0
    object query_tabs: TPageControl
      Left = 2
      Top = 15
      Width = 697
      Height = 437
      Align = alClient
      TabOrder = 0
    end
  end
  object GroupBox1: TGroupBox
    Left = 0
    Top = 0
    Width = 153
    Height = 454
    Align = alLeft
    Caption = #1058#1072#1073#1083#1080#1094#1099
    TabOrder = 1
    object table_list: TListBox
      Left = 2
      Top = 15
      Width = 149
      Height = 437
      Align = alClient
      ItemHeight = 13
      TabOrder = 0
      OnDblClick = table_listDblClick
    end
  end
  object MainMenu1: TMainMenu
    Left = 152
    Top = 8
    object N5: TMenuItem
      Caption = #1047#1072#1087#1088#1086#1089#1099
      object N6: TMenuItem
        Caption = #1057#1086#1079#1076#1072#1090#1100
        ShortCut = 16468
        OnClick = N6Click
      end
      object N7: TMenuItem
        Caption = #1054#1090#1082#1088#1099#1090#1100
        ShortCut = 16463
        OnClick = N7Click
      end
      object N8: TMenuItem
        Caption = #1057#1086#1093#1088#1072#1085#1080#1090#1100
        ShortCut = 16467
        OnClick = N8Click
      end
      object N9: TMenuItem
        Caption = #1047#1072#1082#1088#1099#1090#1100
        ShortCut = 16471
        OnClick = N9Click
      end
      object N10: TMenuItem
        Caption = #1042#1099#1087#1086#1083#1085#1080#1090#1100
        ShortCut = 120
        OnClick = N10Click
      end
      object N11: TMenuItem
        Caption = #1054#1090#1095#1105#1090
        OnClick = N11Click
      end
    end
    object N1: TMenuItem
      Caption = #1053#1072#1089#1090#1088#1086#1081#1082#1080
      object N2: TMenuItem
        Caption = #1057#1086#1077#1076#1080#1085#1077#1085#1080#1077
        ShortCut = 16464
        OnClick = N2Click
      end
    end
    object N3: TMenuItem
      Caption = #1054#1073#1085#1086#1074#1080#1090#1100
      object N4: TMenuItem
        Caption = #1057#1087#1080#1089#1086#1082' '#1090#1072#1073#1083#1080#1094
        ShortCut = 16466
        OnClick = N4Click
      end
    end
  end
  object opendlg: TOpenDialog
    DefaultExt = 'sql'
    Filter = 'SQL scripts (*.sql)|*.sql|All files|*'
    InitialDir = '.'
    Left = 120
    Top = 96
  end
  object savedlg: TSaveDialog
    DefaultExt = 'sql'
    Filter = 'SQL scripts (*.sql)|*.sql|All files|*'
    InitialDir = '.'
    Left = 152
    Top = 96
  end
  object saverep: TSaveDialog
    DefaultExt = 'htm'
    Filter = 'Html|*.html;*.htm'
    Left = 184
    Top = 96
  end
end
