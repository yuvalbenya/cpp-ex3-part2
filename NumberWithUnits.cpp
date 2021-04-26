#include "NumberWithUnits.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <string.h>
#include <map>
#include <ctime>
#include <stdexcept>

const double EPS = 0.0001;


using namespace std;
namespace ariel
{

    map<string, map<string, double>> NumberWithUnits::converter = {};
    NumberWithUnits::NumberWithUnits(double amount, const string &unit)
    {
        if (converter.count(unit) == 0)
        {
            throw invalid_argument{"Unit doesn't exist in the units table!"};
        }
        this->amount = amount;
        this->unit = unit;
    }
    void NumberWithUnits::read_units(ifstream &unitfile)
    {
        string un1, un2, cmp;
        double n1, n2;

        while (unitfile >> n1 >> un1 >> cmp >> n2 >> un2)
        {
            converter[un1][un1] = 1;
            converter[un1][un2] = n2 / n1;
            converter[un2][un1] =  n1 / n2;
            addConvertion(un1, un2);
            addConvertion(un2, un1);
        }

        for (const auto &p : converter)
        {
            std::cout << p.first << "->";
            for (const auto &p1 : converter[p.first])
            {
                std::cout << "{"<< p1.first << ", " << converter[p.first][p1.first] <<  "}";
            }

            cout << endl;
        }
        cout << "************************************************************\n";
    }

    //map[m][km][1\1000];
    //map[cm][km][1\1000\100]
    //map[cm][m][1\100]
    void NumberWithUnits::addConvertion(string u1, string u2)
    {
        for (pair<string, double> element : converter[u1])
        {
            converter[u2][element.first] =  converter[u1][element.first] * converter[u2][u1];
            converter[element.first][u2] = 1 / converter[u2][element.first];
        }
    }

    double NumberWithUnits::convert(const string &fromType, const string &toType, double amount)
    {
        if (fromType == toType)
        {
            return amount;
        }
        try
        {
            double coef = converter.at(fromType).at(toType);
            return (coef * amount);
        }
        catch (const exception &e)
        {
            throw invalid_argument{"Units do not match - [" + fromType + "] cannot be converted to [" + toType + "]"};
        }
    }
    /***** Overloading Arithmetic operators *******/

    NumberWithUnits NumberWithUnits::operator+(const NumberWithUnits &num)
    {
        double convertedAmount = convert(num.unit, this->unit, num.amount);
        return NumberWithUnits(this->amount + convertedAmount, this->unit);
    }
    NumberWithUnits &NumberWithUnits::operator+=(const NumberWithUnits &num)
    {
        *this = *this + num;
        return *this;
    }

    NumberWithUnits NumberWithUnits::operator+()
    {
        return *this;
    }
    NumberWithUnits NumberWithUnits::operator-()
    {
        return NumberWithUnits(-this->amount, this->unit);
    }
    NumberWithUnits NumberWithUnits::operator-(const NumberWithUnits &num)
    {
        return *this + (-NumberWithUnits(num.amount, num.unit));
    }
    NumberWithUnits &NumberWithUnits::operator-=(const NumberWithUnits &num)
    {
        *this = *this - num;
        return *this;
    }
    /**** Overloading boolean operators *******/
    bool operator>(const NumberWithUnits &num1, const NumberWithUnits &num2) { return num1.amount  > NumberWithUnits::convert(num2.unit, num1.unit, num2.amount) + EPS; }
    bool operator>=(const NumberWithUnits &num1, const NumberWithUnits &num2) { return !(num1 < num2); }
    bool operator<(const NumberWithUnits &num1, const NumberWithUnits &num2) { return num1.amount   < NumberWithUnits::convert(num2.unit, num1.unit, num2.amount) - EPS; }
    bool operator<=(const NumberWithUnits &num1, const NumberWithUnits &num2) { return !(num1 > num2); }
    bool operator==(const NumberWithUnits &num1, const NumberWithUnits &num2) { return (num1.amount - EPS <= NumberWithUnits::convert(num2.unit, num1.unit, num2.amount)) && (num1.amount + EPS >= NumberWithUnits::convert(num2.unit, num1.unit, num2.amount)); }
    bool operator!=(const NumberWithUnits &num1, const NumberWithUnits &num2) { return !(num1 == num2); }

    /**** Overloading incremental operators *******/
    NumberWithUnits &operator++(NumberWithUnits &num)
    {
        num.amount++;
        return num;
    }
    NumberWithUnits operator++(NumberWithUnits &num, int)
    {
        return NumberWithUnits(num.amount++, num.unit);
    }
    NumberWithUnits &operator--(NumberWithUnits &num)
    {
        num.amount--;
        return num;
    }
    NumberWithUnits operator--(NumberWithUnits &num, int)
    {
        return NumberWithUnits(num.amount--, num.unit);
    }

    /**** Overloading multiplication operators *******/
    NumberWithUnits operator*(const NumberWithUnits &nwu, double num)
    {
        return NumberWithUnits(nwu.amount * num, nwu.unit);
    }

    NumberWithUnits operator*(double num, const NumberWithUnits &nwu)
    {
        return NumberWithUnits(nwu.amount * num, nwu.unit);
    }
    
    NumberWithUnits &NumberWithUnits::operator*=(double num)
    {
        this->amount *= num;
        return *this;
    }
    std::ostream &operator<<(std::ostream &out, const NumberWithUnits &num)
    {
        return out << num.amount << "[" + num.unit + "]";
    }
    std::istream &operator>>(std::istream &in, NumberWithUnits &num)
    {
        double s1;
        char  s2,s4;
        string s3;
        in >> s1 >> s2 >> s3;
        if(s3.at(s3.length() - 1) == ']'){
            s3 = s3.substr(0, s3.size()-1);
               
        }
        else{in >> s4;}
        num = NumberWithUnits(s1,s3);
        return in;
    }
}
