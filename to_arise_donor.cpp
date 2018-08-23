#include "to_arise_donor.h"
#include "donor.h"
#include "unit_of_blood.h"
#include "queue_of_blood.h"

to_arise_donor::to_arise_donor(uint32_t* id_donor, uint64_t* id_blood, const uint16_t t2): t2_(t2),
                                                                                           actual_id_blood_(
	                                                                                           (*id_blood)++),
                                                                                           actual_id_donor_(
	                                                                                           (*id_donor)++)
{
}

void to_arise_donor::execute(queue_of_blood* priority_queue_blood, blood_donation_point* blood_point,
                             const uint64_t current_time) const
{
	const auto person_donor = new donor(actual_id_donor_);

	priority_queue_blood->add_blood(new unit_of_blood(actual_id_blood_, current_time, t2_));
	delete person_donor;
	priority_queue_blood->update_quantity_blood(blood_point);
}
