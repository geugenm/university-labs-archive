object Form1: TForm1
  Left = 0
  Top = 0
  Caption = 'Lab5'
  ClientHeight = 381
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
    Left = 40
    Top = 40
    Width = 52
    Height = 13
    Caption = 'Array size:'
  end
  object MatrixWidthLabel: TLabel
    Left = 40
    Top = 80
    Width = 32
    Height = 13
    Caption = 'Width:'
  end
  object MatrixHeightLabel: TLabel
    Left = 40
    Top = 120
    Width = 35
    Height = 13
    Caption = 'Height:'
  end
  object OutputResultLabel: TLabel
    Left = 456
    Top = 98
    Width = 34
    Height = 13
    Caption = 'Result:'
  end
  object MatrixWidthEdit: TEdit
    Left = 88
    Top = 77
    Width = 121
    Height = 21
    TabOrder = 0
    Text = '8'
  end
  object MatrixHeightEdit: TEdit
    Left = 88
    Top = 117
    Width = 121
    Height = 21
    TabOrder = 1
    Text = '8'
  end
  object ApplyMatrixSizeButton: TButton
    Left = 240
    Top = 115
    Width = 75
    Height = 25
    Caption = 'Apply'
    TabOrder = 2
    OnClick = ApplyMatrixSizeButtonClick
  end
  object OutputResultField: TEdit
    Left = 416
    Top = 117
    Width = 121
    Height = 21
    Alignment = taCenter
    TabOrder = 3
    Text = 'Result...'
  end
  object MatrixGrid: TStringGrid
    Left = 56
    Top = 164
    Width = 521
    Height = 201
    ColCount = 8
    FixedCols = 0
    RowCount = 8
    FixedRows = 0
    Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goEditing, goFixedRowDefAlign]
    ScrollBars = ssNone
    TabOrder = 4
  end
  object GenerateNewMatrixButton: TButton
    Left = 432
    Top = 40
    Width = 89
    Height = 25
    Caption = 'Generate new'
    TabOrder = 5
    OnClick = GenerateNewMatrixButtonClick
  end
end
