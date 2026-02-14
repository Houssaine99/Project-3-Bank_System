// Bank System Using OOP Started on 12/02/2022:

#include <iostream>
#include "clsBankClient.h"

int main()
{
	clsBankClient Client1 = clsBankClient::Find("A101");
	clsBankClient Client2 = clsBankClient::Find("A111");

	Client1.Print();

	std::cout << std::endl;

	Client2.Print();

	std::cout << std::endl << clsBankClient::IsClientExists("A101") << std::endl;
	std::cout << clsBankClient::IsClientExists("A1") << std::endl;

	system("pause>0");
	return 0;
}
