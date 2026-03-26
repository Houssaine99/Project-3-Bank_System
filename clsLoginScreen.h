#pragma once

#include <iostream>

#include "clsScreen.h"
#include "clsMainScreen.h"
#include "clsInputValidate.h"

class clsLoginScreen : protected clsScreen
{
private:

	static void _Login()
	{
		bool LoginFaild = false;
		std::string Username;
		std::string Password;

		do
		{
			if (LoginFaild)
			{
				std::cout << "\nInvalid Username/Password!\n";
			}

			std::cout << "\nPlease Enter Username: ";
			Username = clsInputValidate::ReadString();

			std::cout << "Please Enter Password: ";
			Password = clsInputValidate::ReadString();

			CurrentUser = clsUser::Find(Username, Password);
			LoginFaild = CurrentUser.IsEmpty();

		} while (LoginFaild);

		clsMainScreen::ShowMainMenu();
	}

public:

	static void ShowLoginScreen()
	{
		system("cls");
		_DrawScreenHeader("\t    Login Screen");
		_Login();
	}

};

