#ifndef SHAPE_HPP
#define SHAPE_HPP

#include "opencv2/core.hpp"
#include <iostream>
struct Triangle {

  cv::Point2i v1;
  cv::Point2i v2;
  cv::Point2i v3;

  Triangle(cv::Point2i v1, cv::Point2i v2, cv::Point2i v3)
      : v1(v1), v2(v2), v3(v3) {}

  friend std::ostream &operator<<(std::ostream &stream, const Triangle &t);
};

void drawTriangle(cv::Mat, const Triangle &);

void drawRectangle(cv::Mat, const cv::Rect2i &);

// struct Rect {
//   cv::Point2i v1;
//   cv::Point2i v2;
//   cv::Point2i v3;
//   cv::Point2i v4;

//   Parallelogramm(cv::Point2i v1, cv::Point2i v2, cv::Point2i v3, cv::Point2i
//   v4)
//       : v1(v1), v2(v2), v3(v3), v4(v4) {}
//   friend std::ostream &operator<<(std::ostream &stream,
//                                   const Parallelogramm &t);
// };

#endif