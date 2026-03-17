#pragma once

#include <iostream>

#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsBankClient.h"

class clsUpdateClientScreen : protected clsScreen
{
private:

	static void _PrintClient(clsBankClient& Client)
	{
		std::cout << "\nClient Card:";
		std::cout << "\n___________________";
		std::cout << "\nFirstName   : " << Client.FirstName;
		std::cout << "\nLastName    : " << Client.LastName;
		std::cout << "\nFull Name   : " << Client.FullName();
		std::cout << "\nEmail       : " << Client.Email;
		std::cout << "\nPhone       : " << Client.Phone;
		std::cout << "\nAcc. Number : " << Client.AccountNumber();
		std::cout << "\nPassword    : " << Client.PINCode;
		std::cout << "\nBalance     : " << Client.AccountBalance;
		std::cout << "\n___________________\n";
	}

	static void _ReadClientInfo(clsBankClient& Client)
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

public:

	static void ShowUpdateClientScreen()
	{
		std::string AccountNumber;

		_DrawScreenHeader("\tUpdate Client Screen");

		std::cout << "\nPlease Enter Client Account Number: ";
		AccountNumber = clsInputValidate::ReadString();

		while (!clsBankClient::IsClientExists(AccountNumber))
		{
			std::cout << "\Account Number is NOT Found! Enter Another One: ";
			AccountNumber = clsInputValidate::ReadString();
		}

		clsBankClient Client = clsBankClient::Find(AccountNumber);
		_PrintClient(Client);

		std::cout << "\nUpdate The Client Info:";
		std::cout << "\n-----------------------\n";

		_ReadClientInfo(Client);

		clsBankClient::enSaveResults SaveResults = Client.Save();

		switch (SaveResults)
		{
		case clsBankClient::enSaveResults::svSucceeded:
			std::cout << "\nUpdates Saved Successfully.\n";
			_PrintClient(Client);
			break;

		case clsBankClient::enSaveResults::svFaildEmptyObject:
			std::cout << "\nError! Updates Are Not Saved.\n";
			break;
		}
	}
};

