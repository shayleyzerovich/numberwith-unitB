#include <string>
#include <iostream>
#include <map>


namespace ariel{

class NumberWithUnits{


    private:
      double value;
	    std::string type;   

    public:
  
        NumberWithUnits(double value, const std::string& type);

        double getVal() const{
          return this->value;
        }

        std::string getType() const{
          return this->type;
        }

        static void read_units(std::ifstream& f);

        //prefix increment  
        NumberWithUnits& operator++();
        NumberWithUnits& operator--();

        //postfix increment
        NumberWithUnits operator++(int dummy_flag_for_postfix_increment);
        NumberWithUnits operator--(int dummy_flag_for_postfix_increment);

        //unary
        NumberWithUnits operator+(); 
        NumberWithUnits operator-();

        // arithmetic operators
        NumberWithUnits& operator+=(const NumberWithUnits& c) ;
        NumberWithUnits& operator-=(const NumberWithUnits& c) ;
        NumberWithUnits operator+(const NumberWithUnits& c);
        NumberWithUnits operator-(const NumberWithUnits& c);

        //output , input
        friend std::ostream& operator<<(std::ostream& output, const NumberWithUnits& c);
        friend std::istream& operator>>(std::istream& input, NumberWithUnits& c);

        //bool Comparisons
        friend bool operator==(const NumberWithUnits& c1, const NumberWithUnits& c2);
        friend bool operator!=(const NumberWithUnits& c1, const NumberWithUnits& c2);
        friend bool operator<(const NumberWithUnits& c1, const NumberWithUnits& c2);	
        friend bool operator>(const NumberWithUnits& c1, const NumberWithUnits& c2);
        friend bool operator<=(const NumberWithUnits& c1, const NumberWithUnits& c2);
        friend bool operator>=(const NumberWithUnits& c1, const NumberWithUnits& c2);

         //mult
        friend  NumberWithUnits operator*(const NumberWithUnits& c1, const double num);
        friend  NumberWithUnits operator*(const double num, const NumberWithUnits& c1);



  };

}

