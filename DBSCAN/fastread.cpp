#include "dbscan.h"
vector<double> point;
vector<double> fast_pow;

inline void fill_fast_pow(int max_digit_count)
{  for(int i=0;i<max_digit_count;i++)
        fast_pow.push_back(pow(10.0,i ));
}

inline double fast_atof( const char * st )
{   double val = 0.0;
    double frac_part = 0.0;
    int frac_digit_count = 0;
    bool neg = false;
    if (*st == '-')
    {   neg = true;
        ++st;
    }
    while (*st >= '0' && *st <= '9')
        val = (val*10.0) + (*st++ - '0');
    if (*st == '.')
    {   ++st;
        while (*st >= '0' && *st <= '9')
        {   frac_part = (frac_part*10.0) + (*st++ - '0');
            ++frac_digit_count;
        }
        val += frac_part / fast_pow[frac_digit_count];
    }
    if (neg)
        val = -val;
    return val;
}

void fastRead(string& filename)
{
    clock_t start = clock();
    const char* file = filename.c_str();
    fill_fast_pow(25);                        //initialises power of 10 vectors
    long point_count=0;
    FILE *fp;
    char  buffer[32],str[1048576];
    int i,it = 0;

    fp = fopen(file, "r");
    while(fgets(str,1048576,fp) != nullptr){
        i=0;
        point.clear();
        classified_flag.push_back(-1);        //Assigning each point ClusterId to UNCLASSIFIED or -1
        point.push_back(point_count++);       //Assigning each point its location in file

        while(true)
        {
            while(isdigit(str[i]) || str[i]=='.' || str[i]=='-')
                buffer[it++]=str[i++];
            point.push_back(fast_atof(buffer)); //Filling Single point vector
            memset(buffer,0,32);
            it=0;
            if(str[i]=='\n')
                break;
            i++;
        }
        points.push_back(point);               //Pushing single point to points vector
    }
    fclose(fp);

    double time_taken = (clock()-start)/(double) CLOCKS_PER_SEC;
    //cout<<"\nTime taken in READ is :"<<time_taken<<endl;
    //cout<<"Point_Count: "<<point_count<<endl;
}

