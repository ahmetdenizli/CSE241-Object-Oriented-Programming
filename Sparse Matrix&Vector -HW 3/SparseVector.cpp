/*##############################################*/
/*				  Ahmet Denizli  				*/
/*					161044020					*/
/*##############################################*/
#include <iostream>
#include "SparseVector.h"

using namespace std;

SparseVector::SparseVector(){
	SparseVec.resize(0);
}

//Constructor takes a string filename data, opens the file, reads the contents, creates and populates an object.
SparseVector::SparseVector(const string &File){
	int index;
	double data;
	char ch;

	ifstream InputFile;
	InputFile.open(File);
	if (InputFile.is_open()){
		while ( InputFile >> index >> ch >> data )
		{
			if (data != 0)
			{
				SparseVec.push_back(index);
				SparseVec.push_back(data);
			}
		}
	}

	InputFile.close();
}

// Creates another SparseVector object, assign adds two SparseVector and return it.
SparseVector SparseVector::operator+(const SparseVector& other){
	int size1 =SparseVec.size(), size2 =other.SparseVec.size(), k=0, j=0;
	SparseVector ret_Vec;

	for (int i = 0; i < (size1+size2); i+=2)
	{
		if (k >size1 || j >size2)
			break;
		if (k <size1 && j <size2 && SparseVec[k] == other.SparseVec[j])
		{
			ret_Vec.SparseVec.push_back(SparseVec[k]);
			ret_Vec.SparseVec.push_back(SparseVec[k+1] + other.SparseVec[j+1]);
			k+=2; j+=2;
		}
		else if (k <size1 && SparseVec[k] < other.SparseVec[j])
		{
			ret_Vec.SparseVec.push_back(SparseVec[k]);
			ret_Vec.SparseVec.push_back(SparseVec[k+1]);
			k+=2;
		}
		else if (j <size2 && other.SparseVec[j] < SparseVec[k])
		{
			ret_Vec.SparseVec.push_back(other.SparseVec[j]);
			ret_Vec.SparseVec.push_back(other.SparseVec[j+1]);
			j+=2;
		}
	}
	return ret_Vec;
}

// Creates another SparseVector object, assign Subtracts one SparseVector from another and return it.
SparseVector SparseVector::operator-(const SparseVector& other){
	int size1 =SparseVec.size(), size2 =other.SparseVec.size(), k=0, j=0;
	SparseVector ret_Vec;

	for (int i = 0; i < (size1+size2); i+=2)
	{
		if (k <size1 && j <size2 && SparseVec[k] == other.SparseVec[j])
		{
			ret_Vec.SparseVec.push_back(k);
			ret_Vec.SparseVec.push_back(SparseVec[k+1] - other.SparseVec[j+1]);
			k+=2; j+=2;
		}
		else if (k <size1 && SparseVec[k] < other.SparseVec[j])
		{
			ret_Vec.SparseVec.push_back(k);
			ret_Vec.SparseVec.push_back(SparseVec[k+1]);
			k+=2;
		}
		else if (j <size2 && other.SparseVec[j] < SparseVec[k])
		{
			ret_Vec.SparseVec.push_back(j);
			ret_Vec.SparseVec.push_back(-(other.SparseVec[j+1]));
			j+=2;
		}
	}
	return ret_Vec;
}

// Creates another SparseVector object which is element-by-element negative of the operant and return it.
SparseVector SparseVector::operator-(){
	int size =SparseVec.size();
	SparseVector ret_Vec;

	for (int i = 0; i < size; i+=2){
		ret_Vec.SparseVec.push_back(i);
		ret_Vec.SparseVec.push_back(-(SparseVec[i+1]));
	}

	return ret_Vec;
}

// Assigns one SparseVector to another
SparseVector& SparseVector::operator=(const SparseVector& other){

	if (this != &other) {		// self-assignment check expected
		SparseVec.clear();

		for (int i = 0; i < other.SparseVec.size(); ++i)
			SparseVec.push_back(other.SparseVec[i]);
	}
	return *this;
}

// friend function
// Creates the text representation of a SparseVector and sends it to a std::ostream object.
ostream& operator<<(ostream &output_stream, const SparseVector& obj){
	int size =obj.SparseVec.size();

	for (int i = 0; i < size; i+=2)
	{
		output_stream << (int) obj.SparseVec[i] << ':' <<  obj.SparseVec[i+1] << ' ';
	}

	return output_stream;
}

// friend function
// Calculates the dot product(inner product) of two SparseVectors. Returns a real number.
double dot(const SparseVector& lhs, const SparseVector& rhs){
	int size1 =lhs.SparseVec.size(), size2 =rhs.SparseVec.size(), k=0, j=0;
	double ret_val =0;

	for (int i = 0; i < (size1+size2); i+=2)
	{
		if (k>size1 || j>size2)
			break;

		if (lhs.SparseVec[k] == rhs.SparseVec[j])
		{
			ret_val += (lhs.SparseVec[k+1] * rhs.SparseVec[j+1]);
			k+=2; j+=2;
		}
		else if (lhs.SparseVec[k] < rhs.SparseVec[j])
			k+=2;
		else if (rhs.SparseVec[j] < lhs.SparseVec[k])
			j+=2;
	}

	return ret_val;
}
