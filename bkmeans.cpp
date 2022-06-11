//program to convert a text file to a matrix
#include <iostream>
#include <fstream>  //for file input/output
#include "bkmeans.h"    //for the matrix class  //include the header file
#include <stdlib.h> 
#include <time.h> 
#include <algorithm> 
#include <math.h>    
#include <map>
#include <iterator> 
#include <vector>  //for the vector class
#include <sstream>  //for the stringstream class
#define N 6 //number of clusters

using namespace std;
//function to create matrix
Matrice :: Matrice(int nbl, int nbc, float *Vtemp){
    //declare variables
    int sizeH, sizeW;
    //initialize variables
    sizeH = nbl;
    sizeW = nbc;
    int size = nbl*nbc;
    float *vect = new float[size];  //convert the matrix to a vector
    //loop through the matrix
    for(int i = 0; i < size; i++){
        vect[i] = Vtemp[i];
    }
    //declare the point vector
}


//function to convert a text file to a matrix
Matrice :: Matrice(char * base){
    //open the file
    ifstream fileIn(base);
    //check if the file is open
    if(fileIn.is_open()){
        fileIn >> sizeH;
        fileIn >> sizeW;
        vect = new float[sizeH*sizeW];
        int size = sizeH*sizeW;
        //loop through the file
        for(int i = 0; i < size; i++){
            fileIn >> vect[i];
        }
    }
}


float Matrice :: outMatrice(char * base){
    //open the file
    ofstream fileOut(base);
    //check if the file is open
    if(fileOut.is_open()){
        fileOut << sizeH << "   ";
        fileOut << sizeW <<endl;
        vect = new float[sizeH*sizeW];
        int size = sizeH*sizeW;
        //loop through the file
        for(int i = 0; i < size; i++){
            fileOut << vect[i];
        }
    }
    fileOut.close();
}


//function to get values from the matrix
float Matrice :: getValue(int i, int j){
    return vect[i*sizeW + j];
}
//function to set values in the matrix
float Matrice :: setValue(int i, int j, float value){
    return vect[i*sizeW + j];
}
//function to get sizeH
int Matrice :: getH(){
    return sizeH;
}
//function to get sizeW
int Matrice :: getW(){
    return sizeW;
}

//function to classify the matrix with the bisecting k-means algorithm
cluster :: cluster(Matrice* mat, int clusterId, point centroid){
 
        
            this->clusterId = clusterId; // Assign cluster ID
            for (int i = 0; i < centroid.getDimensions(); i++)
        {
            this->centroid.push_back(centroid.getVal(i));
        }
        this->addPoint(centroid);

        void addPoint(point p){
        p.setCluster(this->clusterId);
        points.push_back(p);
    }

    bool removePoint(int pointId)
    {
        int size = points.size();

        for (int i = 0; i < size; i++)
        {
            if (points[i].getID() == pointId)
            {
                points.erase(points.begin() + i);
                return true;
            }
        }
        return false;
    }

    void removeAllPoints() { 
        points.clear(); }

    int getId() {
        return clusterId; }

    point :: getPoint(int pos) { 
        return points[pos]; }

    int getSize() { 
        return points.size(); }

    double getCentroidByPos(int pos) { 
        return centroid[pos]; }

    void setCentroidByPos(int pos, double val) {
        this->centroid[pos] = val; }
    



}


point :: point(int id, int *line){
    {
        pointId = id;
        dimensions = values.size();
        clusterId = 0; // Initially not assigned to any cluster
    }

    int point :: getDimensions() {
        return dimensions; }

    int point :: getCluster() {
        return clusterId; }

    int point :: getID() {
        return pointId; }

    void point :: setCluster(int val) {
        clusterId = val; }

    double point :: getVal(int pos) {
        return values[pos]; }
}




