#include <iostream>
#include <stdlib.h>
#include <vector>
#define N 6 //number of clusters

using namespace std;

class Matrice {
  int sizeH, sizeW;
  float *vect;
  public:
    Matrice(int nbl, int nbc, float *Vtemp); //constructor
    Matrice(const char * base);     //convert a text file to a Inmatrix
    ~Matrice();   //destructor
    void outMatrice(const char * base);
    float getValue(int i, int j);  //get value from the matrix
    void setValue(int i, int j, float value); //set value in the matrix
    int getH();
    int getW();
};

class point {
private:
    int pointId, clusterId;
    int dimensions;
    vector<double> values;

public:
    point(int id, Matrice* mat, int line);  //take the line of the matrix as a point

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
    cluster(int clusterId, point centroid);
    cluster(int clusterId, vector<point> pts);  //cluster with all the points
    void addPoint(point p);
    bool removePoint(int pointId);
    void removeAllPoints();
    int getId();
    void setId(int id);
    point getPoint(int pos);
    int getSize();
    double getCentroidByPos(int pos);
    void setCentroidByPos(int pos, double val);
    void updateCentroid();   //centroid = mean of the points
    double getSSE();   //sum of squared errors of the cluster
};

class bkmeans {
    private:
    int K, iters, trials;
    int dimensions;
    vector<cluster> clusters;
    double distance(point p, vector<double> c);
    void kmeans2(cluster c, cluster &c1, cluster &c2);  //split a cluster in 2
    public:
    bkmeans(int K, int iters, int trials);
    void run(vector<point> &all_points);
    void outResult(const char * base);
    void print();
};
