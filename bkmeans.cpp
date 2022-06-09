//program to convert a text file to a matrix
#include <iostream>
#include <fstream>  //for file input/output
#include "bkmeans.h"    //for the matrix class  //include the header file
#include <stdlib.h> 
#include <time.h> 
#include <algorithm> 
#include <math.h>    
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
void classify(Matrice * mat, int k){
    //declare variables
    int sizeH = mat->getH();
    int sizeW = mat->getW();
    int size = sizeH*sizeW;

    
    }




