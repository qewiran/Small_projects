#ifndef TRANSFORM_HPP
#define TRANSFORM_HPP
#include "opencv2/core/matx.hpp"
#include <array>
#include <opencv2/core.hpp>
#include <vector>
#include <utility>

template <typename T, size_t ROWS, size_t COLS>
struct TransformMatx : public cv::Matx<T, ROWS, COLS> {

  TransformMatx(const cv::Matx<T, ROWS, COLS> &base)
      : cv::Matx<T, ROWS, COLS>(base) {}
  TransformMatx(const cv::Matx<T, COLS, ROWS> &base)
      : cv::Matx<T, ROWS, COLS>(base.t()) {}

  TransformMatx(const cv::Matx<T, ROWS - 1, COLS> &matInit, T w) {
    for (size_t i = 0; i < ROWS - 1; ++i) {
      for (size_t j = 0; j < COLS; ++j) {
        (*this)(i, j) = matInit(i, j);
      }
    }

    for (size_t j = 0; j < COLS; ++j) {
      (*this)(ROWS - 1, j) = w;
    }
  }

  TransformMatx rotate(double angle, size_t axis1, size_t axis2) {
    angle = std::numbers::pi * angle / 180.;

    auto rotationMatx = cv::Matx<T, ROWS, ROWS>::eye();
    rotationMatx(axis1, axis1) = std::cos(angle);
    rotationMatx(axis1, axis2) = -std::sin(angle);
    rotationMatx(axis2, axis1) = std::cos(angle);
    rotationMatx(axis2, axis2) = std::sin(angle);

    return (*this).t() * rotationMatx;
  }

  TransformMatx parTransp(const std::array<T, ROWS - 1> &transpVals) {
    auto transpMatx = cv::Matx<T, ROWS, ROWS>::eye();
    for (size_t j = 0; j < ROWS - 1; ++j)
      transpMatx(ROWS - 1, j) = transpVals[j];
    return (*this).t() * transpMatx;
  }

  TransformMatx scale(const std::array<T, ROWS - 1> scaleFactors) {
    auto scaleMatx = cv::Matx<T, ROWS, ROWS>::eye();
    for (size_t i = 0; i < ROWS - 1; ++i)
      scaleMatx(i, i) = scaleFactors[i];

    return (*this).t() * scaleMatx ;
  }
};

template<typename T, size_t ROWS>
using TransformColVec = TransformMatx<T,ROWS,1>;

template <typename T, size_t COLS>
using TransformRowVec = TransformMatx<T,1,COLS>;

enum class ProjCategory {
  AXON_ISOMETRIC = 1,
  AXON_DIMETRIC,
  AXON_TRIMETRIC,
  PERSPECTIVE_1P,
  PERSPECTIVE_2P,
  PERSPECTIVE_3P
};

template <typename T, size_t N>
TransformColVec<T, N>
axonometricProj(const TransformColVec<T, N> &coordinate, ProjCategory projCat,
            const std::vector<T> &angles = {45., 45.},
            const std::vector<std::pair<size_t, size_t>> &axesOrder = {
                {1, 2}, {0, 2}}) {
  TransformColVec<T, N> result = coordinate;
  for (size_t i = 0; i < static_cast<size_t>(projCat); ++i) {
    result = result.rotate(angles[i], axesOrder[i].first, axesOrder[i].second);
  }
  auto orthogonalProj = cv::Matx<T, N, N>::eye();
  orthogonalProj(2, 2) = static_cast<T>(0);
  result = result.t() * orthogonalProj;
  return result;
}
template <typename T, size_t N>
TransformColVec<T, N> perspectiveProj(const TransformColVec<T, N> &coordinate,
                                      int projCat, size_t axis, T projCenter) {
  TransformColVec<T, N> result = coordinate;
  auto perspectiveMat = cv::Matx<T, N, N>::eye();
  perspectiveMat(axis, axis) = static_cast<T>(0);
  T r = -coordinate[axis] / projCenter;
  perspectiveMat(axis, N - 1) = r;
  result = result.t() * perspectiveMat;
  return result;
}
#endif // TRANSFORM_HPP
