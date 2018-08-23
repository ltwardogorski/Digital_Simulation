#include "blood_order.h"
#include "queue_of_blood.h"
#include "one_event.h"
#include "simulation_time.h"


blood_order::blood_order(queue_of_blood* queue_blood): priority_queue_blood_(queue_blood)
{
}

bool blood_order::execute(const uint64_t current_time, const bool lock_order, const uint64_t temp_z, time* time) const
{
	if (priority_queue_blood_->lack_of_blood() && !lock_order)
	{
		const auto normal_provision_blood_time = temp_z + current_time;

		time->add_event(new one_event(time::no_data, normal_provision_blood_time, time::normal_provision_blood_comming));

		return true;
	}
	return false;
} 
