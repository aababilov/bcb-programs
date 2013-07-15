object SettingsForm: TSettingsForm
  Left = 108
  Top = 109
  Caption = 'Domino'
  ClientHeight = 569
  ClientWidth = 814
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  KeyPreview = True
  OldCreateOrder = False
  OnDestroy = FormDestroy
  OnKeyDown = FormKeyDown
  PixelsPerInch = 96
  TextHeight = 13
  object lblInfo: TLabel
    Left = 536
    Top = 64
    Width = 3
    Height = 13
  end
  object Button2: TButton
    Left = 536
    Top = 16
    Width = 75
    Height = 25
    Caption = 'Start'
    TabOrder = 0
    OnClick = Button2Click
  end
  object leLength: TLabeledEdit
    Left = 24
    Top = 16
    Width = 121
    Height = 21
    EditLabel.Width = 33
    EditLabel.Height = 13
    EditLabel.Caption = 'Length'
    TabOrder = 1
    Text = '0.206'
  end
  object leWidth: TLabeledEdit
    Left = 24
    Top = 56
    Width = 121
    Height = 21
    EditLabel.Width = 28
    EditLabel.Height = 13
    EditLabel.Caption = 'Width'
    TabOrder = 2
    Text = '0.133'
  end
  object leThickness: TLabeledEdit
    Left = 152
    Top = 16
    Width = 121
    Height = 21
    EditLabel.Width = 49
    EditLabel.Height = 13
    EditLabel.Caption = 'Thickness'
    TabOrder = 3
    Text = '0.028'
  end
  object leStep: TLabeledEdit
    Left = 152
    Top = 56
    Width = 121
    Height = 21
    EditLabel.Width = 22
    EditLabel.Height = 13
    EditLabel.Caption = 'Step'
    TabOrder = 4
    Text = '0.10'
  end
  object leDomCount: TLabeledEdit
    Left = 280
    Top = 56
    Width = 121
    Height = 21
    EditLabel.Width = 28
    EditLabel.Height = 13
    EditLabel.Caption = 'Count'
    TabOrder = 5
    Text = '16'
  end
  object leDelta_T: TLabeledEdit
    Left = 408
    Top = 16
    Width = 121
    Height = 21
    EditLabel.Width = 38
    EditLabel.Height = 13
    EditLabel.Caption = 'Delta_T'
    TabOrder = 6
    Text = '0.01'
  end
  object leTollerance: TLabeledEdit
    Left = 408
    Top = 56
    Width = 121
    Height = 21
    EditLabel.Width = 50
    EditLabel.Height = 13
    EditLabel.Caption = 'Tollerance'
    TabOrder = 7
    Text = '0.001'
  end
  object leInterval: TLabeledEdit
    Left = 280
    Top = 16
    Width = 121
    Height = 21
    EditLabel.Width = 35
    EditLabel.Height = 13
    EditLabel.Caption = 'Interval'
    TabOrder = 8
    Text = '10'
  end
  object ViewPanel: TPanel
    Left = 8
    Top = 88
    Width = 793
    Height = 473
    Color = clBlack
    TabOrder = 9
    OnMouseDown = ViewPanelMouseDown
    OnMouseMove = ViewPanelMouseMove
  end
  object Timer: TTimer
    Enabled = False
    OnTimer = TimerTimer
    Left = 448
    Top = 48
  end
  object ApplicationEvents1: TApplicationEvents
    OnMessage = ApplicationEvents1Message
    Left = 480
    Top = 48
  end
end
