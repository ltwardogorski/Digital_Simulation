#include <iostream>
#include <iomanip>
#include <string>

#include "geometric_distribution.h"
#include "statistics.h"

geometric_distribution::geometric_distribution(const uint64_t grain, const uint64_t m, const uint64_t a) :
	grain_(grain),
	kernel_(0),
	m_(m), a_(a)
{
}

void geometric_distribution::test(const double p, const uint16_t samples)
{
	std::cout << std::endl;
	std::cout << "p: " << std::setprecision(10) << p << std::endl;

	double average = 0;

	for (auto i = 0; i < samples; ++i)
	{
		kernel_ = 1;
		while (true)
		{
			if (uniform_distr() > p)
			{
				kernel_ ++;
				continue;
			}
			break;
		}

		statistics::save_in_file(grain_, kernel_, "geometric.xls");
		average = average + kernel_;
	}

	std::cout << "w : " << 1 / (average / samples) << std::endl;
	std::cout << "average : " << double(average / samples) << std::endl;
}

void geometric_distribution::change_grain()
{
	for (uint64_t i = 0; i <= 200000; i++)
	{
		grain_ = grain_ * a_ % m_;
	}
}

uint64_t geometric_distribution::generate(const double p)
{
	kernel_ = 1;
	while (true)
	{
		if (uniform_distr() > p)
		{
			kernel_ ++;
			continue;
		}
		break;
	}

	return kernel_;
}

double geometric_distribution::uniform_distr()
{
	grain_ = grain_ * a_ % m_;
	return static_cast<double>(grain_) / m_;
}
