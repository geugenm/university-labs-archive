//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------

#pragma package(smart_init)
#pragma resource "*.dfm"
TLab4 *Lab4;
//---------------------------------------------------------------------------
 /* Глобальные переменные(необх. для работы с массивом, без переопределений) */
int max_array_size = 8;
int user_size = max_array_size;

int *initial_array = new int[max_array_size];
//---------------------------------------------------------------------------

int CalculateMultiplication(int array[], int array_size) {
	// Функция считает произведение элементов, распол. между нулевыми элементами
	// По умолчанию, если условия не будут выполнены, получим значение '0'
	int result = 0;

	for(int i = 0; i < array_size; i++) {
		// Ищем первый ноль
		if(array[i] == 0) {
			// Если нашли 0, приступаем к произведению чисел до второго 0
			for(int j = i + 1; j < array_size && array[j] != 0; j++) {
				if(j == (i + 1)) {
					// Подготовка result к произведению
					// (меняется при первой итерации)
					result = 1;
				}
				if(j == array_size - 1) {
					// Т.к. в условии for идет проверка на ноль (array[j] != 0),
					// то дойдя до сюда второго нуля не будет => возвр. 0
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
	// Функция заполнения поля массивом при запуске
	randomize();

	// По умолчанию при запуске будет стоять значение 8
	ArraySizeEdit -> Text = IntToStr(max_array_size);
	InitialArrayGrid -> ColCount = max_array_size;

	for(int i = 0; i < max_array_size; i++) {
		// Проводим заполнение массива, выводя каждый его элемент
		initial_array[i] = random(7) - 5;
		InitialArrayGrid -> Cells[i][0] = IntToStr(initial_array[i]);
	}

	// Вывод произведения
	OutputResultField -> Text = IntToStr(CalculateMultiplication(initial_array, max_array_size));
}
//---------------------------------------------------------------------------

void __fastcall TLab4::ApplyArraySizeButtonClick(TObject *Sender) {
	// Функция изменения размера выведенного массива на экран
	user_size = StrToInt(ArraySizeEdit -> Text);

	// Проверяем правильность введенного размера массива
	if(user_size > 0 && user_size <= max_array_size) {
        InitialArrayGrid -> ColCount = user_size;

		for(int i = 0; i < user_size; i++) {
			// Меняем кол-во элементов на экране
			InitialArrayGrid -> Cells[i][0] = IntToStr(initial_array[i]);
		}

		// Вывод произведения
		OutputResultField -> Text = IntToStr(CalculateMultiplication(initial_array, user_size));
	}
	else {
        ShowMessage("Incorrect array size!");
    }

}
//---------------------------------------------------------------------------

void __fastcall TLab4::GenerateNewArrayButtonClick(TObject *Sender) {
	// Функция генерации нового массива
	randomize();

	for(int i = 0; i < max_array_size; i++) {
		// Проводим заполнение массива, выводя каждый его элемент
		initial_array[i] = random(7) - 5;
		InitialArrayGrid -> Cells[i][0] = IntToStr(initial_array[i]);
	}

    // Вывод произведения
	OutputResultField -> Text = IntToStr(CalculateMultiplication(initial_array, user_size));
}
//---------------------------------------------------------------------------