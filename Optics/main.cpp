#include <bits/stdc++.h>
#define UNDEFINED INFINITY
using namespace std;

struct pointset{
    vector<double> points;
    double reachability_distance;
    double core_distance;
    bool processed;
    int index;
};

//global dataset and dimension.
vector<pointset> database;
int dimension;
string write_to_file;
int process_count = 0;

//function prototypes
vector<pointset> file_processing(string filename);
void optics(int minpts, double epsilon);
void expand_cluster_order(pointset &object, int minpts, double epsilon);
vector<int> calculate_neighbors(pointset &object, double epsilon, int minpts);
void update_queue(multimap<double, int> &priority_map, vector<int> neighbour_list, pointset &object);
double calculate_distance(vector<double> obj_1, vector<double> obj_2);

int main(int argc, char *argv[]) {
    string filename = argv[3];
    int minpts = stoi(argv[1]);
    double epsilon = stod(argv[2]);
//cout<<filename;

    //database created.
    database = file_processing(filename);

    //Optics is called.
    optics(minpts, epsilon);

    cout<<"Total Processed items are : "<< process_count<<endl;
    return 0;
}

//File_processing and pre-processing of data. It returns a vector of structures.
vector<pointset> file_processing(string filename){
    ifstream in_file;
    vector<pointset> temp;
    in_file.open(filename);
    string data;
    int index = 0;

    if(!in_file){
        cout<<"File not found."<<endl;
    }else{
        while(getline(in_file, data)){
            vector<double> items;
            istringstream stream (data);
            double item;
            int count = 0;
            while(stream>>item){
                count += 1;
                items.push_back(item);
            }
            pointset p;
            dimension = count;
            p.points = items;
            p.core_distance = UNDEFINED;
            p.processed = false;
            p.index = index;
            p.reachability_distance = UNDEFINED;
            temp.push_back(p);
            index++;
        }
    }
    return temp;
}

void optics(int minpts, double epsilon){
    auto itr = database.begin();
    ofstream out_file("optics.txt");
    while(itr != database.end()){
        if(!itr->processed){
            expand_cluster_order(*itr, minpts, epsilon);
        }
        itr++;
    }
    out_file<<write_to_file;
    out_file.close();
}

void expand_cluster_order(pointset &object, int minpts, double epsilon){
    vector<int> N = calculate_neighbors(object, epsilon, minpts);
    object.processed = true;
    process_count++;
    write_to_file += to_string(object.index) + " " + to_string(object.reachability_distance) + " " + to_string(object.core_distance) + "\n";

    if(object.core_distance != UNDEFINED){
        multimap<double, int> priority_map;
        update_queue(priority_map, N, object);

        while(!priority_map.empty()){
            auto top_itr = priority_map.begin();
            pair<double, int> top = * top_itr;
            priority_map.erase(top_itr);
            pointset *curr_object = &database[top.second];
            vector<int> N_co = calculate_neighbors(*curr_object, epsilon, minpts);
            curr_object->processed = true;
            process_count++;
            write_to_file += to_string(curr_object->index) + " " + to_string(curr_object->reachability_distance) + " " + to_string(curr_object->core_distance) + "\n";
            if(curr_object->core_distance != UNDEFINED){
                update_queue(priority_map, N_co, *curr_object);
            }
        }
    }
}

// calculates neighbors of a point and check if it is core point. If it is then its core distance is set.
vector<int> calculate_neighbors(pointset &object, double epsilon, int minpts){
    vector<int> neighbor_indexes;
    vector<double> distances;
    auto itr = database.begin();
    while(itr!=database.end()){
        if(itr->index != object.index){
            vector<double> temp;
            for(int i = 0; i<dimension; i++){
                temp.push_back(pow((itr->points[i] - object.points[i]),2));
            }
            double sum = 0;
            for(auto j : temp)sum += j;
            double s = sqrt(sum);
            if(s <= epsilon){
                neighbor_indexes.push_back(itr->index);
                distances.push_back(s);
            }
        }
        itr++;
    }
    if(neighbor_indexes.size()>=(minpts-1)){
        sort(distances.begin(), distances.end());
        object.core_distance = distances[minpts-2];
    }
    return neighbor_indexes;
}

void update_queue(multimap<double, int> &priority_map, vector<int> neighbour_list, pointset &object){
    //cout<<"Updating for : "<< object.index << endl;
    int len = neighbour_list.size();
    for(int i = 0; i<len; i++){
        pointset *p = &database[neighbour_list[i]];
        if(!p->processed){
            double new_r_distance = max(object.core_distance, calculate_distance(object.points, p->points));
            double old_r_distance = p->reachability_distance;

            if(old_r_distance == UNDEFINED){
                p->reachability_distance = new_r_distance;
                priority_map.insert(make_pair(p->reachability_distance, p->index));

            }else if(new_r_distance < old_r_distance){
                p->reachability_distance = new_r_distance;
                auto itr = priority_map.equal_range(old_r_distance);
                for(auto loop = itr.first; loop !=itr.second; loop++){
                    if(loop->second == p->index){
                        priority_map.erase(loop);
                        priority_map.insert(make_pair(p->reachability_distance, p->index));
                        break;
                    }
                }
            }

        }
    }
}

double calculate_distance(vector<double> obj_1, vector<double> obj_2){
    vector<double> temp;
    for(int i = 0; i<dimension; i++){
        temp.push_back(pow((obj_1[i] - obj_2[i]), 2));
    }
    double sum = 0.0;
    for(auto j : temp)sum += j;
    return sqrt(sum);
}
