object FormProgress: TFormProgress
  Left = 490
  Top = 218
  BorderIcons = []
  BorderStyle = bsNone
  Caption = 'Progress'
  ClientHeight = 56
  ClientWidth = 278
  Color = 14869218
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  FormStyle = fsStayOnTop
  OldCreateOrder = False
  Position = poScreenCenter
  PixelsPerInch = 96
  TextHeight = 13
  object Panel1: TPanel
    Left = 4
    Top = 4
    Width = 271
    Height = 22
    BevelInner = bvLowered
    Caption = 'Loading...'
    TabOrder = 0
  end
  object Panel2: TPanel
    Left = 4
    Top = 28
    Width = 271
    Height = 22
    TabOrder = 1
    object ProgressBar1: TProgressBar
      Left = 3
      Top = 3
      Width = 265
      Height = 16
      Min = 0
      Max = 100
      TabOrder = 0
    end
  end
  object FormTranslation1: TFormTranslation
    Left = 128
    Top = 8
  end
end
