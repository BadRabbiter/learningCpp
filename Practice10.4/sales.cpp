#include <iostream>
#include "Sales.h"

Sales::Sales()
{
	for (int i = 0; i < QUARTERS; i++)
	{
		sales[i] = 0;
	}
	//sales[QUARTERS] = {0};
	//只有在数组初始化时允许花括号形式。
	average = 0.0;
	max = 0.0;
	min = 0.0;
}

Sales::Sales(const double ar[], int n)
{
	if (n<0 || n>QUARTERS)
	{
		std::cout << "Wrong Number!\n";
		for (int i = 0; i < QUARTERS; i++)
		{
			sales[i] = 0;
		}
		//sales[QUARTERS] = {0};
		//只有在数组初始化时允许花括号形式。
		average = 0.0;
		max = 0.0;
		min = 0.0;
	}
	else
	{
		double count;
		if (0< n)
			sales[0] = ar[0];
		else
			sales[0] = 0;
		count = max = min = sales[0];
		for (int i = 1; i < QUARTERS; i++)
		{
			if (i < n)
				sales[i] = ar[i];
			else
				sales[i] = 0;
			count += sales[i];
			max =( (max > sales[i]) ? max : sales[i]);
			min = min < sales[i] ? min : sales[i];
		}
		average = count / QUARTERS;
	}
}


void Sales::setSales() {
	using std::cout;
	using std::cin;
	cout << "Please Enter 4 sales!\n#1:";
	cin >> sales[0];
	double count;
	count = max = min = sales[0];
	for (int i = 1; i < QUARTERS; i++)
	{
		cout << "#" << i + 1 << ":";
		cin >> sales[i];
		count += sales[i];
		max = max > sales[i] ? max : sales[i];
		min = min < sales[i] ? min : sales[i];
	}
	average = count / QUARTERS;
}

void Sales::showSales() const {
	using std::cout;
	for (int i = 0; i < QUARTERS; i++)
	{
		cout << "Sale #" << i + 1 << ':'
			<< sales[i] << '\n';
	}
	cout << "Average: " << average;
	cout << " Max: " << max;
	cout << " Min: " << min << '\n';
}