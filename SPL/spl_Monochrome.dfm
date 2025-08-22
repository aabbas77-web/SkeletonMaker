object FormMonochrom: TFormMonochrom
  Left = 515
  Top = 161
  BorderIcons = [biSystemMenu]
  BorderStyle = bsToolWindow
  Caption = 'Monochrome'
  ClientHeight = 79
  ClientWidth = 277
  Color = 14869218
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 277
    Height = 79
    Align = alClient
    TabOrder = 0
    object GroupBox1: TGroupBox
      Left = 4
      Top = 4
      Width = 270
      Height = 72
      Caption = 'Threshold'
      Color = 14869218
      ParentColor = False
      TabOrder = 0
      object SpeedButton1: TSpeedButton
        Left = 14
        Top = 43
        Width = 60
        Height = 22
        Caption = 'Fisher'
        Flat = True
        OnClick = SpeedButton1Click
      end
      object SpeedButton2: TSpeedButton
        Left = 76
        Top = 43
        Width = 60
        Height = 22
        Caption = 'Entropy'
        Flat = True
        OnClick = SpeedButton2Click
      end
      object SpeedButton3: TSpeedButton
        Left = 205
        Top = 43
        Width = 51
        Height = 22
        Caption = 'Close'
        Flat = True
        OnClick = SpeedButton3Click
      end
      object TrackBar1: TTrackBar
        Left = 7
        Top = 18
        Width = 256
        Height = 22
        Max = 255
        Orientation = trHorizontal
        PageSize = 1
        Frequency = 1
        Position = 128
        SelEnd = 0
        SelStart = 0
        TabOrder = 0
        TickMarks = tmBottomRight
        TickStyle = tsAuto
        OnChange = TrackBar1Change
      end
      object Panel2: TPanel
        Left = 141
        Top = 44
        Width = 60
        Height = 21
        BevelInner = bvLowered
        Caption = '128'
        Color = 3487029
        Font.Charset = DEFAULT_CHARSET
        Font.Color = 11796403
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentFont = False
        TabOrder = 1
      end
    end
  end
  object FormTranslation1: TFormTranslation
    Left = 132
    Top = 12
  end
end
