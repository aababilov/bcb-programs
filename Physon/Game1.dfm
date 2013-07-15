object Game1Form: TGame1Form
  Left = 0
  Top = 0
  BorderStyle = bsNone
  Caption = 'Game1Form'
  ClientHeight = 480
  ClientWidth = 640
  Color = clYellow
  TransparentColor = True
  TransparentColorValue = clYellow
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -19
  Font.Name = 'Times New Roman'
  Font.Style = []
  FormStyle = fsStayOnTop
  OldCreateOrder = False
  OnClose = FormClose
  PixelsPerInch = 96
  TextHeight = 21
  object plInfo: TPanel
    Left = 344
    Top = 304
    Width = 289
    Height = 169
    BevelInner = bvLowered
    BevelWidth = 8
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -21
    Font.Name = 'Times New Roman'
    Font.Style = []
    ParentFont = False
    TabOrder = 0
    object lblCapWhite: TLabel
      Left = 32
      Top = 40
      Width = 60
      Height = 23
      Caption = #1041#1077#1083#1099#1077':'
    end
    object lblCapBlack: TLabel
      Left = 32
      Top = 104
      Width = 73
      Height = 23
      Caption = #1063#1105#1088#1085#1099#1077':'
    end
    object lblCapLead: TLabel
      Left = 176
      Top = 40
      Width = 42
      Height = 23
      Caption = #1061#1086#1076':'
    end
    object lblScWhite: TLabel
      Left = 112
      Top = 40
      Width = 33
      Height = 23
      Alignment = taRightJustify
      AutoSize = False
      Caption = '0'
    end
    object lblScBlack: TLabel
      Left = 112
      Top = 104
      Width = 33
      Height = 23
      Alignment = taRightJustify
      AutoSize = False
      Caption = '0'
    end
    object lblLead: TLabel
      Left = 224
      Top = 40
      Width = 33
      Height = 23
      Alignment = taRightJustify
      AutoSize = False
      Caption = '1'
    end
  end
  object plBoard: TPanel
    Left = 344
    Top = 8
    Width = 289
    Height = 289
    BevelInner = bvLowered
    BevelWidth = 8
    TabOrder = 1
    object FieldView: TPaintBox
      Left = 16
      Top = 16
      Width = 257
      Height = 257
      Color = clWhite
      ParentColor = False
      OnMouseDown = FieldImageMouseDown
      OnMouseMove = FieldViewMouseMove
      OnPaint = FieldViewPaint
    end
  end
  object plRules: TPanel
    Left = 7
    Top = 8
    Width = 330
    Height = 465
    BevelInner = bvLowered
    BevelWidth = 8
    TabOrder = 2
    object lblRules1: TLabel
      Left = 24
      Top = 48
      Width = 276
      Height = 126
      Caption = 
        '  '#1051#1072#1076#1100#1080' - '#1095#1105#1088#1085#1072#1103' ('#1077#1081' '#1080#1075#1088#1072#1077#1090' '#1082#1086#1084#1087#1100#1102#1090#1077#1088') '#1080' '#1073#1077#1083#1072#1103' ('#1077#1081' '#1080#1075#1088#1072#1077#1090#1077' '#1042#1099') -' +
        ' '#1093#1086#1076#1103#1090' '#1087#1086' '#1086#1095#1077#1088#1077#1076#1080'. '#1063#1090#1086#1073#1099' '#1089#1076#1077#1083#1072#1090#1100' '#1093#1086#1076', '#1097#1077#1083#1082#1085#1080#1090#1077' '#1084#1099#1096#1100#1102' '#1085#1072' '#1082#1083#1077#1090#1082#1077', ' +
        #1074' '#1082#1086#1090#1086#1088#1091#1102' '#1042#1099' '#1093#1086#1090#1080#1090#1077' '#1087#1086#1084#1077#1089#1090#1080#1090#1100' '#1083#1072#1076#1100#1102'.'
      WordWrap = True
    end
    object lblTitle: TLabel
      Left = 96
      Top = 16
      Width = 160
      Height = 31
      Caption = #1055#1088#1072#1074#1080#1083#1072' '#1080#1075#1088#1099
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -27
      Font.Name = 'Times New Roman'
      Font.Style = []
      ParentFont = False
    end
    object lblRules4: TLabel
      Left = 24
      Top = 296
      Width = 287
      Height = 147
      Caption = 
        '  '#1044#1083#1103' '#1087#1086#1073#1077#1076#1099' '#1085#1077#1086#1073#1093#1086#1076#1080#1084#1086' '#1089#1098#1077#1089#1090#1100' '#1073#1086#1083#1100#1096#1077' '#1087#1077#1096#1077#1082', '#1095#1077#1084' '#1095#1105#1088#1085#1072#1103' '#1090#1091#1088#1072' - '#1080 +
        ' '#1085#1077' '#1087#1086#1087#1072#1089#1090#1100#1089#1103' '#1077#1081', '#1080#1085#1072#1095#1077' '#1042#1099' '#1087#1088#1086#1080#1075#1088#1072#1077#1090#1077'! '#1048#1075#1088#1072' '#1079#1072#1082#1086#1085#1095#1080#1090#1089#1103', '#1077#1089#1083#1080' '#1074#1089#1077 +
        ' '#1087#1077#1096#1082#1080' '#1073#1091#1076#1091#1090' '#1089#1098#1077#1076#1077#1085#1099', '#1087#1088#1086#1081#1076#1105#1090' 20 '#1093#1086#1076#1086#1074' '#1080#1083#1080' '#1095#1105#1088#1085#1072#1103' '#1083#1072#1076#1100#1103' '#1089#1098#1077#1089#1090' '#1073#1077 +
        #1083#1091#1102'.'
      WordWrap = True
    end
    object lblRules3: TLabel
      Left = 24
      Top = 264
      Width = 226
      Height = 21
      Caption = '  '#1055#1077#1088#1074#1086#1081' '#1093#1086#1076#1080#1090' '#1073#1077#1083#1072#1103' '#1083#1072#1076#1100#1103'.'
    end
    object lblRules2: TLabel
      Left = 24
      Top = 176
      Width = 287
      Height = 84
      Caption = 
        '  '#1051#1072#1076#1100#1103' '#1093#1086#1076#1080#1090' '#1087#1086' '#1075#1086#1088#1080#1079#1086#1085#1090#1072#1083#1080' '#1083#1080#1073#1086' '#1087#1086' '#1074#1077#1088#1090#1080#1082#1072#1083#1080' '#1085#1072' '#1083#1102#1073#1086#1077' '#1082#1086#1083#1080#1095#1077#1089#1090 +
        #1074#1086' '#1082#1083#1077#1090#1086#1082', '#1085#1086' '#1085#1077#1083#1100#1079#1103' '#1087#1077#1088#1077#1087#1088#1099#1075#1080#1074#1072#1090#1100' '#1095#1077#1088#1077#1079' '#1079#1072#1085#1103#1090#1099#1077' '#1087#1086#1083#1103'.'
      WordWrap = True
    end
  end
end
