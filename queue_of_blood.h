#pragma once
#include <queue>

#include "unit_of_blood.h"


struct sort_blood
{
	bool operator()(unit_of_blood* first_unit_blood, unit_of_blood* second_unit_blood) const;
}; // struktura umozliwiajaca sortowanie jednostek krwi w kolejce


class queue_of_blood : public unit_of_blood
{
	uint16_t r_;
	uint64_t deleted_blood_;
	uint64_t created_blood_;

public:
	explicit queue_of_blood(uint16_t);
	~queue_of_blood() = default;

	typedef std::priority_queue<unit_of_blood*, std::vector<unit_of_blood*>, sort_blood> priority_queue_blood;
	// priorytetowa kolejka jednostek krwi

	priority_queue_blood queue_blood; // utworzenie kolejki krwi

	void add_blood(unit_of_blood*);
	void update_quantity_blood(blood_donation_point*) const;
	// funkcja aktualizuj¹ca iloœæ dostêpnej krwi w punkcie krwiodawstwa
	void reset_stats();

	bool pop_blood();
	bool lack_of_blood() const;
	bool no_blood() const;
	bool delete_blood(uint64_t = 0);

	size_t size_of_queue() const;
	uint64_t deleted_blood_queue() const;
	uint64_t created_blood() const;
}; // klasa reprezentuj¹ca kolejkê krwi
