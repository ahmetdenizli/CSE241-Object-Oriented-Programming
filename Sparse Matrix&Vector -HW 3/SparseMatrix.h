#ifndef SPARSEMATRIX_H
#define	SPARSEMATRIX_H

#include <fstream>
#include <vector>
#include <string>

class SparseMatrix {
public:
	//Base constructor
	SparseMatrix();
	//Constructor takes a string filename data, opens the file, reads the contents, creates and populates an object.
	SparseMatrix(const std::string &File);

	// Creates another SparseMatrix object, assign adds two SparseMatrix and return it.
	SparseMatrix operator+(const SparseMatrix& other);
	// Creates another SparseMatrix object, assign Subtracts one SparseMatrix from another and return it.
	SparseMatrix operator-(const SparseMatrix& other);
	// Creates another SparseMatrix object which is element-by-element negative of the operant and return it.
	SparseMatrix operator-();
	// Assigns one SparseMatrix to another
	SparseMatrix& operator=(const SparseMatrix& other);

	// friend function
	// Creates the text representation of a SparseMatrix and sends it to a std::ostream object.
	friend std::ostream& operator<<(std::ostream &output_stream, const SparseMatrix& obj);
	// Creates another SparseMatrix object which is the Multiplies two matrices (Regular matrix multiplication) and return it.
	SparseMatrix operator*( SparseMatrix& other);
	// Creates another SparseMatrix object which is the transpose of the original object and return it.
	SparseMatrix transpose();

private:
	std::vector< std::vector<double> > SparseMat;
};

#endif	/* SPARSEMATRIX_H */