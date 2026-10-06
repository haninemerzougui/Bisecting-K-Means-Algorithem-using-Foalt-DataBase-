#include <iostream>
#include <time.h>
#include "bkmeans.h"

using namespace std;

int main(){
    srand(time(NULL));
    //create matrix containing txt file
    Matrice * mat = new Matrice("data/base.txt");
    if(mat->getH() == 0){
        delete mat;
        return 1;
    }

    //print the size of the matrix
    cout << "sizeH: " << mat->getH() << endl; //height
    cout << "sizeW: " << mat->getW() << endl; //width
    cout << "size: " << mat->getH()*mat->getW() << endl; //total size

    //every line of the matrix is a point
    vector<point> all_points;
    for(int i = 0; i < mat->getH(); i++){
        point p(i, mat, i);
        all_points.push_back(p);
    }

    //bisecting k-means with N clusters, 100 iterations max and 10 trials for each split
    bkmeans bk(N, 100, 10);
    bk.run(all_points);
    bk.print();

    //save the result
    bk.outResult("result.txt");
    cout << "result saved in result.txt" << endl;

    delete mat;
    return 0;
}
