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

        NumberWithUnits operator+();  
        NumberWithUnits& operator++();
        NumberWithUnits operator+(const NumberWithUnits& n);
	NumberWithUnits operator++(int n);
	NumberWithUnits operator-();
        NumberWithUnits& operator--();
	NumberWithUnits operator-(const NumberWithUnits& n);
        NumberWithUnits operator--(int n);

       
        NumberWithUnits& operator+=(const NumberWithUnits& n) ;
        NumberWithUnits& operator-=(const NumberWithUnits& n) ;
       
        friend NumberWithUnits operator*(const NumberWithUnits& n, const double num);
        friend NumberWithUnits operator*(const double num, const NumberWithUnits& n);

        friend bool operator==(const NumberWithUnits& n1, const NumberWithUnits& n2);
        friend bool operator!=(const NumberWithUnits& n1, const NumberWithUnits& n2);
        friend bool operator<(const NumberWithUnits& n1, const NumberWithUnits& n2);	
        friend bool operator>(const NumberWithUnits& n1, const NumberWithUnits& n2);
        friend bool operator<=(const NumberWithUnits& n1, const NumberWithUnits& n2);
        friend bool operator>=(const NumberWithUnits& n1, const NumberWithUnits& n2);
	
        friend std::ostream& operator<<(std::ostream& output, const NumberWithUnits& n);
        friend std::istream& operator>>(std::istream& input, NumberWithUnits& n);
    

  };

}

