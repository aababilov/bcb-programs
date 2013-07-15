object Form1: TForm1
  Left = 293
  Top = 38
  Caption = 'Ice'
  ClientHeight = 555
  ClientWidth = 506
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  KeyPreview = True
  OldCreateOrder = False
  Position = poDesigned
  OnDestroy = FormDestroy
  OnKeyDown = FormKeyDown
  OnPaint = Repainting
  OnResize = Repainting
  OnShow = Repainting
  DesignSize = (
    506
    555)
  PixelsPerInch = 96
  TextHeight = 13
  object ViewPanel: TPanel
    Left = 0
    Top = 0
    Width = 506
    Height = 505
    Align = alTop
    Anchors = [akLeft, akTop, akRight, akBottom]
    Color = clBlack
    TabOrder = 0
    OnMouseDown = ViewPanelMouseDown
    OnMouseMove = ViewPanelMouseMove
  end
  object Start: TButton
    Left = 8
    Top = 522
    Width = 75
    Height = 25
    Anchors = [akLeft, akBottom]
    Caption = 'Start'
    TabOrder = 1
    OnClick = StartClick
  end
  object btnChangeTimer: TButton
    Left = 89
    Top = 522
    Width = 75
    Height = 25
    Anchors = [akLeft, akBottom]
    Caption = 'Pause'
    TabOrder = 2
    OnClick = btnChangeTimerClick
  end
  object Timer1: TTimer
    Enabled = False
    Interval = 100
    OnTimer = Timer1Timer
    Left = 16
    Top = 16
  end
end
