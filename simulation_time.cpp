#include <iostream>

#include "simulation_time.h"
#include "statistics.h"

#include "queue_of_patients.h"
#include "queue_of_blood.h"
#include "blood_donation_point.h"

#include "to_arise_donor.h"
#include "destruction_of_blood_.h"
#include "provision_of_blood.h"
#include "accident.h"
#include "to_arise_patient.h"
#include "emergency_blood_order.h"


bool line_time::operator()(one_event* first_event, one_event* second_event) const
{
	return first_event->give_time_event() > second_event->give_time_event();
}

void time::add_event(one_event* event)
{
	line_time.push(event);
}

void time::doing_event()
{
	if (!line_time.empty())
		current_time_ = line_time.top()->give_time_event();
	else
		current_time_++;
}

void time::delete_event()
{
	if (!line_time.empty())
	{
		delete line_time.top();
		line_time.pop();
	}
}


time::time(const uint64_t number_patient, const uint64_t finish, const std::string& temp,
           uniform_distribution* uniform_distribution_accident_b,
           uniform_distribution* uniform_distribution_accident_t,
           geometric_distribution* geometric_distribution_b,
           exponential_distribution* exponential_distribution_order_n,
           exponential_distribution* exponential_distribution_patient,
           exponential_distribution* exponential_distribution_donor,
           normal_distribution* normal_distribution_order_e
)
{
	id_donor_ = 0;
	id_patient_ = 0;
	id_blood_ = 0;
	number_of_orders_ = 0;
	number_of_emergency_orders_ = 0;
	number_of_accident_ = 0;
	temp_ = temp;

	used_blood_ = 0;
	used_blood_accident_ = 0;

	emergency_blood_ = 0;

	current_time_ = 0;
	finish_time_ = finish;
	number_of_patient_ = number_patient;
	number_of_event_ = 0;

	uniform_distribution_accident_blood_ = uniform_distribution_accident_b;
	uniform_distribution_accident_time_ = uniform_distribution_accident_t;

	geometric_distribution_needed_blood_ = geometric_distribution_b;

	exponential_distribution_normal_order_ = exponential_distribution_order_n;
	exponential_distribution_patient_time_ = exponential_distribution_patient;
	exponential_distribution_donor_time_ = exponential_distribution_donor;

	normal_distribution_emergency_order_ = normal_distribution_order_e;


	r_ = 15; // próg jednostek krwi zamówienie normalnego [jednostek krwi]
	n_ = 20; // liczba zamawianych jednostek krwi dla zamówienie normalnego [jednostek krwi]

	t1_ = 300; // czas wa¿noœci zamówionej krwi [jednostek czasu]
	t2_ = 500; // czas wa¿noœci krwi od dawcy [jednostek czasu]

	q_ = 11; // liczba zamawianych jednostek krwi dla zamówienie awaryjnego [jednostek krwi]

	tw_min_ = 15000; // dolna granica rozk³adu równomiernego
	tw_max_ = 16000; // górna granica rozk³adu równomiernego

	tk_min_ = 10; // dolna granica rozk³adu równomiernego
	tk_max_ = 20; // górna granica rozk³adu równomiernego

	temp_l_ = exponential_distribution_donor_time_->generate(l_lambda_);

	temp_p_ = exponential_distribution_patient_time_->generate(p_lambda_);
	temp_w_ = geometric_distribution_needed_blood_->generate(w_);

	temp_z_ = exponential_distribution_normal_order_->generate(z_lambda_);
	temp_q_ = normal_distribution_emergency_order_->generate(e_, ew2_);

	temp_tw_ = uniform_distribution_accident_time_->generate(tw_min_, tw_max_);
	temp_tk_ = uniform_distribution_accident_blood_->generate(tk_min_, tk_max_);

	blood_order_ = nullptr;
	blood_transfusion_ = nullptr;
}


void time::change_r(const uint16_t r)
{
	r_ = r;
}

void time::change_n(const uint16_t n)
{
	n_ = n;
}

void time::change_t1(const uint16_t t1)
{
	t1_ = t1;
}

void time::change_t2(const uint16_t t2)
{
	t2_ = t2;
}

void time::change_q(const uint16_t q)
{
	q_ = q;
}

void time::simulation(queue_of_patients* queue_patients, queue_of_blood* priority_queue_blood,
                      blood_donation_point* blood_point, const uint64_t initial_phase)
{
	blood_order_ = new blood_order(priority_queue_blood);
	blood_transfusion_ = new blood_transfusion(priority_queue_blood, queue_patients);
	auto last_accident = accident(priority_queue_blood, blood_point, temp_tk_);

	auto lock_order_normal = false;
	auto lock_order_emergency = false;

	add_event(new one_event(no_data, temp_l_, donor_blood_comming));

	add_event(new one_event(no_data, temp_tw_, is_accident));

	add_event(new one_event(no_data, temp_p_, is_patient));

	add_event(new one_event(no_data, initial_phase, clear_stats));

	do
	{
		doing_event(); // skok do nastepnego zdarzenia


		if (temp_[0] == 'y' || temp_[0] == 'Y')
		{
			std::cin.get();
		}



		/////////////////////////////////////////////////////// UTYLIZACJA ///////////////////////////////////////////////////////////		

		if (!line_time.empty() && line_time.top()->check_task(blood_delete))
		{
			delete_event();
			if (blood_point->availble_blood_in_system())
			{
				destruction_of_blood::execute(priority_queue_blood, blood_point, current_time_);
				statistics::save_in_file(blood_point->availble_blood_in_system(), current_time_, "avalible_blood.xls");
			
			}
			number_of_event_++;
		} //usuniecie przeterminowanej krwi

		/////////////////////////////////////////////////////// UTYLIZACJA ///////////////////////////////////////////////////////////		



		////////////////////////////////////////////////////// DAWCA ///////////////////////////////////////////////////////////		

		if (!line_time.empty() && line_time.top()->check_task(donor_blood_comming))
		{
			to_arise_donor(&id_donor_, &id_blood_,t2_).execute(priority_queue_blood, blood_point, current_time_);

			statistics::save_in_file(blood_point->availble_blood_in_system(), current_time_, "avalible_blood.xls");

			delete_event();
			number_of_event_++;

			temp_l_ = exponential_distribution_donor_time_->generate(l_lambda_);

			add_event(new one_event(no_data, current_time_ + t2_, blood_delete));

			add_event(new one_event(no_data, current_time_ + temp_l_, donor_blood_comming));
		} //przybycie dawcy 

		/////////////////////////////////////////////////////// DAWCA //////////////////////////////////////////////////////////////////

		/////////////////////////////////////////////////////// AWARYJNE ZAMOWIENIE ///////////////////////////////////////////////////////////		

		if (!line_time.empty() && line_time.top()->check_task(emergency_provision_blood_comming) && lock_order_emergency)
		{
			provision_of_blood(t1_).execute(priority_queue_blood, blood_point, &id_blood_, current_time_, q_);
			lock_order_emergency = false;
			number_of_emergency_orders_++;
			number_of_event_++;

			emergency_blood_ += q_;
			statistics::save_in_file(blood_point->availble_blood_in_system(), current_time_, "avalible_blood.xls");
			statistics::save_in_file(number_of_emergency_orders_, current_time_, "emergency_provision_blood.xls");

			delete_event();

			add_event(new one_event(no_data, current_time_ + t1_, blood_delete));
		} //przybycie awaryjnego zamowienia krwi

		/////////////////////////////////////////////////////// AWARYJNE ZAMOWIENIE ///////////////////////////////////////////////////////////		


		/////////////////////////////////////////////////////// NORMALNE ZAMOWIENIE ///////////////////////////////////////////////////////////		

		if (!line_time.empty() && line_time.top()->check_task(normal_provision_blood_comming) && lock_order_normal)
		{
			delete_event();
			provision_of_blood(t1_).execute(priority_queue_blood, blood_point, &id_blood_, current_time_, n_);
			lock_order_normal = false;
			number_of_orders_++;
			number_of_event_++;

			statistics::save_in_file(blood_point->availble_blood_in_system(), current_time_, "avalible_blood.xls");
			statistics::save_in_file(number_of_orders_, current_time_, "normal_provision_blood.xls");

			add_event(new one_event(no_data, current_time_ + t1_, blood_delete));
		} //przybycie normalnego zamowienia krwi	

		if (!line_time.empty() && priority_queue_blood->lack_of_blood())

			if (blood_order_->execute(current_time_, lock_order_normal, temp_z_, this))
			{
				temp_z_ = exponential_distribution_normal_order_->generate(z_lambda_);
				number_of_event_++;
				lock_order_normal = true;
			} //zamownienie krwi i okreslenie kiedy przyjedzie

		/////////////////////////////////////////////////////// NORMALNE ZAMOWIENIE ///////////////////////////////////////////////////////////	

		/////////////////////////////////////////////////////// PACJENT //////////////////////////////////////////////////////////////////////	

		if (!line_time.empty() && line_time.top()->check_task(is_patient))
		{		
	//		statistics::save_in_file(blood_point->availble_blood_in_system(), current_time_, "avalible_blood.xls");
	//		statistics::save_in_file(queue_patients->size_of_queue(), current_time_, "queue_patients.xls");
			delete_event();
			to_arise_patient(&id_patient_, temp_w_).execute(queue_patients);

			statistics::save_in_file(temp_w_, current_time_, "new_patient.xls");
			number_of_event_++;

			temp_p_ = exponential_distribution_patient_time_->generate(p_lambda_);

			temp_w_ = geometric_distribution_needed_blood_->generate(w_);

			add_event(new one_event(no_data, current_time_ + temp_p_, is_patient));
			statistics::save_in_file(queue_patients->size_of_queue(), current_time_, "queue_patients.xls");
		} // przybycie nowego pacjenta


		/////////////////////////////////////////////////////// PACJENT //////////////////////////////////////////////////////////////////////	


		/////////////////////////////////////////////////////// TRANSFUZJA //////////////////////////////////////////////////////////////////////	

		if (blood_transfusion_->check())
		{
			number_of_event_ += queue_patients->size_of_queue();
			used_blood_ += blood_transfusion_->execute(blood_point);
			number_of_event_ -= queue_patients->size_of_queue();

			if (!queue_patients->no_patients() && queue_patients->first_patient()->check_its_condition())
				if (blood_transfusion_->check() && emergency_blood_order::execute(current_time_, lock_order_emergency, temp_q_,
				                                                                  this)
				)
				{
					number_of_event_++;
					lock_order_emergency = true;
					temp_q_ = normal_distribution_emergency_order_->generate(e_, ew2_);
				} //zamowienie krwi i okreslenie kiedy przyjedzie

			statistics::save_in_file(queue_patients->size_of_queue(), current_time_, "queue_patients.xls");
		} // przybycie nowego pacjenta


		/////////////////////////////////////////////////////// TRANZFUZJA //////////////////////////////////////////////////////////////////////	


		/////////////////////////////////////////////////////// WYPADEK //////////////////////////////////////////////////////////////////////	

		if (!line_time.empty() && line_time.top()->check_task(is_accident))
		{
			delete_event();

			last_accident = accident(priority_queue_blood, blood_point, temp_tk_);

			used_blood_accident_ += last_accident.execute(&number_of_accident_);
			number_of_event_++;

			statistics::save_in_file(blood_point->availble_blood_in_system(), current_time_, "avalible_blood.xls");
			statistics::save_in_file(temp_tk_, current_time_, "accident.xls");

			temp_tw_ = uniform_distribution_accident_time_->generate(tw_min_, tw_max_);
			temp_tk_ = uniform_distribution_accident_blood_->generate(tk_min_, tk_max_);

			add_event(new one_event(no_data, current_time_ + temp_tw_, is_accident));
		} // zdarzenie wypadek
		/////////////////////////////////////////////////////// WYPADEK //////////////////////////////////////////////////////////////////////	


		/////////////////////////////////////////////////////// KREW AWARYJNA-WYPADEK //////////////////////////////////////////////////////////////////////	


		if (!last_accident.accident_done())
		{
			used_blood_accident_ += last_accident.pop_blood();
			number_of_event_++;

			if (!last_accident.accident_done() && emergency_blood_order::execute(current_time_, lock_order_emergency, temp_q_,
			                                                                     this))
			{
				number_of_event_++;
				lock_order_emergency = true;
				temp_q_ = normal_distribution_emergency_order_->generate(e_, ew2_);
			} //zamowienie krwi i okreslenie kiedy przyjedzie 
			statistics::save_in_file(blood_point->availble_blood_in_system(), current_time_, "avalible_blood.xls");
		} // przybycie nowego pacjenta
		/////////////////////////////////////////////////////// KREW AWARYJNA-WYPADEK //////////////////////////////////////////////////////////////////////	


		if (number_of_event_ % 10000 == 0)
			std::cout << "wait..." << std::endl;

		/////////////////////////////////////////////////////// FAZA POCZATKOWA //////////////////////////////////////////////////////////////////////	

		if (!line_time.empty() && line_time.top()->check_task(clear_stats))
		{
			delete_event();
			id_donor_ = 0;
			id_patient_ = 0;
			used_blood_ = 0;
			number_of_accident_ = 0;
			used_blood_accident_ = 0;
			number_of_orders_ = 0;
			number_of_emergency_orders_ = 0;
			number_of_event_ = 0;
			emergency_blood_ = 0;
			priority_queue_blood->reset_stats();
		} // wyczyszczenie statystyk fazy pocz¹tkowej




		/////////////////////////////////////////////////////// FAZA POCZATKOWA //////////////////////////////////////////////////////////////////////	
	}
	while (current_time_ < finish_time_ && id_patient_ < number_of_patient_);

	statistics::print_in_terminal(id_donor_, id_patient_, used_blood_, number_of_accident_, used_blood_accident_,
	                              priority_queue_blood->deleted_blood_queue(),
	                              number_of_orders_, number_of_emergency_orders_, n_, r_, ap_, current_time_,
	                              number_of_event_,
	                              priority_queue_blood->created_blood(), emergency_blood_);

	statistics::print_to_file(id_donor_, id_patient_, used_blood_, number_of_accident_, used_blood_accident_,
	                          priority_queue_blood->deleted_blood_queue(),
	                          number_of_orders_, number_of_emergency_orders_, n_, r_, ap_, current_time_, number_of_event_,
	                          priority_queue_blood->created_blood(), emergency_blood_);
}
