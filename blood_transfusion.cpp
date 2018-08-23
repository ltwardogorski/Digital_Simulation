#include "blood_transfusion.h"
#include "queue_of_patients.h"
#include "patient.h"
#include "queue_of_blood.h"


blood_transfusion::
blood_transfusion(queue_of_blood* queue_blood, queue_of_patients* queue_patients): pop_blood_(0),
                                                                                   queue_patients_(queue_patients),
                                                                                   priority_queue_blood_(queue_blood)
{
}

uint16_t blood_transfusion::execute(blood_donation_point* blood_point)
{
	pop_blood_ = 0;
	if (!queue_patients_->no_patients() && queue_patients_->first_patient()->how_much_blood() == 0)
	{
		queue_patients_->delete_patient();
	}
	if (!queue_patients_->no_patients() && queue_patients_->first_patient()->how_much_blood() != 0)
	{
		while (!queue_patients_->no_patients() && !priority_queue_blood_->no_blood())
		{
			if (priority_queue_blood_->pop_blood())
			{
				queue_patients_->first_patient()->take_blood_and_check(blood_point->availble_blood_in_system());
				pop_blood_++;
				priority_queue_blood_->update_quantity_blood(blood_point);
			}

			if (!queue_patients_->no_patients() && queue_patients_->first_patient()->how_much_blood() == 0)
			{
				queue_patients_->delete_patient();
			}
		}
	}
	return pop_blood_;
}

bool blood_transfusion::check() const
{
	return !queue_patients_->no_patients();
}
