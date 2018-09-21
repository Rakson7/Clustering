#ifndef FAST_DBSCAN_DBSCAN_H
#define FAST_DBSCAN_DBSCAN_H

#include<bits/stdc++.h>
#include "MetricTree.hpp"
using  namespace std;

/******VARIABLES********/
extern double Eps;
extern int MinPts;
extern ofstream outfile;

extern vector<vector<double>> points;      //Stores all points in d-dimension
extern vector<long> classified_flag;       //*** -1:Unclassified(initial)  -2:NOISE   >=0:ClusterID***//

/******FaSST Functions********/
double euclideanDistance(const vector<double>& p1, const vector<double>& p2);
typedef MetricTree<vector<double> , euclideanDistance> MTREE;

vector<vector<double>> mtreesearch(vector<double>& point , double Eps);

/******FUNCTIONS********/
void fastRead(string&);
bool ExpandCluster(MTREE& , vector<double>&  , long , long);

/**********Temp Testing Items***************/
vector<vector<double>> brutesearch(vector<double>& point , double Eps);   //Used for testing performance of BRUTE FORCE

#endif //FAST_DBSCAN_DBSCAN_H