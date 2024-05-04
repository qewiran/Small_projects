#ifndef SHAPE_HPP
#define SHAPE_HPP

#include "line_algorithm.hpp"
#include "opencv2/core/types.hpp"
#include "opencv2/core/mat.hpp"
#include <iostream>

using color_t = size_t;
template <size_t vertexCount, typename PointT = cv::Point2i> class Polygon {
  std::array<PointT, vertexCount> points;

public:
  using Iterator = std::array<PointT, vertexCount>::iterator;
  using ConstIterator = std::array<PointT, vertexCount>::const_iterator;

  Iterator begin() { return points.begin(); }
  ConstIterator begin() const { return points.cbegin(); }
  ConstIterator cbegin() const { return points.cbegin(); }
  Iterator end() { return points.end(); }
  ConstIterator end() const { return points.cend(); }
  ConstIterator cend() const { return points.cend(); }

  Polygon(const std::array<PointT, vertexCount>& points)
      : points(points) {}
  Polygon(const Polygon &other) : points(other.points) {}
  Polygon() {}

  auto& at(size_t pos) { return points.at(pos); }
  const auto& at(size_t pos) const { return const_cast<const PointT&>(points.at(pos));}

  void draw(cv::Mat img, color_t color) const {
    ConstIterator it = this->cbegin();
    ConstIterator it2 = it + 1;
    ConstIterator end = this->cend();
    for (; it != end - 1; ++it, ++it2) {
      bresenhamLine(img, *it, *it2, color);
    }
    bresenhamLine(img, *(this->cbegin()), *(this->cend() - 1), color);
  }
  template <size_t N, typename PointType>
  friend std::ostream &operator<<(std::ostream &, const Polygon<N,PointType> &);
};
template <typename PointT = cv::Point2i> class Triangle : public Polygon<3> {};

template <typename PointT = cv::Point2i> class Rectangle : public Polygon<4> {
public:
  PointT tl() const {
    return *std::min_element(this->cbegin(), this->cend(),
                             [](cv::Point2i p1, cv::Point2i p2) {
                               return p1.x < p2.x && p1.y < p2.y;
                             });
  }
  PointT br() const {
    return *std::max_element(this->cbegin(), this->cend(),
                             [](cv::Point2i p1, cv::Point2i p2) {
                               return p1.x < p2.x && p1.y < p2.y;
                             });
  }
  Rectangle(const std::array<PointT, 4> &points) : Polygon(points) {}
};


template <size_t vertexCount, typename PointT>
std::ostream &operator<<(std::ostream &stream,
                         const Polygon<vertexCount, PointT> &poly) {
  for (auto v : poly)
    stream << v << " ";
  return stream;
}
#endif
