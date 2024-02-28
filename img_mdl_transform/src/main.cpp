#include "../hdr/ColorImage.hpp"
#include "../hdr/ColorSystemTypes.hpp"
#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include <typeinfo>
#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;

int main()
{
    vector<vector<Point<u_char>>> v;

    v.resize(1, vector<Point<u_char>>(1));
    cv::Mat matRGB(cv::Size2d(1, 1), CV_8UC3);

    for (size_t i = 0; i < 1; ++i)
        for (size_t j = 0; j < 1; ++j)
        {
            v.at(i).at(j) = std::make_tuple(100, 20, 45);
            matRGB.at<cv::Vec3b>(i, j) = cv::Vec3b(100, 20, 45);
        }

    cv::Mat matHSV;
    cv::cvtColor(matRGB, matHSV, cv::COLOR_RGB2HSV);

    std::cout << "matHSV:\n" << matHSV << '\n';

    RGB rgb{ v };
    // std::cout << "rgb:\n" << rgb << '\n';

    HSV hsv = static_cast<HSV>(rgb);
    std::cout << "hsv:\n" << hsv << '\n';





}