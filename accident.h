#pragma once
#include "blood_donation_point.h"

class accident
{
	uint64_t actual_number_accident_;
	uint64_t needed_bloods_;
	uint64_t amount_bloods_;
	blood_donation_point* blood_point_;
	queue_of_blood* priority_queue_blood_;
public:
	accident(queue_of_blood*, blood_donation_point*, uint64_t);

	~accident() = default;

	bool accident_done() const;

	uint64_t execute(uint32_t*);
	uint64_t pop_blood();
}; // klasa odpowiedzialna za obs³ugê wypadku 
