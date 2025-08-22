object FormMain: TFormMain
  Left = 180
  Top = 121
  Width = 696
  Height = 482
  Caption = 'Skeleton'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  Menu = MainMenu1
  OldCreateOrder = False
  OnCreate = FormCreate
  OnDestroy = FormDestroy
  PixelsPerInch = 96
  TextHeight = 13
  object ScrollBox1: TScrollBox
    Left = 0
    Top = 0
    Width = 680
    Height = 404
    Align = alClient
    TabOrder = 0
    object Image: TImage
      Left = 0
      Top = 0
      Width = 105
      Height = 105
      AutoSize = True
    end
  end
  object StatusBar1: TStatusBar
    Left = 0
    Top = 404
    Width = 680
    Height = 19
    Panels = <>
    SimplePanel = False
  end
  object MainMenu1: TMainMenu
    Left = 216
    Top = 124
    object File1: TMenuItem
      Caption = '&File'
      object Open1: TMenuItem
        Caption = '&Open...'
        OnClick = Open1Click
      end
      object N1: TMenuItem
        Caption = '-'
      end
      object Saveas1: TMenuItem
        Caption = 'Save &as...'
        OnClick = Saveas1Click
      end
      object N2: TMenuItem
        Caption = '-'
      end
      object Exit1: TMenuItem
        Caption = 'E&xit'
        ShortCut = 16472
        OnClick = Exit1Click
      end
    end
    object Operations1: TMenuItem
      Caption = '&Operations'
      object Skeletonize1: TMenuItem
        Caption = '&Skeletonize'
        OnClick = Skeletonize1Click
      end
    end
  end
  object OpenPictureDialog: TOpenPictureDialog
    DefaultExt = 'bmp'
    Options = [ofOverwritePrompt, ofHideReadOnly, ofEnableSizing]
    Left = 216
    Top = 152
  end
  object SavePictureDialog: TSavePictureDialog
    Options = [ofOverwritePrompt, ofHideReadOnly, ofEnableSizing]
    Left = 244
    Top = 152
  end
end
