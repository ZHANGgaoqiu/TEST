#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

// 定义图像大小
const int IMAGE_WIDTH = 10;
const int IMAGE_HEIGHT = 10;

// 定义Canny边缘检测函数
vector<vector<int>> cannyEdgeDetection(const vector<vector<int>>& image) {
    // 声明Sobel算子
    vector<vector<int>> sobelX = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    vector<vector<int>> sobelY = {{1, 2, 1}, {0, 0, 0}, {-1, -2, -1}};

    // 计算梯度幅值
    vector<vector<int>> gradientMagnitude(IMAGE_HEIGHT, vector<int>(IMAGE_WIDTH, 0));
    for (int y = 1; y < IMAGE_HEIGHT - 1; ++y) {
        for (int x = 1; x < IMAGE_WIDTH - 1; ++x) {
            int gx = 0, gy = 0;
            for (int i = -1; i <= 1; ++i) {
                for (int j = -1; j <= 1; ++j) {
                    gx += sobelX[i + 1][j + 1] * image[y + i][x + j];
                    gy += sobelY[i + 1][j + 1] * image[y + i][x + j];
                }
            }
            gradientMagnitude[y][x] = sqrt(gx * gx + gy * gy);
        }
    }

    // 非极大值抑制
    vector<vector<int>> edgeMap(IMAGE_HEIGHT, vector<int>(IMAGE_WIDTH, 0));
    for (int y = 1; y < IMAGE_HEIGHT - 1; ++y) {
        for (int x = 1; x < IMAGE_WIDTH - 1; ++x) {
            int dx = (gradientMagnitude[y][x + 1] - gradientMagnitude[y][x - 1]) / 2;
            int dy = (gradientMagnitude[y + 1][x] - gradientMagnitude[y - 1][x]) / 2;
            if (gradientMagnitude[y][x] >= max(gradientMagnitude[y + dy][x + dx], gradientMagnitude[y - dy][x - dx])) {
                edgeMap[y][x] = gradientMagnitude[y][x];
            }
        }
    }

    return edgeMap;
}

// 定义霍夫变换提取边缘直线函数
vector<pair<double, double>> houghTransform(const vector<vector<int>>& edgeMap) {
    vector<pair<double, double>> lines;

    // 定义霍夫空间的参数范围
    const int rhoMax = hypot(IMAGE_HEIGHT, IMAGE_WIDTH);
    const int thetaMax = 180;
    const int rhoResolution = 1;
    const int thetaResolution = 1;

    // 初始化霍夫累加器
    vector<vector<int>> accumulator(rhoMax / rhoResolution, vector<int>(thetaMax / thetaResolution, 0));

    // 在霍夫空间中进行累加
    for (int y = 0; y < IMAGE_HEIGHT; ++y) {
        for (int x = 0; x < IMAGE_WIDTH; ++x) {
            if (edgeMap[y][x] > 0) {
                for (int theta = 0; theta < thetaMax; theta += thetaResolution) {
                    double thetaRadians = theta * M_PI / 180.0;
                    int rho = round(x * cos(thetaRadians) + y * sin(thetaRadians));
                    rho += rhoMax / 2; // 调整rho的值到非负范围
                    accumulator[rho / rhoResolution][theta / thetaResolution]++;
                }
            }
        }
    }

    // 从累加器中提取直线
    for (int rhoIdx = 0; rhoIdx < accumulator.size(); ++rhoIdx) {
        for (int thetaIdx = 0; thetaIdx < accumulator[0].size(); ++thetaIdx) {
            if (accumulator[rhoIdx][thetaIdx] > 100) { // 阈值可以根据需要调整
                double rho = rhoIdx * rhoResolution - rhoMax / 2;
                double theta = thetaIdx * thetaResolution * M_PI / 180.0;
                lines.push_back({rho, theta});
            }
        }
    }

    return lines;
}


int main() {
    // 生成随机图像作为示例
    vector<vector<int>> image(IMAGE_HEIGHT, vector<int>(IMAGE_WIDTH, 0));
    for (int y = 0; y < IMAGE_HEIGHT; ++y) {
        for (int x = 0; x < IMAGE_WIDTH; ++x) {
            if (rand() % 2 == 0) {
                image[y][x] = 255;
            }
        }
    }

    // 进行Canny边缘检测
    vector<vector<int>> edgeMap = cannyEdgeDetection(image);

    // 进行霍夫变换提取边缘直线
    vector<pair<double, double>> lines = houghTransform(edgeMap);

    // 输出直线参数
    for (const auto& line : lines) {
        cout << "Line parameters: (" << line.first << ", " << line.second << ")" << endl;
    }

    return 0;
}
