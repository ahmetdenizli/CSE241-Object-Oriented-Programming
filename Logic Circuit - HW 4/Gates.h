/*##############################################*/
/*				  Ahmet Denizli  				*/
/*					161044020					*/
/*			  Class implementations				*/
/*##############################################*/
#include <string>

using namespace std;

class Gate {
public:
	void set_data(const bool _data) { data = _data;}									// Sets boolean data
	void set_cont(const int _control) { control = _control;}							// Sets control variable
	void set_Gate1( Gate* _gate) { first = _gate;}										// Sets first gate
	void set_Gates( Gate* _gate1, Gate* _gate2) { first = _gate1; second = _gate2;}		// Sets first and second gate
	const string get_name() const {return name;}										// Gets gate name

	virtual bool out() = 0;				// Pure virual function that return output recursively

protected:
	Gate * first;		// Gate* for the first input of gate
	Gate * second;		// Gate* for the second input of gate
	string name;		// string name for gates name
	bool data;			// boolean data for inputs
	int control;		// int variable for checks to see if the gate is worked once
};

// Class for Inputs inherited from Gate Class
class Inp : public Gate {
public:
	Inp(const string _name) {first=NULL; second=NULL; name=_name;}		// Constructor

	bool out() override{
		return data;
	}
};

// Class for And Gates inherited from Gate Class
class And : public Gate {
public:
	And(const string _name) {first=NULL; second=NULL; name=_name;}								// Constructor
	And(Gate *ptr1, Gate *ptr2, const string _name) {first =ptr1; second=ptr2; name=_name;}		// Constructor

	bool out() override{
		if (control==1 || control==0)
			return control;
		if (first->out()==0 || second->out()==0){
			control=0;
			return 0;
		}
		else{
			control=1;
			return 1;
		}
	}
};

// Class for Or Gates inherited from Gate Class
class Or : public Gate {
public:
	Or(const string _name) {first=NULL; second=NULL; name=_name;}								// Constructor
	Or(Gate *ptr1, Gate *ptr2, const string _name) {first =ptr1; second=ptr2; name=_name;}		// Constructor

	bool out() override{
		if (control==1 || control==0)
			return control;
		if (first->out()==1 || second->out()==1){
			control=1;
			return 1;
		}
		else{
			control=0;
			return 0;
		}
	}
};

// Class for Not Gates inherited from Gate Class
class Not : public Gate {
public:
	Not(const string _name) {first=NULL; second=NULL; name=_name;}						// Constructor
	Not(Gate *ptr1, const string _name) {first =ptr1; second=NULL; name=_name;}			// Constructor
	
	bool out() override{
		if (control==1 || control==0)
			return control;
		if (first->out()==1){
			control=0;
			return 0;
		}
		else{
			control=1;
			return 1;
		}
	}
};

// Class for FlipFlop Gates inherited from Gate Class
class FlipFlop : public Gate {
public:
	FlipFlop(const string _name) : former_out(0) {first=NULL; second=NULL; name=_name;}					// Constructor
	FlipFlop(Gate *ptr1, const string _name) : former_out(0) {first =ptr1; second=NULL; name=_name;}	// Constructor

	void set_f_out(const bool _data) {former_out = _data;}

	bool out() override{
		if (control==1 || control==0)
			return control;
		if ( (first->out()==0 && former_out==0) || (first->out()==1 && former_out==1) ){
			former_out = 0;
			control=0;
			return 0;
		}
		else{
			former_out = 1;
			control=1;
			return 1;
		}
	}
private:
	bool former_out;
};

// Class for Decoder Gates 1.output, inherited from Gate Class
class Decoder1 : public Gate {
public:
	Decoder1(const string _name) {first=NULL; second=NULL; name=_name;}								// Constructor
	Decoder1(Gate *ptr1, Gate *ptr2, const string _name) {first =ptr1; second=ptr2; name=_name;}	// Constructor
	
	bool out() override{
		if (control==1 || control==0)
			return control;
		if (first->out()==0 && second->out()==0){
			control=1;
			return 1;
		}
		else{
			control=0;
			return 0;
		}
	}
};

// Class for Decoder Gates 2.output, inherited from Gate Class
class Decoder2 : public Gate {
public:
	Decoder2(const string _name) {first=NULL; second=NULL; name=_name;}								// Constructor
	Decoder2(Gate *ptr1, Gate *ptr2, const string _name) {first =ptr1; second=ptr2; name=_name;}	// Constructor
	
	bool out() override{
		if (control==1 || control==0)
			return control;
		if (first->out()==0 && second->out()==1){
			control=1;
			return 1;
		}
		else{
			control=0;
			return 0;
		}
	}
};

// Class for Decoder Gates 3.output, inherited from Gate Class
class Decoder3 : public Gate {
public:
	Decoder3(const string _name) {first=NULL; second=NULL; name=_name;}								// Constructor
	Decoder3(Gate *ptr1, Gate *ptr2, const string _name) {first =ptr1; second=ptr2; name=_name;}	// Constructor
	
	bool out() override{
		if (control==1 || control==0)
			return control;
		if (first->out()==1 && second->out()==0){
			control=1;
			return 1;
		}
		else{
			control=0;
			return 0;
		}
	}
};

// Class for Decoder Gates 4.output, inherited from Gate Class
class Decoder4 : public Gate {
public:
	Decoder4(const string _name) {first=NULL; second=NULL; name=_name;}								// Constructor
	Decoder4(Gate *ptr1, Gate *ptr2, const string _name) {first =ptr1; second=ptr2; name=_name;}	// Constructor
	
	bool out() override{
		if (control==1 || control==0)
			return control;
		if (first->out()==1 && second->out()==1){
			control=1;
			return 1;
		}
		else{
			control=0;
			return 0;
		}
	}
};