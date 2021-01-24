#pragma once
#include "Bank.h"
#include "Bankomat.h"

enum class Location { outside =0, bank, bankomat  };

class Gra
{
public:
	Gra();
	int execute();
	void printCommandsOutside();
	void playerActionOutside(int& location);
	std::vector<PaymentSystem> GetSystems();
private:
	bool mState;
	std::shared_ptr<Bank> mBank;
	std::shared_ptr<Bankomat> mBankomat;
	Location mLocation;
};

