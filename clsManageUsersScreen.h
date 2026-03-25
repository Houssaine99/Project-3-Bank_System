#pragma once

#include <iostream>
#include <string>
#include <iomanip>

#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsListUsersScreen.h"
#include "clsAddNewUserScreen.h"
#include "clsDeleteUserScreen.h"
#include "clsUpdateUserScreen.h"
#include "clsFindUserScreen.h"

class clsManageUsersScreen : protected clsScreen
{
private:

	enum enManageUsersMenuOptions {eListUsers = 1, eAddNewUser = 2, eDeleteUser = 3, eUpdateUser = 4,
	eFindUser = 5, eShowMainMenu = 6};

    static short _ReadManageUsersMenuOption()
    {
        short Option = 0;
        std::cout << std::left << std::setw(37) << "" << "Choose What Do You Want To Do [1 to 6]? ";
        Option = clsInputValidate::ReadIntNumberBetween(1, 6, "Enter a Number Between (1 and 6) ");

        return Option;
    }

    static void _GoBackToManageUsersMenu()
    {
        std::cout << std::setw(37) << std::left << "" << "\n\tPress any key to go back to Manage Users Menu...\n";

        system("pause>0");
        ShowManageUsersMenu();
    }

    static void _ShowListUsersScreen()
    {
        clsListUsersScreen::ShowUsersList();
    }

    static void _ShowAddNewUserScreen()
    {
        clsAddNewUserScreen::ShowAddNewUserScreen();
    }

    static void _ShowDeleteUserScreen()
    {
        clsDeleteUserScreen::ShowDeleteUserScreen();
    }

    static void _ShowUpdateUserScreen()
    {
        clsUpdateUserScreen::ShowUpdateUserScreen();
    }

    static void _ShowFindUserScreen()
    {
        clsFindUserScreen::ShowFindUserScreen();
    }

    static void _PerformManageUsersMenuOptions(enManageUsersMenuOptions ManageUsersMenuOptions)
    {
        switch (ManageUsersMenuOptions)
        {
        case enManageUsersMenuOptions::eListUsers:
            system("cls");
            _ShowListUsersScreen();
            _GoBackToManageUsersMenu();
            break;

        case enManageUsersMenuOptions::eAddNewUser:
            system("cls");
            _ShowAddNewUserScreen();
            _GoBackToManageUsersMenu();
            break;

        case enManageUsersMenuOptions::eDeleteUser:
            system("cls");
            _ShowDeleteUserScreen();
            _GoBackToManageUsersMenu();
            break;

        case enManageUsersMenuOptions::eUpdateUser:
            system("cls");
            _ShowUpdateUserScreen();
            _GoBackToManageUsersMenu();
            break;

        case enManageUsersMenuOptions::eFindUser:
            system("cls");
            _ShowFindUserScreen();
            _GoBackToManageUsersMenu();
            break;

        case enManageUsersMenuOptions::eShowMainMenu:
        {

        }
        }
    }


public:

	static void ShowManageUsersMenu()
	{
        system("cls");
        _DrawScreenHeader("\t  Manage Users Screen");

        std::cout << std::setw(37) << std::left << "" << "===========================================\n";
        std::cout << std::setw(37) << std::right << "" << std::string(2, '\t') << " Manage Users Menu\n";
        std::cout << std::setw(37) << std::left << "" << "===========================================\n";
        std::cout << std::setw(37) << std::left << "" << "\t[1] List Users.\n";
        std::cout << std::setw(37) << std::left << "" << "\t[2] Add New User.\n";
        std::cout << std::setw(37) << std::left << "" << "\t[3] Delete User.\n";
        std::cout << std::setw(37) << std::left << "" << "\t[4] Update User.\n";
        std::cout << std::setw(37) << std::left << "" << "\t[5] Find User.\n";
        std::cout << std::setw(37) << std::left << "" << "\t[6] Main Menu.\n";
        std::cout << std::setw(37) << std::left << "" << "===========================================\n";
        _PerformManageUsersMenuOptions((enManageUsersMenuOptions)_ReadManageUsersMenuOption());
	}
};

