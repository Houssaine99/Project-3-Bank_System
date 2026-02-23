// Bank System Using OOP Started on 12/02/2022:

#include <iostream>
#include "clsBankClient.h"
#include "clsInputValidate.h"

void ReadClientInfo(clsBankClient& Client)
{
	std::cout << "\nEnter Client First Name: ";
	Client.FirstName = clsInputValidate::ReadString();
	
	std::cout << "\nEnter Client Last Name: ";
	Client.LastName = clsInputValidate::ReadString();

	std::cout << "\nEnter Client Email: ";
	Client.Email = clsInputValidate::ReadString();

	std::cout << "\nEnter Client Phone: ";
	Client.Phone = clsInputValidate::ReadString();

	std::cout << "\nEnter Client PINCode: ";
	Client.PINCode = clsInputValidate::ReadString();

	std::cout << "\nEnter Client Account Balance? ";
	Client.AccountBalance = clsInputValidate::ReadFltNumber();
}

void UpdateClient()
{
	std::string AccountNumber;

	std::cout << "\nPlease Enter Client Account Number: ";
	AccountNumber = clsInputValidate::ReadString();

	while (!clsBankClient::IsClientExists(AccountNumber))
	{
		std::cout << "\Account Number is NOT Found! Enter Another One: ";
		AccountNumber = clsInputValidate::ReadString();
	}

	clsBankClient Client = clsBankClient::Find(AccountNumber);
	Client.Print();

	std::cout << "\nUpdate The Client Info:";
	std::cout << "\n-----------------------\n";

	ReadClientInfo(Client);

	clsBankClient::enSaveResults SaveResults = Client.Save();

	switch (SaveResults)
	{
	case clsBankClient::enSaveResults::svSucceeded:
		std::cout << "\nUpdates Saved Successfully.\n";
		Client.Print();
		break;

	case clsBankClient::enSaveResults::svFaildEmptyObject:
		std::cout << "\nError! Updates Are Not Saved.\n";
		break;
	}
}

int main()
{
	UpdateClient();
	
	
	system("pause>0");
	return 0;
}
