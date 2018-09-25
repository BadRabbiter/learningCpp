#pragma once
typedef int Item;
class List {
private:
	static const int Size = 10;
	Item arr[Size];
	//int first;
	int last;
public:
	List();
	void clearList();
	bool listEmpty();
	bool listFull();
	int listLength();
	bool getElem(int position, Item &elem);
	bool locateElem(const Item &elem, int &Pos);
	bool priorElem(const Item & curElem, Item & preElem);
	bool nextElem(const Item &curElem, Item & nextElem);
	bool listInsert(int position, Item & elem);
	bool listDelete(int position, Item & e);
	bool listTraverse();
};