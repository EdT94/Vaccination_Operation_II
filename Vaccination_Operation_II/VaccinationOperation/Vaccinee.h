#ifndef VACOP_VACCINEE_H
#define VACOP_VACCINEE_H

#include <ostream>
#include "Person.h"
#include "LinkedList.h"
using namespace std;
class Appointment;

static const char* riskGroups[5] = { "Regular", "High", "Max"," RiskGroupCount", "Invalid" };

class Vaccinee : virtual public Person 
{

private: 
    const Vaccinee &operator=(const Vaccinee &other);

public:
    enum eRiskGroup {
        Regular, High, Max,
        RiskGroupCount,
        Invalid
    };
    

protected:
    LinkedList<Appointment*>* appointments;
    int phasesComplete;
    eRiskGroup riskGroup;
    int appointmentsCount;

public:
    Vaccinee(const string& name, int phasesComplete = 0, eRiskGroup riskGroup = Regular);

    Vaccinee(const Vaccinee& other);

    Vaccinee(Vaccinee &&other);

    const Vaccinee &operator=(Vaccinee &&other);

    int getPhasesComplete() const;

    void setPhasesComplete(const int phasesComplete);

    bool addAppointment(Appointment* appointment);

    bool removeAppointment(Appointment& appointment);

    LinkedList<Appointment*>* getAppointments() const;

    eRiskGroup getRiskGroup() const { return this->riskGroup;}

    void setRiskGroup(eRiskGroup riskGroup);

    void setAppointments(LinkedList<Appointment*>* newAppointmentsArr);

    int getAppointmentsCount() const;

    void setAppointmentsCount(const int newAppointmentsCount);

    virtual void toOs2(ostream& os) const {}

    virtual void toOs(ostream& os) const 
    {
        os<< ", risk group: " << riskGroups[riskGroup] << ", phases complete : " << phasesComplete
            << ", appointments count: " << appointmentsCount <<endl;
    }

    
};


#endif //VACOP_VACCINEE_H
