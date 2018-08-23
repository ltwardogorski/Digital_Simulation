#include "queue_of_patients.h"

queue_of_patients::queue_of_patients() noexcept
{
}


void queue_of_patients::add_patient(patient* patient)
{
	queue_patient.push(patient);
}

void queue_of_patients::delete_patient()
{
	if (!queue_patient.empty())
	{
		delete queue_patient.front();
		queue_patient.pop();
	}
}

bool queue_of_patients::no_patients() const
{
	return queue_patient.empty();
}

size_t queue_of_patients::size_of_queue() const
{
	return queue_patient.size();
}


patient* queue_of_patients::first_patient()
{
	return queue_patient.front();
}
