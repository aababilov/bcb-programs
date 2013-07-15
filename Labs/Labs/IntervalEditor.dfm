object IntervalFrame: TIntervalFrame
  Left = 0
  Top = 0
  Width = 121
  Height = 50
  TabOrder = 0
  DesignSize = (
    121
    50)
  object TheGroupBox: TGroupBox
    Left = 0
    Top = 0
    Width = 121
    Height = 49
    Anchors = [akLeft, akBottom]
    Caption = 'TheGroupBox'
    TabOrder = 0
    object edtTo: TEdit
      Left = 64
      Top = 16
      Width = 33
      Height = 21
      ReadOnly = True
      TabOrder = 2
      Text = '5'
    end
    object edtFrom: TEdit
      Left = 8
      Top = 16
      Width = 33
      Height = 21
      ReadOnly = True
      TabOrder = 0
      Text = '-5'
    end
    object udwFrom: TUpDown
      Left = 41
      Top = 16
      Width = 15
      Height = 21
      Associate = edtFrom
      Min = -32768
      Position = -5
      TabOrder = 1
      Wrap = False
      OnClick = udwFromClick
    end
    object udwTo: TUpDown
      Left = 97
      Top = 16
      Width = 15
      Height = 21
      Associate = edtTo
      Min = -4
      Max = 32767
      Position = 5
      TabOrder = 3
      Wrap = False
    end
  end
end
