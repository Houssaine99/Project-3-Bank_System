#pragma once

#include <iostream>
#include <string>
#include <iomanip>

#include "clsScreen.h"
#include "ClsUtil.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"

class clsTotalBalancesScreen : protected clsScreen
{
private:

	static void _PrintClientRecordBalanceLine(clsBankClient& Client)
	{
		std::cout << std::left << std::setw(10) << "" << "| " << std::left << std::setw(25) << Client.AccountNumber();
		std::cout << "| " << std::left << std::setw(40) << Client.FullName();
		std::cout << "| " << std::left << std::setw(29) << Client.AccountBalance << std::left << std::setw(1) << "|\n";
	}

public:

	static void ShowTotalBalancesScreen()
	{
		std::vector <clsBankClient> vClients = clsBankClient::GetClientsList();

		int NumberOfClients = vClients.size();
		double TotalBalances = 0;
		std::string Title = "\t   Total Balances";
		std::string SubTitle = "\t   (" + std::to_string(NumberOfClients) + ") Clients(s)";

		_DrawScreenHeader(Title, SubTitle);

		std::cout << std::left << std::setw(10) << "" << std::string(101, '-') << "\n";
		std::cout << std::left << std::setw(10) << "" << "| " << std::left << std::setw(25) << "Account Number";
		std::cout << "| " << std::left << std::setw(40) << "Client Name";
		std::cout << "| " << std::left << std::setw(29) << "Account Balance" << std::left << std::setw(1) << "|\n";
		std::cout << std::left << std::setw(10) << "" << std::string(101, '-') << "\n";

		TotalBalances = clsBankClient::GetTotalBalances();

		if (NumberOfClients == 0)
			std::cout << std::left << std::setw(10) << "" << "| " << std::string(4, '\t') << "No Clients Available In the System!" << std::right << std::setw(36) << "|" << std::endl;
		else
		{
			for (clsBankClient& Client : vClients)
				_PrintClientRecordBalanceLine(Client);
		}

		std::cout << std::left << std::setw(10) << "" << std::string(101, '-') << std::endl;

		std::cout << std::string(5, '\t') << "  Total Balances = " << TotalBalances << std::endl;
		std::cout << std::string(5, '\t') << "  ( " << clsUtil::NumberToText(TotalBalances) << ")\n";
	}
};

