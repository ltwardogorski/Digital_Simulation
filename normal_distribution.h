#pragma once
#include <cstdint>

class normal_distribution
{
	uint64_t grain_;
	uint64_t kernel_;
	const uint64_t m_;
	const uint64_t a_;

public:
	normal_distribution(uint64_t, uint64_t, uint64_t);
	~normal_distribution() = default;

	void test(double, double, uint16_t);
	void change_grain();

	uint64_t generate(double, double);

	double uniform_distr();
};
