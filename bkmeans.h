#include <iostream>
#include <stdlib.h>

using namespace std;

class Matrice {
  int sizeH, sizeW; 
  float *vect; 
  public:
    Matrice(int nbl, int nbc, float *Vtemp); //constructor
    Matrice(char * base);     //convert a text file to a Inmatrix
    float outMatrice(char * base);
    float getValue(int i, int j);  //get value from the matrix
    float setValue(int i, int j, float value); //set value in the matrix
    int getH();
    int getW();
};

class point{
private:
    int pointId, clusterId;
    int dimensions;
    vector<double> values;

public:
    point(int id, int *line)
    {
        pointId = id;
        values = Matrice.getValue(line);
        dimensions = values.size();
        clusterId = 0; // Initially not assigned to any cluster
    }

    int getDimensions();

    int getCluster();

    int getID();

    void setCluster(int val);

    double getVal(int pos);

};

class cluster {
    private:
    int clusterId;
    vector<double> centroid;
    vector<point> points;
    public:
    void addPoint(point p);  
        
        
        
};

