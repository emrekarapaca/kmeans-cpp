#include "KMeans.h"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cmath>
#include "matplotlibcpp.h"

namespace plt = matplotlibcpp;
/*
	reads file from specific path
*/
void readFile(KMeans& obj) {
	ifstream file(obj.getFilePath());
	string line;
	int i = 0;
	if (!file.is_open())
		throw runtime_error("File couldnt be read.");
	while (getline(file, line)) {
		istringstream iss(line);
		double x, y;
		if (iss >> x >> y) {
			Point newPoint(make_pair(x, y), 0, i);
			obj.points.push_back(newPoint);
			cout << newPoint;
		}
		else
			throw runtime_error("Error about .txt file (x,y).");
		i++;
	}
	cout << "Reading file operation successful." << endl;
	file.close();
}
/**
 * @brief Constructor
 * @param PATH: The file path to be set, T: iteration num, CL : cluster number
 */
KMeans::KMeans(string& PATH, int IT, int CL)
	:filePath(PATH),
	iterNum(IT),
	clusterNum(CL) {
	if (IT < 0)
		throw invalid_argument("Iteration value must be > 0");
	if (CL < 0)
		throw invalid_argument("Cluster number must be > 0");
	readFile(*this);
}

KMeans::~KMeans(){}

void KMeans::setIterNum(int IT) {
	if (IT < 0)
		throw invalid_argument("Iteration value must be > 0");
	iterNum = IT;
}

void KMeans::setClusterNum(int CL) {
	if (CL < 0)
		throw invalid_argument("Cluster number must be > 0");
	clusterNum = CL;
}

void KMeans::setFilePath(string& PATH) {
	filePath.assign(PATH);
}

int KMeans::getIterNum() const {
	return iterNum;
}

int KMeans::getClusterNum() const {
	return clusterNum;
}

string KMeans::getFilePath() const {
	return filePath;
}

vector<Point> KMeans::getPoints() const {
	return points;
}
/**
 * @brief Calculates the average coordinates of the given set of points.
 *
 * This function calculates the average coordinates (mean) of a set of points.
 * It iterates through each point in the provided vector and computes the average of x and y coordinates separately.
 *
 * @param obj The vector of points for which the average coordinates will be calculated.
 * @return The average coordinates as a pair of doubles (x, y).
 */
pair<double, double> KMeans::pointsAverage(vector<Point>& obj) {
	double sumX = 0.0;
	double sumY = 0.0;
	for (auto const& sample : obj) {
		sumX += sample.getCoord().first;
		sumY += sample.getCoord().second;
	}
	size_t size = obj.size();
	return make_pair(sumX / size, sumY / size);
}
/**
 * This function initializes the clusters for the K-Means algorithm by setting initial cluster centers.
 * It currently sets the initial cluster centers using average of samples method.
 */
void KMeans::initClusters() {
	double avg_x = pointsAverage(points).first;
	double avg_y = pointsAverage(points).second;
	for (auto i = 0; i < getClusterNum(); i++) {
		Point newCluster(make_pair((avg_x - rand() % 10), (avg_y - rand() % 10)), i, 0);
		points.push_back(newCluster);
	}
}
/**
 * @brief Calculates the Euclidean distance between two points.
 *
 * This function calculates the Euclidean distance between two points in a 2D space.
 *
 * @param s The first point as a pair of doubles (x, y).
 * @param p The second point as a pair of doubles (x, y).
 * @return The Euclidean distance between the two points.
 */
double KMeans::euclidean(pair<double, double>s, pair<double, double>c){
	return sqrt(pow((s.first - c.first), 2) + pow((s.second - c.second), 2));
}
/**
 * @brief Finds the nearest cluster for each sample and assigns its ID accordingly.
 *
 * Calculates the Euclidean distance between each sample and all clusters,
 * and assigns the ID of the nearest cluster to each sample.
 */
void KMeans::findNewID(){
	for (size_t i = 0; i <= points.size() - getClusterNum(); ++i) {
		vector<double>distances;
		for (size_t j = (points.size()-getClusterNum()); j < points.size(); j++) {
			distances.push_back(euclidean(points[i].getCoord(), points[j].getCoord()));
		}
		auto minDistIter = min_element(distances.begin(), distances.end());
		int minJ = distance(distances.begin(), minDistIter);
		points[i].setID(minJ);
	}
}
/**
 * @brief Updates the cluster centers based on the samples assigned to each cluster.
 *
 * For each cluster, collects the samples assigned to that cluster and calculates a new center.
 * The new center is set for the cluster if the collected points have valid coordinates.
 */
void KMeans::updateClusterCenters(){
	
	for (int i = 0; i < getClusterNum(); i++) {
		vector<Point> thatPoints;
		for (int j = 0; j < (getPoints().size() - getClusterNum()); j++) {
			if (getPoints()[j].getID() == i) {
				if (!isnan(getPoints()[j].getCoord().first) &&
					!isnan(getPoints()[j].getCoord().second)) {
					thatPoints.push_back(getPoints()[j]);
				}
			}
		}
		if (!thatPoints.empty()) {
			pair<double, double> newCoord = pointsAverage(thatPoints);
			points[getPoints().size() - getClusterNum() +i ].setCoord(newCoord);
		}
	}
}
/**
 * @brief Runs the K-Means algorithm to cluster the samples.
 *
 * This function executes the K-Means algorithm by initializing clusters,
 * assigning samples to their nearest clusters, and updating cluster centers iteratively
 * for a specified number of iterations (getIterNum). It prints the clusters
 * and samples at the beginning and end of the algorithm.
 */
void KMeans::runKMeans(){
	initClusters();
	for (int i = 0; i < getIterNum(); i++) {
		findNewID();
		updateClusterCenters();
	}
	for (const auto& p : points) {
		cout << p;
	}
}

void KMeans::plot2D() {
	auto s = getPoints().size();
	vector<Point>clusters;
	copy(points.begin() + s - getClusterNum(), points.begin() + s, back_inserter(clusters));
	vector<double> x_samples, y_samples;
	vector<double> x_centers, y_centers;
	for (const auto& sample : getPoints()) {
		x_samples.push_back(sample.getCoord().first);
		y_samples.push_back(sample.getCoord().second);
	}

	for (const auto& cluster : clusters) {
		x_centers.push_back(cluster.getCoord().first);
		y_centers.push_back(cluster.getCoord().second);
	}


	vector<vector<double>> x_samples_by_cluster(clusters.size());
	vector<vector<double>> y_samples_by_cluster(clusters.size());

	for (size_t i = 0; i < getPoints().size(); ++i) {
		int cluster_id = getPoints()[i].getID();
		x_samples_by_cluster[cluster_id].push_back(x_samples[i]);
		y_samples_by_cluster[cluster_id].push_back(y_samples[i]);

		plt::annotate(std::to_string(i), x_samples[i], y_samples[i]);
	}

	for (size_t i = 0; i < clusters.size(); ++i) {
		string point_color = "C" + to_string(i);
		plt::scatter(x_samples_by_cluster[i], y_samples_by_cluster[i], 20.0, { {"color", point_color} });
	}

	plt::scatter(x_centers, y_centers, 30.0, { {"color", "red"}, {"marker", "x"} });
	plt::title("KMeans Graph");
	plt::show();
}