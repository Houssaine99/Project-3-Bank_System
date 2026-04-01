#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include "clsPerson.h"
#include "clsString.h"
#include "clsDate.h"
#include "clsUtil.h"
class clsUser : public clsPerson
{
private:

	enum enMode { EmptyMode = 0, UpdateMode = 1, AddNewMode = 2 };

	enMode _Mode;
	std::string _UserName;
	std::string _Password;
	int _Permissions = 0;
	bool _MarkForDelete = false;
	struct stLoginRegisterRecord;

	static stLoginRegisterRecord _ConvertLoginRegisterLineToRecord(std::string DataLine, std::string Seperator = "#//#")
	{
		stLoginRegisterRecord LoginRegisterRecord;

		std::vector <std::string> vLoginRegister = clsString::Split(DataLine, Seperator);

		LoginRegisterRecord.DateTime = vLoginRegister.at(0);
		LoginRegisterRecord.Username = vLoginRegister.at(1);
		LoginRegisterRecord.Password = clsUtil::DecryptText(vLoginRegister.at(2));
		LoginRegisterRecord.Permissions = std::stoi(vLoginRegister.at(3));

		return LoginRegisterRecord;
	}

	std::string _PrepareLoginRecord(std::string Seperator = "#//#")
	{
		std::string LoginRecord;
		LoginRecord += clsDate::GetSystemDateTimeString() + Seperator;
		LoginRecord += UserName + Seperator;
		LoginRecord += clsUtil::EncryptText(Password) + Seperator;
		LoginRecord += std::to_string(Permissions);

		return LoginRecord;
	}

	static clsUser _ConvertLineToUserObject(std::string Line, std::string Seperator = "#//#")
	{
		std::vector <std::string> vUserData = clsString::Split(Line, Seperator);
		
		return clsUser(enMode::UpdateMode, vUserData.at(0), vUserData.at(1), vUserData.at(2), vUserData.at(3),
			vUserData.at(4), clsUtil::DecryptText(vUserData.at(5)), std::stoi(vUserData.at(6)));
	}

	static std::string _ConvertUserObjectToLine(clsUser User, std::string Seperator = "#//#")
	{
		std::string Line;

		Line += User.FirstName + Seperator;
		Line += User.LastName + Seperator;
		Line += User.Email + Seperator;
		Line += User.Phone + Seperator;
		Line += User.UserName + Seperator;
		Line += clsUtil::EncryptText(User.Password) + Seperator;
		Line += std::to_string(User.Permissions);

		return Line;
	}

	static clsUser _GetEmptyUserObject()
	{
		return clsUser(enMode::EmptyMode, "", "", "", "", "", "", 0);
	}

	static std::vector <clsUser> _LoadUsersDataFromFile()
	{
		std::vector <clsUser> vUsersData;
		std::fstream File;

		File.open("Users.txt", std::ios::in);

		if (File.is_open())
		{
			std::string Line;

			while (std::getline(File, Line))
			{
				clsUser User = _ConvertLineToUserObject(Line);
				vUsersData.push_back(User);
			}

			File.close();
		}

		return vUsersData;
	}

	static void _SaveUsersDataToFile(std::vector <clsUser> vUsersData)
	{
		std::fstream File;
		File.open("Users.txt", std::ios::out);

		if (File.is_open())
		{
			std::string Line;

			for (clsUser& User : vUsersData)
			{
				if (!User.MarkedForDeleted())
				{
					Line = _ConvertUserObjectToLine(User);
					File << Line << std::endl;
				}
			}

			File.close();
		}
	}

	static void _AddDataLineToFile(std::string DataLine)
	{
		std::fstream File;
		File.open("Users.txt", std::ios::out | std::ios::app);

		if (File.is_open())
		{
			File << DataLine << std::endl;
			File.close();
		}
	}

	void _Update()
	{
		std::vector <clsUser> vUsers = _LoadUsersDataFromFile();

		for (clsUser& User : vUsers)
		{
			if (User.UserName == _UserName)
			{
				User = *this;
				break;
			}
		}

		_SaveUsersDataToFile(vUsers);
	}

	void _AddNew()
	{
		_AddDataLineToFile(_ConvertUserObjectToLine(*this));
	}

public:

	clsUser(enMode Mode, std::string FirstName, std::string LastName, std::string Email, std::string Phone,
		std::string UserName, std::string Password, int Permissions) :
		clsPerson(FirstName, LastName, Email, Phone)
	{
		_Mode = Mode;
		_UserName = UserName;
		_Password = Password;
		_Permissions = Permissions;
	}

	enum enPermissions { eAll = -1, pListClient = 1, pAddNewClient = 2, pDeleteClient = 4,
	pUpdateClient = 8, pFindClient = 16, pTransactions = 32, pManageUsers = 64, pLoginRegister = 128 };

	struct stLoginRegisterRecord
	{
		std::string Username;
		std::string Password;
		std::string DateTime;
		int Permissions;
	};

	bool IsEmpty()
	{
		return (_Mode == enMode::EmptyMode);
	}

	bool MarkedForDeleted()
	{
		return _MarkForDelete;
	}


	void SetUserName(std::string UserName)
	{
		_UserName = UserName;
	}

	std::string GetUserName()
	{
		return _UserName;
	}

	__declspec(property(get = GetUserName, put = SetUserName)) std::string UserName;


	void SetPassword(std::string Password)
	{
		_Password = Password;
	}

	std::string GetPassword()
	{
		return _Password;
	}
	
	__declspec(property(get = GetPassword, put = SetPassword)) std::string Password;


	void SetPermissions(int Permissions)
	{
		_Permissions = Permissions;
	}

	int GetPermissions()
	{
		return _Permissions;
	}

	__declspec(property(get = GetPermissions, put = SetPermissions)) int Permissions;


	static clsUser Find(std::string UserName)
	{
		std::fstream File;

		File.open("Users.txt", std::ios::in);

		if (File.is_open())
		{
			std::string Line;

			while (std::getline(File, Line))
			{
				clsUser User = _ConvertLineToUserObject(Line);

				if (User.UserName == UserName)
				{
					File.close();
					return User;
				}
			}

			File.close();
		}

		return _GetEmptyUserObject();
	}

	static clsUser Find(std::string UserName, std::string Password)
	{
		std::fstream File;

		File.open("Users.txt", std::ios::in);

		if (File.is_open())
		{
			std::string Line;

			while (std::getline(File, Line))
			{
				clsUser User = _ConvertLineToUserObject(Line);

				if (User.UserName == UserName && User.Password == Password)
				{
					File.close();
					return User;
				}
			}

			File.close();
		}

		return _GetEmptyUserObject();
	}

	static bool IsUserExist(std::string UserName)
	{
		clsUser User = clsUser::Find(UserName);

		return (!User.IsEmpty());
	}

	enum enSaveResults { svFaildEmptyObject = 0, svSucceeded = 1, svFaildUsernameExist = 2 };

	enSaveResults Save()
	{
		switch (_Mode)
		{
		case enMode::EmptyMode:
			return svFaildEmptyObject;

		case enMode::UpdateMode:
			_Update();
			return svSucceeded;

		case enMode::AddNewMode:
			if (IsUserExist(_UserName))
				return svFaildUsernameExist;

			_AddNew();
			_Mode = enMode::UpdateMode;
			return svSucceeded;
		}
	}

	bool Delete()
	{
		std::vector <clsUser> vUsers = _LoadUsersDataFromFile();

		for (clsUser& User : vUsers)
		{
			if (User.UserName == UserName)
			{
				User._MarkForDelete = true;
				break;
			}
		}

		_SaveUsersDataToFile(vUsers);

		*this = _GetEmptyUserObject();

		return true;
	}

	static clsUser GetAddNewUserObject(std::string UserName)
	{
		return clsUser(enMode::AddNewMode, "", "", "", "", UserName, "", 0);
	}

	static std::vector <clsUser> GetUsersList()
	{
		return _LoadUsersDataFromFile();
	}

	bool CheckAccessPermissions(enPermissions Permissions)
	{
		if (this->Permissions == enPermissions::eAll)
			return true;
		else if ((this->Permissions & Permissions) == Permissions)
			return true;
		else
			return false;
	}

	void RegisterLogIn()
	{
		std::string DataLine = _PrepareLoginRecord();
		std::fstream File;
		File.open("LoginRegister.txt", std::ios::out | std::ios::app);

		if (File.is_open())
		{
			File << DataLine << std::endl;
			File.close();
		}
	}

	static std::vector <stLoginRegisterRecord> GetLoginRegisterList()
	{
		std::vector <stLoginRegisterRecord> vLoginRegisterRecords;
		std::fstream File;
		File.open("LoginRegister.txt", std::ios::in);

		if (File.is_open())
		{
			std::string Line;
			stLoginRegisterRecord Record;
			while (std::getline(File, Line))
			{
				Record = _ConvertLoginRegisterLineToRecord(Line);
				vLoginRegisterRecords.push_back(Record);
			}
			File.close();
		}

		return vLoginRegisterRecords;
	}
};

