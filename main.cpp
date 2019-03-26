#include "Bill.h"
#include<vector>
#include <fstream>
#include <string>
using std::cout;
using std::cin;
using std::vector;


void Console_Input(vector<Bill*>&t); //Консольный Ввод
void Main_Console_Output(vector<Bill*>&t);//Консольный Вывод
void Type_Console_Output(vector<Bill*>&t);//Вывод на консоль по типу данных
void File_Input(vector<Bill*>&t);//Ввод из файла
void File_Output(vector<Bill*>&t);//Сохранение в файл
void Exit(vector<Bill*>&t);//Выход из приложения
bool Change_By_Date(vector<Bill*>&t);//Изминение данных по дате
void Clear(vector<Bill*>&t);// Очистка
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
			<< "4.Вывод в  файл.\n"
			<< "5.Изменение по дате\n"
			<< "100.Выход.\n"
			<< ": ";

		cin >> input;
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
		case 4://Вывод в файл
			File_Output(tax);
			break;
		case 5://Изменение по дате
			if (Change_By_Date(tax))
				std::cout << "Успешно изменено.\n";
			else
				std::cout << "Не изменено.\n";
			break;
		case 100:
			Exit(tax);
			return 0;
		default:
			std::cout << "Выбран неверный номер.\n";
			break;
		}
	}
	return 0;
}

void Console_Input(vector<Bill*>&t)
{
	char type_of_bill;
	int quantity;
	cout << "Введите тип налога e - эллектричество j - ЖКХ.\n"
		<< ": ";
	cin >> type_of_bill;
	switch (type_of_bill) //Обработка типа налогов
	{
	case 'e':case 'E':
		cout << "Введите колличество счетов, которое планируется ввести.\n"
			<< ": ";
		cin >> quantity;
		for (int i = 0; i < quantity; i++)
		{
			t.push_back(new Electricity_Bill());
			t[count++]->Create(); //Добавление файлов с консоли
		}
		break;
	case 'j':case 'J':
		cout << "Введите колличество счетов, которое планируется ввести.\n"
			<< ": ";
		cin >> quantity;
		for (int i = 0; i < quantity; i++)
		{
			t.push_back(new JKH());
			t[count++]->Create();//Добавление файлов с консоли
		}
		break;
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
	std::cout << "Введите название файла\n"
		<< ": ";
	std::getline(std::cin, file_name);
	fin.open(file_name);
	if (!fin.is_open())
	{
		std::cout << "Невозможно открыть файл\n";
		exit(EXIT_FAILURE);
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
	std::cout << "Введите название файла\n"
		<< ": ";
	std::getline(std::cin, file_name);
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
			case 'a':case'A':
				for (int i = 0; i < count; i++)
					t[i]->Save(file_name);
				break;
			case 'r':case'R':
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
	std::cout << "Что вы хотите изменить?\n"
		<< "1.Данные счета(дата,сумма оплаты,задолженность)\n"
		<< "2.Тип счета\n"
		<< "3.Удалить счет\n"
		<< ": ";
	cin >> chose;
	std::cout << "Введите дату счета, который хотите изменить\n";
	cin >> check_date;
	cin.get();
	for (; ptr != t.end(); ptr++)
		if ((*ptr)->date == check_date)// определяем нужный нам счет
			break;
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