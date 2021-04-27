#include "NumberWithUnits.hpp"
#include <iostream>
#include <fstream>
#include <map>
using namespace std;
using namespace ariel;

namespace ariel{

    const double eps = 0.00001;
    static map<string, map<string, double> > units;

    NumberWithUnits :: NumberWithUnits(double value, const string& type){
        units.at(type);
        this->value=value;
        this->type=type;
    }

    double convert(double value, const string& unit1, const string& unit2){
        if(unit1 == unit2) {return value;} //same type
        if(units[unit1][unit2] == 0){ //It is impossible to connect them
            throw invalid_argument{"Unable to convert - ["+unit1+"] to ["+unit2+"]"};
        }
        return value*units[unit1][unit2];
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
         return output << c.value << "[" << c.type << "]";
       }


        istream& operator>>(istream& input, NumberWithUnits& c) {
            double value = 0;
            string type;
            char ch = ']';
            input >> value >> ch;
            while(ch != ']') {
                if(ch != '[') { type.insert(type.end(), ch); }
                input >> ch;
            }

            if(units[type].empty()){throw invalid_argument{"error unit"};};
                c.value = value;
                c.type = type;
                return input;
            }
        

    NumberWithUnits& NumberWithUnits::operator+=(const NumberWithUnits &c) {
    this->value += convert(c.value, c.type, this->type);
    return *this;
    }

    NumberWithUnits& NumberWithUnits::operator-=(const NumberWithUnits& c) {
    this->value -= convert(c.value, c.type, this->type);
    return *this;
    }

    NumberWithUnits NumberWithUnits::operator+(const NumberWithUnits& c) {
        double cVal = convert(c.value, c.type, this->type);
        double temp = this->value + cVal;
        NumberWithUnits ans(temp, this->type);
        return ans;
    }

     NumberWithUnits NumberWithUnits::operator-(const NumberWithUnits& c){
        double cVal = convert(c.value, c.type, this->type);
        double temp = this->value - cVal;
        NumberWithUnits ans(temp, this->type);
        return ans;
    }

    NumberWithUnits NumberWithUnits::operator+() { //unary
        NumberWithUnits ans(+this->value , this->type);
        return ans;
    }

    NumberWithUnits NumberWithUnits::operator-() { //unary
        NumberWithUnits ans(-this->value, this->type);
        return ans;
    }

    NumberWithUnits& NumberWithUnits::operator++(){//prefix increment  
            ++(this->value);
            return *this;
        }


    NumberWithUnits& NumberWithUnits::operator--(){
            --(this->value);
            return *this;
        }

   
    NumberWithUnits NumberWithUnits::operator++(int dummy_flag_for_postfix_increment){
            double d = (this->value)++;
            return  NumberWithUnits(d , this->type);
        }

    NumberWithUnits NumberWithUnits::operator--(int dummy_flag_for_postfix_increment){
            double d = (this->value)--;
            return  NumberWithUnits(d , this->type);        }


	bool operator==(const NumberWithUnits& c1, const NumberWithUnits& c2){
        return (abs(c1.value - convert(c2.value, c2.type, c1.type)) <= eps);
         }

	bool operator!=(const NumberWithUnits& c1, const NumberWithUnits& c2){
        return !(c1==c2);
         }

    bool operator<(const NumberWithUnits& c1, const NumberWithUnits& c2){
        return ((c1.value - convert(c2.value, c2.type, c1.type)) < 0 );
         }

	bool operator>(const NumberWithUnits& c1, const NumberWithUnits& c2){
        return ((c1.value - convert(c2.value, c2.type, c1.type)) >  0);
         }

	bool operator<=(const NumberWithUnits& c1, const NumberWithUnits& c2){
        return ((c1<c2)|| (c1==c2));
         }

	bool operator>=(const NumberWithUnits& c1, const NumberWithUnits& c2){
        return ((c1>c2)|| (c1==c2));
         }


	NumberWithUnits operator*(const NumberWithUnits& c1, const double num){
        return NumberWithUnits(c1.value*num , c1.type);
         }

    NumberWithUnits operator*(const double num, const NumberWithUnits& c1 ){
        return NumberWithUnits(num*c1.value,c1.type);
         }
   }
