#pragma once

#include <iostream>

#include "clsScreen.h"
#include "clsMainScreen.h"
#include "clsInputValidate.h"

class clsLoginScreen : protected clsScreen
{
private:

	static bool _Login()
	{
		bool LoginFaild = false;
		short FaildLoginCount = 0;
		std::string Username;
		std::string Password;

		do
		{
			if (LoginFaild)
			{
				FaildLoginCount++;
				std::cout << "\nInvalid Username/Password!\n";
				std::cout << "You Have " << (3 - FaildLoginCount) << " Trial(s) To Login.\n";
			}

			if (FaildLoginCount == 3)
			{
				std::cout << "\n\nYou Are Locked After 3 Faild Trials.\n\n";
				return false;
			}

			std::cout << "\nPlease Enter Username: ";
			Username = clsInputValidate::ReadString();

			std::cout << "Please Enter Password: ";
			Password = clsInputValidate::ReadString();

			CurrentUser = clsUser::Find(Username, Password);
			LoginFaild = CurrentUser.IsEmpty();

		} while (LoginFaild);

		clsMainScreen::ShowMainMenu();
		return true;
	}

public:

	static bool ShowLoginScreen()
	{
		system("cls");
		_DrawScreenHeader("\t    Login Screen");
		return _Login();
	}

};

