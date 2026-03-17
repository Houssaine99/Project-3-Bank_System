// Bank System Using OOP Started on 12/02/2022:

#include <iostream>
#include <string>
#include <iomanip>

#include "clsBankClient.h"
#include "clsInputValidate.h"
#include "ClsUtil.h"
#include "clsMainScreen.h"


void PrintClientRecordBalanceLine(clsBankClient Client)
{
	std::cout << "| " << std::left << std::setw(25) << Client.AccountNumber();
	std::cout << "| " << std::left << std::setw(58) << Client.FullName();
	std::cout << "| " << std::left << std::setw(29) << Client.AccountBalance << std::left << std::setw(1) << "|\n";
}

void ShowTotalBalances()
{
	std::vector <clsBankClient> vClients = clsBankClient::GetClientsList();
	int NumberOfClients = vClients.size();
	double TotalBalances = 0;

	std::cout << "\n" << std::string(5, '\t') << "Balances List(" << NumberOfClients << ") Client(s)\n";

	std::cout << std::string(119, '-') << "\n";
	std::cout << "| " << std::left << std::setw(25) << "Account Number";
	std::cout << "| " << std::left << std::setw(58) << "Client Name";
	std::cout << "| " << std::left << std::setw(29) << "Account Balance" << std::left << std::setw(1) << "|\n";
	std::cout << std::string(119, '-') << "\n";

	TotalBalances = clsBankClient::GetTotalBalances();

	if(NumberOfClients == 0)
		std::cout << "| " << std::string(4, '\t') << "No Clients Available In the System!" << std::right << std::setw(52) << "|" << std::endl;
	else
	{
		for (clsBankClient& Client : vClients)
			PrintClientRecordBalanceLine(Client);
	}

	std::cout << std::string(119, '-') << std::endl;

	std::cout << std::string(5, '\t') << "  Total Balances = " << TotalBalances << std::endl;
	std::cout << std::string(5, '\t') << "  ( " << clsUtil::NumberToText(TotalBalances) << ")\n";
}

int main()
{
	clsMainScreen Main;

	Main.ShowMainMenu();

	system("pause>0");
	return 0;
}
