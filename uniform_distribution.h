#pragma once
#include <cstdint>

class uniform_distribution
{
	uint64_t grain_;
	uint64_t kernel_;
	const uint64_t m_;
	const uint64_t a_;

public:
	uniform_distribution(uint64_t, uint64_t, uint64_t);
	~uniform_distribution() = default;

	void test(uint16_t, uint16_t, uint16_t);
	void change_grain();

	uint64_t generate(uint16_t, uint16_t);

	double uniform_distr();
};
