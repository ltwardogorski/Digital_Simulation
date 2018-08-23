#include "to_arise_patient.h"
#include "queue_of_patients.h"
#include "patient.h"


to_arise_patient::to_arise_patient(uint32_t* id_patient, const uint64_t blood): actual_id_patient_((*id_patient)++),
                                                                                needed_blood_temp_(blood)
{
}

void to_arise_patient::execute(queue_of_patients* queue_patients) const
{
	queue_patients->add_patient(new patient(actual_id_patient_, needed_blood_temp_));
}
