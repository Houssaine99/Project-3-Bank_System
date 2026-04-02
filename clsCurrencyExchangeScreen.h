#pragma once

#include <iostream>
#include <string>
#include <iomanip>

#include "clsScreen.h"
#include "clsCurrency.h"
#include "clsInputValidate.h"

class clsCurrencyExchangeScreen : protected clsScreen
{
private:

    enum enCurrencyExchangeMenuOptions { eListCurrency = 1, eFindCurrency = 2, eUpdateRate = 3, eCurrencyCalculator = 4,
        eMainMenu = 5};

    static short _ReadCurrencyExchangeMenuOption()
    {
        short Choice = 0;

        std::cout << std::setw(37) << std::left << "" << "Choose What Do You Want To Do [1 to 5]? ";
        Choice = clsInputValidate::ReadIntNumberBetween(1, 5, "Enter Number between 1 to 5 ?");

        return Choice;
    }

    static void _ShowListCurrencyScreen()
    {
        std::cout << "List Currency Scrren Will Be Here.\n";
    }

    static void _GoBackToCurrencyExchangeMenu()
    {
        std::cout << std::setw(37) << std::left << "" << "\n\tPress any key to go back to currency exchange menu...\n";

        system("pause>0");
        ShowCurrencyExchangeScreen();
    }

    static void _ShowFindCurrencyScreen()
    {
        std::cout << "Find Currency Scrren Will Be Here.\n";
    }

    static void _ShowUpdateRateScreen()
    {
        std::cout << "Update Rate Scrren Will Be Here.\n";

    }

    static void _ShowCurrencyCalculatorScreen()
    {
        std::cout << "Show Currency Calculator Scrren Will Be Here.\n";

    }

    static void _PerformCurrencyExchangeMenuOptions(enCurrencyExchangeMenuOptions Option)
    {
        switch (Option)
        {
        case enCurrencyExchangeMenuOptions::eListCurrency:
            system("cls");
            _ShowListCurrencyScreen();
            _GoBackToCurrencyExchangeMenu();
            break;

        case enCurrencyExchangeMenuOptions::eFindCurrency:
            system("cls");
            _ShowFindCurrencyScreen();
            _GoBackToCurrencyExchangeMenu();
            break;

        case enCurrencyExchangeMenuOptions::eUpdateRate:
            system("cls");
            _ShowUpdateRateScreen();
            _GoBackToCurrencyExchangeMenu();
            break;

        case enCurrencyExchangeMenuOptions::eCurrencyCalculator:
            system("cls");
            _ShowCurrencyCalculatorScreen();
            _GoBackToCurrencyExchangeMenu();
            break;

        case enCurrencyExchangeMenuOptions::eMainMenu:
        {}

        }
    }



public:

	static void ShowCurrencyExchangeScreen()
	{
        system("cls");
        _DrawScreenHeader("\tCurrency Exchange Screen");

        std::cout << std::setw(37) << std::left << "" << "===========================================\n";
        std::cout << std::setw(37) << std::right << "" << std::string(2, '\t') << "Currency Exchange Menu\n";
        std::cout << std::setw(37) << std::left << "" << "===========================================\n";
        std::cout << std::setw(37) << std::left << "" << "\t[1] List Currency.\n";
        std::cout << std::setw(37) << std::left << "" << "\t[2] Find Currency.\n";
        std::cout << std::setw(37) << std::left << "" << "\t[3] Update Rate.\n";
        std::cout << std::setw(37) << std::left << "" << "\t[4] Currency Calculator.\n";
        std::cout << std::setw(37) << std::left << "" << "\t[5] Main Menu.\n";
        std::cout << std::setw(37) << std::left << "" << "===========================================\n";
        _PerformCurrencyExchangeMenuOptions((enCurrencyExchangeMenuOptions)_ReadCurrencyExchangeMenuOption());
    }

};

