#pragma once

#include <iostream>
#include <iomanip>
#include <string>

#include "clsScreen.h"
#include "clsBankClient.h"


class clsClientListScreen : protected clsScreen
{
private:

	static void _PrintClientRecordLine(clsBankClient Client)
	{
		
		std::cout << std::setw(2) << std::left << "" << "| " << std::left << std::setw(15) << Client.AccountNumber();
		std::cout << "| " << std::left << std::setw(25) << Client.FullName();
		std::cout << "| " << std::left << std::setw(12) << Client.Phone;
		std::cout << "| " << std::left << std::setw(30) << Client.Email;
		std::cout << "| " << std::left << std::setw(10) << Client.PINCode;
		std::cout << "| " << std::left << std::setw(12) << Client.AccountBalance << std::left << std::setw(1) << "|" << std::endl;
	}

public:

	static void ShowClientsList()
	{
		std::vector <clsBankClient> vClients = clsBankClient::GetClientsList();
		std::string Title = "\t  Client List Screen";
		std::string SubTitle = "\t    (" + std::to_string(vClients.size()) + ") Client(s)";

		_DrawScreenHeader(Title, SubTitle);

		
		std::cout << std::setw(2) << std::left << "" << std::string(117, '-') << std::endl;
		std::cout << std::setw(2) << std::left << "" << "| " << std::left << std::setw(15) << "Account Number";
		std::cout << "| " << std::left << std::setw(25) << "Client Name";
		std::cout << "| " << std::left << std::setw(12) << "Phone";
		std::cout << "| " << std::left << std::setw(30) << "Email";
		std::cout << "| " << std::left << std::setw(10) << "PIN Code";
		std::cout << "| " << std::left << std::setw(12) << "Balance" << std::left << std::setw(1) << "|" << std::endl;
		std::cout << std::setw(2) << std::left << "" << std::string(117, '-') << std::endl;

		if (vClients.size() == 0)
		{
			std::cout << std::setw(2) << std::left << "" << "| " << std::string(4, '\t') << "No Clients Available In the System!" << std::right << std::setw(52) << "|" << std::endl;
		}
		else
		{
			for (clsBankClient& Client : vClients)
				_PrintClientRecordLine(Client);
		}

		std::cout << std::setw(2) << std::left << "" << std::string(117, '-') << std::endl;
	}

};

