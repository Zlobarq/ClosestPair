#include <iostream>
#include <algorithm> 
#include <random>
#include <vector>
#include <utility>  
#include <cmath>
#include <time.h>
//struct for point
struct point
{
	int number;
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

float bruteForce(std::vector<point> in)
{
	int n=in.size();
    float min = INFINITY;
    for (int i = 0; i < n; ++i)
        for (int j = i+1; j < n; ++j)
            if (eul_distance(in[i], in[j]) < min)
                min = eul_distance(in[i], in[j]);
    return min;
}







//MAIN FUNCTION
int main()
{
//initialize vector of points
std::vector<point> points_xsorted;
//float randomizer
std::uniform_real_distribution<float> distribution(0.0,100.0);
std::default_random_engine generator;

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
clock_t tStart = clock();
float distance=bruteForce(points_xsorted);
clock_t tEnd = clock();
printf("The distance is: %f\n", distance);
printf("Time taken: %.2f\n", (double)(tEnd - tStart));
printf("Real Time taken: %.2f\n", (double)(tEnd - tStart)/CLOCKS_PER_SEC);
	return 0;
}