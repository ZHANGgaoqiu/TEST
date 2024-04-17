#include <iostream>
#include <vector>
#include <cmath>
#include "imgproc.h"
#include "bina.h"

using namespace std;


// 定义灰度图像像素数据的一维数组
//unsigned char binaData[307200];

int main() {

    // 定义图像大小
    int WIDTH = 640;
    int HEIGHT = 480;

    vector<vector<int>> image(HEIGHT, vector<int>(WIDTH, 0));
    // 将一维数组中的数据复制到二维数组中
    for (int i = 0; i < HEIGHT; ++i) {
        for (int j = 0; j < WIDTH; ++j) {
            // 根据一维数组的索引计算二维数组的索引
            int index = i * WIDTH + j;
            // 复制数据
        image[i][j] = binaData[index];
        }
    }
    /*// 生成随机图像作为示例
    for (int y = 0; y < IMAGE_HEIGHT; ++y) {
        for (int x = 0; x < IMAGE_WIDTH; ++x) {
            if (rand() % 2 == 0) {
                image[y][x] = 255;
            }
        }
    }*/

    // 进行Canny边缘检测
    vector<vector<int>> edgeMap = cannyEdgeDetection(image, WIDTH, HEIGHT);


    // 进行霍夫变换提取边缘直线
    vector<pair<double, double>> lines = houghTransform(edgeMap, WIDTH, HEIGHT);

    // 输出直线参数
    for (const auto& line : lines) {
        cout << "Line parameters: (" << line.first << ", " << line.second << ")" << endl;
    }

    return 0;
}
