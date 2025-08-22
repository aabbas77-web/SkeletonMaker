object FormVectorImage: TFormVectorImage
  Left = 190
  Top = 148
  Width = 544
  Height = 376
  BorderIcons = [biSystemMenu, biMaximize]
  Caption = 'Vector Image'
  Color = 14869218
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
    Height = 293
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
  object StatusBar: TStatusBar
    Left = 0
    Top = 311
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
        Text = 'C000'
        Width = 50
      end
      item
        Alignment = taCenter
        Text = 'Hint'
        Width = 50
      end>
    SimplePanel = False
  end
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 536
    Height = 18
    Align = alTop
    AutoSize = True
    TabOrder = 2
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
  object ActionList1: TActionList
    Left = 238
    Top = 108
    object AEmbroidery: TAction
      Category = 'Embroidery'
      Caption = '&Embroidery'
      Hint = 'Embroidery menu'
      OnExecute = AEmbroideryExecute
    end
    object AEmrboid: TAction
      Category = 'Embroidery'
      Caption = '&Embroid'
      Hint = 'Show embroidery settings'
      OnExecute = AEmrboidExecute
    end
    object AFile: TAction
      Category = 'File'
      Caption = '&File'
      Hint = 'File menu'
      OnExecute = AFileExecute
    end
    object ASave: TAction
      Category = 'File'
      Caption = '&Save as...'
      Hint = 'Save vector image to file'
      OnExecute = ASaveExecute
    end
    object AObject: TAction
      Category = 'Object'
      Caption = '&Object'
      Hint = 'Object menu'
      OnExecute = AObjectExecute
    end
    object AProperties: TAction
      Category = 'Object'
      Caption = '&Properties'
      Hint = 'Show object properties'
      OnExecute = APropertiesExecute
    end
    object AExport: TAction
      Category = 'File'
      Caption = 'Export...'
      OnExecute = AExportExecute
    end
    object AExportObject: TAction
      Category = 'Object'
      Caption = 'Export Object'
      OnExecute = AExportObjectExecute
    end
  end
  object MainMenu1: TMainMenu
    AutoHotkeys = maManual
    AutoLineReduction = maManual
    Left = 198
    Top = 148
    object File1: TMenuItem
      Action = AFile
      object Saveas1: TMenuItem
        Action = ASave
      end
      object Embroid1: TMenuItem
        Action = AExport
      end
    end
    object Object1: TMenuItem
      Action = AObject
      object Properties1: TMenuItem
        Action = AProperties
      end
      object ExportObject1: TMenuItem
        Action = AExportObject
      end
    end
    object Embroidery1: TMenuItem
      Action = AEmbroidery
      object Emboid1: TMenuItem
        Action = AEmrboid
      end
    end
  end
  object SaveDialogEMB: TSaveDialog
    Options = [ofOverwritePrompt, ofHideReadOnly, ofAllowMultiSelect, ofEnableSizing]
    Left = 162
    Top = 186
  end
  object SavePictureDialogEMF: TSavePictureDialog
    DefaultExt = 'emf'
    Filter = 'Enhanced MetaFiles (*.emf)|*.emf'
    Options = [ofOverwritePrompt, ofHideReadOnly, ofAllowMultiSelect, ofEnableSizing]
    Left = 378
    Top = 222
  end
  object PopupMenuObject: TPopupMenu
    Left = 66
    Top = 156
    object Properties2: TMenuItem
      Action = AProperties
    end
    object ExportObject2: TMenuItem
      Action = AExportObject
    end
  end
  object SaveDialogML: TSaveDialog
    DefaultExt = 'ml'
    Filter = 'MultiLayer Files (*.ml)|*.ml'
    Options = [ofOverwritePrompt, ofHideReadOnly, ofEnableSizing]
    Left = 230
    Top = 192
  end
  object SaveDialogRGN: TSaveDialog
    DefaultExt = 'rgn'
    Filter = 'Region Files (*.rgn)|*.rgn'
    Options = [ofOverwritePrompt, ofHideReadOnly, ofEnableSizing]
    Left = 274
    Top = 164
  end
  object FormTranslation1: TFormTranslation
    Left = 158
    Top = 60
  end
end
