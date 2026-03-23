#pragma once

#include <iostream>
#include <string>
#include <iomanip>

#include "clsScreen.h"
#include "clsUser.h"

class clsListUsersScreen : protected clsScreen
{
private:

	static void _PrintUserRecordLine(clsUser& User)
	{
		std::cout << std::setw(2) << std::left << "" << "| " << std::left << std::setw(15) << User.UserName;
		std::cout << "| " << std::left << std::setw(25) << User.FullName();
		std::cout << "| " << std::left << std::setw(12) << User.Phone;
		std::cout << "| " << std::left << std::setw(30) << User.Email;
		std::cout << "| " << std::left << std::setw(10) << User.Password;
		std::cout << "| " << std::left << std::setw(12) << User.Permissions << std::left << std::setw(1) << "|" << std::endl;
	}

public:

	static void ShowUsersList()
	{
		std::vector <clsUser> vUsers = clsUser::GetUsersList();
		std::string Title = "\t  Users List Screen";
		std::string SubTitle = "\t    (" + std::to_string(vUsers.size()) + ") User(s)";

		_DrawScreenHeader(Title, SubTitle);


		std::cout << std::setw(2) << std::left << "" << std::string(117, '-') << std::endl;
		std::cout << std::setw(2) << std::left << "" << "| " << std::left << std::setw(15) << "Username";
		std::cout << "| " << std::left << std::setw(25) << "Full Name";
		std::cout << "| " << std::left << std::setw(12) << "Phone";
		std::cout << "| " << std::left << std::setw(30) << "Email";
		std::cout << "| " << std::left << std::setw(10) << "Password";
		std::cout << "| " << std::left << std::setw(12) << "Permissions" << std::left << std::setw(1) << "|" << std::endl;
		std::cout << std::setw(2) << std::left << "" << std::string(117, '-') << std::endl;

		if (vUsers.size() == 0)
		{
			std::cout << std::setw(2) << std::left << "" << "| " << std::string(4, '\t') << "No Users Available In the System!" << std::right << std::setw(52) << "|" << std::endl;
		}
		else
		{
			for (clsUser& User : vUsers)
				_PrintUserRecordLine(User);
		}

		std::cout << std::setw(2) << std::left << "" << std::string(117, '-') << std::endl;
	}
};

