#pragma once

#include <algorithm>
#include "Card.h"

enum class PaymentSystem;


class Helper
{
public:
	static void GenerateSystems(std::vector<PaymentSystem>& ps);
	static bool isNumber(std::string s);
};
