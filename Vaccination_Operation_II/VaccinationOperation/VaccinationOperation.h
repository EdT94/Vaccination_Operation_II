#ifndef VACOP_VACCINATIONOPERATION_H
#define VACOP_VACCINATIONOPERATION_H

#include "Clinic.h"
#include "Vaccinee.h"
#include "MedicalWorker.h"
#include <vector>

class VaccinationOperation 
{
private:
    vector<Clinic*> clinicsArr;
    vector<Vaccinee*> vaccineesArr;
    vector<MedicalWorker*> medicalWorkersArr;

    VaccinationOperation(const VaccinationOperation &other);

    VaccinationOperation &operator=(const VaccinationOperation& other);

    VaccinationOperation();

    VaccinationOperation(VaccinationOperation&& other);

    VaccinationOperation& operator=(VaccinationOperation&& other);

    static VaccinationOperation vaccinationOperation;


public:
    static VaccinationOperation* getInstance();

    ~VaccinationOperation();

    void addClinic(Clinic& clinic);

    void addVaccinee(Vaccinee& vaccinee);

    void addMedicalWorker(MedicalWorker& medicalWorker); 

    bool removeClinic(const int clinicId);

    bool removeVaccinee(const int vaccineeId);

    bool removeMedicalWorker(const int medicalWorkerId);

    Clinic* getClinic(const int clinicId);

    Vaccinee* getVaccinee(const int vaccineeId);

    MedicalWorker* getMedicalWorker(const int medicalWorkerId);

    void setAppointment(Appointment*appointment) ;

    bool cancelAppointment(const int appointmentId);

    void showAllAppointments() const;

    void showAllMedicalWorkers() const;

    void showAllVaccinees() const;

    void showAllClinics() const;

    void showAppointmentsForVaccinee(const int vaccineeId) const;

    void showAppointmentsForMedicalWorker(const int medicalWorkerId) const;

    void showAppointmentsForClinic(const int clinicId) const;

    bool replaceWorkerForAppointment(const int appointmentId, const int newWorkerId);

    void showWorkersForClinic(const int clinicId) const;

    void showVaccineesOfRiskGroup(Vaccinee::eRiskGroup riskGroup) const;

    void showVaccineesWithNoAppointments() const;

    MedicalWorker* getMedicalWorkerFromClinic(int appointmentWorkerId, int appointmentClinicId);

    const vector<Clinic*>& getClinicsArr();

    const vector<Vaccinee*>& getVaccineesArr();

    const vector<MedicalWorker*>& getMedicalWorkersArr();

    int getClinicsCount() const;

    int getVaccineesCount() const;

    int getMedicalWorkersCount() const;


};



#endif //VACOP_VACCINATIONOPERATION_H
