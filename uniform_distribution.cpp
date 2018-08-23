#include "uniform_distribution.h"
#include <iostream>
#include <string>

#include "statistics.h"

uniform_distribution::uniform_distribution(const uint64_t grain, const uint64_t m, const uint64_t a): grain_(grain),
                                                                                                      kernel_(0),
                                                                                                      m_(m), a_(a)
{
}


void uniform_distribution::test(const uint16_t min, const uint16_t max, const uint16_t samples)
{
	std::cout << "lower bound == " << min << std::endl;
	std::cout << "upper bound == " << max << std::endl;


	double average = 0;
	for (auto i = 0; i < samples; ++i)
	{
		kernel_ = min + (max - min) * uniform_distr();

		statistics::save_in_file(grain_, kernel_, "uniform.xls");
		average = average + kernel_;
	}

	std::cout << "average : " << average / samples << std::endl;
}

void uniform_distribution::change_grain()
{
	for (uint64_t i = 0; i <= 200000; i++)
	{
		grain_ = grain_ * a_ % m_;
	}
}

uint64_t uniform_distribution::generate(const uint16_t min, const uint16_t max)
{
	kernel_ = min + (max - min) * uniform_distr();

	return kernel_;
}

double uniform_distribution::uniform_distr()
{
	grain_ = grain_ * a_ % m_;
	return static_cast<double>(grain_) / m_;
}
