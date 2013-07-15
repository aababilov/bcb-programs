object SudokuForm: TSudokuForm
  Left = 206
  Top = 57
  Width = 674
  Height = 631
  Caption = 'SudokuForm'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -13
  Font.Name = 'Courier New'
  Font.Style = []
  Menu = MainMnu
  OldCreateOrder = False
  OnMouseUp = FormMouseUp
  OnPaint = FormPaint
  PixelsPerInch = 96
  TextHeight = 16
  object OpenDlg: TOpenDialog
    DefaultExt = '.sdk'
    Filter = 'Sudoku files (*.sdk)|*.sdk|All files (*.*)|*.*'
    Left = 8
    Top = 8
  end
  object MainMnu: TMainMenu
    Left = 72
    Top = 8
    object miFile: TMenuItem
      Caption = '&File'
      object miOpen: TMenuItem
        Caption = '&Open'
        ShortCut = 79
        OnClick = miOpenClick
      end
      object miSave: TMenuItem
        Caption = '&Save'
        ShortCut = 83
        OnClick = miSaveClick
      end
    end
    object miWork: TMenuItem
      Caption = '&Work'
      object miExtgo: TMenuItem
        Caption = '&Ext go'
        ShortCut = 69
        OnClick = miExtgoClick
      end
      object miGo: TMenuItem
        Caption = '&Go'
        ShortCut = 71
        OnClick = miGoClick
      end
      object miByStep: TMenuItem
        AutoCheck = True
        Caption = '&By step'
        Checked = True
        ShortCut = 66
      end
    end
  end
  object SaveDlg: TSaveDialog
    DefaultExt = '.sdk'
    Filter = 'Sudoku files (*.sdk)|*.sdk|All files (*.*)|*.*'
    Left = 40
    Top = 8
  end
end
