#pragma once
#include <cstdint>

class queue_of_patients;

class to_arise_patient
{
	uint32_t actual_id_patient_;
	uint64_t needed_blood_temp_;

public:
	to_arise_patient(uint32_t*, uint64_t);
	~to_arise_patient() = default;

	void execute(queue_of_patients*) const;
}; //klasa reprezentuj¹ca przyjœcie pacjenta do punktu
