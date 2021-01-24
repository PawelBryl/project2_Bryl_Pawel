#pragma once
#include <string>
#include "Account.h"

enum BankCommands { ca =1, gc, ex, SIZE };

class Bank
{
public:
	Bank() : mAccountNumber(0),mCurrUser(nullptr) {}
	void CreateAccount();
	Card* GenerateCard(std::string owner);
	void AddNewCard(Account* acc);
	int GetAccountPos(Account* acc);
	void printCommands();
	void playerAction(int& location);
	std::vector<std::pair<std::string, std::string>> GetUserCards(Account* acc);
	Account* CurrUser() const { return  mCurrUser; }
	~Bank();
private:
	unsigned int mAccountNumber;
	std::vector<Account*> mAccounts;
	Account* mCurrUser;
};

