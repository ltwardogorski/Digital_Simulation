#pragma once
#include "blood_donation_point.h"

class provision_of_blood
{
	uint16_t t1_;
	uint64_t actual_id_blood_;

public:
	explicit provision_of_blood(uint16_t);
	~provision_of_blood() = default;


	void execute(queue_of_blood*, blood_donation_point*, uint64_t*, uint64_t, uint16_t);
}; // klasa reprezentuj¹ca przyjœcie krwi
