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
        if(unit1 == unit2) {return size;} 
        if(units[unit1][unit2] == 0){ 
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
       NumberWithUnits NumberWithUnits::operator+() { 
       NumberWithUnits ans(+this->size , this->unit);
        return ans;
    }
       NumberWithUnits& NumberWithUnits::operator++(){
            ++(this->size);
            return *this;
    }
       NumberWithUnits NumberWithUnits::operator++(int n){
            double d = (this->size)++;
            return  NumberWithUnits(d , this->unit);
    }
       NumberWithUnits NumberWithUnits::operator+(const NumberWithUnits& n) {
        double nSize = convert(n.size, n.unit, this->unit);
        double temp = this->size + nSize;
        NumberWithUnits ans(temp, this->unit);
        return ans;
    }
       NumberWithUnits NumberWithUnits::operator-() { 
        NumberWithUnits ans(-this->size, this->unit);
        return ans;
    }

       NumberWithUnits& NumberWithUnits::operator--(){
            --(this->size);
            return *this;
    }
       NumberWithUnits NumberWithUnits::operator-(const NumberWithUnits& n){
        double nSize = convert(n.size, n.unit, this->unit);
        double temp = this->size - nSize;
        NumberWithUnits ans(temp, this->unit);
        return ans;
    }
       NumberWithUnits NumberWithUnits::operator--(int n){
            double x = (this->size)--;
            return  NumberWithUnits(x , this->unit);        
    }
       NumberWithUnits& NumberWithUnits::operator+=(const NumberWithUnits & n) {
       this->size += convert(n.size, n.unit, this->unit);
       return *this;
    }

       NumberWithUnits& NumberWithUnits::operator-=(const NumberWithUnits& n) {
       this->size -= convert(n.size, n.unit, this->unit);
       return *this;
    }
    
       NumberWithUnits operator*(const NumberWithUnits& n, const double num){return NumberWithUnits(n.size*num , n.unit);}
       NumberWithUnits operator*(const double num, const NumberWithUnits& n ){return NumberWithUnits(num*n.size,n.unit);}


        bool operator==(const NumberWithUnits& n1, const NumberWithUnits& n2){return (abs(n1.size - convert(n2.size, n2.unit, n1.unit)) <= EPS);}
	bool operator!=(const NumberWithUnits& n1, const NumberWithUnits& n2){return !(n1==n2);}
        bool operator<(const NumberWithUnits& n1, const NumberWithUnits& n2){return ((n1.size - convert(n2.size, n2.unit, n1.unit)) < 0 );}
	bool operator>(const NumberWithUnits& n1, const NumberWithUnits& n2){return ((n1.size - convert(n2.size, n2.unit, n1.unit)) >  0);}
	bool operator<=(const NumberWithUnits& n1, const NumberWithUnits& n2){return ((n1<n2)|| (n1==n2));}
	bool operator>=(const NumberWithUnits& n1, const NumberWithUnits& n2){return ((n1>n2)|| (n1==n2));}
	
	//input , output
       ostream& operator<<(ostream& output, const NumberWithUnits& n){
       return output << n.size << "[" << n.unit << "]";
       }


        istream& operator>>(istream& input, NumberWithUnits& n) {
            double size = 0;
            string unit;
            char ch = ']';
            input >> size >> ch;
            while(ch != ']') {
                if(ch != '[') { unit.insert(unit.end(), ch); }
                input >> ch;
            }

            if(units[unit].empty()){throw invalid_argument{"error"};};
                n.size = size;
                n.unit = unit;
                return input;
            }
   }
