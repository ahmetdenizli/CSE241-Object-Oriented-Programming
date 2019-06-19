/*##############################################*/
/*				  Ahmet Denizli  				*/
/*					161044020					*/
/*##############################################*/
#include <iostream>
#include "SparseVector.h"
#include "SparseMatrix.h"

using namespace std;

int main()
{
	ofstream outfile;
	outfile.open("output.txt", ios::out | ios::trunc );

	//Creating a SparseVector from file
	SparseVector a1("a1.txt");
	outfile<<"a1"<<endl<<a1<<endl;

	//Binary operations and assignment
	a1 = a1 + a1;
	outfile<<"a1"<<endl<<a1<<endl;

	//Creating SparseMatrix from file
	SparseMatrix m1("m1.txt");
	SparseMatrix m2("m2.txt");
	outfile<<"m2"<<endl<<m2<<endl;

	//Transpose
	outfile<<m2.transpose()<<endl;

	//Dot product
	outfile<<dot(a1,a1)<<endl;

	return 0;
}