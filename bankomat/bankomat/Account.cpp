#include "Account.h"

#include <memory>


Account::Account(unsigned id, std::string fname, std::string sName, std::string passport,std::string city, std::string email, std::string date)
: UserInfo(fname, sName, passport, city, email, date), mId(id), mBalance(0) {}

void Account::addCard(std::string number, std::string owner, std::string expiration, std::string cvv, std::string pin, std::vector<PaymentSystem>&& paySystems)
{
	mCards.emplace_back(new Card(number, owner, expiration, cvv, pin, std::move(paySystems)));
}

void Account::addCard(Card* c)
{
	mCards.emplace_back(c);
}

Card* Account::CardByNumber(std::string number)
{
	auto it = std::find_if(mCards.begin(), mCards.end(), [&number](Card* c) { return c->Number() == number;});
	if (it != mCards.end()) return mCards.at(it - mCards.begin());
	else return nullptr;
}


Account::~Account()
{
	for (auto* element : mCards) delete element;
}
