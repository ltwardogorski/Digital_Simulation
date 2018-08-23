// simulation_main_code.cpp : Defines the entry point for the console application.//

#include <iostream>
#include <string>

#include "simulation_main_code.h"
#include "simulation_time.h"
#include "test_generators.h"
#include "queue_of_patients.h"
#include "queue_of_blood.h"
#include "blood_donation_point.h"
#include "statistics.h"


int main()
{
	std::cout << "Start Simulation" << std::endl << std::endl;
	statistics::clear_file();

	const uint64_t m = 2147483647;
	const uint64_t a = 16807;
	const uint64_t grain = 1179;

	uint64_t initial_phase = 1;

	std::cout << "Generators TEST y/n ? : ";
	std::string temp_gen;
	std::cin >> temp_gen;
	if (temp_gen[0] == 'y' || temp_gen[0] == 'Y')
	{
		auto* test = new test_generators(20000); //dla generowania arkuszy excel

		auto temp = test->make_grain(grain, 200000); // generowanie kolejnych ziaren oddalonych o 200 000
		std::cout << "grain: " << temp << std::endl;
		statistics::save_in_file(temp, grain, "grain.xls");
		for (auto i = 1; i <= 7; i++)
		{
			temp = test->make_grain(temp, 200000);
			statistics::save_in_file(temp, grain, "grain.xls");
			std::cout << temp << std::endl;
		}

		delete test;
	}


	std::cout << std::endl << "Finish Time (-1 ~ inf) : ";
	std::cin.get();
	uint64_t finish;
	std::cin >> finish;
	std::cout << std::endl;

	std::cout << "Initial Phase (20 000): ";
	std::cin.get();
	std::cin >> initial_phase;
	std::cout << std::endl;

	std::cout << "Number of Patient (20 000): ";
	std::cin.get();
	uint64_t number_patient;
	std::cin >> number_patient;
	std::cout << std::endl;

	std::cout << "N (20): ";
	std::cin.get();
	uint16_t n;
	std::cin >> n;
	std::cout << std::endl;

	std::cout << "R (15): ";
	uint16_t r;
	std::cin.get();
	std::cin >> r;
	std::cout << std::endl;

	std::cout << "Q (11): ";
	uint16_t q;
	std::cin.get();
	std::cin >> q;
	std::cout << std::endl;

	std::cout << "T1 (300): ";
	std::cin.get();
	uint16_t t1;
	std::cin >> t1;
	std::cout << std::endl;

	std::cout << "T2 (500): ";
	std::cin.get();
	uint16_t t2;
	std::cin >> t2;
	std::cout << std::endl;

	std::cout << "Number of Simulation (10): ";
	uint64_t number_simulation;
	std::cin.get();
	std::cin >> number_simulation;
	std::cout << std::endl;

	std::cout << "Step by Step Simulation y/n (print in file) ? : ";
	std::cin.get();
	std::string temp;
	std::cin >> temp;
	std::cout << std::endl;

	const auto uniform_distribution_accident_blood = new uniform_distribution(1165488310, m, a);
	const auto uniform_distribution_accident_time = new uniform_distribution(1159207177, m, a);

	const auto geometric_distribution_needed_blood = new geometric_distribution(1096242934, m, a);

	const auto exponential_distribution_normal_order = new exponential_distribution(890406057, m, a);
	const auto exponential_distribution_patient_time = new exponential_distribution(148268933, m, a);
	const auto exponential_distribution_donor_time = new exponential_distribution(1923159837, m, a);

	const auto normal_distribution_emergency_order = new normal_distribution(609360128, m, a);


	for (uint64_t i = 1; i <= number_simulation; i++)
	{
		std::cout << std::endl << std::endl << "@@@@@@@@ Number Simulation: " << i << std::endl;

		const auto queue_patients = new queue_of_patients;
		const auto prioiry_queue_blood = new queue_of_blood(r);
		const auto donation_point = new blood_donation_point;

		auto* simulation_clock = new time(number_patient, finish, temp,
		                                  uniform_distribution_accident_blood, uniform_distribution_accident_time,
		                                  geometric_distribution_needed_blood, exponential_distribution_normal_order,
		                                  exponential_distribution_patient_time, exponential_distribution_donor_time,
		                                  normal_distribution_emergency_order);

		statistics::new_simulation_in_file(i);

		simulation_clock->change_n(n);
		simulation_clock->change_r(r);
		simulation_clock->change_q(q);
		simulation_clock->change_t1(t1);
		simulation_clock->change_t2(t2);

		simulation_clock->simulation(queue_patients, prioiry_queue_blood, donation_point, initial_phase);

		//przygotowanie kolejnej symulacji
		uniform_distribution_accident_blood->change_grain();
		uniform_distribution_accident_time->change_grain();

		geometric_distribution_needed_blood->change_grain();

		exponential_distribution_normal_order->change_grain();
		exponential_distribution_patient_time->change_grain();
		exponential_distribution_donor_time->change_grain();

		normal_distribution_emergency_order->change_grain();

		delete queue_patients;
		delete prioiry_queue_blood;
		delete donation_point;

		delete simulation_clock;
	}

	std::cout << "Finish Simulation" << std::endl << std::endl;

	std::cin.get();
	std::cin.get();
	return 0;
}
