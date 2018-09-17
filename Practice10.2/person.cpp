#include<iostream>
#include <cstring>
#include"person.h"

Person::Person(const std::string & ln, const char * fn)
{
	lname = ln;
	strncpy_s(fname, fn, LIMIT);
	//fname=fn;
	//上句报错expression must be a modifiable lvalue;
	//char数组不能通过将指针赋值给数组名修改；
}

void Person::show() const {
	std::cout << "Name: " << fname << " " << lname << '\n';
}

void Person::formalShow() const {
	std::cout << "Name: " << lname << " " << fname << '\n';
}