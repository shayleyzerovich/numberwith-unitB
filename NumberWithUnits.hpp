#include <iostream>
#include <map>
#include <string>
using namespace std;

namespace ariel {

    class NumberWithUnits{

    private:
        double size;
        string unit;

    public:
        NumberWithUnits(double size, const string& unit);
        ~NumberWithUnits(){}
        static void read_units(ifstream& file);
        friend int compare(const NumberWithUnits& obj1, const NumberWithUnits& obj2);

        NumberWithUnits operator+(const NumberWithUnits& num);
        NumberWithUnits operator+();
        NumberWithUnits& operator+=(const NumberWithUnits& num);
        NumberWithUnits operator-(const NumberWithUnits& num);
        NumberWithUnits operator-();
        NumberWithUnits& operator-=(const NumberWithUnits& num);

        NumberWithUnits& operator++();       
        NumberWithUnits operator++(int);    
        NumberWithUnits& operator--();        
        NumberWithUnits operator--(int);   

      
        NumberWithUnits operator*(double x) const;
        NumberWithUnits& operator*=(double x);
        friend NumberWithUnits operator*(double x, const NumberWithUnits& num){
            return num*x;
        }


        bool operator>(const NumberWithUnits& num) const;
        bool operator>=(const NumberWithUnits& num) const;
        bool operator<(const NumberWithUnits& num) const;
        bool operator<=(const NumberWithUnits& num) const;
        bool operator==(const NumberWithUnits& num) const;
        bool operator!=(const NumberWithUnits& num) const;


     
        friend ostream& operator<<(ostream& output, const NumberWithUnits& num);
        friend istream& operator>>(istream& in, NumberWithUnits& num);
    };
}
