#pragma once
#include <utility>
#include <iostream>
using namespace std;

class Point
{
	friend ostream& operator<<(ostream&, const Point&);
private:
	pair<double, double>coord;
	int id;
	int index;
	static int count;

public:
	Point(pair<double, double>, int = 0, int = 0);
	~Point();
	void setCoord(pair<double, double>);
	void setID(int);
	void setIndex(int);
	pair<double, double> getCoord() const;
	int getID() const;
	int getIndex() const;
	int getCount() const;
};

