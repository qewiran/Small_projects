#include "line_algorithm.hpp"
#include "shape.hpp"
#include <opencv2/core/types.hpp>
#include <sys/types.h>

static double eps = 1e-14;

void LBclip(cv::Mat img, const Rectangle<cv::Point2i> &clipRect, cv::Point2i p1,
            cv::Point2i p2);

template <size_t N>
std::array<cv::Point2i, N> getNormals(const Polygon<N> &poly) {
  std::array<cv::Point2i, N> result{};
  for (size_t i = 1; i < N; ++i) {
    auto dp = poly.at(i) - poly.at(i - 1);
    result.at(i - 1) = cv::Point2i(-dp.y, dp.x);
  }
  auto dp = poly.at(N - 1) - poly.at(0);
  result.at(N - 1) = cv::Point2i(-dp.y, dp.x);

  return result;
};

template <size_t N>
void CBclip(cv::Mat img, const Polygon<N, cv::Point2i> &poly, const std::array<cv::Point2i, N>& normals, cv::Point2i p1,
            cv::Point2i p2) {
  double t0 = 0;
  double t1 = 1;

  auto it = poly.cbegin();
  auto end = poly.cend();
  auto normal = normals.cbegin();

  for (; it != end; ++it, ++normal) {
    double Q = (p1 - *it).dot(*normal);
    double P = (p2 - p1).dot(*normal);

    if (std::abs(P) < eps) {
      if (Q < 0) { // not in window
        break;
      }
    } else {
      double t = -Q / P;
      if (t < 1 && t > 0) {
        if (P < 0) {
          if (t < t1)
            t1 = t;

        } else {
          if (t > t0)
            t0 = t;
        }
      }
    }
  }
  bresenhamLine(img, p1+t0*(p2-p1), p1+t1*(p2-p1), 255);
};
