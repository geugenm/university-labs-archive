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
	/* ����������� �������������� ������� */
double Factorial(double target) {
    // ������� ����������
	double result = 1;

	for(int i = 1; i <= target; i++) {
		result *= i;
	}
    return result;
}
//---------------------------------------------------------------------------
	/* ����������� ������� ��� �������, �������� �. 3.3.2 (5) */
double FunctionS(double x_arg, double sum_limit) {
    // ������� S(x)
	double result = 0;

	for(int i = 0; i <= sum_limit; i++) {
		result += cos(i * x_arg) / Factorial(i);
	}
	return result;
}

double FunctionY(double x_arg, double place_holder) {
    // ������� Y(x)
	return pow(M_E, cos(x_arg)) * cos(sin(x_arg));
}
//---------------------------------------------------------------------------
	/* ����������� ������� ������ */
	// �������:
	// 	������ ����������� ������� ��-�� ��������� ����� ����������.
	//  ������ �� ���� ���������� ��������� ���� ��� ����� �������, ����
	//  ��� ������� � �� ��������.
    //
	//  �������� ���� ������� ������� �����, ���� �� �� ���� ������� �������
	//  ���� ������� ��� ������
void Out_Rez(double Function_1(double el_1, double el_2), double Function_2(double el_1, double el_2),
	 double x_lower, double x_upper, double x_step, double sum_limit, TStringGrid *Table, int cols,
	 int rows, bool IsSubstract) {

	for(int i = 0; i < cols; i++) {
		for(int j = 0; j < rows; j++) {
			double local_arg = x_lower + x_step * j; // ���������� ���������
				if(local_arg <= x_upper) {
					// ��������� �� ������� �������� �� ������� ������
					if (IsSubstract) {
                        // �������� �� ������� ������� ������ ��������
                        Table -> Cells[0][j] = local_arg;
						Table -> Cells[1][j] = abs(Function_1(local_arg, sum_limit)
						- Function_2(local_arg, sum_limit));
					}
					else {
                        // ���� ������� �� ����, �� ������� �������� �������
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
	// ������� ������� ������ 'Calculate'
	double alpha_param = AlphaParameterEdit -> Text.ToDouble();
	double beta_param = BetaParameterEdit -> Text.ToDouble();

	double h_param = HParameterEdit -> Text.ToDouble();
	double n_param = NParameterEdit -> Text.ToDouble();

    /* ��������� ������� */
	int table_rows = 9;
	int table_cols = 2;

	switch(CalculateRadioGroup -> ItemIndex) {
        // �������� ��������� ����� � 'Configuration'
		case 0:
            // ������� ��� ������ Y(x)
			Out_Rez(FunctionY, FunctionS, alpha_param, beta_param, h_param,
				n_param, FunctionOutputGrid, table_cols, table_rows, false);
			break;
		case 1:
			// ������� ��� ������ S(x)
			Out_Rez(FunctionS, FunctionY, alpha_param, beta_param, h_param,
				n_param, FunctionOutputGrid, table_cols, table_rows, false);
			break;
		case 2:
			// ������� ��� ������ �������� �������
			Out_Rez(FunctionY, FunctionS, alpha_param, beta_param, h_param,
				n_param, FunctionOutputGrid, table_cols, table_rows, true);
			break;
		default:
            // ���� ������ �� �������
            ShowMessage("An error occured!");
	}

}
//---------------------------------------------------------------------------

