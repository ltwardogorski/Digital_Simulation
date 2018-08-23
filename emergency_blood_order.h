#pragma once
#include "cstdint"

class queue_of_blood;
class time;

class emergency_blood_order
{
public:
	emergency_blood_order() = default;

	~emergency_blood_order() = default;

	static bool execute(uint64_t, bool, uint64_t, time*);
}; // klasa odpowiedzialna za awaryjne zamówienie krwi
