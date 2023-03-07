#ifndef VACOP_CLINIC_H
#define VACOP_CLINIC_H

#include <ostream>
#include "Address.h"
#include "MedicalWorker.h"
#include <vector>
#include <algorithm>


using namespace std;

class Appointment;

class Clinic 
{

private:
    Clinic(const Clinic& other);

    const Clinic& operator=(const Clinic& other);


protected:
    static int current_id;
    int id;
    string name;
    Address address;
    vector<Appointment*> appointments;          
    vector<MedicalWorker*> medicalWorkers;


public:
    Clinic(const string& name, const Address& address);

    Clinic(Clinic&& other);

    const Clinic& operator=(Clinic&& other);

    int getId() const;

    bool addAppointment(Appointment* appointment);

    bool addMedicalWorker(MedicalWorker& medicalWorker);

    bool removeAppointment(const int appointmentId);

    bool removeMedicalWorker(MedicalWorker& medicalWorker);

    const string getName() const;

    string getName();

    bool setName(const string& name);

    const Address& getAddress() const;

    const vector<Appointment*>& getAppointments() const;

    void setAppointments(vector<Appointment*> newAppointments);

    const vector<MedicalWorker*>& getMedicalWorkers() const;

    //Abstract method
    virtual void toOs(ostream& os) const {}

    //Template method
    friend std::ostream& operator<<(std::ostream& os, Clinic& clinic)
    {
        os << "Clinic id: " << clinic.id << ", name: " << clinic.name << ", address: " << clinic.address << endl;
        if (clinic.medicalWorkers.size() != 0)
        {

            os << clinic.medicalWorkers.size() << " medical workers:" << endl;
            vector<MedicalWorker*>::iterator itr = clinic.medicalWorkers.begin();      
            vector<MedicalWorker*>::iterator itrEnd = clinic.medicalWorkers.end();      
            for (; itr != itrEnd; ++itr)                                
                os << **itr << endl;                                      
        }
        clinic.toOs(os);
        return os;
    }

    int getAppointmentsCount() const;

    int getMedicalWorkersCount() const;

    bool operator<(const Clinic& other) const;

    bool operator>(const Clinic& other) const;

    bool operator<=(const Clinic& other) const;

    bool operator>=(const Clinic& other) const;

    bool operator==(const Clinic& other) const;

    bool operator!=(const Clinic& other) const;

    virtual ~Clinic();
};


#endif //VACOP_CLINIC_H
