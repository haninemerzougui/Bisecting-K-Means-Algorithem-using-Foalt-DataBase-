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
    //initialize variables
    sizeH = nbl;
    sizeW = nbc;
    int size = nbl*nbc;
    vect = new float[size];  //convert the matrix to a vector
    //loop through the matrix
    for(int i = 0; i < size; i++){
        vect[i] = Vtemp[i];
    }
}


//function to convert a text file to a matrix
Matrice :: Matrice(const char * base){
    sizeH = 0;
    sizeW = 0;
    vect = NULL;
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
        fileIn.close();
    }
    else{
        cout << "can't open the file " << base << endl;
    }
}

//destructor
Matrice :: ~Matrice(){
    delete [] vect;
}


void Matrice :: outMatrice(const char * base){
    //open the file
    ofstream fileOut(base);
    //check if the file is open
    if(fileOut.is_open()){
        fileOut << sizeH << "   ";
        fileOut << sizeW <<endl;
        //loop through the matrix
        for(int i = 0; i < sizeH; i++){
            for(int j = 0; j < sizeW; j++){
                fileOut << vect[i*sizeW + j] << "\t";
            }
            fileOut << endl;
        }
    }
    fileOut.close();
}


//function to get values from the matrix
float Matrice :: getValue(int i, int j){
    return vect[i*sizeW + j];
}
//function to set values in the matrix
void Matrice :: setValue(int i, int j, float value){
    vect[i*sizeW + j] = value;
}
//function to get sizeH
int Matrice :: getH(){
    return sizeH;
}
//function to get sizeW
int Matrice :: getW(){
    return sizeW;
}


//function to create a point from a line of the matrix
point :: point(int id, Matrice* mat, int line){
    pointId = id;
    for(int j = 0; j < mat->getW(); j++){
        values.push_back(mat->getValue(line, j));
    }
    dimensions = values.size();
    clusterId = 0; // Initially not assigned to any cluster
}

int point :: getDimensions() { return dimensions; }

int point :: getCluster() { return clusterId; }

int point :: getID() { return pointId; }

void point :: setCluster(int val) { clusterId = val; }

double point :: getVal(int pos) { return values[pos]; }


//function to create a cluster with one point as centroid
cluster :: cluster(int clusterId, point centroid){
    this->clusterId = clusterId; // Assign cluster ID
    for (int i = 0; i < centroid.getDimensions(); i++)
    {
        this->centroid.push_back(centroid.getVal(i));
    }
    this->addPoint(centroid);
}

//function to create a cluster with a list of points
cluster :: cluster(int clusterId, vector<point> pts){
    this->clusterId = clusterId;
    if(pts.size() > 0){
        this->centroid.resize(pts[0].getDimensions(), 0.0);
    }
    for(int i = 0; i < (int)pts.size(); i++){
        this->addPoint(pts[i]);
    }
    this->updateCentroid();
}

void cluster :: addPoint(point p){
    p.setCluster(this->clusterId);
    points.push_back(p);
}

bool cluster :: removePoint(int pointId)
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

void cluster :: removeAllPoints() { points.clear(); }

int cluster :: getId() { return clusterId; }

//change the id of the cluster and of all its points
void cluster :: setId(int id){
    clusterId = id;
    for(int i = 0; i < (int)points.size(); i++){
        points[i].setCluster(id);
    }
}

point cluster :: getPoint(int pos) { return points[pos]; }

int cluster :: getSize() { return points.size(); }

double cluster :: getCentroidByPos(int pos) { return centroid[pos]; }

void cluster :: setCentroidByPos(int pos, double val) { this->centroid[pos] = val; }

//function to recalculate the centroid (mean of all the points)
void cluster :: updateCentroid(){
    int size = points.size();
    if(size == 0) return;  //nothing to do, keep the old centroid
    for(int j = 0; j < (int)centroid.size(); j++){
        double sum = 0.0;
        for(int i = 0; i < size; i++){
            sum += points[i].getVal(j);
        }
        centroid[j] = sum / size;
    }
}

//function to calculate the sum of squared errors
double cluster :: getSSE(){
    double sse = 0.0;
    for(int i = 0; i < (int)points.size(); i++){
        for(int j = 0; j < (int)centroid.size(); j++){
            double d = points[i].getVal(j) - centroid[j];
            sse += d*d;
        }
    }
    return sse;
}


//bisecting k-means
bkmeans :: bkmeans(int K, int iters, int trials){
    this->K = K;
    this->iters = iters;    //max iterations of k-means
    this->trials = trials;  //how many times we try to split a cluster
    dimensions = 0;
}

//euclidean distance between a point and a centroid
double bkmeans :: distance(point p, vector<double> c){
    double sum = 0.0;
    for(int j = 0; j < dimensions; j++){
        sum += pow(p.getVal(j) - c[j], 2.0);
    }
    return sqrt(sum);
}

//function to split a cluster in 2 with the normal k-means (k = 2)
void bkmeans :: kmeans2(cluster c, cluster &c1, cluster &c2){
    int size = c.getSize();
    vector<double> cent1(dimensions), cent2(dimensions);

    //choose 2 different random points as the first centroids
    int r1 = rand() % size;
    int r2 = rand() % size;
    while(r2 == r1){
        r2 = rand() % size;
    }
    for(int j = 0; j < dimensions; j++){
        cent1[j] = c.getPoint(r1).getVal(j);
        cent2[j] = c.getPoint(r2).getVal(j);
    }

    vector<int> assign(size, -1);
    int iter = 0;
    bool changed = true;
    while(changed && iter < iters){
        changed = false;
        //assign every point to the nearest centroid
        for(int i = 0; i < size; i++){
            point p = c.getPoint(i);
            int a;
            if(distance(p, cent1) <= distance(p, cent2)) a = 0;
            else a = 1;
            if(a != assign[i]){
                assign[i] = a;
                changed = true;
            }
        }
        //recalculate the 2 centroids
        vector<double> sum1(dimensions, 0.0), sum2(dimensions, 0.0);
        int n1 = 0, n2 = 0;
        for(int i = 0; i < size; i++){
            point p = c.getPoint(i);
            for(int j = 0; j < dimensions; j++){
                if(assign[i] == 0) sum1[j] += p.getVal(j);
                else sum2[j] += p.getVal(j);
            }
            if(assign[i] == 0) n1++;
            else n2++;
        }
        for(int j = 0; j < dimensions; j++){
            if(n1 > 0) cent1[j] = sum1[j] / n1;
            if(n2 > 0) cent2[j] = sum2[j] / n2;
        }
        iter++;
    }

    //put the points in the 2 new clusters
    vector<point> pts1, pts2;
    for(int i = 0; i < size; i++){
        if(assign[i] == 0) pts1.push_back(c.getPoint(i));
        else pts2.push_back(c.getPoint(i));
    }
    //if one of them is empty we just cut the cluster in 2
    if(pts1.size() == 0 || pts2.size() == 0){
        pts1.clear();
        pts2.clear();
        for(int i = 0; i < size; i++){
            if(i < size/2) pts1.push_back(c.getPoint(i));
            else pts2.push_back(c.getPoint(i));
        }
    }
    c1 = cluster(c.getId(), pts1);
    c2 = cluster(c.getId(), pts2);
}

void bkmeans :: run(vector<point> &all_points){
    if(all_points.size() == 0) return;
    dimensions = all_points[0].getDimensions();
    if(K > (int)all_points.size()) K = all_points.size();

    //at the begining all the points are in the same cluster
    clusters.clear();
    clusters.push_back(cluster(1, all_points));

    while((int)clusters.size() < K){
        //find the cluster with the biggest SSE (we can't split a cluster with 1 point)
        int pos = -1;
        double maxSSE = -1.0;
        for(int i = 0; i < (int)clusters.size(); i++){
            if(clusters[i].getSize() > 1 && clusters[i].getSSE() > maxSSE){
                maxSSE = clusters[i].getSSE();
                pos = i;
            }
        }
        if(pos == -1) break;

        //try to split it many times and keep the best split
        cluster best1 = clusters[pos], best2 = clusters[pos];
        double bestSSE = -1.0;
        for(int t = 0; t < trials; t++){
            cluster c1 = clusters[pos], c2 = clusters[pos];
            kmeans2(clusters[pos], c1, c2);
            double sse = c1.getSSE() + c2.getSSE();
            if(bestSSE < 0 || sse < bestSSE){
                bestSSE = sse;
                best1 = c1;
                best2 = c2;
            }
        }
        cout << "split a cluster of " << clusters[pos].getSize() << " points"
             << " -> " << best1.getSize() << " + " << best2.getSize() << endl;

        //replace the old cluster by the 2 new ones
        clusters.erase(clusters.begin() + pos);
        clusters.push_back(best1);
        clusters.push_back(best2);
    }

    //give the final id to every cluster and update the points
    for(int i = 0; i < (int)clusters.size(); i++){
        clusters[i].setId(i+1);
        for(int k = 0; k < clusters[i].getSize(); k++){
            int id = clusters[i].getPoint(k).getID();
            all_points[id].setCluster(i+1);
        }
    }
}

//write the cluster of every point in a file
void bkmeans :: outResult(const char * base){
    ofstream fileOut(base);
    if(fileOut.is_open()){
        for(int i = 0; i < (int)clusters.size(); i++){
            fileOut << "Cluster " << clusters[i].getId() << " (" << clusters[i].getSize() << " points)" << endl;
            fileOut << "centroid: ";
            for(int j = 0; j < dimensions; j++){
                fileOut << clusters[i].getCentroidByPos(j) << " ";
            }
            fileOut << endl << "points: ";
            for(int k = 0; k < clusters[i].getSize(); k++){
                fileOut << clusters[i].getPoint(k).getID() << " ";
            }
            fileOut << endl << endl;
        }
    }
    fileOut.close();
}

void bkmeans :: print(){
    double total = 0.0;
    for(int i = 0; i < (int)clusters.size(); i++){
        cout << "cluster " << clusters[i].getId() << " : " << clusters[i].getSize()
             << " points, SSE = " << clusters[i].getSSE() << endl;
        total += clusters[i].getSSE();
    }
    cout << "total SSE: " << total << endl;
}
