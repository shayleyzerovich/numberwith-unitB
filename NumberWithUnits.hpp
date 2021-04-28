#include <string>
#include <iostream>
#include <map>


namespace ariel{

class NumberWithUnits{


    private:
      double size;
	    std::string unit;   

    public:
  
        NumberWithUnits(double size, const std::string& unit);

        double getSize() const{
          return this->size;
        }

        std::string getUnit() const{
          return this->unit;
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
        bool operator==(const NumberWithUnits& c1, const NumberWithUnits& c2);
        bool operator!=(const NumberWithUnits& c1, const NumberWithUnits& c2);
        bool operator<(const NumberWithUnits& c1, const NumberWithUnits& c2);	
        bool operator>(const NumberWithUnits& c1, const NumberWithUnits& c2);
        bool operator<=(const NumberWithUnits& c1, const NumberWithUnits& c2);
        bool operator>=(const NumberWithUnits& c1, const NumberWithUnits& c2);

         //mult
        NumberWithUnits operator*(const NumberWithUnits& c1, const double num);
        NumberWithUnits operator*(const double num, const NumberWithUnits& c1);



  };

}

