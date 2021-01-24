#include "Bankomat.h"
#include <iostream>

Bankomat::Bankomat(std::shared_ptr<Bank> const& bank, std::vector<PaymentSystem>&& systems)
{
	mAcceptedSystems = systems;
	isCardInserted = false;
	mBank = bank;
	mCardInserted = nullptr;
}


void Bankomat::printCommands()
{
	std::cout << "Bankomat commands:\n";
	for (size_t i = 1; i <= BankomatCommands::cb_SIZE; i++)
	{
		switch (i)
		{
		case BankomatCommands::wd:
		{
			std::cout << "2. Withdraw\n";
			break;
		}
		case BankomatCommands::dep:
		{
			std::cout << "3. Deposit\n";
			break;
		}
		case BankomatCommands::bal:
		{
			std::cout << "1. Card balance\n";
			break;
		}
		case BankomatCommands::pc:
		{
			std::cout << "4. Change PIN\n";
			break;
		}
		case BankomatCommands::gcb:
		{
			std::cout << "5. Return card\n";
			break;
		}
		default:
		{
			std::cout << "Unknown command\n";
			break;
		}
		}
	}
}

Bankomat::~Bankomat()
{
	delete mCardInserted;
}


void Bankomat::deposit()
{
	std::cout << "Enter deposit amount:";
	double amount;
	while (!(std::cin >> amount) || amount < 0)
	{
		std::cout << "Bad input - try again: ";
		std::cin.clear();
		std::cin.ignore(INT_MAX, '\n'); 
	}
	std::cout << "Amount " << amount << " was added to your account"<< std::endl;
	double newBalance = mCardInserted->Balance() + amount;
	mCardInserted->SetBalance(newBalance);
}

void Bankomat::withdraw()
{
	double wdraw = 0;
	std::cout << "Enter withdraw amount: ";
	
	while (!(std::cin >> wdraw) || wdraw <= 0)
	{
		std::cout << "Bad input - try again: ";
		std::cin.clear();
		std::cin.ignore(INT_MAX, '\n');
	}
	double balance = mCardInserted->Balance();
	if (balance >= wdraw) {
		mCardInserted->SetBalance(balance - wdraw);
		std::cout << "Your updated Checkings balance is: " << balance - wdraw << std::endl;
	}
	else {
		std::cout << "Not able to withdraw " << wdraw << " from card." << std::endl;
		std::cout << "Not enough funds..." << std::endl;
	}
}


void Bankomat::playerAction(int& location)
{
	if (!isCardInserted)
	{

		std::vector<std::pair<std::string, std::string>> cardsStrings = mBank->GetUserCards(mBank->CurrUser());
		if (cardsStrings.empty()) std::cout << "Sorry, you don't have cards, go bank\n";
		else
		{
			int i = 0;
			std::cout << "Which card do you want to insert?\n";
			for (auto element : cardsStrings)
			{
				std::cout << i + 1 << ". "  << element.first  << std::endl;
				++i;
			}
			std::cout << i + 1 << ". " << "Leave bankomat" << std::endl;
			++i;
			int choose;
			std::cin >> choose;
			if (choose < 1 || choose > cardsStrings.size() + 1)
			{
				std::cout << "Wrong command\n";
			}
			else
			{
				if(choose == (cardsStrings.size() + 1))
				{
					location = 0;
					std::cout << "Leaving bankomat..." << std::endl;
					return;
				}
				
				mCardInserted = mBank->CurrUser()->CardByNumber(cardsStrings[choose - 1].first);
				isCardInserted = true;

				const bool isAcceptble = checkCardSystem(mCardInserted);
				if(!isAcceptble)
				{
					std::cout << "Bankomat doesn't accept cards with these payment systems" << std::endl;
					isCardInserted = false;
					mCardInserted = nullptr;
					
				}
				else
				{
					std::cout << "Please input card's PIN: ";
					std::string pin;
					while (!(std::cin >> pin) || pin != mCardInserted->PIN())
					{
						std::cout << "Wrong PIN: ";
						std::cin.clear();
						std::cin.ignore(INT_MAX, '\n');
					}
				}
			}
		}

	}
	else
	{
		int mCode;
		std::cout << "Input a command code (1-5)\n";
		std::cin >> mCode;
		switch (mCode)
		{
		case BankomatCommands::wd:
		{
			withdraw();
			break;
		}
		case BankomatCommands::dep:
		{
			deposit();
			break;
		}
		case BankomatCommands::bal:
		{
			std::cout << "There are " << mCardInserted->Balance() << " on this card\n";
			break;
		}
		case BankomatCommands::pc:
		{
			changePIN();
			break;
		}
		case BankomatCommands::gcb:
		{
			mCardInserted = nullptr;
			isCardInserted = false;
			break;
		}
		}
	}
}

void Bankomat::changePIN()
{
	Card* card = CurrCard();
	std::string newPin;


	while (true) 
	{
		std::cout << "Enter new PIN code:";
		std::cin >> newPin;

		if (Helper::isNumber(newPin))
		{
			if (newPin.size() != 4) { std::cout << "PIN must consist of 4 numbers\n"; }
			else
			{
				card->SetPin(std::move(newPin));
				std::cout << "Pin was changed!!!\n";
				break;
			}
		}                            
		else
		{
			std::cout << "Not an integer.\n";
			std::cin.clear();
			std::cin.ignore(INT_MAX, '\n'); 
		}
	}
}

bool Bankomat::checkCardSystem(Card* c)
{
	for (PaymentSystem element : c->PaySystems())
	{
		auto it = std::find(mAcceptedSystems.begin(), mAcceptedSystems.end(), element);
		if (it != mAcceptedSystems.end()) return true;
	}
	return false;
}
