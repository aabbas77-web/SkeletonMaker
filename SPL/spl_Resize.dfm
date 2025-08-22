object FormResize: TFormResize
  Left = 190
  Top = 105
  BorderIcons = [biSystemMenu]
  BorderStyle = bsSingle
  Caption = 'Resize'
  ClientHeight = 116
  ClientWidth = 186
  Color = 14869218
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  OnActivate = FormActivate
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object Panel1: TPanel
    Left = 0
    Top = 84
    Width = 186
    Height = 32
    Align = alBottom
    Color = 14869218
    TabOrder = 0
    object SpeedButton1: TSpeedButton
      Left = 31
      Top = 5
      Width = 60
      Height = 22
      Caption = 'Ok'
      Flat = True
      OnClick = SpeedButton1Click
    end
    object SpeedButton2: TSpeedButton
      Left = 95
      Top = 5
      Width = 60
      Height = 22
      Caption = 'Cancel'
      Flat = True
      OnClick = SpeedButton2Click
    end
  end
  object Panel2: TPanel
    Left = 0
    Top = 0
    Width = 186
    Height = 84
    Align = alClient
    Color = 14869218
    TabOrder = 1
    object Label9: TLabel
      Left = 4
      Top = 11
      Width = 40
      Height = 13
      Alignment = taCenter
      AutoSize = False
      Caption = 'Width'
    end
    object Label10: TLabel
      Left = 4
      Top = 35
      Width = 40
      Height = 13
      Alignment = taCenter
      AutoSize = False
      Caption = 'Height'
    end
    object Label1: TLabel
      Left = 4
      Top = 60
      Width = 40
      Height = 13
      Alignment = taCenter
      AutoSize = False
      Caption = 'Filter'
    end
    object Edit2: TEdit
      Left = 48
      Top = 7
      Width = 75
      Height = 21
      MaxLength = 13
      TabOrder = 0
      Text = '400'
      OnChange = Edit2Change
    end
    object Edit3: TEdit
      Left = 48
      Top = 31
      Width = 75
      Height = 21
      MaxLength = 13
      TabOrder = 1
      Text = '400'
      OnChange = Edit3Change
    end
    object CheckBox1: TCheckBox
      Left = 128
      Top = 20
      Width = 50
      Height = 17
      Caption = 'Linked'
      Checked = True
      State = cbChecked
      TabOrder = 2
    end
    object ComboBox1: TComboBox
      Left = 48
      Top = 56
      Width = 75
      Height = 21
      Style = csDropDownList
      ItemHeight = 13
      TabOrder = 3
      Items.Strings = (
        'Box'
        'Triangle'
        'Hermite'
        'Bell'
        'Spline'
        'Lanczos3'
        'Mitchell')
    end
  end
  object FormTranslation1: TFormTranslation
    Left = 76
    Top = 32
  end
end
