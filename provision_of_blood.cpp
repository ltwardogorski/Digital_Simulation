#include "provision_of_blood.h"
#include "unit_of_blood.h"
#include "queue_of_blood.h"


provision_of_blood::provision_of_blood(const uint16_t t1): t1_(t1), actual_id_blood_(0)
{
}

void provision_of_blood::execute(queue_of_blood* priority_queue_blood, blood_donation_point* blood_point,
                                 uint64_t* id_blood, const uint64_t current_time,
                                 uint16_t amount_of_blood)
{
	while (amount_of_blood--)
	{
		actual_id_blood_ = (*id_blood)++;
		priority_queue_blood->add_blood(new unit_of_blood(actual_id_blood_, current_time, t1_));
	}
	priority_queue_blood->update_quantity_blood(blood_point);
}
