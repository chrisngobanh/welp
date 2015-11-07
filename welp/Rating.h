#ifndef RATING_H
#define RATING_H
#include <string>

using namespace std;

// TODO: Add a feature to allow editing Ratings
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
        
        Data(): next(NULL), previous(NULL) {}
        Data(string _description, int _stars, string _owner):  next(NULL), previous(NULL) {}
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
};

#endif