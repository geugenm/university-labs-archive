//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------

#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
 /* Глобальные переменные(необх. для работы с матрицей, без переопределений) */
int max_height = 8;
int max_width = 8;

int user_height = 8;
int user_width = 8;

int **initial_matrix = new int*[max_height]; // Двумерный массив(матрица)
// (Ширина будет доопределена при заполнении. Создадим массив массивов)

int findInternalElement(int **matrix, int width, int height) {
	// Функция поиска элемента, удов. условиям задачи
	int count = 0;
	for (int i = 1; i < width - 1; i++) {
		// Начинаем с 1, т.к. нам нужен элемент между
		for (int j = 0; j < height; j++) {
			if(matrix[i - 1][j] < matrix[i][j] && matrix[i + 1][j] > matrix[i][j]) {
				// Если вып. условия задачи, то добавляем + 1 к счетчику
				// count++ <=> count = count + 1
                count++;
			}
		}
	}
    return count;
}
//---------------------------------------------------------------------------

__fastcall TForm1::TForm1(TComponent* Owner) : TForm(Owner) {
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormCreate(TObject *Sender) {
	// Функция заполнения матрицы при запуске
	randomize();

	for(int i = 0; i < max_height; i++) {
		initial_matrix[i] = new int[max_height]; // Создаем двумерный массив
		// (или массив массивов)
		for(int j = 0; j < max_height; j++) {
			// Само заполнение случайными числами
			initial_matrix[i][j] = random(7) - 5;
			MatrixGrid -> Cells[i][j] = IntToStr(initial_matrix[i][j]);
		}
	}

	// Поиск элементов удовл. задаче в матрице при запуске
	OutputResultField -> Text = IntToStr(findInternalElement(initial_matrix, max_width, max_height));
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ApplyMatrixSizeButtonClick(TObject *Sender) {
	// Функция отвечающая за нажатие на кнопку 'Apply'
	user_height = StrToInt(MatrixHeightEdit -> Text);
	user_width = StrToInt(MatrixWidthEdit -> Text);

	// Булевые переменные(Правда/Ложь) проверяющие размеры матрицы
	bool verify_height = user_height > 0 && user_height <= max_height;
	bool verify_width = user_width > 0 && user_width <= max_height;

	if(verify_height && verify_width) {
		// Если размеры правильны, то:
		MatrixGrid -> RowCount = user_width;
		MatrixGrid -> ColCount = user_height;

		for(int i = 0; i < user_width; i++) {
			for(int j = 0; j < user_height; j++) {
				// Изменение размера
				MatrixGrid -> Cells[i][j] = IntToStr(initial_matrix[i][j]);
            }
		}

		// Поиск элементов удовл. задаче в заданном пользователем диапазоне
		OutputResultField -> Text = IntToStr(findInternalElement(initial_matrix, user_width, user_height));
	}
	else {
        ShowMessage("Incorrect matrix size!");
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::GenerateNewMatrixButtonClick(TObject *Sender) {
    // Функция генерации нового массива, кнопка 'Generate new'
	randomize();

	for(int i = 0; i < max_height; i++) {
		initial_matrix[i] = new int[max_height];
		for(int j = 0; j < max_height; j++) {
			initial_matrix[i][j] = random(7) - 5;
			MatrixGrid -> Cells[i][j] = IntToStr(initial_matrix[i][j]);
		}
	}

	// Поиск элементов удовл. задаче в максимальном диапазоне
	OutputResultField -> Text = IntToStr(findInternalElement(initial_matrix, user_width, user_height));
}
//---------------------------------------------------------------------------
