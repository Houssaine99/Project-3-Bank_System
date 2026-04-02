#pragma once

#include <iostream>
#include <string>
#include <cctype>
#include <vector>
#include <fstream>

#include "clsString.h"

class clsCurrency
{
private:

	enum enMode { eEmptyMode = 0, eUpdateMode = 1};

	enMode _Mode;
	std::string _Country;
	std::string _CurrencyCode;
	std::string _CurrencyName;
	float _Rate = 0;
	
	static std::string _ConvertCurrencyObjectToLine(clsCurrency& Currency , std::string Seperator = "#//#")
	{
		std::string RecordLine;

		RecordLine += Currency.Country() + Seperator;
		RecordLine += Currency.CurrencyCode() + Seperator;
		RecordLine += Currency.CurrencyName() + Seperator;
		RecordLine += std::to_string(Currency.Rate());

		return RecordLine;
	}

	static clsCurrency _ConvertLineToCurrencyObject(std::string Line, std::string Seperator = "#//#")
	{
		std::vector <std::string> vCurrencyRecord = clsString::Split(Line, Seperator);

		return clsCurrency(enMode::eUpdateMode, vCurrencyRecord.at(0), vCurrencyRecord.at(1), vCurrencyRecord.at(2),
			std::stof(vCurrencyRecord.at(3)));
	}

	static clsCurrency _GetEmptyCurrencyObject()
	{
		return clsCurrency(eEmptyMode, "", "", "", 0);
	}

	static std::vector <clsCurrency> _LoadCurrenciesDataFromFile()
	{
		std::vector <clsCurrency> vCurrencies;
		std::fstream File;
		File.open("Currencies.txt", std::ios::in);

		if (File.is_open())
		{
			std::string Line;
			while (std::getline(File, Line))
			{
				clsCurrency Currency = _ConvertLineToCurrencyObject(Line);
				vCurrencies.push_back(Currency);
			}
			File.close();
		}
		return vCurrencies;
	}

	static void _SaveCurrenciesDataToFile(std::vector <clsCurrency>& vCurrencies)
	{
		std::fstream File;
		File.open("Currencies.txt", std::ios::out);

		if (File.is_open())
		{
			std::string Line;
			for (clsCurrency& Currency : vCurrencies)
			{
				Line = _ConvertCurrencyObjectToLine(Currency);
				File << Line << std::endl;
			}
			File.close();
		}
	}

	void _Update()
	{
		std::vector <clsCurrency> vCurrencies = _LoadCurrenciesDataFromFile();
		
		for (clsCurrency& Currency : vCurrencies)
		{
			if (Currency.CurrencyCode() == _CurrencyCode)
			{
				Currency = *this;
				break;
			}
		}

		_SaveCurrenciesDataToFile(vCurrencies);
	}

public:

	clsCurrency(enMode Mode, std::string Country, std::string CurrencyCode, std::string CurrencyName, float Rate)
	{
		_Mode = Mode;
		_Country = Country;
		_CurrencyCode = CurrencyCode;
		_CurrencyName = CurrencyName;
		_Rate = Rate;
	}

	bool IsEmpty()
	{
		return (_Mode == eEmptyMode);
	}

	std::string Country()
	{
		return _Country;
	}

	std::string CurrencyCode()
	{
		return _CurrencyCode;
	}

	std::string CurrencyName()
	{
		return _CurrencyName;
	}

	void UpdateRate(float Rate)
	{
		_Rate = Rate;
		_Update();
	}

	float Rate()
	{
		return _Rate;
	}

	static clsCurrency FindByCountry(std::string Country)
	{
		Country = clsString::UpperAllString(Country);
		std::fstream File;
		File.open("Currencies.txt", std::ios::in);

		if (File.is_open())
		{
			std::string Line;
			while (std::getline(File, Line))
			{
				clsCurrency Currency = _ConvertLineToCurrencyObject(Line);
				if (clsString::UpperAllString(Currency.Country()) == Country)
				{
					File.close();
					return Currency;
				}
			}
			File.close();
		}

		return _GetEmptyCurrencyObject();
	}

	static clsCurrency FindByCurrencyCode(std::string CurrencyCode)
	{
		CurrencyCode = clsString::UpperAllString(CurrencyCode);
		std::fstream File;
		File.open("Currencies.txt", std::ios::in);

		if (File.is_open())
		{
			std::string Line;
			while (std::getline(File, Line))
			{
				clsCurrency Currency = _ConvertLineToCurrencyObject(Line);
				if (Currency.CurrencyCode() == CurrencyCode)
				{
					File.close();
					return Currency;
				}
			}
			File.close();
		}

		return _GetEmptyCurrencyObject();
	}

	static bool IsCurrencyExist(std::string CurrencyCode)
	{
		clsCurrency Currency = FindByCurrencyCode(CurrencyCode);
		return (!Currency.IsEmpty());
	}

	static std::vector <clsCurrency> GetCurrenciesList()
	{
		return _LoadCurrenciesDataFromFile();
	}

	
};

