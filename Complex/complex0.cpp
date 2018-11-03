#include "pch.h"
#include "complex0.h"

complex::complex()
{
	real = imaginary = 0.0;
}
complex::complex(double r, double i)
{
	real = r;
	imaginary = i;
}
complex complex::operator+(complex & c) const
{
	complex sum;
	sum.real = real + c.real;
	sum.imaginary = imaginary + c.imaginary;
	return sum;
}
complex complex::operator-(complex & c) const
{
	complex diff;
	diff.real = real - c.real;
	diff.imaginary = imaginary - c.imaginary;
	return diff;
}
complex complex::operator*(complex & c) const
{
	complex product;
	product.real = real * c.real - imaginary * c.imaginary;
	product.imaginary = real * c.imaginary + imaginary * c.real;
	return product;
}
complex complex::operator*(double n) const
{
	complex multi;
	multi.real = n * real;
	multi.imaginary = n * imaginary;
	return multi;
}
complex operator*(double n, const complex & c)
{
	return c * n;
}
complex complex::operator~() const
{
	complex conjugate;
	conjugate.real = real;
	conjugate.imaginary = -imaginary;
	return conjugate;
}
std::ostream & operator<<(std::ostream & os, const complex & c)
{
	std::cout << "(" << c.real << ", " << c.imaginary << "i)";
	return os;
}
std::istream & operator>>(std::istream & is, complex & c)
{
	std::cout << "real:";
	if (std::cin >> c.real)
		std::cout << "imaginary:";
	else
		return is;
	std::cin >> c.imaginary;
	return is;
}