object DataEditorForm: TDataEditorForm
  Left = 180
  Top = 149
  BorderStyle = bsSingle
  Caption = 'DataEditorForm'
  ClientHeight = 199
  ClientWidth = 322
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  FormStyle = fsStayOnTop
  OldCreateOrder = False
  Position = poScreenCenter
  OnDestroy = FormDestroy
  PixelsPerInch = 96
  TextHeight = 13
  object EditorPages: TPageControl
    Left = 0
    Top = 0
    Width = 322
    Height = 199
    ActivePage = pgWords
    Align = alClient
    TabIndex = 1
    TabOrder = 0
    object pgPassword: TTabSheet
      Caption = '&Password'
      object edtCurrPassword: TLabeledEdit
        Left = 72
        Top = 32
        Width = 161
        Height = 21
        EditLabel.Width = 82
        EditLabel.Height = 13
        EditLabel.Caption = '&Current password'
        LabelPosition = lpAbove
        LabelSpacing = 3
        MaxLength = 16
        PasswordChar = '*'
        TabOrder = 0
      end
      object edtNewPassword: TLabeledEdit
        Left = 72
        Top = 80
        Width = 161
        Height = 21
        EditLabel.Width = 70
        EditLabel.Height = 13
        EditLabel.Caption = '&New password'
        LabelPosition = lpAbove
        LabelSpacing = 3
        PasswordChar = '*'
        TabOrder = 1
      end
      object btnSetPassword: TButton
        Left = 112
        Top = 120
        Width = 75
        Height = 25
        Caption = 'OK'
        Default = True
        TabOrder = 2
        OnClick = btnSetPasswordClick
      end
    end
    object pgWords: TTabSheet
      Caption = '&Words'
      ImageIndex = 1
      object gbSuffixes: TGroupBox
        Left = 8
        Top = 8
        Width = 145
        Height = 153
        Caption = 'Suffixes'
        TabOrder = 0
        object lwSuffixes: TListView
          Left = 8
          Top = 16
          Width = 129
          Height = 129
          Columns = <>
          Font.Charset = ANSI_CHARSET
          Font.Color = clWindowText
          Font.Height = -13
          Font.Name = 'Arial'
          Font.Style = []
          ParentFont = False
          TabOrder = 0
          ViewStyle = vsList
          OnSelectItem = lwSuffixesSelectItem
        end
      end
      object gbRoots: TGroupBox
        Left = 160
        Top = 8
        Width = 145
        Height = 153
        Caption = 'Roots'
        TabOrder = 1
        object lwRoots: TListView
          Left = 8
          Top = 16
          Width = 129
          Height = 129
          Columns = <>
          Font.Charset = ANSI_CHARSET
          Font.Color = clWindowText
          Font.Height = -13
          Font.Name = 'Arial'
          Font.Style = []
          ParentFont = False
          TabOrder = 0
          ViewStyle = vsList
          OnEdited = lwRootsEdited
        end
      end
    end
    object pgHosts: TTabSheet
      Caption = '&Hosts'
      ImageIndex = 2
      object lwHosts: TListView
        Left = 0
        Top = 0
        Width = 313
        Height = 169
        Columns = <>
        PopupMenu = HostMenu
        TabOrder = 0
        ViewStyle = vsList
      end
    end
  end
  object HostMenu: TPopupMenu
    Left = 112
    Top = 40
    object miAdd: TMenuItem
      Caption = '&Add'
      ShortCut = 45
      OnClick = AddHost
    end
    object miDelete: TMenuItem
      Caption = '&Delete'
      ShortCut = 16430
      OnClick = DeleteHost
    end
  end
end
