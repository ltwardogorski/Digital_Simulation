#pragma once
#include <cstdint>

#include "blood_donation_point.h"


class unit_of_blood : public blood_donation_point
{
	uint64_t id_;
	uint16_t expiration_time_;
	uint64_t time_of_coming_;
	uint64_t time_to_delete_;

public:
	explicit unit_of_blood(uint64_t = 0, uint64_t = 0, uint16_t = 0) noexcept;
	~unit_of_blood();

	bool has_expired; // flaga okreœlaj¹ca wa¿noœæ krwi

	bool validaty(uint64_t current_time);

	uint16_t expiration_time_of_blood() const;
	uint64_t my_id() const;
}; // klasa reprezentuj¹ca jednostki krwi
