#pragma once
#include "Point.h"
#include <vector>

class KMeans
{
	friend void readFile(KMeans&);
private:
	vector<Point>points; //holds samples&cluster centers
	int iterNum;
	int clusterNum;
	string filePath;
public:
	KMeans(string&, int=0, int=0);
	~KMeans();

	void setIterNum(int);
	void setClusterNum(int);
	void setFilePath(string&);

	int getIterNum() const;
	int getClusterNum() const;
	string getFilePath() const;
	vector<Point> getPoints() const;

	pair<double, double> pointsAverage(vector<Point>&);
	void initClusters();
	double euclidean(pair<double, double>, pair<double, double>);
	void findNewID();
	void updateClusterCenters();
	void runKMeans();
	void plot2D();
};