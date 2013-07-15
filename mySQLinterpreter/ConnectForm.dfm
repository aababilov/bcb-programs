object fm_connect: Tfm_connect
  Left = 269
  Top = 189
  BorderStyle = bsDialog
  Caption = #1057#1086#1077#1076#1080#1085#1077#1085#1080#1077
  ClientHeight = 190
  ClientWidth = 278
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  OnDestroy = FormDestroy
  PixelsPerInch = 96
  TextHeight = 13
  object GroupBox1: TGroupBox
    Left = 8
    Top = 0
    Width = 265
    Height = 129
    Caption = #1057#1077#1088#1074#1077#1088' '#1080' '#1087#1086#1083#1100#1079#1086#1074#1072#1090#1077#1083#1100
    TabOrder = 0
    object edt_host: TLabeledEdit
      Left = 8
      Top = 32
      Width = 121
      Height = 21
      EditLabel.Width = 24
      EditLabel.Height = 13
      EditLabel.Caption = #1061#1086#1089#1090
      LabelPosition = lpAbove
      LabelSpacing = 3
      TabOrder = 0
      Text = 'localhost'
    end
    object edt_user: TLabeledEdit
      Left = 136
      Top = 32
      Width = 121
      Height = 21
      EditLabel.Width = 73
      EditLabel.Height = 13
      EditLabel.Caption = #1055#1086#1083#1100#1079#1086#1074#1072#1090#1077#1083#1100
      LabelPosition = lpAbove
      LabelSpacing = 3
      TabOrder = 1
      Text = 'root'
    end
    object edt_port: TLabeledEdit
      Left = 8
      Top = 72
      Width = 121
      Height = 21
      EditLabel.Width = 25
      EditLabel.Height = 13
      EditLabel.Caption = #1055#1086#1088#1090
      LabelPosition = lpAbove
      LabelSpacing = 3
      TabOrder = 2
    end
    object edt_password: TLabeledEdit
      Left = 136
      Top = 72
      Width = 121
      Height = 21
      EditLabel.Width = 38
      EditLabel.Height = 13
      EditLabel.BiDiMode = bdRightToLeftNoAlign
      EditLabel.Caption = #1055#1072#1088#1086#1083#1100
      EditLabel.ParentBiDiMode = False
      LabelPosition = lpAbove
      LabelSpacing = 3
      TabOrder = 3
    end
    object Button1: TButton
      Left = 96
      Top = 96
      Width = 75
      Height = 25
      Caption = #1057#1086#1077#1076#1080#1085#1080#1090#1100#1089#1103
      TabOrder = 4
      OnClick = Button1Click
    end
  end
  object gb_select_db: TGroupBox
    Left = 8
    Top = 136
    Width = 265
    Height = 49
    Caption = #1041#1072#1079#1072' '#1076#1072#1085#1085#1099#1093
    TabOrder = 1
    object db_name: TComboBox
      Left = 8
      Top = 20
      Width = 121
      Height = 21
      ItemHeight = 13
      TabOrder = 0
    end
    object btn_select_db: TButton
      Left = 158
      Top = 16
      Width = 75
      Height = 25
      Caption = #1042#1099#1073#1088#1072#1090#1100
      Enabled = False
      TabOrder = 1
      OnClick = btn_select_dbClick
    end
  end
end
