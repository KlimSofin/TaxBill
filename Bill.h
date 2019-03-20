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
	string date;
public:
	Bill(double cpaid = 0.0, double cdebt = 0.0, const string& cdate = "0:0:0", const string& cname = "No name") :name(cname), paid(cpaid), debt(cdebt), date(cdate) {}
	friend std::ostream& operator<<(std::ostream& out, const Bill &);
	virtual void Save(std::string&) = 0; //Сохранение в файл
	virtual void Read_File(std::string&) = 0;//Чтение из файла
	virtual void Create() = 0; //Создание налога с консоли
	virtual void Output() = 0; //Вывод на консоль
	
	virtual ~Bill() {}
};

class Electricity_Bill:public Bill
{
public:
	Electricity_Bill(double epaid = 0.0, double edebt = 0.0, const string& edate = "0:0:0") :Bill(epaid, edebt, edate, "Электричество") {}
	friend std::ostream& operator<<(std::ostream& out, const Electricity_Bill & obj);
	void Save(std::string&);
	void Read_File(std::string&);
	void Create();
	void Output();
	~Electricity_Bill() {}
};

class JKH :public Bill
{
public:
	JKH(double epaid = 0.0, double edebt = 0.0, const string& edate = "0:0:0") :Bill(epaid, edebt, edate, "ЖКХ") {}
	friend std::ostream& operator<<(std::ostream& out, const JKH & obj);
	void Save(std::string&);
	void Read_File(std::string&);
	void Create();
	void Output();
	~JKH() {}
};

#endif // !TAXBILL_H_


