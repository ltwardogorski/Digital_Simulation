#include "accident.h"
#include "unit_of_blood.h"
#include "queue_of_blood.h"

accident::accident(queue_of_blood* priority_queue_blood, blood_donation_point* blood_point,
                   const uint64_t amount_of_blood):
	actual_number_accident_(1), needed_bloods_(amount_of_blood), amount_bloods_(1),
	blood_point_(blood_point), priority_queue_blood_(priority_queue_blood)
{
}

uint64_t accident::execute(uint32_t* number_of_accident)
{
	amount_bloods_ = needed_bloods_;
	actual_number_accident_ = (*number_of_accident)++;

	while (needed_bloods_)
	{
		if (priority_queue_blood_->pop_blood())
		{
			--needed_bloods_;
			priority_queue_blood_->update_quantity_blood(blood_point_);
		}
		else
			break;
	}

	priority_queue_blood_->update_quantity_blood(blood_point_);

	return amount_bloods_ - needed_bloods_;
}


uint64_t accident::pop_blood()
{
	amount_bloods_ = needed_bloods_;
	while (needed_bloods_)
	{
		if (priority_queue_blood_->pop_blood())
		{
			--needed_bloods_;
			priority_queue_blood_->update_quantity_blood(blood_point_);
		}
		else
			break;
	}

	priority_queue_blood_->update_quantity_blood(blood_point_);

	return amount_bloods_ - needed_bloods_;
}

bool accident::accident_done() const
{
	return needed_bloods_ == 0;
}
