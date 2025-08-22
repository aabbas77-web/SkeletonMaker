object FormLayersViewer: TFormLayersViewer
  Left = 193
  Top = 306
  Width = 120
  Height = 267
  Align = alLeft
  Caption = 'Layers Viewer'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  WindowState = wsMaximized
  OnCreate = FormCreate
  OnDestroy = FormDestroy
  PixelsPerInch = 96
  TextHeight = 13
  object PanelBase: TPanel
    Left = 0
    Top = 0
    Width = 112
    Height = 240
    Align = alLeft
    BevelOuter = bvNone
    TabOrder = 0
  end
  object ImageList: TImageList
    Width = 48
    Left = 28
    Top = 92
  end
end
