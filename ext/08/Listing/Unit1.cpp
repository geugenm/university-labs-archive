//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include "ustring.h"
//---------------------------------------------------------------------------

#pragma package(smart_init)
#pragma link "perfgrap"
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
	/* Определение математических функций */
double Factorial(double target) {
    // Функция факториала
	double result = 1;

	for(int i = 1; i <= target; i++) {
		result *= i;
	}
    return result;
}
//---------------------------------------------------------------------------
	/* Определение функций для задания, согласно п. 3.3.2 (5) */
double FunctionS(double x_arg, double sum_limit) {
    // Функция S(x)
	double result = 0;

	for(int i = 0; i <= sum_limit; i++) {
		result += cos(i * x_arg) / Factorial(i);
	}
	return result;
}

double FunctionY(double x_arg, double place_holder) {
    // Функция Y(x)
	return pow(M_E, cos(x_arg)) * cos(sin(x_arg));
}
//---------------------------------------------------------------------------
	/* Определение функции вывода */
	// ЗАМЕТКА:
	// 	Крайне нагруженная функция из-за огромного числа аргументов.
	//  Каждый из этих аргументов необходим либо для самих функций, либо
	//  для таблицы и ее размеров.
    //
	//  Возможно было сделать гораздо легче, если бы не было задания создать
	//  одну функцию для вывода
void Out_Rez(double Function_1(double el_1, double el_2), double Function_2(double el_1, double el_2),
	 double x_lower, double x_upper, double x_step, double sum_limit, TStringGrid *Table, int cols,
	 int rows, bool IsSubstract) {

	for(int i = 0; i < cols; i++) {
		for(int j = 0; j < rows; j++) {
			double local_arg = x_lower + x_step * j; // Инкремента аргумента
				if(local_arg <= x_upper) {
					// Проверяем не выходит аргумент за верхний предел
					if (IsSubstract) {
                        // Проверка на наличие запроса вывода разности
                        Table -> Cells[0][j] = local_arg;
						Table -> Cells[1][j] = abs(Function_1(local_arg, sum_limit)
						- Function_2(local_arg, sum_limit));
					}
					else {
                        // Если запроса не было, то выводим значение функции
                        Table -> Cells[0][j] = local_arg;
						Table -> Cells[1][j] = Function_1(local_arg, sum_limit);
					}
			}
		}
	}
}
//---------------------------------------------------------------------------

__fastcall TForm1::TForm1(TComponent* Owner) : TForm(Owner) {
}
//---------------------------------------------------------------------------

void __fastcall TForm1::CalculateButtonClick(TObject *Sender) {
	// Функция нажатия кнопки 'Calculate'
	double alpha_param = AlphaParameterEdit -> Text.ToDouble();
	double beta_param = BetaParameterEdit -> Text.ToDouble();

	double h_param = HParameterEdit -> Text.ToDouble();
	double n_param = NParameterEdit -> Text.ToDouble();

    /* Параметры таблицы */
	int table_rows = 9;
	int table_cols = 2;

	switch(CalculateRadioGroup -> ItemIndex) {
        // Проверка выбранной опции в 'Configuration'
		case 0:
            // Активно при выборе Y(x)
			Out_Rez(FunctionY, FunctionS, alpha_param, beta_param, h_param,
				n_param, FunctionOutputGrid, table_cols, table_rows, false);
			break;
		case 1:
			// Активно при выборе S(x)
			Out_Rez(FunctionS, FunctionY, alpha_param, beta_param, h_param,
				n_param, FunctionOutputGrid, table_cols, table_rows, false);
			break;
		case 2:
			// Активно при выборе разности функций
			Out_Rez(FunctionY, FunctionS, alpha_param, beta_param, h_param,
				n_param, FunctionOutputGrid, table_cols, table_rows, true);
			break;
		default:
            // Если ничего не выбрано
            ShowMessage("An error occured!");
	}

}
//---------------------------------------------------------------------------

