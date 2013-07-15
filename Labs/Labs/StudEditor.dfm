object StudEditorForm: TStudEditorForm
  Left = 423
  Top = 198
  BorderStyle = bsDialog
  Caption = 'StudEditorForm'
  ClientHeight = 255
  ClientWidth = 338
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  OnClose = FormClose
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object lblFavSubject: TLabel
    Left = 8
    Top = 136
    Width = 81
    Height = 13
    Caption = 'Favourite subject'
  end
  object lblDateBirth: TLabel
    Left = 8
    Top = 48
    Width = 58
    Height = 13
    Caption = 'Date of birth'
    FocusControl = dateBirth
  end
  object edtTestBook: TLabeledEdit
    Left = 176
    Top = 104
    Width = 153
    Height = 21
    EditLabel.Width = 48
    EditLabel.Height = 13
    EditLabel.Caption = 'Test book'
    LabelPosition = lpAbove
    LabelSpacing = 3
    TabOrder = 4
  end
  object edtSection: TLabeledEdit
    Left = 8
    Top = 192
    Width = 113
    Height = 21
    EditLabel.Width = 36
    EditLabel.Height = 13
    EditLabel.Caption = 'Section'
    LabelPosition = lpAbove
    LabelSpacing = 3
    TabOrder = 6
  end
  object edtResidence: TLabeledEdit
    Left = 176
    Top = 64
    Width = 153
    Height = 21
    EditLabel.Width = 51
    EditLabel.Height = 13
    EditLabel.Caption = 'Residence'
    LabelPosition = lpAbove
    LabelSpacing = 3
    TabOrder = 2
  end
  object edtPlaceBirth: TLabeledEdit
    Left = 8
    Top = 104
    Width = 153
    Height = 21
    EditLabel.Width = 62
    EditLabel.Height = 13
    EditLabel.Caption = 'Place of birth'
    LabelPosition = lpAbove
    LabelSpacing = 3
    TabOrder = 3
  end
  object edtGrant: TLabeledEdit
    Left = 240
    Top = 192
    Width = 89
    Height = 21
    EditLabel.Width = 26
    EditLabel.Height = 13
    EditLabel.Caption = 'Grant'
    LabelPosition = lpAbove
    LabelSpacing = 3
    TabOrder = 8
  end
  object edtFullName: TLabeledEdit
    Left = 8
    Top = 24
    Width = 321
    Height = 21
    EditLabel.Width = 45
    EditLabel.Height = 13
    EditLabel.Caption = 'Full name'
    LabelPosition = lpAbove
    LabelSpacing = 3
    TabOrder = 0
  end
  object edtForLang: TLabeledEdit
    Left = 128
    Top = 192
    Width = 105
    Height = 21
    EditLabel.Width = 82
    EditLabel.Height = 13
    EditLabel.Caption = 'Foreign language'
    LabelPosition = lpAbove
    LabelSpacing = 3
    TabOrder = 7
  end
  object dateBirth: TDateTimePicker
    Left = 8
    Top = 63
    Width = 153
    Height = 21
    CalAlignment = dtaLeft
    Date = -620658.385181007
    Time = -620658.385181007
    DateFormat = dfShort
    DateMode = dmComboBox
    Kind = dtkDate
    ParseInput = False
    TabOrder = 1
  end
  object cbxFavSubject: TComboBox
    Left = 8
    Top = 152
    Width = 321
    Height = 21
    Style = csDropDownList
    ItemHeight = 13
    TabOrder = 5
    Items.Strings = (
      #1040#1083#1075#1086#1088#1080#1090#1084#1080#1095#1077#1089#1082#1080#1077' '#1103#1079#1099#1082#1080' '#1080' '#1087#1088#1086#1075#1088#1072#1084#1084#1080#1088#1086#1074#1072#1085#1080#1077
      #1048#1085#1086#1089#1090#1088#1072#1085#1085#1099#1081' '#1103#1079#1099#1082
      #1048#1085#1078#1077#1085#1077#1088#1085#1072#1103' '#1075#1088#1072#1092#1080#1082#1072
      #1056#1077#1083#1080#1075#1080#1086#1074#1077#1076#1077#1085#1080#1077
      #1042#1099#1089#1096#1072#1103' '#1084#1072#1090#1077#1084#1072#1090#1080#1082#1072
      #1060#1080#1079#1080#1082#1072
      #1048#1089#1090#1086#1088#1080#1103' '#1059#1082#1088#1072#1080#1085#1099)
  end
  object btnOK: TButton
    Left = 88
    Top = 224
    Width = 75
    Height = 25
    Caption = 'OK'
    Default = True
    ModalResult = 1
    TabOrder = 9
  end
  object btnCancel: TButton
    Left = 176
    Top = 224
    Width = 75
    Height = 25
    Cancel = True
    Caption = 'Cancel'
    ModalResult = 2
    TabOrder = 10
  end
end
