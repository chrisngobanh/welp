#include <iostream>
#include "Car.h"
#include <fstream>
#include <string>
#include <cstdlib>

using namespace std;

Car* load();
int getArrayLength();

int main()
{
	Car* list = load();
	
	for (int i = 0; i < getArrayLength() ; i ++)
	{
	    cout << list[i].getMake() << " " << list[i].getModel() << " " <<  list[i].getType() << " " << list[i].getEngine() << " " << list[i].getMPGCity() << " " << list[i].getMPGFreeway() << " " << list[i].getPrice() << "\n";
	}
	
	cout << getArrayLength();

	system("PAUSE");
	return 0;
}

//Make/Model/MPG City/MPG Freeway/Car Type/Engine Type/Price
//Honda,Civic (Sedan),25,40,Sedan,Gasoline,25000

int getArrayLength()
{
	string line;
	int length = 0;
	ifstream in("info.txt");
	if (in.is_open())
	{
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
		cout << "Error: Unable to open file.\n\n";
		return -1;
	}
}

Car* load()
{
	Car* list = new Car[getArrayLength()];
	string line;
	int index = 0;

	int substr_start, offset;

	string make, model, type, engine;
	int mpgcity, mpgfree, msrp;

	char divider = ',';

	ifstream in("info.txt");
	if (in.is_open())
	{
		in.clear();
		in.seekg(0, ios::beg);
		while (getline(in, line))
		{
			substr_start = 0;
			offset = 0;
			while (line[substr_start + offset] != divider)
			{
				offset++;
			}
			make = line.substr(substr_start, offset);
			substr_start = substr_start + offset + 1;
			offset = 0;


			while (line[substr_start + offset] != divider)
			{
				offset++;
			}
			model = line.substr(substr_start, offset);
			substr_start = substr_start + offset + 1;
			offset = 0;


			while (line[substr_start + offset] != divider)
			{
				offset++;
			}
			mpgcity = atoi(line.substr(substr_start, offset).c_str());
			substr_start = substr_start + offset + 1;
			offset = 0;

			while (line[substr_start + offset] != divider)
			{
				offset++;
			}
			mpgfree = atoi(line.substr(substr_start, offset).c_str());
			substr_start = substr_start + offset + 1;
			offset = 0;

			while (line[substr_start + offset] != divider)
			{
				offset++;
			}
			type = line.substr(substr_start, offset);
			substr_start = substr_start + offset + 1;
			offset = 0;

			while (line[substr_start + offset] != divider)
			{
				offset++;
			}
			engine = line.substr(substr_start, offset);
			substr_start = substr_start + offset + 1;
			offset = 0;

			while (line[substr_start + offset] != NULL)
			{
				offset++;
			}
			msrp = atoi(line.substr(substr_start, offset).c_str());
			substr_start = substr_start + offset + 1;
			offset = 0;

			list[index] = Car(make, model, type, engine, mpgcity, mpgfree, msrp);
			index++;
		}

		in.close();
		return list;
	}
	else
	{
		cout << "Error: Unable to open the file.\n\n";
		exit(-1);
	}
}


//Book book;
//    string line;
//    ifstream in ("library.txt");
//    if (in.is_open())
//    {
//        while (getline(in, line))
//        {
//            string title = line;
//            getline(in, line);
//            string isbn = line;
//            getline(in, line);
//            string author = line;
//            getline(in, line);
//            string status = line;
//            library.push_back(new Book(title, isbn, author, status));
//        }
//        in.close();
//    }
//    else cout << "Error: Unable to open file.\n\n";
