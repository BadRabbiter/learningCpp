#include "time_friend.h"

Time::Time()
{
	hours = minutes = 0;
}
Time::Time(int h, int m)
{
	hours = h;
	minutes = m;
}
void Time::AddMin(int m)
{
	minutes += m;
	hours += minutes / 60;
	minutes %= 60;
}
void Time::AddHr(int h)
{
	hours += h;
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
Time Time::operator-(const Time & t) const
{
	Time diff;
	int tot1, tot2;
	tot1 = t.minutes + 60 * t.hours;
	tot2 = minutes + 60 * hours;
	diff.hours = (tot1 - tot2) / 60;
	diff.minutes = (tot1 - tot2) % 60;
	return diff;
}
Time Time::operator*(double m) const
{
	Time result;
	long tot = hours * m * 60 + minutes * m;
	result.hours = tot / 60;
	result.minutes = tot % 60;
	return result;
}
std::ostream & operator<<(std::ostream & os, const Time & t)
{
	os << t.hours << " hours, " << t.minutes << " minutes";
	return os;
}