object FormRasterImage: TFormRasterImage
  Left = 190
  Top = 127
  Width = 544
  Height = 375
  Caption = 'Raster Image'
  Color = 12639424
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  Menu = MainMenu1
  OldCreateOrder = False
  OnCreate = FormCreate
  OnDestroy = FormDestroy
  OnKeyDown = FormKeyDown
  PixelsPerInch = 96
  TextHeight = 13
  object ScrollBox1: TScrollBox
    Left = 0
    Top = 18
    Width = 536
    Height = 292
    HorzScrollBar.Tracking = True
    VertScrollBar.Tracking = True
    Align = alClient
    Color = 12639424
    ParentColor = False
    TabOrder = 0
    object Image: TImage
      Left = 0
      Top = 0
      Width = 100
      Height = 100
      Cursor = crArrow
      AutoSize = True
      OnMouseDown = ImageMouseDown
      OnMouseMove = ImageMouseMove
      OnMouseUp = ImageMouseUp
    end
  end
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 536
    Height = 18
    Align = alTop
    AutoSize = True
    TabOrder = 1
    object ProgressBar: TProgressBar
      Left = 1
      Top = 1
      Width = 534
      Height = 16
      Align = alClient
      Min = 0
      Max = 100
      TabOrder = 0
    end
  end
  object StatusBar: TStatusBar
    Left = 0
    Top = 310
    Width = 536
    Height = 19
    Color = 14869218
    Panels = <
      item
        Alignment = taCenter
        Text = '0000,0000'
        Width = 60
      end
      item
        Alignment = taCenter
        Text = '000,000,000'
        Width = 70
      end
      item
        Alignment = taCenter
        Text = '0000x0000x00'
        Width = 80
      end
      item
        Alignment = taCenter
        Text = '000'
        Width = 30
      end
      item
        Alignment = taCenter
        Text = 'Hint'
        Width = 50
      end>
    SimplePanel = False
  end
  object MainMenu1: TMainMenu
    AutoHotkeys = maManual
    AutoLineReduction = maManual
    Left = 184
    Top = 140
    object File1: TMenuItem
      Action = AFile
      object ImportImage1: TMenuItem
        Action = AOpenImage
      end
      object Open1: TMenuItem
        Action = AImportImage
      end
      object RestoreImage1: TMenuItem
        Action = ARestoreImage
      end
      object Save1: TMenuItem
        Action = ASaveImage
      end
    end
    object Imaging2: TMenuItem
      Action = AImaging
      object Quantize2: TMenuItem
        Action = AQuantize
      end
      object Smooth2: TMenuItem
        Action = ASmooth
      end
      object Resize1: TMenuItem
        Action = AResize
      end
      object Invert2: TMenuItem
        Action = AInvert
      end
      object Reverse2: TMenuItem
        Action = AReverse
      end
      object Gray1: TMenuItem
        Action = AGray
      end
      object Monochrome1: TMenuItem
        Action = AMonochrome
      end
    end
    object Help1: TMenuItem
      Action = AHelp
      object Contents1: TMenuItem
        Action = AContents
      end
      object N2: TMenuItem
        Caption = '-'
      end
      object About1: TMenuItem
        Action = AAbout
      end
    end
  end
  object Timer1: TTimer
    Enabled = False
    Interval = 1
    Left = 222
    Top = 134
  end
  object SavePictureDialog1: TSavePictureDialog
    DefaultExt = 'bmp'
    Left = 155
    Top = 64
  end
  object ActionList1: TActionList
    Left = 234
    Top = 64
    object AFile: TAction
      Category = 'File'
      Caption = '&File'
      Hint = 'File menu'
      OnExecute = AFileExecute
    end
    object AOpenImage: TAction
      Category = 'File'
      Caption = '&Open Image...'
      Hint = 'Open new image from file'
      OnExecute = AOpenImageExecute
    end
    object AImportImage: TAction
      Category = 'File'
      Caption = '&Import Image...'
      Hint = 'Import new image by scanner devices'
      OnExecute = AImportImageExecute
    end
    object ASaveImage: TAction
      Category = 'File'
      Caption = '&Save Image...'
      Hint = 'Save image to file'
      OnExecute = ASaveImageExecute
    end
    object AImaging: TAction
      Category = 'Imaging'
      Caption = '&Imaging'
      Hint = 'Imaging Menu'
      OnExecute = AImagingExecute
    end
    object AResize: TAction
      Category = 'Imaging'
      Caption = '&Resize'
      Hint = 'Resize the image'
      OnExecute = AResizeExecute
    end
    object ARestoreImage: TAction
      Category = 'File'
      Caption = '&Restore Image'
      Hint = 'Restore image'
      ShortCut = 116
      OnExecute = ARestoreImageExecute
    end
    object AInvert: TAction
      Category = 'Imaging'
      Caption = '&Invert'
      Hint = 'Invert the image colors'
      OnExecute = AInvertExecute
    end
    object ASmooth: TAction
      Category = 'Imaging'
      Caption = '&Smooth'
      Hint = 'Smooth the image'
      OnExecute = ASmoothExecute
    end
    object AReverse: TAction
      Category = 'Imaging'
      Caption = 'Rever&se'
      Hint = 'Reverse the image'
      OnExecute = AReverseExecute
    end
    object AQuantize: TAction
      Category = 'Imaging'
      Caption = '&Quantize'
      Hint = 'Quantize the image colors'
      OnExecute = AQuantizeExecute
    end
    object ADigitizer: TAction
      Category = 'Digitizer'
      Caption = '&Digitizer'
      Hint = 'Digitizer menu'
      OnExecute = ADigitizerExecute
    end
    object ADigitize: TAction
      Category = 'Digitizer'
      Caption = '&Digitize'
      Hint = 'Digitize the image (Convert from raster to vector)'
      OnExecute = ADigitizeExecute
    end
    object AGray: TAction
      Category = 'Imaging'
      Caption = '&Gray'
      Hint = 'Convert image colors to gray'
      OnExecute = AGrayExecute
    end
    object AHelp: TAction
      Category = 'Help'
      Caption = '&Help'
      Hint = 'Help menu'
      OnExecute = AHelpExecute
    end
    object AContents: TAction
      Category = 'Help'
      Caption = '&Contents'
      Hint = 'Show help contents'
      OnExecute = AContentsExecute
    end
    object AAbout: TAction
      Category = 'Help'
      Caption = '&About'
      Hint = 'Show about dialoge'
      OnExecute = AAboutExecute
    end
    object AMonochrome: TAction
      Category = 'Imaging'
      Caption = '&Monochrome'
      Hint = 'Convert image colors to monochrome'
      OnExecute = AMonochromeExecute
    end
  end
  object OpenPictureDialog1: TOpenPictureDialog
    DefaultExt = 'bmp'
    Options = [ofOverwritePrompt, ofHideReadOnly, ofEnableSizing]
    Left = 118
    Top = 112
  end
  object FormTranslation1: TFormTranslation
    Left = 282
    Top = 140
  end
end
