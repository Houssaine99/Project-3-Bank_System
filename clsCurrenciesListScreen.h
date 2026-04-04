#pragma once

#include <iostream>
#include <string>
#include <iomanip>
#include <vector>

#include "clsCurrency.h"
#include "clsScreen.h"

class clsCurrenciesListScreen : protected clsScreen
{
private:

	static void _PrintCurrencyRecordLine(clsCurrency& Currency)
	{
		std::cout << std::left << std::setw(15) << "" << "| " << std::left << std::setw(30) << Currency.Country();
		std::cout << "| " << std::left << std::setw(6) << Currency.CurrencyCode();
		std::cout << "| " << std::left << std::setw(30) << Currency.CurrencyName();
		std::cout << "| " << std::left << std::setw(15) << Currency.Rate() << std::left << std::setw(1) << "|" << std::endl;
	}

public:

	static void ShowCurrenciesListScreen()
	{
		std::vector <clsCurrency> vCurrencies = clsCurrency::GetCurrenciesList();
		std::string Title = "\tCurrencies List Screen";
		std::string SubTitle = "\t  (" + std::to_string(vCurrencies.size()) + ") Currencies";

		_DrawScreenHeader(Title, SubTitle);

		std::cout << std::left << std::setw(15) << "" << std::string(90, '-') << std::endl;
		std::cout << std::left << std::setw(15) << "" << "| " << std::left << std::setw(30) << "Country";
		std::cout << "| " << std::left << std::setw(6) << "Code";
		std::cout << "| " << std::left << std::setw(30) << "Name";
		std::cout << "| " << std::left << std::setw(15) << "Rate/(1$)" << std::left << std::setw(1) << "|" << std::endl;
		std::cout << std::left << std::setw(15) << "" << std::string(90, '-') << std::endl;

		for (clsCurrency& Currency : vCurrencies)
		{
			_PrintCurrencyRecordLine(Currency);
		}

		std::cout << std::left << std::setw(15) << "" << std::string(90, '-') << std::endl;
	}
};

