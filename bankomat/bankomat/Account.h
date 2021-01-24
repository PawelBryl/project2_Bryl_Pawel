#pragma once
#include <memory>
#include <string>
#include "Card.h"

class UserInfo
{
public:
	UserInfo(std::string fname, std::string sName, std::string passport, std::string city, std::string email, std::string date)
		: mFirstName(fname), mSecondName(sName), mPassportNumber(passport), mCityName(city), mEmail(email), mDate(date) {}
	virtual ~UserInfo() = default;
	std::string FirstName() const { return mFirstName; }
	std::string SecondName() const { return mSecondName; }
	std::string PassportNumber() const { return mPassportNumber; }
	std::string City() const { return mCityName; }
	std::string Email() const { return mEmail; }
	std::string Date() const { return mDate; }
protected:
	std::string mFirstName;
	std::string mSecondName;
	std::string mPassportNumber;
	std::string mCityName;
	std::string mEmail;
	std::string mDate;
};

class Account : public UserInfo
{
public:
	Account(unsigned int id, std::string fname, std::string sName, std::string passport, std::string city, std::string email, std::string date);
	~Account();
	void addCard(std::string number, std::string owner, std::string expiration, std::string cvv, std::string pin, std::vector<PaymentSystem>&& paySystems);
	void addCard(Card* c);
	Card* CardByNumber(std::string number);
	long long Balance() const { return mBalance; }
	unsigned int Id() const { return  mId; }
	std::vector<Card*> Cards() const { return mCards; }
private:
	unsigned int mId;
	long long mBalance;
	std::vector<Card*> mCards;
};
