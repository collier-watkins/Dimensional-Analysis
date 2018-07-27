#include <iostream>
#include <string>

using namespace std;





/*
Base Dimensions:
	*Length
	*Mass
	*Currency
	*Time
	*Qty (null)
	*Tempurature
	*Electrical Charge
	
	
Derived Dimensions:
	*Velocity = Length / Time
	*Acceleration = Velocity / Time    or    Length / Time^2
	*Force = Mass * Acceleration
	*
*/


class UnitDouble {
	
	public:
		double value;
		string unit;
		//string numerator;		//Replace unit variable
		//string denominator;	//Make string into vector of strings? 
		string dimension;
		
	UnitDouble(double v, string u){
		value = v;
		unit = u;
		dimension = "length";
		//Find dimension in table
	}
	
	
	//Operator overload for +
	UnitDouble operator + (const UnitDouble y) const{
		UnitDouble z(0.0,"");
		
		if(dimension == y.dimension){
			z.dimension = dimension;
			z.unit = unit;	//Fix later
			z.value = value + y.value;
			return z;
		}
		else{
			z.dimension = "";
			z.unit = "";
			z.value = 0.0;
		}
	}
	
};

//Operator overload for << & UnitDouble
ostream& operator << (ostream& os, const UnitDouble& ud){
	os << ud.value << " " << ud.unit << "(" << ud.dimension << ")";
	return os;
}
	



int main() {
	
	UnitDouble x(3.0, "meter");
	UnitDouble y(5.0, "meter");
	
	cout<<"Test Addition:";
	cout<<x+y<<endl;
	
	return 0;
}