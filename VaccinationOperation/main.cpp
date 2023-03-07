#include <iostream>
#include "main.h"
#include "VaccinationOperation.h"
#include "Appointment.h"
#include "Date.h"
#include "PrivateClinic.h"

using namespace std;


int menu(const int optionsCount, const char *options[]) {

    int option;
    cout << "\n\nChoose one of the following options:\n";
    for (int i = 0; i < optionsCount; i++) {
        cout << i << " - " << options[i] << "\n";
    }
    cout << "-1 - " << "Quit\n\n";
    cin >> option;
    return option;
}

int mainMenu() {
    return menu(MainMenuOptionsCount, MainMenuOptionsStr);
}

int addingMenu() {
    return menu(AddMenuOptionsCount, AddMenuOptionsStr);
}

int showingMenu() {
    return menu(ShowMenuOptionsCount, ShowMenuOptionsStr);
}

int main() {
    VaccinationOperation* vaccinationOperation = VaccinationOperation::getInstance();

    int choice, subChoice;
    do {
        choice = mainMenu();
        switch (choice) {
            case MENU_QUIT:
                cout << "\n\nGoodbye!";
                break;
            case eAddMenu:
                do {
                    subChoice = addingMenu();
                    switch (subChoice)
                    {
                        case MENU_QUIT:
                            subChoice = MENU_QUIT;
                            break;

                        case eAddClinic:
                        {
                            vaccinationOperation->addClinic(*initClinic());
                            break;
                        }

                        case eAddVaccinee:
                        {
                            vaccinationOperation->addVaccinee(*initVaccinee());
                            break;
                        }

                        case eAddWorker: 
                        {
                            vaccinationOperation->addMedicalWorker(*initMedicalWorker(*vaccinationOperation));
                            break;
                        }

                        default:
                        {
                            cout << "\nInvalid choice!\n";
                            break;
                        }
                            
                    }
                } while (subChoice != MENU_QUIT);
                break;
            case eShowMenu:
                do {
                    subChoice = showingMenu();
                    switch (subChoice)
                    {
                        case MENU_QUIT:
                            subChoice = MENU_QUIT;
                            break;

                        case eShowAllClinics:
                        {

                            vaccinationOperation->showAllClinics();
                            break;
                        }

                        case eShowAllAppointments:
                            vaccinationOperation->showAllAppointments();
                            break;

                        case eShowAllVaccinees:
                        {
                            vaccinationOperation->showAllVaccinees();
                            break;
                        }

                        case eShowAllMedicalWorkers:
                        {
                            vaccinationOperation->showAllMedicalWorkers();
                            break;
                         }
                        
                        default:
                        {
                            cout << "\nInvalid choice!\n";
                            break;
                        }
                    }
                } while (subChoice != MENU_QUIT);
                break;
            case eSetAppointment:
            {
                Appointment* appointment = initAppointment(*vaccinationOperation);
                if (appointment == nullptr)
                    cout << "There must be at least 1 clinic and 1 vaccinee for setting an appointment." << endl;
                else
                {
                    cout << "The appointment is set." << endl;
                    vaccinationOperation->setAppointment(appointment);
                }
                break;
            }
            case eCancelAppointment: 
            {
                int appointmentId;
                cout << "Enter appointment id:\n";
                cin >> appointmentId;
                if (!vaccinationOperation->cancelAppointment(appointmentId))
                    cout << "There is no appointment with this id\n";
                
                break;
            }
            case eShowAppointmentsForVaccinee: 
            {
                int vaccineeId;
                cout << "Enter vacinee id:\n";
                cin >> vaccineeId;
                if (!vaccinationOperation->getVaccinee(vaccineeId))
                    cout << "There is no vaccinee with id " << vaccineeId << "\n";
                else
                    vaccinationOperation->showAppointmentsForVaccinee(vaccineeId);
                break;
            }
            case eShowAppointmentsForWorker:
            {
                int medicalWorkerId;
                cout << "Enter worker id:\n";
                cin >> medicalWorkerId;
                vaccinationOperation->showAppointmentsForMedicalWorker(medicalWorkerId);
                break;
            }
            case eShowAppointmentsForClinic: 
            {
                int clinicId;
                cout << "Enter clinic id:\n";
                cin >> clinicId;
                vaccinationOperation->showAppointmentsForClinic(clinicId);
                break;
            }
            case eReplaceWorkerForAppointment: 
            {
                int appointmentId, newWorkerId;
                cout << "Enter appointment id:\n";
                cin >> appointmentId;
                cout << "Enter new worker id:\n";
                cin >> newWorkerId;
                if (!vaccinationOperation->replaceWorkerForAppointment(appointmentId, newWorkerId))
                    cout << "no appointment with such id or no worker with such id!\n"; 
                
                break;
            }
            case eShowClinicWorkers: 
            {
                int clinicId;
                cout << "Enter clinic id:\n";
                cin >> clinicId;
                vaccinationOperation->showWorkersForClinic(clinicId);
                break;
            }
            case eShowVaccineesOfRiskGroup: 
            {
                vaccinationOperation->showVaccineesOfRiskGroup(getRiskGroupFromUser());
                break;
            }

            case eShowVaccineesWithNoAppointments: 
            {
                vaccinationOperation->showVaccineesWithNoAppointments();
                break;
            }

            default:
            {
                cout << "\nInvalid choice!\n";
                break;
            }
        }

    } while (choice != MENU_QUIT);

}

Vaccinee::eRiskGroup getRiskGroupFromUser() {
    int riskGroupId;
    do {
        cout << "\nEnter risk group: \n";
        for (int i = 0; i < Vaccinee::eRiskGroup::RiskGroupCount; ++i) {
            cout << i << " - " << riskGroups[i] << "\n";
        }
        cin >> riskGroupId;
        if (riskGroupId < 0 || riskGroupId >= Vaccinee::eRiskGroup::RiskGroupCount) 
            cout << "\nInvalid choice!";
        
        else 
            return static_cast<Vaccinee::eRiskGroup>(riskGroupId);
        
    } while (riskGroupId < 0 || riskGroupId >= Vaccinee::eRiskGroup::RiskGroupCount);
    return Vaccinee::Invalid;
}

Clinic *initClinic() {
    string clinicName;
    cout << "Enter clinic name: ";
    cin >> clinicName;
    string clinicDistrict;
    cout << "Enter clinic district: ";
    cin >> clinicDistrict;
    string ClinicStreet;
    cout << "Enter clinic street: ";
    cin >> ClinicStreet;
    int clinicHouseNumber;
    cout << "Enter clinic house number: ";
    cin >> clinicHouseNumber;
    Address clinicAddress(clinicDistrict, ClinicStreet, clinicHouseNumber);
    string isPrivate;
    do
    {
        cout << "Is this clinic private? yes/no ";
        cin >> isPrivate;
        if (isPrivate == "yes")
        {
            int price;
            cout << "Enter clinic premium price: ";
            cin >> price;
            return new PrivateClinic(Clinic(clinicName, clinicAddress), price);
        }
        else if (isPrivate == "no")
            return new Clinic(clinicName, clinicAddress);

        cout << "Invalid input." << endl;

    } while (isPrivate != "yes" || isPrivate != "no");

    
        
    
}

Vaccinee *initVaccinee() {
    string vaccineeName;
    int phase;
    cout << "Enter vaccinee name: ";
    cin >> vaccineeName;
    Vaccinee::eRiskGroup vaccineeRiskGroup = getRiskGroupFromUser();
    cout << "Enter number of phases the vacinee has done: ";
    cin >> phase;

    return new Vaccinee(vaccineeName,phase, vaccineeRiskGroup);
}

MedicalWorker* initMedicalWorker(VaccinationOperation& vaccinationOperation) {
    string medicalWorkerName;
    cout << "Enter medical worker name: ";
    cin >> medicalWorkerName;
    cout << "Enter medical worker clinic id (enter -1 if worker is not assigned to any clinic): ";
    int medicalWorkerClinicId;
    cin >> medicalWorkerClinicId;
    if (medicalWorkerClinicId == -1)
        return new MedicalWorker(medicalWorkerName, nullptr);

    else if(vaccinationOperation.getClinic(medicalWorkerClinicId) == nullptr)
    {
        cout << "There is no clinic with this id, medical worker's clinic set to unknown" << endl;
        return new MedicalWorker(medicalWorkerName, nullptr);
    }
    
    else
        return new MedicalWorker(medicalWorkerName, vaccinationOperation.getClinic(medicalWorkerClinicId));
}

VaccineeWorker *initVaccineeWorker(VaccinationOperation& vaccinationOperation) {
    string vaccineeWorkerName;
    cout << "Enter vaccinee worker name: ";
    cin >> vaccineeWorkerName;
    cout << "Enter vaccinee worker clinic id(enter -1 if worker is not assigned to any clinic): ";
    int vaccineeWorkerClinicId;
    cin >> vaccineeWorkerClinicId;
    if (vaccineeWorkerClinicId == -1)
        return new VaccineeWorker(MedicalWorker(vaccineeWorkerName, nullptr), Vaccinee(vaccineeWorkerName));

    else if (vaccinationOperation.getClinic(vaccineeWorkerClinicId) == nullptr)
    {
        cout << "There is no clinic with this id, worker's clinic set to unknown" << endl;
        return new VaccineeWorker(MedicalWorker(vaccineeWorkerName, nullptr), Vaccinee(vaccineeWorkerName));
    }
        
    else
        return new VaccineeWorker(MedicalWorker(vaccineeWorkerName, vaccinationOperation.getClinic(vaccineeWorkerClinicId)), Vaccinee(vaccineeWorkerName));
    
}

Appointment *initAppointment(VaccinationOperation& vaccinationOperation) {
    Date appointmentDate;
    DateAdapter* dateAdapter;
    Clinic* appointmentClinic;
    Vaccinee* appointmentVaccinee;
    int appointmentClinicId;
    if (vaccinationOperation.getClinicsCount() == 0 || vaccinationOperation.getVaccineesCount() == 0)
        return nullptr;

    cout << "Enter a valid future appointment date: (day month year)";
    cin >> appointmentDate;
    if (!appointmentDate.checkDateValidation())
    {
        dateAdapter = new DateAdapter();
        cout << "Invalid date, appointment date set to " << *dateAdapter << endl;
        appointmentDate.setDay(dateAdapter->getDay());
        appointmentDate.setMonth(dateAdapter->getMonth());
        appointmentDate.setYear(dateAdapter->getYear());
    }

    do
    {
        cout << "Enter clinic id:";
        cin >> appointmentClinicId;
        appointmentClinic = vaccinationOperation.getClinic(appointmentClinicId);
        if(appointmentClinic == nullptr)
            cout << "There is no clinic with this id!\n";
    } while (appointmentClinic == nullptr);

    cout << "Enter medical worker id:";
    int appointmentWorkerId;
    cin >> appointmentWorkerId;
    MedicalWorker *appointmentWorker = vaccinationOperation.getMedicalWorkerFromClinic(appointmentWorkerId, appointmentClinicId);
    if (appointmentWorker == nullptr) 
        cout << "There is no medical worker with id: " << appointmentWorkerId << ", in clinic id: " << appointmentClinicId <<". no medical worker for this appointment." << endl;
 
    do
    {
        cout << "Enter vaccinee id:";
        int appointmentVaccineeId;
        cin >> appointmentVaccineeId;
        appointmentVaccinee = vaccinationOperation.getVaccinee(appointmentVaccineeId);
        if(appointmentVaccinee == nullptr)
            cout << "There is no vaccinee with this id" << endl;

    } while (appointmentVaccinee == nullptr);

    return new Appointment(appointmentDate, *appointmentClinic, *appointmentVaccinee, appointmentWorker);
    

}

