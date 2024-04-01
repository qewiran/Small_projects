#ifndef LINE_ALGORITHM_HPP
#define LINE_ALGORITHM_HPP
#include "opencv2/core.hpp"

#include <cmath>
#include <iostream>


void bresenhamLineUp(cv::Mat, cv::Point2i, cv::Point2i);
void bresenhamLineDown(cv::Mat, cv::Point2i, cv::Point2i);

void bresenhamLine(cv::Mat, cv::Point2i, cv::Point2i);

void dda(cv::Mat, cv::Point2i, cv::Point2i);
#endif