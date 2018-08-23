#pragma once
#include <cstdint>

class one_event
{
	uint16_t task_;
	uint16_t data_; // ex. needed blood
	uint64_t time_event_;

public:
	one_event(uint16_t, uint64_t, uint16_t);

	~one_event() = default;

	void take_task(uint16_t);
	void take_data(uint16_t);
	void take_time_event(uint64_t);

	bool check_data_and_dec();
	bool check_task(uint16_t) const;

	uint16_t give_task() const;
	uint16_t give_data() const;	
	uint64_t give_time_event() const;
};
