object Lab4: TLab4
  Left = 0
  Top = 0
  Caption = 'Lab4'
  ClientHeight = 299
  ClientWidth = 635
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object ArraySizeLabel: TLabel
    Left = 80
    Top = 72
    Width = 52
    Height = 13
    Caption = 'Array size:'
  end
  object OutputResultLabel: TLabel
    Left = 298
    Top = 208
    Width = 34
    Height = 13
    Caption = 'Result:'
  end
  object ArraySizeEdit: TEdit
    Left = 138
    Top = 69
    Width = 121
    Height = 21
    TabOrder = 0
    Text = 'Input array size...'
  end
  object ApplyArraySizeButton: TButton
    Left = 272
    Top = 67
    Width = 75
    Height = 25
    Caption = 'Apply'
    TabOrder = 1
    OnClick = ApplyArraySizeButtonClick
  end
  object InitialArrayGrid: TStringGrid
    Left = 56
    Top = 152
    Width = 521
    Height = 25
    ColCount = 8
    FixedCols = 0
    RowCount = 1
    FixedRows = 0
    ScrollBars = ssNone
    TabOrder = 2
  end
  object OutputResultField: TEdit
    Left = 256
    Top = 240
    Width = 121
    Height = 21
    Alignment = taCenter
    TabOrder = 3
    Text = 'Result...'
  end
  object GenerateNewArrayButton: TButton
    Left = 440
    Top = 67
    Width = 97
    Height = 25
    Caption = 'Generate new'
    TabOrder = 4
    OnClick = GenerateNewArrayButtonClick
  end
end
