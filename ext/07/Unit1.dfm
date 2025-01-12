object Lab7: TLab7
  Left = 0
  Top = 0
  Caption = 'Lab7'
  ClientHeight = 364
  ClientWidth = 553
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  OnClose = FormClose
  PixelsPerInch = 96
  TextHeight = 13
  object InititalsInputLabel: TLabel
    Left = 39
    Top = 40
    Width = 35
    Height = 13
    Caption = 'Initials:'
  end
  object InputMathRatingLabel: TLabel
    Left = 173
    Top = 74
    Width = 28
    Height = 13
    Caption = 'Math:'
  end
  object InputPhysRatingLabel: TLabel
    Left = 63
    Top = 74
    Width = 35
    Height = 13
    Caption = 'Physics'
  end
  object InputITRatingLabel: TLabel
    Left = 280
    Top = 74
    Width = 14
    Height = 13
    Caption = 'IT:'
  end
  object UserGroupInputLabel: TLabel
    Left = 241
    Top = 40
    Width = 33
    Height = 13
    Caption = 'Group:'
  end
  object InitialsInputEdit: TEdit
    Left = 80
    Top = 37
    Width = 121
    Height = 21
    TabOrder = 0
    TextHint = 'Initials...'
  end
  object InputRatingMathEdit: TEdit
    Left = 144
    Top = 93
    Width = 89
    Height = 21
    TabOrder = 1
    TextHint = 'Grade...'
  end
  object AddNewUserButton: TButton
    Left = 446
    Top = 91
    Width = 75
    Height = 25
    Caption = 'Add'
    TabOrder = 2
    OnClick = AddNewUserButtonClick
  end
  object OpenUserFileButton: TButton
    Left = 144
    Top = 304
    Width = 75
    Height = 25
    Caption = 'Open'
    TabOrder = 3
    OnClick = OpenUserFileButtonClick
  end
  object CreateUserFileButton: TButton
    Left = 40
    Top = 304
    Width = 75
    Height = 25
    Caption = 'Create'
    TabOrder = 4
    OnClick = CreateUserFileButtonClick
  end
  object SaveUserFileButton: TButton
    Left = 248
    Top = 304
    Width = 75
    Height = 25
    Caption = 'Save'
    TabOrder = 5
    OnClick = SaveUserFileButtonClick
  end
  object EditUserButton: TButton
    Left = 446
    Top = 200
    Width = 75
    Height = 25
    Caption = 'Edit'
    TabOrder = 6
    OnClick = EditUserButtonClick
  end
  object DeleteUserButton: TButton
    Left = 446
    Top = 152
    Width = 75
    Height = 25
    Caption = 'Delete'
    TabOrder = 7
    OnClick = DeleteUserButtonClick
  end
  object OutputGrid: TStringGrid
    Left = 39
    Top = 145
    Width = 394
    Height = 153
    Color = clWhite
    ColCount = 6
    FixedCols = 0
    RowCount = 6
    FixedRows = 0
    Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goEditing, goFixedRowDefAlign]
    ScrollBars = ssVertical
    TabOrder = 8
  end
  object InputRatingPhysEdit: TEdit
    Left = 40
    Top = 93
    Width = 89
    Height = 21
    TabOrder = 9
    TextHint = 'Grade...'
  end
  object InputRatingITEdit: TEdit
    Left = 248
    Top = 93
    Width = 89
    Height = 21
    TabOrder = 10
    TextHint = 'Grade...'
  end
  object UserGroupInputEdit: TEdit
    Left = 280
    Top = 37
    Width = 75
    Height = 21
    TabOrder = 11
    TextHint = 'Initials...'
  end
  object FindSpecialUsers: TButton
    Left = 357
    Top = 304
    Width = 75
    Height = 25
    Caption = 'Find'
    TabOrder = 12
    OnClick = FindSpecialUsersClick
  end
  object UserSortAlphButton: TButton
    Left = 38
    Top = 120
    Width = 68
    Height = 25
    Caption = 'Name'
    TabOrder = 13
    OnClick = UserSortAlphButtonClick
  end
  object UserSortGrpButton: TButton
    Left = 105
    Top = 120
    Width = 67
    Height = 25
    Caption = 'Group'
    TabOrder = 14
    OnClick = UserSortGrpButtonClick
  end
  object UserSortPhysButton: TButton
    Left = 171
    Top = 120
    Width = 69
    Height = 25
    Caption = 'Phys'
    TabOrder = 15
    OnClick = UserSortPhysButtonClick
  end
  object UserSortMathButton: TButton
    Left = 239
    Top = 120
    Width = 63
    Height = 25
    Caption = 'Math'
    TabOrder = 16
    OnClick = UserSortMathButtonClick
  end
  object UserSortITButton: TButton
    Left = 301
    Top = 120
    Width = 67
    Height = 25
    Caption = 'IT'
    TabOrder = 17
    OnClick = UserSortITButtonClick
  end
  object UserSortAvrgButton: TButton
    Left = 368
    Top = 120
    Width = 64
    Height = 25
    Caption = 'Average'
    TabOrder = 18
    OnClick = UserSortAvrgButtonClick
  end
  object OpenUserFileDialog: TOpenDialog
    Left = 472
    Top = 16
  end
  object SaveUserFileDialog: TSaveDialog
    Left = 440
    Top = 16
  end
end
