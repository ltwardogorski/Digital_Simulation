#include "queue_of_blood.h"

bool sort_blood::operator()(unit_of_blood* first_unit_blood, unit_of_blood* second_unit_blood) const
{
	return first_unit_blood->expiration_time_of_blood() > second_unit_blood->expiration_time_of_blood();
}

queue_of_blood::queue_of_blood(const uint16_t r): r_(r), deleted_blood_(0), created_blood_(0)
{
}


void queue_of_blood::add_blood(unit_of_blood* blood)
{
	queue_blood.push(blood);
	created_blood_++;
}

void queue_of_blood::reset_stats()
{
	deleted_blood_ = 0;
	created_blood_ = 0;
}

void queue_of_blood::update_quantity_blood(blood_donation_point* blood_point) const
{
	blood_point->blood_update(size_of_queue());
}

bool queue_of_blood::delete_blood(const uint64_t current_time)
{
	auto flag = false;
	while (!queue_blood.empty() && !queue_blood.top()->validaty(current_time))
	{
		if (queue_blood.size() == 1)
			if (queue_blood.empty())

				delete queue_blood.top();
		queue_blood.pop();
		deleted_blood_++;
		flag = true;
	}


	return flag;
}

bool queue_of_blood::pop_blood()
{
	if (queue_blood.empty())
	{
		//		std::cout << "Warning!! We don't have blood units !!!! " << std::endl;
		return false;
	}
	if (queue_blood.size() == 1)
	{
		delete queue_blood.top();
		queue_blood.pop();
		//		std::cout << "Warning!! We don't have blood units !!!! " << std::endl;
		return true;
	}
	delete queue_blood.top();
	queue_blood.pop();
	return true;
}

bool queue_of_blood::lack_of_blood() const
{
	if (queue_blood.empty())
		return true;

	return queue_blood.size() <= r_;
}


bool queue_of_blood::no_blood() const
{
	return queue_blood.empty();
}

size_t queue_of_blood::size_of_queue() const
{
	return queue_blood.size();
}

uint64_t queue_of_blood::deleted_blood_queue() const
{
	return deleted_blood_;
}

uint64_t queue_of_blood::created_blood() const
{
	return created_blood_;
}

