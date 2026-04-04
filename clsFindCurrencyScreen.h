#pragma once

#include <iostream>
#include <string>

#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsCurrenciesListScreen.h"

class clsFindCurrencyScreen : protected clsScreen
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

	static void _ShowResult(clsCurrency& Currency)
	{
		if (Currency.IsEmpty())
			std::cout << "\nCurrency is not found :-(\n";
		else
		{
			std::cout << "\nCurrency is Found :-)\n";
			_PrintCurrencyCard(Currency);
		}
	}

public:

	static void ShowFindCurrencyScreen()
	{
		_DrawScreenHeader("\tFind Currency Screen");

		short Answer = 0;
		std::cout << "\nFind By: [1] Code or [2] Country? ";
		Answer = clsInputValidate::ReadIntNumberBetween(1, 2, "Invalid Number! Enter a Number Between (1 and 2)? ");

		if (Answer == 1)
		{
			std::string Code;
			std::cout << "\nPlease Enter Currency Code? ";
			Code = clsInputValidate::ReadString();
			clsCurrency Currency = clsCurrency::FindByCurrencyCode(Code);
			_ShowResult(Currency);
		}
		else
		{
			std::string Country;
			std::cout << "\nPlease Enter Country? ";
			Country = clsInputValidate::ReadString();
			clsCurrency Currency = clsCurrency::FindByCountry(Country);
			_ShowResult(Currency);
		}
	}
};

