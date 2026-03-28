#pragma once

#include <iostream>
#include <string>

#include "clsUser.h"
#include "clsDate.h"
#include "Global.h"


class clsScreen
{
protected:

	static void _DrawScreenHeader(std::string Title, std::string SubTitle = "")
	{
        std::cout << std::string(5, '\t') << "______________________________________\n\n";
        std::cout << std::string(5, '\t') <<  std::string(2, ' ') << Title;

        if (SubTitle != "")
        {
            std::cout << "\n" << std::string(5, '\t') << std::string(2, ' ') << SubTitle;
        }

        std::cout << "\n" << std::string(5, '\t') << "______________________________________\n\n";
    
        std::cout << std::string(5, '\t') << "User: " << CurrentUser.UserName << std::endl;
        std::cout << std::string(5, '\t') << "Date:" << clsDate::DateToString(clsDate()) << "\n\n";
    }

    static bool _CheckAccessRights(clsUser::enPermissions Permissions)
    {
        if (!CurrentUser.CheckAccessPermissions(Permissions))
        {
            _DrawScreenHeader("Access Denied! Contact You Admin.");
            return false;
        }
        else
            return true;
    }

};

