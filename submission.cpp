#include <bits/stdc++.h>
using namespace std;

class PointStruct
{
	public: int x_co_od;
	public: int y_co_od;
};

int compareX_co_od_comparision(const void* a, const void* b)
{
	PointStruct *p1 = (PointStruct *)a, *p2 = (PointStruct *)b;
	return (p1->x_co_od - p2->x_co_od);
}

int compareY_co_od_comparision(const void* a, const void* b)
{
	PointStruct *point1 = (PointStruct *)a, *point2 = (PointStruct *)b;
	return (point1->y_co_od - point2->y_co_od);
}

float findDistance(PointStruct point1, PointStruct point2)
{
	return sqrt( (point1.x_co_od - point2.x_co_od)*(point1.x_co_od - point2.x_co_od) +
				(point1.y_co_od - point2.y_co_od)*(point1.y_co_od - point2.y_co_od)
			);
}

float bruteForce(PointStruct P[], int n)
{
       float min = FLT_MAX;
       
    int l =n-1;
    while(l>=0){
        int m = n-1;
        while(m>=(l+1)){
            if (findDistance(P[l], P[m]) < min){ 
                min = findDistance(P[l], P[m]); }
            m--;
        }
        l--;
    }
    return min; 
}

float minimum(float x_co_ord, float y_co_ord)
{
    if(x_co_ord<y_co_ord){
        return x_co_ord;
    }
    else{
        return y_co_ord;
    }
}

float stripClosest(PointStruct strip[], int size, float d)
{
	float min = d; // Initialize the minimum distance as d

	qsort(strip, size, sizeof(PointStruct), compareY_co_od_comparision);

	int l = size-1;
	while(l>=0){
	    int m = size-1;
	    while(m>=(l+1) && (strip[m].y_co_od - strip[l].y_co_od) < min){
	        //cout << l << m << endl;
			if (findDistance(strip[l],strip[m]) < min){
			min = findDistance(strip[l], strip[m]);}
			m--;
	    }
	    l--;
	}
	return min;
}

float closestUtil(PointStruct P[], int n)
{
	if (n <= 3)
		return bruteForce(P, n);

	int mid = n/2;
	PointStruct midPoint = P[mid];
	float dl = closestUtil(P, mid);
	float dr = closestUtil(P + mid, n - mid);

	float d = minimum(dl, dr);

	PointStruct strip[n];
	int m = 0;
	int l = n;
	while(l>=0){
	    if (abs(P[l].x_co_od - midPoint.x_co_od) < d){
			strip[m] = P[l],
			m++;
	    }
	    l--;
	}
	return minimum(d, stripClosest(strip, m, d) );
}

float closestDistance(PointStruct P[], int n)
{
	qsort(P, n, sizeof(PointStruct), compareX_co_od_comparision);

	return closestUtil(P, n);
}

// main function
int main(int argc, char** argv)
{	
	//ifstream inputFile;
    ofstream outFile;
    string outputfile=argv[1];
    //string inputFilename=argv[1];
	outFile.open(outputfile);
    int n, x_co_ord, y_co_ord;
    n=10000;
    PointStruct p[n];
    for(int i =0;i<n;i++){
        p[i]={n-i, n-i};
    }
	
	outFile << closestDistance(p, n)<<endl;
	return 0;
}
