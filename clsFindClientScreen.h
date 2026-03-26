#pragma once

#include <iostream>


#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsBankClient.h"

class clsFindClientScreen : protected clsScreen
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

	static void ShowFindClientScreen()
	{
		if (!_CheckAccessRights(clsUser::enPermissions::pFindClient))
			return;

		std::string AccountNumber;

		_DrawScreenHeader("\tFind Client Screen");

		std::cout << "\nPlease Enter Account Number: ";
		AccountNumber = clsInputValidate::ReadString();
		while (!clsBankClient::IsClientExists(AccountNumber))
		{
			std::cout << "\nAccount number is not found, choose another one: ";
			AccountNumber = clsInputValidate::ReadString();
		}

		clsBankClient Client = clsBankClient::Find(AccountNumber);

		if (!Client.IsEmpty())
		{
			std::cout << "\nClient Found :-)\n";
		}
		else
		{
			std::cout << "\nClient Was not Found :-(\n";
		}

		_PrintClient(Client);
	}
};


