#include<iostream>
#include <cstring>
#include"person.h"

Person::Person(const std::string & ln, const char * fn)
{
	lname = ln;
	strncpy_s(fname, fn, LIMIT);
	//fname=fn;
	//�Ͼ䱨��expression must be a modifiable lvalue;
	//char���鲻��ͨ����ָ�븳ֵ���������޸ģ�
}

void Person::show() const {
	std::cout << "Name: " << fname << " " << lname << '\n';
}

void Person::formalShow() const {
	std::cout << "Name: " << lname << " " << fname << '\n';
}