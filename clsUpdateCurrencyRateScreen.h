#pragma once

#include <iostream>

#include "clsScreen.h"
#include "clsCurrency.h"
#include "clsInputValidate.h"

class clsUpdateCurrencyRateScreen : protected clsScreen
{
private:

	static void _PrintCurrencyCard(clsCurrency& Currency)
	{
		std::cout << "\nCurrency Card:";
		std::cout << "\n___________________";
		std::cout << "\nCountry : " << Currency.Country();
		std::cout << "\nCode    : " << Currency.CurrencyCode();
		std::cout << "\nName    : " << Currency.CurrencyName();
		std::cout << "\nRate(1$): " << Currency.Rate();
		std::cout << "\n___________________\n";
	}

	static float _ReadNewRate()
	{
		float Rate = 0;
		std::cout << "\nPlease Enter New Rate? ";
		Rate = clsInputValidate::ReadFltNumber();

		return Rate;
	}

public:

	static void ShowUpdateCurrencyRateScreen()
	{
		_DrawScreenHeader("  Update Currency Rate Screen");

		std::string CurrencyCode;
		std::cout << "\nPlease Enter Currency Code? ";
		CurrencyCode = clsInputValidate::ReadString();

		while (!clsCurrency::IsCurrencyExist(CurrencyCode))
		{
			std::cout << "\nCurrency Was Not Found! Try Another Currency Code? ";
			CurrencyCode = clsInputValidate::ReadString();
		}

		clsCurrency Currency = clsCurrency::FindByCurrencyCode(CurrencyCode);
		_PrintCurrencyCard(Currency);

		char Answer = 'n';
		std::cout << "\nAre you sure you want to update this currency rate (y/n)? ";
		std::cin >> Answer;

		if (toupper(Answer) == 'Y')
		{
			std::cout << "\nUpdate Currency Rate:";
			std::cout << "\n--------------------\n";

			Currency.UpdateRate(_ReadNewRate());
			std::cout << "\nCurrency Rate Was Updated Successfully :-)\n";
			_PrintCurrencyCard(Currency);
		}
		else
			std::cout << "\nOperation Was Cancelled!\n";
	}
};

