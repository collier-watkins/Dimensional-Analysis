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
		UnitDouble temp(value, numerator, denominator, dimension);
		//1. Convert all units to base units
		
		//2. Multiply values
		temp.value = value * x.value;
		
		//3. Combine unit numerators and denominators
		
		temp.numerator.insert(temp.numerator.end(), x.numerator.begin(), x.numerator.end());
		temp.denominator.insert(temp.denominator.end(), x.denominator.begin(), x.denominator.end());
		
		
		//4a. Cancel units numerator to denominator
		for(int i = 0; i < temp.numerator.size(); i++){
			for(int j = 0; j < temp.denominator.size(); j++){
				if(temp.numerator[i] == temp.denominator[j]){
					temp.numerator.erase(temp.numerator.begin() + i);
					temp.denominator.erase(temp.denominator.begin() + j);
					
					i = 0; //reset main loop because of deletion
 					break; //break loop because of deletion
				}
			}
		}
		
		//4b. Cancel units denominator to numerator
		for(int i = 0; i < temp.denominator.size(); i++){
			for(int j = 0; j < temp.numerator.size(); j++){
				if(temp.denominator[i] == temp.numerator[j]){
					temp.denominator.erase(temp.denominator.begin() + i);
					temp.numerator.erase(temp.numerator.begin() + j);
					
					i = 0; //reset main loop because of deletion
 					break; //break loop because of deletion
				}
			}
		}
		
		
		
		//5. Determine new dimension
		
		
		//6. return temp
		return temp;
		
	}
	
	UnitDouble operator / (const UnitDouble x) const{
		UnitDouble self(value, numerator, denominator, dimension);
		UnitDouble inv_x(1/x.value, x.denominator, x.numerator, x.dimension);
		
		return self * inv_x;
		
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
	
	vector<string> time_sq;
	time_sq.push_back("s");
	time_sq.push_back("s");
	
	
	vector<string> empty;
	
	UnitDouble a(3.0, len, time_sq, "acceleration");
	UnitDouble b(5.0, time, empty, "time");
	
	cout<<"a: " << a <<endl;
	cout<<"b: " << b <<endl;
	
	cout<<"Test Multiplication: ";
	cout<<a*b<<endl;

	cout<<"Test Division: ";
	cout<<a/b<<endl;

	
	

	
	return 0;
}