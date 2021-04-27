#include <iostream>
#include <fstream>
#include <iomanip>
#include <map>
#include <limits>
#include "NumberWithUnits.hpp"
using namespace std;
const double EPS = 0.001;

namespace ariel {
    static map<string, map<string, double> > units;

    NumberWithUnits::NumberWithUnits(double size, const string& unit){
        if(units.count(unit) == 0){
            throw invalid_argument{"Unit doesn't exist"};
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
            units[unit2][unit1] = 1/size2;

       
            for(auto &pair : units[unit2]) {
                double w = units[unit1][unit2] * pair.second;
                units[unit1][pair.first] = w;
                units[pair.first][unit1] = 1/w;
            }
       
            for(auto &pair : units[unit1]) {
                double w = units[unit2][unit1] * pair.second;
                units[unit2][pair.first] = w;
                units[pair.first][unit2] = 1/w;
            }
        }
    }

    double convertFromTo(double value, const string& from, const string& to){
        if(from == to) {
            return value;
        }
        try {
            return value * units.at(from).at(to);
        }
        catch(const exception& e) {
            throw invalid_argument{"Units do not match - ["+from+"] cannot be converted to ["+to+"]"};
        }
    }

    int compare(const NumberWithUnits& obj1, const NumberWithUnits& obj2){
        double obj2_new_size = convertFromTo(obj2.size, obj2.unit, obj1.unit);
        double compare = obj1.quantity - obj2_size;
        int ans = 0;
        if(compare > EPS){
             ans = 1;
        }
        else if(compare < -EPS){
            ans = -1;
        }
        return ans;
    }

  
    NumberWithUnits NumberWithUnits::operator+(const NumberWithUnits& num){
        double num_new_size = convertFromTo(num.size, num.unit, this->unit);
        NumberWithUnits ans(this->size+num_new_size, this->unit);
        return ans;
    }
    NumberWithUnits NumberWithUnits::operator+(){
        NumberWithUnits ans(+this->size, this->unit);
        return ans;
    }
    NumberWithUnits& NumberWithUnits::operator+=(const NumberWithUnits& num){    
        this->size += convertFromTo(num.size, num.unit, this->unit);
        return *this;
    }
    NumberWithUnits NumberWithUnits::operator-(const NumberWithUnits& num){
        double num_new_size = convertFromTo(num.size, num.unit, this->unit);
        NumberWithUnits ans(this->size-num_new_size, this->unit);
        return ans;
    }
    NumberWithUnits NumberWithUnits::operator-(){
        NumberWithUnits ans(-this->size, this->unit);
        return ans;
    }
    NumberWithUnits& NumberWithUnits::operator-=(const NumberWithUnits& num){
        this->size -= convertFromTo(num.size, num.unit, this->unit);
        return *this;
    }

  
    NumberWithUnits& NumberWithUnits::operator++(){
        (this->size)++;
        return *this;
    }
    NumberWithUnits NumberWithUnits::operator++(int){
        NumberWithUnits copy = *this;
        this->size++;
        return copy;
    }
    NumberWithUnits& NumberWithUnits::operator--(){
        (this->size)--;
        return *this;
    }
    NumberWithUnits NumberWithUnits::operator--(int){
        NumberWithUnits copy = *this;
        this->size--;
        return copy;  
    }
  
    NumberWithUnits NumberWithUnits::operator*(double x) const{
        NumberWithUnits ans(this->size*x, this->unit);
        return ans;
    }
   
    NumberWithUnits& NumberWithUnits::operator*=(double x){
        this->size *= x;
        return *this;
    }


    bool NumberWithUnits::operator>(const NumberWithUnits& num) const{
        return compare(*this, num) > 0;
    }
    bool NumberWithUnits::operator>=(const NumberWithUnits& num) const{
        return compare(*this, num) >= 0;
    }
    bool NumberWithUnits::operator<(const NumberWithUnits& num) const{
        return compare(*this, num) < 0;
    }
    bool NumberWithUnits::operator<=(const NumberWithUnits& num) const{
                return compare(*this, num) <= 0;
    }
    bool NumberWithUnits::operator==(const NumberWithUnits& num) const{
        return compare(*this, num) == 0;
    }
    bool NumberWithUnits::operator!=(const NumberWithUnits& num) const{
        return compare(*this, num) != 0;
    }


    ostream& operator<<(ostream& output, const NumberWithUnits& num){
        out << num.size << "[" << num.unit << "]";
        return out;
    }

    istream& operator>>(istream& input, NumberWithUnits& num){
        double n = 0;
        string inp;
        char suff = ']';
        input >> n;
        input >> suff;
        while (suff != ']') {
            if (suff != '[') {
                inp.push_back(suff);
            }
            input>>suff;
        }
        if (units.find(inp_t) != units.end()) {
            num.size = n;
            num.unit = inp;
        }
        else {
            throw std::invalid_argument{"There is no such unit"};
        }
        return input;
    }
}
