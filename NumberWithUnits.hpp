#include <iostream>
#include <fstream>
#include <string>
#include <map>

namespace ariel
{
    class NumberWithUnits
    {

    private:
        double num;
        std::string unit;

    public:
        NumberWithUnits(double num, const std::string &unit);

        static void read_units(std::ifstream &units_file);

        //Six accounting operators
        NumberWithUnits operator+(const NumberWithUnits &n2);
        NumberWithUnits operator-(const NumberWithUnits &n2);
        NumberWithUnits &operator+=(const NumberWithUnits &n2);
        NumberWithUnits &operator-=(const NumberWithUnits &n2);
        NumberWithUnits operator+();
        NumberWithUnits operator-();

        //Six comparison operators
        friend bool operator>(const NumberWithUnits &n1, const NumberWithUnits &n2);
        friend bool operator>=(const NumberWithUnits &n1, const NumberWithUnits &n2);
        friend bool operator<(const NumberWithUnits &n1, const NumberWithUnits &n2);
        friend bool operator<=(const NumberWithUnits &n1, const NumberWithUnits &n2);
        friend bool operator==(const NumberWithUnits &n1, const NumberWithUnits &n2);
        friend bool operator!=(const NumberWithUnits &n1, const NumberWithUnits &n2);

        //Increase by 1 (++) and decrease by 1 (--) before and after the number
         NumberWithUnits &operator++(); //++n
         NumberWithUnits operator++(int); //n++
         NumberWithUnits &operator--(); //--n
         NumberWithUnits operator--(int); //n--

        //Multiplication by real number
        friend NumberWithUnits operator*(const NumberWithUnits &n, double x);
        friend NumberWithUnits operator*(double x, const NumberWithUnits &n);
        NumberWithUnits &operator*=(double x);

        //Input and output operator
        friend std::ostream &operator<<(std::ostream &output, const NumberWithUnits &n);
        friend std::istream &operator>>(std::istream &input, NumberWithUnits &n);
    };
}
