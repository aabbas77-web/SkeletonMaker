object FormEmbParams: TFormEmbParams
  Left = 190
  Top = 105
  BorderIcons = [biSystemMenu]
  BorderStyle = bsSingle
  Caption = 'Embroidery Parameters'
  ClientHeight = 371
  ClientWidth = 419
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
    Top = 325
    Width = 419
    Height = 46
    Align = alBottom
    Color = 14869218
    TabOrder = 0
    object SpeedButton1: TSpeedButton
      Left = 148
      Top = 12
      Width = 60
      Height = 22
      Caption = 'Ok'
      Flat = True
      OnClick = SpeedButton1Click
    end
    object SpeedButton2: TSpeedButton
      Left = 212
      Top = 12
      Width = 60
      Height = 22
      Caption = 'Cancel'
      Flat = True
      OnClick = SpeedButton2Click
    end
    object CheckBoxBestJump: TCheckBox
      Left = 320
      Top = 8
      Width = 93
      Height = 17
      Caption = 'Best Jump'
      TabOrder = 0
      Visible = False
    end
    object ComboBoxAdjustMethode: TComboBox
      Left = 8
      Top = 12
      Width = 100
      Height = 21
      Style = csDropDownList
      ItemHeight = 13
      TabOrder = 1
      Visible = False
      Items.Strings = (
        'Methode 0'
        'Methode 1'
        'Methode 2')
    end
    object CheckBoxReplaceJump: TCheckBox
      Left = 320
      Top = 24
      Width = 93
      Height = 17
      Caption = 'Replace Jump'
      TabOrder = 2
    end
  end
  object Panel2: TPanel
    Left = 0
    Top = 0
    Width = 419
    Height = 325
    Align = alClient
    Color = 14869218
    TabOrder = 1
    object GroupBox1: TGroupBox
      Left = 4
      Top = 4
      Width = 202
      Height = 316
      Caption = 'Design Info'
      TabOrder = 0
      object Label11: TLabel
        Left = 8
        Top = 23
        Width = 109
        Height = 13
        Alignment = taCenter
        AutoSize = False
        Caption = 'Comment'
      end
      object Bevel2: TBevel
        Left = 8
        Top = 40
        Width = 186
        Height = 6
        Shape = bsBottomLine
      end
      object Bevel3: TBevel
        Left = 8
        Top = 68
        Width = 186
        Height = 6
        Shape = bsBottomLine
      end
      object Label9: TLabel
        Left = 8
        Top = 80
        Width = 87
        Height = 13
        Alignment = taCenter
        AutoSize = False
        Caption = 'Design Width (cm)'
      end
      object Label10: TLabel
        Left = 8
        Top = 104
        Width = 90
        Height = 13
        Alignment = taCenter
        AutoSize = False
        Caption = 'Design Height (cm)'
      end
      object Bevel4: TBevel
        Left = 8
        Top = 122
        Width = 186
        Height = 6
        Shape = bsBottomLine
      end
      object Label1: TLabel
        Left = 8
        Top = 135
        Width = 107
        Height = 13
        Alignment = taCenter
        AutoSize = False
        Caption = 'Minimum Stitch Length'
      end
      object Label2: TLabel
        Left = 8
        Top = 159
        Width = 107
        Height = 13
        Alignment = taCenter
        AutoSize = False
        Caption = 'Minimum Jump Length'
      end
      object Label5: TLabel
        Left = 8
        Top = 183
        Width = 107
        Height = 13
        Alignment = taCenter
        AutoSize = False
        Caption = 'Jump Length'
      end
      object Edit1: TEdit
        Left = 120
        Top = 20
        Width = 75
        Height = 21
        MaxLength = 13
        TabOrder = 0
        Text = 'WWPTC'
      end
      object CheckBox1: TCheckBox
        Left = 8
        Top = 51
        Width = 75
        Height = 17
        Caption = 'Centered'
        Checked = True
        State = cbChecked
        TabOrder = 1
      end
      object Edit2: TEdit
        Left = 120
        Top = 77
        Width = 75
        Height = 21
        MaxLength = 13
        TabOrder = 2
        Text = '10.0'
        OnChange = Edit2Change
      end
      object Edit3: TEdit
        Left = 120
        Top = 101
        Width = 75
        Height = 21
        MaxLength = 13
        TabOrder = 3
        Text = '10.0'
        OnChange = Edit3Change
      end
      object CSpinEdit5: TCSpinEdit
        Left = 120
        Top = 179
        Width = 75
        Height = 22
        TabStop = True
        MaxValue = 121
        MinValue = 1
        ParentColor = False
        TabOrder = 4
        Value = 121
      end
      object CSpinEdit2: TCSpinEdit
        Left = 120
        Top = 155
        Width = 75
        Height = 22
        TabStop = True
        MaxValue = 121
        MinValue = 1
        ParentColor = False
        TabOrder = 5
        Value = 10
      end
      object CSpinEdit1: TCSpinEdit
        Left = 120
        Top = 131
        Width = 75
        Height = 22
        TabStop = True
        MaxValue = 121
        MinValue = 1
        ParentColor = False
        TabOrder = 6
        Value = 3
      end
      object CheckBox4: TCheckBox
        Left = 120
        Top = 51
        Width = 75
        Height = 17
        Caption = 'Ret To Sta'
        Checked = True
        State = cbChecked
        TabOrder = 7
      end
      object Panel3: TPanel
        Left = 9
        Top = 206
        Width = 185
        Height = 102
        BevelInner = bvLowered
        BevelOuter = bvNone
        Color = 14869218
        TabOrder = 8
        object Image1: TImage
          Left = 1
          Top = 1
          Width = 183
          Height = 100
          Align = alClient
        end
      end
    end
    object GroupBox2: TGroupBox
      Left = 212
      Top = 4
      Width = 202
      Height = 193
      Caption = 'Fill Parameters'
      TabOrder = 1
      object Label12: TLabel
        Left = 8
        Top = 48
        Width = 107
        Height = 13
        Alignment = taCenter
        AutoSize = False
        Caption = 'Fill Stitch Output'
      end
      object Label6: TLabel
        Left = 8
        Top = 120
        Width = 107
        Height = 13
        Alignment = taCenter
        AutoSize = False
        Caption = 'Stitching Direction'
      end
      object Label7: TLabel
        Left = 8
        Top = 144
        Width = 107
        Height = 13
        Alignment = taCenter
        AutoSize = False
        Caption = 'Start Direction'
      end
      object Label8: TLabel
        Left = 8
        Top = 168
        Width = 107
        Height = 13
        Alignment = taCenter
        AutoSize = False
        Caption = 'Stitch Margin'
      end
      object Label4: TLabel
        Left = 8
        Top = 72
        Width = 107
        Height = 13
        Alignment = taCenter
        AutoSize = False
        Caption = 'Run Length'
      end
      object Label3: TLabel
        Left = 8
        Top = 96
        Width = 107
        Height = 13
        Alignment = taCenter
        AutoSize = False
        Caption = 'Fill Density'
      end
      object ComboBox1: TComboBox
        Left = 120
        Top = 44
        Width = 75
        Height = 21
        Style = csDropDownList
        ItemHeight = 13
        TabOrder = 0
        Items.Strings = (
          'ZigZag'
          'Tatami')
      end
      object ComboBox2: TComboBox
        Left = 120
        Top = 116
        Width = 75
        Height = 21
        Style = csDropDownList
        ItemHeight = 13
        TabOrder = 1
        Items.Strings = (
          'Horizontal'
          'Diagonal'
          'Vertical')
      end
      object ComboBox3: TComboBox
        Left = 120
        Top = 140
        Width = 75
        Height = 21
        Style = csDropDownList
        ItemHeight = 13
        TabOrder = 2
        Items.Strings = (
          'Horizontal'
          'Diagonal'
          'Vertical')
      end
      object CSpinEdit6: TCSpinEdit
        Left = 120
        Top = 164
        Width = 75
        Height = 22
        TabStop = True
        MaxValue = 10000
        ParentColor = False
        TabOrder = 3
        Value = 121
      end
      object CSpinEdit4: TCSpinEdit
        Left = 120
        Top = 68
        Width = 75
        Height = 22
        TabStop = True
        MaxValue = 121
        MinValue = 1
        ParentColor = False
        TabOrder = 4
        Value = 30
      end
      object CSpinEdit3: TCSpinEdit
        Left = 120
        Top = 92
        Width = 75
        Height = 22
        TabStop = True
        MaxValue = 121
        MinValue = 1
        ParentColor = False
        TabOrder = 5
        Value = 5
      end
      object CheckBox2: TCheckBox
        Left = 8
        Top = 23
        Width = 80
        Height = 17
        Caption = 'Embroid In'
        Checked = True
        State = cbChecked
        TabOrder = 6
      end
      object CheckBox5: TCheckBox
        Left = 120
        Top = 23
        Width = 80
        Height = 17
        Caption = 'Adjust'
        Checked = True
        State = cbChecked
        TabOrder = 7
      end
    end
    object GroupBox3: TGroupBox
      Left = 212
      Top = 200
      Width = 202
      Height = 120
      Caption = 'Line Parameters'
      TabOrder = 2
      object Label14: TLabel
        Left = 8
        Top = 47
        Width = 107
        Height = 13
        Alignment = taCenter
        AutoSize = False
        Caption = 'Line Stitch Output'
      end
      object Label13: TLabel
        Left = 8
        Top = 71
        Width = 107
        Height = 13
        Alignment = taCenter
        AutoSize = False
        Caption = 'Satin Height'
      end
      object Label15: TLabel
        Left = 8
        Top = 95
        Width = 107
        Height = 13
        Alignment = taCenter
        AutoSize = False
        Caption = 'Line Density'
      end
      object CSpinEdit8: TCSpinEdit
        Left = 120
        Top = 91
        Width = 75
        Height = 22
        TabStop = True
        MaxValue = 121
        MinValue = 1
        ParentColor = False
        TabOrder = 0
        Value = 5
      end
      object CSpinEdit7: TCSpinEdit
        Left = 120
        Top = 67
        Width = 75
        Height = 22
        TabStop = True
        MaxValue = 121
        MinValue = 1
        ParentColor = False
        TabOrder = 1
        Value = 121
      end
      object ComboBox4: TComboBox
        Left = 120
        Top = 43
        Width = 75
        Height = 21
        Style = csDropDownList
        ItemHeight = 13
        TabOrder = 2
        Items.Strings = (
          'Run'
          'Satin')
      end
      object CheckBox3: TCheckBox
        Left = 8
        Top = 23
        Width = 80
        Height = 17
        Caption = 'Embroid Out'
        Checked = True
        State = cbChecked
        TabOrder = 3
      end
      object CheckBox6: TCheckBox
        Left = 120
        Top = 23
        Width = 80
        Height = 17
        Caption = 'Adjust'
        Checked = True
        State = cbChecked
        TabOrder = 4
      end
    end
  end
  object FormTranslation1: TFormTranslation
    Left = 208
    Top = 132
  end
end
