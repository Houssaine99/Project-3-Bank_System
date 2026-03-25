#pragma once

#include <iostream>
#include <string>

#include "clsScreen.h"
#include "clsUser.h"
#include "clsInputValidate.h"

class clsFindUserScreen : protected clsScreen
{
private:

	static void _PrintUser(clsUser& User)
	{
		std::cout << "\nUser Card: ";
		std::cout << "\n___________________";
		std::cout << "\nFirstName   : " << User.FirstName;
		std::cout << "\nLastName    : " << User.LastName;
		std::cout << "\nFull Name   : " << User.FullName();
		std::cout << "\nEmail       : " << User.Email;
		std::cout << "\nPhone       : " << User.Phone;
		std::cout << "\nUsername    : " << User.UserName;
		std::cout << "\nPassword    : " << User.Password;
		std::cout << "\nPermissions : " << User.Permissions;
		std::cout << "\n___________________\n";
	}

public:

	static void ShowFindUserScreen()
	{
		_DrawScreenHeader("\t  Find User Screen");

		std::string Username;
		std::cout << "\nPlease Enter Username? ";
		Username = clsInputValidate::ReadString();

		while (!clsUser::IsUserExist(Username))
		{
			std::cout << "\nUsername is not found, choose another one: ";
			Username = clsInputValidate::ReadString();
		}

		clsUser User = clsUser::Find(Username);

		if (!User.IsEmpty())
		{
			std::cout << "\nUser Found :-)\n";
		}
		else
		{
			std::cout << "\nUser Was not Found :-(\n";
		}

		_PrintUser(User);
	}
};

