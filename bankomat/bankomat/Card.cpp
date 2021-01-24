#include "Card.h"
#include <iostream>

Card::Card(std::string number, std::string owner, std::string expiration, std::string cvv, std::string pin, std::vector<PaymentSystem>&& paySystems)
{
	mNumber = number;
	mOwnerName = owner;
	mExpDate = expiration;
	mCVV = cvv;
	mPIN = pin;
	mPaySystems = paySystems;
	mBalance = 0;
}

void Card::PrintInfo()
{
	std::cout << "\n\nNow you have card:\n";
	std::cout << "Number: " << mNumber << std::endl;
	std::cout << "Expiration date: " << mExpDate << std::endl;
	std::cout << "Owner name: " << mOwnerName << std::endl;
	std::cout << "PIN: " << mPIN << std::endl;
	std::cout << "CVV: " << mCVV << std::endl;

	std::string s;
	for (auto element : mPaySystems)
	{
		s += ToString(element) + ",";
	}
	s.pop_back();
	std::cout << "Pay Systems:" << s << std::endl;
	std::cout << "\n\n";
}
