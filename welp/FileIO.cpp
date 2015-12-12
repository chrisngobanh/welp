#include "FileIO.h"

// Author(s): Kevin
// Gets the amount of cars
int getNumberOfCars()
{
    ifstream in("Kars Data.txt");
    if (in.is_open())
    {
        int length = 0;
        string line;
        in.clear();
        in.seekg(0, ios::beg);
        while (getline(in, line))
        {
            length++;
        }
        in.close();
        return length;
    }
    else
    {
        cout << "Error 1: Unable to open file \"Kars Data.txt\"" << endl << endl;
        return -1;
    }
}

// Authors(s): Kevin, Han
// Loads car data from Kars Data into an array
Car* load()
{
    Car* list = new Car[numOfCars];

    ifstream in("Kars Data.txt");
    if (in.is_open())
    {
        string line;
        int index = 0;

        int substr_start, offset;

        string make, model, type, engine;
        int mpgcity, mpgfree, msrp, views;

        char divider = '/';

        in.clear();
        in.seekg(0, ios::beg);
        while (getline(in, line))
        {
            //Get the make
            substr_start = 0;
            offset = 0;
            while (line[substr_start + offset] != divider)
            {
                offset++;
            }
            make = line.substr(substr_start, offset);
            substr_start = substr_start + offset + 1;
            offset = 0;

            //Get the model
            while (line[substr_start + offset] != divider)
            {
                offset++;
            }
            model = line.substr(substr_start, offset);
            substr_start = substr_start + offset + 1;
            offset = 0;

            //Get the mpgcity
            while (line[substr_start + offset] != divider)
            {
                offset++;
            }
            mpgcity = atoi(line.substr(substr_start, offset).c_str());
            substr_start = substr_start + offset + 1;
            offset = 0;

            //Get the mpgfree
            while (line[substr_start + offset] != divider)
            {
                offset++;
            }
            mpgfree = atoi(line.substr(substr_start, offset).c_str());
            substr_start = substr_start + offset + 1;
            offset = 0;

            //Get the engine
            while (line[substr_start + offset] != divider)
            {
                offset++;
            }
            engine = line.substr(substr_start, offset);
            substr_start = substr_start + offset + 1;
            offset = 0;

            //Get the price
            while (line[substr_start + offset] != divider)
            {
                offset++;
            }
            msrp = atoi(line.substr(substr_start, offset).c_str());
            substr_start = substr_start + offset + 1;
            offset = 0;

            //Get the views
            while (line[substr_start + offset] != '\0')
            {
                offset++;
            }
            views = atoi(line.substr(substr_start, offset).c_str());
            substr_start = substr_start + offset + 1;
            offset = 0;

            //make << model << engine << mpgcity <<  mpgfree << msrp
            list[index] = Car(make, model, engine, mpgcity, mpgfree, msrp);

            viewTable.addItem(make, model, views);
            index++;
            // << "Added successfully" << endl;
        }
        in.close();

        return list;
    }
    else
    {
        cout << "Error 2: Unable to open the file \"Kars Data.txt\"." << endl << endl;
        exit(-1);
    }
}

// Authors(s): Kevin, Han
// Loads review file into a hashtable
void loadReviewTable(HashTable<Review> &table)
{
    string line;

    int substr_start, offset;

    string make, model, owner, description;
    int stars;

    char divider = '/';

    ifstream in("reviews.txt");
    if (in.is_open())
    {
        in.clear();
        in.seekg(0, ios::beg);
        while (getline(in, line))
        {
            //Get the make
            substr_start = 0;
            offset = 0;
            while (line[substr_start + offset] != divider)
            {
                offset++;
            }
            make = line.substr(substr_start, offset);
            substr_start = substr_start + offset + 1;
            offset = 0;

            //Get the model
            while (line[substr_start + offset] != divider)
            {
                offset++;
            }
            model = line.substr(substr_start, offset);
            substr_start = substr_start + offset + 1;
            offset = 0;

            //Get the owner
            while (line[substr_start + offset] != divider)
            {
                offset++;
            }
            owner = line.substr(substr_start, offset);
            substr_start = substr_start + offset + 1;
            offset = 0;

            //Get the stars
            while (line[substr_start + offset] != divider)
            {
                offset++;
            }
            stars = atoi(line.substr(substr_start, offset).c_str());
            substr_start = substr_start + offset + 1;
            offset = 0;

            //Get the description
            while (line[substr_start + offset] != '\0')
            {
                offset++;
            }
            description = line.substr(substr_start, offset);
            substr_start = substr_start + offset + 1;
            offset = 0;

            //owner >> description >> stars >> make >> model
            Review review = Review(owner, description, stars, make, model);
            table.addItem(make, model, review);
        }
        in.close();
    }
    else
    {
        cout << "Error 3: Unable to open the file \"reviews.txt\"." << endl << endl;
        exit(-1);
    }
}

// Authors(s): Kevin, Han
// Sorts the car in a BST by MPG
void loadMpgBST(Car* list, BST<int, Car> &bst)
{
    for (int i = 0; i < numOfCars; i++)
    {
        bst.add(list[i].getMPGCity(), list[i]);
    }
}

// Authors(s): Kevin, Han
// Sorts the car in a BST by MPGFreeway
void loadMpgFreewayBST(Car* list, BST<int, Car> &bst)
{
    for (int i = 0; i < numOfCars; i++)
    {
        bst.add(list[i].getMPGFreeway(), list[i]);
    }
}

// Authors(s): Kevin, Han
// Sorts the car in a BST by price
void loadPriceBST(Car* list, BST<int, Car> &bst)
{
    for (int i = 0; i < numOfCars; i++)
    {
        bst.add(list[i].getPrice(), list[i]);
    }
}

// Authors(s): Kevin, Han
// Sorts the car in a BST by avg rating
void loadAvgRatingBST(Car* list, HashTable<Review> &table, BST<double, Car> &bst)
{
    for (int i = 0; i < numOfCars; i++)
    {
        Car car = list[i];
        double avg_rating = table.getAverageRatingBucket(car.getMake(), car.getModel());
        bst.add(avg_rating, car);
    }
}

// Authors(s): Han
// Gets an array of the car makes
void loadCarMake(vector<string>& makeList, Car* cList)
{
    string Make;
    bool isDupe = true;
    int makeSize = 0;

    //Reads car makes from clist
    for (int i = 0; i < numOfCars; i++)
    {
        Make = cList[i].getMake();
        makeSize = static_cast<int>(makeList.size());

        // If carMake is empty then pushback Make
        if (makeSize == 0)
        {
            makeList.push_back(Make);
        }

        // If carMake is not empty then check if Make is a duplicate
        // Duplicates are ignored, while new Makes are added
        else
        {
            for (int j = 0; j < makeSize; j++)
            {
                if (Make == makeList[j])
                {
                    isDupe = true;
                    break;
                }
                else isDupe = false;
            }
            if (!isDupe) makeList.push_back(Make);
        }
    }
}

// Authors(s): Han
// Saves the reviews from the HashTable to a file
void saveReviews(HashTable<Review> &Table, Car* list)
{
    // Make/Model/Owner/Stars/Description

    string Make, Model;
    ofstream save("reviews.txt");
    List<Review> rList;

    if (save.is_open())
    {
        // Checks every car for reviews
        for (int i = 0; i < numOfCars; i++)
        {
            Make = list[i].getMake();
            Model = list[i].getModel();

            // If the car has no reviews, move to next car
            // Cars with reviews are outputted to 'reviews.txt'
            if (Table.indexIsFilled(Make, Model))
            {
                rList = Table.getValue(Make, Model);
                rList.begin();
                while (!rList.off_end())
                {
                    save << rList.current().getMake() << "/" << rList.current().getModel() << "/" << rList.current().getOwner() << "/" << rList.current().getStars() << "/" << rList.current().getDescription() << endl;
                    rList.scroll();
                }
            }

        }

        save.close();
    }
    else
    {
        cout << "Error : Unable to open file 'reviews.txt' ";
        exit(-1);
    }

}

// Authors(s): Han
// Saves the car array into a file
void saveCars(Car* cList)
{
    // Make/Model/MPGe City/MPGe Highway/Type/Price/Views

    ofstream save("Kars Data.txt");

    if (save.is_open())
    {
        // Checks every car for reviews
        for (int i = 0; i < numOfCars; i++)
        {
            save << cList[i].getMake() << "/" << cList[i].getModel() << "/" << cList[i].getMPGCity() << "/" << cList[i].getMPGFreeway() << "/" << cList[i].getEngine() << "/" << cList[i].getPrice() << "/" << viewTable.getFront(cList[i].getMake(), cList[i].getModel()) << endl;
        }
        save.close();
    }
    else
    {
        cout << "Error : Unable to open file 'Kars Data.txt' ";
        exit(-1);
    }

}

// Author : Kevin
// Loads the car into a MaxHeap according to the no. of views
void loadViewHeap()
{
    for (int i = 0; i < numOfCars; i++)
    {
        Car car = carList[i];
        int views = viewTable.getFront(car.getMake(), car.getModel());
        viewHeap.addObject(car, views);
    }
    viewHeap.build();
}
