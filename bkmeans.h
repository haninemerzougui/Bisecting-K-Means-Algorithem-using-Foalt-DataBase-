#include <iostream>

class Matrice {
  int sizeH, sizeW; 
  float *vect; 
  public:
    Matrice(int nbl, int nbc, float *Vtemp); //constructor
    Matrice(char * base);     //convert a text file to a matrix
    float getValue(int i, int j);  //get value from the matrix
    float setValue(int i, int j, float value); //set value in the matrix
    int getH();
    int getW();


};

struct Point {
    double x, y;     // coordinates
    int cluster;     // no default cluster
    double minDist;  // default infinite dist to nearest cluster

    Point() : 
        x(0.0), 
        y(0.0),
        cluster(-1),
        minDist(__DBL_MAX__) {}
        
    Point(double x, double y) : 
        x(x), 
        y(y),
        cluster(-1),
        minDist(__DBL_MAX__) {}

    double distance(Point p) {
        return (p.x - x) * (p.x - x) + (p.y - y) * (p.y - y);
    }
};