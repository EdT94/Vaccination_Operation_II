#ifndef VACOP_DATE__H
#define VACOP_DATE__H

#include <iostream>

#define MIN_APPOINTMENT_DAY 1
#define MIN_APPOINTMENT_MONTH 7
#define MIN_APPOINTMENT_YEAR 2022

class AbstractDate 
{
public:
    virtual int getDay() const = 0;
    virtual int getMonth() const = 0;
    virtual int getYear() const = 0;
};

class Date: public AbstractDate 
{
protected:
    int day;
    int month;
    int year;

public:
    Date() = default;

    Date(int day, int month, int year);

    int getDay() const;

    int getMonth() const;

    int getYear() const;

    bool setDay(const int day);

    bool setMonth(const int month);

    bool setYear(const int year);

    bool checkDateValidation();

    bool operator==(const Date& other) const;

    bool operator!=(const Date& other) const;

    bool operator<(const Date& other) const;

    bool operator>(const Date& other) const;

    bool operator<=(const Date& other) const;

    bool operator>=(const Date& other) const;


    friend std::ostream& operator<<(std::ostream& os, const Date& date)
    {
        os  << date.day << "/" << date.month << "/" << date.year;
        return os;
    }

    friend std::istream& operator>>(std::istream& is, Date& date)
    {
        is >> date.day >> date.month >> date.year;
        return is;
    }

};


class DateAdapter : public AbstractDate, private Date
{
public:
    DateAdapter() : Date(MIN_APPOINTMENT_DAY, MIN_APPOINTMENT_MONTH, MIN_APPOINTMENT_YEAR){}

    virtual int getDay() const { return this->day; }
    virtual int getMonth() const { return this->month; }
    virtual int getYear() const { return this->year; }
    friend std::ostream& operator<<(std::ostream& os, const DateAdapter& date)
    {
        os << date.day << "/" << date.month << "/" << date.year;
        return os;
    }
};

#endif // VACOP_DATE__H



