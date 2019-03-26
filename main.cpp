#include "Bill.h"
#include<vector>
#include <fstream>
#include <string>
using std::cout;
using std::cin;
using std::vector;


void Console_Input(vector<Bill*>&t); //���������� ����
void Main_Console_Output(vector<Bill*>&t);//���������� �����
void Type_Console_Output(vector<Bill*>&t);//����� �� ������� �� ���� ������
void File_Input(vector<Bill*>&t);//���� �� �����
void File_Output(vector<Bill*>&t);//���������� � ����
void Exit(vector<Bill*>&t);//����� �� ����������
bool Change_By_Date(vector<Bill*>&t);//��������� ������ �� ����
void Clear(vector<Bill*>&t);// �������
int count = 0;

int main()
{
	vector<Bill*>tax;
	int input;
	while (true)
	{
		setlocale(LC_ALL, "Rus");
		std::cout << "�������� �����.\n";
		std::cout << "1.���� � �������.\n"
			<< "2.����� ��  �������.\n"
			<< "3.���� ��  �����.\n"
			<< "4.����� �  ����.\n"
			<< "5.��������� �� ����\n"
			<< "100.�����.\n"
			<< ": ";

		cin >> input;
		switch (input) //������ ��������� ����
		{
		case 1://���� � �������
			Console_Input(tax);
			break;
		case 2://���� �� �������
			Main_Console_Output(tax);
			break;
		case 3://���� �� �����
			File_Input(tax);
			break;
		case 4://����� � ����
			File_Output(tax);
			break;
		case 5://��������� �� ����
			if (Change_By_Date(tax))
				std::cout << "������� ��������.\n";
			else
				std::cout << "�� ��������.\n";
			break;
		case 100:
			Exit(tax);
			return 0;
		default:
			std::cout << "������ �������� �����.\n";
			break;
		}
	}
	return 0;
}

void Console_Input(vector<Bill*>&t)
{
	char type_of_bill;
	int quantity;
	cout << "������� ��� ������ e - �������������� j - ���.\n"
		<< ": ";
	cin >> type_of_bill;
	switch (type_of_bill) //��������� ���� �������
	{
	case 'e':case 'E':
		cout << "������� ����������� ������, ������� ����������� ������.\n"
			<< ": ";
		cin >> quantity;
		for (int i = 0; i < quantity; i++)
		{
			t.push_back(new Electricity_Bill());
			t[count++]->Create(); //���������� ������ � �������
		}
		break;
	case 'j':case 'J':
		cout << "������� ����������� ������, ������� ����������� ������.\n"
			<< ": ";
		cin >> quantity;
		for (int i = 0; i < quantity; i++)
		{
			t.push_back(new JKH());
			t[count++]->Create();//���������� ������ � �������
		}
		break;
	}
}
void Main_Console_Output(vector<Bill*>&t)
{
	std::cout << " ����� ���������.\n"
		<< "1.������� ���.\n"
		<< "2.����� �� ���� �����.\n"
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
void Type_Console_Output(vector<Bill*>&t) //����� �� ���� �����
{
	std::cout << "����� ������ ���� �������.\n"
		<< "1.�������������.\n"
		<< "2.���.\n"
		<< ": ";
	unsigned int chose;
	cin >> chose;
	cin.get();
	switch (chose)
	{
	case 1:
		for (int i = 0; i < count; i++)
			if (t[i]->name_of_bill() == "�������������")
				t[i]->Output();
		break;
	case 2:
		for (int i = 0; i < count; i++)
			if (t[i]->name_of_bill() == "���")
				t[i]->Output();
		break;
	default:
		break;
	}
}
void File_Input(vector<Bill*>&t)
{
	std::string file_name, read_line; //���������� ��� ����� ����� � ������
	std::ifstream fin;
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
			t.push_back(new Electricity_Bill());
			t[count++]->Read_File(read_line);
		}
		else if (read_line[0] == '�')
		{
			t.push_back(new JKH());
			t[count++]->Read_File(read_line);
		}
	}
	cout << "�������\n";
}
void File_Output(vector<Bill*>&t)
{
	std::string file_name;
	char check_ch, chose;
	cin.get();
	std::cout << "������� �������� �����\n"
		<< ": ";
	std::getline(std::cin, file_name);
	std::ifstream f_check(file_name); //������������ ��� �������� �� ������������� �����
	std::ofstream clear; //������������ ��� ������� ������
	if (f_check.is_open()) //�������� �� ������������� 
	{
		f_check >> check_ch;
		if (!f_check.eof()) //�������� �� ����� �����, ����� ��� ����������� ���� �� ���� ��� ��� 
		{

			f_check.close();
			std::cout << "� ����� ���� ���������� ������� �� ��� �������� � ��� �����?(r/a): ";
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
				std::cout << "�������� ����\n ������ ����������.";
				return;
			}
		}
		else //���� ����
		{
			for (int i = 0; i < count; i++)
				t[i]->Save(file_name);
		}
	}
	else //���� �� ����������
	{
		for (int i = 0; i < count; i++)
			t[i]->Save(file_name);
	}
	std::cout << "���������\n";
}
bool Change_By_Date(vector<Bill*>&t)
{

	Bill::Date check_date;
	int chose;
	char type_of_bill;
	auto ptr = t.begin(); // ��������� �� ����� ������� �������
	std::cout << "��� �� ������ ��������?\n"
		<< "1.������ �����(����,����� ������,�������������)\n"
		<< "2.��� �����\n"
		<< "3.������� ����\n"
		<< ": ";
	cin >> chose;
	std::cout << "������� ���� �����, ������� ������ ��������\n";
	cin >> check_date;
	cin.get();
	for (; ptr != t.end(); ptr++)
		if ((*ptr)->date == check_date)// ���������� ������ ��� ����
			break;
	if (ptr == t.end())
		return false;

	switch (chose)
	{
	case 1:
		(*ptr)->Change();
		return true;
	case 2:
		cout << "������� ��� ������ e - �������������� j - ���.\n"
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
				std::cout << "�������� ����\n";
				break;
			}
		}
	case 3:
		delete (*ptr);
		t.erase(ptr);
		count--;
		return true;
	default:
		std::cout << "�������� ����, ������� � ����.\n";
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
	std::cout << "��������� ��������� ���������� � ����?\n";
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
			std::cout << "�������� ����\n";
			break;
		}

	}
}