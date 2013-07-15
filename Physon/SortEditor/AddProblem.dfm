object AddProbForm: TAddProbForm
  Left = 239
  Top = 233
  BorderStyle = bsDialog
  Caption = #1057#1086#1079#1076#1072#1085#1080#1077' '#1085#1086#1074#1086#1081' '#1079#1072#1076#1072#1095#1080
  ClientHeight = 146
  ClientWidth = 269
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  OnCloseQuery = FormCloseQuery
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object edtProbName: TLabeledEdit
    Left = 112
    Top = 8
    Width = 145
    Height = 21
    EditLabel.Width = 53
    EditLabel.Height = 13
    EditLabel.Caption = #1053#1072#1079#1074#1072#1085#1080#1077':'
    LabelPosition = lpLeft
    LabelSpacing = 3
    TabOrder = 0
    OnKeyPress = edtProbNameKeyPress
  end
  object edtGroup1: TLabeledEdit
    Left = 112
    Top = 32
    Width = 145
    Height = 21
    EditLabel.Width = 105
    EditLabel.Height = 13
    EditLabel.Caption = #1055#1077#1088#1074#1072#1103' '#1075#1088#1091#1087#1087#1072' '#1089#1083#1086#1074':'
    LabelPosition = lpLeft
    LabelSpacing = 3
    MaxLength = 10
    TabOrder = 1
  end
  object edtGroup2: TLabeledEdit
    Left = 112
    Top = 56
    Width = 145
    Height = 21
    EditLabel.Width = 103
    EditLabel.Height = 13
    EditLabel.Caption = #1042#1090#1086#1088#1072#1103' '#1075#1088#1091#1087#1087#1072' '#1089#1083#1086#1074':'
    LabelPosition = lpLeft
    LabelSpacing = 3
    MaxLength = 10
    TabOrder = 2
  end
  object edtGroup3: TLabeledEdit
    Left = 112
    Top = 80
    Width = 145
    Height = 21
    EditLabel.Width = 103
    EditLabel.Height = 13
    EditLabel.Caption = #1058#1088#1077#1090#1100#1103' '#1075#1088#1091#1087#1087#1072' '#1089#1083#1086#1074':'
    LabelPosition = lpLeft
    LabelSpacing = 3
    MaxLength = 10
    TabOrder = 3
  end
  object btnOK: TBitBtn
    Left = 48
    Top = 112
    Width = 75
    Height = 25
    TabOrder = 4
    Kind = bkOK
  end
  object btnCancel: TBitBtn
    Left = 136
    Top = 112
    Width = 75
    Height = 25
    Caption = #1054#1090#1084#1077#1085#1072
    TabOrder = 5
    Kind = bkCancel
  end
end
