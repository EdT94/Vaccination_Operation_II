#include "MedicalWorker.h"
#include "Appointment.h"
#include "Clinic.h"

MedicalWorker::MedicalWorker(const string& name, Clinic* clinic) : Person(name)
{
	this->setClinic(clinic);
}

MedicalWorker::MedicalWorker(const MedicalWorker& base) : Person(base.getName())
{
	this->setClinic(base.getClinic());
}

MedicalWorker::MedicalWorker(MedicalWorker&& other) : Person(other.name)
{
	this->name = other.name;
	this->appointmentsArr = other.appointmentsArr;
	this->clinic = other.clinic;
	other.clinic = nullptr;

}

void MedicalWorker::setClinic(Clinic* clinic) 
{
	if (this->clinic != clinic)
	{
		this->clinic = clinic;
		if (this->clinic != nullptr)
			this->clinic->addMedicalWorker(*this);
	}
}


bool MedicalWorker::addAppointment(Appointment* appointment)
{
	vector<Appointment*>::iterator itr = appointmentsArr.begin();      //#CH
	vector<Appointment*>::iterator itrEnd = appointmentsArr.end();       //#CH
	for (; itr != itrEnd; ++itr)                                //#CH
		if ((*itr)->getId() == appointment->getId())
			return false;

	appointmentsArr.push_back(appointment);
	return true;
}

//void MedicalWorker::setAppointmentsCount(const int newAppointmentsCount)
//{
//	this->appointmentsCount = newAppointmentsCount;
//}



bool MedicalWorker::removeAppointment(const int appointment)
{
	vector<Appointment*>::iterator itr = appointmentsArr.begin();      //#CH
	vector<Appointment*>::iterator itrEnd = appointmentsArr.end();       //#CH
	for (; itr != itrEnd; ++itr)                                //#CH
		if ((*itr)->getId() == appointment)
		{
			appointmentsArr.erase(itr);
			return true;
		}

	return false;
}


const vector<Appointment*>& MedicalWorker::getAppointmentsArr() const
{
	return appointmentsArr;
}

void MedicalWorker::setAppointmentsArr(vector<Appointment*> newAppointmentsArr)
{
	this->appointmentsArr = newAppointmentsArr;
}

Clinic* MedicalWorker::getClinic() const
{
	return this->clinic;
}

int MedicalWorker::getAppointmentsCount() const
{
	return this->appointmentsArr.size();
}

const MedicalWorker& MedicalWorker::operator=(MedicalWorker&& other)
{
	if (this != &other)
	{
		std::swap(this->name, other.name);
		std::swap(this->appointmentsArr, other.appointmentsArr);
		std::swap(this->clinic, other.clinic);
	}
	return *this;
}

MedicalWorker::~MedicalWorker()
{
	this->appointmentsArr.clear();;
}