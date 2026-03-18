#pragma once

#include <iostream>
#include <string>

#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"

class clsDepositScreen : protected clsScreen
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

	static void ShowDepositScreen()
	{
		std::string AccountNumber;

		_DrawScreenHeader("\tDeposit Screen");

		std::cout << "\nPlease Enter Account Number: ";
		AccountNumber = clsInputValidate::ReadString();

		while (!clsBankClient::IsClientExists(AccountNumber))
		{
			std::cout << "\nAccount number is not found, choose another one: ";
			AccountNumber = clsInputValidate::ReadString();
		}

		clsBankClient Client = clsBankClient::Find(AccountNumber);
		_PrintClient(Client);

		double Amount = 0;
		std::cout << "\nPlease Enter Deposit Amount? ";
		Amount = clsInputValidate::ReadDblNumber();

		char Answer = 'y';
		std::cout << "\nAre You Sure You Want To Perform This Operation (y/n)? ";
		std::cin >> Answer;

		if (Answer == 'Y' || Answer == 'y')
		{
			Client.Deposit(Amount);
			std::cout << "\nOperation Done Successfully.\n";
			std::cout << "\nNew Balance is " << Client.AccountBalance << std::endl;
		}
		else
			std::cout << "\nOperation Was Cancelled\n";
	}
};

