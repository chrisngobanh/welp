#include "FileIO.h"

Car* load()
{
    Car* list = new Car[getArrayLength()];
    string line;
    int index = 0;
    
    int substr_start, offset;
    
    string make, model, type, engine;
    int mpgcity, mpgfree, msrp, views;
    
    char divider = '/';
    
    ifstream in("Kars Data.txt");
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

void loadMpgBST(Car* list, BST<int, Car> &bst)
{
    int size = getArrayLength();
    for (int i = 0; i < size; i++)
    {
        bst.add(list[i].getMPGCity(), list[i]);
    }
}

void loadMpgFreewayBST(Car* list, BST<int, Car> &bst)
{
    int size = getArrayLength();
    for (int i = 0; i < size; i++)
    {
        bst.add(list[i].getMPGFreeway(), list[i]);
    }
}

void loadPriceBST(Car* list, BST<int, Car> &bst)
{
    int size = getArrayLength();
    for (int i = 0; i < size; i++)
    {
        bst.add(list[i].getPrice(), list[i]);
    }
}

void loadAvgRatingBST(Car* list, HashTable<Review> &table, BST<double, Car> &bst)
{
    int size = getArrayLength();
    for (int i = 0; i < size; i++)
    {
        Car car = list[i];
        double avg_rating = table.getAverageRatingBucket(car.getMake(), car.getModel());
        bst.add(avg_rating, car);
    }
}

void loadCarMake(vector<string>& makeList, Car* cList)
{
    string Make;
    bool isDupe = true;
    int makeSize = 0;
    int size = getArrayLength();
    
    //Reads car makes from clist
    for (int i = 0; i < size; i++)
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

void saveReviews(HashTable<Review> &Table, Car* list)
{
    // Make/Model/Owner/Stars/Description
    
    int size = getArrayLength();
    string Make, Model;
    ofstream save("reviews.txt");
    List<Review> rList;
    
    if (save.is_open())
    {
        // Checks every car for reviews
        for (int i = 0; i < size; i++)
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

void saveCars(Car* cList)
{
    // Make/Model/MPGe City/MPGe Highway/Type/Price/Views
    
    int size = getArrayLength();
    ofstream save("Kars Data.txt");
    
    if (save.is_open())
    {
        // Checks every car for reviews
        for (int i = 0; i < size; i++)
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
