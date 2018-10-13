#include "Time.h"
#include <iostream>

Time::Time()
{
	hours = minutes = 0;
}

Time::Time(int h, int m)
{
	hours = h;
	minutes = m;
}

void Time::AddHr(int h)
{
	hours += h;
}

void Time::AddMin(int m)
{
	minutes += m;
}

void Time::Reset(int h, int m)
{
	hours = h;
	minutes = m;
}

Time Time::operator+(const Time & t) const
{
	Time sum;
	sum.minutes = minutes + t.minutes;
	sum.hours = hours + t.hours + sum.minutes / 60;
	sum.minutes %= 60;
	return sum;
}

Time Time::operator - (const Time & t) const
{
	Time diff;
	int tot1, tot2;
	tot1 = t.minutes + 60 * t.hours;
	tot2 = minutes + 60 * hours;
	diff.hours = (tot2 - tot1) / 60;
	diff.minutes = (tot2 - tot1) % 60;
	return diff;
}

Time Time::operator *(double n) const
{
	Time result;
	long tot;
	tot = n*minutes + n*60 * hours;
	result.minutes = tot % 60;
	result.hours = tot / 60;
	return result;
}

void Time::Show() const
{
	std::cout << hours << " hours, " << minutes << "minutes";
}
