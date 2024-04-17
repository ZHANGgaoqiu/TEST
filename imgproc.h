//imgproc.h
#ifndef IMGPROC_H
#define IMGPROC_H

#include <iostream>
#include <vector>
#include <cmath>


vector<vector<int>> cannyEdgeDetection(const vector<vector<int>>& image, int IMAGE_WIDTH, int IMAGE_HEIGHT);
vector<pair<double, double>> houghTransform(const vector<vector<int>>& edgeMap, int IMAGE_WIDTH, int IMAGE_HEIGHT) ;


#endif