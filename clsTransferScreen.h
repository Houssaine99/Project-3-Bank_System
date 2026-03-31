#pragma once

#include <iostream>

#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"

class clsTransferScreen : protected clsScreen
{
private:

	static void _PrintClient(clsBankClient& Client)
	{
		std::cout << "\nClient Card:";
		std::cout << "\n___________________";
		std::cout << "\nFull Name   : " << Client.FullName();
		std::cout << "\nAcc. Number : " << Client.AccountNumber();
		std::cout << "\nBalance     : " << Client.AccountBalance;
		std::cout << "\n___________________\n";
	}

	static std::string _ReadAccountNumber()
	{
		std::string AccountNumber = clsInputValidate::ReadString();
		while (!clsBankClient::IsClientExists(AccountNumber))
		{
			std::cout << "\nAccount number is not found, choose another one: ";
			AccountNumber = clsInputValidate::ReadString();
		}
		return AccountNumber;
	}

	static double _ReadAmount(clsBankClient& DestinationClient)
	{
		std::cout << "\nEnter Transfer Amount? ";
		double Amount = clsInputValidate::ReadDblNumber();

		while (Amount > DestinationClient.AccountBalance)
		{
			std::cout << "\nAmount Exceeds Available Balance! Enter Another Amount? ";
			Amount = clsInputValidate::ReadDblNumber();
		}

		return Amount;
	}

public:

	static void ShowTransferScreen()
	{
		_DrawScreenHeader("\t   Transfer Screen");

		std::cout << "\nPlease Enter Account Number To Transfer From: ";
		clsBankClient SourceClient = clsBankClient::Find(_ReadAccountNumber());
		_PrintClient(SourceClient);

		std::cout << "\nPlease Enter Account Number To Transfer To: ";
		clsBankClient DestinationClient = clsBankClient::Find(_ReadAccountNumber());
		_PrintClient(DestinationClient);

		double Amount = _ReadAmount(DestinationClient);

		char Answer = 'Y';
		std::cout << "\nAre You Sure You Want To Perform This Operation (y/n)? ";
		std::cin >> Answer;

		if (Answer == 'Y' || Answer == 'y')
		{
			if (SourceClient.Transfer(Amount, DestinationClient))
			{
				std::cout << "\nTransfer Done Successfully.\n";
				_PrintClient(SourceClient);
				_PrintClient(DestinationClient);
			}
			else
				std::cout << "\nTransfer Faild!\n";
		}
		else
			std::cout << "\nThis Operation Was Cancelled!\n";
	}
};

