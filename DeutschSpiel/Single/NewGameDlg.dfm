object EndGameForm: TEndGameForm
  Left = 299
  Top = 221
  BorderStyle = bsDialog
  Caption = #1048#1075#1088#1072' '#1079#1072#1082#1086#1085#1095#1080#1083#1072#1089#1100
  ClientHeight = 151
  ClientWidth = 202
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -13
  Font.Name = 'Georgia'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 16
  object lblNewGame: TLabel
    Left = 32
    Top = 96
    Width = 132
    Height = 16
    Caption = #1053#1072#1095#1072#1090#1100' '#1085#1086#1074#1091#1102' '#1080#1075#1088#1091'?'
  end
  object lblWon: TLabel
    Left = 8
    Top = 32
    Width = 185
    Height = 16
    Alignment = taCenter
    AutoSize = False
    Caption = 'lblWon'
  end
  object BitBtn1: TBitBtn
    Left = 8
    Top = 120
    Width = 89
    Height = 25
    Caption = '&'#1044#1072
    TabOrder = 0
    Kind = bkYes
  end
  object BitBtn2: TBitBtn
    Left = 104
    Top = 120
    Width = 89
    Height = 25
    Cancel = True
    Caption = '&'#1042#1099#1081#1090#1080
    ModalResult = 7
    TabOrder = 1
    Glyph.Data = {
      DE010000424DDE01000000000000760000002800000024000000120000000100
      0400000000006801000000000000000000001000000000000000000000000000
      80000080000000808000800000008000800080800000C0C0C000808080000000
      FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00388888888877
      F7F787F8888888888333333F00004444400888FFF444448888888888F333FF8F
      000033334D5007FFF4333388888888883338888F0000333345D50FFFF4333333
      338F888F3338F33F000033334D5D0FFFF43333333388788F3338F33F00003333
      45D50FEFE4333333338F878F3338F33F000033334D5D0FFFF43333333388788F
      3338F33F0000333345D50FEFE4333333338F878F3338F33F000033334D5D0FFF
      F43333333388788F3338F33F0000333345D50FEFE4333333338F878F3338F33F
      000033334D5D0EFEF43333333388788F3338F33F0000333345D50FEFE4333333
      338F878F3338F33F000033334D5D0EFEF43333333388788F3338F33F00003333
      4444444444333333338F8F8FFFF8F33F00003333333333333333333333888888
      8888333F00003333330000003333333333333FFFFFF3333F00003333330AAAA0
      333333333333888888F3333F00003333330000003333333333338FFFF8F3333F
      0000}
    NumGlyphs = 2
  end
end
