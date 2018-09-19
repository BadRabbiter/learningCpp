#include <iostream>
#include "Sales.h"

int main() {
	double ar[4] = { 23,-5.4,44.75,33 };
	Sales s1 = Sales(ar, 5);
	Sales s2 = Sales();
	s1.showSales();
	s2.showSales();
	s2.setSales();
	s2.showSales();
	std::cin.get();
	std::cin.get();
	return 0;
}