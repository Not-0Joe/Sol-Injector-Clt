#include <iostream>

void waitForKey()
{
	std::cin.ignore(999999999, '\n');
	std::cin.get();
}