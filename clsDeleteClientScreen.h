#pragma once

#include <iostream>
#include <string>

#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"

class clsDeleteClientScreen : clsScreen
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

public:

	static void ShowDeleteClientScreen()
	{
		std::string AccountNumber;

		_DrawScreenHeader("\tDelete Client Screen");

		std::cout << "\nPlease Enter Client Account Number: ";
		AccountNumber = clsInputValidate::ReadString();

		while (!clsBankClient::IsClientExists(AccountNumber))
		{
			std::cout << "\Account Number is NOT Found! Enter Another One: ";
			AccountNumber = clsInputValidate::ReadString();
		}

		clsBankClient Client = clsBankClient::Find(AccountNumber);
		_PrintClient(Client);

		char Answer;

		std::cout << "\nAre You Sure You Want To Delete This Client (Y/N)? ";
		std::cin >> Answer;

		if (Answer == 'Y' || Answer == 'y')
		{
			if (Client.Delete())
			{
				std::cout << "\nClient Deleted Succssefully.\n";
				_PrintClient(Client);
			}
			else
				std::cout << "\nFaild To Delete Client!\n";
		}
	}
};

