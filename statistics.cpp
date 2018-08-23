#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <vector>

#include "statistics.h"

void statistics::print_in_terminal(const uint32_t id_donor, const uint32_t id_patient, const uint64_t used_blood,
                                   const uint32_t number_of_accident, const uint64_t used_blood_accident,
                                   const uint64_t deleted_blood, const uint32_t number_of_orders,
                                   const uint32_t number_of_emergency_orders, const uint16_t n, const uint16_t r,
                                   const uint8_t ap, const uint64_t current_time, const uint64_t number_of_event,
                                   const uint64_t created_blood,
                                   const uint64_t emergency_blood)
{
	std::cout << "______________________________________________________________________________________" << std::endl;

	std::cout << "Statistics to finish time:" << current_time << "                  " << "number_of_event: " <<
		number_of_event << std
		::endl << std::endl;
	std::cout << "Number of donors: " << id_donor << std::endl << std::endl;

	std::cout << "Number of patients: " << id_patient << std::endl;
	std::cout << "Used blood by patients: " << used_blood << std::endl << std::endl;

	std::cout << "Number of accidents: " << number_of_accident << std::endl;
	std::cout << "Used blood in an accident: " << used_blood_accident << std::endl << std::endl;

	std::cout << "Created units of bloods: " << created_blood << std::endl;
	std::cout << "Expired blood: " << deleted_blood << std::endl;
	std::cout << "Emergency blood: " << emergency_blood << std::endl << std::endl;

	std::cout << "Percent deleted blood: " << std::setprecision(3) << 100 * static_cast<double>(deleted_blood) /
		created_blood << " %" << std::endl;
	std::cout << "Percent emergency blood: " << std::setprecision(3) << 100 * static_cast<double>(emergency_blood) /
		created_blood << " %" << std::endl << std::endl;

	std::cout << "Completed normall orders: " << number_of_orders << std::endl;
	std::cout << "Completed emergency orders: " << number_of_emergency_orders << std::endl;
	const auto temp_probability = static_cast<double>(number_of_emergency_orders * 100.0) / number_of_event;
	std::cout << "Probability of emergency ordering: " << std::setprecision(3) << temp_probability << '%'
		<< std::endl << std::endl;

	std::cout << "Change n_ about: " << int(n) - 20 << std::endl;
	std::cout << "Change r_ about: " << int(r) - 15 << std::endl << std::endl;

	if (temp_probability > ap)
		std::cout << "Simulation condition it is not met!!!" << std::endl;
	else
		std::cout << "Simulation condition is fulfilled" << std::endl;
	std::cout << "--------------------------------------------------------------------------------------" << std::endl;
}


void statistics::print_to_file(const uint32_t id_donor, const uint32_t id_patient, const uint64_t used_blood,
                               const uint32_t number_of_accident, const uint64_t used_blood_accident,
                               const uint64_t deleted_blood, const uint32_t number_of_orders,
                               const uint32_t number_of_emergency_orders, const uint16_t n, const uint16_t r,
                               const uint8_t ap, const uint64_t current_time, const uint64_t number_of_event,
                               const uint64_t created_blood,
                               const uint64_t emergency_blood)
{
	std::ofstream result;
	result.open("statistics.txt", std::ios::out | std::ios::app);

	result << "______________________________________________________________________________________" << std::endl;

	result << "Statistics to finish time:" << current_time << "                  " << "number_of_event: " <<
		number_of_event << std::
		endl << std::endl;
	result << "Number of donors: " << id_donor << std::endl << std::endl;

	result << "Number of patients: " << id_patient << std::endl;
	result << "Used blood by patients: " << used_blood << std::endl << std::endl;

	result << "Number of accidents: " << number_of_accident << std::endl;
	result << "Used blood in an accident: " << used_blood_accident << std::endl << std::endl;

	result << "Created units of bloods: " << created_blood << std::endl;
	result << "Expired blood: " << deleted_blood << std::endl;
	result << "Emergency blood: " << emergency_blood << std::endl << std::endl;

	result << "Percent deleted blood: " << std::setprecision(3) << 100 * static_cast<double>(deleted_blood) / created_blood
		<< " %" << std::endl;
	result << "Percent emergency blood: " << std::setprecision(3) << 100 * static_cast<double>(emergency_blood) /
		created_blood << " %" << std::endl << std::endl;

	result << "Completed normall orders: " << number_of_orders << std::endl;
	result << "Completed emergency orders: " << number_of_emergency_orders << std::endl;
	const auto temp_probability = static_cast<double>(number_of_emergency_orders * 100.0) / number_of_event;
	result << "Probability of emergency ordering: " << std::setprecision(3) << temp_probability << '%'
		<< std::endl << std::endl;

	result << "Change n_ about: " << int(n) - 20 << std::endl;
	result << "Change r_ about: " << int(r) - 15 << std::endl << std::endl;

	if (temp_probability > ap)
		result << "Simulation condition it is not met!!!" << std::endl;
	else
		result << "Simulation condition is fulfilled" << std::endl;
	result << "--------------------------------------------------------------------------------------" << std::endl;
	result.close();
}


void statistics::save_in_file(const uint64_t data, const uint64_t time, const std::string file_name)
{
	std::ofstream result;
	result.open(file_name, std::ios::out | std::ios::app);
	result << time << "\t\t" << data << std::endl;
	result.close();
}

void statistics::clear_file()
{
	std::ofstream result;
	result.open("avalible_blood.xls", std::ios::out | std::ios::trunc);
	result.close();

	result.open("normal_provision_blood.xls", std::ios::out | std::ios::trunc);
	result.close();

	result.open("emergency_provision_blood.xls", std::ios::out | std::ios::trunc);
	result.close();

	result.open("accident.xls", std::ios::out | std::ios::trunc);
	result.close();

	result.open("new_patient.xls", std::ios::out | std::ios::trunc);
	result.close();

	result.open("queue_patients.xls", std::ios::out | std::ios::trunc);
	result.close();

	result.open("statistics.txt", std::ios::out | std::ios::trunc);
	result.close();


	result.open("uniform.xls", std::ios::out | std::ios::trunc);
	result.close();

	result.open("geometric.xls", std::ios::out | std::ios::trunc);
	result.close();

	result.open("exponential.xls", std::ios::out | std::ios::trunc);
	result.close();

	result.open("normal.xls", std::ios::out | std::ios::trunc);
	result.close();

	result.open("grain.xls", std::ios::out | std::ios::trunc);
	result.close();
}

void statistics::new_simulation_in_file(const uint64_t number_simulation)
{
	std::ofstream result;
	result.open("avalible_blood.xls", std::ios::out | std::ios::app);
	result << std::endl << std::endl << "@@@@@@@@ Number Simulation: " << number_simulation << std::endl << std::endl;
	result.close();

	result.open("normal_provision_blood.xls", std::ios::out | std::ios::app);
	result << std::endl << std::endl << "@@@@@@@@ Number Simulation: " << number_simulation << std::endl << std::endl;
	result.close();

	result.open("emergency_provision_blood.xls", std::ios::out | std::ios::app);
	result << std::endl << std::endl << "@@@@@@@@ Number Simulation: " << number_simulation << std::endl << std::endl;
	result.close();

	result.open("accident.xls", std::ios::out | std::ios::app);
	result << std::endl << std::endl << "@@@@@@@@ Number Simulation: " << number_simulation << std::endl << std::endl;
	result.close();

	result.open("new_patient.xls", std::ios::out | std::ios::app);
	result << std::endl << std::endl << "@@@@@@@@ Number Simulation: " << number_simulation << std::endl << std::endl;
	result.close();

	result.open("queue_patients.xls", std::ios::out | std::ios::app);
	result << std::endl << std::endl << "@@@@@@@@ Number Simulation: " << number_simulation << std::endl << std::endl;
	result.close();

	result.open("statistics.txt", std::ios::out | std::ios::app);
	result << std::endl << std::endl << "@@@@@@@@ Number Simulation: " << number_simulation << std::endl << std::endl;
	result.close();
}


/*
void statistics::read_from_file() const
//UWAGA FUNKCJA TESTOWA !!!!
{
	std::fstream data; //odczyt z pliku tekstu
	data.open("RESULT.TXT", std::ios::in);
	if (data.good())
	{
		std::string word_data;
		std::cout << "in file \"DATA.txt\"" << std::endl;
		while (!data.eof())
		{
			getline(data, word_data);
			std::cout << word_data << std::endl;
		}
		data.close();
	}
	else
		std::cout << "I'm can't open this file \"DATA.txt\"" << std::endl; //koniec odczytu tesktu


	std::fstream data_num; //odczyt z pliku cyfr do wektora
	data_num.open("NUMBERS.TXT", std::ios::in);
	std::vector<double> num_data;
	if (data_num.good())
	{
		std::cout << "in file \"NUMBERS.TXT\"" << std::endl;
		while (!data_num.eof())
		{
			std::string temp;
			getline(data_num, temp);
			num_data.push_back(atof(temp.c_str()));
		}
		data_num.close();
		if (num_data.back() == 0)
			num_data.pop_back(); //usuniecie ostatniej pustej lini tekstu "0"
	}
	else
		std::cout << "I'm can't open this file \"NUMBERS.TXT\"" << std::endl;
	//koniec odczytu cyfr i kopiowania elementow do wektora


	auto num_iter_data = num_data.begin(); //utworzenie iteratora i drukowanie zawartosci wektora
	for (; num_iter_data != num_data.end(); ++num_iter_data)
	{
		if (num_data.size() <= 1)
		{
			std::cout << "\"num_Data\" is empty!" << std::endl;
			break;
		}
		std::cout << *num_iter_data << std::endl; // koniec drukowania zawartosci wektora
	}
}
*/
