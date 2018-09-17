#include <iostream>
#include "person.h"

int main()
{
	Person one;
	Person two("Fu");
	Person three("Fu", "waiye");
	one.show();
	one.formalShow();
	two.show();
	two.formalShow();
	three.show();
	three.formalShow();
	std::cin.get();
}