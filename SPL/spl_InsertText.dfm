object FormInsertText: TFormInsertText
  Left = 190
  Top = 105
  BorderIcons = [biSystemMenu]
  BorderStyle = bsSingle
  Caption = 'Insert Text'
  ClientHeight = 200
  ClientWidth = 321
  Color = 14869218
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  PixelsPerInch = 96
  TextHeight = 13
  object Label: TLabel
    Left = 4
    Top = 5
    Width = 135
    Height = 96
    BiDiMode = bdLeftToRight
    Caption = 'Label'
    Font.Charset = ARABIC_CHARSET
    Font.Color = clWindowText
    Font.Height = -64
    Font.Name = 'Traditional Arabic'
    Font.Style = []
    ParentBiDiMode = False
    ParentFont = False
  end
  object Panel1: TPanel
    Left = 0
    Top = 159
    Width = 321
    Height = 41
    Align = alBottom
    BevelOuter = bvNone
    Color = 14869218
    TabOrder = 0
    object BitBtn1: TBitBtn
      Left = 83
      Top = 8
      Width = 75
      Height = 25
      TabOrder = 0
      Kind = bkOK
    end
    object BitBtn2: TBitBtn
      Left = 163
      Top = 8
      Width = 75
      Height = 25
      TabOrder = 1
      Kind = bkCancel
    end
  end
  object RichEdit: TRichEdit
    Left = 0
    Top = 33
    Width = 321
    Height = 126
    Align = alClient
    BiDiMode = bdLeftToRight
    Font.Charset = ARABIC_CHARSET
    Font.Color = clWindowText
    Font.Height = -27
    Font.Name = 'Traditional Arabic'
    Font.Style = []
    Lines.Strings = (
      'WWPTC')
    ParentBiDiMode = False
    ParentFont = False
    TabOrder = 1
  end
  object Panel2: TPanel
    Left = 0
    Top = 0
    Width = 321
    Height = 33
    Align = alTop
    BevelOuter = bvNone
    Color = 14869218
    TabOrder = 2
    object ToolBar2: TToolBar
      Left = 112
      Top = 4
      Width = 93
      Height = 25
      Align = alNone
      AutoSize = True
      ButtonHeight = 21
      ButtonWidth = 89
      Caption = 'ToolBar1'
      EdgeBorders = [ebLeft, ebTop, ebRight, ebBottom]
      Flat = True
      ShowCaptions = True
      TabOrder = 0
      object ToolButton4: TToolButton
        Left = 0
        Top = 0
        Caption = 'Traditional Arabic'
        ImageIndex = 1
        OnClick = ToolButton4Click
      end
    end
  end
  object FontDialog: TFontDialog
    Font.Charset = ARABIC_CHARSET
    Font.Color = clWindowText
    Font.Height = -64
    Font.Name = 'Traditional Arabic'
    Font.Style = []
    MinFontSize = 0
    MaxFontSize = 0
    Options = [fdTrueTypeOnly, fdEffects]
    Left = 100
    Top = 88
  end
  object FormTranslation1: TFormTranslation
    Left = 136
    Top = 88
  end
end
