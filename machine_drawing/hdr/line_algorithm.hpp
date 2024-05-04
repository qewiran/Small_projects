#ifndef LINE_ALGORITHM_HPP
#define LINE_ALGORITHM_HPP
#include "opencv2/core/types.hpp"
#include <cmath>


void bresenhamLineUp(cv::Mat, cv::Point2i, cv::Point2i, size_t );
void bresenhamLineDown(cv::Mat, cv::Point2i, cv::Point2i, size_t);

void bresenhamLine(cv::Mat, cv::Point2i, cv::Point2i, size_t);

void dda(cv::Mat, cv::Point2i, cv::Point2i);
#endif
