#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <cmath>
#include <iostream>


void bresenhamLineUp(cv::Mat, cv::Point2i, cv::Point2i);
void bresenhamLineDown(cv::Mat, cv::Point2i, cv::Point2i);

void bresenhamLine(cv::Mat, cv::Point2i, cv::Point2i);