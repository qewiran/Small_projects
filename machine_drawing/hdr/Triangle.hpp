#include <iostream>
#include <opencv2/core.hpp>
#include <vector>
struct Triangle {

  cv::Point2i v1;
  cv::Point2i v2;
  cv::Point2i v3;

  Triangle(cv::Point2i v1, cv::Point2i v2, cv::Point2i v3)
      : v1(v1), v2(v2), v3(v3) {}

  friend std::ostream &operator<<(std::ostream &stream, const Triangle &t);
};

void drawTriangle(cv::Mat, const Triangle &);