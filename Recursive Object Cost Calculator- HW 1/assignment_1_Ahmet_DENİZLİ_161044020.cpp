/*##############################################*/
/*				  Ahmet Denizli  				*/
/*					161044020					*/
/*##############################################*/
#include <iostream>
#include <string>
#include <cstdlib>
#include <iomanip>		// include for setprecision

using namespace std;

// This function according to the user input, creates
// dynamic responses and do simple calculations with recursion.
double rec(string str);

int main(int argc, char const *argv[])
{
	string obj;							// Declaring variable for obj
	double result;						// Declaring variable for result

	cout << fixed << showpoint;			// Floating point formatting
	cout << setprecision(2);

	cout << "Define the object:" << endl;
	cin >> obj;							// Taking input from user for object

	cin.clear();						// Cin clear and ignore for getline
	cin.ignore(10000,'\n');

	result = rec(obj);					// Use rec function for object

	cout << "Total cost of "<< obj << " " << result << endl;	// Printing result
	
	return 0;
}

// This function according to the user input, creates
// dynamic responses and do simple calculations with recursion.
double rec(string str){
	double dbltmp;					// Declaring variable for double part 
	string ln1, ln2, temp1, temp2;	// Declaring variables 
	size_t found, fnd2;				// Declaring variables for positions

	found = str.find('*');		// Assign the position of the '*' character of the first match

	// If '*' character found
	if(found!= string::npos){
		temp1 = str.substr(0,found);			// Taking substr up to the '*' character
		dbltmp= strtod(temp1.c_str(), NULL);	// taking double part of object
		temp1 = str.substr(found+1);			// taking substr from the '*' character

		fnd2 = temp1.find('+');					// looking '+' character
		if(fnd2!= string::npos){				// If it is found
			temp2 = temp1.substr(0, fnd2);		// Taking string name part of object

			cout << "What is " << temp2 << "?:" << endl;
			getline(cin, ln1);					// Get line from user for objects part

			ln2 = temp1.substr(fnd2+1);

			return dbltmp * rec(ln1) + rec(ln2);
		}
		return dbltmp * rec(temp1);

	}
	else if (dbltmp= strtod(str.c_str(), NULL)){	// If '*' character not found and

		return dbltmp;								// there is only double part
	}
	else{											// If there is only object name
		cout << "What is " << str << "?:" << endl;
		getline(cin, ln1);
		return rec(ln1);
	}

}