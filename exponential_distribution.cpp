#include <iostream>
#include <iomanip>
#include <string>

#include "exponential_distribution.h"
#include "statistics.h"

exponential_distribution::exponential_distribution(const uint64_t grain, const uint64_t m, const uint64_t a) :
	grain_(grain), kernel_(0),
	m_(m), a_(a)
{
}

void exponential_distribution::test(const double lambda, const uint16_t samples)
{
	std::cout << std::endl;
	std::cout << "lambda: " << std::setprecision(10) << lambda << std::endl;

	double average = 0;

	for (auto i = 0; i < samples; ++i)
	{
		kernel_ = -1 / lambda * log(uniform_distr());

		statistics::save_in_file(grain_, kernel_, "exponential.xls");
		average = average + kernel_;
	}

	std::cout << "average : " << average / samples << std::endl;
}

void exponential_distribution::change_grain()
{
	for (uint64_t i = 0; i <= 200000; i++)
	{
		grain_ = grain_ * a_ % m_;
	}
}

uint64_t exponential_distribution::generate(const double lambda)
{
	kernel_ = -1 / lambda * log(uniform_distr());

	return kernel_;
}

double exponential_distribution::uniform_distr()
{
	grain_ = grain_ * a_ % m_;
	return static_cast<double>(grain_) / m_;
}
