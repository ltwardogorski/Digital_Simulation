#pragma once
#include <cstdint>

class geometric_distribution
{
	uint64_t grain_;
	uint64_t kernel_;
	const uint64_t m_;
	const uint64_t a_;

public:
	geometric_distribution(uint64_t, uint64_t, uint64_t);
	~geometric_distribution() = default;

	void test(double, uint16_t);
	void change_grain();

	uint64_t generate(double);

	double uniform_distr();
};
