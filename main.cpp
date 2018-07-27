#include <iostream>
#include <string>
#include <vector>

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
		vector<string> numerator;
		vector<string> denominator;	
		string dimension;
		
	UnitDouble(double val, vector<string> num, vector<string> den, string dim){
		value = val;
		numerator = num;
		denominator = den;
		dimension = dim;
	}
	
	UnitDouble(){
		value = 0.0;
		dimension = "";
	}
	
	
	//Operator overload for +
	UnitDouble operator + (const UnitDouble x) const{
		UnitDouble z;
		
		if(dimension == x.dimension){
			z.dimension = dimension;
			z.numerator = numerator;	//Fix later
			z.denominator = denominator;
			z.value = value + x.value;
			return z;
		}
		else{
			z.dimension = "ERROR";
			z.numerator.push_back("ERROR");
			z.value = 0.0;
			return z;
		}
	}
	
	UnitDouble operator - (const UnitDouble x) const{
		UnitDouble z;
		
		if(dimension == x.dimension){
			z.dimension = dimension;
			z.numerator = numerator;	//Fix later
			z.denominator = denominator;
			z.value = value - x.value;
			return z;
		}
		else{
			z.dimension = "ERROR";
			z.numerator.push_back("ERROR");
			z.value = 0.0;
			return z;
		}
	}
	
	UnitDouble operator * (const UnitDouble x) const{
		UnitDouble z;
		
		//1. Convert all units to base units
		
		//2. Multiply values
		z.value = value * x.value;
		
		//3. Cancel / combine units
		for(int i = 0; i < numerator.size(); i++){
			for(int j = 0; j < x.denominator.size(); j++){
				if(numerator[i] == x.denominator[j]){
					numerator.erase(numerator.begin() + i);
					x.denominator.erase(x.denominator.begin() + j);
					
					
					i = 0; //reset main loop because of deletion
 					break; //break loop because of deletion
				}
			}
		}
		
		z.numerator = numerator;
		
		//4. Determine new dimension
		z.dimension = dimension;
		
		//5. return z
		return z;
		
	}
	
	
	

	
	
	
};

//Operator overload for << & UnitDouble
ostream& operator << (ostream& os, const UnitDouble& ud){
	os << ud.value;
	
	if(ud.numerator.size() > 0) {
		os << " (" << ud.numerator[0];
	
		for(int i = 1; i < ud.numerator.size(); i++){
			os << "*" << ud.numerator[i];
		}
		
		os << ")";
	}
	
	
	
	if(ud.denominator.size() > 0) {
		os << "/(" << ud.denominator[0];
	
		for(int i = 1; i < ud.denominator.size(); i++){
			os << "*" << ud.denominator[i];
		}
		
		os << ") ";
	}
	
	return os;
}
	



int main() {
	vector<string> num;
	num.push_back("meter");
	
	vector<string> den;
	den.push_back("s");
	den.push_back("s");
	
	UnitDouble x(3.0, num, den, "acceleration");
	UnitDouble y(5.2, num, den, "acceleration");
	
	cout<<"x: " << x <<endl;
	cout<<"y: " << y <<endl;
	
	cout<<"Test Addition: ";
	cout<<x+y<<endl;

	cout<<"Test Subtraction: ";
	cout<<x-y<<endl;
	
	cout<<endl;
	
	
	/////////////////
	
	
	vector<string> len;
	len.push_back("meter");
	
	vector<string> time;
	time.push_back("s");
	
	vector<string> empty;
	
	UnitDouble a(3.0, len, time, "speed");
	UnitDouble b(5.0, time, empty, "time");
	
	
	cout<<"Test Multiplication: ";
	cout<<a*b<<endl;

	
	

	
	return 0;
}