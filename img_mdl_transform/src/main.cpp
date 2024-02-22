#include "../hdr/ColorImage.hpp"
#include "../hdr/ColorSystemTypes.hpp"
// #include "opencv2/core.hpp"
// #include "opencv2/imgproc.hpp"
#include <typeinfo>
#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;

struct A
{
    A() { std::cout << "A ctr\n"; }
    A(int) { std::cout << "A overloaded ctr\n"; }
};

struct B : public A
{
    B() { std::cout << "B ctr\n"; }
    B(int v): A(v) { std::cout << "B overloaded ctr\n"; }
};

int main()
{
    vector<vector<Point<u_char>>> v;

    v.resize(5, vector<Point<u_char>>(5));
    // // cv::Mat matRGB(cv::Size2d(5, 5), CV_8UC3);

    for (size_t i = 0; i < 5; ++i)
        for (size_t j = 0; j < 5; ++j)
        {
            v.at(i).at(j) = std::make_tuple(i * 10 + 100 * j, i * 5 + 10 * j, 100 * i + 10 * j);
    //         // matRGB.at<cv::Vec3b>(i, j) = cv::Vec3b(i * 10 + 100 * j, i * 5 + 10 * j, 100 * i + 10 * j);
        }

    // cv::Mat matHSV;
    // cv::cvtColor(matRGB, matHSV, cv::COLOR_RGB2HSV);

    // std::cout << "matHSV:\n" << matHSV << '\n';

    RGB rgb(v);
    // std::cout << "rgb:\n" << rgb << '\n';

    // Lab lab = static_cast<Lab>(rgb);

    // HSV hsv = static_cast<HSV>(rgb);
    // std::cout << "hsv:\n" << hsv << '\n';

    // RGB rgb_new = static_cast<RGB>(hsv);
    // std::cout << "rgb:\n" << rgb << '\n';



}