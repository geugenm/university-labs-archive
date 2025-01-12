object Lab6: TLab6
  Left = 0
  Top = 0
  Caption = 'Lab6'
  ClientHeight = 169
  ClientWidth = 635
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object EnterStringLabel: TLabel
    Left = 272
    Top = 24
    Width = 95
    Height = 19
    Caption = 'Enter strings:'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
  end
  object AmountLabel: TLabel
    Left = 128
    Top = 120
    Width = 53
    Height = 13
    Caption = #39'1'#39' amount:'
  end
  object InputStringEdit: TEdit
    Left = 40
    Top = 69
    Width = 553
    Height = 21
    TabOrder = 0
    Text = 'Enter a string...'
    OnKeyPress = InputStringEditKeyPress
  end
  object OutputResultField: TEdit
    Left = 187
    Top = 117
    Width = 65
    Height = 21
    ReadOnly = True
    TabOrder = 1
    Text = 'Result...'
  end
  object CloseButton: TButton
    Left = 398
    Top = 115
    Width = 75
    Height = 25
    Caption = 'Close'
    TabOrder = 2
    OnClick = CloseButtonClick
  end
end
