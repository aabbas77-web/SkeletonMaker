object FormDigitize: TFormDigitize
  Left = 197
  Top = 430
  BorderIcons = [biSystemMenu]
  BorderStyle = bsSingle
  Caption = 'Digitize'
  ClientHeight = 110
  ClientWidth = 211
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
  object Panel2: TPanel
    Left = 0
    Top = 0
    Width = 211
    Height = 78
    Align = alClient
    Color = 14869218
    TabOrder = 0
    object Label1: TLabel
      Left = 8
      Top = 7
      Width = 70
      Height = 13
      Alignment = taCenter
      AutoSize = False
      Caption = 'Colors Count'
    end
    object Label2: TLabel
      Left = 8
      Top = 31
      Width = 70
      Height = 13
      Alignment = taCenter
      AutoSize = False
      Caption = 'Filter Dim'
    end
    object Label3: TLabel
      Left = 8
      Top = 55
      Width = 70
      Height = 13
      Alignment = taCenter
      AutoSize = False
      Caption = 'Repeat Count'
    end
    object CSpinEdit1: TCSpinEdit
      Left = 84
      Top = 3
      Width = 120
      Height = 22
      TabStop = True
      MaxValue = 255
      MinValue = 1
      ParentColor = False
      TabOrder = 0
      Value = 8
    end
    object CSpinEdit2: TCSpinEdit
      Left = 84
      Top = 27
      Width = 120
      Height = 22
      TabStop = True
      Increment = 2
      MaxValue = 30
      MinValue = 3
      ParentColor = False
      TabOrder = 1
      Value = 7
    end
    object CSpinEdit3: TCSpinEdit
      Left = 84
      Top = 51
      Width = 120
      Height = 22
      TabStop = True
      MaxValue = 30
      MinValue = 1
      ParentColor = False
      TabOrder = 2
      Value = 4
    end
  end
  object Panel1: TPanel
    Left = 0
    Top = 78
    Width = 211
    Height = 32
    Align = alBottom
    Color = 14869218
    TabOrder = 1
    object SpeedButton1: TSpeedButton
      Left = 43
      Top = 5
      Width = 60
      Height = 22
      Caption = 'Ok'
      Flat = True
      OnClick = SpeedButton1Click
    end
    object SpeedButton2: TSpeedButton
      Left = 107
      Top = 5
      Width = 60
      Height = 22
      Caption = 'Cancel'
      Flat = True
      OnClick = SpeedButton2Click
    end
  end
  object FormTranslation1: TFormTranslation
    Left = 96
    Top = 32
  end
end
