#include "Rating.h"
#include <iostream>

using namespace std;

Rating::Rating(): size(0), head(NULL), tail(NULL), iterator(NULL) {}

Rating::Rating(string _description, int _stars, string _owner)
{
    if (head == NULL)
    {
        head = new Data(_description, _stars, _owner);
        tail = head;
        iterator = head;
        size++;
    }
    else
    {
        Noderef newData = new Data(_description, _stars, _owner);
        tail->next = newData;
        newData->previous = tail;
        tail = newData;
        size++;
    }
}

void Rating::newReview(string _description, int _stars, string _owner)
{
    if (size == 0)
    {
        head = new Data(_description, _stars, _owner);
        tail = head;
        iterator = head;
        size++;
    }
    else
    {
        Noderef newData = new Data(_description, _stars, _owner);
        tail->next = newData;
        newData->previous = tail;
        tail = newData;
        size++;
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

// Manipulator Functions for Linked List
int Rating::currentStar()
{
    if (iterator != NULL)
        return iterator->stars;
    else
    {
        iterator = head;
        return (0000);
    }
}

string Rating::currentOwner()
{
    if (iterator != NULL)
        return iterator->owner;
    else
    {
        iterator = head;
        return ("nonValid");
    }
}

bool Rating::off_end()
{
    if (iterator == NULL)
        return true;
    else
        return false;
}

int Rating::get_size()
{
    return size;
}

void Rating::begin()
{
    if (size != 0)
        iterator = head;
}

void Rating::remove()
{
    if (off_end())
        cout << "The iterator is not pointint to anything.\n";
    else if (iterator == tail)
        pop_back();
    else
    {
        Noderef temp = iterator->next;
        iterator->next = iterator->next->next;
        delete temp;
        size--;
    }
}

void Rating::pop_back()
{
    if (size == 1)
    {
        delete head;
        head = tail = iterator = NULL;
        
        size = 0;
    }
    else
    {
        Noderef temp = tail;
        iterator = head;
        while (iterator != tail)
        {
            if (iterator->next == tail)
            {
                tail->previous = NULL;
                tail = iterator;
                iterator->next = NULL;
                delete temp;
            }
            else
                iterator = iterator->next;
        }
        size--;
    }
}

void Rating::scroll()
{
    int choice;
    
    if (iterator->next != NULL)
        iterator = iterator->next;
    else
    {
        cout << "You've reached the end of the list.\n";
        cout << "Would you like to scroll from the beginning-(1) or backwards-(2)?";
        cin >> choice;
        if (choice == 1)
            begin();
        else if (choice == 2)
            scrollBackward();
    }
}

void Rating::scrollBackward()
{
    int choice;
    
    if (iterator->previous != NULL)
        iterator = iterator->previous;
    else
    {
        cout << "You've reached the start of the list.\n";
        cout << "Would you like to scroll forward (Y/N) ?";
        cin >> choice;
        if (choice == 'Y')
            scroll();
    }
}

void Rating::printAll()
{
    iterator = head;
    cout << "Printing data: ";
    while (iterator != NULL)
    {
        cout << iterator->stars << endl;
        cout << iterator->owner << endl;
        cout << iterator->description << endl << endl;
        iterator = iterator->next;
    }
}

void Rating::print()
{
    if (off_end())
        cout << "The iterator is not pointing to anyting\n";
    else
    {
        cout << "Stars: " << iterator->stars << endl;
        cout << "Owner: " << iterator->owner << endl;
        cout << "Description: " << iterator->description << endl << endl;
    }
}

bool Rating::searchByOwner(string _owner)   
{
    bool found = false;
    
    if (size != 0)
    {
        iterator = head;
        while (iterator != NULL)
        {
            if (_owner == iterator->owner)
            {
                found = true;
                return found;
            }
            else
            {
                if (iterator->next != NULL)
                {
                    iterator = iterator->next;
                }
                else
                    return found;
            }
        }
    }
    else
        return found;
    
    return found;
}








