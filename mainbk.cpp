#include <iostream>
#include "bkmeans.h"

using namespace std;

int main(){
    //create matrix containing txt file
    Matrice * mat = new Matrice("base.txt");
    //print the first element of the matrix
    cout << mat->getValue(0,0) << endl;
    //print the last element of the matrix1235
    cout << mat->getValue(mat->getH()-1, mat->getW()-1) << endl;
    //print all the elements of the matrix
    for(int i = 0; i < mat->getH(); i++){
        for(int j = 0; j < mat->getW(); j++){
            cout << mat->getValue(i,j) << " ";
        }
        cout << endl;
    }

    
    return 0;
}