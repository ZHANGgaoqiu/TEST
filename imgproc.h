//imgproc.h
#ifndef IMGPROC_H
#define IMGPROC_H

#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

// 定义图像大小
const int IMAGE_WIDTH = 10;
const int IMAGE_HEIGHT = 10;

vector<vector<int>> cannyEdgeDetection(const vector<vector<int>>& image);
vector<pair<double, double>> houghTransform(const vector<vector<int>>& edgeMap) ;


#endif