/*##############################################*/
/*				  Ahmet Denizli  				*/
/*					161044020					*/
/*##############################################*/
#include <string>

using namespace std;

class Catalog {
public:
	Catalog(){}

	virtual const string get_title() const {return title;}										// Gets title
	virtual const string get_year() const {return year;}										// Gets year

protected:
	string title;			// string title
	string year;			// string year
};

class Book : public Catalog {
public:
	Book() {}
	Book(const string _title, const string _authors, const string _year, const string _tags) 
					{ title = _title; authors = _authors; year = _year; tags = _tags;}	// Sets data

	void set_data(const string _title, const string _authors, const string _year, const string _tags) 
					{ title = _title; authors = _authors; year = _year; tags = _tags;}	// Sets data
	const string get_authors() const {return authors;}									// Gets authors
	const string get_tags() const {return tags;}										// Gets tags

private:
	string authors;			// private data string authors
	string tags;			// private data string tags
};

class Music : public Catalog {
public:
	Music() {}
	Music(const string _title, const string _artists, const string _year, const string _genre) 
					{ title = _title; artists = _artists; year = _year; genre = _genre;}

	void set_data(const string _title, const string _artists, const string _year, const string _genre) 
					{ title = _title; artists = _artists; year = _year; genre = _genre;}	// Sets data
	const string get_artists() const {return artists;}									// Gets artists
	const string get_genre() const {return genre;}										// Gets genre

private:
	string artists;			// private data string artists
	string genre;			// private data string genre
};

class Movie : public Catalog {
public:
	Movie() {}
	Movie(const string _title, const string _director, const string _year, const string _genre, const string _starring) 
					{ title = _title; director = _director; year = _year; genre = _genre; starring=_starring;}

	void set_data(const string _title, const string _director, const string _year, const string _genre, const string _starring) 
					{ title = _title; director = _director; year = _year; genre = _genre; starring=_starring;}	// Sets data
	const string get_director() const {return director;}								// Gets director
	const string get_genre() const {return genre;}										// Gets genre
	const string get_starring() const {return starring;}								// Gets starring

private:
	string director;		// private data string director
	string genre;			// private data string genre
	string starring;		// private data string starring
};