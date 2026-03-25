#pragma once

#include <iostream>
#include <string>
#include <cctype>

#include "clsScreen.h"
#include "clsUser.h"
#include "clsInputValidate.h"

class clsAddNewUserScreen : protected clsScreen
{
private:

	static void _ReadUserInfo(clsUser& User)
	{
		std::cout << "\nEnter User's First Name: ";
		User.FirstName = clsInputValidate::ReadString();

		std::cout << "\nEnter User's Last Name: ";
		User.LastName = clsInputValidate::ReadString();

		std::cout << "\nEnter User's Email: ";
		User.Email = clsInputValidate::ReadString();

		std::cout << "\nEnter User's Phone: ";
		User.Phone = clsInputValidate::ReadString();

		std::cout << "\nEnter User's Password: ";
		User.Password = clsInputValidate::ReadString();

		std::cout << "\nEnter Permissions: ";
		User.Permissions = _ReadPermissionsToSet();
	}

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

	static int _ReadPermissionsToSet()
	{
		short Permissions = 0;
		char Answer = 'Y';

		std::cout << "\nDo you want to give full access? y/n? ";
		std::cin >> Answer;

		if (toupper(Answer) == 'Y')
			return clsUser::enPermissions::eAll;

		std::cout << "\nDo you want to give access to:\n";

		std::cout << "\nShow Client List y/n? ";
		std::cin >> Answer;

		if (toupper(Answer) == 'Y')
			Permissions += clsUser::enPermissions::pListClient;

		std::cout << "\nAdd New Client y/n? ";
		std::cin >> Answer;

		if (toupper(Answer) == 'Y')
			Permissions += clsUser::enPermissions::pAddNewClient;

		std::cout << "\nDelete Client y/n? ";
		std::cin >> Answer;

		if (toupper(Answer) == 'Y')
			Permissions += clsUser::enPermissions::pDeleteClient;

		std::cout << "\nUpdate Client y/n? ";
		std::cin >> Answer;

		if (toupper(Answer) == 'Y')
			Permissions += clsUser::enPermissions::pUpdateClient;

		std::cout << "\nFind Client y/n? ";
		std::cin >> Answer;

		if (toupper(Answer) == 'Y')
			Permissions += clsUser::enPermissions::pFindClient;

		std::cout << "\nTransactions y/n? ";
		std::cin >> Answer;

		if (toupper(Answer) == 'Y')
			Permissions += clsUser::enPermissions::pTransactions;

		std::cout << "\nManage Users y/n? ";
		std::cin >> Answer;

		if (toupper(Answer) == 'Y')
			Permissions += clsUser::enPermissions::pManageUsers;

		return Permissions;
	}

public:

	static void ShowAddNewUserScreen()
	{
		_DrawScreenHeader("\t  Add New User Screen");

		std::string Username;

		std::cout << "\nPlease Enter Username: ";
		Username = clsInputValidate::ReadString();

		while (clsUser::IsUserExist(Username))
		{
			std::cout << "\nUsername is Already Exist! Enter Another One: ";
			Username = clsInputValidate::ReadString();
		}

		clsUser NewUser= clsUser::GetAddNewUserObject(Username);

		_ReadUserInfo(NewUser);

		clsUser::enSaveResults SaveResults = NewUser.Save();

		switch (SaveResults)
		{
		case clsUser::enSaveResults::svSucceeded:
			std::cout << "\nUser Saved Successfully. :-)\n";
			_PrintUser(NewUser);
			break;

		case clsUser::enSaveResults::svFaildEmptyObject:
			std::cout << "\nError! User is Not Saved.\n";
			break;

		case clsUser::enSaveResults::svFaildUsernameExist:
			std::cout << "\nError! User is Already exist.\n";
			break;
		}
	}
};

