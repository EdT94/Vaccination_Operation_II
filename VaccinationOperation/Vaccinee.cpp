#include "Vaccinee.h"
#include "Appointment.h"
using namespace std;

Vaccinee::Vaccinee(const string& name, int phasesComplete, eRiskGroup riskGroup) : Person(name)
{
	this->phasesComplete = phasesComplete;
	this->riskGroup = riskGroup;
	this->appointmentsCount = 0;
	this->appointments = new LinkedList<Appointment*>;
}

Vaccinee::Vaccinee(const Vaccinee& other) : Person(other.name)
{
	this->appointmentsCount = other.appointmentsCount;
	this->phasesComplete = other.phasesComplete;
	this->riskGroup = other.riskGroup;

	this->appointments = other.appointments;
}


Vaccinee::Vaccinee(Vaccinee&& other) : Person(other.name) 
{
	this->name = other.name;

	this->appointments = other.appointments;
	this->riskGroup = other.riskGroup;
	this->phasesComplete = other.phasesComplete;
	this->appointmentsCount = other.appointmentsCount;
}



bool Vaccinee::removeAppointment(Appointment& appointment)
{
	if (this->appointments->deleteNode(&appointment))
	{
		this->appointmentsCount--;
		return true;
	}
	return false;	
}

void Vaccinee::setAppointments(LinkedList<Appointment*>* newAppointmentsArr)
{
	this->appointments = newAppointmentsArr;
}


int Vaccinee::getPhasesComplete() const
{
	return this->phasesComplete;
}


LinkedList<Appointment*>* Vaccinee::getAppointments() const
{
	return this->appointments;
}


void Vaccinee::setRiskGroup(eRiskGroup riskGroup)
{
	this->riskGroup = riskGroup;
}

int Vaccinee::getAppointmentsCount() const
{
	return this->appointmentsCount;
}


void Vaccinee::setPhasesComplete(const int phasesComplete)
{
	this->phasesComplete = phasesComplete;
}

void Vaccinee::setAppointmentsCount(const int newAppointmentsCount)
{
	this->appointmentsCount = newAppointmentsCount;
}

bool Vaccinee::addAppointment(Appointment* appointment)
{
	if (this->appointments->search(appointment->getId()))
		return false;

	this->appointments->insert(appointment);
	this->appointmentsCount++;
	return true;

	
}


const Vaccinee& Vaccinee::operator=(Vaccinee&& other)
{
	if (this != &other)
	{
		std::swap(this->name, other.name);
		std::swap(this->appointments, other.appointments);
		this->riskGroup = other.riskGroup;
		this->phasesComplete = other.phasesComplete;
		this->appointmentsCount = other.appointmentsCount;
	}
	return *this;
}

