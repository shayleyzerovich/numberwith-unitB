#include <iostream>
#include <fstream>
#include <map>
#include <iomanip>
#include <limits>
#include <sstream>
#include <stdexcept>
#include <string>
#include <map>
#include <cmath>
#include <algorithm>
#include "NumberWithUnits.hpp"

using namespace std;

const double EPS = 0.001;

namespace ariel{

        std::map<string,std::map<string,double>> units;
            
        NumberWithUnits::NumberWithUnits(double size, const string& unit){
                    
        if(units.count(unit) == 0){
            throw invalid_argument{"Unit doesn't exists"};
        }
        this->size = size;
        this->unit = unit;
    }

        void NumberWithUnits::read_units(ifstream& file){
                    
        string buff;
        string unit1;
        string unit2;
        double size1 = 0;
        double size2 = 0;
                    
        while(file >> size1 >> unit1 >> buff >> size2 >> unit2) {
                    
            units[unit1][unit2] = size2;
            units[unit2][unit1] = 1/ size2;
                    
            for(auto &pair : units[unit2]) {
                double w = units_table[unit1][unit2] * pair.second;
                units_table[unit1][pair.first] = w;
                units_table[pair.first][unit1] = 1/w;
            }
         
            for(auto &pair : units[unit1]) {
                double w = units[unit2][unit1] * pair.second;
                units_table[unit2][pair.first] = w;
                units_table[pair.first][unit2] = 1/w;
            }
        }
    }
  
       double convert(double value, const string& from, const string& to)
    {
        if (from == to){return value;}
        if (units[from].count(to) != 0){return value * units[before][after];}
        throw invalid_argument("isn't the same unit!");
    }
            
       int compare(const NumberWithUnits& num1, const NumberWithUnits& num2)
       {
       double newSize = convert(num2.size, num2.unit, num1.unit);
       double compare = num1.size - newSize;
       int ans = 0;
       if(compare > EPS){ans = 1;}
       else if(compare < -EPS){ans = -1;}
       return ans;
       }
            
       NumberWithUnits NumberWithUnits::operator+(const NumberWithUnits &num2)
    {
        double convertation = convert(num2.size, num2.unit, this->unit);
        return NumberWithUnits(this->size + convertation, this->unit);
    }
            
      NumberWithUnits NumberWithUnits::operator+()
    {
        return NumberWithUnits(+this->size, this->unit);
    }
            
      NumberWithUnits &NumberWithUnits::operator+=(const NumberWithUnits &num2)
    {
        double convertation = convert(num2.size, num2.unit, this->unit);
        this->size += convertation;
        return *this;
    }
            
      NumberWithUnits NumberWithUnits::operator-(const NumberWithUnits &num2)
    {
        double convertation = convert(num2.size, num2.unit, this->unit);
        return NumberWithUnits(this->size - convertation, this->unit);
    }

    NumberWithUnits NumberWithUnits::operator-()
    {
        return NumberWithUnits(-this->size, this->unit);
    }
            
    NumberWithUnits &NumberWithUnits::operator-=(const NumberWithUnits &num2)
    {
        double convertation = convert(num2.size, num2.unit, this->unit);
        this->size -= convertation;
        return *this;
    }
            
    bool NumberWithUnits::operator>(const NumberWithUnits& num) const{return compare(*this, num) > 0;}
    bool NumberWithUnits::operator<(const NumberWithUnits& num) const{return compare(*this, num) < 0;}
    bool NumberWithUnits::operator>=(const NumberWithUnits& num) const{return compare(*this, num) >= 0;}
    bool NumberWithUnits::operator<=(const NumberWithUnits& num) const{return compare(*this, num) <= 0;}
    bool NumberWithUnits::operator==(const NumberWithUnits& num) const{return compare(*this, num) == 0;}
    bool NumberWithUnits::operator!=(const NumberWithUnits& num) const{return compare(*this, num) != 0;}

    NumberWithUnits NumberWithUnits::operator*(double x) const{
        NumberWithUnits ans(this->size*x, this->unit);
        return ans;
    }
   
    NumberWithUnits& NumberWithUnits::operator*=(double x){
        this->size *= x;
        return *this;
    }
            
    ostream &operator<<(ostream &output, const NumberWithUnits &num)
    {
        output << num.size << "[" << num.unit << "]";
        return output;
    }

    istream &operator>>(std::istream &input, NumberWithUnits &num)
    {
        double size=0;
        string type;
        char begin=' ';
        char end=' ';

        is >> skipws >> size >> begin >> type;
        if (type.at(type.length()-1) == ']'){type = type.substr(0, type.length() - 1);}
        else{is >> skipws >> end;}
        if (units.count(type)!=1){throw invalid_argument("invalid unit");}
                
        num.size = size;
        num.unit = type;
        return input;
    }   

}
