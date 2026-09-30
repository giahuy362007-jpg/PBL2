#include "Date.h"

Date::Date() {
    day = 1;
    month = 1;
    year = 2000;
}

Date::Date(int day, int month, int year) {
    this->day = day;
    this->month = month;
    this->year = year;

    if (!isValid()) {
        this->day = 1;
        this->month = 1;
        this->year = 2000;
    }
}

bool Date::isLeapYear() const {
    return year % 400 == 0 || (year % 4 == 0 && year % 100 != 0);
}

int Date::daysInMonth() const {
    if (month == 2)
        return isLeapYear() ? 29 : 28;

    if (month == 4 || month == 6 || month == 9 || month == 11)
        return 30;

    return 31;
}

bool Date::isValid() const {
    if (year < 1)
        return false;

    if (month < 1 || month > 12)
        return false;

    if (day < 1 || day > daysInMonth())
        return false;

    return true;
}

void Date::input() {
    do {
        cout << "Nhap ngay thang nam: ";
        cin >> day >> month >> year;

        if (!isValid())
            cout << "Ngay khong hop le!\n";

    } while (!isValid());
}

void Date::output() const {
    cout << day << "/" << month << "/" << year;
}

int Date::getDay() const {
    return day;
}

int Date::getMonth() const {
    return month;
}

int Date::getYear() const {
    return year;
}

void Date::setDay(int day) {
    int old = this->day;
    this->day = day;

    if (!isValid())
        this->day = old;
}

void Date::setMonth(int month) {
    int old = this->month;
    this->month = month;

    if (!isValid())
        this->month = old;
}

void Date::setYear(int year) {
    int old = this->year;
    this->year = year;

    if (!isValid())
        this->year = old;
}

Date& Date::operator++() {
    day++;

    if (day > daysInMonth()) {
        day = 1;
        month++;

        if (month > 12) {
            month = 1;
            year++;
        }
    }

    return *this;
}

Date Date::operator++(int) {
    Date temp = *this;
    ++(*this);
    return temp;
}

bool Date::operator==(const Date& other) const {
    return day == other.day &&
           month == other.month &&
           year == other.year;
}

bool Date::operator!=(const Date& other) const {
    return !(*this == other);
}

bool Date::operator<(const Date& other) const {
    if (year != other.year)
        return year < other.year;

    if (month != other.month)
        return month < other.month;

    return day < other.day;
}

bool Date::operator>(const Date& other) const {
    return other < *this;
}

bool Date::operator<=(const Date& other) const {
    return !(*this > other);
}

bool Date::operator>=(const Date& other) const {
    return !(*this < other);
}

int Date::operator-(const Date& other) const {
    Date a = *this;
    Date b = other;

    int count = 0;

    if (a == b)
        return 0;

    if (a > b) {
        while (b < a) {
            ++b;
            count++;
        }
    }
    else {
        while (a < b) {
            ++a;
            count++;
        }
    }

    return (a == *this) ? count : -count;
}

istream& operator>>(istream& in, Date& date) {
    do {
        in >> date.day >> date.month >> date.year;

        if (!date.isValid())
            cout << "Ngay khong hop le, nhap lai: ";

    } while (!date.isValid());

    return in;
}

ostream& operator<<(ostream& out, const Date& date) {
    out << date.day << "/" << date.month << "/" << date.year;
    return out;
}