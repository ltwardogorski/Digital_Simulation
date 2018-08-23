#pragma once
// ReSharper disable CppUnusedIncludeDirective
#include "blood_donation_point.h"
// ReSharper restore CppUnusedIncludeDirective

class destruction_of_blood
{
public:
	destruction_of_blood() = default;
	~destruction_of_blood() = default;

	static bool execute(queue_of_blood*, blood_donation_point*, uint64_t);
}; // klasa reprezentuj¹ca usuniêcie przeterminowanej krwi
