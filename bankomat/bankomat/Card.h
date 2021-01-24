#pragma once
#include <string>
#include <vector>
#include "Helper.h"

enum class PaymentSystem
{
VISA,
China_UnionPay,
VISA_Electron,
Mastercard,
American_Express,
SIZE = 5,
Unknown = -1
};

inline std::string ToString(const PaymentSystem& v)
{
	switch (v)
	{
	case PaymentSystem::VISA:			  return "VISA";
	case PaymentSystem::China_UnionPay:   return "China UnionPay";
	case PaymentSystem::VISA_Electron:	  return "VISA Electron";
	case PaymentSystem::Mastercard:		  return "Mastercard";
	case PaymentSystem::American_Express: return "American Express";
	default: return "[Unknown PaymentSystem type]";
	}
}
inline PaymentSystem StringToSystem(const std::string& s)
{
	if(s == "VISA")	return PaymentSystem::VISA;
	if (s == "China UnionPay") return PaymentSystem::China_UnionPay;
	if (s =="VISA Electron")  return PaymentSystem::VISA_Electron;
	if (s == "Mastercard") return PaymentSystem::Mastercard;
	if (s == "American Express") return PaymentSystem::American_Express;
	else return PaymentSystem::Unknown;
	
}

class Card
{
public:
	Card(std::string number, std::string owner, std::string expiration, std::string cvv, std::string pin,std::vector<PaymentSystem>&& paySystems);
	void PrintInfo();
	void SetPin(std::string&& newPin) { mPIN = newPin; }
	void SetBalance (int&& newB) { mBalance = newB; }

	std::string Number() const { return  mNumber; }
	std::string Owner() const { return  mOwnerName; }
	std::string Expiration() const { return  mExpDate; }
	std::string CVV() const { return  mCVV; }
	std::string PIN() const { return  mPIN; }
	std::vector<PaymentSystem> PaySystems() const { return  mPaySystems; }
	double Balance() const { return  mBalance; }
	void SetBalance(double amount) { mBalance = amount; }
private:
	double mBalance;
	std::string mNumber;
	std::string mOwnerName;
	std::string mExpDate;
	std::string mCVV;
	std::string mPIN;
	std::vector<PaymentSystem> mPaySystems;
};

