#pragma once

#include <iostream>
#include <string>


class clsScreen
{
protected:

	static void _DrawScreenHeader(std::string Title, std::string SubTitle = "")
	{
        std::cout << std::string(5, '\t') << "______________________________________\n\n";
        std::cout << std::string(6, '\t') <<  std::string(5, ' ') << Title;

        if (SubTitle != "")
        {
            std::cout << "\n" << std::string(6, '\t') << std::string(5, ' ') << SubTitle;
        }

        std::cout << "\n" << std::string(5, '\t') << "______________________________________\n\n";
    }

};

