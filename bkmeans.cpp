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
float Matrice :: setValue(int i, int j){
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
cluster :: cluster(int clusterId, point centroid){
 
        
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
        values = getValue(line);
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




void bkmeans :: clearClusters(){

    for (int i = 0; i < k; i++)
    {
        clusters[i].removeAllPoints();
    }
    
}

int bkmeans :: getNearestClusterId(point point)
    {
        double sum = 0.0, min_dist;
        int NearestClusterId;
        if(dimensions==1) {
            min_dist = abs(clusters[0].getCentroidByPos(0) - point.getVal(0));
        }	
        else 
        {
          for (int i = 0; i < dimensions; i++)
          {
             sum += pow(clusters[0].getCentroidByPos(i) - point.getVal(i), 2.0);
             // sum += abs(clusters[0].getCentroidByPos(i) - point.getVal(i));
          }
          min_dist = sqrt(sum);
        }
        NearestClusterId = clusters[0].getId();

        for (int i = 1; i < k; i++)
        {
            double dist;
            sum = 0.0;
            
            if(dimensions==1) {
                  dist = abs(clusters[i].getCentroidByPos(0) - point.getVal(0));
            } 
            else {
              for (int j = 0; j < dimensions; j++)
              {
                  sum += pow(clusters[i].getCentroidByPos(j) - point.getVal(j), 2.0);
                  // sum += abs(clusters[i].getCentroidByPos(j) - point.getVal(j));
              }

              dist = sqrt(sum);
              // dist = sum;
            }
            if (dist < min_dist)
            {
                min_dist = dist;
                NearestClusterId = clusters[i].getId();
            }
        }

        return NearestClusterId;
    }





