#include <iostream>
#include <stdlib.h>
#include <utility> 
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include "Logic.h"

		food::food(string a, string b, string c){ // takes in target cuisine->a, lat->b, long ->c
			target = a;
			currentLat = atof(b.c_str()); // converts argv[2] to a double for current location
			currentLong = atof(c.c_str()); // converts argv[3] to a double for current location
			read();
			print();
		}
		double food::heversine(double lat1, double lon1, double lat2, double lon2) {
			lat1 = TO_RAD * lat1;
			lat2 = TO_RAD * lat2;
			lon1 = TO_RAD * lon1;
			lon2 = TO_RAD * lon2;
			double dLat = (lat2 - lat1) / 2;
			double dLon = (lon2 - lon1) / 2;
			double a = sin(dLat);
			double b = sin(dLon);
			return 2 * R * asin(sqrt(a*a + cos(lat1)*cos(lat2)*b*b));
		}
		void food::read(){ //reads the csvfile and if cuisine == target, it will compute the distance and push distance, resturant name, and location into seperate vectors
			ifstream file("resturants.csv");
			if (!file.is_open()){
				cout << "error opening file" << endl;
			}
			while (!file.eof()){
				getline(file, cuisine, ',');
				getline(file, longitude, ',');
				getline(file, latitude, ',');
				getline(file, restaurantName, ',');
				getline(file, address, '\n');
				
				if (cuisine == target){
					double tempLong = atof(longitude.c_str()); // converts longitude string to a double
					double tempLat = atof(latitude.c_str()); // converts latitude string to a double
					distance.push_back(heversine(currentLat, currentLong, tempLat, tempLong));
					rName.push_back(restaurantName);
					loc.push_back(address);
				}
			}
			file.close();
		}
		void food::print(){ // start with very large variables for x,y,z. Max km from one side of the earth to the other side is 12,756km so this covers it.
			double x = 100000, y = 100000, z = 100000;
			int store1= 0, store2 =0, store3 =0;
			for (int i = 0; i < distance.size(); i++){   //  number < x  
				if(distance[i] < x){
					swap(y,z); // z = y
					swap(store2,store3);
					swap(x,y); // y = x
					swap(store1,store2);
					x = distance[i]; // x = new cloest
					store1 = i;
				}
				else if((distance[i] >= x) && distance[i] < y){ // x < number < y 
					swap(y,z);
					swap(store2,store3);
					y = distance[i];
					store2 = i;
				}
				else if(distance[i] >= y && distance[i] < z ){ // y < number < z
					z = distance[i];
					store3 = i;
				}
			}
			cout << "store 1: " << rName[store1] << ", " << distance[store1] << " km" << ", " << loc[store1] << endl;  // since position is the same for all 3 vectors, as soon as we find the .
			cout << "store 2: " << rName[store2] << ", " << distance[store2] << " km" << ", " << loc[store2] << endl;  // position in which the distance is the shortest, we can find all info.
			cout << "store 3: " << rName[store3] << ", " << distance[store3] << " km" << ", " << loc[store3] << endl;
		} 