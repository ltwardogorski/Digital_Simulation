#include "emergency_blood_order.h"
#include "simulation_time.h"
#include "one_event.h"
#include <iostream>


bool emergency_blood_order::execute(const uint64_t current_time, const bool lock_order, const uint64_t temp_q,
                                    time* time)
{
	if (!time->line_time.empty() && !lock_order)
	{
		const auto finish_time_event_emergency = temp_q + current_time;

		time->add_event(new one_event(time->line_time.top()->give_data(), finish_time_event_emergency,
		                              time::emergency_provision_blood_comming));

		return true;
	}

	return false;
} 
