#include "Bill.h"
#include<vector>
#include <fstream>
#include<sstream>

using std::cout;
using std::cin;
using std::vector;

void Console_Input(vector<Bill*>&t, int&);
void Console_Output(vector<Bill*>&t, int&);
void File_Input(vector<Bill*>&t, int&);
void File_Output(vector<Bill*>&t, int&);

int main()
{
	vector<Bill*>tax;
	int input, count = 0;
	while (true)
	{
		setlocale(LC_ALL, "Rus");
		std::cout << "Выберети пункт.\n";
		std::cout << "1.Ввод с консоли.\n"
			<< "2.Вывод на  консоль.\n"
			<< "3.Ввод из  файла.\n"
			<< "4.Вывод в  файл.\n"
			<< "100.Выход.\n"
			<< ": ";

		cin >> input;
		switch (input) //Начало отработки меню
		{
		case 1://Ввод с консоли
			Console_Input(tax, count);
			break;
		case 2://Ввод на консоль
			Console_Output(tax, count);
			break;
		case 3://Ввод из файла
			File_Input(tax, count);
			break;
		case 4://Вывод в файл
			File_Output(tax, count);
			break;
		case 100: return 0;
		default:return 0;
			break;
		}

	}
}

void Console_Input(vector<Bill*>&t, int& count)
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
void Console_Output(vector<Bill*>&t, int& count)
{
	for (int i = 0; i < count; i++)
		t[i]->Output();
}
void File_Input(vector<Bill*>&t, int& count)
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
void File_Output(vector<Bill*>&t, int& count)
{
	std::string file_name;
	cin.get();
	std::cout << "Введите название файла\n"
		<< ": ";
	std::getline(std::cin, file_name);
	for (int i = 0; i < count; i++)
		t[i]->Save(file_name);
}