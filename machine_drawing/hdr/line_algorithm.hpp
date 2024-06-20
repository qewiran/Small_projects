#ifndef LINE_ALGORITHM_HPP
#define LINE_ALGORITHM_HPP
#include <opencv2/core/types.hpp>
#include <cmath>
#include <vector>

std::vector<cv::Point2i> bresenhamLineUp(cv::Mat, cv::Point2i, cv::Point2i,
                                         size_t);
std::vector<cv::Point2i> bresenhamLineDown(cv::Mat, cv::Point2i, cv::Point2i,
                                           size_t);

std::vector<cv::Point2i> bresenhamLine(cv::Mat, cv::Point2i, cv::Point2i,
                                       size_t);

void dda(cv::Mat, cv::Point2i, cv::Point2i);
void drawCircle(cv::Mat, cv::Point2i, int);
#endif
