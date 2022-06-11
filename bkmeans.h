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
    float getValue(float *vect);  //get value from the matrix
    float setValue(float *value); //set value in the matrix
    int getH();
    int getW();
};

class point:public Matrice{
private:
    int pointId, clusterId;
    int dimensions;
    vector<double> values;

public:
    point(int id, int *line)
    {
        pointId = id;
        values = getValue(line);
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
    cluster(int clusterId, point centroid);
        
        
        
};

class bkmeans: public cluster{
    private:
    int k, iters, dimensions, total_points;
    vector<cluster> clusters;
    string output_dir;

    void clearClusters();
    int getNearestClusterId(point point);

    
    public:
    bkmeans(int k, int iterations, string output_dir);
    void run(vector<point> &all_points);

    
    };

