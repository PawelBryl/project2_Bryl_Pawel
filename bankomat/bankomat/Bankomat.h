#pragma once
#include "Bank.h"
enum BankomatCommands
{
	bal = 1, wd = 2, dep = 3, pc = 4, gcb = 5, cb_SIZE = 5
};

enum class my_enum {  };

class Bankomat
{

public:
	Bankomat(std::shared_ptr<Bank> const& bank, std::vector<PaymentSystem>&& systems);
	~Bankomat();
	void printCommands();
	void playerAction(int& location);
	void changePIN();
	void deposit();
	void withdraw();
	bool checkCardSystem(Card* c);
	const std::shared_ptr<Bank>& GetBank() const {return mBank;}
	bool CardInserted() const { return isCardInserted; }
	Card* CurrCard() const { return mCardInserted; }
private:
	bool isCardInserted;
	Card* mCardInserted;
	std::shared_ptr<Bank> mBank;
	std::vector<PaymentSystem> mAcceptedSystems;
};

