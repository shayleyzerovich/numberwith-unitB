  
#include <iostream>
#include <fstream>
#include <string>
#include <map>

namespace ariel
{
    class NumberWithUnits
    {

    private:
        double size;
        std::string unit;

    public:
        NumberWithUnits(double size, const std::string &unit);
        ~NumberWithUnits(){}
        static void read_units(ifstream& file);
        friend int compare(const NumberWithUnits& num1, const NumberWithUnits& num2);
        static void read_units(std::ifstream &units_file);

       
        NumberWithUnits operator+(const NumberWithUnits &n2);
        NumberWithUnits operator+();
        NumberWithUnits &operator+=(const NumberWithUnits &n2);
        NumberWithUnits operator-(const NumberWithUnits &n2);
        NumberWithUnits operator-();
        NumberWithUnits &operator-=(const NumberWithUnits &n2);

        NumberWithUnits &operator++();
        NumberWithUnits operator++(int);
        NumberWithUnits &operator--();
        NumberWithUnits operator--(int); 

       
        bool operator>(const NumberWithUnits &n1, const NumberWithUnits &n2);
        bool operator>=(const NumberWithUnits &n1, const NumberWithUnits &n2);
        bool operator<(const NumberWithUnits &n1, const NumberWithUnits &n2);
        bool operator<=(const NumberWithUnits &n1, const NumberWithUnits &n2);
        bool operator==(const NumberWithUnits &n1, const NumberWithUnits &n2);
        bool operator!=(const NumberWithUnits &n1, const NumberWithUnits &n2);

        NumberWithUnits operator*(double x) const;
        NumberWithUnits& operator*=(double x);
        friend NumberWithUnits operator*(double x, const NumberWithUnits& num){
            return num*x;
        }


        friend std::ostream &operator<<(std::ostream &output, const NumberWithUnits &num);
        friend std::istream &operator>>(std::istream &input, NumberWithUnits &num);
    };
}
