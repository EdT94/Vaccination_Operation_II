#ifndef VACOP_MEDICALWORKER_H
#define VACOP_MEDICALWORKER_H

#include <ostream>
#include "Person.h"
#include <vector>
using namespace std;

class Clinic;

class Appointment;

class MedicalWorker : virtual public Person 
{

private:
    const MedicalWorker& operator=(const MedicalWorker& other);
    
protected:
    vector<Appointment*> appointmentsArr;
    Clinic* clinic;

public:
    MedicalWorker(const string& name, Clinic *clinic = nullptr);

    MedicalWorker(const MedicalWorker& base);

    const MedicalWorker& operator=(MedicalWorker&& other);

    MedicalWorker(MedicalWorker&& other);

    virtual ~MedicalWorker();

    bool addAppointment(Appointment *appointment);

    bool removeAppointment(const int appointmentId);

    const vector<Appointment*>& getAppointmentsArr() const;

    Clinic* getClinic() const;

    void setClinic(Clinic *clinic);

    void setAppointmentsCount(const int newAppointmentsCount);

    void setAppointmentsArr(vector<Appointment*> newAppointmentsArr);

    int getAppointmentsCount() const;

    virtual void toOs(ostream& os) const 
    {
    
        os << " ,number of appointments: " << appointmentsArr.size();
        if (this->clinic == nullptr)
            os << ", is unemployed";
        os << endl;      
    }

  

};


#endif //VACOP_MEDICALWORKER_H
