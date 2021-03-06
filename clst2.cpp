#include <iostream>
#include <algorithm> 
#include <random>
#include <vector>
#include <utility>  
#include <cmath>
#include <time.h>

//struct for point
struct point
{	int number;
	float x;
	float y;
  static bool is_smaller_X(const point& l, const point& r) {
    return l.x < r.x;
  }
  

};





//euclidean distance
float eul_distance(point p1, point p2)
{
    return sqrt( (p1.x - p2.x)*(p1.x - p2.x) +
                 (p1.y - p2.y)*(p1.y - p2.y)
               );
}
//end of euclidean distance


//swap distance with temporary when temporary is smaller
void update_smaller_dist(point const& a, point const& b, float &distance)
{
	float temp=eul_distance(a,b);
	if(temp<distance)
	{
		distance=temp;
	}
}
//end

//initialization of xorted vector and definition of sorting function

void sort_by_x(std::vector<point> &in)
{
	std::sort (in.begin(), in.end(), point::is_smaller_X);
}
//end of sorting function



void DivideAndConquer(std::vector<point> in,std::pair<int,int> subset,float &distance)
{
	int size=subset.second-subset.first;
	if (size>2)
	{
	//creating median...
	int median=subset.first+(size/2);
	//left and right subest
	std::pair<int,int> left_subset=std::make_pair(subset.first, median);
	DivideAndConquer(in,left_subset,distance);
	std::pair<int,int> right_subset=std::make_pair(median+1,subset.second);
	DivideAndConquer(in,right_subset,distance);
	//the median subset...goes slower than brute that way,couldn't find solution ):	
	std::vector<point> mid_subset;
	int chk_ind_lower=median-1;
	int check_distance_x=in[median].x-in[chk_ind_lower].x;
	//check the smaller then median
	while (distance!= INFINITY && check_distance_x<distance && chk_ind_lower>=0)
		{
		mid_subset.push_back(in[chk_ind_lower]);
		chk_ind_lower-=1;
		check_distance_x=in[median].x-in[chk_ind_lower].x;
		}
	int chk_ind_higher=median+1;
	check_distance_x=in[chk_ind_higher].x-in[median].x;
	//check the bigger than median	
	while (distance!= INFINITY && check_distance_x<distance && chk_ind_higher<=size)
		{
		mid_subset.push_back(in[chk_ind_lower]);
		chk_ind_higher+=1;
		check_distance_x=in[chk_ind_higher].x-in[median].x;
		}	
	for (point a: mid_subset)
	{
		for (int i=0;i<=mid_subset.size();i++)
		{
			//couldnt figure out a wait to check
			if(a.x!=mid_subset[i].x && a.y!=mid_subset[i].y && abs(a.x-mid_subset[i].x)<distance)
			{
			update_smaller_dist(a,mid_subset[i],distance);
			}
		}
	}
	}
else
	{
		//update when we have simple case with 3 points
		if (size==2) 
		{
			for (int i=0;i<=size;i++)
			{
			//mod 3 to prevent segmentation
			update_smaller_dist(in[subset.first+i],in[subset.first+(i+1)%3],distance);
			}
		}
		else
		//update when we have simple case with 2 points
		{
		update_smaller_dist(in[subset.first],in[subset.second],distance);
		}
	}
}







//MAIN FUNCTION
int main()
{
//initialize vector of points
std::vector<point> points_xsorted;
//float randomizer
std::uniform_real_distribution<float> distribution(0.0,100.0);
std::default_random_engine generator;

//random generation
for (int i=0;i<100;i++)
	{
	point new_point;
	new_point.number=i;
	new_point.x=distribution(generator); 
	new_point.y=distribution(generator);
	//print
	//std::cout<<new_point.number<<" ";
	//std::cout<<new_point.x<<" ";
	//std::cout<<new_point.y<<"\n";
	points_xsorted.push_back(new_point);
	}

//sort vector,here the vector becomes "x sorted"
sort_by_x(points_xsorted);

std::pair<int,int> subset =std::make_pair(0, points_xsorted.size());
float distance = INFINITY;
clock_t tStart = clock();
DivideAndConquer(points_xsorted,subset,distance);
clock_t tEnd = clock();
printf("The distance is: %f\n", distance);
printf("Time taken: %.2f\n", (double)(tEnd - tStart));
printf("Real Time taken: %.2f\n", (double)(tEnd - tStart)/CLOCKS_PER_SEC);
	return 0;
}