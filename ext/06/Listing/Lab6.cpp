// ---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
// ---------------------------------------------------------------------------

#pragma package(smart_init)
#pragma resource "*.dfm"
TLab6 *Lab6;
// ---------------------------------------------------------------------------

int findUnitCount(String user_string) {
	// ������� ������ ������ � �������� ������� (����������� - ����� ������)
	int counter = 0;
    int local_zeros = 0;
	int local_ones = 0;

	for (int i = 0; i <= user_string.Length(); i++) {
		// ���� ���� �� �������� ����� (����� ���������� � 0, ������� ������
		// ������������ ������� ���������. ������� - ��������� ��������������
		// ��������� �������� '\0')
		if (user_string.c_str()[i] == 49) {
			// ���� ������������� � �������� ASCII (49 - ��� 1)
			local_ones++;
		}
		else {
			if (user_string.c_str()[i] == 48) {
				// ���� ������������� � �������� ASCII (48 - ��� 0)
				local_zeros++;
			}
            else {
				if ((local_zeros + local_ones) % 2 != 0) {
					// �������� �� ����������
					counter += local_ones;
				}
				// ������� � ����. ������ ��������� ����� ����������. �����������
                local_ones = 0;
				local_zeros = 0;
			}
		}
	}

	return counter;
}

// ---------------------------------------------------------------------------

__fastcall TLab6::TLab6(TComponent* Owner) : TForm(Owner) {
}
// ---------------------------------------------------------------------------

void __fastcall TLab6::InputStringEditKeyPress(TObject *Sender, System::WideChar &Key) {
	// �������� ������� �� enter
	if (Key == VK_RETURN) {
		OutputResultField -> Text = findUnitCount(InputStringEdit -> Text);
	}
}
// ---------------------------------------------------------------------------
void __fastcall TLab6::CloseButtonClick(TObject *Sender) {
    // ������ �������� 'close'
    Lab6 -> Close();
}
//---------------------------------------------------------------------------



