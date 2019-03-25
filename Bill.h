#ifndef TAXBILL_H_
#define TAXBILL_H_

#include<string>
#include<iostream>

using std::string;

class Bill
{
private:
	string name;
	double paid;
	double debt;

public:
	struct Date {
		int day;
		int month;
		int year;
		Date(const string &cr_date = "0.0.0", int cday = 0, int cmonth = 0, int cyear = 0) :day(cday), month(cmonth), year(cyear) {}
		friend std::istream& operator>>(std::istream& in, Date& obj) {
			while (true)
			{
				std::cout << "����: ";
				in >> obj.day;
				if (obj.day < 0 || obj.day>31)
				{
					std::cout << "�������� ����\n";
					continue;
				}
				std::cout << "�����: ";
				in >> obj.month;
				if (obj.month < 0 || obj.month>12)
				{
					std::cout << "�������� ����\n";
					continue;
				}
				std::cout << "���: ";
				in >> obj.year;
				if (obj.year < 1900 || obj.year>3000)
				{
					std::cout << "�������� ����\n";
					continue;
				}
				break;
			}
			return in;
		}
		friend std::ostream& operator<<(std::ostream& out, const Date & obj) { out << ((obj.day < 10) ? "0" : "") << obj.day << ":" << ((obj.month < 10) ? "0" : "") << obj.month << ":" << obj.year; return out; }
		friend  bool operator==(const Date & obj_one, const Date & obj_two) { return (obj_one.day == obj_two.day && obj_one.month == obj_two.month && obj_one.year == obj_two.year); }
	} date;
	Bill(double cpaid = 0.0, double cdebt = 0.0, const Date& cdate = Date(), const string& cname = "No name") :name(cname), paid(cpaid), debt(cdebt), date(cdate) {}
	friend std::ostream& operator<<(std::ostream& out, const Bill &);
	string  name_of_bill() { return name; }
	virtual void Save(std::string&) = 0; //���������� � ����
	virtual void Read_File(std::string&) = 0;//������ �� �����
	virtual void Create() = 0; //�������� ������ � �������
	virtual void Output() = 0; //����� �� �������
	virtual void Change() = 0; //��������� � �������
	virtual ~Bill() {}
};

class Electricity_Bill :public Bill
{
public:
	Electricity_Bill(double epaid = 0.0, double edebt = 0.0, const Date& edate = Date()) :Bill(epaid, edebt, edate, "�������������") {}
	friend std::ostream& operator<<(std::ostream& out, const Electricity_Bill & obj);
	void Save(std::string&);
	void Read_File(std::string&);
	void Create();
	void Output();
	void Change();
	~Electricity_Bill() {}
};

class JKH :public Bill
{
public:
	JKH(double jpaid = 0.0, double jdebt = 0.0, const Date& jdate = Date()) :Bill(jpaid, jdebt, jdate, "���") {}
	friend std::ostream& operator<<(std::ostream& out, const JKH & obj);
	void Save(std::string&);
	void Read_File(std::string&);
	void Create();
	void Output();
	void Change();
	~JKH() {}
};
#endif //TAXBILL_H_
