//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include <fstream>
//---------------------------------------------------------------------------

#pragma package(smart_init)
#pragma resource "*.dfm"
TLab7 *Lab7;
//---------------------------------------------------------------------------

FILE *USER_LIST = NULL;
String user_list_file_name;

//---------------------------------------------------------------------------

__fastcall TLab7::TLab7(TComponent* Owner) : TForm(Owner) {
}
//---------------------------------------------------------------------------

String CaclulateAverageGrade(TStringGrid *Table, int target_user) {
	// ������� �������� �������� ����� �� ���� ���������
	float result = 0;

	for(int i = 2; i < Table -> ColCount - 1; i++) {
        // ��������� ��� � ���� ����������
		result += StrToFloat(Table -> Cells[i][target_user]);
	}

	return FloatToStr(result / 3);
}
//---------------------------------------------------------------------------

void OpenFile(TStringGrid *Table) {
    // ������� ���������� ������� ���������� ������� �� �����
	TStringList *Table1 = new TStringList;
	// ��������� ���� ��������������� �������
	Table1 -> LoadFromFile(user_list_file_name);

	// ������ ���-�� ����� � Table �� ��������������� �������
	Table -> RowCount = Table1 -> Count;

	for(int i = 0 ; i < Table -> RowCount; i++) {
		// �������� (���������) ������ � ��������������� ������� � Table
	  Table -> Rows[i] -> DelimitedText = Table1->Strings[i];
	}

    // ������� ������ ���������� ��������������� ��������
	delete Table1;
}
//---------------------------------------------------------------------------

void FillRow(TStringGrid *Table, TEdit *usr_initials, TEdit *usr_group, TEdit *usr_phys,
			 TEdit *usr_math, TEdit *usr_prog, int arg) {
	// ������� ���������� ������. ������� ��� �������� / �������������� ��������
	// �����!!! �������� ������� � ����� ������������ ����� �������!
	// 	������� - � ����������� ������� Sort() ������� ���������� ����� ������
	//  ����� ���� �������� ���� ����������, �� ����� ��������� �� �����������
	//  ������ � ����, �.�. � ���� ��� ���������� �� ����������

    //�������� ������������ ��������� ������
	if(StrToInt(usr_phys -> Text) < 10 && StrToInt(usr_phys -> Text) >= 0 &&
	   StrToInt(usr_math -> Text) < 10 && StrToInt(usr_math -> Text) >= 0 &&
	   StrToInt(usr_prog -> Text) < 10 && StrToInt(usr_prog -> Text) >= 0)
	{
        // ���������� ������� ������
		Table -> Cells[0][arg] = usr_initials -> Text;
		Table -> Cells[1][arg] = usr_group -> Text;
		Table -> Cells[2][arg] = usr_phys -> Text;
		Table -> Cells[3][arg] = usr_math -> Text;
		Table -> Cells[4][arg] = usr_prog -> Text;
		Table -> Cells[5][arg] = CaclulateAverageGrade(Table, (Table -> RowCount) - 1);
	}
	else {
        ShowMessage("Wrong data given");
    }
}
//---------------------------------------------------------------------------
void SortGridCol(TStringGrid *Table, int col_sort) {
	// ������� ���������� �� �������
	// �������:
	//  ������ �������� �������� ������ � ��������� �� 0 �� 10(��� ��� ������ ���)
	//  ��� �������������� ������ ��������� �������� ���-�� ���������.
	//  ��� ���������� ���������� ������� ���������� ������� Sort()

	TStringList *lst  = new TStringList;
	TStringList *lst1 = new TStringList;

	for(int i = 0; i < Table -> RowCount; ++i) {
		// �������� ��� � ���� � ����� �������������� ����,
		// ���������� ����� ������, ��� �� ����� ��� �����������
		lst -> Add(Table -> Cells[col_sort][i] + "~" + IntToStr(i));
	}

    // ���������
	lst -> Sort();

	for(int i = 0 ; i < Table -> RowCount; ++i) {
		// ������ �������� �������,��� �� ����� ����� ����������� ��������
		lst1 -> Add(Table -> Rows[i] -> Text);
	}

	for(int i = 0; i < Table -> RowCount; ++i) {
        //������ �������������� �������
		Table -> Rows[i] -> DelimitedText = lst1 -> Strings[lst ->
		Strings[i].SubString(lst -> Strings[i].Pos("~")
		+ 1, lst -> Strings[i].Length()).ToInt()];
	}

    // ������� ������
	delete lst;
	delete lst1;
}
//---------------------------------------------------------------------------

void __fastcall TLab7::CreateUserFileButtonClick(TObject *Sender) {
    // �������, ���������� �� �������� � ����������� �������� �����
    OpenUserFileDialog -> Title = "Create New File";

	if(OpenUserFileDialog -> Execute()) {
        // �������� �� ����������� ���� ��� ����� � ��������� ���
		user_list_file_name = OpenUserFileDialog -> FileName;
		USER_LIST = fopen(AnsiString(user_list_file_name).c_str(), "wb");
		if(USER_LIST) {
            // ��������� ���� � ��������� � ������
			fclose(USER_LIST);
			std::ofstream outfile;

            // �������� 0-������������, ��� ������
			outfile.open(AnsiString(user_list_file_name).c_str(), std::ios::trunc);
			outfile << "0 0 0 0 0 0";
			outfile.close();

            // ��������� ���� � ������� ������
			OpenFile(OutputGrid);
            fclose(USER_LIST);
		}
		else {
			ShowMessage("File creation error");
			return;
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TLab7::OpenUserFileButtonClick(TObject *Sender) {
    // ������� �������� ��� ���������� �����
	OpenUserFileDialog -> Title = "Open a file";

	if(OpenUserFileDialog -> Execute()) {
        // �������� �� ����������� ���� ��� ����� � ��������� ���
		user_list_file_name = OpenUserFileDialog -> FileName;
		USER_LIST = fopen(AnsiString(user_list_file_name).c_str(), "rb");
		if(USER_LIST) {
            // ��������� ������� � ������� ������
			OpenFile(OutputGrid);
            fclose(USER_LIST);
		}
		else {
			ShowMessage("File open error");
			return;
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TLab7::SaveUserFileButtonClick(TObject *Sender) {
    // ������� ���������� �����
	if(USER_LIST) {
        // ��������� �����
		std::ofstream outfile;

        // ������ ����� � ����� ���������� �����(trunc)
		outfile.open(AnsiString(user_list_file_name).c_str(), std::ios::trunc);
		for(int i = 0; i < OutputGrid -> RowCount; i++) {
			for(int j = 0; j < OutputGrid -> ColCount; j++) {
				if (j == OutputGrid -> ColCount - 1) {
                    // ���� ����� �� ����� ������, �� ����������� �� � endl
                    outfile << AnsiString(OutputGrid -> Cells[j][i]).c_str() << std::endl;
				}
				else {
					// � ���� ������ ������ ��������� ����������� - ������ " ")
					outfile << AnsiString(OutputGrid -> Cells[j][i]).c_str() << " ";
				}
			}
		}
        // �������� ������ � ������� ������
		outfile.close();
        fclose(USER_LIST);
	}
	else {
		ShowMessage("First open the file");
    }
}
//---------------------------------------------------------------------------

void __fastcall TLab7::FindSpecialUsersClick(TObject *Sender) {
	// ������� ������ �������� ������������
	if(USER_LIST) {
		for(int i = 0; i < OutputGrid -> RowCount; i++) {
			if(StrToFloat(OutputGrid -> Cells[2][i]) >= 4.0 && StrToFloat(OutputGrid -> Cells[2][i]) <= 5.0) {
				if(StrToFloat(OutputGrid -> Cells[3][i]) >= 8.0 && StrToFloat(OutputGrid -> Cells[4][i]) >= 8.0) {
                    // �������� ������� ������
					TGridRect SelectedGrid;
					SelectedGrid.Left = 5;
					SelectedGrid.Top = i;
					SelectedGrid.Bottom = i;
					SelectedGrid.Right = 0;
					OutputGrid -> Selection = SelectedGrid;
					ShowMessage("Found the user you were looking for!");
				}
			}
		}
	}
	else {
		ShowMessage("First open the file");
	}

}
//---------------------------------------------------------------------------

void __fastcall TLab7::AddNewUserButtonClick(TObject *Sender) {
    // ������� ���������� ������ � ������������
	if(USER_LIST) {
        // ��������� �������
		OutputGrid -> RowCount += 1;
        // ��������� ������
		FillRow(OutputGrid, InitialsInputEdit, UserGroupInputEdit, InputRatingPhysEdit,
				InputRatingMathEdit, InputRatingITEdit, (OutputGrid -> RowCount) - 1);
	}
    else {
		ShowMessage("First open the file");
	}
}
//---------------------------------------------------------------------------

void __fastcall TLab7::DeleteUserButtonClick(TObject *Sender) {
    // ������� �������� ������ � ������������
	if(USER_LIST) {
        // ������� ������
		int Index = OutputGrid -> Selection.Top;
		if(Index != OutputGrid -> RowCount - 1) {
            // ���� ������ ������� �����-������ ������
			for(int i = Index; i < OutputGrid -> RowCount - 1; i++) {
				// � ������� ������ �� ��������� �������� ������� ������ ���������
				OutputGrid -> Rows[i] = OutputGrid -> Rows[i + 1];
			}
            // ������� ��������� ������
			OutputGrid->RowCount--;
		}
	}
	else {
		ShowMessage("First open the file");
	}
}
//---------------------------------------------------------------------------

void __fastcall TLab7::EditUserButtonClick(TObject *Sender) {
    // ������� �������������� ������ � ������������
	if(USER_LIST) {
        // ��������� ������
		FillRow(OutputGrid, InitialsInputEdit, UserGroupInputEdit, InputRatingPhysEdit,
				InputRatingMathEdit, InputRatingITEdit, OutputGrid -> Selection.Top);
	}
	else {
		ShowMessage("First open the file");
	}
}
//---------------------------------------------------------------------------

void __fastcall TLab7::UserSortAlphButtonClick(TObject *Sender) {
    // ���������� �� �����
	if(USER_LIST) {
		SortGridCol(OutputGrid, 0);
	}
	else {
		ShowMessage("First open the file");
	}
}
//---------------------------------------------------------------------------

void __fastcall TLab7::UserSortGrpButtonClick(TObject *Sender) {
    // ���������� �� ������
	if(USER_LIST) {
		SortGridCol(OutputGrid, 1);
	}
	else {
		ShowMessage("First open the file");
	}
}
//---------------------------------------------------------------------------

void __fastcall TLab7::UserSortPhysButtonClick(TObject *Sender) {
    // ���������� �� ����������� ������ 'phys'
    if(USER_LIST) {
		SortGridCol(OutputGrid, 2);
	}
	else {
		ShowMessage("First open the file");
	}
}
//---------------------------------------------------------------------------

void __fastcall TLab7::UserSortMathButtonClick(TObject *Sender) {
	// ���������� �� ����������� ����������� 'math'
	if(USER_LIST) {
		SortGridCol(OutputGrid, 3);
	}
	else {
		ShowMessage("First open the file");
	}
}
//---------------------------------------------------------------------------

void __fastcall TLab7::UserSortITButtonClick(TObject *Sender) {
    // ���������� �� ����������� ���������������� 'it'
    if(USER_LIST) {
		SortGridCol(OutputGrid, 4);
	}
	else {
		ShowMessage("First open the file");
	}
}
//---------------------------------------------------------------------------

void __fastcall TLab7::UserSortAvrgButtonClick(TObject *Sender) {
	// ���������� �� �������� ����� 'Average'
	if(USER_LIST) {
		SortGridCol(OutputGrid, 5);
	}
	else {
		ShowMessage("First open the file");
	}
}
//---------------------------------------------------------------------------

void __fastcall TLab7::FormClose(TObject *Sender, TCloseAction &Action) {
    // ������� �������� ����
	fclose(USER_LIST);
}
//---------------------------------------------------------------------------

