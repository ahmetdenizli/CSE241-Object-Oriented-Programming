#ifndef SPARSEVECTOR_H
#define	SPARSEVECTOR_H

#include <fstream>
#include <vector>
#include <string>

class SparseVector {
public:
	//Base constructor
	SparseVector();
	//Constructor takes a string filename data, opens the file, reads the contents, creates and populates an object.
	SparseVector(const std::string &File);

	// Creates another SparseVector object, assign adds two SparseVector and return it.
	SparseVector operator+(const SparseVector& other);
	// Creates another SparseVector object, assign Subtracts one SparseVector from another and return it.
	SparseVector operator-(const SparseVector& other);
	// Creates another SparseVector object which is element-by-element negative of the operant and return it.
	SparseVector operator-();
	// Assigns one SparseVector to another
	SparseVector& operator=(const SparseVector& other);

	// friend function
	// Creates the text representation of a SparseVector and sends it to a std::ostream object.
	friend std::ostream& operator<<(std::ostream &output_stream, const SparseVector& obj);

	// friend function
	// Calculates the dot product(inner product) of two SparseVectors. Returns a real number.
	friend double dot(const SparseVector& lhs, const SparseVector& rhs);

private:
	std::vector<double> SparseVec;

};

#endif	/* SPARSEVECTOR_H */