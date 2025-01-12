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
	// Функция поиска единиц в нечетных группах (разделитель - любой символ)
	int counter = 0;
    int local_zeros = 0;
	int local_ones = 0;

	for (int i = 0; i <= user_string.Length(); i++) {
		// Цикл идет по занчение длины (циклы нумеруются с 0, поэтому обычно
		// используется строгое равенство. Причина - включение терминирующего
		// строчного элемента '\0')
		if (user_string.c_str()[i] == 49) {
			// Идет сопоставление с таблицей ASCII (49 - это 1)
			local_ones++;
		}
		else {
			if (user_string.c_str()[i] == 48) {
				// Идет сопоставление с таблицей ASCII (48 - это 0)
				local_zeros++;
			}
            else {
				if ((local_zeros + local_ones) % 2 != 0) {
					// Проверка на нечетность
					counter += local_ones;
				}
				// Переход к след. группе элементов после произвольн. разделителя
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
	// Проверка нажатия на enter
	if (Key == VK_RETURN) {
		OutputResultField -> Text = findUnitCount(InputStringEdit -> Text);
	}
}
// ---------------------------------------------------------------------------
void __fastcall TLab6::CloseButtonClick(TObject *Sender) {
    // Кнопка закрытия 'close'
    Lab6 -> Close();
}
//---------------------------------------------------------------------------



