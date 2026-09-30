#ifndef DATE_H
#define DATE_H

#include <iostream>
using namespace std;

class Date {
private:
    int day;
    int month;
    int year;

    bool isLeapYear() const;
    int daysInMonth() const;

public:
    Date();
    Date(int day, int month, int year);

    bool isValid() const;

    void input();
    void output() const;

    int getDay() const;
    int getMonth() const;
    int getYear() const;

    void setDay(int day);
    void setMonth(int month);
    void setYear(int year);

    Date& operator++();
    Date operator++(int);

    bool operator==(const Date& other) const;
    bool operator!=(const Date& other) const;
    bool operator<(const Date& other) const;
    bool operator>(const Date& other) const;
    bool operator<=(const Date& other) const;
    bool operator>=(const Date& other) const;

    int operator-(const Date& other) const;

    friend istream& operator>>(istream& in, Date& date);
    friend ostream& operator<<(ostream& out, const Date& date);
};

#endif