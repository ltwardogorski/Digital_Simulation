#include "patient.h"

patient::patient(const uint32_t id_gen,
                 const uint64_t blood) noexcept: is_supported_(false), id_(id_gen), needed_blood_(blood)
{
}

void patient::supported(const bool condition)
{
	is_supported_ = condition;
}

bool patient::transfusion_is_possible(const uint32_t avalible_blood) const
{
	return avalible_blood >= needed_blood_;
}

bool patient::take_blood_and_check(const uint64_t available_blood)
{
	if (needed_blood_ == 0 || available_blood == 0)
		return false;

	--needed_blood_;
	supported(true);
	return true;
}

bool patient::check_its_condition() const
{
	return is_supported_;
}

uint32_t patient::my_id() const
{
	return id_;
}

uint64_t patient::how_much_blood() const
{
	return needed_blood_;
}
