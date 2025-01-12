//Объявить шаблон класса «Двусвязный линейный список». Определить структуру класса и его методы.
//В классе должен быть конструктор по умолчанию, конструктор с формальными параметрами, конструктор копирования и деструктор.
//Определить методы :
//• инициализация первого элемента структуры;
//• запись в структуру нового элемента;
//• удаление элемента;
//• поиск элемента по заданному ключу поиска(значению информационного поля);
//• вывод элементов списка на экран;
//• удаления всех элементов списка.
//Используя объекты класса «Двусвязный линейный список», реализовать алгоритм своего варианта задания 7.6.
//7.6
//Выполнить задания, используя двусвязные динамические структуры данных в виде связных компонент. Оценить асимптотическую сложность алгоритма.
//8. Даны натуральное число n, действительные числа a1, a2, ..., a2n. Получить  a(n)*a(n+1)+a(n-1)*a(n+2)+..+a(1)*a(2n).


#include <iostream>
#include <ctime>

using namespace std;

template <class T>
struct link {
	T number;
	link * next;
	link * pred;
};

template <class T>
class Spisok {
private:
	link<T> * first;
	link<T> * last;
public:
	Spisok() { //конструктор без аргументов
		first = NULL;
		last = first;
	}

	Spisok(int n) { //конструктор инициализации
		first = NULL;
		last = first;
		for (int i = 0; i < n; i++) {
			AddNewElement(-1);
		}
	}

	Spisok(const Spisok & sp) { //собственный конструктор копирования
		first = NULL;
		last = first;
		link<T> * current = sp.last;
		while (current) {
			AddNewElement(current->number);
			current = current->pred;
		}
	}

	~Spisok() { //деструктор
		link<T> * pv;
		while (first) {
			pv = first;
			first = first->next;
			if (first) {
				first->pred = NULL;
			}
			else {
				last = NULL;
			}
			delete pv;
		}
	}

	void FirstElement(T n) { //добавление первого элемента в список
		if (first == NULL) {
			link<T> * newlink = new link<T>;
			newlink->number = n;
			newlink->next = first;
			newlink->pred = last;
			first = newlink;
			last = newlink;
		}
	}

	void AddNewElement(T n) { //добавление элемента в список
		link<T> * newlink = new link<T>;

		newlink->number = n;
		newlink->next = NULL;
		newlink->pred = NULL;
		if (!first) {
			first = newlink;
			last = newlink;
		}
		else {
			newlink->next = first;
			first->pred = newlink;
			first = newlink;
		}
	}

	void EraseElement(T key) { //удаление элемента с определенным значение информационного поля
		while (FindElement(key)) {
			link<T> * pv, * ppv;
			if (first->number == key) {
				pv = first;
				first = first->next;
				if (first) {
					first->pred = NULL;
				}
				else {
					last = NULL;
				}
				delete pv;
			}
			else {
				pv = first;
				ppv = first;
				while (pv && (pv->number != key)) {
					ppv = pv;
					pv = pv->next;
				}
				ppv->next = pv->next;
				if (pv->next) {
					pv->next->pred = ppv;
				}
				else {
					last = ppv;
				}
				delete pv;
			}
		}
	}

	bool FindElement(T key) { //поиск элемента по заданному значению информационного поля
		link<T> * current = first;
		while (current) {
			if (current->number == key) {
				return true;
			}
			current = current->next;
		}
		return false;
	}

	void Print() { //вывод списка на экран
		link<T> * current = first;
		while (current) {
			cout << current->number << " ";
			current = current->next;
		}
		cout << endl;
	}

	void Print2() { //вывод списка на экран
		link<T> * current = last;
		while (current) {
			cout << current->number << " ";
			current = current->pred;
		}
		cout << endl;
	}

	void DeleteSpisok() { //удаление списка
		link<T> * pv;
		while (first) {
			pv = first;
			first = first->next;
			if (first) {
				first->pred = NULL;
			}
			else {
				last = NULL;
			}
			delete pv;
		}
	}

	void FillingDouble(int n) { //рандомит и добавляет в список n элементов
		srand(time(0));
		for (int i = 0; i < n; i++) {
			AddNewElement(rand() % 10 + rand() % 10 * 1.0 / 10);
		}
	}

	int Size() {
		int size = 0;
		link<T> * current = first;
		while (current) {
			size++;
			current = current->next;

		}
		return size;
	}

	T & operator[](const int index) {
		if (index < 0 || index >= Size()) {
			exit(1);
		}
		else {
			link<T> * current = first;
			for (int i = 0; i < index; i++) {
				current = current->next;
			}
			return current->number;

		}

	}
};
using namespace std;

double Result(Spisok<double> A) {
	double Sum = 1;
	for (int i = 0; i < A.Size(); i++) {
		Sum *= (A[i] + A[A.Size() - i - 1]);
	}
	return Sum;
}

void runBeta_2_3() {
	cout << "Enter n: ";
	int n;
	cin >> n;
	Spisok<double> A;
	A.FillingDouble(n);
	cout << "Spisok A: " << endl;
	A.Print();
	cout << "Result: ";
	cout << Result(A) << endl;
	A.DeleteSpisok();
}