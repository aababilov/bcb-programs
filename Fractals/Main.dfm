object Form1: TForm1
  Left = 185
  Top = 107
  Width = 704
  Height = 480
  Caption = 'Form1'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnCreate = FormCreate
  DesignSize = (
    696
    453)
  PixelsPerInch = 96
  TextHeight = 13
  object Image1: TImage
    Left = 0
    Top = 0
    Width = 514
    Height = 453
    Anchors = [akLeft, akTop, akRight, akBottom]
  end
  object bntNewton: TButton
    Left = 553
    Top = 8
    Width = 75
    Height = 25
    Anchors = [akTop, akRight]
    Caption = 'bntNewton'
    Default = True
    TabOrder = 0
    OnClick = bntNewtonClick
  end
  object bntMandel: TButton
    Left = 553
    Top = 48
    Width = 75
    Height = 25
    Anchors = [akTop, akRight]
    Caption = 'bntMandel'
    TabOrder = 1
    OnClick = bntMandelClick
  end
  object edtColCoeff: TLabeledEdit
    Left = 553
    Top = 152
    Width = 121
    Height = 21
    Anchors = [akTop, akRight]
    EditLabel.Width = 55
    EditLabel.Height = 13
    EditLabel.Caption = 'edtColCoeff'
    LabelPosition = lpAbove
    LabelSpacing = 3
    TabOrder = 2
    Text = '$3FFF'
  end
  object edtMaxIter: TLabeledEdit
    Left = 553
    Top = 192
    Width = 121
    Height = 21
    Anchors = [akTop, akRight]
    EditLabel.Width = 50
    EditLabel.Height = 13
    EditLabel.Caption = 'edtMaxIter'
    LabelPosition = lpAbove
    LabelSpacing = 3
    TabOrder = 3
    Text = '$FF'
  end
  object edtBailOut: TLabeledEdit
    Left = 553
    Top = 232
    Width = 121
    Height = 21
    Anchors = [akTop, akRight]
    EditLabel.Width = 49
    EditLabel.Height = 13
    EditLabel.Caption = 'edtBailOut'
    LabelPosition = lpAbove
    LabelSpacing = 3
    TabOrder = 4
    Text = '0,7'
  end
  object edtPLeft: TLabeledEdit
    Left = 553
    Top = 296
    Width = 121
    Height = 21
    Anchors = [akTop, akRight]
    EditLabel.Width = 40
    EditLabel.Height = 13
    EditLabel.Caption = 'edtPLeft'
    LabelPosition = lpAbove
    LabelSpacing = 3
    TabOrder = 5
    Text = '-0,25'
  end
  object edtPWidth: TLabeledEdit
    Left = 553
    Top = 336
    Width = 121
    Height = 21
    Anchors = [akTop, akRight]
    EditLabel.Width = 50
    EditLabel.Height = 13
    EditLabel.Caption = 'edtPWidth'
    LabelPosition = lpAbove
    LabelSpacing = 3
    TabOrder = 6
    Text = '0,5'
  end
  object edtPTop: TLabeledEdit
    Left = 553
    Top = 376
    Width = 121
    Height = 21
    Anchors = [akTop, akRight]
    EditLabel.Width = 41
    EditLabel.Height = 13
    EditLabel.Caption = 'edtPTop'
    LabelPosition = lpAbove
    LabelSpacing = 3
    TabOrder = 7
    Text = '0,216'
  end
  object edtPHeight: TLabeledEdit
    Left = 553
    Top = 416
    Width = 121
    Height = 21
    Anchors = [akTop, akRight]
    EditLabel.Width = 53
    EditLabel.Height = 13
    EditLabel.Caption = 'edtPHeight'
    LabelPosition = lpAbove
    LabelSpacing = 3
    TabOrder = 8
    Text = '2'
  end
  object btnJulia: TButton
    Left = 553
    Top = 80
    Width = 75
    Height = 25
    Anchors = [akTop, akRight]
    Caption = 'btnJulia'
    TabOrder = 9
    OnClick = btnJuliaClick
  end
  object btnRecolor: TButton
    Left = 553
    Top = 112
    Width = 75
    Height = 25
    Anchors = [akTop, akRight]
    Caption = 'btnRecolor'
    TabOrder = 10
  end
  object Timer1: TTimer
    Interval = 10
    OnTimer = Timer1Timer
    Left = 368
    Top = 120
  end
end
