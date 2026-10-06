# Bisecting-K-Means-Algorithem-using-Foalt-DataBase-
Bisecting K-Means using C++ 

files:

    src/bkmeans.h     the classes (Matrice, point, cluster, bkmeans)
    src/bkmeans.cpp   the code of the classes and the algorithm
    src/mainbk.cpp    main
    data/base.txt     the database (1000 lines, 19 columns)

compile:

    make

or

    g++ -o bk src/mainbk.cpp src/bkmeans.cpp

run (from the main folder):

    ./bk

the program reads data/base.txt (first line = number of lines and columns), every line is a point.
the number of clusters is N in bkmeans.h. the result is written in result.txt
