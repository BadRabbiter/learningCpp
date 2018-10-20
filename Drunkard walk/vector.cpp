#include <cmath>
#include "vector.h"
using std::sqrt;
using std::sin;
using std::cos;
using std::atan;//float angle=atan(y/x);
using std::atan2;//flaot angle=atan2(y,x);当x=0时依然可用；
using std::cout;

namespace VECTOR
{
	//compute degree in one radian
	const double Rad_to_deg = 45.0 / atan(1.0);
	// should be about 57.2957795130823

	//private methods
	//calculates magnitude from x and y;
	void Vector::set_mag()
	{
		mag = sqrt(x*x + y * y);
	}

	void Vector::set_ang()
	{
		if (0 == x && 0 == y)
			ang = 0.0;
		else
			ang = atan2(y, x);
	}

	//set x from polar coordinate
	void Vector::set_x()
	{
		x = mag * cos(ang);
	}
	//set y from polar coordinate
	void Vector::set_y()
	{
		y = mag * sin(ang);
	}
	//public methods
	Vector::Vector()
	{
		x = y = mag = ang = 0.0;
		mode = RECT;
	}

	//construct vector form rectangular coordinates if form is 
	//r(the default) or else form polar coordinates if form os p
	Vector::Vector(double n1, double n2, Mode form)
	{
		mode = form;
		if (form == RECT)
		{
			x = n1;
			y = n2;
			set_ang();
			set_mag();
		}
		else if (form == POL)
		{
			mag = n1;
			ang = n2/Rad_to_deg;
			set_x();
			set_y();
		}
		else
		{
			cout << "incorrect 3rd argument to Vector() --";
			cout << "Vector set to 0\n";
			x = y = mag = ang = 0;
			mode = RECT;
		}
	}
	//reset vector from rectangular coordinates if form is 
	//RECT(the default) or else from polar coordinates if 
	//form is POL
	void Vector::reset(double n1, double n2, Mode form)
	{
		mode = form;
		if (form == RECT)
		{
			x = n1;
			y = n2;
			set_ang();
			set_mag();
		}
		else if (form == POL)
		{
			mag = n1;
			ang = n2 / Rad_to_deg;
			set_x();
			set_y();
		}
		else
		{
			cout << "incorrect 3rd argument to Vector() --";
			cout << "Vector set to 0\n";
			x = y = mag = ang = 0;
			mode = RECT;
		}
	}

	Vector::~Vector()
	{
	}

	void Vector::polar_mode()
	{
		mode = POL;
	}

	void Vector::rect_mode()
	{
		mode = RECT;
	}

	Vector Vector::operator+(const Vector & b) const
	{
		return Vector(x + b.x, y + b.y);
	}

	Vector Vector::operator-(const Vector & b) const
	{
		return Vector(x - b.x, y - b.y);
	}

	Vector Vector::operator-() const
	{
		return Vector(-x, -y);
	}

	Vector Vector::operator*(double n) const
	{
		return Vector(x*n, y*n);
	}

	Vector operator*(double n, const Vector & a)
	{
		return a * n;
	}

	std::ostream & operator<<(std::ostream & os, const Vector & v)
	{
		if (v.mode == Vector::RECT)
			os << "(x,y)=(" << v.x << ", " << v.y << ")";
		else if (v.mode == Vector::POL)
		{
			os << "(m,a)=(" << v.mag << ", " << v.ang*Rad_to_deg << ")";
		}
		else
			os << "Vector object mode is invalid";
		return os;
	}
}