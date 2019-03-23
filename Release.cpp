#include "Bill.h"

#include<fstream>
#include<sstream>
////////////////////////////////////////////Bill
void Bill::Save(std::string&cname)//����\������� ������ � ����
{
	setlocale(LC_ALL, "Rus");
	std::ofstream fout(cname, std::ofstream::app);
	if (!fout.is_open())
	{
		std::cout << "���������� ������� ����\n";
		exit(EXIT_FAILURE);
	}
	fout << *this;
	fout.close();
	std::ofstream fout_val("Val" + cname, std::ofstream::app); //�������� ����� �� �������� � ���������� ����� ��������� ����������
	if (!fout_val.is_open())
	{
		std::cout << "���������� ������� ����\n";
		exit(EXIT_FAILURE);
	}
	fout_val << name << " " << paid << " " << debt << " " << date.day << " " << date.month << " " << date.year << std::endl;

}
void Bill::Read_File(std::string& �name)//������ ������ �� �����
{
	std::istringstream read(�name);
	read >> name;
	read >> paid;
	read >> debt;
	read >> date.day;
	read >> date.month;
	read >> date.year;

}

void Bill::Create() //���������� ������ � �������
{
	setlocale(LC_ALL, "Rus");
	std::cout << "������� ����.\n";
	std::cin >> date;
	std::cout << "������� ����� ������: ";
	std::cin >> paid;
	std::cout << "������� ������� �����: ";
	std::cin >> debt;
	std::cin.get();
}
void Bill::Output() //����� �� �������
{
	std::cout << *this;
}
std::ostream& operator<<(std::ostream& out, const Bill & obj)
{
	setlocale(LC_ALL, "Rus");
	out << "���� �� " << obj.date << ". �� " << obj.name << std::endl
		<< "������ " << obj.paid << std::endl
		<< "���� " << obj.debt << std::endl
		<< "/////////////////////////////////////////////////\n";
	return out;
}

////////////////////////////////////////////Electricity_Bill
void Electricity_Bill::Save(std::string&cname)
{
	Bill::Save(cname);
}
void Electricity_Bill::Read_File(std::string& �name)
{
	Bill::Read_File(�name);
}
void Electricity_Bill::Create()
{
	Bill::Create();
}
void Electricity_Bill::Output()
{
	Bill::Output();
}
std::ostream& operator<<(std::ostream& out, const Electricity_Bill & obj)
{
	setlocale(LC_ALL, "Rus");
	out << (const Bill&)obj;
	return out;
}

////////////////////////////////////////////JKH
void JKH::Save(std::string&cname)
{
	Bill::Save(cname);
}
void JKH::Read_File(std::string& �name)
{
	Bill::Read_File(�name);
}
void JKH::Create()
{
	Bill::Create();
}
void JKH::Output()
{
	Bill::Output();
}
std::ostream& operator<<(std::ostream& out, const JKH & obj)
{
	setlocale(LC_ALL, "Rus");
	out << (const Bill&)obj;
	return out;
}

