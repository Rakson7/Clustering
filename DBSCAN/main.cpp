#include "dbscan.h"
vector<vector<double>> points;     //Stores all points in d-dimension
vector<long> classified_flag;       //*** -1:Unclassified(initial)  -2:NOISE   >=0:ClusterID***//
double  Eps;int MinPts;            //Get these parameters from through command line

string in_filename;
string  out_filename;
ofstream outfile;
clock_t start_main=clock();

void PerformDBscan(MTREE& mtree)
{   const char* out_file = out_filename.c_str();
    outfile.open(out_file);

    long ClusterId = 0;
    for (long point_loc = 0; point_loc < points.size(); point_loc++)
    {   //cout<<"processing Point No.: "<<point_loc<<"\n";
        if (classified_flag[point_loc] == -1)
            if (ExpandCluster(mtree,points[point_loc], ClusterId ,point_loc))
            {   //cout<<"Found Cluster No: "<<ClusterId<<"\n";
                ClusterId++;
            }
    }

    outfile<<"#outlier\n";
    for(int i=0;i<classified_flag.size();i++)
        if(classified_flag[i] <0)
            outfile<<i<<"\n";
    outfile.close();                      //#######File write complete

    //cout<<"\nTotal No of clusters is : "<<ClusterId<<"\n";
}

int main(int argc, char* argv[])
{
    in_filename=argv[3];
    out_filename="dbscan.txt";
    Eps=stod(argv[2]);
    MinPts=stoi(argv[1]);

    fastRead(in_filename);     //This fills d-dimension points to points vector

    clock_t mtree_time=clock();
    MTREE mtree(points);       //This creates Mtree index structure
    double time_mtree = (clock()-mtree_time)/(double) CLOCKS_PER_SEC;
    //cout<<"###################\nMTree Build Time  is :"<<time_mtree<<endl;

    PerformDBscan(mtree);

    double time_taken = (clock()-start_main)/(double) CLOCKS_PER_SEC;
    //cout<<"###################\nTotal Time taken is :"<<time_taken<<endl;
    return 0;
}
