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
		void food::print(){ // start with very large variables for x,y,z. Max km from one side of the earth to the other side is 12,756km so this covers all distance.
			double x = 100000, y = 100000, z = 100000;
			int restaurant1= 0, restaurant2 =0, restaurant3 =0;
			for (int i = 0; i < distance.size(); i++){   //  number < x  
				if(distance[i] < x){
					swap(y,z); // z = y
					swap(restaurant2,restaurant3);
					swap(x,y); // y = x
					swap(restaurant1,restaurant2);
					x = distance[i]; // x = new cloest
					restaurant1 = i;
				}
				else if((distance[i] >= x) && distance[i] < y){ // x < number < y 
					swap(y,z);
					swap(restaurant2,restaurant3);
					y = distance[i];
					restaurant2 = i;
				}
				else if(distance[i] >= y && distance[i] < z ){ // y < number < z
					z = distance[i];
					restaurant3 = i;
				}
			}
			cout << "restaurant 1: " << rName[restaurant1] << ", " << distance[restaurant1] << " km" << ", " << loc[restaurant1] << endl;  // since position is the same for all 3 vectors, as soon as we find the .
			cout << "restaurant 2: " << rName[restaurant2] << ", " << distance[restaurant2] << " km" << ", " << loc[restaurant2] << endl;  // position in which the distance is the shortest, we can find all info.
			cout << "restaurant 3: " << rName[restaurant3] << ", " << distance[restaurant3] << " km" << ", " << loc[restaurant3] << endl;
		} 