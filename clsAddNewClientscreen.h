#pragma once

#include <iostream>
#include <iomanip>
#include <string>

#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsBankClient.h"


class clsAddNewClientscreen : protected clsScreen
{
private:

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

	static void ShowAddNewClientScreen()
	{
		_DrawScreenHeader("\t  Add New Client Screen");

		std::string AccountNumber;

		std::cout << "\nPlease Account Number: ";
		AccountNumber = clsInputValidate::ReadString();

		while (clsBankClient::IsClientExists(AccountNumber))
		{
			std::cout << "\Account Number is Already Exist! Enter Another One: ";
			AccountNumber = clsInputValidate::ReadString();
		}

		clsBankClient NewClient = clsBankClient::GetAddNewClientObject(AccountNumber);

		_ReadClientInfo(NewClient);

		clsBankClient::enSaveResults SaveResults = NewClient.Save();

		switch (SaveResults)
		{
		case clsBankClient::enSaveResults::svSucceeded:
			std::cout << "\nClient Saved Successfully. :-)\n";
			_PrintClient(NewClient);
			break;

		case clsBankClient::enSaveResults::svFaildEmptyObject:
			std::cout << "\nError! Client is Not Saved.\n";
			break;

		case clsBankClient::enSaveResults::svFaildAccountNumberExist:
			std::cout << "\nError! Client is Already exist.\n";
			break;
		}
	}
};

