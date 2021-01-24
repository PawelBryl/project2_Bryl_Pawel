#include "Bank.h"
#include <iostream>
#include <fstream>
#include <ctime>
#include <regex>

#include "Helper.h"

Card* Bank::GenerateCard(std::string owner)
{
	srand(time(0));
	unsigned int number1 = 1000 + (rand() % static_cast<int>(9999 - 1000 + 1));
	unsigned int number2 = 1000 + (rand() % static_cast<int>(9999 - 1000 + 1));
	unsigned int number3 = 1000 + (rand() % static_cast<int>(9999 - 1000 + 1));
	unsigned int number4 = 1000 + (rand() % static_cast<int>(9999 - 1000 + 1));

	struct tm local_time;
	time_t now = time(0);
	localtime_s(&local_time, &now);
	
	unsigned int year = 1900 + local_time.tm_year;
	unsigned int month = 1 + local_time.tm_mon;

	unsigned int cvv = 100 + (rand() % static_cast<int>(999 - 100 + 1));
	unsigned int pin = 1000 + (rand() % static_cast<int>(9999 - 1000 + 1));

	std::vector<PaymentSystem> ps;
	Helper::GenerateSystems(ps);
	
	std::string exp = std::to_string(month) + '/' + std::to_string(year + 10);
	std::string number = std::to_string(number1) + " " + std::to_string(number2) + " " + std::to_string(number3) + " " + std::to_string(number4);

	return new Card(number, owner, exp, std::to_string(cvv), std::to_string(pin), std::move(ps));
}

void Bank::CreateAccount()
{
	std::string fName, sName, city, email, dBirth, passport;
	std::cout << "CREATING NEW ACCOUNT:\n";
	std::cout << "Please input your first name:\n";
	while (!(std::cin >> fName) || !regex_match(fName, std::regex("^[a-zA-Z]+(([',. -][a-zA-Z ])?[a-zA-Z]*)*$")))
	{
		std::cout << "Sorry, invalid first name\n";
		std::cout << "Input again:";
		std::cin.clear();
		std::cin.ignore(INT_MAX, '\n');
	}
	std::cout << "Please input your second name:\n";
	while (!(std::cin >> sName) || !regex_match(sName, std::regex("^[a-zA-Z]+(([',. -][a-zA-Z ])?[a-zA-Z]*)*$")))
	{
		std::cout << "Sorry, invalid second name\n";
		std::cout << "Input again:";
		std::cin.clear();
		std::cin.ignore(INT_MAX, '\n');
	}
	std::cout << "Please input your passport number:\n";
	while (!(std::cin >> passport) || !regex_match(passport, std::regex("^(?!^0+$)[a-zA-Z0-9]{3,20}$")))
	{
		std::cout << "Sorry, invalid passport number\n";
		std::cout << "Input again:";
		std::cin.clear();
		std::cin.ignore(INT_MAX, '\n');
	}

	std::cout << "Please input your city:\n";
	while (!(std::cin >> city) || !regex_match(city, std::regex("^[a-zA-Z]+(?:[\s-] [a-zA-Z]+)*$")))
	{
		std::cout << "Sorry, invalid city\n";
		std::cout << "Input again:";
		std::cin.clear();
		std::cin.ignore(INT_MAX, '\n');
	}

	std::cout << "Please input your email:\n";
	while (!(std::cin >> email) || !regex_match(email, std::regex("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+")))
	{
		std::cout << "Sorry, invalid email\n";
		std::cout << "Input again:";
		std::cin.clear();
		std::cin.ignore(INT_MAX, '\n');
	}
	std::cout << "Please input your date of birth (mm/dd/yyyy):\n";
	while (!(std::cin >> dBirth) || !regex_match(dBirth, std::regex("^(1[0-2]|0[1-9])/(3[01]|[12][0-9]|0[1-9])/[0-9]{4}$")))
	{
		std::cout << "Sorry, invalid date\n";
		std::cout << "Input again:";
		std::cin.clear();
		std::cin.ignore(INT_MAX, '\n');
	}

	if (!mAccounts.empty())
	{
		int pos = -1;
		for (auto it = mAccounts.begin(); it != mAccounts.end(); ++it)
		{
			if ((*it)->PassportNumber() == passport)
			{
				std::cout << "Sorry, but you already have account\n";
				return;
			}
			else pos = it - mAccounts.begin();
		}
	}
	Account* acc = new Account(mAccountNumber, fName, sName, passport, city, email, dBirth);
	mAccounts.emplace_back(acc);

	mCurrUser = acc;
	std::cout << "You're registered successfully\n";

	auto it = std::find(mAccounts.begin(), mAccounts.end(), acc);
	if (it != mAccounts.end())
	{
		Card* c = GenerateCard(mAccounts.at(it - mAccounts.begin())->FirstName() + mAccounts.at(it - mAccounts.begin())->SecondName());
		mAccounts.at(it - mAccounts.begin())->addCard(c);
		c->PrintInfo();
	}
}

Bank::~Bank()
{
	for (auto* element : mAccounts) delete element;
	delete mCurrUser;
}

void Bank::printCommands()
{
	std::cout << "Bank commands:\n";
	for (size_t i = 1; i < BankCommands::SIZE; i++)
	{
		switch (i)
		{
		case BankCommands::ca:
		{
			std::cout << "1. Create Account\n";
			break;
		}
		case BankCommands::gc:
		{
			std::cout << "2. Get new card\n";
			break;
		}
		case BankCommands::ex:
		{
			std::cout << "3. Exit\n";
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

void Bank::AddNewCard(Account* acc)
{
	int pos = GetAccountPos(acc);
	std::string owner;
	if (!pos)
	{
		unsigned int numberOfCards = mAccounts.at(pos)->Cards().size();
		if (numberOfCards == 3)
		{
			std::cout << "Bank don't allow to have more than 3 cards\n";
		}
		else
		{
			owner = mAccounts.at(pos)->FirstName() + mAccounts.at(pos)->SecondName();
			Card* c = GenerateCard(owner);
			mAccounts.at(pos)->addCard(c);
			c->PrintInfo();
			std::cout << "New card was added!\n";
		}
	}
	else
	{
		std::cout << "Sorry, but you don't have account in a bank\n";
	}
}

int Bank::GetAccountPos(Account* acc)
{
	if (mAccounts.empty()) return -1;
	auto it = std::find(mAccounts.begin(), mAccounts.end(), acc);
	if (it != mAccounts.end()) return it - mAccounts.begin();
	else return -1;
}

void Bank::playerAction(int& location)
{
	int mCode;
	std::cout << "Input a command code (1-3)\n";
	std::cin >> mCode;
	switch (mCode)
	{
	case BankCommands::ca:
	{
		if (mCurrUser == nullptr) CreateAccount();
		else std::cout << "You are already registered\n";
		break;
	}
	case BankCommands::gc:
	{
		if (mCurrUser != nullptr) AddNewCard(mCurrUser);
		else std::cout << "Create account first\n";
		break;
	}
	case BankCommands::ex:
	{
		location--;
		break;
	}
	}
	
}

std::vector<std::pair<std::string, std::string>> Bank::GetUserCards(Account* acc)
{
	std::vector<std::pair<std::string, std::string>> cards;
	int pos = GetAccountPos(acc);
	if(pos > -1)
	{
		for (Card* element : acc->Cards())
		{
			cards.emplace_back(std::make_pair<std::string, std::string>(element->Number(),element->PIN()));
		}
		return cards;
	}
	else
	{
		std::cout << "You don't have cards, go bank and create account\n";
		return std::vector<std::pair<std::string, std::string>>();
	}
}

