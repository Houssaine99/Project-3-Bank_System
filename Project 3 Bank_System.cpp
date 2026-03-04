// Bank System Using OOP Started on 12/02/2022:

#include <iostream>
#include <string>
#include <iomanip>

#include "clsBankClient.h"
#include "clsInputValidate.h"
#include "ClsUtil.h"
#include "clsMainScreen.h"

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

void PrintClientRecordLine(clsBankClient Client)
{
	std::cout << "| " << std::left << std::setw(15) << Client.AccountNumber();
	std::cout << "| " << std::left << std::setw(25) << Client.FullName();
	std::cout << "| " << std::left << std::setw(12) << Client.Phone;
	std::cout << "| " << std::left << std::setw(30) << Client.Email;
	std::cout << "| " << std::left << std::setw(10) << Client.PINCode;
	std::cout << "| " << std::left << std::setw(12) << Client.AccountBalance << std::left << std::setw(1) << "|" << std::endl;
}

void ShowClientsList()
{
	std::vector <clsBankClient> vClients = clsBankClient::GetClientsList();

	std::cout << std::endl << std::string(5, '\t') << "Clients List: (" << vClients.size() << ") Clients" << std::endl;
	std::cout << std::string(117, '-') << std::endl;

	std::cout << "| " << std::left << std::setw(15) << "Account Number";
	std::cout << "| " << std::left << std::setw(25) << "Client Name";
	std::cout << "| " << std::left << std::setw(12) << "Phone";
	std::cout << "| " << std::left << std::setw(30) << "Email";
	std::cout << "| " << std::left << std::setw(10) << "PIN Code";
	std::cout << "| " << std::left << std::setw(12) << "Balance" << std::left << std::setw(1) << "|" << std::endl;
	std::cout << std::string(117, '-') << std::endl;

	if (vClients.size() == 0)
	{
		std::cout << "| " << std::string(4, '\t') << "No Clients Available In the System!" << std::right << std::setw(50) << "|" << std::endl;
	}
	else
	{
		for (clsBankClient& Client : vClients)
			PrintClientRecordLine(Client);
	}

	std::cout << std::string(117, '-') << std::endl;
}

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
