// logic for getting user input

#include "getUserChoice.h" // contains io, and numriclimits
#include "userChoiceEnum.h" // contains enum for switch

UserChoice getUserChoice()
{
	// handle and sanitize user input
	int userChoice{};
	int ValidChoice = false;

	while (ValidChoice == false)
	{
		std::cin >> userChoice;
		// make use choice is not a char or string
		if (!std::cin)
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cerr << "ERROR: Invalid option try again\n:";
		}
		// make sure choice is not outside bounds
		if (userChoice < 0 || userChoice > 3)
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cerr << "ERROR: Invalid option try again\n:";
		}
		else
		{
			ValidChoice = true;
		}
	}
	// both checks passed

	// return enum so main can use in a switch for options
	switch (static_cast<UserChoice>(userChoice))
	{
	case UserChoice::PID:
	{
		return UserChoice::PID;
		break;
	}
	case UserChoice::NAME:
	{
		return UserChoice::NAME;
		break;
	}
	case UserChoice::LIST:
	{
		return UserChoice::LIST;
		break;
	}
	case UserChoice::DISCORD:
	{
		return UserChoice::DISCORD;
		break;
	}
	default: // should never happen
	{
		std::cerr << "ERROR: defualt case hit in getUserChoice.cpp\n";
		return UserChoice::INVALID;
	}
	}

}

// is this very messy and bloated can be reduced a ton will redo at some point gpt roasted me about this one