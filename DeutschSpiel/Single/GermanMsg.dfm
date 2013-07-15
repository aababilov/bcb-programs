object MsgForm: TMsgForm
  Left = 192
  Top = 107
  BorderStyle = bsDialog
  Caption = 'MsgForm'
  ClientHeight = 86
  ClientWidth = 318
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Georgia'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  PixelsPerInch = 96
  TextHeight = 14
  object lblText: TLabel
    Left = 56
    Top = 8
    Width = 250
    Height = 14
    Alignment = taCenter
    AutoSize = False
  end
  object Img: TImage
    Left = 8
    Top = 8
    Width = 32
    Height = 32
  end
  object BitBtn1: TBitBtn
    Left = 120
    Top = 48
    Width = 75
    Height = 25
    TabOrder = 0
    Kind = bkOK
  end
end
