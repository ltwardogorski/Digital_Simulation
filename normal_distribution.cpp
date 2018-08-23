#include <iostream>
#include <iomanip>
#include <string>


#include "normal_distribution.h"
#include "statistics.h"


normal_distribution::normal_distribution(const uint64_t grain, const uint64_t m, const uint64_t a) : grain_(grain),
                                                                                                     kernel_(0),
                                                                                                     m_(m), a_(a)
{
}

void normal_distribution::test(const double e, const double ew, const uint16_t samples)
{
	std::cout << std::endl;
	std::cout << "e: " << std::setprecision(10) << e << std::endl;
	std::cout << "ew: " << std::setprecision(10) << ew << std::endl;


	double average = 0;

	for (auto i = 0; i < samples; ++i)
	{
		kernel_ = 0;
		double temp = 0;
		for (auto index = 0; index < 12; index++)
		{
			temp += uniform_distr();
		}
		temp -= 6.0;
		kernel_ = temp * ew + e;

		statistics::save_in_file(grain_, kernel_, "normal.xls");
		average = average + kernel_;
	}

	std::cout << "average : " << average / samples << std::endl;
}

void normal_distribution::change_grain()
{
	for (uint64_t i = 0; i <= 200000; i++)
	{
		grain_ = grain_ * a_ % m_;
	}
}

uint64_t normal_distribution::generate(const double e, const double ew)
{
	double temp = 0;
	for (auto i = 0; i < 12; i++)
	{
		temp += uniform_distr();
	}
	temp -= 6.0;
	kernel_ = temp * ew + e;
	return kernel_;
}

double normal_distribution::uniform_distr()
{
	grain_ = grain_ * a_ % m_;
	return static_cast<double>(grain_) / m_;
}
