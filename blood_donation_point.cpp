#include "blood_donation_point.h"


blood_donation_point::blood_donation_point() noexcept: availble_blood_(0)
{
}

void blood_donation_point::blood_update(const uint64_t amount_of_blood)
{
	availble_blood_ = amount_of_blood;
}

uint64_t blood_donation_point::availble_blood_in_system() const
{
	return availble_blood_;
}
