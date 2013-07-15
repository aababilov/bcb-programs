object Stand: TStand
  Left = 240
  Top = 200
  Width = 181
  Height = 134
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  Icon.Data = {
    0000010001002020100000000000E80200001600000028000000200000004000
    0000010004000000000080020000000000000000000000000000000000000000
    000000008000008000000080800080000000800080008080000080808000C0C0
    C0000000FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00CCCC
    CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC
    CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC000CCCCCCCCCCCCCCCCC000CCCCCC
    CC08880CCCCCCCCCCCCCCC08880CCCCCC0880880CCCCCCCCCCCCC0880880CCCC
    C0808080CCCCCCCCCCCCC0808080999990880880999999999999908808809999
    9908880999999999999999088809B9999990009999999999999999900099B999
    999999999999999999999999999999999999999999999999999999999999C999
    9999999999999999999999999999CC999999999999999999999999999999CCCC
    C99EEE0EEEEEEE1999EEEEEE1199CCCCCC99E0EEEEEEEE1999EEEEEE1999CCCC
    CCC99EEEEEEEEE1999EEEEEE199CCCCCCCCC99EEEEEEEE1999EEEEEE199CCCCC
    CCCCC99EEEEEEE1999EEEEEE99CCCCCCCCCCCC99EEEEEEE999EEEEEE99CCCCCC
    CCCCCCC99EEEEEE999EEEEE99CCCCCCCCCCCCCCC99999999999999999CCCCCCC
    CCCCCCCCC999999999999999CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC
    CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC
    CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC
    CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC
    CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC0000
    0000000000000000000000000000000000000000000000000000000000000000
    0000000000000000000000000000000000000000000000000000000000000000
    0000000000000000000000000000000000000000000000000000000000000000
    000000000000000000000000000000000000000000000000000000000000}
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object TurnLeft: TSpeedButton
    Left = 0
    Top = 0
    Width = 33
    Height = 33
    Flat = True
    Glyph.Data = {
      76020000424D7602000000000000760000002800000020000000200000000100
      0400000000000002000000000000000000001000000000000000000000000000
      8000008000000080800080000000800080008080000080808000C0C0C0000000
      FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00FFFFFFFFFFFF
      FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
      FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF0FFFFFFFFFFFFFFFFFFFFFFFFFFFFFF00
      FFFFFFFFFFFFFFFFFFFFFFFFFFFFF090FFFFFFFFFFFFFFFFFFFFFFFFFFFF0990
      FFFFFFFFFFFFFFFFFFFFFFFFFFF09990FFFFFFFFFFFFFFFFFFFFFFFFFF099990
      FFFFFFFFFFFFFFFFFFFFFFFFF0999990FFFFFFFFFFFFFFFFFFFFFFFF09999990
      00000000000000000000FFF09999999999999999999999999990FF0999999999
      99999999999999999990F0999999999999999999999999999990099999999999
      99999999999999999990F0999999999999999999999999999990FF0999999999
      99999999999999999990FFF09999999999999999999999999990FFFF09999990
      00000000000000000000FFFFF0999990FFFFFFFFFFFFFFFFFFFFFFFFFF099990
      FFFFFFFFFFFFFFFFFFFFFFFFFFF09990FFFFFFFFFFFFFFFFFFFFFFFFFFFF0990
      FFFFFFFFFFFFFFFFFFFFFFFFFFFFF090FFFFFFFFFFFFFFFFFFFFFFFFFFFFFF00
      FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF0FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
      FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
      FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
      FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF}
    OnClick = TurnLeftClick
  end
  object TurnRight: TSpeedButton
    Left = 64
    Top = 0
    Width = 33
    Height = 33
    Flat = True
    Glyph.Data = {
      76020000424D7602000000000000760000002800000020000000200000000100
      0400000000000002000000000000000000001000000000000000000000000000
      8000008000000080800080000000800080008080000080808000C0C0C0000000
      FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00FFFFFFFFFFFF
      FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
      FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF0FFFFFFFFFFFFFFFFFFFFFFF
      FFFFFFFF00FFFFFFFFFFFFFFFFFFFFFFFFFFFFFF090FFFFFFFFFFFFFFFFFFFFF
      FFFFFFFF0990FFFFFFFFFFFFFFFFFFFFFFFFFFFF09990FFFFFFFFFFFFFFFFFFF
      FFFFFFFF099990FFFFFFFFFFFFFFFFFFFFFFFFFF0999990FFFFF000000000000
      0000000009999990FFFF09999999999999999999999999990FFF099999999999
      999999999999999990FF0999999999999999999999999999990F099999999999
      999999999999999999900999999999999999999999999999990F099999999999
      999999999999999990FF09999999999999999999999999990FFF000000000000
      0000000009999990FFFFFFFFFFFFFFFFFFFFFFFF0999990FFFFFFFFFFFFFFFFF
      FFFFFFFF099990FFFFFFFFFFFFFFFFFFFFFFFFFF09990FFFFFFFFFFFFFFFFFFF
      FFFFFFFF0990FFFFFFFFFFFFFFFFFFFFFFFFFFFF090FFFFFFFFFFFFFFFFFFFFF
      FFFFFFFF00FFFFFFFFFFFFFFFFFFFFFFFFFFFFFF0FFFFFFFFFFFFFFFFFFFFFFF
      FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
      FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
      FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF}
    OnClick = TurnRightClick
  end
  object sbtnPause: TSpeedButton
    Left = 32
    Top = 0
    Width = 33
    Height = 33
    Flat = True
    Glyph.Data = {
      76020000424D7602000000000000760000002800000020000000200000000100
      0400000000000002000000000000000000001000000000000000000000000000
      8000008000000080800080000000800080008080000080808000C0C0C0000000
      FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00FFFFFFFFFFFF
      FFFFFFFFFFFFFFFFFFFFFFFFFFFCCCCCCFFFFFFCCCCCCFFFFFFFFFFFFFFCCCCC
      CFFFFFFCCCCCCFFFFFFFFFFFFFFCCCCCCFFFFFFCCCCCCFFFFFFFFFFFFFFCCCCC
      CFFFFFFCCCCCCFFFFFFFFFFFFFFCCCCCCFFFFFFCCCCCCFFFFFFFFFFFFFFCCCCC
      CFFFFFFCCCCCCFFFFFFFFFFFFFFCCCCCCFFFFFFCCCCCCFFFFFFFFFFFFFFCCCCC
      CFFFFFFCCCCCCFFFFFFFFFFFFFFCCCCCCFFFFFFCCCCCCFFFFFFFFFFFFFFCCCCC
      CFFFFFFCCCCCCFFFFFFFFFFFFFFCCCCCCFFFFFFCCCCCCFFFFFFFFFFFFFFCCCCC
      CFFFFFFCCCCCCFFFFFFFFFFFFFFCCCCCCFFFFFFCCCCCCFFFFFFFFFFFFFFCCCCC
      CFFFFFFCCCCCCFFFFFFFFFFFFFFCCCCCCFFFFFFCCCCCCFFFFFFFFFFFFFFCCCCC
      CFFFFFFCCCCCCFFFFFFFFFFFFFFCCCCCCFFFFFFCCCCCCFFFFFFFFFFFFFFCCCCC
      CFFFFFFCCCCCCFFFFFFFFFFFFFFCCCCCCFFFFFFCCCCCCFFFFFFFFFFFFFFCCCCC
      CFFFFFFCCCCCCFFFFFFFFFFFFFFCCCCCCFFFFFFCCCCCCFFFFFFFFFFFFFFCCCCC
      CFFFFFFCCCCCCFFFFFFFFFFFFFFCCCCCCFFFFFFCCCCCCFFFFFFFFFFFFFFCCCCC
      CFFFFFFCCCCCCFFFFFFFFFFFFFFCCCCCCFFFFFFCCCCCCFFFFFFFFFFFFFFCCCCC
      CFFFFFFCCCCCCFFFFFFFFFFFFFFCCCCCCFFFFFFCCCCCCFFFFFFFFFFFFFFCCCCC
      CFFFFFFCCCCCCFFFFFFFFFFFFFFCCCCCCFFFFFFCCCCCCFFFFFFFFFFFFFFCCCCC
      CFFFFFFCCCCCCFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF}
    OnClick = sbtnPauseClick
  end
  object Slower: TSpeedButton
    Left = 136
    Top = 32
    Width = 33
    Height = 33
    Flat = True
    Glyph.Data = {
      76020000424D7602000000000000760000002800000020000000200000000100
      0400000000000002000000000000000000001000000000000000000000000000
      8000008000000080800080000000800080008080000080808000C0C0C0000000
      FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00FFFFFFFFFFFF
      FFF0FFFFFFFFFFFFFFFFFFFFFFFFFFFFFF090FFFFFFFFFFFFFFFFFFFFFFFFFFF
      F09990FFFFFFFFFFFFFFFFFFFFFFFFFF0999990FFFFFFFFFFFFFFFFFFFFFFFF0
      99999990FFFFFFFFFFFFFFFFFFFFFF09999999990FFFFFFFFFFFFFFFFFFFF099
      9999999990FFFFFFFFFFFFFFFFFF099999999999990FFFFFFFFFFFFFFFF09999
      999999999990FFFFFFFFFFFFFF0999999999999999990FFFFFFFFFFFF0999999
      99999999999990FFFFFFFFFF09999999999999999999990FFFFFFFF000000009
      9999999900000000FFFFFFFFFFFFF0999999999990FFFFFFFFFFFFFFFFFF0999
      99999999990FFFFFFFFFFFFFFFF09999999999999990FFFFFFFFFFFFFF099999
      9999999999990FFFFFFFFFFFF099999999999999999990FFFFFFFFFF09999999
      999999999999990FFFFFFFF0000000009999999000000000FFFFFFFFFFFFFFF0
      99999990FFFFFFFFFFFFFFFFFFFFFFF099999990FFFFFFFFFFFFFFFFFFFFFFF0
      99999990FFFFFFFFFFFFFFFFFFFFFFF099999990FFFFFFFFFFFFFFFFFFFFFFF0
      99999990FFFFFFFFFFFFFFFFFFFFFFF099999990FFFFFFFFFFFFFFFFFFFFFFF0
      99999990FFFFFFFFFFFFFFFFFFFFFFF099999990FFFFFFFFFFFFFFFFFFFFFFF0
      99999990FFFFFFFFFFFFFFFFFFFFFFF099999990FFFFFFFFFFFFFFFFFFFFFFF0
      99999990FFFFFFFFFFFFFFFFFFFFFFF000000000FFFFFFFFFFFF}
    OnClick = SlowerClick
  end
  object Quicker: TSpeedButton
    Left = 136
    Top = 0
    Width = 33
    Height = 33
    Flat = True
    Glyph.Data = {
      76020000424D7602000000000000760000002800000020000000200000000100
      0400000000000002000000000000000000001000000000000000000000000000
      8000008000000080800080000000800080008080000080808000C0C0C0000000
      FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00FFFFFFFFFFF0
      00000000FFFFFFFFFFFFFFFFFFFFFFF099999990FFFFFFFFFFFFFFFFFFFFFFF0
      99999990FFFFFFFFFFFFFFFFFFFFFFF099999990FFFFFFFFFFFFFFFFFFFFFFF0
      99999990FFFFFFFFFFFFFFFFFFFFFFF099999990FFFFFFFFFFFFFFFFFFFFFFF0
      99999990FFFFFFFFFFFFFFFFFFFFFFF099999990FFFFFFFFFFFFFFFFFFFFFFF0
      99999990FFFFFFFFFFFFFFFFFFFFFFF099999990FFFFFFFFFFFFFFFFFFFFFFF0
      99999990FFFFFFFFFFFFFFFFFFFFFFF099999990FFFFFFFFFFFFFFF000000000
      9999999000000000FFFFFFFF09999999999999999999990FFFFFFFFFF0999999
      99999999999990FFFFFFFFFFFF0999999999999999990FFFFFFFFFFFFFF09999
      999999999990FFFFFFFFFFFFFFFF099999999999990FFFFFFFFFFFFFFFFFF099
      9999999990FFFFFFFFFFFFF0000000099999999900000000FFFFFFFF09999999
      999999999999990FFFFFFFFFF099999999999999999990FFFFFFFFFFFF099999
      9999999999990FFFFFFFFFFFFFF09999999999999990FFFFFFFFFFFFFFFF0999
      99999999990FFFFFFFFFFFFFFFFFF0999999999990FFFFFFFFFFFFFFFFFFFF09
      999999990FFFFFFFFFFFFFFFFFFFFFF099999990FFFFFFFFFFFFFFFFFFFFFFFF
      0999990FFFFFFFFFFFFFFFFFFFFFFFFFF09990FFFFFFFFFFFFFFFFFFFFFFFFFF
      FF090FFFFFFFFFFFFFFFFFFFFFFFFFFFFFF0FFFFFFFFFFFFFFFF}
    OnClick = QuickerClick
  end
  object TurnBack: TSpeedButton
    Left = 32
    Top = 32
    Width = 33
    Height = 33
    Glyph.Data = {
      76020000424D7602000000000000760000002800000020000000200000000100
      0400000000000002000000000000000000001000000000000000000000000000
      8000008000000080800080000000800080008080000080808000C0C0C0000000
      FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00FFFFFFFFFFFF
      FFF0FFFFFFFFFFFFFFFFFFFFFFFFFFFFFF090FFFFFFFFFFFFFFFFFFFFFFFFFFF
      F09990FFFFFFFFFFFFFFFFFFFFFFFFFF0999990FFFFFFFFFFFFFFFFFFFFFFFF0
      99999990FFFFFFFFFFFFFFFFFFFFFF09999999990FFFFFFFFFFFFFFFFFFFF099
      9999999990FFFFFFFFFFFFFFFFFF099999999999990FFFFFFFFFFFFFFFF09999
      999999999990FFFFFFFFFFFFFF0999999999999999990FFFFFFFFFFFF0999999
      99999999999990FFFFFFFFFF09999999999999999999990FFFFFFFF000000000
      9999999000000000FFFFFFFFFFFFFFF099999990FFFFFFFFFFFFFFFFFFFFFFF0
      99999990FFFFFFFFFFFFFFFFFFFFFFF099999990FFFFFFFFFFFFFFFFFFFFFFF0
      99999990FFFFFFFFFFFFFFFFFFFFFFF099999990FFFFFFFFFFFFFFFFFFFFFFF0
      99999990FFFFFFFFFFFFFFFFFFFFFFF099999990FFFFFFFFFFFFFFFFFFFFFFF0
      99999990FFFFFFFFFFFFFFFFFFFFFFF099999990FFFFFFFFFFFFFFFFFFFFFFF0
      99999990FFFFFFFFFFFFFFFFFFFFFFF099999990FFFFFFFFFFFFFFFFFFFFFFF0
      99999990FFFFFFFFFFFFFFFFFFFFFFF099999990FFFFFFFFFFFFFFFFFFFFFFF0
      99999990FFFFFFFFFFFFFFFFFFFFFFF099999990FFFFFFFFFFFFFFFFFFFFFFF0
      99999990FFFFFFFFFFFFFFFFFFFFFFF099999990FFFFFFFFFFFFFFFFFFFFFFF0
      99999990FFFFFFFFFFFFFFFFFFFFFFF000000000FFFFFFFFFFFF}
    OnClick = TurnBackClick
  end
  object Go: TTimer
    Interval = 20
    OnTimer = GoTimer
    Left = 96
    Top = 64
  end
end