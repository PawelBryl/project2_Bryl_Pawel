#include "Gra.h"
#include <iostream>

Gra::Gra()
{
	mState = true;
	mLocation = Location::outside;
	mBank = std::make_shared<Bank>();
	mBankomat = std::make_shared<Bankomat>(mBank, GetSystems());
}


int Gra::execute()
{
	int loc;
	while (mState)
	{
		switch (mLocation)
		{
		case Location::outside:
		{
			printCommandsOutside();
			loc = static_cast<int>(mLocation);
			playerActionOutside(loc);
			if (loc == -1) return 0;
			mLocation = static_cast<Location>(loc);
			break;
		}
		case Location::bank:
		{
			mBank->printCommands();
			loc = static_cast<int>(mLocation);
			mBank->playerAction(loc);
			mLocation = static_cast<Location>(loc);
			break;
		}
		case Location::bankomat:
		{
			if (mBank->CurrUser() == nullptr)
			{
				std::cout << "Sorry, you don't have account\n";
				mLocation = Location::outside;
				break;
			}
			if (mBankomat->CardInserted())mBankomat->printCommands();
			loc = static_cast<int>(mLocation);
			mBankomat->playerAction(loc);
			mLocation = static_cast<Location>(loc);
			break;
		}
		}
	}
}

void Gra::printCommandsOutside()
{
	std::cout << "Where are you going?\n";
	std::cout << "1. Bank\n";
	std::cout << "2. Bankomat\n";
	std::cout << "3. End Game\n";
}

void Gra::playerActionOutside(int& location)
{
	int mCode;
	std::cout << "Input a command code (1-3)\n";
	std::cin >> mCode;
	if(mCode == 1)
	{
		++location;
	}
	else if (mCode == 2)
	{
		location = 2;
	}
	else if (mCode == 3)
	{
		location = -1;
	}
	else
	{
		std::cout << "Unknown command\n";
	}
}

std::vector<PaymentSystem> Gra::GetSystems()
{
	int key = 1;
	std::vector<std::string> cardsTypes;
	std::vector<PaymentSystem> pBankomat;
	for (int i = 0; i < static_cast<int>(PaymentSystem::SIZE); ++i)
	{
		cardsTypes.emplace_back(ToString(static_cast<PaymentSystem>(i)));
	}
	std::cout << "Hello in game bankomat!!!!\n";
	std::cout << "Select which cards bankomat accepts:\n";
	while (key)
	{
		if (cardsTypes.empty()) break;
		for (int i = 0; i < cardsTypes.size(); i++)
		{
			std::cout << i + 1 << ". " << cardsTypes[i] << '\n';
		}
		std::cout << "0. End input types\n";
		while (!(std::cin >> key) || key < 0 || key > cardsTypes.size())
		{
			std::cout << "Wrong command\n";
			std::cout << "Input again:";
			std::cin.clear();
			std::cin.ignore(INT_MAX, '\n');
		}
		if (key == 0)
		{
			if (pBankomat.empty())
			{
				std::cout << "Bankomat can't be without payment system\n";
				key = 100;
			}
			else
			{
				break;
			}
		}
		else
		{
			pBankomat.emplace_back(StringToSystem(cardsTypes[key - 1]));
			cardsTypes.erase(cardsTypes.begin() + key - 1);
			if (cardsTypes.empty())
			{
				std::cout << "All systems were added to bankomat";
				break;
			}
		}
	}
	return pBankomat;
}
