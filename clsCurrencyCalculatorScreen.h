#pragma once

#include <iostream>

#include "clsScreen.h"
#include "clsCurrency.h"
#include "clsInputValidate.h"
 
class clsCurrencyCalculatorScreen : protected clsScreen
{
private:

	static void _PrintCurrencyCard(clsCurrency& Currency, std::string Title)
	{
		std::cout << "\n" << Title;
		std::cout << "\n___________________";
		std::cout << "\nCountry : " << Currency.Country();
		std::cout << "\nCode    : " << Currency.CurrencyCode();
		std::cout << "\nName    : " << Currency.CurrencyName();
		std::cout << "\nRate(1$): " << Currency.Rate();
		std::cout << "\n___________________\n\n";
	}

	static clsCurrency _GetCurrency(std::string Message)
	{
		std::string CurrencyCode;
		std::cout << "\n" << Message;
		CurrencyCode = clsInputValidate::ReadString();

		while (!clsCurrency::IsCurrencyExist(CurrencyCode))
		{
			std::cout << "\nCurrency Was Not Found! Try Another Currency Code? ";
			CurrencyCode = clsInputValidate::ReadString();
		}

		clsCurrency Currency = clsCurrency::FindByCurrencyCode(CurrencyCode);

		return Currency;
	}

	static float _ReadExchangeAmount()
	{
		float ExchangeAmount = 0;
		std::cout << "\nPlease Enter Exchange Amount? ";
		ExchangeAmount = clsInputValidate::ReadFltNumber();

		return ExchangeAmount;
	}

	static void _PrintCalculationResult(float Amount, clsCurrency& CurrencyFrom, clsCurrency& CurrencyTo)
	{
		_PrintCurrencyCard(CurrencyFrom, "Convert From:");

		float AmountInUSD = CurrencyFrom.ConvertToUSD(Amount);
		std::cout << Amount << " " << CurrencyFrom.CurrencyCode() << " = " << AmountInUSD << " USD\n";
		
		if (CurrencyTo.CurrencyCode() == "USD")
			return;

		_PrintCurrencyCard(CurrencyTo, "Converting From USD to:");

		float AmountInCurrency2 = CurrencyFrom.ConvertToOtherCurrency(Amount, CurrencyTo);
		std::cout << Amount << " " << CurrencyFrom.CurrencyCode() << " = " << AmountInCurrency2
			<< " " << CurrencyTo.CurrencyCode() << std::endl;
	}

public:

	static void ShowCurrencyCalculatorScreen()
	{
		char Continue = 'y';

		while (toupper(Continue) == 'Y')
		{
			system("cls");
			_DrawScreenHeader("   Currency Calculator Screen");

			clsCurrency CurrencyFrom = _GetCurrency("Please Enter First Currency? ");
			clsCurrency CurrencyTo = _GetCurrency("Please Enter Second Currency? ");
			float ExchangeAmount = _ReadExchangeAmount();

			_PrintCalculationResult(ExchangeAmount, CurrencyFrom, CurrencyTo);

			std::cout << "\nDo you want to perform another calculation (y/n)? ";
			std::cin >> Continue;
		}
	}
};

