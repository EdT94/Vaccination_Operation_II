#include "Clinic.h"
#include "Appointment.h"
#include "MedicalWorker.h"

int Clinic::current_id = 0;

Clinic::Clinic(const string& name, const Address& address) : id(++current_id), address(address.getDistrict(), address.getStreet(), address.getHouseNum())
{
	this->name = name;
}


Clinic::Clinic(Clinic&& other) : address(other.address)
{
	this->name = other.name;
	this->appointments = other.appointments;
	this->medicalWorkers = other.medicalWorkers;
	this->id = other.id;
}

int Clinic::getId() const
{
	return this->id;
}


const string Clinic::getName() const
{
	return this->name;
}


string Clinic::getName() 
{
	return this->name;
}


bool Clinic::setName(const string& name)
{
	this->name = name;
	return &this->name != nullptr;
}


const Address& Clinic:: getAddress() const
{
	return this->address;
}


int Clinic::getAppointmentsCount() const
{
	return this->appointments.size();
}



int Clinic::getMedicalWorkersCount() const
{
	return this->medicalWorkers.size();
}


const vector<Appointment*>& Clinic::getAppointments() const //#CH
{
	return this->appointments;
}


const vector<MedicalWorker*>& Clinic::getMedicalWorkers() const //#CH
{
	return this->medicalWorkers;
}


bool Clinic::addAppointment(Appointment* appointment)
{
	vector<Appointment*>::iterator itr = appointments.begin();
	vector<Appointment*>::iterator itrEnd = appointments.end();
	for (; itr != itrEnd; ++itr)
		if ((*itr)->getId() == appointment->getId())
			return false;

	this->appointments.push_back(appointment);
	return true;
}


void Clinic::setAppointments(vector<Appointment*> newAppointments) //#CH
{
	this->appointments.clear();
	this->appointments = newAppointments;
}



bool Clinic::addMedicalWorker(MedicalWorker& medicalWorker)
{
	vector<MedicalWorker*>::iterator itr = medicalWorkers.begin();
	vector<MedicalWorker*>::iterator itrEnd = medicalWorkers.end();
	for (; itr != itrEnd; ++itr)
		if ((*itr)->getId() == medicalWorker.getId())
			return false;

	medicalWorkers.push_back(&medicalWorker);
	medicalWorker.setClinic(this);
	return true;

}


bool Clinic::removeAppointment(const int appointmentId)
{

	vector<Appointment*>::iterator itr = this->appointments.begin();
	vector<Appointment*>::iterator itrEnd = this->appointments.end();
	Appointment* appointmentToDeleteFromLinkedList;
	for (; itr != itrEnd; ++itr)
	{
		if ((*itr)->getId() == appointmentId)
		{
			appointmentToDeleteFromLinkedList = *(itr);
			if ((*itr)->getVaccinee().removeAppointment(*appointmentToDeleteFromLinkedList))
			{
				if ((*itr)->getMedicalWorker() != nullptr)
				{
					if ((*itr)->getMedicalWorker()->removeAppointment(appointmentId))
					{
						appointments.erase(itr);
						return true;
					}
				}
			}
		}
	}
	return false;
}


bool Clinic::removeMedicalWorker(MedicalWorker& medicalWorker)
{
	int idToRemove = medicalWorker.getId();

	vector<MedicalWorker*>::iterator itr = medicalWorkers.begin();
	vector<MedicalWorker*>::iterator itrEnd = medicalWorkers.end();
	for (; itr != itrEnd; ++itr)
		if ((*itr)->getId() == idToRemove)
		{
			medicalWorkers.erase(itr);
			return true;
		}

	return false;
}



const Clinic& Clinic::operator=(Clinic&& other)
{
	if (this != &other)
	{
		std::swap(this->name, other.name);
		std::swap(this->address, other.address);
		std::swap(this->appointments, other.appointments);
		std::swap(this->medicalWorkers, other.medicalWorkers);
	}
	return *this;
}


bool Clinic::operator<(const Clinic& other) const
{
	return this->appointments.size() < other.appointments.size();
}


bool Clinic::operator>(const Clinic& other) const
{
	return !(*this < other);
}


bool Clinic::operator<=(const Clinic& other) const
{
	return *this < other || *this == other;
}


bool Clinic::operator>=(const Clinic& other) const
{
	return *this > other || *this == other;

}


bool Clinic::operator==(const Clinic& other) const
{
	return this->appointments.size() == other.appointments.size();
}


bool Clinic::operator!=(const Clinic& other) const
{
	return !(*this == other);
}


Clinic::~Clinic()
{	
	this->appointments.clear();
	this->medicalWorkers.clear();
}