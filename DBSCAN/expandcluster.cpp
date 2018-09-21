#include "dbscan.h"
/********* -1:Unclassified(initial)  -2:NOISE   >=0:ClusterID**************/
vector<vector<double>> seeds;
vector<vector<double>> resultPList;
vector<double> currentP;

long count_classified=0;
long class_flag;

bool ExpandCluster(MTREE& mtree,vector<double>& Point , long ClusterId,long point_loc)
{
    seeds.clear();
    mtree.search(Point,Eps,seeds);                                //This gives Eps-Neighbours  of Point in seedList

    if(seeds.size()<MinPts)                                         //If TRUE:Classify it as NOISE for now
    {   classified_flag[point_loc] = -2;
        return false;
    }
    else
    {
        outfile<<"#"<<ClusterId<<"\n";                              //**********************Writing file************
        int i=0;
        for(i=0;i<seeds.size();i++)                               //Assigning cluster of all elements in seedList to ClusterId
        {   if(classified_flag[seeds[i][0]] < 0)
            {
                classified_flag[seeds[i][0]] = ClusterId;
                outfile << seeds[i][0]<< "\n";                             //**********************Writing file************
                //cout << "Classified point no " << count_classified++ <<" to ClusterID: "<<ClusterId<<" ; SEED Size : "<<seeds.size()<< "\n";
            }
        }

        auto it = find (seeds.begin(), seeds.end(),Point);
        seeds.erase(it);                                            //Delete point_no from seedList as its processing over

        while(seeds.size()>0)
        {   currentP=seeds[0];                                      //Select elements from seedList one by one and process it
            resultPList.clear();
            mtree.search(currentP,Eps,resultPList);                 //This fills Eps-Neighbour "point_no" of currentP in resultPList

            if(resultPList.size()>=MinPts)                           //If selected element from seedList is a CORE point
                for(i=0;i<resultPList.size();i++)
                {
                    class_flag=classified_flag[resultPList[i][0]];
                    if (class_flag < 0 )                             //This means ith point of resultPList not classified yet
                    {
                        if (class_flag == -1)                        //This means ith point of resultPList is  UNCLASSIFIED
                            seeds.push_back(resultPList[i]);
                        classified_flag[resultPList[i][0]]  = ClusterId;   //This means ith point of resultPList is CLASSIFIED here
                        outfile << resultPList[i][0]  << "\n";        //**********************Writing file************
                        //cout << "Classified point no " << count_classified++ << " to ClusterID: " << ClusterId <<" ; Result Size : "<<resultPList.size()<< "\n";
                    }
                }
            seeds.erase(seeds.begin());
        }
        return true;
    }
}




double euclideanDistance(const vector<double>& p1, const vector<double>& p2){
    double sum = 0.0;
    for (int i = 1; i < p1.size(); i++)
        sum += (p1[i] - p2[i])*(p1[i] - p2[i]);
    return sqrt(sum);

}