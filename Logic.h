#ifndef LOGIC_H
#define LOGIC_H
#include <iostream>
#include <stdlib.h>
#include <utility> 
#include <fstream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

const double R = 6372.8; //radius of earth in km
const double TO_RAD = 3.14159256/180; //conversion of degrees to rads

class food {
	public:
		food(string a, string b, string c); //  takes in target cuisine->a, lat->b, long ->c
		double heversine(double lat1, double lon1, double lat2, double lon2);
		void read();
		void print();
	private:
		vector<string> rName; // resturant name
		vector<double> distance; // stores the distance of all stores from inputed lat and long. 
		vector<string> loc; 
		string target; // target = cuisine 
		string cuisine, longitude, latitude, restaurantName, address;
		double currentLat, currentLong;
};

#endif
