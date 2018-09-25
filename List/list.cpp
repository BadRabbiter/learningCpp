#include <iostream>
#include "list.h"

List::List()
{
	//first = 0;
	last = 0;
}

void List::clearList()
{
	last = 0;
}

bool List::listEmpty()
{
	return last == 0;
}

bool List::listFull()
{
	return last == Size;
}

int List::listLength()
{
	return last;
}

bool List::getElem(int position, Item &elem)
{
	//if (position <= last&&position >= first&&last>0)
	if (position <= last && position > 0 && last>0)
	{
		elem = arr[position-1];
		return true;
	}
	else
		return false;
}

bool List::locateElem(const Item &elem, int &pos)
{
	for (int i = 0; i < last; i++)
	{
		if (arr[i] == elem)
		{
			pos = i + 1;
			return true;
		}
	//	else
	//		pos = pos;
	}
	pos = 0;
	return false;
}

bool List::priorElem(const Item & curElem, Item & preElem)
{
	int curPos=0;
	this->locateElem(curElem, curPos);
	if (curPos > 1)
	{
		preElem = arr[curPos - 2];
		return true;
	}
	else
		return false;
}

bool List::nextElem(const Item &curElem, Item & nextElem)
{
	int curPos=0;
	if (this->locateElem(curElem, curPos))
	{
		if (curPos < last)
		{
			nextElem = arr[curPos];
			return true;
		}
		else
			return false;
	}
	else
		return false;
}

bool List::listInsert(int position, Item & elem)
{
	if (position > 0 && position <= last + 1 && last < Size)
	{
		for (int i = last; i >= position; i--)
		{
			arr[i] = arr[i - 1];
		}
		arr[position - 1] = elem;
		last += 1;
		return true;
	}
	else
		return false;
}

bool List::listDelete(int position, Item & e)
{
	if (position > 0 && position <= last)
	{
		e = arr[position - 1];
		last -= 1;
		for (int i = position-1; i < last; i++)
		{
			arr[i] = arr[i + 1];
		}
		return true;
	}
	else
		return false;
}

bool List::listTraverse()
{
	if (this->listEmpty())
		return false;
	else
	{
		for (int i = 0; i < last; i++)
		{
			std::cout << "#" << i + 1 << ": " << arr[i]<<'\n';
		}
	}
}