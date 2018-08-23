#pragma once
#include "blood_donation_point.h"

class patient : public blood_donation_point
{
	bool is_supported_;
	uint32_t id_;
	uint64_t needed_blood_;

public:
	explicit patient(uint32_t = 0, uint64_t = 0) noexcept;
	~patient() = default;

	void supported(bool);

	bool transfusion_is_possible(uint32_t = 0) const;
	bool take_blood_and_check(uint64_t = 0);
	bool check_its_condition() const;

	uint64_t how_much_blood() const;
	uint32_t my_id() const;
}; // klasa reprezentuj�ca pacjenta
