#pragma once

#include <iostream>
#include <vector>
#include <fstream>
#include <string>

#include "clsPerson.h"
#include "clsString.h"
#include "clsDate.h"


class clsBankClient : public clsPerson
{
private:
	enum enMode { EmptyMode = 0, UpdateMode = 1, AddNew = 2 };

	enMode _Mode;
	std::string _AccountNumber;
	std::string _PINCode;
	float _AccountBalance;
	bool _MarkForDelete = false;
	struct stTransferLogRecord;

	static stTransferLogRecord _ConvertTransferLogLineToRecord(std::string Line, std::string Seperator = "#//#")
	{
		stTransferLogRecord TransferLogRecord;
		std::vector <std::string> vTransferLog = clsString::Split(Line, Seperator);

		TransferLogRecord.DateTime = vTransferLog.at(0);
		TransferLogRecord.SourceClientAccNumber = vTransferLog.at(1);
		TransferLogRecord.DestinationClientAccNumber = vTransferLog.at(2);
		TransferLogRecord.Amount = std::stod(vTransferLog.at(3));
		TransferLogRecord.SourceClientAccBalance = std::stod(vTransferLog.at(4));
		TransferLogRecord.DestinationClientAccBalance = std::stod(vTransferLog.at(5));
		TransferLogRecord.Username = vTransferLog.at(6);

		return TransferLogRecord;
	}

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
				if (!Client._MarkForDelete)
				{
					DataLine = _ConvertClientObjectToLine(Client);
					MyFile << DataLine << std::endl;
				}
			}

			MyFile.close();
		}
	}

	static void _AddDataLineToFile(std::string DataLine)
	{
		std::fstream MyFile;
		MyFile.open("Clients.txt", std::ios::out | std::ios::app);

		if (MyFile.is_open())
		{
			MyFile << DataLine << std::endl;

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

	void _AddNew()
	{
		_AddDataLineToFile(_ConvertClientObjectToLine(*this));
	}

	std::string _PrepareTransferLogRecord(double Amount, clsBankClient& DestinationClient, std::string Username, std::string Seperator = "#//#")
	{
		std::string RecordLine;

		RecordLine += clsDate::GetSystemDateTimeString() + Seperator;
		RecordLine += AccountNumber() + Seperator;
		RecordLine += DestinationClient.AccountNumber() + Seperator;
		RecordLine += std::to_string(Amount) + Seperator;
		RecordLine += std::to_string(AccountBalance) + Seperator;
		RecordLine += std::to_string(DestinationClient.AccountBalance) + Seperator;
		RecordLine += Username;

		return RecordLine;
	}

	void _RegisterTransferLog(double Amount, clsBankClient& DestinationClient, std::string Username)
	{
		std::string DataLine = _PrepareTransferLogRecord(Amount, DestinationClient, Username);
		std::fstream File;
		File.open("TransferLog.txt", std::ios::out | std::ios::app);

		if (File.is_open())
		{
			File << DataLine << std::endl;
			File.close();
		}
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

	struct stTransferLogRecord
	{
		std::string DateTime;
		std::string SourceClientAccNumber;
		std::string DestinationClientAccNumber;
		double Amount = 0;
		double SourceClientAccBalance = 0;
		double DestinationClientAccBalance = 0;
		std::string Username;
	};

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

	static clsBankClient GetAddNewClientObject(std::string AccountNumber)
	{
		return clsBankClient(enMode::AddNew, "", "", "", "", AccountNumber, "", 0);
	}

	enum enSaveResults { svFaildEmptyObject = 0, svSucceeded = 1, svFaildAccountNumberExist = 2 };

	enSaveResults Save()
	{
		 switch (_Mode)
		 {
		 case enMode::EmptyMode:
			 return enSaveResults::svFaildEmptyObject;

		 case enMode::UpdateMode:
			 _Update();
			 return enSaveResults::svSucceeded;

		 case enMode::AddNew:

			 if (IsClientExists(AccountNumber()))
				 return enSaveResults::svFaildAccountNumberExist;

			 _AddNew();
			 _Mode = enMode::UpdateMode;
			 return enSaveResults::svSucceeded;
		 }
	}

	bool Delete()
	{
		std::vector <clsBankClient> vClients = _LoadClientsDataFromFile();

		for (clsBankClient& Client : vClients)
		{
			if (Client.AccountNumber() == AccountNumber())
			{
				Client._MarkForDelete = true;
				break;
			}
		}

		_SaveClientsDataToFile(vClients);

		*this = _GetEmptyClientObject();

		return true;
	}

	static std::vector <clsBankClient> GetClientsList()
	{
		return _LoadClientsDataFromFile();
	}

	static float GetTotalBalances()
	{
		std::vector <clsBankClient> vClients = _LoadClientsDataFromFile();
		float TotalBalances = 0;

		for (clsBankClient& Client : vClients)
		{
			TotalBalances += Client.AccountBalance;
		}

		return TotalBalances;
	}

	void Deposit(double Amount)
	{
		_AccountBalance += Amount;
		Save();
	}

	bool Withdraw(double Amount)
	{
		if (_AccountBalance < Amount)
			return false;
		else
		{
			_AccountBalance -= Amount;
			Save();
			return true;
		}
	}

	bool Transfer(double Amount, clsBankClient& DestinationClient, std::string Username)
	{
		if (Amount > AccountBalance)
			return false;
		
		Withdraw(Amount);
		DestinationClient.Deposit(Amount);
		_RegisterTransferLog(Amount, DestinationClient, Username);
		return true;
	}

	static std::vector <stTransferLogRecord> GetTransferLogList()
	{
		std::vector <stTransferLogRecord> vTransferLog;
		std::fstream File;
		File.open("TransferLog.txt", std::ios::in);

		if (File.is_open())
		{
			std::string Line;
			stTransferLogRecord Record;

			while (std::getline(File, Line))
			{
				Record = _ConvertTransferLogLineToRecord(Line);
				vTransferLog.push_back(Record);
			}
			File.close();
		}

		return vTransferLog;
	}
};

