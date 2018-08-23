#pragma once
#include <cstdint>

#include "uniform_distribution.h"
#include "geometric_distribution.h"
#include "exponential_distribution.h"
#include "normal_distribution.h"

class test_generators
{
	uint32_t sample_test_;

	const uint64_t m_ = 2147483647;
	const uint64_t a_ = 16807;
	uint64_t grain_ = 0;

	uniform_distribution* uniform_distribution_accident_blood_;
	uniform_distribution* uniform_distribution_accident_time_;

	geometric_distribution* geometric_distribution_needed_blood_;

	exponential_distribution* exponential_distribution_normal_order_;
	exponential_distribution* exponential_distribution_patient_time_;
	exponential_distribution* exponential_distribution_donor_time_;

	normal_distribution* normal_distribution_emergency_order_;

public:
	explicit test_generators(uint32_t) noexcept;
	~test_generators();

	void test_uniform_distribution() const;
	void test_geometric_distribution() const;
	void test_normal_distribution() const;
	void test_exponential_distribution() const;

	uint64_t make_grain(uint64_t, uint64_t);
}; // klasa testujaca generatory
