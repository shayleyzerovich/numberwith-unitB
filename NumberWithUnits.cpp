#include "NumberWithUnits.hpp"
#include <iostream>
#include <fstream>
#include <map>
using namespace std;
using namespace ariel;

namespace ariel{

    const double EPS = 0.00001;
    static map<string, map<string, double> > units;

    NumberWithUnits :: NumberWithUnits(double size, const string& unit){
        units.at(unit);
        this->size=size;
        this->unit=unit;
    }

    double convert(double size, const string& unit1, const string& unit2){
        if(unit1 == unit2) {return size;} //same unit
        if(units[unit1][unit2] == 0){ //It is impossible to connect them
            throw invalid_argument{"Unable to convert - ["+unit1+"] to ["+unit2+"]"};
        }
        return size*units[unit1][unit2];
    }

    void NumberWithUnits::read_units(ifstream& file){

        int num1 = 0; 
        double num2 = 0;
        string unit1, unit2;
        char eq = '=';
        
        while(file >> num1 >> unit1 >> eq >> num2 >> unit2){

            units[unit1][unit2] = num2;
            units[unit2][unit1]= num1/num2;
            
            for(auto &pair : units[unit1]) {
                double unitTemp = units[unit2][unit1] * pair.second;
                units[unit2][pair.first] = unitTemp;
                units[pair.first][unit2] = 1/unitTemp;            }

            for(auto &pair : units[unit2]) {
                double unitTemp = units[unit1][unit2] * pair.second;
                units[unit1][pair.first] = unitTemp;
                units[pair.first][unit1] = 1/unitTemp;
            }
        }
    }


//input , output
       ostream& operator<<(ostream& output, const NumberWithUnits& c){
         return output << c.size << "[" << c.unit << "]";
       }


        istream& operator>>(istream& input, NumberWithUnits& c) {
            double size = 0;
            string unit;
            char ch = ']';
            input >> size >> ch;
            while(ch != ']') {
                if(ch != '[') { unit.insert(unit.end(), ch); }
                input >> ch;
            }

            if(units[unit].empty()){throw invalid_argument{"error unit"};};
                c.size = size;
                c.unit = unit;
                return input;
            }
        

    NumberWithUnits& NumberWithUnits::operator+=(const NumberWithUnits &c) {
    this->size += convert(c.size, c.unit, this->unit);
    return *this;
    }

    NumberWithUnits& NumberWithUnits::operator-=(const NumberWithUnits& c) {
    this->size -= convert(c.size, c.unit, this->unit);
    return *this;
    }

    NumberWithUnits NumberWithUnits::operator+(const NumberWithUnits& c) {
        double cVal = convert(c.size, c.unit, this->unit);
        double temp = this->size + cVal;
        NumberWithUnits ans(temp, this->unit);
        return ans;
    }

     NumberWithUnits NumberWithUnits::operator-(const NumberWithUnits& c){
        double cVal = convert(c.size, c.unit, this->unit);
        double temp = this->size - cVal;
        NumberWithUnits ans(temp, this->unit);
        return ans;
    }

    NumberWithUnits NumberWithUnits::operator+() { //unary
        NumberWithUnits ans(+this->size , this->unit);
        return ans;
    }

    NumberWithUnits NumberWithUnits::operator-() { //unary
        NumberWithUnits ans(-this->size, this->unit);
        return ans;
    }

    NumberWithUnits& NumberWithUnits::operator++(){//prefix increment  
            ++(this->size);
            return *this;
        }


    NumberWithUnits& NumberWithUnits::operator--(){
            --(this->size);
            return *this;
        }

   
    NumberWithUnits NumberWithUnits::operator++(int dummy_flag_for_postfix_increment){
            double d = (this->size)++;
            return  NumberWithUnits(d , this->unit);
        }

    NumberWithUnits NumberWithUnits::operator--(int dummy_flag_for_postfix_increment){
            double d = (this->size)--;
            return  NumberWithUnits(d , this->unit);        }


	bool operator==(const NumberWithUnits& c1, const NumberWithUnits& c2){
        return (abs(c1.size - convert(c2.size, c2.unit, c1.unit)) <= eps);
         }

	bool operator!=(const NumberWithUnits& c1, const NumberWithUnits& c2){
        return !(c1==c2);
         }

    bool operator<(const NumberWithUnits& c1, const NumberWithUnits& c2){
        return ((c1.size - convert(c2.size, c2.unit, c1.unit)) < 0 );
         }

	bool operator>(const NumberWithUnits& c1, const NumberWithUnits& c2){
        return ((c1.size - convert(c2.size, c2.unit, c1.unit)) >  0);
         }

	bool operator<=(const NumberWithUnits& c1, const NumberWithUnits& c2){
        return ((c1<c2)|| (c1==c2));
         }

	bool operator>=(const NumberWithUnits& c1, const NumberWithUnits& c2){
        return ((c1>c2)|| (c1==c2));
         }


	NumberWithUnits operator*(const NumberWithUnits& c1, const double num){
        return NumberWithUnits(c1.size*num , c1.unit);
         }

    NumberWithUnits operator*(const double num, const NumberWithUnits& c1 ){
        return NumberWithUnits(num*c1.size,c1.unit);
         }
   }
