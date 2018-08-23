#pragma once
#include "blood_donation_point.h"

class queue_of_blood;
class time;

class blood_order
{
	queue_of_blood* priority_queue_blood_;
public:
	explicit blood_order(queue_of_blood*);

	~blood_order() = default;

	bool execute(uint64_t, bool, uint64_t, time*) const;
}; // klasa odpowiedzialna za zamówienie krwi
