#pragma once
#include <iostream>

class complex
{
private:
	double real;
	double imaginary;
public:
	complex();
	complex(double r, double i);
	complex operator+(complex & c) const;
	complex operator-(complex & c) const;
	complex operator*(complex & c) const;
	complex operator*(double n) const;
	complex operator~() const;
	friend complex operator*(double n, const complex & c);
	friend std::ostream & operator<<(std::ostream & os, const complex & c);
	friend std::istream & operator>>(std::istream & is, complex & c);
};