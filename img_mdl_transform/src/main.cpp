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

    v.resize(5, vector<Point<u_char>>(5));
    cv::Mat matRGB(cv::Size2d(5, 5), CV_8UC3);

    for (size_t i = 0; i < 5; ++i)
        for (size_t j = 0; j < 5; ++j)
        {
            v.at(i).at(j) = std::make_tuple(i * 10 + 100 * j, i * 5 + 10 * j, 100 * i + 10 * j);
            matRGB.at<cv::Vec3b>(i, j) = cv::Vec3b(i * 10 + 100 * j, i * 5 + 10 * j, 100 * i + 10 * j);
        }

    // cv::Mat matXYZ;
    // cv::cvtColor(matRGB, matXYZ, cv::COLOR_RGB2XYZ);

    std::cout << "matRGB:\n" << matRGB << '\n';

    RGB rgb{ v };
    // std::cout << "rgb:\n" << rgb << '\n';

    CMYK cmyk = static_cast<CMYK>(rgb);
    std::cout << "lab:\n" << cmyk << '\n';





}