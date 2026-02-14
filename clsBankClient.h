#pragma once

#include <iostream>
#include <vector>
#include <fstream>
#include <string>

#include "clsPerson.h"
#include "clsString.h"


class clsBankClient : public clsPerson
{
private:
	enum enMode { EmptyMode = 0, UpdateMode = 1 };

	enMode _Mode;
	std::string _AccountNumber;
	std::string _PINCode;
	float _AccountBalance;

	static clsBankClient _ConvertLineToClientObject(std::string Line, std::string Seperator = "#//#")
	{
		std::vector <std::string> vSplitedLine = clsString::Split(Line, Seperator);

		return clsBankClient(enMode::UpdateMode, vSplitedLine[0], vSplitedLine[1], vSplitedLine[2], vSplitedLine[3],
			vSplitedLine[4], vSplitedLine[5], std::stof(vSplitedLine[6]));

	}

	static clsBankClient _GetEmptyClientObject()
	{
		return clsBankClient(enMode::EmptyMode, "", "", "", "", "", "", 0);
	}

public:
	clsBankClient(enMode Mode, std::string FirstName, std::string LastName, std::string Email, std::string Phone,
		std::string AccountNumber, std::string PINCode, float AccountBalance) :
		clsPerson(FirstName, LastName, Email, Phone)

	{
		_Mode = Mode;
		_AccountNumber = AccountNumber;
		_PINCode = PINCode;
		_AccountBalance = AccountBalance;
	}

	bool IsEmpty()
	{
		return (_Mode == enMode::EmptyMode);
	}

	std::string GetAccountNumber()
	{
		return _AccountNumber;
	}

	
	void SetPINCode(std::string PINCode)
	{
		_PINCode = PINCode;
	}

	std::string GetPINCode()
	{
		return _PINCode;
	}

	__declspec(property(get = GetPINCode, put = SetPINCode)) std::string PINCode;


	void SetAccountBalance(float AccountBalance)
	{
		_AccountBalance = AccountBalance;
	}

	float GetAccountBlance()
	{
		return _AccountBalance;
	}

	__declspec(property(get = GetAccountBlance, put = SetAccountBalance)) float AccountBalance;

	void Print()
	{
		std::cout << "\nClient Card:";
		std::cout << "\n___________________";
		std::cout << "\nFirstName   : " << FirstName;
		std::cout << "\nLastName    : " << LastName;
		std::cout << "\nFull Name   : " << FullName();
		std::cout << "\nEmail       : " << Email;
		std::cout << "\nPhone       : " << Phone;
		std::cout << "\nAcc. Number : " << _AccountNumber;
		std::cout << "\nPassword    : " << _PINCode;
		std::cout << "\nBalance     : " << _AccountBalance;
		std::cout << "\n___________________\n";
	}

	static clsBankClient Find(std::string AccountNumber)
	{
		std::fstream MyFile;

		MyFile.open("Clients.txt", std::ios::in);

		if (MyFile.is_open())
		{
			std::string Line;

			while (std::getline(MyFile, Line))
			{
				clsBankClient Client = _ConvertLineToClientObject(Line);

				if (Client.GetAccountNumber() == AccountNumber)
				{
					MyFile.close();
					return Client;
				}

			}

			MyFile.close();
		}

		return _GetEmptyClientObject();
	}

	static clsBankClient Find(std::string AccountNumber, std::string PINCode)
	{
		std::fstream MyFile;

		MyFile.open("Clients.txt", std::ios::in);

		if (MyFile.is_open())
		{
			std::string Line;

			while (std::getline(MyFile, Line))
			{
				clsBankClient Client = _ConvertLineToClientObject(Line);

				if (Client.GetAccountNumber() == AccountNumber && Client.PINCode == PINCode)
				{
					MyFile.close();
					return Client;
				}
			}

			MyFile.close();
		}

		return _GetEmptyClientObject();
	}

	static bool IsClientExists(std::string AccountNumber)
	{
		clsBankClient Client = clsBankClient::Find(AccountNumber);

		return (!Client.IsEmpty());
	}

};

