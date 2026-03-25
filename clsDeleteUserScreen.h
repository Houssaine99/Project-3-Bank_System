#pragma once

#include <iostream>
#include <string>

#include "clsScreen.h"
#include "clsUser.h"
#include "clsInputValidate.h"


class clsDeleteUserScreen : protected clsScreen
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

	static void ShowDeleteUserScreen()
	{
		_DrawScreenHeader("\t  Delete User Screen");

		std::string Username;

		std::cout << "\nPlease Enter Username: ";
		Username = clsInputValidate::ReadString();

		while (!clsUser::IsUserExist(Username))
		{
			std::cout << "\nAccount Number is NOT Found! Enter Another One: ";
			Username = clsInputValidate::ReadString();
		}

		clsUser User = clsUser::Find(Username);
		_PrintUser(User);

		char Answer = 'n';
		std::cout << "\nAre You Sure You Want To Delete This User (y/n)? ";
		std::cin >> Answer;

		if (Answer == 'Y' || Answer == 'y')
		{
			if (User.Delete())
			{
				std::cout << "\nUser is Deleted Successfully.\n";
				_PrintUser(User);
			}
			else
				std::cout << "\nFaild To Delete User!\n";
		}

		
	}
};

