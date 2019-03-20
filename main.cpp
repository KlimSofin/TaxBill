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
		std::cout  << "�������� �����.\n";
		std::cout  << "1.���� � �������.\n"
			<< "2.����� ��  �������.\n"
			<< "3.���� ��  �����.\n"
			<< "4.����� �  ����.\n"
			<< "100.�����.\n"
			<< ": ";

		cin >> input;
		switch (input) //������ ��������� ����
		{
		case 1://���� � �������
			cout << "������� ��� ������ e - �������������� j - ���.\n"
				<< ": ";
			cin >> type_of_bill;
			switch (type_of_bill) //��������� ���� �������
			{
			case 'e':case 'E':
				cout << "������� ����������� ������, ������� ����������� ������.\n"
					<< ": ";
				cin >> input;
				for (int i = 0; i < input; i++)
				{
					tax.push_back(new Electricity_Bill());
					tax[count++]->Create();
				}
				break;
			case 'j':case 'J':
				cout << "������� ����������� ������, ������� ����������� ������.\n"
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
		case 2://���� �� �������
			for (int i = 0; i < count; i++)
				tax[i]->Output();
			break;
		case 3://���� �� �����
			cin.get();
			std::cout << "������� �������� �����\n"
				<< ": ";
			std::getline(std::cin, file_name);
			fin.open(file_name);
			if (!fin.is_open())
			{
				std::cout << "���������� ������� ����\n";
				exit(EXIT_FAILURE);
			}
			while (getline(fin, read_line))
			{
				
				if (read_line[0] == '�')
				{
					tax.push_back(new Electricity_Bill());
					tax[count++]->Read_File(read_line);
				}
				else if (read_line[0] == '�')
				{
					tax.push_back(new JKH());
					tax[count++]->Read_File(read_line);
				}
			}
			cout << "�������\n";
			break;
		case 4://����� � ����
			cin.get();
			std::cout << "������� �������� �����\n"
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