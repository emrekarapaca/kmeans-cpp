#include "Point.h"
#include <stdexcept>
#include <iomanip>

int Point::count = 0;

ostream& operator<<(ostream& os, const Point& obj) {
	os << setw(5) << "Point " << setw(7) << obj.getIndex() << ", coordinates: " << setw(10) << obj.getCoord().first <<
		setw(10) << obj.getCoord().second << setw(20) << "@Cluster ID: " << setw(3) << obj.getID() << endl;
	return os;
}
/**
	 * @brief Constructor for the Point class.
	 *
	 * Initializes a Point with the specified coordinates, ID, and index.
	 *
	 * @param COORD A pair representing the coordinates of the Point.
	 * @param ID An integer representing the ID of the Point.
	 * @param INDEX An integer representing the index of the Point.
	 */
Point::Point(pair<double, double>COORD, int ID, int INDEX)
	:coord(COORD),
	id(ID),
	index(INDEX)
{
	if (ID < 0)
		throw invalid_argument("ID value must be >=0");
	if (INDEX < 0)
		throw invalid_argument("INDEX value must be >=0");
	count++;
}

Point::~Point() {
	count--;
}

void Point::setCoord(pair<double, double>COORD) {
	coord.first = COORD.first;
	coord.second = COORD.second;
}

void Point::setID(int ID) {
	if (ID < 0)
		throw invalid_argument("ID value must be >=0");
	id = ID;
}

void Point::setIndex(int INDEX) {
	if (INDEX < 0)
		throw invalid_argument("INDEX value must be >=0");
	index = INDEX;
}

pair<double, double> Point::getCoord() const {
	return coord;
}

int Point::getID() const {
	return id;
}

int Point::getIndex() const {
	return index;
}

int Point::getCount() const {
	return count;
}