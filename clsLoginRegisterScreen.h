#pragma once

#include <iostream>
#include <iomanip>

#include "clsScreen.h"
#include "clsUser.h"

class clsLoginRegisterScreen : protected clsScreen
{
private:

	static void _PrintLoginRegisterRecordLine(clsUser::stLoginRegisterRecord& LoginRegisterRecord)
	{
		std::cout << std::left << std::setw(18) << "" << "| " << std::left << std::setw(30) << LoginRegisterRecord.DateTime;
		std::cout << "| " << std::left << std::setw(15) << LoginRegisterRecord.Username;
		std::cout << "| " << std::left << std::setw(15) << LoginRegisterRecord.Password;
		std::cout << "| " << std::left << std::setw(15) << LoginRegisterRecord.Permissions << std::left << std::setw(1) << "|" << std::endl;
	}

public:

	static void ShowLoginRegisterScreen()
	{
		if (!_CheckAccessRights(clsUser::enPermissions::pLoginRegister))
			return;

		std::vector <clsUser::stLoginRegisterRecord> vLoginRegisterRecords = clsUser::GetLoginRegisterList();

		std::string Title = "  Login Register List Screen";
		std::string Subtitle = "\t   (" + std::to_string(vLoginRegisterRecords.size()) + ") Record(s)";

		_DrawScreenHeader(Title, Subtitle);

		std::cout << std::left << std::setw(18) << "" << std::string(84, '-') << std::endl;
		std::cout << std::left << std::setw(18) << "" << "| " << std::left << std::setw(30) << "Date/Time";
		std::cout << "| " << std::left << std::setw(15) << "Username";
		std::cout << "| " << std::left << std::setw(15) << "Password";
		std::cout << "| " << std::left << std::setw(15) << "Permissions" << std::left << std::setw(1) << "|" << std::endl;
		std::cout << std::left << std::setw(18) << "" << std::string(84, '-') << std::endl;

		for (clsUser::stLoginRegisterRecord& Record : vLoginRegisterRecords)
		{
			_PrintLoginRegisterRecordLine(Record);
		}

		std::cout << std::left << std::setw(18) << "" << std::string(84, '-') << std::endl;

	}
};

