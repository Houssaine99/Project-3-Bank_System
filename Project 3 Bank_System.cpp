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

void AddNewClient()
{
	std::string AccountNumber;

	std::cout << "\nPlease Account Number: ";
	AccountNumber = clsInputValidate::ReadString();

	while (clsBankClient::IsClientExists(AccountNumber))
	{
		std::cout << "\Account Number is Already Exist! Enter Another One: ";
		AccountNumber = clsInputValidate::ReadString();
	}

	clsBankClient NewClient = clsBankClient::GetAddNewClientObject(AccountNumber);

	ReadClientInfo(NewClient);

	clsBankClient::enSaveResults SaveResults = NewClient.Save();

	switch (SaveResults)
	{
	case clsBankClient::enSaveResults::svSucceeded:
		std::cout << "\nClient Saved Successfully.\n";
		NewClient.Print();
		break;

	case clsBankClient::enSaveResults::svFaildEmptyObject:
		std::cout << "\nError! Client is Not Saved.\n";
		break;

	case clsBankClient::enSaveResults::svFaildAccountNumberExist:
		std::cout << "\nError! Client is Already exist.\n";
		break;
	}
}

void DeleteClient()
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

	char Answer;

	std::cout << "\nAre You Sure You Want To Delete This Client (Y/N)? ";
	std::cin >> Answer;

	if (Answer == 'Y' || Answer == 'y')
	{
		if (Client.Delete())
		{
			std::cout << "\nClient Deleted Succssefully.\n";
			Client.Print();
		}
		else
			std::cout << "\nFaild To Delete Client!\n";
	}

}

int main()
{
	DeleteClient();
	
	
	system("pause>0");
	return 0;
}
