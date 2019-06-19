/*##############################################*/
/*				  Ahmet Denizli  				*/
/*					161044020					*/
/*##############################################*/
#include <iostream>
#include <sstream>
#include "SparseMatrix.h"

using namespace std;

//reading lines in a loop
//a helper function in order to secure file read operations
int check_errors(ifstream* f);

//Base constructor
SparseMatrix::SparseMatrix(){
	SparseMat.resize(1);
}

//Constructor takes a string filename data, opens the file, reads the contents, creates and populates an object.
SparseMatrix::SparseMatrix(const string &File){
	int row_index, index, k=0;
	double data;
	char ch;
	string line, temp;

	ifstream InputFile;
	InputFile.open(File);

	SparseMat.resize(1);

	if (InputFile.is_open()){
		while(1) {
			getline(InputFile, line);
			if (check_errors(&InputFile))
				break;

			if(SparseMat.size() == k)
				SparseMat.resize( k+1 );

			stringstream ss(line);

			ss >> row_index;
			SparseMat[k].push_back(row_index);

			while( ss >> index ){
				ss >> ch >> data;

				if (data != 0)
				{
					SparseMat[k].push_back(index);
					SparseMat[k].push_back(data);
				}
			}

			k++;
		}
	}
	InputFile.close();
}

// Creates another SparseMatrix object, assign adds two SparseMatrix and return it.
SparseMatrix SparseMatrix::operator+(const SparseMatrix& other){
	int size1 =SparseMat.size(), size2 =other.SparseMat.size(), col_size1, col_size2, k=0, j=0, row=0, x=1, y=1;
	SparseMatrix ret_Mat;

	for (int i = 0; i < (size1+size2); i++)
	{
		if (k >=size1 && j >=size2)
			break;
		if(ret_Mat.SparseMat.size() == row)
			ret_Mat.SparseMat.resize( k+1 );
		if (k <size1 && j <size2 && SparseMat[k][0] == other.SparseMat[j][0])
		{
			x=1; y=1;
			ret_Mat.SparseMat[row].push_back(SparseMat[k][0]);
			col_size1 = SparseMat[k].size();
			col_size2 = other.SparseMat[j].size();

			for (int m = 1; m < (col_size1 + col_size2); m+=2)
			{
				if (x >=col_size1 && y >=col_size2)
					break;
				if (x <col_size1 && y <col_size2 && SparseMat[k][x] == other.SparseMat[j][y])
				{
					ret_Mat.SparseMat[row].push_back(SparseMat[k][x]);
					ret_Mat.SparseMat[row].push_back(SparseMat[k][x+1] + other.SparseMat[j][y+1]);
					x+=2; y+=2;
				}
				else if (x <col_size1 && SparseMat[k][x] < other.SparseMat[j][y])
				{
					ret_Mat.SparseMat[row].push_back(SparseMat[k][x]);
					ret_Mat.SparseMat[row].push_back(SparseMat[k][x+1]);
					x+=2;
				}
				else if (y <col_size2 && other.SparseMat[j][y] < SparseMat[k][x])
				{
					ret_Mat.SparseMat[row].push_back(other.SparseMat[j][y]);
					ret_Mat.SparseMat[row].push_back(other.SparseMat[j][y+1]);
					y+=2;
				}
			}
			k++; j++; row++;
		}
		else if (k <size1 && SparseMat[k][0] < other.SparseMat[j][0])
		{
			for (int m = 0; m < SparseMat[k].size(); m++)
				ret_Mat.SparseMat[row].push_back(SparseMat[k][m]);

			k++; row++;
		}
		else if (j <size2 && other.SparseMat[j][0] < SparseMat[k][0])
		{
			for (int m = 0; m < other.SparseMat[j].size(); m++)
				ret_Mat.SparseMat[row].push_back(other.SparseMat[j][m]);

			j++; row++;
		}
	}

	return ret_Mat;
}

// Creates another SparseMatrix object, assign Subtracts one SparseMatrix from another and return it.
SparseMatrix SparseMatrix::operator-(const SparseMatrix& other){
	int size1 =SparseMat.size(), size2 =other.SparseMat.size(), col_size1, col_size2, k=0, j=0, row=0, x=1, y=1;
	SparseMatrix ret_Mat;

	for (int i = 0; i < (size1+size2); i++)
	{
		if (k >=size1 && j >=size2)
			break;
		if(ret_Mat.SparseMat.size() == row)
			ret_Mat.SparseMat.resize( k+1 );
		if (k <size1 && j <size2 && SparseMat[k][0] == other.SparseMat[j][0])
		{
			x=1; y=1;
			ret_Mat.SparseMat[row].push_back(SparseMat[k][0]);
			col_size1 = SparseMat[k].size();
			col_size2 = other.SparseMat[j].size();

			for (int m = 1; m < (col_size1 + col_size2); m+=2)
			{
				if (x >=col_size1 && y >=col_size2)
					break;
				if (x <col_size1 && y <col_size2 && SparseMat[k][x] == other.SparseMat[j][y])
				{
					ret_Mat.SparseMat[row].push_back(SparseMat[k][x]);
					ret_Mat.SparseMat[row].push_back(SparseMat[k][x+1] - other.SparseMat[j][y+1]);
					x+=2; y+=2;
				}
				else if (x <col_size1 && SparseMat[k][x] < other.SparseMat[j][y])
				{
					ret_Mat.SparseMat[row].push_back(SparseMat[k][x]);
					ret_Mat.SparseMat[row].push_back(SparseMat[k][x+1]);
					x+=2;
				}
				else if (y <col_size2 && other.SparseMat[j][y] < SparseMat[k][x])
				{
					ret_Mat.SparseMat[row].push_back(other.SparseMat[j][y]);
					ret_Mat.SparseMat[row].push_back(-(other.SparseMat[j][y+1]) );
					y+=2;
				}
			}
			k++; j++; row++;
		}
		else if (k <size1 && SparseMat[k][0] < other.SparseMat[j][0])
		{
			for (int m = 0; m < SparseMat[k].size(); m++)
				ret_Mat.SparseMat[row].push_back(SparseMat[k][m]);

			k++; row++;
		}
		else if (j <size2 && other.SparseMat[j][0] < SparseMat[k][0])
		{
			ret_Mat.SparseMat[row].push_back((other.SparseMat[j][0]) );
			for (int m = 1; m < other.SparseMat[j].size(); m+=2){
				ret_Mat.SparseMat[row].push_back(other.SparseMat[j][m]);
				ret_Mat.SparseMat[row].push_back(-(other.SparseMat[j][m+1]) );
			}

			j++; row++;
		}
	}

	return ret_Mat;
}

// Creates another SparseMatrix object which is element-by-element negative of the operant and return it.
SparseMatrix SparseMatrix::operator-(){
	int size =SparseMat.size();
	SparseMatrix ret_Mat;

	ret_Mat.SparseMat.resize(size);

	for (int i = 0; i < size; ++i){
		ret_Mat.SparseMat[i].push_back(SparseMat[i][0]);
		for (int m = 1; m < SparseMat[i].size(); m+=2)
		{
			ret_Mat.SparseMat[i].push_back(SparseMat[i][m]);
			ret_Mat.SparseMat[i].push_back(-(SparseMat[i][m+1]));
		}
	}

	return ret_Mat;
}

// Assigns one SparseMatrix to another
SparseMatrix& SparseMatrix::operator=(const SparseMatrix& other){
	if (this != &other) {		// self-assignment check expected
		SparseMat.clear();
		SparseMat.resize(other.SparseMat.size());

		for (int i = 0; i < other.SparseMat.size(); ++i){
			for (int m = 0; m < other.SparseMat[i].size(); ++m)
				SparseMat[i].push_back(other.SparseMat[i][m]);
		}
	}
	return *this;
}

// Creates the text representation of a SparseMatrix and sends it to a std::ostream object.
ostream& operator<<(ostream &output_stream, const SparseMatrix& obj){
	int size =obj.SparseMat.size();

	for (int i = 0; i < size; ++i)
	{
		output_stream << (int) obj.SparseMat[i][0] << " ";
		for (int m = 1; m < obj.SparseMat[i].size(); m+=2){
			output_stream << (int) obj.SparseMat[i][m] << ':' <<  obj.SparseMat[i][m+1] << " ";
		}
		output_stream << endl;
	}
	return output_stream;
}

// Creates another SparseMatrix object which is the Multiplies two matrices (Regular matrix multiplication) and return it.
SparseMatrix SparseMatrix::operator*( SparseMatrix& other){
	int size1 =SparseMat.size(), size2, col_size1, col_size2, sum=0, k=0, j=0, row=0, junk=0, junk2=0;;
	SparseMatrix ret_Mat, other_transpoze;

	other_transpoze = other.transpose();
	size2 =other_transpoze.SparseMat.size();
	ret_Mat.SparseMat.resize(1);

	for (int j = 0; j < size1; ++j)
	{
		junk2=0;
		for (int k = 0; k < size2; ++k)
		{
			sum=0;
			junk=0;
			for (int m = 1; m < other_transpoze.SparseMat[k].size(); m+=2){
				for (int i = 1; i < SparseMat[j].size(); i+=2){
					if (SparseMat[j][i] == other_transpoze.SparseMat[k][m])
					{
						sum += SparseMat[j][i+1] * other_transpoze.SparseMat[k][m+1];
						junk=1;
					}
				}
			}
			if (junk==1 && junk2==0){
				if (ret_Mat.SparseMat.size() == row)
					ret_Mat.SparseMat.resize(row+1);
				ret_Mat.SparseMat[row].push_back(SparseMat[j][0]);
				junk2=1;
			}
			if (junk==1)
			{
				ret_Mat.SparseMat[row].push_back(other_transpoze.SparseMat[k][0]);
				ret_Mat.SparseMat[row].push_back(sum);
			}
		}
		if (junk2==1)
			row++;
	}

	return ret_Mat;
}

// Creates another SparseMatrix object which is the transpose of the original object and return it.
SparseMatrix SparseMatrix::transpose(){
	int size =SparseMat.size(), row=0, count =0, junk=0;
	double temp;
	SparseMatrix ret_Mat;

	ret_Mat.SparseMat.resize(0);

	for (int i = 0; i < size; ++i){
		temp= SparseMat[i].size()-2;
		if(count < (SparseMat[i][temp]) )
			count = (int) SparseMat[i][temp];
	}

	for (int j = 0; j < count+1; ++j)
	{
		junk=0;
		for (int i = 0; i < size; ++i){
			for (int m = 1; m < SparseMat[i].size(); m+=2){
				if (SparseMat[i][m] == j){
					if (ret_Mat.SparseMat.size() == row)
						ret_Mat.SparseMat.resize(row+1);

					ret_Mat.SparseMat[row].push_back(j);
					row++;	junk=1;
					break;
				}
			}
			if (junk==1)
				break;
		}
	}

	row=0;
	for (int j = 0; j < count+1; ++j)
	{
		junk=0;
		for (int i = 0; i < size; ++i){
			for (int m = 1; m < SparseMat[i].size(); m+=2){
				if (SparseMat[i].size() < m+1)
					continue;

				if (SparseMat[i][m] == j)
				{
					ret_Mat.SparseMat[row].push_back(SparseMat[i][0]);
					ret_Mat.SparseMat[row].push_back(SparseMat[i][m+1]);
					junk=1;
				}
			}
		}
		if (junk==1)
			row++;
	}

	return ret_Mat;
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