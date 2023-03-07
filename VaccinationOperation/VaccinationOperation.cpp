#include "VaccinationOperation.h"
#include "Appointment.h"
#include "Vaccinee.h"
#include "MedicalWorker.h"

VaccinationOperation VaccinationOperation::vaccinationOperation;


VaccinationOperation::VaccinationOperation() {}



VaccinationOperation* VaccinationOperation::getInstance()
{
	return &vaccinationOperation;
}



void VaccinationOperation::addClinic(Clinic& clinic)
{
	this->clinicsArr.push_back(&clinic);
}


void VaccinationOperation::addVaccinee(Vaccinee& vaccinee)
{
	this->vaccineesArr.push_back(&vaccinee);
}


void VaccinationOperation::addMedicalWorker(MedicalWorker& medicalWorker)
{
	this->medicalWorkersArr.push_back(&medicalWorker);
}


bool VaccinationOperation::removeClinic(const int clinicId)
{
	vector<Clinic*>::iterator itr = this->clinicsArr.begin();      
	vector<Clinic*>::iterator itrEnd = this->clinicsArr.end();       
	for (; itr != itrEnd; ++itr)
		if ((*itr)->getId() == clinicId)
		{
			this->clinicsArr.erase(itr);
			return true;
		}
	return false;
}


bool VaccinationOperation::removeVaccinee(const int vaccineeId)
{
	vector<Vaccinee*>::iterator itr = this->vaccineesArr.begin();      
	vector<Vaccinee*>::iterator itrEnd = this->vaccineesArr.end();       
	for (; itr != itrEnd; ++itr)
		if ((*itr)->getId() == vaccineeId)
		{
			this->vaccineesArr.erase(itr);
			return true;
		}
	return false;
}


bool VaccinationOperation::removeMedicalWorker(const int medicalWorkerId)
{
	vector<MedicalWorker*>::iterator itr = this->medicalWorkersArr.begin();      
	vector<MedicalWorker*>::iterator itrEnd = this->medicalWorkersArr.end();       
	for (; itr != itrEnd; ++itr)
		if ((*itr)->getId() == medicalWorkerId)
		{
			this->medicalWorkersArr.erase(itr);
			return true;
		}
	return false;

}


Clinic* VaccinationOperation::getClinic(const int clinicId)
{
	vector<Clinic*>::iterator itr = this->clinicsArr.begin();      
	vector<Clinic*>::iterator itrEnd = this->clinicsArr.end();       
	for (; itr != itrEnd; ++itr)
		if ((*itr)->getId() == clinicId)
			return *itr;

	return nullptr;
}


Vaccinee* VaccinationOperation::getVaccinee(const int vaccineeId)
{
	vector<Vaccinee*>::iterator itr = this->vaccineesArr.begin();      
	vector<Vaccinee*>::iterator itrEnd = this->vaccineesArr.end();       
	for (; itr != itrEnd; ++itr)
		if ((*itr)->getId() == vaccineeId)
			return *itr;

	return nullptr;
}


MedicalWorker* VaccinationOperation::getMedicalWorker(const int medicalWorkerId)
{
	vector<MedicalWorker*>::const_iterator itr = this->medicalWorkersArr.begin();      
	vector<MedicalWorker*>::const_iterator itrEnd = this->medicalWorkersArr.end();      
	for (; itr != itrEnd; ++itr)
		if ((*itr)->getId() == medicalWorkerId)
			return *itr;

	return nullptr;
}



MedicalWorker* VaccinationOperation::getMedicalWorkerFromClinic(int appointmentWorkerId, int appointmentClinicId)
{
	Clinic* clinic = this->getClinic(appointmentClinicId);
	if (clinic == nullptr)
		return nullptr;

	vector<MedicalWorker*>::const_iterator itr = (clinic->getMedicalWorkers()).begin();     
	vector<MedicalWorker*>::const_iterator itrEnd = (clinic->getMedicalWorkers()).end();       
	for (; itr != itrEnd; ++itr)
		if ((*itr)->getId() == appointmentWorkerId)
			return *itr;

	return nullptr;
}



void VaccinationOperation::setAppointment(Appointment* appointment)
{
	int workerId;
	int clinicId = appointment->getClinic().getId();
	int vaccineeId = appointment->getVaccinee().getId();
	if (appointment->getMedicalWorker() == nullptr)
		workerId = -1;
	else if (appointment->getMedicalWorker()->getId() == NULL)
		workerId = -1;
	else
		workerId = appointment->getMedicalWorker()->getId();

	vector<Clinic*>::iterator itr = this->clinicsArr.begin();
	vector<Clinic*>::iterator itrEnd = this->clinicsArr.end();
	for (; itr != itrEnd; ++itr)
		if ((*itr)->getId() == clinicId)
			(*itr)->addAppointment(appointment);

	vector<Vaccinee*>::iterator itr1 = this->vaccineesArr.begin();
	vector<Vaccinee*>::iterator itrEnd1 = this->vaccineesArr.end();
	for (; itr1 != itrEnd1; ++itr1)
		if ((*itr1)->getId() == vaccineeId)
			(*itr1)->addAppointment(appointment);

	vector<MedicalWorker*>::iterator itr2 = this->medicalWorkersArr.begin();
	vector<MedicalWorker*>::iterator itrEnd2 = this->medicalWorkersArr.end();
	for (; itr2 != itrEnd2; ++itr2)
		if ((*itr2)->getId() == workerId)
			(*itr2)->addAppointment(appointment);

}


bool VaccinationOperation::cancelAppointment(const int appointmentId)
{
	vector<Appointment*> currentAppointment;

	vector<Clinic*>::iterator itr = this->clinicsArr.begin();
	vector<Clinic*>::iterator itrEnd = this->clinicsArr.end();


	for (; itr != itrEnd; ++itr)
	{
		currentAppointment = (*itr)->getAppointments();
		vector<Appointment*>::iterator itr1 = currentAppointment.begin();      
		vector<Appointment*>::iterator itrEnd1 = currentAppointment.end();       
		for (; itr1 != itrEnd1; ++itr1)
		{
			if ((*itr1)->getId() == appointmentId)
			{
				(*itr)->removeAppointment(appointmentId);
				return true;
			}

		}
	}
	return false;
}




void VaccinationOperation::showAllAppointments() const
{
	cout << "All appointments:\n";
	vector<Appointment*> currentAppointment;

	vector<Clinic*>::const_iterator itr = this->clinicsArr.begin();      //#CH
	vector<Clinic*>::const_iterator itrEnd = this->clinicsArr.end();       //#CH
	for (; itr != itrEnd; ++itr)
	{
		currentAppointment = (*itr)->getAppointments();
		vector<Appointment*>::const_iterator itr1 = currentAppointment.begin();      //#CH
		vector<Appointment*>::const_iterator itrEnd1 = currentAppointment.end();       //#CH
		for (; itr1 != itrEnd1; ++itr1)
			cout << **itr1 << endl;
	}

}


void VaccinationOperation::showAllMedicalWorkers() const
{
	if (this->medicalWorkersArr.size() == 0)
	{
		cout << "There is no medical workers" << endl;
		return;
	}

	cout << "\n\nAll medical workers:\n";
	vector<MedicalWorker*>::const_iterator itr = this->medicalWorkersArr.begin();     //#CH
	vector<MedicalWorker*>::const_iterator itrEnd = this->medicalWorkersArr.end();       //#CH
	for (; itr != itrEnd; ++itr)
		cout << **itr << endl;

}



void VaccinationOperation::showAllVaccinees() const
{
	if (this->vaccineesArr.size() == 0)
	{
		cout << "There is no vaccinees" << endl;
		return;
	}

	cout << "\n\nAll vaccinees:\n";
	vector<Vaccinee*>::const_iterator itr = this->vaccineesArr.begin();     //#CH
	vector<Vaccinee*>::const_iterator itrEnd = this->vaccineesArr.end();       //#CH
	for (; itr != itrEnd; ++itr)
		cout << **itr << endl;
}



void VaccinationOperation::showAllClinics() const
{
	if (this->clinicsArr.size() == 0)
	{
		cout << "There is no clinics" << endl;
		return;
	}

	cout << "\n\nAll clinics:\n";
	vector<Clinic*>::const_iterator itr = this->clinicsArr.begin();     //#CH
	vector<Clinic*>::const_iterator itrEnd = this->clinicsArr.end();       //#CH
	for (; itr != itrEnd; ++itr)
		cout << **itr << endl;
}



void VaccinationOperation::showAppointmentsForVaccinee(const int vaccineeId) const
{
	LinkedList<Appointment*>* currentVaccineeAppoinments;
	int numOfAppointments = -1;

	vector<Vaccinee*>::const_iterator itr = this->vaccineesArr.begin();      
	vector<Vaccinee*>::const_iterator itrEnd = this->vaccineesArr.end();       
	for (; itr != itrEnd; ++itr)
	{
		if ((*itr)->getId() == vaccineeId)
		{
			currentVaccineeAppoinments = (*itr)->getAppointments();
			numOfAppointments = (*itr)->getAppointmentsCount();
			if (numOfAppointments == -1 || numOfAppointments == 0)
			{
				cout << "There is no appointments for this vaccinee" << endl;
				return;
			}
			else
			{
				cout << "All appointments for vaccinee id " << vaccineeId << " are:\n";
				currentVaccineeAppoinments->display();
				return;
			}
		}
	}

	

	
}



void VaccinationOperation::showAppointmentsForMedicalWorker(const int medicalWorkerId) const
{
	vector<Appointment*> currentAppointments;
	int numOfAppointments = -1;

	vector<MedicalWorker*>::const_iterator itr = this->medicalWorkersArr.begin();      
	vector<MedicalWorker*>::const_iterator itrEnd = this->medicalWorkersArr.end();       
	for (; itr != itrEnd; ++itr)
	{
		if ((*itr)->getId() == medicalWorkerId)
		{
			currentAppointments = (*itr)->getAppointmentsArr();
			numOfAppointments = (*itr)->getAppointmentsCount();
			break;
		}
	}

	if (numOfAppointments == -1 || numOfAppointments == 0)
	{
		cout << "There is no appointments for this medical doctor" << endl;
		return;
	}

	cout << "All appointments for medical's doctor id " << medicalWorkerId << " are:\n";
	vector<Appointment*>::const_iterator itr1 = currentAppointments.begin();      
	vector<Appointment*>::const_iterator itrEnd1 = currentAppointments.end();       
	for (; itr1 != itrEnd1; ++itr1)
		cout << **itr1 << endl;

}


void VaccinationOperation::showAppointmentsForClinic(const int clinicId) const
{
	vector<Appointment*> currentAppointments;
	int numOfAppointments = -1;

	vector<Clinic*>::const_iterator itr = this->clinicsArr.begin();      
	vector<Clinic*>::const_iterator itrEnd = this->clinicsArr.end();       
	for (; itr != itrEnd; ++itr)
	{
		if ((*itr)->getId() == clinicId)
		{
			currentAppointments = (*itr)->getAppointments();
			numOfAppointments = (*itr)->getAppointmentsCount();
			break;
		}
	}

	if (numOfAppointments == -1 || numOfAppointments == 0)
	{
		cout << "There is no appointments for this clinic" << endl;
		return;
	}

	cout << "All appointments for clinic id " << clinicId << " are:\n";
	vector<Appointment*>::const_iterator itr1 = currentAppointments.begin();      
	vector<Appointment*>::const_iterator itrEnd1 = currentAppointments.end();       
	for (; itr1 != itrEnd1; ++itr1)
		cout << **itr1 << endl;

}



bool VaccinationOperation::replaceWorkerForAppointment(const int appointmentId, const int newWorkerId)
{

	vector<Appointment*> currentAppointments;

	vector<MedicalWorker*>::const_iterator itr = this->medicalWorkersArr.begin();      
	vector<MedicalWorker*>::const_iterator itrEnd = this->medicalWorkersArr.end();      
	for (; itr != itrEnd; ++itr)
	{
		currentAppointments = (*itr)->getAppointmentsArr();
		vector<Appointment*>::const_iterator itr1 = currentAppointments.begin();      
		vector<Appointment*>::const_iterator itrEnd1 = currentAppointments.end();       
		for (; itr1 != itrEnd1; ++itr1)
		{

			if ((*itr1)->getId() == appointmentId)
			{
				(*itr1)->setMedicalWorker(*itr);
				return true;
			}

		}
	}
	return false;
}



void VaccinationOperation::showWorkersForClinic(const int clinicId) const
{
	cout << "All medical workers for clinic id " << clinicId << " are:\n";
	vector<MedicalWorker*> medicalWorkers;

	vector<Clinic*>::const_iterator itr = this->clinicsArr.begin();      
	vector<Clinic*>::const_iterator itrEnd = this->clinicsArr.end();       
	for (; itr != itrEnd; ++itr)
	{
		if ((*itr)->getId() == clinicId)
		{
			medicalWorkers = (*itr)->getMedicalWorkers();
			vector<MedicalWorker*>::const_iterator itr1 = medicalWorkers.begin();      
			vector<MedicalWorker*>::const_iterator itrEnd1 = medicalWorkers.end();       
			for (; itr1 != itrEnd1; ++itr1)
				cout << **itr1 << endl;
			break;
		}
	}
}



void VaccinationOperation::showVaccineesOfRiskGroup(Vaccinee::eRiskGroup riskGroup) const
{
	cout << "All vaccinees of risk group: " << riskGroups[riskGroup] << " are:\n";
	vector<Vaccinee*>::const_iterator itr = vaccineesArr.begin();      
	vector<Vaccinee*>::const_iterator itrEnd = vaccineesArr.end();       
	for (; itr != itrEnd; ++itr)
		if ((*itr)->getRiskGroup() == riskGroup)
			cout << **itr << endl;
}


void VaccinationOperation::showVaccineesWithNoAppointments() const
{
	cout << "All vaccinees with no appointments are: \n";
	vector<Vaccinee*>::const_iterator itr = vaccineesArr.begin();      
	vector<Vaccinee*>::const_iterator itrEnd = vaccineesArr.end();       
	for (; itr != itrEnd; ++itr)
		if ((*itr)->getAppointmentsCount() == 0)
			cout << **itr << endl;
}

const vector<Clinic*>& VaccinationOperation::getClinicsArr()
{
	return this->clinicsArr;
}



const vector<Vaccinee*>& VaccinationOperation::getVaccineesArr()
{
	return this->vaccineesArr;
}



const vector<MedicalWorker*>& VaccinationOperation::getMedicalWorkersArr()
{
	return this->medicalWorkersArr;
}


int VaccinationOperation::getClinicsCount() const
{
	return this->clinicsArr.size();
}


int VaccinationOperation::getVaccineesCount() const
{
	return this->vaccineesArr.size();
}


int VaccinationOperation::getMedicalWorkersCount() const
{
	return this->medicalWorkersArr.size();
}


VaccinationOperation::~VaccinationOperation()
{
	this->clinicsArr.clear();
	this->vaccineesArr.clear();
	this->medicalWorkersArr.clear();
}
