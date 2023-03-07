#ifndef VACOP_ADDRESS_H
#define VACOP_ADDRESS_H
using namespace std;

#include <ostream>

class Address 
{
private:
    string district;
    string street;
    int houseNum;

public:
    Address(const string& district, const string& street, const int houseNum);

    const string getDistrict() const;

    const string getStreet() const;
    
    const int getHouseNum() const;

    
    friend std::ostream& operator<<(std::ostream& os, const Address& address)
    {
        os << "district: " << address.district << ", street: " << address.street << ", house number: " << address.houseNum;
        return os;
    }
};


#endif //VACOP_ADDRESS_H
