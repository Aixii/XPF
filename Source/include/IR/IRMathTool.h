#ifndef IRMATHTOOL_H
#define IRMATHTOOL_H

//#include <iostream>
#include <vector>

#define PI 3.141592653589793
#define R2D (180.0 / PI)
#define D2R (PI / 180.0)

using namespace std;

namespace IRMathTool {
// 最小二乘法拟合二维直线，y=kx+b
template <typename T>
static bool leastSquaresFittingLine(vector<pair<T, T>>& points, T& k, T& b) {
    int n = points.size();
    if (n < 2)
        return false;

    // 分别为x、y、xy和x的平方的和
    T sum_x = 0, sum_y = 0, sum_xy = 0, sum_x2 = 0;
    for (int i = 0; i < n; i++) {
        sum_x += points[i].first; // x的和
        sum_y += points[i].second; // y的和
        sum_xy += points[i].first * points[i].second; // xy的和
        sum_x2 += points[i].first * points[i].first; // x平方和
    }
    k = (sum_xy - sum_x * sum_y / n) / (sum_x2 - sum_x * sum_x / n);
    b = (sum_y - k * sum_x) / n;
    return true;
}

/*
    #define N 5//散点数量

//二维直线拟合，y=kx+b
void Least_Squares_1(float x[], float y[], float n, float &k, float &b)
{
    //分别为x、y、xy和x的平方的和
    float sum_x = 0, sum_y = 0, sum_xy = 0, sum_x2 = 0;
    for (int i = 0; i < n; i++)
    {
        sum_x += x[i];//x的和
        sum_y += y[i];//y的和
        sum_xy += x[i] * y[i];//xy的和
        sum_x2 += x[i] * x[i];//x平方和
    }
    k = (sum_xy - sum_x * sum_y / n) / (sum_x2 - sum_x * sum_x / n);
    b = (sum_y - k * sum_x) / n;
    cout << "拟合出来的函数为：" << "y=" << k << "x" << (b >= 0 ? "+" : "") << b << endl;
}

    //二次曲线拟合，y=ax^2+bx+c
    void Least_Squares_2(float x[], float y[], float n, float &a, float &b, float &c)
    {
        float sum_x = 0, sum_y = 0, sum_xy = 0, sum_x2 = 0, sum_x3 = 0, sum_x4 = 0, \
            sum_x2y = 0;//分别为x、y、xy和x的平方的和
        for (int i = 0; i < n; i++)
        {
            sum_x += x[i];//x的和
            sum_y += y[i];//y的和
            sum_xy += x[i] * y[i];//xy的和
            sum_x2 += x[i] * x[i];//x的平方和
            sum_x3 += x[i] * x[i] * x[i];//x的立方和
            sum_x4 += x[i] * x[i] * x[i] * x[i];//x的四次方和
            sum_x2y += x[i] * x[i] * y[i];//(x^2)(y)的和
        }
        a = (sum_x2y - sum_x2 * sum_y / n + (sum_xy - sum_x * sum_y / n) *
            (sum_x2 * sum_x / n - sum_x3) / (sum_x2 - sum_x * sum_x / n)) /
            (sum_x4 - sum_x2 * sum_x2 / n + (sum_x2*sum_x / n - sum_x3)*
            (sum_x3 - sum_x2 * sum_x / n) / (sum_x2 - sum_x * sum_x / n));
        b = (sum_xy - a * sum_x3 - sum_x * sum_y / n + a * sum_x2*sum_x / n) /
            (sum_x2 - sum_x * sum_x / n);
        c = (sum_y - b * sum_x - a * sum_x2) / n;
        cout << "拟合出来的函数为：" << "y=" << a << "x^2" <<
            (b >= 0 ? "+" : "") << b << "x" << (c >= 0 ? "+" : "") << c << endl;
    }

    int main()
    {
        float k, b;//拟合出来的系数，y=kx+b
        float a, c;
        float x1[N] = { 1, 1.25, 1.5,1.75,2 };//课件例题，使用Least_Squares_1进行拟合
        float y1[N] = { 5.1,5.79,6.53,7.45,8.46 };
        Least_Squares_1(x1, y1, N, k, b);
        float x2[N] = { 1, 2, 3,4,5 };//取函数y=0.3x^2+0.7x-7的点验证二次拟合
        float y2[N] = { -6, -4.4, -2.2,0.6,4 };
        Least_Squares_2(x2, y2, N, a, b, c);
        return 0;
    }
    */
}

#endif // IRMATHTOOL_H
