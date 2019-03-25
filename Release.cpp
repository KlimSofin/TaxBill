#include "Bill.h"
#include<iostream>
#include<fstream>
#include<sstream>
////////////////////////////////////////////Bill
void Bill::Save(std::string&cname) //Сохо\ранение данных в файл
{
	setlocale(LC_ALL, "Rus");
	std::ofstream fout(cname, std::ofstream::app);
	if (!fout.is_open())
	{
		std::cout << "Невозможно открыть файл\n";
		exit(EXIT_FAILURE);
	}
	fout << *this;
	fout.close();
	std::ofstream fout_val("Val" + cname, std::ofstream::app); //Создание файла из которого в дальнейшим можно считывать информацию
	if (!fout_val.is_open())
	{
		std::cout << "Невозможно открыть файл\n";
		exit(EXIT_FAILURE);
	}
	fout_val << name << " " << paid << " " << debt << " " << date.day << " " << date.month << " " << date.year << std::endl;

}
void Bill::Read_File(std::string& сname)//Чтение данных из файла
{
	std::istringstream read(сname);
	read >> name;
	read >> paid;
	read >> debt;
	read >> date.day;
	read >> date.month;
	read >> date.year;
}
void Bill::Create() //Добавление файлов с консоли
{
	setlocale(LC_ALL, "Rus");
	std::cout << "Введите дату.\n";
	std::cin >> date;
	std::cout << "Введите сумму оплаты: ";
	std::cin >> paid;
	std::cout << "Введите остаток долга: ";
	std::cin >> debt;
	std::cin.get();
}
void Bill::Output()  //Вывод на консоль
{
	std::cout << *this;
}
void Bill::Change()
{
	std::cout << "Какой параметр желаете изменить?\n"
		<< "1.Дата.\n"
		<< "2.Сумма оплаты\n"
		<< "3.Долг\n";
	int chose;
	std::cin >> chose;
	switch (chose)
	{
	case 1:
		std::cin >> this->date; break;
	case 2:
		std::cout << ": ";
		std::cin >> this->paid; break;
	case 3:
		std::cout << ": ";
		std::cin >> this->debt; break;
	default:
		std::cout << "Неверный ввод!\n";
		break;
	}


}
std::ostream& operator<<(std::ostream& out, const Bill & obj)
{
	setlocale(LC_ALL, "Rus");
	out << "Счет от " << obj.date << ". За " << obj.name << std::endl
		<< "Пришло " << obj.paid << std::endl
		<< "Долг " << obj.debt << std::endl
		<< "/////////////////////////////////////////////////\n";
	return out;
}


////////////////////////////////////////////Electricity_Bill
void Electricity_Bill::Save(std::string&cname)
{
	Bill::Save(cname);
}
void Electricity_Bill::Read_File(std::string& сname)
{
	Bill::Read_File(сname);
}
void Electricity_Bill::Create()
{
	Bill::Create();
}
void Electricity_Bill::Output()
{
	Bill::Output();
}
void Electricity_Bill::Change()
{
	Bill::Change();
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
void JKH::Read_File(std::string& сname)
{
	Bill::Read_File(сname);
}
void JKH::Create()
{
	Bill::Create();
}
void JKH::Output()
{
	Bill::Output();
}
void JKH::Change()
{
	Bill::Change();
}
std::ostream& operator<<(std::ostream& out, const JKH & obj)
{
	setlocale(LC_ALL, "Rus");
	out << (const Bill&)obj;
	return out;
}

