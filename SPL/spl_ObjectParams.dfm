object FormObjectParams: TFormObjectParams
  Left = 190
  Top = 105
  BorderIcons = [biSystemMenu]
  BorderStyle = bsSingle
  Caption = 'Object Parameters'
  ClientHeight = 262
  ClientWidth = 419
  Color = 14869218
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object Panel1: TPanel
    Left = 0
    Top = 230
    Width = 419
    Height = 32
    Align = alBottom
    Color = 14869218
    TabOrder = 0
    object SpeedButton1: TSpeedButton
      Left = 148
      Top = 5
      Width = 60
      Height = 22
      Caption = 'Ok'
      Flat = True
      OnClick = SpeedButton1Click
    end
    object SpeedButton2: TSpeedButton
      Left = 212
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
    Width = 419
    Height = 230
    Align = alClient
    Color = 14869218
    TabOrder = 1
    object GroupBox1: TGroupBox
      Left = 4
      Top = 4
      Width = 202
      Height = 221
      Caption = 'Fill Parameters'
      TabOrder = 0
      object Label3: TLabel
        Left = 8
        Top = 123
        Width = 95
        Height = 13
        Alignment = taCenter
        AutoSize = False
        Caption = 'Fill Density'
      end
      object Label4: TLabel
        Left = 8
        Top = 99
        Width = 95
        Height = 13
        Alignment = taCenter
        AutoSize = False
        Caption = 'Run Length'
      end
      object Bevel1: TBevel
        Left = 8
        Top = 40
        Width = 185
        Height = 6
        Shape = bsBottomLine
      end
      object Label12: TLabel
        Left = 8
        Top = 75
        Width = 95
        Height = 13
        Alignment = taCenter
        AutoSize = False
        Caption = 'Fill Stitch Output'
      end
      object Label6: TLabel
        Left = 8
        Top = 147
        Width = 95
        Height = 13
        Alignment = taCenter
        AutoSize = False
        Caption = 'Stitching Direction'
      end
      object Label7: TLabel
        Left = 8
        Top = 171
        Width = 95
        Height = 13
        Alignment = taCenter
        AutoSize = False
        Caption = 'Start Direction'
      end
      object Label8: TLabel
        Left = 8
        Top = 195
        Width = 95
        Height = 13
        Alignment = taCenter
        AutoSize = False
        Caption = 'Stitch Margin'
      end
      object CSpinEdit3: TCSpinEdit
        Left = 108
        Top = 119
        Width = 85
        Height = 22
        TabStop = True
        MaxValue = 121
        MinValue = 1
        ParentColor = False
        TabOrder = 0
        Value = 5
      end
      object CSpinEdit4: TCSpinEdit
        Left = 108
        Top = 95
        Width = 85
        Height = 22
        TabStop = True
        MaxValue = 121
        MinValue = 1
        ParentColor = False
        TabOrder = 1
        Value = 30
      end
      object CheckBox1: TCheckBox
        Left = 8
        Top = 23
        Width = 80
        Height = 17
        Caption = 'Embroid In'
        Checked = True
        State = cbChecked
        TabOrder = 2
      end
      object ComboBox4: TComboBox
        Left = 108
        Top = 19
        Width = 85
        Height = 21
        Style = csOwnerDrawVariable
        ItemHeight = 15
        TabOrder = 3
        OnDrawItem = ComboBox4DrawItem
      end
      object ComboBox1: TComboBox
        Left = 108
        Top = 71
        Width = 85
        Height = 21
        Style = csDropDownList
        ItemHeight = 13
        TabOrder = 4
        Items.Strings = (
          'ZigZag'
          'Tatami')
      end
      object ComboBox2: TComboBox
        Left = 108
        Top = 143
        Width = 85
        Height = 21
        Style = csDropDownList
        ItemHeight = 13
        TabOrder = 5
        Items.Strings = (
          'Horizontal'
          'Diagonal'
          'Vertical')
      end
      object CSpinEdit6: TCSpinEdit
        Left = 108
        Top = 191
        Width = 85
        Height = 22
        TabStop = True
        MaxValue = 10000
        ParentColor = False
        TabOrder = 6
        Value = 121
      end
      object ComboBox3: TComboBox
        Left = 108
        Top = 167
        Width = 85
        Height = 21
        Style = csDropDownList
        ItemHeight = 13
        TabOrder = 7
        Items.Strings = (
          'Horizontal'
          'Diagonal'
          'Vertical')
      end
      object CheckBox3: TCheckBox
        Left = 8
        Top = 51
        Width = 80
        Height = 17
        Caption = 'Adjust'
        Checked = True
        State = cbChecked
        TabOrder = 8
      end
    end
    object GroupBox2: TGroupBox
      Left = 212
      Top = 4
      Width = 202
      Height = 221
      Caption = 'Outline Parameters'
      TabOrder = 1
      object Label10: TLabel
        Left = 8
        Top = 75
        Width = 95
        Height = 13
        Alignment = taCenter
        AutoSize = False
        Caption = 'Line Stitch Output'
      end
      object Bevel2: TBevel
        Left = 8
        Top = 40
        Width = 185
        Height = 6
        Shape = bsBottomLine
      end
      object Label9: TLabel
        Left = 8
        Top = 99
        Width = 95
        Height = 13
        Alignment = taCenter
        AutoSize = False
        Caption = 'Satin Height'
      end
      object Label1: TLabel
        Left = 8
        Top = 123
        Width = 95
        Height = 13
        Alignment = taCenter
        AutoSize = False
        Caption = 'Line Density'
      end
      object CheckBox2: TCheckBox
        Left = 8
        Top = 23
        Width = 80
        Height = 17
        Caption = 'Embroid Out'
        Checked = True
        State = cbChecked
        TabOrder = 0
      end
      object ComboBox5: TComboBox
        Left = 108
        Top = 19
        Width = 85
        Height = 21
        Style = csOwnerDrawVariable
        ItemHeight = 15
        TabOrder = 1
        OnDrawItem = ComboBox4DrawItem
      end
      object ComboBox6: TComboBox
        Left = 108
        Top = 71
        Width = 85
        Height = 21
        Style = csDropDownList
        ItemHeight = 13
        TabOrder = 2
        Items.Strings = (
          'Run'
          'Satin')
      end
      object CSpinEdit7: TCSpinEdit
        Left = 108
        Top = 95
        Width = 85
        Height = 22
        TabStop = True
        MaxValue = 121
        MinValue = 1
        ParentColor = False
        TabOrder = 3
        Value = 121
      end
      object CSpinEdit1: TCSpinEdit
        Left = 108
        Top = 119
        Width = 85
        Height = 22
        TabStop = True
        MaxValue = 121
        MinValue = 1
        ParentColor = False
        TabOrder = 4
        Value = 5
      end
      object Panel3: TPanel
        Left = 9
        Top = 148
        Width = 185
        Height = 65
        BevelInner = bvLowered
        BevelOuter = bvNone
        Color = 14869218
        TabOrder = 5
        object Image1: TImage
          Left = 1
          Top = 1
          Width = 183
          Height = 63
          Align = alClient
        end
      end
      object CheckBox4: TCheckBox
        Left = 8
        Top = 51
        Width = 80
        Height = 17
        Caption = 'Adjust'
        Checked = True
        State = cbChecked
        TabOrder = 6
      end
    end
  end
  object FormTranslation1: TFormTranslation
    Left = 196
    Top = 160
  end
end
