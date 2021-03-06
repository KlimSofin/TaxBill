﻿#include "Bill.h"
#include<vector>
#include <fstream>
#include <string>
using std::cout;
using std::cin;
using std::endl;
using std::vector;

//Функции управления(main)
void Console_Input(vector<Bill*>&t); //Консольный Ввод
void Main_Console_Output(vector<Bill*>&t);//Консольный Вывод
void File_Input(vector<Bill*>&t);//Ввод из файла
void File_Output(vector<Bill*>&t);//Сохранение в файл
void Exit(vector<Bill*>&t);//Выход из приложения
bool Change_By_Date(vector<Bill*>&t);//Изминение данных по дате
void Sort(vector<Bill*>&t, int l, int r);//Функция выполняющая сортировки
//Алгоритмы сортировки
void Sort_Ascending(vector<Bill*>&t, int l, int r);//Сортировка по убыванию
void Descending_Sort(vector<Bill*>&t, int l, int r);//Сортировка по возрастанию
int partition(vector<Bill*>&t, int l, int r);
int rand_chose(vector<Bill*>&t, int l, int r);
void Quick_Sort_Ascending(vector<Bill*>&t, int l, int r);
//Вспомогательный функции
void Clear(vector<Bill*>&t);// Очистка
void Type_Console_Output(vector<Bill*>&t);//Вывод на консоль по типу данных

int count = 0;

int main()
{
	vector<Bill*>tax;
	int input;
	while (true)
	{
		setlocale(LC_ALL, "Rus");
		std::cout << "Выберети пункт.\n";
		std::cout << "1.Ввод с консоли.\n"
			<< "2.Вывод на  консоль.\n"
			<< "3.Ввод из  файла.\n"
			<< "4.Сохранение в  файл.\n"
			<< "5.Изменение по дате\n"
			<< "6.Сортировка\n"
			<< "100.Выход.\n"
			<< ": ";
		if (!(cin >> input))
		{
			cin.clear();
			cin.get();
			cout << "Не корректный ввод.\n";
			continue;
		}
		switch (input) //Начало отработки меню
		{
		case 1://Ввод с консоли
			Console_Input(tax);
			break;
		case 2://Ввод на консоль
			Main_Console_Output(tax);
			break;
		case 3://Ввод из файла
			File_Input(tax);
			break;
		case 4://Сохранение в файл
			File_Output(tax);
			break;
		case 5://Изменение по дате
			if (Change_By_Date(tax))
				std::cout << "Успешно изменено.\n";
			else
				std::cout << "Не изменено.\n";
			break;
		case 6://Сортировка
			Sort(tax, 0, tax.size() - 1);
			break;
		case 100://Выход
			Exit(tax);
			return 0;
		default:
			std::cout << "Выбран неверный номер.\n";
			break;
		}
	}
	return 0;
}
//Функции управления(main)
void Console_Input(vector<Bill*>&t)
{
	char type_of_bill;
	int quantity;
	cout << "Введите колличество счетов, которое планируется ввести.\n"
		<< ": ";
	cin >> quantity;
	while (quantity != 0)
	{

		cout << "Введите тип налога e(E) - эллектричество, j(J) - ЖКХ(q,Q -отмена ввода.\n"
			<< ": ";
		cin >> type_of_bill;
		switch (type_of_bill) //Обработка типа налогов

		{
		case 'e':case 'E':
			t.push_back(new Electricity_Bill());
			t[count++]->Create(); //Добавление файлов с консоли
			quantity--;
			break;
		case 'j':case 'J':
			t.push_back(new JKH());
			t[count++]->Create();//Добавление файлов с консоли
			quantity--;
			break;
		case 'q':case 'Q':
			std::cout << "Отмена ввода\n";
			return;
		default:
			std::cout << "Неверный ввод\n";
			break;

		}
	}
}
void Main_Console_Output(vector<Bill*>&t)
{
	std::cout << " Вывод информции.\n"
		<< "1.Вывести все.\n"
		<< "2.Вывод по типу счета.\n"
		<< ": ";
	int chose;
	cin >> chose;
	cin.get();
	switch (chose)
	{
	case 1:

		for (int i = 0; i < count; i++)
			t[i]->Output();
		break;
	case 2:
		Type_Console_Output(t);
	default:
		break;
	}

}
void Type_Console_Output(vector<Bill*>&t) //Вывод по типу счета
{
	std::cout << "Счета какого типа вывести.\n"
		<< "1.Электричество.\n"
		<< "2.ЖКХ.\n"
		<< ": ";
	unsigned int chose;
	cin >> chose;
	cin.get();
	switch (chose)
	{
	case 1:
		for (int i = 0; i < count; i++)
			if (t[i]->name_of_bill() == "Электричество")
				t[i]->Output();
		break;
	case 2:
		for (int i = 0; i < count; i++)
			if (t[i]->name_of_bill() == "ЖКХ")
				t[i]->Output();
		break;
	default:
		break;
	}
}
void File_Input(vector<Bill*>&t)
{
	std::string file_name, read_line; //Переменные для имени файла и строки
	std::ifstream fin;
	cin.get();
	std::cout << "Введите название файла или quit для отмены считывания\n"
		<< ": ";
	std::getline(std::cin, file_name);
	if (file_name == "quit")
	{
		std::cout << "Отменна ввода\n";
		return;
	}
	fin.open(file_name);
	if (!fin.is_open())
	{
		std::cout << "Невозможно открыть файл\n";
		return;
	}
	while (getline(fin, read_line))
	{

		if (read_line[0] == 'Э')
		{
			t.push_back(new Electricity_Bill());
			t[count++]->Read_File(read_line);
		}
		else if (read_line[0] == 'Ж')
		{
			t.push_back(new JKH());
			t[count++]->Read_File(read_line);
		}
	}
	cout << "Считано\n";
}
void File_Output(vector<Bill*>&t)
{
	std::string file_name;
	char check_ch, chose;
	cin.get();
	std::cout << "Введите название файла или quit для отмены сохранения\n"
		<< ": ";
	std::getline(std::cin, file_name);
	if (file_name == "quit")
	{
		std::cout << "Отменна ввода\n";
		return;
	}
	std::ifstream f_check(file_name); //Используется для проверки на существование файла
	std::ofstream clear; //Используется для очистки файлов
	if (f_check.is_open()) //Проверка на существование 
	{
		f_check >> check_ch;
		if (!f_check.eof()) //Проверка на конец файла, нужна для определения пуст ли файл или нет 
		{

			f_check.close();
			std::cout << "В файле есть информация стереть ее или добавить к ней новую?(r/a): ";
			cin >> chose;
			switch (chose)
			{
			case 'a':case'A'://Добавить новую информацию к уже существующей 
				for (int i = 0; i < count; i++)
					t[i]->Save(file_name);
				break;
			case 'r':case'R'://Перезаписать файл
				clear.open(file_name);
				clear.close();
				clear.open("Val" + file_name);
				clear.close();
				for (int i = 0; i < count; i++)
					t[i]->Save(file_name);
				break;
			default:
				std::cout << "Неверный ввод\n Отмена сохранения.";
				return;
			}
		}
		else //Файл пуст
		{
			for (int i = 0; i < count; i++)
				t[i]->Save(file_name);
		}
	}
	else //Файл не существует
	{
		for (int i = 0; i < count; i++)
			t[i]->Save(file_name);
	}
	std::cout << "Сохранено\n";
}
bool Change_By_Date(vector<Bill*>&t)
{

	Bill::Date check_date;
	int chose;
	char type_of_bill;
	auto ptr = t.begin(); // Указатель на перый элемент вектора
	std::cout << "Что вы хотите изменить(введите любой символ для отмены)?\n"
		<< "1.Данные счета(дата,сумма оплаты,задолженность)\n"
		<< "2.Тип счета\n"
		<< "3.Удалить счет\n"
		<< ": ";
	if (!(cin >> chose) || chose > 3)//Проверка ввода
	{
		cin.clear();
		cin.get();
		std::cout << "Отмена редактирования\n";
		return false;
	}
	std::cout << "Введите дату счета, который хотите изменить\n";
	cin >> check_date;
	cin.get();
	for (; ptr != t.end(); ptr++)
		if ((*ptr)->date == check_date)// определяем нужный нам счет
		{
			(*ptr)->Output();
			cout << "Вы хотите изменить этот счет(y/n)\n";
			char chose;
			cin >> chose;
			if (chose == 'y')
				break;
		}
	if (ptr == t.end())
		return false;

	switch (chose)
	{
	case 1:
		(*ptr)->Change();
		return true;
	case 2:
		cout << "Введите тип налога e - эллектричество j - ЖКХ.\n"
			<< ": ";
		cin >> type_of_bill;
		while (true)
		{

			switch (type_of_bill)
			{
			case 'e':case'E':
				delete (*ptr);
				(*ptr) = new Electricity_Bill();
				(*ptr)->Create();
				return true;
			case 'j':case'J':
				delete (*ptr);
				(*ptr) = new JKH();
				(*ptr)->Create();
				return true;
			default:
				std::cout << "Неверный ввод\n";
				break;
			}
		}
	case 3:
		delete (*ptr);
		t.erase(ptr);
		count--;
		return true;
	default:
		std::cout << "Неверный ввод, возврат в меню.\n";
		break;
	}
	return false;
}
//Вспомогательный функции
void Clear(vector<Bill*>&t)
{
	for (auto &i : t)
		delete i;
}
void Exit(vector<Bill*>&t)
{
	char chose;
	std::cout << "Сохранить следующую информацию в файл?\n";
	Main_Console_Output(t);
	while (true)
	{
		std::cout << "y/n: ";
		cin >> chose;
		switch (chose)
		{
		case 'y':case'Y':
			File_Output(t);
			Clear(t);
			return;
		case 'n':case'N':
			Clear(t);
			return;
		default:
			std::cout << "Неверный ввод\n";
			break;
		}

	}
}
//Алгоритмы сортировки

void Sort_Ascending(vector<Bill*>&t, int l, int r)//Сортировка по возрастанию
{

	for (int i = r; i > l; i--)
		if (t[i]->date < t[i - 1]->date)
		{
			Bill* ptr = t[i];
			t[i] = t[i - 1];
			t[i - 1] = ptr;
		}
	for (int i = l + 2; i <= r; i++)
	{
		int j = i;
		Bill* ptr = t[j];
		while (ptr->date < t[j - 1]->date)
		{
			t[j] = t[j - 1];
			j--;
		}
		t[j] = ptr;
	}
}
void Descending_Sort(vector<Bill*>&t, int l, int r)//Сортировка по убыванию

{
	for (int i = r; i > l; i--)
		if (t[i]->date > t[i - 1]->date)
		{
			Bill* ptr = t[i];
			t[i] = t[i - 1];
			t[i - 1] = ptr;
		}
	for (int i = l + 2; i <= r; i++)
	{
		int j = i;
		Bill*ptr = t[j];
		while (ptr->date > t[j - 1]->date)
		{
			t[j] = t[j - 1];
			j--;
		}
		t[j] = ptr;
	}
}
//Быстрая сортировка по возрастанию
int partition(vector<Bill*>&t, int l, int r)
{
	int i = l - 1, j = r;
	Bill*ptr = t[r];
	while (true)
	{
		while (t[++i]->date < ptr->date);
		while (t[--j]->date > ptr->date)
		{
			if (j == 1)
				break;
		}
		if (i >= j) break;
		Bill* swap_ptr = t[i];
		t[i] = t[j];
		t[j] = swap_ptr;
	}
	Bill* swap_ptr = t[i];
	t[i] = t[r];
	t[r] = swap_ptr;
	return i;
}
int rand_chose(vector<Bill*>&t, int l, int r)
{
	int ra = rand() % (r - l + 1) + l;
	Bill* swap_ptr = t[ra];
	t[ra] = t[r];
	t[r] = swap_ptr;
	return partition(t, l, r);
}
void Quick_Sort_Ascending(vector<Bill*>&t, int l, int r)
{
	if (r - l <= 10) {
		Sort_Ascending(t, l, r);
		return;
	}
	int i = rand_chose(t, l, r);
	Quick_Sort_Ascending(t, l, i - 1);
	Quick_Sort_Ascending(t, i + 1, r);
}
//Сортировка слиянием по убыванию
void merge(vector<Bill*>&t, int l, int m, int r)
{
	static Bill* aux[1000];
	int i, j;
	for (i = m + 1; i > l; i--) aux[i - 1] = t[i - 1];
	for (j = m; j < r; j++)aux[r + m - j] = t[j + 1];
	for (int k = l; k <= r; k++)
		if (aux[i] < aux[j])
			t[k] = aux[j--];
		else
			t[k] = aux[i++];
}
void Merge_Sort_Descending(vector<Bill*>&t, int l, int r)
{
	if (r - l <= 10)
	{
		Descending_Sort(t, l, r);
		return;
	}
	int m = (r + l) / 2;
	Merge_Sort_Descending(t, l, m);
	Merge_Sort_Descending(t, m + 1, r);
	merge(t, l, m, r);
}
void Sort(vector<Bill*>&t, int l, int r)
{
	if (t.size() < 1)
	{
		cout << "Нечего сортировать.\n";
		return;
	}
	cout << "Как отсортировать файл?\n"
		<< "1.Сортировка по убыванию.\n"
		<< "2.Сортировка по возрастанию.\n"
		<< ": ";
	int chose;
	cin >> chose;
	switch (chose)
	{
	case 1:
		Merge_Sort_Descending(t, l, r);
		cout << "Отсортировано по убыванию\n";
		break;
	case 2:
		Quick_Sort_Ascending(t, l, r);
		cout << "Отсортировано по возрастанию\n";
		break;
	default:
		cout << "Выбран неверный номер.\n";
		break;
	}

}