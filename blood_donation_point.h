#pragma once
#include <cstdint>

class queue_of_blood;
class queue_of_patients;
class patient;

class blood_donation_point
{
	int64_t availble_blood_;

public:

	 blood_donation_point()	noexcept;
	~blood_donation_point() = default;

	void blood_update(uint64_t);
	uint64_t availble_blood_in_system() const;

}; // klasa reprezentuj¹ca punkt krwiodawstwa
