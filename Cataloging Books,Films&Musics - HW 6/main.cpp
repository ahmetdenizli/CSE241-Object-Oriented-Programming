/*##############################################*/
/*				  Ahmet Denizli  				*/
/*					161044020					*/
/*##############################################*/
#include <iostream>
#include <algorithm>	// std::sort
#include <fstream>
#include <vector>		// std::vector
#include "Catalog.h"	// For catalog and inherited class implementations

struct missing_field {};		// Empty struct for missing field exception
struct duplicate {};			// Empty struct for duplicate exception
struct wrong_command {};		// Empty struct for wrong command exception

// This function reads "data.txt" and creates necessary objects of Catalogs and keeps the log of the catalog read operations.
void readData(ifstream& InputFile, ofstream& OutputFile, vector<Catalog*>& vec, string& catalog_type);
// This function reads "commands.txt" and keeps the log of the output of commands operations.
void readCommands(ifstream& InputFile, ofstream& OutputFile, vector<Catalog*>& vec, string& catalog_type);
// Write searched word in Catalog to the OutputFile
void write_search(ofstream& OutputFile, Catalog* ptr, string& ctlg_type, string& word, string& keyword);
// Write sorted Catalog to the OutputFile
void write_sorted(ofstream& OutputFile, vector<Catalog*>& vec, string& ctlg_type);

//reading lines in a loop a helper function in order to secure file read operations
int check_errors(ifstream* f);

int main(int argc, char const *argv[])
{
	ifstream DataFile("data.txt"), CommandFile("commands.txt");				// Declaring ifstream obj
	ofstream OutputFile("output.txt");										// Declaring ofstream obj

	vector<Catalog*> vec;					// using STL container vector of Catalog*
	string catalog_type;					// declare string for catolog_type

	readData(DataFile, OutputFile, vec, catalog_type);
	readCommands(CommandFile, OutputFile, vec, catalog_type);

	for (int i = 0; i < vec.size(); ++i)	// Deleting objects dynamic memory
		delete vec[i];

	DataFile.close();			// Closing "data.txt"
	CommandFile.close();		// Closing "commands.txt"
	OutputFile.close();			// Closing "output.txt"
	return 0;
}

// This function reads "data.txt" and creates necessary objects of Catalogs and keeps the log of the catalog read operations.
void readData(ifstream& InputFile, ofstream& OutputFile, vector<Catalog*>& vec, string& catalog_type){
	int k=0;
	string ctlg_type, line, temp1, str[5];				// Declaring string variables
	size_t found, fnd2;										// Declaring variable for position
	Catalog* obj;

	if (InputFile.is_open())
	{
		InputFile >> ctlg_type;						// getting Catalog type
		getline(InputFile, line);					// getline for empt \n row
		catalog_type = ctlg_type;					// assing ctlg_type to Catalog type
		OutputFile << "Catalog Read: " << ctlg_type << endl;

		while (1)									// While loop for reading line by line to the eof
		{
			k=0;
			getline(InputFile, line);
			if (check_errors(&InputFile))			// If eof break;
				break;

			temp1 = line;
			found = temp1.find('"');				// Assign the position of the " character of the first match
			while (found!= string::npos){			// While " character found
				temp1 = temp1.substr(found+1);		// Taking substr from the " character
				fnd2 = temp1.find('"');				// Assign the position of the " character of the first match
				str[k] = temp1.substr(0, fnd2);		// Taking substr up to the " character about information of catalog
				k++;

				temp1 = temp1.substr(fnd2+1);
				found = temp1.find('"');
			}

			try{
				if (ctlg_type == "book" || ctlg_type == "music")	// If catolog type is book or music
				{
					if (k!=4)										// Controlling for missing field and throw if it is missing field
						throw missing_field();
					for (int i = 0; i < vec.size(); ++i)
					{
						if (str[0] == vec[i]->get_title())
							throw duplicate();
					}

					if (ctlg_type == "book"){
						obj = new Book(str[0], str[1], str[2], str[3]);
						vec.push_back(obj);
					}
					else if (ctlg_type == "music"){
						obj = new Music(str[0], str[1], str[2], str[3]);
						vec.push_back(obj);
					}
				}
				else if (ctlg_type == "movie")						// If catolog type is movie
				{
					if (k!=5)										// Controlling for missing field and throw if it is missing field
						throw missing_field();
					for (int i = 0; i < vec.size(); ++i)			// Controlling for duplicate entry and throw duplicate if it is
					{
						if (str[0] == vec[i]->get_title())
							throw duplicate();
					}

					obj = new Movie(str[0], str[1], str[2], str[3], str[4]);
					vec.push_back(obj);
				}
			}
			catch(missing_field& e){									// Catch missing field exception
				OutputFile << "Exception: missing field" << endl;
				int i;
				for ( i = 0; i < k-1; ++i)
					OutputFile << "\"" << str[i] << "\" ";
				OutputFile << "\"" << str[i] << "\"" << endl;
			}
			catch(duplicate& e){
				OutputFile << "Exception:  duplicate entry" << endl;	// Catch duplicate exception
				int i;
				for ( i = 0; i < k-1; ++i)
					OutputFile << "\"" << str[i] << "\" ";
				OutputFile << "\"" << str[i] << "\"" << endl;
			}
		}
		OutputFile << vec.size() << " unique entries" << endl;
	}

}

// This function reads "commands.txt" and keeps the log of the output of commands operations.
void readCommands(ifstream& InputFile, ofstream& OutputFile, vector<Catalog*>& vec, string& catalog_type){
	int k=0;
	string command, word, temp, keyword;
	size_t found;				// Declaring variables for positions

	if (InputFile.is_open())
	{
		while(InputFile >> command){							// taking command for every line
			try{
				if (command == "search")						// if command is search
				{
					InputFile >> word >> temp >> keyword;		// taking word and keyword from file
					word = word.substr(1);						// erase "" from word
					found = word.find('"');
					word = word.substr(0, found);

					keyword = keyword.substr(1);				// erase "" from keyword
					found = keyword.find('"');
					keyword = keyword.substr(0, found);

					if (catalog_type == "book")
					{
						if (keyword == "title"){
							for (int i = 0; i < vec.size(); ++i)
							{
								found = (vec[i]->get_title()).find(word);
								if (found!=string::npos)
									write_search(OutputFile, vec[i], catalog_type, word, keyword);
							}
						}
						else if (keyword == "year"){
							for (int i = 0; i < vec.size(); ++i)
							{
								if (vec[i]->get_year() == word)
									write_search(OutputFile, vec[i], catalog_type, word, keyword);
							}
						}
						else if (keyword == "authors"){
							for (int i = 0; i < vec.size(); ++i)
							{
								found = (dynamic_cast<Book*>(vec[i])->get_authors()).find(word);
								if (found!=string::npos)
									write_search(OutputFile, vec[i], catalog_type, word, keyword);
							}
						}
						else if (keyword == "tags"){
							for (int i = 0; i < vec.size(); ++i)
							{
								found = (dynamic_cast<Book*>(vec[i])->get_tags()).find(word);
								if (found!=string::npos)
									write_search(OutputFile, vec[i], catalog_type, word, keyword);
							}
						}
						else
							throw wrong_command();
					}

					if (catalog_type == "music")
					{
						if (keyword == "title"){
							for (int i = 0; i < vec.size(); ++i)
							{
								found = (vec[i]->get_title()).find(word);
								if (found!=string::npos)
									write_search(OutputFile, vec[i], catalog_type, word, keyword);
							}
						}
						else if (keyword == "year"){
							for (int i = 0; i < vec.size(); ++i)
							{
								if (vec[i]->get_year() == word)
									write_search(OutputFile, vec[i], catalog_type, word, keyword);
							}
						}
						else if (keyword == "artists"){
							for (int i = 0; i < vec.size(); ++i)
							{
								found = (dynamic_cast<Music*>(vec[i])->get_artists()).find(word);
								if (found!=string::npos)
									write_search(OutputFile, vec[i], catalog_type, word, keyword);
							}
						}
						else if (keyword == "genre"){
							for (int i = 0; i < vec.size(); ++i)
							{
								found = (dynamic_cast<Music*>(vec[i])->get_genre()).find(word);
								if (found!=string::npos)
									write_search(OutputFile, vec[i], catalog_type, word, keyword);
							}
						}
						else
							throw wrong_command();
					}

					if (catalog_type == "movie")
					{
						if (keyword == "title"){
							for (int i = 0; i < vec.size(); ++i)
							{
								found = (vec[i]->get_title()).find(word);
								if (found!=string::npos)
									write_search(OutputFile, vec[i], catalog_type, word, keyword);
							}
						}
						else if (keyword == "year"){
							for (int i = 0; i < vec.size(); ++i)
							{
								if (vec[i]->get_year() == word)
									write_search(OutputFile, vec[i], catalog_type, word, keyword);
							}
						}
						else if (keyword == "director"){
							for (int i = 0; i < vec.size(); ++i)
							{
								found = (dynamic_cast<Movie*>(vec[i])->get_director()).find(word);
								if (found!=string::npos)
									write_search(OutputFile, vec[i], catalog_type, word, keyword);
							}
						}
						else if (keyword == "genre"){
							for (int i = 0; i < vec.size(); ++i)
							{
								found = (dynamic_cast<Movie*>(vec[i])->get_genre()).find(word);
								if (found!=string::npos)
									write_search(OutputFile, vec[i], catalog_type, word, keyword);
							}
						}
						else if (keyword == "starring"){
							for (int i = 0; i < vec.size(); ++i)
							{
								found = (dynamic_cast<Movie*>(vec[i])->get_starring()).find(word);
								if (found!=string::npos)
									write_search(OutputFile, vec[i], catalog_type, word, keyword);
							}
						}
						else
							throw wrong_command();
					}
				}
				else if (command == "sort")
				{
					InputFile >> word;
					word = word.substr(1);				// erase "" from word
					found = word.find('"');
					word = word.substr(0, found);

					if (catalog_type == "book")
					{
						if (word == "title")
						{
							//using sort functinon from STL
							sort( vec.begin( ), vec.end( ), [ ]( Catalog* lhs, Catalog* rhs ) { return lhs->get_title() < rhs->get_title(); } ); 
							OutputFile << "sort \"" << word << "\"" << endl;
							write_sorted(OutputFile, vec, catalog_type);
						}
						else if (word == "year")
						{
							//using sort functinon from STL
							sort( vec.begin( ), vec.end( ), [ ]( Catalog* lhs, Catalog* rhs ) { return lhs->get_year() < rhs->get_year(); } ); 
							OutputFile << "sort \"" << word << "\"" << endl;
							write_sorted(OutputFile, vec, catalog_type);
						}
						else if (word == "authors")
						{
							//using sort functinon from STL
							sort( vec.begin( ), vec.end( ), [ ]( Catalog* lhs, Catalog* rhs ) { return dynamic_cast<Book*>(lhs)->get_authors() < dynamic_cast<Book*>(rhs)->get_authors(); } ); 
							OutputFile << "sort \"" << word << "\"" << endl;
							write_sorted(OutputFile, vec, catalog_type);
						}
						else if (word == "tags")
						{
							//using sort functinon from STL
							sort( vec.begin( ), vec.end( ), [ ]( Catalog* lhs, Catalog* rhs ) { return dynamic_cast<Book*>(lhs)->get_tags() < dynamic_cast<Book*>(rhs)->get_tags(); } ); 
							OutputFile << "sort \"" << word << "\"" << endl;
							write_sorted(OutputFile, vec, catalog_type);
						}
						else
							throw wrong_command();
					}
					if (catalog_type == "music")
					{
						if (word == "title")
						{
							//using sort functinon from STL
							sort( vec.begin( ), vec.end( ), [ ]( Catalog* lhs, Catalog* rhs ) { return lhs->get_title() < rhs->get_title(); } ); 
							OutputFile << "sort \"" << word << "\"" << endl;
							write_sorted(OutputFile, vec, catalog_type);
						}
						else if (word == "year")
						{
							//using sort functinon from STL
							sort( vec.begin( ), vec.end( ), [ ]( Catalog* lhs, Catalog* rhs ) { return lhs->get_year() < rhs->get_year(); } );
							OutputFile << "sort \"" << word << "\"" << endl;
							write_sorted(OutputFile, vec, catalog_type);
						}
						else if (word == "artists")
						{
							//using sort functinon from STL
							sort( vec.begin( ), vec.end( ), [ ]( Catalog* lhs, Catalog* rhs ) { return dynamic_cast<Music*>(lhs)->get_artists() < dynamic_cast<Music*>(rhs)->get_artists(); } );
							OutputFile << "sort \"" << word << "\"" << endl;
							write_sorted(OutputFile, vec, catalog_type);
						}
						else if (word == "genre")
						{
							//using sort functinon from STL
							sort( vec.begin( ), vec.end( ), [ ]( Catalog* lhs, Catalog* rhs ) { return dynamic_cast<Music*>(lhs)->get_genre() < dynamic_cast<Music*>(rhs)->get_genre(); } );
							OutputFile << "sort \"" << word << "\"" << endl;
							write_sorted(OutputFile, vec, catalog_type);
						}
						else
							throw wrong_command();

					}
					if (catalog_type == "movie")
					{
						if (word == "title")
						{
							//using sort functinon from STL
							sort( vec.begin( ), vec.end( ), [ ]( Catalog* lhs, Catalog* rhs ) { return lhs->get_title() < rhs->get_title(); } );
							OutputFile << "sort \"" << word << "\"" << endl;
							write_sorted(OutputFile, vec, catalog_type);
						}
						else if (word == "year")
						{
							//using sort functinon from STL
							sort( vec.begin( ), vec.end( ), [ ]( Catalog* lhs, Catalog* rhs ) { return lhs->get_year() < rhs->get_year(); } );
							OutputFile << "sort \"" << word << "\"" << endl;
							write_sorted(OutputFile, vec, catalog_type);
						}
						else if (word == "director")
						{
							//using sort functinon from STL
							sort( vec.begin( ), vec.end( ), [ ]( Catalog* lhs, Catalog* rhs ) { return dynamic_cast<Movie*>(lhs)->get_director() < dynamic_cast<Movie*>(rhs)->get_director(); } );
							OutputFile << "sort \"" << word << "\"" << endl;
							write_sorted(OutputFile, vec, catalog_type);
						}
						else if (word == "genre")
						{
							//using sort functinon from STL
							sort( vec.begin( ), vec.end( ), [ ]( Catalog* lhs, Catalog* rhs ) { return dynamic_cast<Movie*>(lhs)->get_genre() < dynamic_cast<Movie*>(rhs)->get_genre(); } );
							OutputFile << "sort \"" << word << "\"" << endl;
							write_sorted(OutputFile, vec, catalog_type);
						}
						else if (word == "starring")
						{
							//using sort functinon from STL
							sort( vec.begin( ), vec.end( ), [ ]( Catalog* lhs, Catalog* rhs ) { return dynamic_cast<Movie*>(lhs)->get_starring() < dynamic_cast<Movie*>(rhs)->get_starring(); } );
							OutputFile << "sort \"" << word << "\"" << endl;
							write_sorted(OutputFile, vec, catalog_type);
						}
						else
							throw wrong_command();
					}
				}
			}
			catch(wrong_command& e){															// Catch wrong command exception
				OutputFile << "Exception: command is wrong" << endl;
				if (command == "search")
					OutputFile << "search \"" << word << "\" in \"" << keyword << "\"" << endl;
				else if (command == "sort")
					OutputFile << "sort \"" << word << "\"" << endl;
			}
		}
	}
}

// Write searched word in Catalog to the OutputFile
void write_search(ofstream& OutputFile, Catalog* ptr, string& ctlg_type, string& word, string& keyword){
	if (ctlg_type == "book"){
		OutputFile << "search \"" << word << "\" in \"" << keyword << "\"" << endl;
		OutputFile << "\"" << ptr->get_title() << "\" " << "\"" << ptr->get_year() << "\" " << "\"" << dynamic_cast<Book*>(ptr)->get_authors() << "\" " << "\"" << dynamic_cast<Book*>(ptr)->get_tags() << "\"" << endl;
	}
	else if (ctlg_type == "music"){
		OutputFile << "search \"" << word << "\" in \"" << keyword << "\"" << endl;
		OutputFile << "\"" << ptr->get_title() << "\" " << "\"" << ptr->get_year() << "\" " << "\"" << dynamic_cast<Music*>(ptr)->get_artists() << "\" " << "\"" << dynamic_cast<Music*>(ptr)->get_genre() << "\"" << endl;
	}
	else if (ctlg_type == "movie"){
		OutputFile << "search \"" << word << "\" in \"" << keyword << "\"" << endl;
		OutputFile << "\"" << ptr->get_title() << "\" " << "\"" << ptr->get_year() << "\" " << "\"" << dynamic_cast<Movie*>(ptr)->get_director() << "\" " << "\"" << dynamic_cast<Movie*>(ptr)->get_genre() << "\" " << "\"" << dynamic_cast<Movie*>(ptr)->get_starring() << "\"" << endl;
	}
}

// Write sorted Catalog to the OutputFile
void write_sorted(ofstream& OutputFile, vector<Catalog*>& vec, string& ctlg_type){
	if (ctlg_type == "book"){
		for (int i = 0; i < vec.size(); ++i)
		{
			OutputFile << "\"" << vec[i]->get_title() << "\" " << "\"" << vec[i]->get_year() << "\" " << "\"" << dynamic_cast<Book*>(vec[i])->get_authors() << "\" " << "\"" << dynamic_cast<Book*>(vec[i])->get_tags() << "\"" << endl;
		}
	}
	else if (ctlg_type == "music"){
		for (int i = 0; i < vec.size(); ++i)
		{
			OutputFile << "\"" << vec[i]->get_title() << "\" " << "\"" << vec[i]->get_year() << "\" " << "\"" << dynamic_cast<Music*>(vec[i])->get_artists() << "\" " << "\"" << dynamic_cast<Music*>(vec[i])->get_genre() << "\"" << endl;
		}
	}
	else if (ctlg_type == "movie"){
		for (int i = 0; i < vec.size(); ++i)
		{
			OutputFile << "\"" << vec[i]->get_title() << "\" " << "\"" << vec[i]->get_year() << "\" " << "\"" << dynamic_cast<Movie*>(vec[i])->get_director() << "\" " << "\"" << dynamic_cast<Movie*>(vec[i])->get_genre() << "\" " << "\"" << dynamic_cast<Movie*>(vec[i])->get_starring() << "\"" << endl;
		}
	}
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