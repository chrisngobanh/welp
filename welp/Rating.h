#ifndef RATING_H
#define RATING_H

#include <string>


using namespace std;

class Rating
{
private:
	struct Data
	{
		string description;
		int stars;
		string owner;

		Data * next;
		Data * previous;

		Data() : next(NULL), previous(NULL) {}
		Data(string _description, int _stars, string _owner) : next(NULL), previous(NULL)
		{
			description = _description;
			stars = _stars;
			owner = _owner;
		}
	};
	typedef struct Data * Noderef;

	Noderef head;
	Noderef tail;
	Noderef iterator;
	int size;


public:
	// Constructor
	Rating();
	Rating(string _description, int _stars, string _owner);


	// Getters
	string getDescription();
	int getStars();
	string getOwner();

	// Setters
	void changeDescription(string _description);
	void changeStars(int _stars);
	void changeOwner(string _owner);

	// Other Functions
	void newReview(string _description, int _stars, string _owner);
	int currentStar();
	//Returns the level of stars for the review where the iterator
	//is pointing to.

	string currentOwner();
	//Returns the name of the owner where the iterator is pointing to.

	bool off_end();
	//Determines if the iterator is off the end of the list.

	int get_size();
	//Returns the length of the list

	void begin();
	//Moves the iterator to point to the first review in the list

	void remove();
	//Removes the review pointed at by the iterator causing iterator to go off-end.

	void pop_back();
	//Removes the last review.

	void scroll();
	//Moves the iterator forward by one element in the list. Has no effect if the iterator
	//is off-end or the list is empty.

	void scrollBackward();
	//Moves the iterator backward by one element in the list. Has no effect if the iterator
	//is off-end or the list is empty.

	void printAll();
	///Prints to the console the reviews of each element in the list sequentially
	//and separated by a blank space

	void print();
	//Prints to the console the information for a single review which include number of
	//stars, owner's name, and review/description.

	bool searchByOwner(string _owner);
	//Searches the list of reviews by the name of the owner.

};

#endif