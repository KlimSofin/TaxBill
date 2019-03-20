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
		std::cout << "�������� �����.\n";
		std::cout << "1.���� � �������.\n"
			<< "2.����� ��  �������.\n"
			<< "3.���� ��  �����.\n"
			<< "4.����� �  ����.\n"
			<< "100.�����.\n"
			<< ": ";

		cin >> input;
		switch (input) //������ ��������� ����
		{
		case 1://���� � �������
			Console_Input(tax, count);
			break;
		case 2://���� �� �������
			Console_Output(tax, count);
			break;
		case 3://���� �� �����
			File_Input(tax, count);
			break;
		case 4://����� � ����
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
void Console_Output(vector<Bill*>&t, int& count)
{
	for (int i = 0; i < count; i++)
		t[i]->Output();
}
void File_Input(vector<Bill*>&t, int& count)
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
void File_Output(vector<Bill*>&t, int& count)
{
	std::string file_name;
	cin.get();
	std::cout << "������� �������� �����\n"
		<< ": ";
	std::getline(std::cin, file_name);
	for (int i = 0; i < count; i++)
		t[i]->Save(file_name);
}