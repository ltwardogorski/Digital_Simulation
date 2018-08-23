#pragma once
#include <cstdint>
#include <string>

class statistics
{
public:
	statistics() = default;

	~statistics() = default;

	static void print_in_terminal(uint32_t, uint32_t, uint64_t, uint32_t, uint64_t, uint64_t, uint32_t,
	                              uint32_t, uint16_t, uint16_t, uint8_t, uint64_t, uint64_t, uint64_t, uint64_t);

	static void print_to_file(uint32_t, uint32_t, uint64_t, uint32_t, uint64_t, uint64_t, uint32_t,
	                          uint32_t, uint16_t, uint16_t, uint8_t, uint64_t, uint64_t, uint64_t, uint64_t);

	static void save_in_file(uint64_t data, uint64_t time, std::string file_name);

	static void clear_file();

	static void new_simulation_in_file(uint64_t);

	//	void read_from_file() const;
}; // klasa odpowiedzialna za zapis i wyœwietlanie statystyk symulacji
