object AdjGameForm: TAdjGameForm
  Left = 0
  Top = 118
  BorderStyle = bsNone
  Caption = 'AdjGameForm'
  ClientHeight = 271
  ClientWidth = 1016
  Color = clBtnFace
  Font.Charset = ANSI_CHARSET
  Font.Color = clWindowText
  Font.Height = -32
  Font.Name = 'Arial'
  Font.Style = []
  OldCreateOrder = False
  OnDestroy = FormDestroy
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 36
  object Field: TImage
    Left = 0
    Top = 0
    Width = 1016
    Height = 153
    Align = alTop
    OnMouseMove = ProcessMove
  end
  object plLeadCard: TPanel
    Left = 7
    Top = 168
    Width = 1002
    Height = 89
    BevelInner = bvLowered
    BevelOuter = bvNone
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -32
    Font.Name = 'Georgia'
    Font.Style = []
    ParentFont = False
    TabOrder = 0
    object CrdWhite: TImage
      Left = 16
      Top = 16
      Width = 153
      Height = 57
    end
    object CrdBlack: TImage
      Left = 840
      Top = 16
      Width = 153
      Height = 57
    end
  end
end
