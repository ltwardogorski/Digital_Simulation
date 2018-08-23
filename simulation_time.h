#pragma once
#include <cstdint>
#include <queue>
#include <string>

#include "normal_distribution.h"
#include "exponential_distribution.h"
#include "geometric_distribution.h"
#include "uniform_distribution.h"

#include "one_event.h"

#include "blood_transfusion.h"
#include "blood_order.h"

struct line_time
{
	bool operator()(one_event* first_event, one_event* second_event) const;
}; // struktura umozliwiajaca sortowanie jednostek krwi w kolejce


class queue_of_patients;
class queue_of_blood;
class blood_donation_point;

class time
{
	//////////////////////////////////////////////////////  WARUNKI_STA£E  ////////////////////////////////////////////////////////////

	uint16_t r_; // próg jednostek krwi zamówienie normalnego [jednostek krwi]
	uint16_t n_; // liczba zamawianych jednostek krwi dla zamówienie normalnego [jednostek krwi]
	const uint16_t z_ = 1700;
	// rozk³ad_wyk³adniczy_œrednia czas od wys³ania do otrzymania zamówienie normalnego [jednostek czasu]
	const double z_lambda_ = 1.0 / z_;

	uint16_t t1_; // czas wa¿noœci zamówionej krwi [jednostek czasu]
	uint16_t t2_; // czas wa¿noœci krwi od dawcy [jednostek czasu]

	const uint16_t p_ = 250; // rozk³ad_wyk³adniczy_œrednia czas ostêpu pomiêdzy kolejnymi pacjentami [jednostek czasu]
	const double p_lambda_ = 1.0 / p_;
	const double w_ = 0.20; // rozk³ad geometryczny_œrednia zu¿ytej krwi pacjenta 1/w_ [jednostek krwi]

	uint16_t q_; // liczba zamawianych jednostek krwi dla zamówienie awaryjnego [jednostek krwi]
	const double ew2_ = 0.1;
	// rozk³ad_normalny_wariancja czas od wys³ania do otrzymania zamówienie awaryjnego [jednostek czasu]
	const uint16_t e_ = 500;
	// rozk³ad_normalny_œrednia czas od wys³ania do otrzymania zamówienie awaryjnego [jednostek czasu]

	const uint16_t l_ = 950; // rozk³ad_wyk³adniczy_œrednia czas ostêpu pomiêdzy kolejnymi dawcami [jednostek czasu]
	const double l_lambda_ = 1.0 / l_;

	const uint8_t ap_ = 6; // procent zamówienia awaryjnego

	uint16_t tw_min_; // dolna granica rozk³adu równomiernego
	uint16_t tw_max_; // górna granica rozk³adu równomiernego

	uint8_t tk_min_; // dolna granica rozk³adu równomiernego
	uint8_t tk_max_; // górna granica rozk³adu równomiernego

	//////////////////////////////////////////////////////  WARUNKI_STA£E  ////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////  WARUNKI_GENERATOROW  ////////////////////////////////////////////////////////////
	uniform_distribution* uniform_distribution_accident_blood_;
	uniform_distribution* uniform_distribution_accident_time_;

	geometric_distribution* geometric_distribution_needed_blood_;

	exponential_distribution* exponential_distribution_normal_order_;
	exponential_distribution* exponential_distribution_patient_time_;
	exponential_distribution* exponential_distribution_donor_time_;

	normal_distribution* normal_distribution_emergency_order_;

	uint64_t temp_l_ = 0;

	uint64_t temp_p_ = 0;
	uint64_t temp_w_ = 0;

	uint64_t temp_z_ = 0;
	uint64_t temp_q_ = 0;


	uint64_t temp_tw_ = 0;
	uint64_t temp_tk_ = 0;
	//////////////////////////////////////////////////////  WARUNKI_GENERATOROW  ////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////  ID  ////////////////////////////////////////////////////////////
	uint32_t id_donor_;

	uint32_t id_patient_;

	uint64_t id_blood_;

	uint32_t number_of_orders_;

	uint32_t number_of_emergency_orders_;

	uint32_t number_of_accident_;

	uint64_t number_of_event_;

	//////////////////////////////////////////////////////  ID  ////////////////////////////////////////////////////////////

	uint64_t current_time_;
	uint64_t finish_time_;

	uint64_t used_blood_;
	uint64_t used_blood_accident_;

	uint64_t emergency_blood_;

	uint64_t number_of_patient_;

	std::string temp_;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	blood_order* blood_order_;
	blood_transfusion* blood_transfusion_;

public:
	time(uint64_t, uint64_t, const std::string&, uniform_distribution*, uniform_distribution* , geometric_distribution* , exponential_distribution* , exponential_distribution* , exponential_distribution* , normal_distribution* );

	~time() = default;

	typedef std::priority_queue<one_event*, std::vector<one_event*>, line_time> prioiry_line_time;
	// priorytetowa kolejka eventow z kolejnoscia czasu

	prioiry_line_time line_time; // utworzenie kolejki krwi

	void add_event(one_event*);
	void doing_event();
	void delete_event();
	void change_r(uint16_t);
	void change_n(uint16_t);
	void change_t1(uint16_t);
	void change_t2(uint16_t);
	void change_q(uint16_t);

	void simulation(queue_of_patients*, queue_of_blood*, blood_donation_point*,uint64_t);


	enum task
	{
		no_data = 0,
		blood_delete =1,
		donor_blood_comming,

		normal_provision_blood_order,
		normal_provision_blood_comming,
		normal_provision_blood_delete,

		emergency_provision_blood_order,
		emergency_provision_blood_comming,
		emergency_provision_blood_delete,

		is_accident,
		no_blood_to_accident,

		statistics,

		is_patient,
		no_blood_to_patient,

		transfusion_blood,

		accident_bloods,

		clear_stats
	};
}; //klasa odpowiedzialna za zdarzenia czasowe
