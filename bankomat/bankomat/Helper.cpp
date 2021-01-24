#include "Helper.h"
void Helper::GenerateSystems(std::vector<PaymentSystem>& ps)
{
	unsigned int numberSystems = 1 + (rand() % static_cast<int>(static_cast<int>(PaymentSystem::SIZE) - 1 + 1));
	unsigned int count = 0;
	while (count < numberSystems)
	{
		PaymentSystem system = static_cast<PaymentSystem>(static_cast<int>(PaymentSystem::VISA) + (rand() % static_cast<int>(static_cast<int>(PaymentSystem::American_Express) - static_cast<int>(PaymentSystem::VISA) + 1)));
		auto it = std::find(ps.begin(), ps.end(), system);
		if (it != ps.end()) continue;
		else ps.push_back(system);
		count++;
	}
}

bool Helper::isNumber(std::string s)
{
	for (int i = 0; i < s.length(); i++)
		if (isdigit(s[i]) == false)
			return false;

	return true;
}