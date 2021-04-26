#pragma once
#include <string>
#include <iostream>
#include <stdbool.h>
#include <map>
using namespace std;
namespace ariel
{

    class NumberWithUnits
    {
    private:
        double amount;
        string unit;
        static map<string, map<string, double>> converter;

    public:
        NumberWithUnits(double amount, const string &unit);
        // ~NumberWithUnits() {}
        // NumberWithUnits(double amount, const string& unit){}

        static void read_units(ifstream &units_file);
        static void addConvertion(string u1, string u2);
        static double convert(
            const string &fromType, const string &toType, double amount);
        NumberWithUnits operator+(const NumberWithUnits &num);
        NumberWithUnits &operator+=(const NumberWithUnits &num);
        NumberWithUnits operator+();
        NumberWithUnits operator-(const NumberWithUnits &num);
        NumberWithUnits &operator-=(const NumberWithUnits &num);
        NumberWithUnits operator-();
        friend bool operator>(const NumberWithUnits &num1, const NumberWithUnits &num2);
        friend bool operator>=(const NumberWithUnits &num1, const NumberWithUnits &num2);
        friend bool operator<=(const NumberWithUnits &num1, const NumberWithUnits &num2);
        friend bool operator<(const NumberWithUnits &num1, const NumberWithUnits &num2);
        friend bool operator==(const NumberWithUnits &num1, const NumberWithUnits &num2);
        friend bool operator!=(const NumberWithUnits &num1, const NumberWithUnits &num2);

        friend NumberWithUnits &operator++(NumberWithUnits &num);
        friend NumberWithUnits operator++(NumberWithUnits &num, int);
        friend NumberWithUnits &operator--(NumberWithUnits &num);
        friend NumberWithUnits operator--(NumberWithUnits &num, int);
        friend std::ostream &operator<<(std::ostream &out, const NumberWithUnits &num);
        friend std::istream &operator>>(std::istream &in, NumberWithUnits &num);
        // friend NumberWithUnits operator*(NumberWithUnits &n, double num);
        // friend NumberWithUnits operator*(double num ,NumberWithUnits &n);
        // friend NumberWithUnits &operator*=(double num ,NumberWithUnits &n);
        // friend NumberWithUnits &operator*=(NumberWithUnits &n, double num);
        // NumberWithUnits &operator*=( double num );
        // friend NumberWithUnits operator*(const NumberWithUnits& n,double num);
        friend NumberWithUnits operator*(const NumberWithUnits &nwu, double num);
        friend NumberWithUnits operator*(double num, const NumberWithUnits &nwu);
        NumberWithUnits &operator*=(double num);
    };

}