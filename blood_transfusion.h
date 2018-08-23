#pragma once
#include  "blood_transfusion.h"
#include "blood_donation_point.h"

class blood_transfusion
{
	uint32_t pop_blood_;
	queue_of_patients* queue_patients_;
	queue_of_blood* priority_queue_blood_;

public:
	blood_transfusion(queue_of_blood*, queue_of_patients*);

	~blood_transfusion() = default;

	bool check() const;

	uint16_t execute(blood_donation_point*);
}; // klasa odpowiedzialna za transfuzje krwi
