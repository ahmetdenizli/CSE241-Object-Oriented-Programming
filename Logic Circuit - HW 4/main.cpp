/*##############################################*/
/*				  Ahmet Denizli  				*/
/*					161044020					*/
/*##############################################*/
#include <iostream>
#include <fstream>
#include <sstream>
#include "Gates.h"		// For class implementations

//reading lines in a loop a helper function in order to secure file read operations
int check_errors(ifstream* f);

// This function finds total gate numbers and return it
int GateNum(int &inp_count, int &out_count);

int main(int argc, char const *argv[])
{
	int m=0, inp_count=0, out_count=0, input, gate_num, temp;
	// taking gate numbers, input count and output count
	gate_num = GateNum(inp_count, out_count);
	string keyword, a, b, c, d, e, f, out_names[out_count];		// Declaring string variables for read.
	Gate *g1, *g2, *g3, *g4, *g5, *g6, *arr[gate_num];			// Declaring gate pointers and gate pointer array for circuit. 

	ifstream InputFile;

	// Creating gate objects for circuit.txt
	InputFile.open("circuit.txt");
	if (InputFile.is_open()){
		InputFile >> keyword;

		for (int i = 0; i < inp_count; ++i)		// Creating input objects
		{
			InputFile >> a;
			g1 = new Inp(a);	arr[m] = g1;
			m++;
		}

		InputFile >> keyword;
		for (int i = 0; i < out_count; ++i){	// Looking output gate names and store in out_names string array
			InputFile >> a;
			out_names[i] = a;
		}

		while ( InputFile >> keyword )		// While loop for Creating gate objects
		{
			if (keyword == "AND")
			{
				InputFile >> a >> b >> c;
				g1 = new And(a);	arr[m] = g1;
				m++;
			}
			else if (keyword == "OR")
			{
				InputFile >> a >> b >> c;
				g1 = new Or(a);	arr[m] = g1;
				m++;
			}
			else if (keyword == "NOT")
			{
				InputFile >> a >> b;
				g1 = new Not(a);	arr[m] = g1;
				m++;
			}
			else if (keyword == "FLIPFLOP")
			{
				InputFile >> a >> b;
				g1 = new FlipFlop(a);
				static_cast<FlipFlop*>(g1)->set_f_out(0);	// initializing former-out 0
				arr[m] = g1;
				m++;
			}
			else if (keyword == "DECODER")
			{
				InputFile >> a >> b >> c >> d >> e >> f;
				g1 = new Decoder1(a);	arr[m] = g1;
				m++;
				g1 = new Decoder2(b);	arr[m] = g1;
				m++;
				g1 = new Decoder3(c);	arr[m] = g1;
				m++;
				g1 = new Decoder4(d);	arr[m] = g1;
				m++;
			}
		}
	}
	InputFile.close();

	// Connecting gates first and second inputs for circuit.txt
	InputFile.open("circuit.txt");
	if (InputFile.is_open()){

		InputFile >> keyword;
		for (int i = 0; i < inp_count; ++i)		// For loop to the end of input line
			InputFile >> a;
		
		InputFile >> keyword;
		for (int i = 0; i < out_count; ++i)		// For loop to the end of output line
			InputFile >> a;

		while ( InputFile >> keyword )			// While loop for connecting gate inputs
		{
			if (keyword == "AND")
			{
				InputFile >> a >> b >> c;
				for (int i = 0; i < gate_num; ++i)
				{
					if (arr[i]->get_name()==a)
						g1 = arr[i];
					if (arr[i]->get_name()==b)
						g2 = arr[i];
					if (arr[i]->get_name()==c)
						g3 = arr[i];
				}
				g1->set_Gates(g2, g3);		// Sets 'a' AND gate inputs are identified b and c
			}
			else if (keyword == "OR")
			{
				InputFile >> a >> b >> c;
				for (int i = 0; i < gate_num; ++i)
				{
					if (arr[i]->get_name()==a)
						g1 = arr[i];
					if (arr[i]->get_name()==b)
						g2 = arr[i];
					if (arr[i]->get_name()==c)
						g3 = arr[i];
				}
				g1->set_Gates(g2, g3);		// Sets 'a' OR gate inputs are identified b and c
			}
			else if (keyword == "NOT")
			{
				InputFile >> a >> b;
				for (int i = 0; i < gate_num; ++i)
				{
					if (arr[i]->get_name()==a)
						g1 = arr[i];
					if (arr[i]->get_name()==b)
						g2 = arr[i];
				}
				g1->set_Gate1(g2);			// Sets 'a' NOT gate input are identified b
			}
			else if (keyword == "FLIPFLOP")
			{
				InputFile >> a >> b;
				for (int i = 0; i < gate_num; ++i)
				{
					if (arr[i]->get_name()==a)
						g1 = arr[i];
					if (arr[i]->get_name()==b)
						g2 = arr[i];
				}
				g1->set_Gate1(g2);			// Sets 'a' FLIPFLOP gate input are identified b
			}
			else if (keyword == "DECODER")
			{
				InputFile >> a >> b >> c >> d >> e >> f;
				for (int i = 0; i < gate_num; ++i)
				{
					if (arr[i]->get_name()==a)
						g1 = arr[i];
					if (arr[i]->get_name()==b)
						g2 = arr[i];
					if (arr[i]->get_name()==c)
						g3 = arr[i];
					if (arr[i]->get_name()==d)
						g4 = arr[i];
					if (arr[i]->get_name()==e)
						g5 = arr[i];
					if (arr[i]->get_name()==f)
						g6 = arr[i];
				}
				g1->set_Gates(g5, g6);		// Sets 'a', 'b', 'c', 'd' DECODER gates inputs are identified e and f
				g2->set_Gates(g5, g6);		
				g3->set_Gates(g5, g6);
				g4->set_Gates(g5, g6);
			}
		}
	}
	InputFile.close();

	// Reading input.txt for inputs
	InputFile.open("input.txt");
	if (InputFile.is_open()){
		while ( InputFile >> input )
		{
			for (int i = 0; i < gate_num; ++i)		// For loop for clear control variable which is checks to see if the gate is worked once
				arr[i]->set_cont(-1);

			arr[0]->set_data(input);				// assign input to input gate
			for (int i = 1; i < inp_count; ++i)		// For loop to the input numbers for assign another inputs to input gates
			{
				InputFile >> input;
				arr[i]->set_data(input);
			}

			for (int i = 0; i < out_count; ++i)
			{
				for (int k = 0; k < gate_num; ++k)
				{
					if (arr[k]->get_name() == out_names[i]){	// Looking Gate pointer array for output gates
						temp = arr[k]->out();
						cout << temp << " ";
					}
				}
			}
			cout << endl;

		}
	}
	InputFile.close();

	// Deleting objects dynamic memory 
	for (int i = 0; i < gate_num; ++i)
		delete arr[i];

	return 0;
}

// This function finds total gate numbers and return it. Also find input count and output count
int GateNum(int &inp_count, int &out_count){
	int ret=0;
	string line, keyword, a;

	ifstream InputFile;
	InputFile.open("circuit.txt");
	if (InputFile.is_open()){
		while(1) {
			getline(InputFile, line);
			if (check_errors(&InputFile))
				break;

			stringstream ss(line);
			ss >> keyword;

			if (keyword == "INPUT")
			{
				while( ss >> a ){
					ret++;
					inp_count++;
				}
			}
			else if (keyword == "OUTPUT"){
				while( ss >> a ){
					out_count++;
				}
			}
			else if (keyword == "DECODER")
				ret+=4;
			else
				ret++;
		}
	}
	InputFile.close();

	return ret;
}

//reading lines in a loop
//a helper function in order to secure file read operations
int check_errors(ifstream* f) {
	int stop = 0;
	if (f->eof()) {
	// EOF after std::getline() is not the criterion to stop processing
	// data: In case there is data between the last delimiter and EOF,
	// getline() extracts it and sets the eofbit.
	stop = 0;
	}
	if (f->fail()) {
	stop = 1;
	}
	if (f->bad()) {
	stop = 1;
	}
	return stop;
}