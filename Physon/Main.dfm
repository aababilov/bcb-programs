object PhysonForm: TPhysonForm
  Left = 0
  Top = 0
  BorderStyle = bsNone
  Caption = 'PhysonForm'
  ClientHeight = 480
  ClientWidth = 640
  Color = clBlack
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  KeyPreview = True
  OldCreateOrder = False
  OnKeyDown = SmplKeyDown
  PixelsPerInch = 96
  TextHeight = 13
  object FormImage: TImage
    Left = 0
    Top = 0
    Width = 773
    Height = 539
    Visible = False
  end
  object ThePanel: TPanel
    Left = 0
    Top = 0
    Width = 649
    Height = 465
    BevelOuter = bvNone
    ParentColor = True
    TabOrder = 0
    Visible = False
    OnMouseDown = ThePanelMouseDown
    object PanelImage: TImage
      Left = 0
      Top = 0
      Width = 649
      Height = 465
      Align = alClient
      OnMouseDown = PanelImageMouseDown1
    end
  end
  object plLeft: TPanel
    Left = 8
    Top = 448
    Width = 200
    Height = 30
    Alignment = taLeftJustify
    BevelOuter = bvNone
    Caption = #1057#1073#1080#1090#1086': 0'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = 16765920
    Font.Height = -24
    Font.Name = 'Georgia'
    Font.Style = []
    ParentColor = True
    ParentFont = False
    TabOrder = 1
    Visible = False
  end
  object plRight: TPanel
    Left = 208
    Top = 448
    Width = 200
    Height = 30
    Alignment = taLeftJustify
    BevelOuter = bvNone
    Caption = #1055#1088#1086#1087#1091#1097#1077#1085#1086': 0'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = 16765920
    Font.Height = -24
    Font.Name = 'Georgia'
    Font.Style = []
    ParentColor = True
    ParentFont = False
    TabOrder = 2
    Visible = False
  end
  object plTime: TPanel
    Left = 408
    Top = 448
    Width = 200
    Height = 30
    Alignment = taLeftJustify
    BevelOuter = bvNone
    Caption = '2:00'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = 16765920
    Font.Height = -24
    Font.Name = 'Georgia'
    Font.Style = []
    ParentColor = True
    ParentFont = False
    TabOrder = 3
    Visible = False
  end
end
