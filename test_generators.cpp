#include "test_generators.h"
#include <fstream>
#include <iostream>
#include "uniform_distribution.h"
#include "geometric_distribution.h"
#include "exponential_distribution.h"
#include "normal_distribution.h"
#include "statistics.h"



test_generators::test_generators(const uint32_t test) noexcept
{
	sample_test_ = test;
	std::cout << " TEST GENERATORS " << std::endl;

	uniform_distribution_accident_blood_ = new uniform_distribution(1165488310, m_, a_);
	uniform_distribution_accident_time_ = new uniform_distribution(1159207177, m_, a_);

	geometric_distribution_needed_blood_ = new geometric_distribution(1096242934, m_, a_);

	exponential_distribution_normal_order_ = new exponential_distribution(890406057, m_, a_);
	exponential_distribution_patient_time_ = new exponential_distribution(148268933, m_, a_);
	exponential_distribution_donor_time_ = new exponential_distribution(1923159837, m_, a_);

	normal_distribution_emergency_order_ = new normal_distribution(609360128, m_, a_);

	test_uniform_distribution();

	test_geometric_distribution();

	test_exponential_distribution();

	test_normal_distribution();

	std::cout << " END TEST GENERATORS " << std::endl << std::endl;
}

test_generators::~test_generators()
{
	delete uniform_distribution_accident_blood_;
	delete uniform_distribution_accident_time_;

	delete geometric_distribution_needed_blood_;

	delete exponential_distribution_normal_order_;
	delete exponential_distribution_patient_time_;
	delete exponential_distribution_donor_time_;

	delete normal_distribution_emergency_order_;
}

void test_generators::test_uniform_distribution() const
{
	const uint16_t tw_min = 15000;
	const uint16_t tw_max = 16000;

	const uint8_t tk_min = 10;
	const uint8_t tk_max = 20;

	std::ofstream result;
	result.open("uniform.xls", std::ios::out | std::ios::app);
	result << std::endl << std::endl << "@@@@ Accident blood: " << "\t\t\t" << 1165488310<<std::endl << std::endl;
	result.close();
	uniform_distribution_accident_blood_->test(tk_min, tk_max, sample_test_);
	/*for (uint32_t i = 0; i < sample_test_ / 100; i++)
	{
		std::cout << uniform_distribution_accident_blood_->generate(tk_min, tk_max) << std::endl;
	}*/
	std::cout << std::endl << std::endl;

	result.open("uniform.xls", std::ios::out | std::ios::app);
	result << std::endl << std::endl << "@@@@ Accident: " << "\t\t\t" << 1159207177 << std::endl << std::endl;
	result.close();
	uniform_distribution_accident_time_->test(tw_min, tw_max, sample_test_);
	/*for (uint32_t i = 0; i < sample_test_ / 100; i++)
	{
		std::cout << uniform_distribution_accident_time_->generate(tw_min, tw_max) << std::endl;
	}*/
}

void test_generators::test_geometric_distribution() const
{
	const auto w = 0.20;

	std::ofstream result;
	result.open("geometric.xls", std::ios::out | std::ios::app);
	result << std::endl << std::endl << "@@@@ Patient blood: " << "\t\t\t" << 1096242934 << std::endl << std::endl;
	result.close();
	geometric_distribution_needed_blood_->test(w, sample_test_);
	/*for (uint32_t i = 0; i < sample_test_ / 100; i++)
	{
		std::cout << geometric_distribution_needed_blood_->generate(w) << std::endl;
	}*/
}


void test_generators::test_exponential_distribution() const
{
	const auto p_lambda = 1.0 / 250;
	const auto l_lambda = 1.0 / 950;
	const auto z_lambda = 1.0 / 1700;

	std::ofstream result;
	result.open("exponential.xls", std::ios::out | std::ios::app);
	result << std::endl << std::endl << "@@@@ Normal time order: " << "\t\t\t" << 890406057 << std::endl << std::endl;
	result.close();
	exponential_distribution_normal_order_->test(z_lambda, sample_test_);
	/*for (uint32_t i = 0; i < sample_test_ / 100; i++)
	{
		std::cout << exponential_distribution_normal_order_->generate(z_lambda) << std::endl;
	}*/

	result.open("exponential.xls", std::ios::out | std::ios::app);
	result << std::endl << std::endl << "@@@@ Patient time: " << "\t\t\t" << 148268933 << std::endl << std::endl;
	result.close();
	exponential_distribution_patient_time_->test(p_lambda, sample_test_);
	/*for (uint32_t i = 0; i < sample_test_ / 100; i++)
	{
		std::cout << exponential_distribution_patient_time_->generate(p_lambda) << std::endl;
	}*/

	result.open("exponential.xls", std::ios::out | std::ios::app);
	result << std::endl << std::endl << "@@@@ Donor time: " << "\t\t\t" << 1923159837 << std::endl << std::endl;
	result.close();
	exponential_distribution_donor_time_->test(l_lambda, sample_test_);
	/*for (uint32_t i = 0; i < sample_test_ / 100; i++)
	{
		std::cout << exponential_distribution_donor_time_->generate(l_lambda) << std::endl;
	}*/
}

void test_generators::test_normal_distribution() const
{
	const auto ew2 = 0.1;
	const uint16_t e = 500;

	std::ofstream result;
	result.open("normal.xls", std::ios::out | std::ios::app);
	result << std::endl << std::endl << "@@@@ Emergency time order: " << "\t\t\t" << 609360128 << std::endl << std::endl;
	result.close();
	normal_distribution_emergency_order_->test(e, ew2, sample_test_);
	/*for (uint32_t i = 0; i < sample_test_ / 100; i++)
	{
		std::cout << normal_distribution_emergency_order_->generate(e, ew2) << std::endl;
	}*/
}

uint64_t test_generators::make_grain(const uint64_t grain, const uint64_t samples)
{
	grain_ = grain;
	for (uint64_t i = 0; i <= samples; i++) {
		grain_ = grain_ * a_ % m_;
	}
	return grain_;
}
