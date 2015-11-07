#include "Rating.h"

Rating::Rating(): size(0), head(NULL), tail(NULL), iterator(NULL) {}

Rating::Rating(string _description, int _stars, string _owner)
{
    if (head == NULL)
    {
        head = new Data(_description, _stars, _owner);
        tail = head;
        iterator = head;
    }
    else
    {
        Noderef newData = new Data(_description, _stars, _owner);
        tail->next = newData;
        newData->previous = tail;
        tail = newData;
    }
}

// Getter Function Definitions
string Rating::getDescription()
{
    return iterator->description;
}

int Rating::getStars()
{
    return iterator->stars;
}

string Rating::getOwner()
{
    return iterator->owner;
}


// Setter Function Definitions //
void Rating::changeDescription(string _description)
{
    iterator->description = _description;
}

void Rating::changeStars(int _stars)
{
    iterator->stars = _stars;
}

void Rating::changeOwner(string _owner)
{
    iterator->owner = _owner;
}
