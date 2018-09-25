#include <iostream>
#include "list.h"

int main()
{
	using namespace std;
	List list1;
	char ch;
	int elem,reElem;
	int pos;
	cout << "Please enter C to clear the List.\n"
		<< "D to delete an element.\n"
		<< "F to check whether the list is full or not.\n"
		<< "G to get an element.\n"
		<< "I to insert an element.\n"
		<< "L to locate the element.\n"		
		<<"N to get the next element.\n"
		<< "P to get the prior element.\n"
		<<"T to traverse the element.\n"	
		<<"or Q to quit.\n";
	while (cin >> ch && toupper(ch) != 'Q')
	{
		while (cin.get() != '\n')
			continue;
		if (!isalpha(ch))
		{
			cout << '\a';
			continue;
		}
		switch (ch)
		{
		case 'c':
		case 'C':list1.clearList();
			break;
		case 'd':
		case 'D': if (list1.listEmpty())
			cout << "No element! The list is empty!\n";
				  else
				  {
					  cout << "Please enter the Position of the element to process:";
					  cin >> pos;
					  while (cin.get() != '\n')
						  continue;
					  if (list1.listDelete(pos, elem))
						  cout << "Element " << elem << "(at " << pos
						  << " Position) has been deleted.\n";
					  else
						  cout << "Delete falied!\n";
				  }
				  break;
		case 'f':
		case 'F':if (list1.listFull())
			cout << "List is full;\n";
				 else
					 cout << "List not full. Length: " << list1.listLength() << '\n';
			break;
		case 'g':
		case 'G': if (list1.listEmpty())
			cout << "No element! The list is empty!\n";
				  else
				  {
					  cout << "Please enter the Position of the element to process:";
					  cin >> pos;
					  while (cin.get() != '\n')
						  continue;
					  if (list1.getElem(pos, elem))
						  cout << "Got element " << elem << "(at " << pos
						  << " Position).\n";
					  else
						  cout << "Get element falied!\n";
				  }
				  break;
		case 'i':
		case 'I':if (list1.listFull())
			cout << "No space! The list is full!\n";
				 else
				 {
					 cout << "Please enter the Position of the element to process:";
					 cin >> pos;
					 while (cin.get() != '\n')
						 continue;
					 cout << "Please enter the value of the element to process:";
					 cin >> elem;
					 while (cin.get() != '\n')
						 continue;
					 if (list1.listInsert(pos, elem))
						 cout << " Element " << elem << "(at " << pos
						 << " Position). has been inserted.\n";
					 else
						 cout << "Insert element falied!\n";
				 }
				 break;
		case 'l':
		case 'L': if (list1.listEmpty())
			cout << "No element! The list is empty!\n";
				  else
				  {
					  cout << "Please enter the value of the element to process:";
					  cin >> elem;
					  while (cin.get() != '\n')
						  continue;
					  if (list1.locateElem(elem,pos))
						  cout << "Element " << elem << " at " << pos
						  << " Position.\n";
					  else
						  cout << "Locate element falied!\n";
				  }
				  break;
		case 'n':
		case 'N': if (list1.listEmpty())
			cout << "No element! The list is empty!\n";
				  else
				  {
					  cout << "Please enter the value of the element to process:";
					  cin >> elem;
					  while (cin.get() != '\n')
						  continue;
					  if (list1.nextElem(elem, reElem))
						  cout << "The next element of " << elem << " is " << reElem
						  << ".\n";
					  else
						  cout << "Get next element falied!\n";
				  }
				  break;
		case 'p':
		case 'P':if (list1.listEmpty())
			cout << "No element! The list is empty!\n";
				 else
				 {
					 cout << "Please enter the value of the element to process:";
					 cin >> elem;
					 while (cin.get() != '\n')
						 continue;
					 if (list1.priorElem(elem, reElem))
						 cout << "The prior element of " << elem << " is " << reElem
						 << ".\n";
					 else
						 cout << "Get prior element falied!\n";
				 }
				 break;
		case 't':
		case 'T':if (!list1.listTraverse())
			cout << "Traverse list failed.\n";
			break;
		}
		cout << "Please enter C to clear the List.\n"
			<< "D to delete an element.\n"
			<< "F to check whether the list is full or not.\n"
			<< "G to get an element.\n"
			<< "I to insert an element.\n"
			<< "L to locate the element.\n"
			<< "N to get the next element.\n"
			<< "P to get the prior element.\n"
			<< "T to traverse the element.\n"
			<< "or Q to quit.\n";
	}
	cout << "Bye\n";
}