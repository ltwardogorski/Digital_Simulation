#pragma once
#include "blood_donation_point.h"

class donor : public blood_donation_point
{
	uint32_t id_;

public:
	explicit donor(uint32_t = 0) noexcept;
	~donor() = default;
}; // klasa reprezentuj¹ca dawce
