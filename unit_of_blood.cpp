#include "unit_of_blood.h"

unit_of_blood::
unit_of_blood(const uint64_t id_gen, const uint64_t time_current, const uint16_t expiration) noexcept: id_(id_gen),
                                                                                                       expiration_time_(
	                                                                                                       expiration),
                                                                                                       time_of_coming_(
	                                                                                                       time_current)
{
	has_expired = true;
	time_to_delete_ = time_of_coming_ + expiration_time_;
}

unit_of_blood::~unit_of_blood()
{
	expiration_time_ = 0;
}

bool unit_of_blood::validaty(const uint64_t current_time)
{
	if (current_time >= time_to_delete_)
	{
		has_expired = false;
		return false;
	}
	return true;
}

uint16_t unit_of_blood::expiration_time_of_blood() const
{
	return expiration_time_;
}

uint64_t unit_of_blood::my_id() const
{
	return id_;
}
