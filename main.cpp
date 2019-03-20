#include "Bill.h"
#include<vector>
#include <fstream>
#include<sstream>

using std::cout;
using std::cin;
using std::vector;

int main()
{
	vector<Bill*>tax;
	unsigned int input, count = 0;
	char type_of_bill;
	std::string file_name,read_line, additional;
	std::ifstream fin;
	while (true)
	{
		setlocale(LC_ALL, "Rus");
		std::cout  << "Выберети пункт.\n";
		std::cout  << "1.Ввод с консоли.\n"
			<< "2.Вывод на  консоль.\n"
			<< "3.Ввод из  файла.\n"
			<< "4.Вывод в  файл.\n"
			<< "100.Выход.\n"
			<< ": ";

		cin >> input;
		switch (input) //Начало отработки меню
		{
		case 1://Ввод с консоли
			cout << "Введите тип налога e - эллектричество j - ЖКХ.\n"
				<< ": ";
			cin >> type_of_bill;
			switch (type_of_bill) //Обработка типа налогов
			{
			case 'e':case 'E':
				cout << "Введите колличество счетов, которое планируется ввести.\n"
					<< ": ";
				cin >> input;
				for (int i = 0; i < input; i++)
				{
					tax.push_back(new Electricity_Bill());
					tax[count++]->Create();
				}
				break;
			case 'j':case 'J':
				cout << "Введите колличество счетов, которое планируется ввести.\n"
					<< ": ";
				cin >> input;
				for (int i = 0; i < input; i++)
				{
					tax.push_back(new JKH());
					tax[count++]->Create();
				}
				break;
			}
			break;
		case 2://Ввод на консоль
			for (int i = 0; i < count; i++)
				tax[i]->Output();
			break;
		case 3://Ввод из файла
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
					tax.push_back(new Electricity_Bill());
					tax[count++]->Read_File(read_line);
				}
				else if (read_line[0] == 'Ж')
				{
					tax.push_back(new JKH());
					tax[count++]->Read_File(read_line);
				}
			}
			cout << "Считано\n";
			break;
		case 4://Вывод в файл
			cin.get();
			std::cout << "Введите название файла\n"
				<< ": ";
			std::getline(std::cin, file_name);
			for (int i = 0; i < count; i++)	
				tax[i]->Save(file_name);
			break;
		case 100: return 0;
		default:return 0;
			break;
		}

	}
}