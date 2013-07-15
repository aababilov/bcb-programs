object Dim3Frame: TDim3Frame
  Left = 0
  Top = 0
  Width = 559
  Height = 333
  TabOrder = 0
  object MatrixScroll: TScrollBox
    Left = 0
    Top = 0
    Width = 559
    Height = 281
    Align = alTop
    TabOrder = 0
    object MatrixView: TImage
      Left = 0
      Top = 0
      Width = 113
      Height = 105
      Hint = #1065#1077#1083#1082#1085#1080#1090#1077' '#1076#1083#1103' '#1080#1079#1084#1077#1085#1077#1085#1080#1103' '#1079#1085#1072#1095#1077#1085#1080#1103
      ParentShowHint = False
      ShowHint = True
    end
  end
  object edtLayer: TLabeledEdit
    Left = 96
    Top = 304
    Width = 65
    Height = 21
    EditLabel.Width = 26
    EditLabel.Height = 13
    EditLabel.Caption = 'Layer'
    LabelPosition = lpAbove
    LabelSpacing = 3
    ReadOnly = True
    TabOrder = 1
    Text = '1'
  end
  object udLayer: TUpDown
    Left = 161
    Top = 304
    Width = 15
    Height = 21
    Associate = edtLayer
    Min = 1
    Max = 4
    Position = 1
    TabOrder = 2
    Wrap = False
    OnClick = udLayerClick
  end
  object edtM: TLabeledEdit
    Left = 8
    Top = 304
    Width = 65
    Height = 21
    EditLabel.Width = 8
    EditLabel.Height = 13
    EditLabel.Caption = 'm'
    LabelPosition = lpAbove
    LabelSpacing = 3
    ReadOnly = True
    TabOrder = 3
    Text = '4'
  end
  object udM: TUpDown
    Left = 73
    Top = 304
    Width = 15
    Height = 21
    Associate = edtM
    Min = 1
    Max = 50
    Position = 4
    TabOrder = 4
    Wrap = False
    OnClick = udMClick
  end
  object btnOpen: TButton
    Left = 192
    Top = 296
    Width = 75
    Height = 25
    Caption = 'Open'
    TabOrder = 5
    OnClick = btnOpenClick
  end
  object btnSave: TButton
    Left = 272
    Top = 296
    Width = 75
    Height = 25
    Caption = 'Save'
    TabOrder = 6
    OnClick = btnSaveClick
  end
  object btnSpec: TButton
    Left = 352
    Top = 296
    Width = 75
    Height = 25
    Caption = 'btnSpec'
    Default = True
    TabOrder = 7
  end
end
