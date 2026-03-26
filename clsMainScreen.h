#pragma once

#include <iostream>
#include <string>
#include <iomanip>

#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsClientListScreen.h"
#include "clsAddNewClientscreen.h"
#include "clsDeleteClientScreen.h"
#include "clsUpdateClientScreen.h"
#include "clsFindClientScreen.h"
#include "clsTransactionsScreen.h"
#include "clsManageUsersScreen.h"
#include "Global.h"


class clsMainScreen : protected clsScreen
{
private:

    enum enMainMenuOptions { eListClients = 1, eAddNewClient = 2, eDeleteClient = 3,
                             eUpdateClient = 4, eFindClient = 5, eShowTransactionsMenu = 6,
                             eManageUsers = 7, eExit = 8 };

    static short _ReadMainMenuOption()
    {
        short Choice = 0;

        std::cout << std::setw(37) << std::left << "" << "Choose What Do You Want To Do [1 to 8]? ";
        Choice = clsInputValidate::ReadIntNumberBetween(1, 8, "Enter Number between 1 and 8? ");

        return Choice;
    }

    static  void _GoBackToMainMenu()
    {
        std::cout << std::setw(37) << std::left << "" << "\n\tPress any key to go back to Main Menu...\n";

        system("pause>0");
        ShowMainMenu();
    }

    static void _ShowAllClientsList()
    {
        clsClientListScreen::ShowClientsList();
    }

    static void _ShowAddNewClientScreen()
    {
        clsAddNewClientscreen::ShowAddNewClientScreen();
    }

    static void _ShowDeleteClientScreen()
    {
        clsDeleteClientScreen::ShowDeleteClientScreen();
    }

    static void _ShowUpdateClientScreen()
    {
        clsUpdateClientScreen::ShowUpdateClientScreen();
    }

    static void _ShowFindClientScreen()
    {
        clsFindClientScreen::ShowFindClientScreen();
    }

    static void _ShowTransactionMenu()
    {
        clsTransactionsScreen::ShowTransactionsMenu();
    }

    static void _ShowManageUsersMenu()
    {
        clsManageUsersScreen::ShowManageUsersMenu();
    }

    static void _Logout()
    {
        CurrentUser = clsUser::Find("", "");
    }

    static void _PerformMainMenuOptions(enMainMenuOptions Option)
    {
        switch (Option)
        {
        case enMainMenuOptions::eListClients:
            system("cls");
            _ShowAllClientsList();
            _GoBackToMainMenu();
            break;

        case enMainMenuOptions::eAddNewClient:
            system("cls");
            _ShowAddNewClientScreen();
            _GoBackToMainMenu();
            break;

        case enMainMenuOptions::eDeleteClient:
            system("cls");
            _ShowDeleteClientScreen();
            _GoBackToMainMenu();
            break;

        case enMainMenuOptions::eUpdateClient:
            system("cls");
            _ShowUpdateClientScreen();
            _GoBackToMainMenu();
            break;

        case enMainMenuOptions::eFindClient:
            system("cls");
            _ShowFindClientScreen();
            _GoBackToMainMenu();
            break;

        case enMainMenuOptions::eShowTransactionsMenu:
            system("cls");
            _ShowTransactionMenu();
            ShowMainMenu();
            break;

        case enMainMenuOptions::eManageUsers:
            system("cls");
            _ShowManageUsersMenu();
            ShowMainMenu();
            break;

        case enMainMenuOptions::eExit:
            system("cls");
            _Logout();
            break;
            
        }
    }

public:

	static void ShowMainMenu()
	{
		system("cls");
		_DrawScreenHeader("\t\tMain Screen");

        std::cout << std::setw(37) << std::left << "" << "===========================================\n";
        std::cout << std::setw(37) << std::right << "" << std::string(3, '\t') << "Main Menu\n";
        std::cout << std::setw(37) << std::left << "" << "===========================================\n";
        std::cout << std::setw(37) << std::left << "" << "\t[1] Show Client List.\n";
        std::cout << std::setw(37) << std::left << "" << "\t[2] Add New Client.\n";
        std::cout << std::setw(37) << std::left << "" << "\t[3] Delete Client.\n";
        std::cout << std::setw(37) << std::left << "" << "\t[4] Update Client Info.\n";
        std::cout << std::setw(37) << std::left << "" << "\t[5] Find Client.\n";
        std::cout << std::setw(37) << std::left << "" << "\t[6] Transactions.\n";
        std::cout << std::setw(37) << std::left << "" << "\t[7] Manage Users.\n";
        std::cout << std::setw(37) << std::left << "" << "\t[8] Logout.\n";
        std::cout << std::setw(37) << std::left << "" << "===========================================\n";
        _PerformMainMenuOptions((enMainMenuOptions)_ReadMainMenuOption());
	}

};

