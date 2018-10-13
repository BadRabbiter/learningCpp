#include "Time.h"
#include <iostream>

int main()
{
	using std::cout;
	using std::endl;
	Time weeding{ 4,35 };
	Time waxing{ 2,47 };
	Time total;
	Time diff;
	Time adjusted;

	cout << "weeding Time =";
	weeding.Show();
	cout << endl;

	cout << "waxing time =";
	waxing.Show();
	cout << endl;

	cout << "total work time =";
	total = weeding + waxing;
	total.Show();
	cout << endl;

	cout << "weeding time - waxing time =";
	diff = weeding - waxing;
	diff.Show();
	cout << endl;

	cout << "waxing time - weeding tiem =";
	diff = waxing - weeding;
	diff.Show();
	cout << endl;

	adjusted = total * 1.5;
	//adjusted = 1.5*total;
	//通过Time类成员函数重载二元运算符，运算符左边须为Time类，
	//否则1.5为double类型，无法调用重载运算符*。
	//为解决此问题引入友元。
	cout << "adjusted work time =";
	adjusted.Show();
	cout << endl;
	std::cin.get();

	return 0;
}