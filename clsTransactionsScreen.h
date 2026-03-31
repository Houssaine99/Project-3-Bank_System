#pragma once

#include <iostream>
#include <string>
#include <iomanip>

#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsDepositScreen.h"
#include "clsWithdrawScreen.h"
#include "clsTotalBalancesScreen.h"
#include "clsTransferScreen.h"
#include "clsTransferLogScreen.h"

class clsTransactionsScreen : protected clsScreen
{
private:

	enum enTransactionsMenuOptions { eDposit = 1, eWithdraw = 2, eTotalBalances = 3, eTransfer = 4, eTransferLog = 5, eShowMainMenu = 6};

	static short _ReadTransactionMenuOption()
	{
		short Choice;
		std::cout << std::left << std::setw(37) << "" << "Choose What Do You Want To Do [1 to 6]? ";
		Choice = clsInputValidate::ReadIntNumberBetween(1, 6, "Enter Number Between 1 and 6? ");
		
		return Choice;
	}

	static void _ShowDepositScreen()
	{
		clsDepositScreen::ShowDepositScreen();
	}

	static void _ShowWithdrawScreen()
	{
		clsWithdrawScreen::ShowWithdrawScreen();
	}

	static void _ShowTotalBalances()
	{
		clsTotalBalancesScreen::ShowTotalBalancesScreen();
	}

	static void _ShowTransferScreen()
	{
		clsTransferScreen::ShowTransferScreen();
	}

	static void _ShowTransferLogScreen()
	{
		clsTransferLogScreen::ShowTransferLogScreen();
	}

	static void _GoBackToTransactionMenu()
	{
		std::cout << "\n\nPress any key to go back to Transactions Menu...";
		system("pause>0");
		ShowTransactionsMenu();
	}

	static void _PerformTranactionsMenuOptions(enTransactionsMenuOptions TransactionMenuOption)
	{
		switch (TransactionMenuOption)
		{
		case enTransactionsMenuOptions::eDposit:
			system("cls");
			_ShowDepositScreen();
			_GoBackToTransactionMenu();
			break;

		case enTransactionsMenuOptions::eWithdraw:
			system("cls");
			_ShowWithdrawScreen();
			_GoBackToTransactionMenu();
			break;

		case enTransactionsMenuOptions::eTotalBalances:
			system("cls");
			_ShowTotalBalances();
			_GoBackToTransactionMenu();
			break;

		case enTransactionsMenuOptions::eTransfer:
			system("cls");
			_ShowTransferScreen();
			_GoBackToTransactionMenu();
			break;

		case enTransactionsMenuOptions::eTransferLog:
			system("cls");
			_ShowTransferLogScreen();
			_GoBackToTransactionMenu();
			break;

		case enTransactionsMenuOptions::eShowMainMenu:
		{

		}
		
		}
	}

public:

	static void ShowTransactionsMenu()
	{
		if (!_CheckAccessRights(clsUser::enPermissions::pTransactions))
			return;

		system("cls");
		_DrawScreenHeader("\t  Tranaction Screen");

		std::cout << std::setw(37) << std::left << "" << "===========================================\n";
		std::cout << std::setw(37) << std::right << "" << std::string(2, '\t') << "  Tranactions Menu\n";
		std::cout << std::setw(37) << std::left << "" << "===========================================\n";
		std::cout << std::setw(37) << std::left << "" << "\t[1] Deposit.\n";
		std::cout << std::setw(37) << std::left << "" << "\t[2] Withdraw.\n";
		std::cout << std::setw(37) << std::left << "" << "\t[3] Total Balances.\n";
		std::cout << std::setw(37) << std::left << "" << "\t[4] Transfer.\n";
		std::cout << std::setw(37) << std::left << "" << "\t[5] Transfer Log.\n";
		std::cout << std::setw(37) << std::left << "" << "\t[6] Main Menu.\n";
		std::cout << std::setw(37) << std::left << "" << "===========================================\n";
		_PerformTranactionsMenuOptions((enTransactionsMenuOptions)_ReadTransactionMenuOption());
	}
};

