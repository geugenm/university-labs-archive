//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------

#pragma package(smart_init)
#pragma resource "*.dfm"
TLab4 *Lab4;
//---------------------------------------------------------------------------
 /* ���������� ����������(�����. ��� ������ � �������� ��� ���������������) */
int max_array_size = 8;
int user_size = max_array_size;

int *initial_array = new int[max_array_size];
//---------------------------------------------------------------------------

int CalculateMultiplication(int array[], int array_size) {
	// ������� ������� ������������ ���������, ������. ����� �������� ����������
	// �� ���������, ���� ������� �� ����� ���������, ������� �������� '0'
	int result = 0;

	for(int i = 0; i < array_size; i++) {
		// ���� ������ ����
		if(array[i] == 0) {
			// ���� ����� 0, ���������� � ������������ ����� �� ������� 0
			for(int j = i + 1; j < array_size && array[j] != 0; j++) {
				if(j == (i + 1)) {
					// ���������� result � ������������
					// (result �������� ������ ��� ������ �������� �����)
					result = 1;
				}
				if(j == array_size - 1) {
					// �.�. � ������� for ���� �������� �� ���� (array[j] != 0),
					// �� ����� �� ���� ������� ���� �� ����� => �����. 0
					return 0;
				}
				result *= array[j];
			}
            break;
        }
	}

	return result;
}
//---------------------------------------------------------------------------

__fastcall TLab4::TLab4(TComponent* Owner) : TForm(Owner) {
}
//---------------------------------------------------------------------------

void __fastcall TLab4::FormCreate(TObject *Sender) {
	// ������� ���������� ���� �������� ��� �������
	randomize();

	// �� ��������� ��� ������� ����� ������ �������� 8
	ArraySizeEdit -> Text = IntToStr(max_array_size);
	InitialArrayGrid -> ColCount = max_array_size;

	for(int i = 0; i < max_array_size; i++) {
		// �������� ���������� �������, ������ ������ ��� �������
		initial_array[i] = random(7) - 5;
		InitialArrayGrid -> Cells[i][0] = IntToStr(initial_array[i]);
	}

	// ����� ������������
	OutputResultField -> Text = IntToStr(CalculateMultiplication(initial_array, max_array_size));
}
//---------------------------------------------------------------------------
void __fastcall TLab4::ApplyArraySizeButtonClick(TObject *Sender) {
	// ������� ��������� ������� ����������� ������� �� �����
	user_size = StrToInt(ArraySizeEdit -> Text);

	// ��������� ������������ ���������� ������� �������
	if(user_size > 0 && user_size <= max_array_size) {
        InitialArrayGrid -> ColCount = user_size;

		for(int i = 0; i < user_size; i++) {
			// ������ ���-�� ��������� �� ������
			InitialArrayGrid -> Cells[i][0] = IntToStr(initial_array[i]);
		}

		// ����� ������������
		OutputResultField -> Text = IntToStr(CalculateMultiplication(initial_array, user_size));
	}
	else {
        ShowMessage("Incorrect array size!");
	}
}
//---------------------------------------------------------------------------
void __fastcall TLab4::GenerateNewArrayButtonClick(TObject *Sender) {
	// ������� ��������� ������ �������
	randomize();

	for(int i = 0; i < max_array_size; i++) {
		// �������� ���������� �������, ������ ������ ��� �������
		initial_array[i] = random(7) - 5;
		InitialArrayGrid -> Cells[i][0] = IntToStr(initial_array[i]);
	}

    // ����� ������������
	OutputResultField -> Text = IntToStr(CalculateMultiplication(initial_array, user_size));
}
//---------------------------------------------------------------------------
