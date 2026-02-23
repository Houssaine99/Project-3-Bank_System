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

	static std::string _ConvertClientObjectToLine(clsBankClient Client, std::string Seperator = "#//#")
	{
		std::string ClientRecord;

		ClientRecord += Client.FirstName + Seperator;
		ClientRecord += Client.LastName + Seperator;
		ClientRecord += Client.Email + Seperator;
		ClientRecord += Client.Phone + Seperator;
		ClientRecord += Client.AccountNumber() + Seperator;
		ClientRecord += Client.PINCode + Seperator;
		ClientRecord += std::to_string(Client.AccountBalance);

		return ClientRecord;

	}

	static clsBankClient _GetEmptyClientObject()
	{
		return clsBankClient(enMode::EmptyMode, "", "", "", "", "", "", 0);
	}

	static std::vector <clsBankClient> _LoadClientsDataFromFile()
	{
		std::vector <clsBankClient> vClients;

		std::fstream MyFile;

		MyFile.open("Clients.txt", std::ios::in);

		if (MyFile.is_open())
		{
			std::string Line;

			while (std::getline(MyFile, Line))
			{
				clsBankClient Client = _ConvertLineToClientObject(Line);

				vClients.push_back(Client);
			}

			MyFile.close();
		}

		return vClients;
	}

	static void _SaveClientsDataToFile(std::vector <clsBankClient> vClients)
	{
		std::fstream MyFile;

		MyFile.open("Clients.txt", std::ios::out);

		if (MyFile.is_open())
		{
			std::string DataLine;

			for (clsBankClient& Client : vClients)
			{
				DataLine = _ConvertClientObjectToLine(Client);
				MyFile << DataLine << std::endl;
			}

			MyFile.close();
		}
	}

	void _Update()
	{
		std::vector <clsBankClient> _vClients = _LoadClientsDataFromFile();

		for (clsBankClient& Client : _vClients)
		{
			if (Client.AccountNumber() == AccountNumber())
			{
				Client = *this;
				break;
			}
		}

		_SaveClientsDataToFile(_vClients);
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

	std::string AccountNumber()
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

				if (Client.AccountNumber() == AccountNumber)
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

				if (Client.AccountNumber() == AccountNumber && Client.PINCode == PINCode)
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

	enum enSaveResults { svFaildEmptyObject = 0, svSucceeded = 1 };

	enSaveResults Save()
	{
		 switch (_Mode)
		 {
		 case enMode::EmptyMode:
			 return enSaveResults::svFaildEmptyObject;

		 case enMode::UpdateMode:
			 _Update();
			 return enSaveResults::svSucceeded;
		 }
	}
};

