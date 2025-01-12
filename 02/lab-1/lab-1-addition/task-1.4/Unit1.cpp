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
	// Функция подсчета среднего балла по трем предметам
	float result = 0;

	for(int i = 2; i < Table -> ColCount - 1; i++) {
        // Суммируем все в одну переменную
		result += StrToFloat(Table -> Cells[i][target_user]);
	}

	return FloatToStr(result / 3);
}
//---------------------------------------------------------------------------

void OpenFile(TStringGrid *Table) {
    // Функция заполнения таблицы приложения данными из файла
	TStringList *Table1 = new TStringList;
	// Загружаем нашу вспомогательную таблицу
	Table1 -> LoadFromFile(user_list_file_name);

	// Задаем кол-во строк в Table из вспомогательной таблицы
	Table -> RowCount = Table1 -> Count;

	for(int i = 0 ; i < Table -> RowCount; i++) {
		// Копируем (построчно) данные с вспомогательной таблицы в Table
	  Table -> Rows[i] -> DelimitedText = Table1->Strings[i];
	}

    // Очистка памяти занимаемой вспомогательной таблицей
	delete Table1;
}
//---------------------------------------------------------------------------

void FillRow(TStringGrid *Table, TEdit *usr_initials, TEdit *usr_group, TEdit *usr_phys,
			 TEdit *usr_math, TEdit *usr_prog, int arg) {
	// Функция заполнения строки. Активна при создании / редактировании элемента
	// ВАЖНО!!! Инициалы вводить с любым разделителем кроме пробела!
	// 	Причина - в стандартной функции Sort() деление происходит через пробел
	//  можно было изменить саму библиотеку, но тогда программа бы запускалась
	//  только у меня, т.к. у всех это библиотека не изменяется

    //Проверка правильности введенных данных
	if(StrToInt(usr_phys -> Text) < 10 && StrToInt(usr_phys -> Text) >= 0 &&
	   StrToInt(usr_math -> Text) < 10 && StrToInt(usr_math -> Text) >= 0 &&
	   StrToInt(usr_prog -> Text) < 10 && StrToInt(usr_prog -> Text) >= 0)
	{
        // Заполнение колонок строки
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
	// Функция сортировки по столбцу
	// ЗАМЕТКА:
	//  Данный алгоритм работает только в диапазоне от 0 до 10(Как раз нужный нам)
	//  Для универсального метода требуется огромное кол-во библиотек.
	//  Тут используем встроенную функцию сортировки списков Sort()

	TStringList *lst  = new TStringList;
	TStringList *lst1 = new TStringList;

	for(int i = 0; i < Table -> RowCount; ++i) {
		// Загоняем все в лист и через разделительный знак,
		// запоминаем номер строки, что бы после все передвинуть
		lst -> Add(Table -> Cells[col_sort][i] + "~" + IntToStr(i));
	}

    // Сортируем
	lst -> Sort();

	for(int i = 0 ; i < Table -> RowCount; ++i) {
		// Делаем дупликат таблицы,что бы поней после пересобрать основную
		lst1 -> Add(Table -> Rows[i] -> Text);
	}

	for(int i = 0; i < Table -> RowCount; ++i) {
        //Строим отсортированую таблицу
		Table -> Rows[i] -> DelimitedText = lst1 -> Strings[lst ->
		Strings[i].SubString(lst -> Strings[i].Pos("~")
		+ 1, lst -> Strings[i].Length()).ToInt()];
	}

    // Очистка памяти
	delete lst;
	delete lst1;
}
//---------------------------------------------------------------------------

void __fastcall TLab7::CreateUserFileButtonClick(TObject *Sender) {
    // Функция, отвечающая за создание и последующее открытие файла
    OpenUserFileDialog -> Title = "Create New File";

	if(OpenUserFileDialog -> Execute()) {
        // Получаем из диалогового окна имя файла и открываем его
		user_list_file_name = OpenUserFileDialog -> FileName;
		USER_LIST = fopen(AnsiString(user_list_file_name).c_str(), "wb");
		if(USER_LIST) {
            // Закрываем файл и переходим к потоку
			fclose(USER_LIST);
			std::ofstream outfile;

            // Создание 0-пользователя, как шаблон
			outfile.open(AnsiString(user_list_file_name).c_str(), std::ios::trunc);
			outfile << "0 0 0 0 0 0";
			outfile.close();

            // Открываем файл и очищаем память
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
    // Функция открытия уже созданного файла
	OpenUserFileDialog -> Title = "Open a file";

	if(OpenUserFileDialog -> Execute()) {
        // Получаем из диалогового окна имя файла и открываем его
		user_list_file_name = OpenUserFileDialog -> FileName;
		USER_LIST = fopen(AnsiString(user_list_file_name).c_str(), "rb");
		if(USER_LIST) {
            // Заполняем таблицу и очищаем память
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
    // Функция сохранения файла
	if(USER_LIST) {
        // Открываем поток
		std::ofstream outfile;

        // Вводим поток в режим перезаписи файла(trunc)
		outfile.open(AnsiString(user_list_file_name).c_str(), std::ios::trunc);
		for(int i = 0; i < OutputGrid -> RowCount; i++) {
			for(int j = 0; j < OutputGrid -> ColCount; j++) {
				if (j == OutputGrid -> ColCount - 1) {
                    // Если дошли до конца строки, то заканчиваем ее с endl
                    outfile << AnsiString(OutputGrid -> Cells[j][i]).c_str() << std::endl;
				}
				else {
					// В ином случае просто добавляем разделитель - пробел " ")
					outfile << AnsiString(OutputGrid -> Cells[j][i]).c_str() << " ";
				}
			}
		}
        // Закрытие потока и очистка памяти
		outfile.close();
        fclose(USER_LIST);
	}
	else {
		ShowMessage("First open the file");
    }
}
//---------------------------------------------------------------------------

void __fastcall TLab7::FindSpecialUsersClick(TObject *Sender) {
	// Функция поиска целевого пользователя
	if(USER_LIST) {
		for(int i = 0; i < OutputGrid -> RowCount; i++) {
			if(StrToFloat(OutputGrid -> Cells[2][i]) >= 4.0 && StrToFloat(OutputGrid -> Cells[2][i]) <= 5.0) {
				if(StrToFloat(OutputGrid -> Cells[3][i]) >= 8.0 && StrToFloat(OutputGrid -> Cells[4][i]) >= 8.0) {
                    // Выделяем целевую строку
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
    // Функция добавления записи о пользователе
	if(USER_LIST) {
        // Добавляем строчку
		OutputGrid -> RowCount += 1;
        // Заполняем строку
		FillRow(OutputGrid, InitialsInputEdit, UserGroupInputEdit, InputRatingPhysEdit,
				InputRatingMathEdit, InputRatingITEdit, (OutputGrid -> RowCount) - 1);
	}
    else {
		ShowMessage("First open the file");
	}
}
//---------------------------------------------------------------------------

void __fastcall TLab7::DeleteUserButtonClick(TObject *Sender) {
    // Функция удаления записи о пользователе
	if(USER_LIST) {
        // Текущая строка
		int Index = OutputGrid -> Selection.Top;
		if(Index != OutputGrid -> RowCount - 1) {
            // Если вообще выбрана какая-нибудь строка
			for(int i = Index; i < OutputGrid -> RowCount - 1; i++) {
				// С текущей строки до последней затираем текущую строку следующей
				OutputGrid -> Rows[i] = OutputGrid -> Rows[i + 1];
			}
            // Удаляем последнюю строку
			OutputGrid->RowCount--;
		}
	}
	else {
		ShowMessage("First open the file");
	}
}
//---------------------------------------------------------------------------

void __fastcall TLab7::EditUserButtonClick(TObject *Sender) {
    // Функция редактирования записи о пользователе
	if(USER_LIST) {
        // Заполняем строку
		FillRow(OutputGrid, InitialsInputEdit, UserGroupInputEdit, InputRatingPhysEdit,
				InputRatingMathEdit, InputRatingITEdit, OutputGrid -> Selection.Top);
	}
	else {
		ShowMessage("First open the file");
	}
}
//---------------------------------------------------------------------------

void __fastcall TLab7::UserSortAlphButtonClick(TObject *Sender) {
    // Сортировка по имени
	if(USER_LIST) {
		SortGridCol(OutputGrid, 0);
	}
	else {
		ShowMessage("First open the file");
	}
}
//---------------------------------------------------------------------------

void __fastcall TLab7::UserSortGrpButtonClick(TObject *Sender) {
    // Сортировка по группе
	if(USER_LIST) {
		SortGridCol(OutputGrid, 1);
	}
	else {
		ShowMessage("First open the file");
	}
}
//---------------------------------------------------------------------------

void __fastcall TLab7::UserSortPhysButtonClick(TObject *Sender) {
    // Сортировка по результатам физики 'phys'
    if(USER_LIST) {
		SortGridCol(OutputGrid, 2);
	}
	else {
		ShowMessage("First open the file");
	}
}
//---------------------------------------------------------------------------

void __fastcall TLab7::UserSortMathButtonClick(TObject *Sender) {
	// Сортировка по результатам фматематики 'math'
	if(USER_LIST) {
		SortGridCol(OutputGrid, 3);
	}
	else {
		ShowMessage("First open the file");
	}
}
//---------------------------------------------------------------------------

void __fastcall TLab7::UserSortITButtonClick(TObject *Sender) {
    // Сортировка по результатам программирования 'it'
    if(USER_LIST) {
		SortGridCol(OutputGrid, 4);
	}
	else {
		ShowMessage("First open the file");
	}
}
//---------------------------------------------------------------------------

void __fastcall TLab7::UserSortAvrgButtonClick(TObject *Sender) {
	// Сортировка по среднему баллу 'Average'
	if(USER_LIST) {
		SortGridCol(OutputGrid, 5);
	}
	else {
		ShowMessage("First open the file");
	}
}
//---------------------------------------------------------------------------

void __fastcall TLab7::FormClose(TObject *Sender, TCloseAction &Action) {
    // Функция закрытия окна
	fclose(USER_LIST);
}
//---------------------------------------------------------------------------

