#include "one_event.h"

one_event::one_event(const uint16_t data_blood, const uint64_t next_time, const uint16_t type_temp):
	task_(type_temp),
	data_(data_blood),
	time_event_(next_time)
{
}

void one_event::take_data(const uint16_t data_temp)
{
	data_ = data_temp;
}

void one_event::take_task(const uint16_t task_temp)
{
	task_ = task_temp;
}

void one_event::take_time_event(const uint64_t temp_time_event)
{
	time_event_ = temp_time_event;
}

bool one_event::check_data_and_dec()
{
	if (data_ == 0)
		return false;

	--data_;
	return true;
}

bool one_event::check_task(const uint16_t temp) const
{
	return task_ == temp;
}

uint16_t one_event::give_data() const
{
	return data_;
}

uint16_t one_event::give_task() const
{
	return task_;
}

uint64_t one_event::give_time_event() const
{
	return time_event_;
}
