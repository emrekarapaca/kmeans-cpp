#include <iostream>
#include "Point.h"
#include "KMeans.h"

int main()
{
    string path = "C:/Users/eeekr/Desktop/KMeans/KMeans/40.txt"; //filepath 
    KMeans obj(path,500,2); //path, #iter, #cluster 
    obj.runKMeans();
    obj.plot2D();
}

