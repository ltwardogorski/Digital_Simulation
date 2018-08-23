#pragma once
#include "blood_donation_point.h"


class to_arise_donor : blood_donation_point
{
	uint16_t t2_;
	uint64_t actual_id_blood_;
	uint32_t actual_id_donor_;

public:
	to_arise_donor(uint32_t*, uint64_t*, uint16_t);
	~to_arise_donor() = default;

	void execute(queue_of_blood*, blood_donation_point*, uint64_t) const;
}; // klasa reprezentuj¹ca pojawienie siê dawcy w punkcie
