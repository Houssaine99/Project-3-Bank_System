#pragma once

#include <iostream>
#include <iomanip>

#include "clsScreen.h"
#include "clsBankClient.h"

class clsTransferLogScreen : protected clsScreen
{
private:

	static void _PrintTransferLogRecord(clsBankClient::stTransferLogRecord& TransfeLogRecord)
	{
		std::cout << std::left << std::setw(8) << "" << "| " << std::left << std::setw(25) << TransfeLogRecord.DateTime;
		std::cout << "| " << std::left << std::setw(10) << TransfeLogRecord.SourceClientAccNumber;
		std::cout << "| " << std::left << std::setw(10) << TransfeLogRecord.DestinationClientAccNumber;
		std::cout << "| " << std::left << std::setw(10) << TransfeLogRecord.Amount;
		std::cout << "| " << std::left << std::setw(10) << TransfeLogRecord.SourceClientAccBalance;
		std::cout << "| " << std::left << std::setw(10) << TransfeLogRecord.DestinationClientAccBalance;
		std::cout << "| " << std::left << std::setw(10) << TransfeLogRecord.Username << std::left << std::setw(1) << "|" << std::endl;
	}

public:

	static void ShowTransferLogScreen()
	{
		std::vector <clsBankClient::stTransferLogRecord> vTransferLog = clsBankClient::GetTransferLogList();
		std::string Title = "\tTransfer Log List Screen";
		std::string SubTitle = "\t      (" + std::to_string(vTransferLog.size()) + ") Log(s)";

		_DrawScreenHeader(Title, SubTitle);

		std::cout << std::left << std::setw(8) << "" << std::string(100, '-') << std::endl;
		std::cout << std::left << std::setw(8) << "" << "| " << std::left << std::setw(25) << "Date/Time";
		std::cout << "| " << std::left << std::setw(10) << "s.Acct";
		std::cout << "| " << std::left << std::setw(10) << "d.Acct";
		std::cout << "| " << std::left << std::setw(10) << "Amount";
		std::cout << "| " << std::left << std::setw(10) << "s.Balance";
		std::cout << "| " << std::left << std::setw(10) << "d.balance";
		std::cout << "| " << std::left << std::setw(10) << "Username" << std::left << std::setw(1) << "|" << std::endl;
		std::cout << std::left << std::setw(8) << "" << std::string(100, '-') << std::endl;

		if (vTransferLog.size() == 0)
		{
			std::cout << std::left << std::setw(8) << "" << "| " << std::string(4, '\t') << "No Transfer Logs Available In the System!" << std::right << std::setw(27) << "|" << std::endl;
		}
		else
		{
			for (clsBankClient::stTransferLogRecord& Record : vTransferLog)
			{
				_PrintTransferLogRecord(Record);
			}
		}

		std::cout << std::left << std::setw(8) << "" << std::string(100, '-') << std::endl;
	}
};

