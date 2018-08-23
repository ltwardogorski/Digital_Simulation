#pragma once
#include <queue>

#include "patient.h"

class queue_of_patients : public patient
{
public:
	queue_of_patients() noexcept;
	~queue_of_patients() = default;

	std::queue<patient*> queue_patient; // kolejka pacjent�w

	void add_patient(patient*);
	void delete_patient();

	bool no_patients() const;

	size_t size_of_queue() const;

	patient* first_patient();
}; // klasa reprezentuj�ca kolejk� pacjent�w
