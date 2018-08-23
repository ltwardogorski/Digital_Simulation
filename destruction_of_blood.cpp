#include "destruction_of_blood_.h"
#include "queue_of_blood.h"

bool destruction_of_blood::execute(queue_of_blood* priority_queue_blood, blood_donation_point* blood_point,
                                   const uint64_t current_time)
{
	if (priority_queue_blood->delete_blood(current_time))
	{
		priority_queue_blood->update_quantity_blood(blood_point);
		return true;
	}

	return false;
}
